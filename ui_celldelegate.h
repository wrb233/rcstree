/********************************************************************************
** Form generated from reading UI file 'celldelegate.ui'
**
** Created: Thu Aug 6 10:57:07 2020
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CELLDELEGATE_H
#define UI_CELLDELEGATE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CellDelegateUI
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *pushButton;

    void setupUi(QWidget *CellDelegateUI)
    {
        if (CellDelegateUI->objectName().isEmpty())
            CellDelegateUI->setObjectName(QString::fromUtf8("CellDelegateUI"));
        CellDelegateUI->resize(170, 25);
        verticalLayout = new QVBoxLayout(CellDelegateUI);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEdit = new QLineEdit(CellDelegateUI);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        pushButton = new QPushButton(CellDelegateUI);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMaximumSize(QSize(30, 16777215));

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(CellDelegateUI);

        QMetaObject::connectSlotsByName(CellDelegateUI);
    } // setupUi

    void retranslateUi(QWidget *CellDelegateUI)
    {
        CellDelegateUI->setWindowTitle(QApplication::translate("CellDelegateUI", "Form", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("CellDelegateUI", "\343\200\213", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CellDelegateUI: public Ui_CellDelegateUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CELLDELEGATE_H
