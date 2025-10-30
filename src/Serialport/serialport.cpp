#include "serialport.h"
#include "ui_serialport.h"
#include <QDataStream>
#include <QTimer>  // 添加定时器头文件

// 初始化ui界面
SerialPort::SerialPort(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SerialPort)
{
    ui->setupUi(this);

    // 初始化协议选择
    ui->protocolComboBox->addItem("TCP");
    ui->protocolComboBox->addItem("UDP");

    findFreePorts();

    // 初始化串口
    serialPort = new QSerialPort(this);
    connect(serialPort, &QSerialPort::readyRead, this, [this]() {
        QByteArray recBuf = serialPort->readAll();
        processReceivedData(recBuf);
    });
    isSerialPortConnected = false;

    // 初始化WiFi TCP
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, &QTcpSocket::readyRead, this, [this]() {
        QByteArray recBuf = tcpSocket->readAll();
        processReceivedData(recBuf);
    });
    connect(tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred),
            this, [this](QAbstractSocket::SocketError error) {
                QMessageBox::warning(this, "TCP错误", tcpSocket->errorString());
            });
    isTcpConnected = false;

    // 初始化WiFi UDP
    udpSocket = new QUdpSocket(this);
    connect(udpSocket, &QUdpSocket::readyRead, this, [this]() {
        while (udpSocket->hasPendingDatagrams()) {
            QByteArray datagram;
            datagram.resize(udpSocket->pendingDatagramSize());
            QHostAddress sender;
            quint16 senderPort;
            udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
            processReceivedData(datagram);
        }
    });
    isUdpBound = false;

    // 初始化测试相关变量
    testFlag = false;
    testTimer = new QTimer(this);
    testTimer->setSingleShot(true);  // 单次定时器
    connect(testTimer, &QTimer::timeout, this, &SerialPort::onTestTimeout);

    //设置串口状态标签为绿色 表示等待连接状态
    ui->lblPortState->setStyleSheet("color:red");
    ui->lblWifiState->setStyleSheet("color:red");

    // 发送、接收计数清零
    sendNum = 0;
    recvNum = 0;

    // 初始化接收缓冲区
    recvBuffer.clear();
}

// 析构函数
SerialPort::~SerialPort()
{
    if(serialPort->isOpen()){
        serialPort->close();
    }
    if (tcpSocket->state() == QAbstractSocket::ConnectedState) {
        tcpSocket->disconnectFromHost();
    }
    if (udpSocket->state() == QAbstractSocket::BoundState) {
        udpSocket->close();
    }
    delete ui;
}

// 数据发送函数
void SerialPort::sendData(const QByteArray &data)
{
    int bytesSent = 0;
    int currentProtocol = ui->protocolComboBox->currentIndex();

    if(isSerialPortConnected){
        if (serialPort->isOpen()) {
            bytesSent = serialPort->write(data);
        } else {
            QMessageBox::warning(this, "警告", "串口未打开");
            return;
        }
    }else if (isTcpConnected) {
        bytesSent = tcpSocket->write(data);
    } else if (isUdpBound) {
        QString ip = "192.168.200.1";
        quint16 port = 12312;

        if (ip.isEmpty() || port == 0) {
            QMessageBox::warning(this, "警告", "请输入有效的目标IP和端口");
            return;
        }

        bytesSent = udpSocket->writeDatagram(data, QHostAddress(ip), port);
    }

    // 发送字节计数并显示
    if(bytesSent > 0) {
        sendNum += bytesSent;
        QString sm = "发送字节数量： %1";
        QString revText = sm.arg(sendNum);
        ui->sendNum->setText(revText);
    }
}

