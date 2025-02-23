/********************************************************************************
** Form generated from reading UI file 'creditordebit.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREDITORDEBIT_H
#define UI_CREDITORDEBIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_creditOrDebit
{
public:
    QPushButton *btnCredit;
    QPushButton *btnDebit;
    QLabel *labelChooseName;

    void setupUi(QDialog *creditOrDebit)
    {
        if (creditOrDebit->objectName().isEmpty())
            creditOrDebit->setObjectName("creditOrDebit");
        creditOrDebit->resize(500, 400);
        btnCredit = new QPushButton(creditOrDebit);
        btnCredit->setObjectName("btnCredit");
        btnCredit->setGeometry(QRect(160, 270, 150, 50));
        btnDebit = new QPushButton(creditOrDebit);
        btnDebit->setObjectName("btnDebit");
        btnDebit->setGeometry(QRect(160, 210, 150, 50));
        labelChooseName = new QLabel(creditOrDebit);
        labelChooseName->setObjectName("labelChooseName");
        labelChooseName->setGeometry(QRect(50, 50, 401, 91));
        QFont font;
        font.setPointSize(16);
        labelChooseName->setFont(font);

        retranslateUi(creditOrDebit);

        QMetaObject::connectSlotsByName(creditOrDebit);
    } // setupUi

    void retranslateUi(QDialog *creditOrDebit)
    {
        creditOrDebit->setWindowTitle(QCoreApplication::translate("creditOrDebit", "Dialog", nullptr));
        btnCredit->setText(QCoreApplication::translate("creditOrDebit", "Credit", nullptr));
        btnDebit->setText(QCoreApplication::translate("creditOrDebit", "Debit", nullptr));
        labelChooseName->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class creditOrDebit: public Ui_creditOrDebit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREDITORDEBIT_H
