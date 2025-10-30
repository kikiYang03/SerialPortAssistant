#include "params.h"
#include "ui_params.h"
#include <QHBoxLayout>
#include <QDebug>

Params::Params(QWidget *parent, SerialPort *serialPort)
    : QWidget(parent)
    , ui(new Ui::Params)
    , m_isGroupFolded(false)
    , m_serialPort(serialPort)
{
    ui->setupUi(this);

    // 设置表格属性
    setupTable();

    // 初始化参数
    setupParameters();

    // 连接参数响应信号（需要在SerialPort中添加这个信号）
    if (m_serialPort) {
        // 注意：需要在SerialPort类中添加parameterResponseReceived信号
        // connect(m_serialPort, &SerialPort::parameterResponseReceived,
        //         this, &Params::onParameterResponseReceived);
    }
}

Params::~Params()
{
    delete ui;
}

void Params::setSerialPort(SerialPort *serialPort)
{
    m_serialPort = serialPort;
    if (m_serialPort) {
        // 连接参数响应信号
        // connect(m_serialPort, &SerialPort::parameterResponseReceived,
        //         this, &Params::onParameterResponseReceived);
    }
}

void Params::setupTable()
{
    // 设置表格列数和标题
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "" << "参数ID" << "参数名称" << "参数值" << "值范围" << "说明");

    // 设置表格属性
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setAlternatingRowColors(true);

    // 设置列宽
    ui->tableWidget->setColumnWidth(0, 30);
    ui->tableWidget->setColumnWidth(1, 80);
    ui->tableWidget->setColumnWidth(2, 120);
    ui->tableWidget->setColumnWidth(3, 150);
    ui->tableWidget->setColumnWidth(4, 120);
}

void Params::setupParameters()
{
    // 定义参数数据
    struct Parameter {
        QString id;
        QString name;
        QString range;
        QString description;
        int defaultValue;
    };

    QVector<Parameter> parameters = {
        {"0x00", "雷达型号", "0-1", "0=N10, 其他=N10_P", 0},
        {"-", "雷达放置位置", "-", "-", 0},
        {"0x01", "X坐标", "0-65535", "位置X坐标值", 0},
        {"0x02", "Y坐标", "0-65535", "位置Y坐标值", 0},
        {"0x03", "Z坐标", "0-65535", "位置Z坐标值", 0},
        {"0x04", "Roll角度", "0-65535", "滚转角", 0},
        {"0x05", "Pitch角度", "0-65535", "俯仰角", 0},
        {"0x06", "Yaw角度", "0-65535", "偏航角", 0}
    };

    // 设置行数
    ui->tableWidget->setRowCount(parameters.size());

    // 填充表格
    for (int row = 0; row < parameters.size(); ++row) {
        const Parameter &param = parameters[row];

        // 在0x01添加折叠按钮
        if (row == 1) {
            QPushButton *foldButton = new QPushButton();
            foldButton->setText("−");
            foldButton->setFixedSize(20, 20);
            foldButton->setProperty("folded", false);
            connect(foldButton, &QPushButton::clicked, this, &Params::onFoldButtonClicked);
            ui->tableWidget->setCellWidget(row, 0, foldButton);
        } else {
            QTableWidgetItem *emptyItem = new QTableWidgetItem();
            ui->tableWidget->setItem(row, 0, emptyItem);
        }

        // 参数ID
        QTableWidgetItem *idItem = new QTableWidgetItem(param.id);
        ui->tableWidget->setItem(row, 1, idItem);

        // 参数名称
        QTableWidgetItem *nameItem = new QTableWidgetItem(param.name);
        ui->tableWidget->setItem(row, 2, nameItem);

        // 值范围
        QTableWidgetItem *rangeItem = new QTableWidgetItem(param.range);
        ui->tableWidget->setItem(row, 4, rangeItem);

        // 说明
        QTableWidgetItem *descItem = new QTableWidgetItem(param.description);
        ui->tableWidget->setItem(row, 5, descItem);

        // 为参数值创建输入控件
        QWidget *valueWidget = createValueWidget(param.id, param.range, param.defaultValue);
        valueWidgets.append(valueWidget);
        ui->tableWidget->setCellWidget(row, 3, valueWidget);
    }

    // 默认展开所有行
    m_isGroupFolded = false;
}

// 填写表格初始信息
QWidget* Params::createValueWidget(const QString &id, const QString &range, int defaultValue)
{
    QWidget *widget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(widget);
    layout->setContentsMargins(5, 2, 5, 2);

    if (id == "0x00") {
        QComboBox *comboBox = new QComboBox();
        comboBox->addItem("N10", 0);
        comboBox->addItem("N10_P", 1);
        comboBox->setCurrentIndex(defaultValue);
        layout->addWidget(comboBox);
    } else if(id == "-"){

    }else {
        QSpinBox *spinBox = new QSpinBox();
        QStringList rangeParts = range.split("-");
        if (rangeParts.size() == 2) {
            spinBox->setRange(rangeParts[0].toInt(), rangeParts[1].toInt());
        }
        spinBox->setValue(defaultValue);
        layout->addWidget(spinBox);
    }

    return widget;
}

