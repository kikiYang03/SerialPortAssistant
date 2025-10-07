#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QMainWindow>
#include <QSerialPort>
#include <QString>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QTimer>
#include <QPainter>
#include <QDebug>
#include <QStatusBar>
#include <QDateTime>


namespace Ui {
class SerialPort;
}

class SerialPort : public QWidget
{
    Q_OBJECT

public:
    explicit SerialPort(QWidget *parent = nullptr);
    ~SerialPort();

    QSerialPort *serialPort;

protected:
    void findFreePorts();  //查找可用串口
    bool initSerialPort(); //初始化串口连接
    void sendMsg(const QString &msg); //发送消息

private slots:
    void on_portSearchBt_clicked();
    void on_portOpenBt_clicked();
    // 手动连接槽函数
    void manual_serialPortReadyRead();

private:
    Ui::SerialPort *ui;

    // 发送、接收字节计数
    long sendNum, recvNum;
    QLabel *lblSendNum;
    QLabel *lblRecvNum;
    void setNumOnLabel(QLabel *lbl, QString strS, long num);
};

#endif // SERIALPORT_H
