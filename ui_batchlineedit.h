/********************************************************************************
** Form generated from reading UI file 'batchlineedit.ui'
**
** Created: Thu Aug 6 10:57:07 2020
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BATCHLINEEDIT_H
#define UI_BATCHLINEEDIT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_BatchLineEditUI
{
public:
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *BatchLineEditUI)
    {
        if (BatchLineEditUI->objectName().isEmpty())
            BatchLineEditUI->setObjectName(QString::fromUtf8("BatchLineEditUI"));
        BatchLineEditUI->resize(357, 77);
        verticalLayout = new QVBoxLayout(BatchLineEditUI);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lineEdit = new QLineEdit(BatchLineEditUI);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(BatchLineEditUI);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(BatchLineEditUI);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        hboxLayout->addWidget(cancelButton);


        verticalLayout->addLayout(hboxLayout);


        retranslateUi(BatchLineEditUI);
        QObject::connect(okButton, SIGNAL(clicked()), BatchLineEditUI, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), BatchLineEditUI, SLOT(reject()));

        QMetaObject::connectSlotsByName(BatchLineEditUI);
    } // setupUi

    void retranslateUi(QDialog *BatchLineEditUI)
    {
        BatchLineEditUI->setWindowTitle(QApplication::translate("BatchLineEditUI", "\350\276\223\345\205\245", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("BatchLineEditUI", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("BatchLineEditUI", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class BatchLineEditUI: public Ui_BatchLineEditUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BATCHLINEEDIT_H
