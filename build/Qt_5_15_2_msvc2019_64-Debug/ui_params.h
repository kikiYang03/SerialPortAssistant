/********************************************************************************
** Form generated from reading UI file 'params.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAMS_H
#define UI_PARAMS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Params
{
public:
    QTextEdit *textEdit;

    void setupUi(QWidget *Params)
    {
        if (Params->objectName().isEmpty())
            Params->setObjectName(QString::fromUtf8("Params"));
        Params->resize(400, 300);
        textEdit = new QTextEdit(Params);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(140, 120, 104, 71));

        retranslateUi(Params);

        QMetaObject::connectSlotsByName(Params);
    } // setupUi

    void retranslateUi(QWidget *Params)
    {
        Params->setWindowTitle(QCoreApplication::translate("Params", "Form", nullptr));
        textEdit->setHtml(QCoreApplication::translate("Params", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\350\256\276\347\275\256\344\270\232\345\212\241\345\217\202\346\225\260</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Params: public Ui_Params {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMS_H
