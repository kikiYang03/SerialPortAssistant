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
#include <QTextCodec>
#include <QByteArray>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QTcpServer>
#include <QNetworkInterface>
#include <QNetworkProxy>
#include <QDataStream>
#include <QtEndian>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


// 简化ROS消息struct（自定义，非ROS原生类型）
struct OccupancyGrid {
    int width, height;
    float resolution;
    QVector<float> data;  // 占用值 [-1:未知, 0:空, 100:占用]
    float origin_x, origin_y;
};

struct LaserScan {
    float angle_min, angle_max, angle_increment;
    QVector<float> ranges;  // 距离数组
    float range_min, range_max;
};

// 修改后的 TFMessage 结构体
struct TFMessage {
    struct Header {
        QString frame_id;  // 父坐标系，通常是 "map"
    };

    struct Transform {
        Header header;           // 添加 header 字段
        QString child_frame_id;  // 添加 child_frame_id 字段
        float x, y, z, yaw;      // 位姿
    };

    QVector<Transform> transforms;  // 多变换
};

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

    // 新增：发送协议数据的公共函数
    void sendProtocolData(qint16 x, qint16 y, qint16 z, qint16 yaw);
    void parseRosFrame(quint8 topicId, const QByteArray &payload);
    double quaternionToYaw(double x, double y, double z, double w);

protected:
    void findFreePorts();  //查找可用串口
    bool initSerialPort(); //初始化串口连接
    void sendMsg(const QString &msg); //发送消息（可保留原有功能）

private slots:
    // 串口通信相关函数
    void on_portSearchBt_clicked();
    void on_portOpenBt_clicked();
    void manual_serialPortReadyRead();
    void on_clearRecvBt_clicked();
    void on_sendBt_clicked();
    void on_btnClearSend_clicked();

    // WiFi TCP相关槽函数
    void tcpReadyRead();
    void tcpErrorOccurred(QAbstractSocket::SocketError error);

    // WiFi UDP相关槽函
    void udpReadyRead();

    // 协议切换
    // void on_protocolComboBox_currentIndexChanged(int index);

    void on_wifiConnectBt_clicked();

    // 新增：ROS解析槽
    void parseRosData(const QByteArray& recBuf);

private:
    Ui::SerialPort *ui;

    // 发送、接收字节计数
    long sendNum, recvNum;

    // 接收数据缓冲区
    QByteArray recvBuffer;

    void parseProtocolData();

    QTimer *m_testTimer;  // 测试数据发送定时器
    bool m_isSendingTestData;  // 是否正在发送测试数据
    QList<QVector<qint16>> m_testDataList;  // 测试数据列表
    int m_currentDataIndex;  // 当前发送的数据索引
    void initTestData();
    void sendTestData();

    // 串口链接
    bool isSerialPortConnected;

    // WiFi通信相关
    QTcpSocket *tcpSocket;
    QUdpSocket *udpSocket;
    bool isTcpConnected;
    bool isUdpBound;

    // 通用数据发送函数
    void sendData(const QByteArray &data);
    // 接收数据
    void processReceivedData(const QByteArray &recBuf);

    QMap<QString, TFMessage::Transform> tfCache;

signals:
    void coordinatesUpdated(qint16 x, qint16 y, qint16 z, qint16 yaw);

    // 修正：使用自定义struct
    void rosMapUpdated(const OccupancyGrid& map);
    void rosScanUpdated(const LaserScan& scan);
    void rosTfUpdated(const TFMessage& tf);

};

#endif // SERIALPORT_H
