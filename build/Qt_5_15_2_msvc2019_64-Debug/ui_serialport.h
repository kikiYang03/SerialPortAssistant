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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
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
    QWidget *widget;
    QVBoxLayout *verticalLayout_14;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_15;
    QWidget *widget2;
    QVBoxLayout *verticalLayout_17;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_25;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_24;
    QLabel *lblPortState;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *portNames;
    QVBoxLayout *verticalLayout;
    QPushButton *portSearchBt;
    QPushButton *portOpenBt;
    QFrame *frame;
    QVBoxLayout *verticalLayout_23;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_21;
    QVBoxLayout *verticalLayout_16;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout_21;
    QTextBrowser *recvEdit;
    QHBoxLayout *horizontalLayout_16;
    QLabel *recvNum;
    QLabel *label_21;
    QPushButton *clearRecvBt;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_22;
    QVBoxLayout *verticalLayout_18;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_22;
    QPushButton *sendBt;
    QLabel *label_23;
    QHBoxLayout *horizontalLayout_18;
    QLabel *sendNum;
    QLabel *label_24;
    QLabel *label_25;
    QVBoxLayout *verticalLayout_20;

    void setupUi(QWidget *SerialPort)
    {
        if (SerialPort->objectName().isEmpty())
            SerialPort->setObjectName(QString::fromUtf8("SerialPort"));
        SerialPort->resize(1064, 565);
        widget = new QWidget(SerialPort);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 2, 2));
        verticalLayout_14 = new QVBoxLayout(widget);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        verticalLayout_14->setContentsMargins(0, 0, 0, 0);
        widget1 = new QWidget(SerialPort);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(0, 0, 2, 2));
        verticalLayout_15 = new QVBoxLayout(widget1);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        verticalLayout_15->setContentsMargins(0, 0, 0, 0);
        widget2 = new QWidget(SerialPort);
        widget2->setObjectName(QString::fromUtf8("widget2"));
        widget2->setGeometry(QRect(0, 0, 2, 2));
        verticalLayout_17 = new QVBoxLayout(widget2);
        verticalLayout_17->setObjectName(QString::fromUtf8("verticalLayout_17"));
        verticalLayout_17->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout(SerialPort);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_25 = new QVBoxLayout();
        verticalLayout_25->setObjectName(QString::fromUtf8("verticalLayout_25"));
        groupBox = new QGroupBox(SerialPort);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_24 = new QVBoxLayout(groupBox);
        verticalLayout_24->setObjectName(QString::fromUtf8("verticalLayout_24"));
        lblPortState = new QLabel(groupBox);
        lblPortState->setObjectName(QString::fromUtf8("lblPortState"));

        verticalLayout_24->addWidget(lblPortState);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        portNames = new QComboBox(groupBox);
        portNames->setObjectName(QString::fromUtf8("portNames"));

        horizontalLayout->addWidget(portNames);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        portSearchBt = new QPushButton(groupBox);
        portSearchBt->setObjectName(QString::fromUtf8("portSearchBt"));

        verticalLayout->addWidget(portSearchBt);

        portOpenBt = new QPushButton(groupBox);
        portOpenBt->setObjectName(QString::fromUtf8("portOpenBt"));

        verticalLayout->addWidget(portOpenBt);


        verticalLayout_2->addLayout(verticalLayout);


        verticalLayout_24->addLayout(verticalLayout_2);


        verticalLayout_25->addWidget(groupBox);

        frame = new QFrame(SerialPort);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        verticalLayout_25->addWidget(frame);


        gridLayout->addLayout(verticalLayout_25, 1, 2, 1, 1);

        verticalLayout_23 = new QVBoxLayout();
        verticalLayout_23->setObjectName(QString::fromUtf8("verticalLayout_23"));
        groupBox_3 = new QGroupBox(SerialPort);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        verticalLayout_21 = new QVBoxLayout(groupBox_3);
        verticalLayout_21->setObjectName(QString::fromUtf8("verticalLayout_21"));
        verticalLayout_16 = new QVBoxLayout();
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        scrollArea = new QScrollArea(groupBox_3);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 842, 336));
        horizontalLayout_21 = new QHBoxLayout(scrollAreaWidgetContents);
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        recvEdit = new QTextBrowser(scrollAreaWidgetContents);
        recvEdit->setObjectName(QString::fromUtf8("recvEdit"));

        horizontalLayout_21->addWidget(recvEdit);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_16->addWidget(scrollArea);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        recvNum = new QLabel(groupBox_3);
        recvNum->setObjectName(QString::fromUtf8("recvNum"));
        recvNum->setStyleSheet(QString::fromUtf8("font: 10pt \"Microsoft YaHei UI\";"));

        horizontalLayout_16->addWidget(recvNum);

        label_21 = new QLabel(groupBox_3);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        horizontalLayout_16->addWidget(label_21);

        clearRecvBt = new QPushButton(groupBox_3);
        clearRecvBt->setObjectName(QString::fromUtf8("clearRecvBt"));

        horizontalLayout_16->addWidget(clearRecvBt);


        verticalLayout_16->addLayout(horizontalLayout_16);


        verticalLayout_21->addLayout(verticalLayout_16);


        verticalLayout_23->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(SerialPort);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        verticalLayout_22 = new QVBoxLayout(groupBox_4);
        verticalLayout_22->setObjectName(QString::fromUtf8("verticalLayout_22"));
        verticalLayout_18 = new QVBoxLayout();
        verticalLayout_18->setObjectName(QString::fromUtf8("verticalLayout_18"));
        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        label_22 = new QLabel(groupBox_4);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        horizontalLayout_17->addWidget(label_22);

        sendBt = new QPushButton(groupBox_4);
        sendBt->setObjectName(QString::fromUtf8("sendBt"));

        horizontalLayout_17->addWidget(sendBt);

        label_23 = new QLabel(groupBox_4);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        horizontalLayout_17->addWidget(label_23);


        verticalLayout_18->addLayout(horizontalLayout_17);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        sendNum = new QLabel(groupBox_4);
        sendNum->setObjectName(QString::fromUtf8("sendNum"));
        sendNum->setStyleSheet(QString::fromUtf8("font: 10pt \"Microsoft YaHei UI\";"));

        horizontalLayout_18->addWidget(sendNum);

        label_24 = new QLabel(groupBox_4);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        horizontalLayout_18->addWidget(label_24);

        label_25 = new QLabel(groupBox_4);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        horizontalLayout_18->addWidget(label_25);


        verticalLayout_18->addLayout(horizontalLayout_18);


        verticalLayout_22->addLayout(verticalLayout_18);


        verticalLayout_23->addWidget(groupBox_4);


        gridLayout->addLayout(verticalLayout_23, 1, 1, 1, 1);

        verticalLayout_20 = new QVBoxLayout();
        verticalLayout_20->setObjectName(QString::fromUtf8("verticalLayout_20"));

        gridLayout->addLayout(verticalLayout_20, 0, 0, 1, 1);


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
        recvNum->setText(QCoreApplication::translate("SerialPort", "\346\216\245\346\224\266\345\255\227\350\212\202\346\225\260\351\207\217\357\274\2320", nullptr));
        label_21->setText(QString());
        clearRecvBt->setText(QCoreApplication::translate("SerialPort", "\346\270\205\347\251\272\345\206\205\345\256\271", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("SerialPort", "\345\217\221\351\200\201", nullptr));
        label_22->setText(QString());
        sendBt->setText(QCoreApplication::translate("SerialPort", "\345\217\221\351\200\201\346\265\213\350\257\225\346\225\260\346\215\256", nullptr));
        label_23->setText(QString());
        sendNum->setText(QCoreApplication::translate("SerialPort", "\345\217\221\351\200\201\345\255\227\350\212\202\346\225\260\351\207\217\357\274\2320", nullptr));
        label_24->setText(QString());
        label_25->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SerialPort: public Ui_SerialPort {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERIALPORT_H
