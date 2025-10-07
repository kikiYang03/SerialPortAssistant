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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Coordinate
{
public:
    QLineEdit *lineEdit;

    void setupUi(QWidget *Coordinate)
    {
        if (Coordinate->objectName().isEmpty())
            Coordinate->setObjectName(QString::fromUtf8("Coordinate"));
        Coordinate->resize(400, 300);
        lineEdit = new QLineEdit(Coordinate);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(140, 200, 113, 21));

        retranslateUi(Coordinate);

        QMetaObject::connectSlotsByName(Coordinate);
    } // setupUi

    void retranslateUi(QWidget *Coordinate)
    {
        Coordinate->setWindowTitle(QCoreApplication::translate("Coordinate", "Form", nullptr));
        lineEdit->setText(QCoreApplication::translate("Coordinate", "\345\235\220\346\240\207\350\275\254\345\214\226\351\241\265\351\235\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Coordinate: public Ui_Coordinate {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COORDINATE_H