// 发送按钮点击槽函数
void SerialPort::on_sendBt_clicked()
{
    // 构建测试数据: 0xAA 0x00 0x01 0x0A
    QByteArray sendArray;
    sendArray.append(static_cast<char>(0xAA));  // 帧头
    sendArray.append(static_cast<char>(0x00));  // 固定数据1
    sendArray.append(static_cast<char>(0x01));  // 固定数据2
    sendArray.append(static_cast<char>(0x0A));  // 帧尾

    // 发送数据
    sendData(sendArray);

    // 在接收框显示发送信息
    ui->recvEdit->append("已发送测试，等待模块回复..");

    // 重置测试标志并启动定时器
    testFlag = false;
    testTimer->start(3000);  // 3秒超时
}

// 测试超时处理函数
void SerialPort::onTestTimeout()
{
    if (!testFlag) {
        ui->recvEdit->append("测试失败!!!");
        testFlag = false;  // 确保标志位重置
    }
}

// 数据处理/////////////////////////////////////////////////////////////////
// 数据处理
void SerialPort::processReceivedData(const QByteArray &recBuf)
{
    // 接收字节计数
    recvNum += recBuf.size();
    QString sm = "接收字节数量： %1";
    QString revText = sm.arg(recvNum);
    ui->recvNum->setText(revText);

    // 将新数据添加到缓冲区
    recvBuffer.append(recBuf);

    // 解析数据
    parseRosData(recBuf);
}

// 初步解析数据，判断帧头帧尾
// 在parseRosData函数中添加参数响应解析
void SerialPort::parseRosData(const QByteArray &recBuf)
{
    static QByteArray buffer;
    buffer.append(recBuf);

    while (buffer.size() > 0) {
        // 查找帧头
        int headIndex = buffer.indexOf(char(0xAA));
        if (headIndex == -1) {
            buffer.clear();
            return;
        }

        // 丢弃帧头前的噪声
        if (headIndex > 0) {
            buffer.remove(0, headIndex);
        }

        // 检查是否有足够的数据
        if (buffer.size() < 3) {
            return; // 等待更多数据
        }

        quint8 command = static_cast<quint8>(buffer.at(1));

        // 根据命令类型确定帧长度
        int frameLength = 0;
        if (command == 0x10 || command == 0x11) {
            // 参数命令帧：AA [命令] [参数ID] [值高字节] [值低字节] 0A (6字节)
            frameLength = 6;
        } else if (command >= 0x01 && command <= 0x03) {
            // ROS话题帧，长度可变，需要查找帧尾
            frameLength = -1; // 表示需要动态查找
        } else if (command == 0x00) {
            // 测试帧：AA 00 01 0A (4字节)
            frameLength = 4;
        } else {
            // 未知命令，丢弃第一个字节继续解析
            buffer.remove(0, 1);
            continue;
        }

        // 对于可变长度帧，查找帧尾
        if (frameLength == -1) {
            int tailIndex = buffer.indexOf(char(0x0A), 2); // 从第3个字节开始查找
            if (tailIndex == -1) {
                return; // 等待更多数据
            }
            frameLength = tailIndex + 1;
        }

        // 检查是否有完整帧
        if (buffer.size() < frameLength) {
            return; // 等待更多数据
        }

        // 提取完整帧
        QByteArray frame = buffer.left(frameLength);
        buffer.remove(0, frameLength);

        // 验证帧头帧尾
        quint8 header = static_cast<quint8>(frame.at(0));
        quint8 tail = static_cast<quint8>(frame.at(frame.size() - 1));

        if (header != 0xAA || tail != 0x0A) {
            qWarning() << "⚠️ 非法帧:" << frame.toHex(' ');
            continue;
        }

        // 根据命令类型分发处理
        if (command >= 0x01 && command <= 0x03) {
            QByteArray payload = frame.mid(2, frame.size() - 3);
            parseRosFrame(command, payload);
        } else if (command == 0x00) {
            parseTestData(frame);
        } else if (command == 0x10 || command == 0x11) {
            // 参数响应帧
            emit parameterResponseReceived(frame);
        }
    }
}

