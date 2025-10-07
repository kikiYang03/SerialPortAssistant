#include "serialport.h"
#include "ui_serialport.h"

SerialPort::SerialPort(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SerialPort)
{
    ui->setupUi(this);
    findFreePorts();

    serialPort = new QSerialPort(this);
    connect(serialPort,SIGNAL(readyRead()),this,SLOT(manual_serialPortReadyRead()));

    //设置串口状态标签为绿色 表示等待连接状态
    ui->lblPortState->setStyleSheet("color:red");

    // 状态栏
    QStatusBar *sBar = new QStatusBar(this);
    // 发送、接收计数清零
    sendNum = 0;
    recvNum = 0;

    // 状态栏的收、发计数标签
    lblSendNum = new QLabel(this);
    lblRecvNum = new QLabel(this);

    // 设置标签最小大小
    lblSendNum->setMinimumSize(100, 20);
    lblRecvNum->setMinimumSize(100, 20);
    setNumOnLabel(lblSendNum, "S: ", sendNum);
    setNumOnLabel(lblRecvNum, "R: ", recvNum);
    // 从右往左依次添加
    sBar->addPermanentWidget(lblSendNum);
    sBar->addPermanentWidget(lblRecvNum);


}

SerialPort::~SerialPort()
{
    delete ui;
}