// 构建通信协议
QByteArray Params::buildParameterFrame(quint8 command, const QString &paramId, int value)
{
    QByteArray frame;

    // 帧头: AA
    frame.append(static_cast<char>(0xAA));

    // 命令类型：0x10=读取, 0x11=写入
    frame.append(static_cast<char>(command));

    // 参数ID（转换为字节）
    bool ok;
    quint8 paramByte = paramId.toUShort(&ok, 0); // 支持0x格式
    if (!ok) {
        qWarning() << "参数ID转换失败:" << paramId;
        return QByteArray();
    }
    frame.append(static_cast<char>(paramByte));

    // 对于写入命令，添加参数值（2字节，大端序）
    if (command == 0x11) {
        // 值高字节
        frame.append(static_cast<char>((value >> 8) & 0xFF));
        // 值低字节
        frame.append(static_cast<char>(value & 0xFF));
    }

    // 帧尾: 0A
    frame.append(static_cast<char>(0x0A));

    return frame;
}

// 读取参数
void Params::sendParameterReadRequest(const QString &paramId)
{
    if (!m_serialPort) {
        QMessageBox::warning(this, "错误", "通信接口未初始化");
        return;
    }

    QByteArray frame = buildParameterFrame(0x10, paramId);
    if (frame.isEmpty()) {
        QMessageBox::warning(this, "错误", "构建读取帧失败");
        return;
    }

    // 使用公共的sendData方法
    m_serialPort->sendData(frame);

    qDebug() << "发送参数读取请求:" << paramId << "数据:" << frame.toHex(' ');
}
// 写入参数
void Params::sendParameterWriteRequest(const QString &paramId, int value)
{
    if (!m_serialPort) {
        QMessageBox::warning(this, "错误", "通信接口未初始化");
        return;
    }

    QByteArray frame = buildParameterFrame(0x11, paramId, value);
    if (frame.isEmpty()) {
        QMessageBox::warning(this, "错误", "构建写入帧失败");
        return;
    }

    // 使用公共的sendData方法
    m_serialPort->sendData(frame);

    qDebug() << "发送参数写入请求:" << paramId << "值:" << value << "数据:" << frame.toHex(' ');
}
// 解析参数响应帧
void Params::parseParameterResponse(const QByteArray &data)
{
    // 读取响应格式: AA 10 [参数ID] [值高字节] [值低字节] 0A
    // 写入响应格式: AA 11 [参数ID] [值高字节] [值低字节] 0A

    if (data.size() != 6) {
        qWarning() << "参数响应帧长度错误，期望6字节，实际:" << data.size();
        return;
    }

    quint8 header = static_cast<quint8>(data.at(0));
    quint8 command = static_cast<quint8>(data.at(1));
    quint8 paramId = static_cast<quint8>(data.at(2));
    quint8 valueHigh = static_cast<quint8>(data.at(3));
    quint8 valueLow = static_cast<quint8>(data.at(4));
    quint8 tail = static_cast<quint8>(data.at(5));

    if (header != 0xAA || tail != 0x0A) {
        qWarning() << "参数响应帧头尾错误";
        return;
    }

    if (command != 0x10 && command != 0x11) {
        qWarning() << "未知的命令类型:" << command;
        return;
    }

    // 提取参数值（2字节，大端序）
    int value = (valueHigh << 8) | valueLow;

    QString paramIdStr = QString("0x%1").arg(paramId, 2, 16, QLatin1Char('0')).toUpper();

    qDebug() << "收到参数响应: 命令=" << command << "参数=" << paramIdStr << "值=" << value;

    // 更新界面显示
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        QTableWidgetItem *idItem = ui->tableWidget->item(row, 1);
        if (idItem && idItem->text().compare(paramIdStr, Qt::CaseInsensitive) == 0) {
            QWidget *widget = valueWidgets[row];
            QLayout *layout = widget->layout();
            if (layout && layout->count() > 0) {
                QWidget *valueControl = layout->itemAt(0)->widget();
                if (QComboBox *comboBox = qobject_cast<QComboBox*>(valueControl)) {
                    // 对于雷达型号参数，直接设置索引
                    if (paramIdStr == "0x00") {
                        comboBox->setCurrentIndex(value);
                    } else {
                        // 其他参数使用组合框的情况
                        comboBox->setCurrentIndex(value);
                    }
                } else if (QSpinBox *spinBox = qobject_cast<QSpinBox*>(valueControl)) {
                    spinBox->setValue(value);
                }
            }
            qDebug() << "更新界面参数:" << paramIdStr << "=" << value;
            break;
        }
    }
}

void Params::onParameterResponseReceived(const QByteArray &data)
{
    parseParameterResponse(data);
}

