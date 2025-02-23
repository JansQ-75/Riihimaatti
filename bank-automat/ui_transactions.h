/********************************************************************************
** Form generated from reading UI file 'transactions.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRANSACTIONS_H
#define UI_TRANSACTIONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Transactions
{
public:
    QLabel *label_header;
    QTableView *tableView;
    QPushButton *btnDown;
    QPushButton *btnUp;
    QLabel *labelCustomer;

    void setupUi(QWidget *Transactions)
    {
        if (Transactions->objectName().isEmpty())
            Transactions->setObjectName("Transactions");
        Transactions->resize(800, 480);
        label_header = new QLabel(Transactions);
        label_header->setObjectName("label_header");
        label_header->setGeometry(QRect(80, 30, 251, 71));
        tableView = new QTableView(Transactions);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(130, 130, 631, 331));
        tableView->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        btnDown = new QPushButton(Transactions);
        btnDown->setObjectName("btnDown");
        btnDown->setGeometry(QRect(30, 300, 65, 65));
        btnUp = new QPushButton(Transactions);
        btnUp->setObjectName("btnUp");
        btnUp->setGeometry(QRect(30, 230, 65, 65));
        labelCustomer = new QLabel(Transactions);
        labelCustomer->setObjectName("labelCustomer");
        labelCustomer->setGeometry(QRect(530, 30, 181, 81));

        retranslateUi(Transactions);

        QMetaObject::connectSlotsByName(Transactions);
    } // setupUi

    void retranslateUi(QWidget *Transactions)
    {
        Transactions->setWindowTitle(QCoreApplication::translate("Transactions", "Form", nullptr));
        label_header->setText(QCoreApplication::translate("Transactions", "Transactions", nullptr));
        btnDown->setText(QCoreApplication::translate("Transactions", "DOWN", nullptr));
        btnUp->setText(QCoreApplication::translate("Transactions", "UP", nullptr));
        labelCustomer->setText(QCoreApplication::translate("Transactions", "Customer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Transactions: public Ui_Transactions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANSACTIONS_H