//寻找空闲状态串口
void SerialPort::findFreePorts(){
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    for (int i = 0; i < ports.size(); ++i){
        if (ports.at(i).isBusy()){
            ports.removeAt(i);
            continue;
        }
        ui->portNames->addItem(ports.at(i).portName());
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
    QSerialPort::BaudRate baudRate;
    QSerialPort::DataBits dataBits;
    QSerialPort::StopBits stopBits;
    QSerialPort::Parity checkBits;

    // 获取串口波特率
    // baudRate = ui->baundrateCb->currentText().toInt();直接字符串转换为 int 的方法

    // if(ui->baundrateCb->currentText()=="1200")
    //     baudRate=QSerialPort::Baud1200;
    // else if(ui->baundrateCb->currentText()=="2400")
    //     baudRate=QSerialPort::Baud2400;
    // else if(ui->baundrateCb->currentText()=="4800")
    //     baudRate=QSerialPort::Baud4800;
    // else if(ui->baundrateCb->currentText()=="9600")
    //     baudRate=QSerialPort::Baud9600;
    // else if(ui->baundrateCb->currentText()=="19200")
    //     baudRate=QSerialPort::Baud19200;
    // else if(ui->baundrateCb->currentText()=="38400")
    //     baudRate=QSerialPort::Baud38400;
    // else if(ui->baundrateCb->currentText()=="57600")
    //     baudRate=QSerialPort::Baud57600;
    // else if(ui->baundrateCb->currentText()=="115200")
    //     baudRate=QSerialPort::Baud115200;

    // 设置默认波特率9600
    baudRate=QSerialPort::Baud9600;

    // 获取串口数据位
    // if(ui->databitCb->currentText()=="5")
    //     dataBits=QSerialPort::Data5;
    // else if(ui->databitCb->currentText()=="6")
    //     dataBits=QSerialPort::Data6;
    // else if(ui->databitCb->currentText()=="7")
    //     dataBits=QSerialPort::Data7;
    // else if(ui->databitCb->currentText()=="8")
    //     dataBits=QSerialPort::Data8;

    // 设置默认数据位
    dataBits=QSerialPort::Data8;

    // 获取串口停止位
    // if(ui->stopbitCb->currentText()=="1")
    //     stopBits=QSerialPort::OneStop;
    // else if(ui->stopbitCb->currentText()=="1.5")
    //     stopBits=QSerialPort::OneAndHalfStop;
    // else if(ui->stopbitCb->currentText()=="2")
    //     stopBits=QSerialPort::TwoStop;

    // 设置默认停止位
    stopBits=QSerialPort::OneStop;

    // 获取串口奇偶校验位
    // if(ui->checkbitCb->currentText() == "none"){
    //     checkBits = QSerialPort::NoParity;
    // }else if(ui->checkbitCb->currentText() == "奇校验"){
    //     checkBits = QSerialPort::OddParity;
    // }else if(ui->checkbitCb->currentText() == "偶校验"){
    //     checkBits = QSerialPort::EvenParity;
    // }else{

    // }

    // 设置默认校验位
    checkBits = QSerialPort::NoParity;

    // 初始化串口属性，设置 端口号、波特率、数据位、停止位、奇偶校验位数
    qDebug() << "portNames: " << ui->portNames->currentText();
    serialPort->setPortName(ui->portNames->currentText());
    serialPort->setBaudRate(baudRate);
    serialPort->setDataBits(dataBits);
    serialPort->setStopBits(stopBits);
    serialPort->setParity(checkBits);

    // 根据初始化好的串口属性，打开串口
    // 如果打开成功，反转打开按钮显示和功能。打开失败，无变化，并且弹出错误对话框。
    if(ui->portOpenBt->text() == "打开串口"){
        if(serialPort->open(QIODevice::ReadWrite) == true){
            ui->portOpenBt->setText("关闭串口");
            // 让端口号下拉框不可选，避免误操作（选择功能不可用，控件背景为灰色）
            ui->portNames->setEnabled(false);
        }else{
            QMessageBox::critical(this, "error", "port open fail!check the port is used");
        };
        //statusBar 状态栏显示端口状态
        QString sm = "%1 Opened";
        QString status = sm.arg(serialPort->portName());
        ui->lblPortState->setText(status);
        ui->lblPortState->setStyleSheet("color:green");
    }else{
        serialPort->close();
        ui->portOpenBt->setText("打开串口");
        // 端口号下拉框恢复可选，避免误操作
        ui->portNames->setEnabled(true);
        //statusBar 状态栏显示端口状态
        QString sm = "%1 Closed";
        QString status = sm.arg(serialPort->portName());
        ui->lblPortState->setText(status);
        ui->lblPortState->setStyleSheet("color:red");
    };
}

// 手动实现接收数据函数
void SerialPort::manual_serialPortReadyRead()
{
    QByteArray recBuf = serialPort->readAll();
    QString str_rev;

    // 接收字节计数
    recvNum += recBuf.size();
    // 状态栏显示计数值
    setNumOnLabel(lblRecvNum, "R: ", recvNum);
    QDateTime nowtime = QDateTime::currentDateTime();
    str_rev = "[" + nowtime.toString("yyyy-MM-dd hh:mm:ss") + "] ";
    str_rev = QString(recBuf).append("\r\n");

    // if(ui->chk_rev_hex->checkState() == false){
    //     if(ui->chk_rev_time->checkState() == Qt::Checked){
    //         QDateTime nowtime = QDateTime::currentDateTime();
    //         str_rev = "[" + nowtime.toString("yyyy-MM-dd hh:mm:ss") + "] ";
    //         str_rev += QString(recBuf).append("\r\n");
    //     }
    //     else{
    //         // 在当前位置插入文本，不会发生换行。如果没有移动光标到文件结尾，会导致文件超出当前界面显示范围，界面也不会向下滚动。
    //         //ui->recvEdit->appendPlainText(buf);
    //         if(ui->chk_rev_line->checkState() == Qt::Checked){
    //             str_rev = QString(recBuf).append("\r\n");
    //         }
    //         else
    //         {
    //             str_rev = QString(recBuf);
    //         }
    //     };
    // }else{

    //     // 16进制显示，并转换为大写
    //     QString str1 = recBuf.toHex().toUpper();//.data();
    //     // 添加空格
    //     QString str2;
    //     for(int i = 0; i<str1.length (); i+=2)
    //     {
    //         str2 += str1.mid (i,2);
    //         str2 += " ";
    //     };
    //     if(ui->chk_rev_time->checkState() == Qt::Checked)
    //     {
    //         QDateTime nowtime = QDateTime::currentDateTime();
    //         str_rev = "[" + nowtime.toString("yyyy-MM-dd hh:mm:ss") + "] ";
    //         str_rev += str2.append("\r\n");
    //     }
    //     else
    //     {
    //         if(ui->chk_rev_line->checkState() == Qt::Checked)
    //             str_rev += str2.append("\r\n");
    //         else
    //             str_rev = str2;

    //     };
    // };
    ui->recvEdit->insertPlainText(str_rev);
    ui->recvEdit->moveCursor(QTextCursor::End);
}

// 状态栏标签显示计数值
void SerialPort::setNumOnLabel(QLabel *lbl, QString strS, long num)
{
    // 标签显示
    QString strN;
    strN.sprintf("%ld", num);
    QString str = strS + strN;
    lbl->setText(str);
}

