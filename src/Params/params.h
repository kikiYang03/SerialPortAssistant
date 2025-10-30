#ifndef PARAMS_H
#define PARAMS_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QSpinBox>
#include <QComboBox>
#include <QMessageBox>
#include "serialport.h"  // 包含串口通信头文件

namespace Ui {
class Params;
}

class Params : public QWidget
{
    Q_OBJECT

public:
    explicit Params(QWidget *parent = nullptr, SerialPort *serialPort = nullptr);
    ~Params();

    void setSerialPort(SerialPort *serialPort);  // 设置通信接口

public slots:
    void onParameterResponseReceived(const QByteArray &data);  // 参数响应处理

private slots:
    void onFoldButtonClicked();
    void on_readButton_clicked();
    void on_writeButton_clicked();
    void on_defaultButton_clicked();


private:
    Ui::Params *ui;
    bool m_isGroupFolded;
    QList<QWidget*> valueWidgets;
    SerialPort *m_serialPort;  // 通信接口指针

    void setupTable();
    void setupParameters();
    QWidget* createValueWidget(const QString &id, const QString &range, int defaultValue);
    void updateTableFromWidgets();
    void restoreDefaultValues();

    // 参数通信相关方法
    void sendParameterReadRequest(const QString &paramId);
    void sendParameterWriteRequest(const QString &paramId, int value);
    QByteArray buildParameterFrame(quint8 command, const QString &paramId, int value = 0);
    void parseParameterResponse(const QByteArray &data);
};

#endif // PARAMS_H
