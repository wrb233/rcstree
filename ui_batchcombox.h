/********************************************************************************
** Form generated from reading UI file 'batchcombox.ui'
**
** Created: Thu Aug 6 10:57:07 2020
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BATCHCOMBOX_H
#define UI_BATCHCOMBOX_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_BatchComboxUI
{
public:
    QVBoxLayout *verticalLayout;
    QComboBox *comboBox;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *BatchComboxUI)
    {
        if (BatchComboxUI->objectName().isEmpty())
            BatchComboxUI->setObjectName(QString::fromUtf8("BatchComboxUI"));
        BatchComboxUI->resize(339, 77);
        verticalLayout = new QVBoxLayout(BatchComboxUI);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        comboBox = new QComboBox(BatchComboxUI);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        verticalLayout->addWidget(comboBox);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(BatchComboxUI);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(BatchComboxUI);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        hboxLayout->addWidget(cancelButton);


        verticalLayout->addLayout(hboxLayout);


        retranslateUi(BatchComboxUI);
        QObject::connect(okButton, SIGNAL(clicked()), BatchComboxUI, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), BatchComboxUI, SLOT(reject()));

        QMetaObject::connectSlotsByName(BatchComboxUI);
    } // setupUi

    void retranslateUi(QDialog *BatchComboxUI)
    {
        BatchComboxUI->setWindowTitle(QApplication::translate("BatchComboxUI", "\351\200\211\346\213\251", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("BatchComboxUI", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("BatchComboxUI", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class BatchComboxUI: public Ui_BatchComboxUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BATCHCOMBOX_H