// 测试数据解析函数
void SerialPort::parseTestData(const QByteArray &frame)
{
    // 检查是否为正确的测试回复数据: 0xAA 0x00 0x01 0x0A
    if (frame.size() == 4 &&
        static_cast<quint8>(frame.at(0)) == 0xAA &&
        static_cast<quint8>(frame.at(1)) == 0x00 &&
        static_cast<quint8>(frame.at(2)) == 0x01 &&
        static_cast<quint8>(frame.at(3)) == 0x0A) {

        // 设置测试标志
        testFlag = true;

        // 停止定时器
        testTimer->stop();

        // 在接收框显示成功信息
        ui->recvEdit->append("测试成功，模块通讯正常!!");

        // 重置标志位
        testFlag = false;
    }
}
// 解析ros话题数据
void SerialPort::parseRosFrame(quint8 topicId, const QByteArray &payload)
{
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(payload, &err);
    if (err.error != QJsonParseError::NoError) {
        qWarning() << "JSON解析错误:" << err.errorString();
        return;
    }
    if (!doc.isObject()) return;
    QJsonObject obj = doc.object();
    // qWarning() << "JSON解析结果:" << obj;

    switch (topicId)
    {
    case 0x01: { // TF
        TFMessage::Transform t;
        t.header.frame_id = obj.value("frame_id").toString();
        t.child_frame_id = obj.value("child_frame_id").toString();
        t.x = obj.value("x").toDouble();
        t.y = obj.value("y").toDouble();
        t.z = obj.value("z").toDouble();

        if (obj.contains("qx")) {
            double qx = obj["qx"].toDouble();
            double qy = obj["qy"].toDouble();
            double qz = obj["qz"].toDouble();
            double qw = obj["qw"].toDouble();
            t.yaw = quaternionToYaw(qx, qy, qz, qw);
        }

        // 缓存每个变换
        tfCache[t.header.frame_id + "->" + t.child_frame_id] = t;

        // ✅ 当 map->odom 和 odom->base_link 都存在时，合成 map->base_link
        if (tfCache.contains("map->odom") && tfCache.contains("odom->base_link")) {
            auto mapOdom = tfCache["map->odom"];
            auto odomBase = tfCache["odom->base_link"];

            // yaw 角合成（简单近似）
            double yaw = mapOdom.yaw + odomBase.yaw;
            double cosY = cos(mapOdom.yaw);
            double sinY = sin(mapOdom.yaw);

            // 坐标合成： map→base_link = map→odom + (odom→base_link 在 map 坐标下的平移)
            double x = mapOdom.x + cosY * odomBase.x - sinY * odomBase.y;
            double y = mapOdom.y + sinY * odomBase.x + cosY * odomBase.y;
            double z = mapOdom.z + odomBase.z;   // ✅ z 直接线性叠加（通常odom/base_link只相差很小）

            TFMessage tf;
            TFMessage::Transform result;
            result.header.frame_id = "map";
            result.child_frame_id = "base_link";
            result.x = x;
            result.y = y;
            result.z = z;
            result.yaw = yaw;
            tf.transforms.append(result);

            emit rosTfUpdated(tf);
            // qDebug() << "TF合成为: map->base_link, x=" << x << " y=" << y << " z=" << z << " yaw=" << yaw;
        }

        break;
    }

    case 0x02: { // Scan
        LaserScan scan;
        scan.angle_min = obj.value("angle_min").toDouble();
        scan.angle_max = obj.value("angle_max").toDouble();
        scan.angle_increment = obj.value("angle_increment").toDouble();
        scan.range_min = 0.05;
        scan.range_max = 30.0;
        QJsonArray arr = obj.value("ranges").toArray();
        for (const auto &v : arr)
            scan.ranges.append(v.toDouble());
        emit rosScanUpdated(scan);
        break;
    }

    case 0x03: { // Map
        // qDebug() << "[Map] 接收ASCII数据:" << asciiData;
        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(payload, &err);
        if (err.error != QJsonParseError::NoError) return;
        QJsonObject obj = doc.object();

        OccupancyGrid map;
        map.width = obj.value("width").toInt();
        map.height = obj.value("height").toInt();
        map.resolution = obj.value("resolution").toDouble();
        map.origin_x = obj.value("origin_x").toDouble();
        map.origin_y = obj.value("origin_y").toDouble();

        QJsonArray rle = obj.value("rle").toArray();
        map.data.reserve(map.width * map.height);
        for (auto entry : rle) {
            QJsonArray pair = entry.toArray();
            int value = pair.at(0).toInt();
            int count = pair.at(1).toInt();
            for (int i = 0; i < count; ++i)
                map.data.append(value);
        }

        emit rosMapUpdated(map);
        break;
    }

    default:
        qWarning() << "未知topicId:" << topicId;
    }
}