// 槽函数
void Params::on_readButton_clicked()
{
    if (!m_serialPort) {
        QMessageBox::warning(this, "错误", "通信接口未初始化");
        return;
    }

    // 使用公共的getter方法检查连接状态
    if (!m_serialPort->getIsTcpConnected() &&
        !m_serialPort->getIsUdpBound() &&
        !m_serialPort->getIsSerialPortConnected()) {
        QMessageBox::warning(this, "错误", "请先建立通信连接");
        return;
    }

    // 发送所有参数的读取请求
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        // 跳过折叠的行
        if (m_isGroupFolded && row >= 1 && row <= 5) continue;

        QTableWidgetItem *idItem = ui->tableWidget->item(row, 1);
        if (idItem) {
            // 添加小延迟，避免连续发送
            QTimer::singleShot(row * 100, this, [this, id = idItem->text()]() {
                sendParameterReadRequest(id);
            });
        }
    }

    QMessageBox::information(this, "读取参数", "正在获取当前模块的参数...");
}


void Params::on_writeButton_clicked()
{
    if (!m_serialPort) {
        QMessageBox::warning(this, "错误", "通信接口未初始化");
        return;
    }

    // 使用公共的getter方法检查连接状态
    if (!m_serialPort->getIsTcpConnected() &&
        !m_serialPort->getIsUdpBound() &&
        !m_serialPort->getIsSerialPortConnected()) {
        QMessageBox::warning(this, "错误", "请先建立通信连接");
        return;
    }

    // 从界面读取值并发送写入请求
    int writeCount = 0;
    for (int row = 0; row < valueWidgets.size(); ++row) {
        // 跳过折叠的行
        if (m_isGroupFolded && row >= 1 && row <= 5) continue;

        QTableWidgetItem *idItem = ui->tableWidget->item(row, 1);
        if (!idItem) continue;

        QWidget *widget = valueWidgets[row];
        QLayout *layout = widget->layout();
        if (layout && layout->count() > 0) {
            QWidget *valueControl = layout->itemAt(0)->widget();
            if (QComboBox *comboBox = qobject_cast<QComboBox*>(valueControl)) {
                int value = comboBox->currentData().toInt();
                // 添加小延迟，避免连续发送
                QTimer::singleShot(writeCount * 100, this, [this, id = idItem->text(), value]() {
                    sendParameterWriteRequest(id, value);
                });
                writeCount++;
            } else if (QSpinBox *spinBox = qobject_cast<QSpinBox*>(valueControl)) {
                int value = spinBox->value();
                // 添加小延迟，避免连续发送
                QTimer::singleShot(writeCount * 100, this, [this, id = idItem->text(), value]() {
                    sendParameterWriteRequest(id, value);
                });
                writeCount++;
            }
        }
    }

    if (writeCount > 0) {
        QMessageBox::information(this, "写入参数", QString("正在将 %1 个参数写入模块...").arg(writeCount));
    } else {
        QMessageBox::warning(this, "警告", "没有找到需要写入的参数");
    }
}

void Params::onFoldButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    if (m_isGroupFolded) {
        // 展开第3-8行（索引2-7）
        for (int row = 2; row <= 7; ++row) {
            ui->tableWidget->setRowHidden(row, false);
        }
        button->setText("−");
        m_isGroupFolded = false;
    } else {
        // 折叠第3-8行（索引2-7）
        for (int row = 2; row <= 7; ++row) {
            ui->tableWidget->setRowHidden(row, true);
        }
        button->setText("+");
        m_isGroupFolded = true;
    }
}

void Params::on_defaultButton_clicked()
{
    restoreDefaultValues();
    QMessageBox::information(this, "恢复默认", "正在恢复参数的默认值...");
}

// 写入参数
void Params::updateTableFromWidgets()
{
    // 从界面控件读取值
    for (int row = 0; row < valueWidgets.size(); ++row) {
        // 跳过折叠的行
        if (m_isGroupFolded && row >= 1 && row <= 5) continue;

        QWidget *widget = valueWidgets[row];
        QLayout *layout = widget->layout();
        if (layout && layout->count() > 0) {
            QWidget *valueControl = layout->itemAt(0)->widget();
            if (QComboBox *comboBox = qobject_cast<QComboBox*>(valueControl)) {
                int value = comboBox->currentData().toInt();
                // 处理下拉框值
                qDebug() << "参数" << row << "值:" << value;
            } else if (QSpinBox *spinBox = qobject_cast<QSpinBox*>(valueControl)) {
                int value = spinBox->value();
                // 处理数字输入框值
                qDebug() << "参数" << row << "值:" << value;
            }
        }
    }
}

// 恢复默认参数
void Params::restoreDefaultValues()
{
    for (int row = 0; row < valueWidgets.size(); ++row) {
        // 跳过折叠的行
        if (m_isGroupFolded && row >= 1 && row <= 5) continue;

        QWidget *widget = valueWidgets[row];
        QLayout *layout = widget->layout();
        if (layout && layout->count() > 0) {
            QWidget *valueControl = layout->itemAt(0)->widget();
            if (QComboBox *comboBox = qobject_cast<QComboBox*>(valueControl)) {
                comboBox->setCurrentIndex(0); // 默认选择第一个
            } else if (QSpinBox *spinBox = qobject_cast<QSpinBox*>(valueControl)) {
                spinBox->setValue(0); // 默认值为0
            }
        }
    }
}
