/********************************************************************************
** Form generated from reading UI file 'serialport.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERIALPORT_H
#define UI_SERIALPORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SerialPort
{
public:
    QGroupBox *groupBox;
    QLabel *lblPortState;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *portNames;
    QVBoxLayout *verticalLayout;
    QPushButton *portSearchBt;
    QPushButton *portOpenBt;
    QGroupBox *groupBox_3;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QTextBrowser *recvEdit;
    QPushButton *clearRecvBt;
    QLabel *recvNum;
    QGroupBox *groupBox_4;
    QPushButton *sendBt;
    QLabel *sendNum;

    void setupUi(QWidget *SerialPort)
    {
        if (SerialPort->objectName().isEmpty())
            SerialPort->setObjectName(QString::fromUtf8("SerialPort"));
        SerialPort->resize(800, 559);
        groupBox = new QGroupBox(SerialPort);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(579, 10, 201, 201));
        lblPortState = new QLabel(groupBox);
        lblPortState->setObjectName(QString::fromUtf8("lblPortState"));
        lblPortState->setGeometry(QRect(20, 30, 161, 16));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 50, 161, 131));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        portNames = new QComboBox(layoutWidget);
        portNames->setObjectName(QString::fromUtf8("portNames"));

        horizontalLayout->addWidget(portNames);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        portSearchBt = new QPushButton(layoutWidget);
        portSearchBt->setObjectName(QString::fromUtf8("portSearchBt"));

        verticalLayout->addWidget(portSearchBt);

        portOpenBt = new QPushButton(layoutWidget);
        portOpenBt->setObjectName(QString::fromUtf8("portOpenBt"));

        verticalLayout->addWidget(portOpenBt);


        verticalLayout_2->addLayout(verticalLayout);

        groupBox_3 = new QGroupBox(SerialPort);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(20, 10, 541, 321));
        scrollArea = new QScrollArea(groupBox_3);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(20, 20, 501, 241));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 499, 239));
        recvEdit = new QTextBrowser(scrollAreaWidgetContents);
        recvEdit->setObjectName(QString::fromUtf8("recvEdit"));
        recvEdit->setGeometry(QRect(0, 0, 501, 241));
        scrollArea->setWidget(scrollAreaWidgetContents);
        clearRecvBt = new QPushButton(groupBox_3);
        clearRecvBt->setObjectName(QString::fromUtf8("clearRecvBt"));
        clearRecvBt->setGeometry(QRect(440, 280, 81, 23));
        recvNum = new QLabel(groupBox_3);
        recvNum->setObjectName(QString::fromUtf8("recvNum"));
        recvNum->setGeometry(QRect(10, 280, 151, 20));
        recvNum->setStyleSheet(QString::fromUtf8("font: 10pt \"Microsoft YaHei UI\";"));
        groupBox_4 = new QGroupBox(SerialPort);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(20, 350, 541, 171));
        sendBt = new QPushButton(groupBox_4);
        sendBt->setObjectName(QString::fromUtf8("sendBt"));
        sendBt->setGeometry(QRect(170, 60, 191, 41));
        sendNum = new QLabel(groupBox_4);
        sendNum->setObjectName(QString::fromUtf8("sendNum"));
        sendNum->setGeometry(QRect(10, 140, 181, 20));
        sendNum->setStyleSheet(QString::fromUtf8("font: 10pt \"Microsoft YaHei UI\";"));

        retranslateUi(SerialPort);

        QMetaObject::connectSlotsByName(SerialPort);
    } // setupUi

    void retranslateUi(QWidget *SerialPort)
    {
        SerialPort->setWindowTitle(QCoreApplication::translate("SerialPort", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SerialPort", "\344\270\262\345\217\243\351\200\211\346\213\251", nullptr));
        lblPortState->setText(QCoreApplication::translate("SerialPort", "\347\255\211\345\276\205\344\270\262\345\217\243\351\223\276\346\216\245", nullptr));
        label->setText(QCoreApplication::translate("SerialPort", "\347\253\257 \345\217\243", nullptr));
        portSearchBt->setText(QCoreApplication::translate("SerialPort", "\346\243\200\346\265\213\344\270\262\345\217\243", nullptr));
        portOpenBt->setText(QCoreApplication::translate("SerialPort", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("SerialPort", "\351\200\232\344\277\241\346\227\245\345\277\227", nullptr));
        clearRecvBt->setText(QCoreApplication::translate("SerialPort", "\346\270\205\347\251\272\345\206\205\345\256\271", nullptr));
        recvNum->setText(QCoreApplication::translate("SerialPort", "\346\216\245\346\224\266\345\255\227\350\212\202\346\225\260\351\207\217\357\274\2320", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("SerialPort", "\345\217\221\351\200\201", nullptr));
        sendBt->setText(QCoreApplication::translate("SerialPort", "\345\217\221\351\200\201\346\265\213\350\257\225\346\225\260\346\215\256", nullptr));
        sendNum->setText(QCoreApplication::translate("SerialPort", "\345\217\221\351\200\201\345\255\227\350\212\202\346\225\260\351\207\217\357\274\2320", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SerialPort: public Ui_SerialPort {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERIALPORT_H