// 四元数转yaw，在解析ros话题数据中使用
double SerialPort::quaternionToYaw(double x, double y, double z, double w)
{
    // 四元数转偏航角 (yaw) - 绕Z轴旋转
    double siny_cosp = 2.0 * (w * z + x * y);
    double cosy_cosp = 1.0 - 2.0 * (y * y + z * z);
    return std::atan2(siny_cosp, cosy_cosp);
}



// 打开网络通信UDP/TCP//////////////////////////////////////////////////////////
// 打开网络通信UDP/TCP
void SerialPort::on_wifiConnectBt_clicked()
{
    // 根据选择的协议启用相应控件
    QString protocol = ui->protocolComboBox->currentText();
    if(ui->wifiConnectBt->text() == "打开连接"){
        // 禁用串口通信方式
        ui->serialBox->setEnabled(false);
        if (protocol == "TCP"){
            if (!isTcpConnected) {
                // QString ip = "172.27.191.1";
                // quint16 port = 6666;

                QString ip = ui->ipInput->text();
                bool ok;
                quint16 port = ui->portInput->text().toUShort(&ok);
                if (!ok || port == 0) {
                    // 转换失败或端口号为0的处理
                    QMessageBox::warning(this, "错误", "请输入有效的端口号(1-65535)");
                    return;
                }

                qDebug() << "开始连接TCP..." << ip << ":" << port;
                // 禁用代理（关键修复点）
                tcpSocket->setProxy(QNetworkProxy::NoProxy);

                // 连接成功信号
                connect(tcpSocket, &QTcpSocket::connected, this, [this]() {
                    qDebug() << "TCP连接成功！";
                    isTcpConnected = true;
                    ui->wifiConnectBt->setText("关闭连接");
                    ui->lblWifiState->setText("TCP已连接");
                    ui->lblWifiState->setStyleSheet("color:green");
                });

                // 连接超时处理
                QTimer::singleShot(5000, this, [this]() {
                    if (!isTcpConnected) {
                        qDebug() << "TCP连接超时";
                        tcpSocket->abort();
                        QMessageBox::warning(this, "错误", "连接超时，请检查网络和服务器");
                    }
                });

                tcpSocket->connectToHost(ip, port);

            } else {
                QMessageBox::warning(this, "警告", "TCP连接已打开");
            }

        }else if(protocol == "UDP"){
            if (!isUdpBound) {
                // todo 待设置
                quint16 port = 12312;

                if (port == 0) {
                    QMessageBox::warning(this, "警告", "请输入有效的端口号");
                    return;
                }

                if (udpSocket->bind(port)) {
                    isUdpBound = true;
                    ui->wifiConnectBt->setText("关闭连接");
                    ui->lblWifiState->setText("UDP已连接");
                    ui->lblWifiState->setStyleSheet("color:green");
                } else {
                    QMessageBox::warning(this, "错误", "UDP绑定失败");
                }
            } else {
                QMessageBox::warning(this, "警告", "UDP连接已打开");
            }
        }
    }else if(ui->wifiConnectBt->text() == "关闭连接"){
        ui->wifiConnectBt->setText("打开连接");
        if (protocol == "TCP"){
            if (isTcpConnected){
                tcpSocket->disconnectFromHost();
                isTcpConnected = false;
                ui->wifiConnectBt->setText("打开连接");
                ui->lblWifiState->setText("未连接");
                ui->lblWifiState->setStyleSheet("color:red");
            }
        }else if(protocol == "UDP"){
            if (isUdpBound) {
                udpSocket->close();
                isUdpBound = false;

                ui->wifiConnectBt->setText("打开连接");
                ui->lblWifiState->setText("未连接");
                ui->lblWifiState->setStyleSheet("color:red");
            }
        }

        ui->serialBox->setEnabled(true);
    }
}



