/********************************************************************************
** Form generated from reading UI file 'coordinate.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COORDINATE_H
#define UI_COORDINATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Coordinate
{
public:
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout;
    QFrame *canvasWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *centralBtn;
    QPushButton *centerArrowBtn;
    QTextEdit *introductText;

    void setupUi(QWidget *Coordinate)
    {
        if (Coordinate->objectName().isEmpty())
            Coordinate->setObjectName(QString::fromUtf8("Coordinate"));
        Coordinate->resize(1145, 669);
        gridLayout_5 = new QGridLayout(Coordinate);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        canvasWidget = new QFrame(Coordinate);
        canvasWidget->setObjectName(QString::fromUtf8("canvasWidget"));
        canvasWidget->setFrameShape(QFrame::StyledPanel);
        canvasWidget->setFrameShadow(QFrame::Raised);

        horizontalLayout->addWidget(canvasWidget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(20);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(20, -1, -1, -1);
        centralBtn = new QPushButton(Coordinate);
        centralBtn->setObjectName(QString::fromUtf8("centralBtn"));

        verticalLayout->addWidget(centralBtn);

        centerArrowBtn = new QPushButton(Coordinate);
        centerArrowBtn->setObjectName(QString::fromUtf8("centerArrowBtn"));

        verticalLayout->addWidget(centerArrowBtn);

        introductText = new QTextEdit(Coordinate);
        introductText->setObjectName(QString::fromUtf8("introductText"));
        introductText->setMouseTracking(false);
        introductText->setAcceptDrops(false);
        introductText->setStyleSheet(QString::fromUtf8("border: none;\n"
"background-color: rgb(240, 240, 240);"));

        verticalLayout->addWidget(introductText);


        horizontalLayout->addLayout(verticalLayout);

        horizontalLayout->setStretch(0, 10);

        gridLayout_5->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(Coordinate);

        QMetaObject::connectSlotsByName(Coordinate);
    } // setupUi

    void retranslateUi(QWidget *Coordinate)
    {
        Coordinate->setWindowTitle(QCoreApplication::translate("Coordinate", "Form", nullptr));
        centralBtn->setText(QCoreApplication::translate("Coordinate", "\345\216\237\347\202\271", nullptr));
        centerArrowBtn->setText(QCoreApplication::translate("Coordinate", "\345\256\232\344\275\215\347\256\255\345\244\264", nullptr));
        introductText->setHtml(QCoreApplication::translate("Coordinate", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">\346\273\232\345\212\250\351\274\240\346\240\207\350\277\233\350\241\214\347\274\251\346\224\276</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:12pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-r"
                        "ight:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">\351\225\277\346\214\211\345\267\246\351\224\256\350\277\233\350\241\214\346\213\226\346\213\275</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Coordinate: public Ui_Coordinate {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COORDINATE_H
