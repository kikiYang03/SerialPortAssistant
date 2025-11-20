#include "tcpclient.h"
#include <QHostAddress>

TcpClient* TcpClient::m_instance = nullptr;
QMutex TcpClient::m_mutex;

TcpClient::TcpClient(QObject *parent)
    : QObject(parent)
    , m_isConnected(false)
    , m_autoReconnect(false)
{
    m_tcpSocket = new QTcpSocket(this);
    m_connectionTimer = new QTimer(this);
    m_reconnectTimer = new QTimer(this);

    // 设置单次定时器
    m_connectionTimer->setSingleShot(true);
    m_reconnectTimer->setSingleShot(true);

    // 禁用代理，避免连接问题
    m_tcpSocket->setProxy(QNetworkProxy::NoProxy);

    // 连接信号槽
    connect(m_tcpSocket, &QTcpSocket::connected, this, &TcpClient::onConnected);
    connect(m_tcpSocket, &QTcpSocket::disconnected, this, &TcpClient::onDisconnected);
    connect(m_tcpSocket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);
    connect(m_tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred),
            this, &TcpClient::onErrorOccurred);

    connect(m_connectionTimer, &QTimer::timeout, this, &TcpClient::onConnectionTimeout);
    // connect(m_reconnectTimer, &QTimer::timeout, this, &TcpClient::onReconnect);
}

TcpClient::~TcpClient()
{
    if (m_tcpSocket->state() == QAbstractSocket::ConnectedState) {
        m_tcpSocket->disconnectFromHost();
        if (m_tcpSocket->state() == QAbstractSocket::ConnectedState) {
            m_tcpSocket->waitForDisconnected(1000);
        }
    }
}

TcpClient* TcpClient::getInstance()
{
    QMutexLocker locker(&m_mutex);
    if (m_instance == nullptr) {
        m_instance = new TcpClient();
    }
    return m_instance;
}

bool TcpClient::connectToHost(const QString &ip, quint16 port, int timeoutMs)
{
    if (m_isConnected) {
        disconnectFromHost();
    }

    m_serverIp = ip;
    m_serverPort = port;

    qDebug() << "开始连接TCP服务器..." << ip << ":" << port;

    // 启动连接超时定时器
    m_connectionTimer->start(timeoutMs);

    m_tcpSocket->connectToHost(ip, port);
    return true;
}

void TcpClient::disconnectFromHost()
{
    m_connectionTimer->stop();
    m_reconnectTimer->stop();
    m_autoReconnect = false;

    if (m_tcpSocket->state() == QAbstractSocket::ConnectedState) {
        m_tcpSocket->disconnectFromHost();
    }
}

bool TcpClient::isConnected() const
{
    return m_isConnected && (m_tcpSocket->state() == QAbstractSocket::ConnectedState);
}

qint64 TcpClient::sendData(const QByteArray &data)
{
    if (!isConnected()) {
        qWarning() << "TCP未连接，无法发送数据";
        return -1;
    }

    qint64 bytesSent = m_tcpSocket->write(data);
    if (bytesSent == -1) {
        qWarning() << "TCP数据发送失败:" << m_tcpSocket->errorString();
    }

    return bytesSent;
}

void TcpClient::setConnectionStatus(bool connected)
{
    if (m_isConnected != connected) {
        m_isConnected = connected;
        emit connectionStatusChanged(connected);
    }
}

void TcpClient::onReconnect()
{
    // if (!m_isConnected && m_autoReconnect) {
    //     qDebug() << "尝试重新连接TCP服务器...";
    //     connectToHost(m_serverIp, m_serverPort);
    // }
}

void TcpClient::onConnected()
{
    m_connectionTimer->stop();
    setConnectionStatus(true);

    qDebug() << "TCP连接成功！";
    emit connected();

    // 连接成功后停止自动重连
    m_autoReconnect = false;
    m_reconnectTimer->stop();
}

void TcpClient::onDisconnected()
{
    setConnectionStatus(false);
    qDebug() << "TCP连接断开";
    emit disconnected();

    // 启动自动重连
    if (m_autoReconnect) {
        qDebug() << "5秒后尝试重新连接...";
        m_reconnectTimer->start(5000);
    }
}

void TcpClient::onReadyRead()
{
    QByteArray data = m_tcpSocket->readAll();
    if (!data.isEmpty()) {
        emit dataReceived(data);
    }
}

void TcpClient::onErrorOccurred(QAbstractSocket::SocketError error)
{
    m_connectionTimer->stop();
    setConnectionStatus(false);

    QString errorString = m_tcpSocket->errorString();
    qWarning() << "TCP连接错误:" << errorString;

    emit connectionError(errorString);

    // 启动自动重连
    m_autoReconnect = true;
    m_reconnectTimer->start(5000);
}

void TcpClient::onConnectionTimeout()
{
    if (!m_isConnected) {
        qDebug() << "TCP连接超时";
        m_tcpSocket->abort();
        emit connectionError("连接超时，请检查网络和服务器");

        // 启动自动重连
        m_autoReconnect = true;
        m_reconnectTimer->start(5000);
    }
}