// 不重要功能和未使用功能//////////////////////////////////////////////////////
//寻找空闲状态串口
void SerialPort::findFreePorts(){
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    for (const auto &port : QSerialPortInfo::availablePorts()) {
        if (!port.isBusy()) {
            ui->portNames->addItem(port.portName());
        }
    };
    if (!ports.size()){
        QMessageBox::warning(NULL,"Tip",QStringLiteral("can not find ports"));
        return;
    };
}

// 检测串口
void SerialPort::on_portSearchBt_clicked()
{
    ui->portNames->clear();
    findFreePorts();
}

// 打开串口
void SerialPort::on_portOpenBt_clicked()
{
    // 设置WifiBox不可选
    ui->wifiBox->setEnabled(false);

    qint32 baudRate = 921600;
    QSerialPort::DataBits dataBits;
    QSerialPort::StopBits stopBits;
    QSerialPort::Parity checkBits;

    // 设置默认波特率921600
    // baudRate=QSerialPort::Baud115200;
    // 设置默认数据位
    dataBits=QSerialPort::Data8;
    // 设置默认停止位
    stopBits=QSerialPort::OneStop;
    // 设置默认校验位
    checkBits = QSerialPort::NoParity;
    // 初始化串口属性，设置 端口号、波特率、数据位、停止位、奇偶校验位数
    // qDebug() << "portNames: " << ui->portNames->currentText();
    serialPort->setPortName(ui->portNames->currentText());
    serialPort->setBaudRate(baudRate);
    serialPort->setDataBits(dataBits);
    serialPort->setStopBits(stopBits);
    serialPort->setParity(checkBits);

    // 如果打开成功，反转打开按钮显示和功能。打开失败，无变化，并且弹出错误对话框。
    if(ui->portOpenBt->text() == "打开串口"){
        if(serialPort->open(QIODevice::ReadWrite) == true){
            isSerialPortConnected=true;
            ui->portOpenBt->setText("关闭串口");
            // 让端口号下拉框不可选，避免误操作（选择功能不可用，控件背景为灰色）
            ui->portNames->setEnabled(false);
            QString sm = "%1 串口已打开";
            QString status = sm.arg(serialPort->portName());
            ui->lblPortState->setText(status);
            ui->lblPortState->setStyleSheet("color:green");
        }else{
            QMessageBox::critical(this, "错误", "串口打开失败，请检查串口是否被占用");
            QString sm = "%1 串口不可用";
            QString status = sm.arg(serialPort->portName());
            ui->lblPortState->setText(status);
            ui->lblPortState->setStyleSheet("color:red");
        };


    }else{
        serialPort->close();
        isSerialPortConnected=false;
        ui->portOpenBt->setText("打开串口");
        // 端口号下拉框恢复可选，避免误操作
        ui->portNames->setEnabled(true);
        //statusBar 状态栏显示端口状态
        QString sm = "%1 串口已关闭";
        QString status = sm.arg(serialPort->portName());
        ui->lblPortState->setText(status);
        ui->lblPortState->setStyleSheet("color:red");
    };
}

// 接收字节数统计归零
void SerialPort::on_clearRecvBt_clicked()
{
    ui->recvEdit->clear();
    // 清除发送、接收字节计数
    recvNum = 0;
    QString sm = "接收字节数量： 0";
    ui->recvNum->setText(sm);
}

// 发送字节数统计归零
void SerialPort::on_btnClearSend_clicked()
{
    // 清除发送、接收字节计数
    sendNum = 0;
    QString sm = "发送字节数量： 0";
    ui->sendNum->setText(sm);
}
