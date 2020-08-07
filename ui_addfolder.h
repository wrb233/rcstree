/********************************************************************************
** Form generated from reading UI file 'addfolder.ui'
**
** Created: Thu Aug 6 10:57:07 2020
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDFOLDER_H
#define UI_ADDFOLDER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddFolderUI
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *AddFolderUI)
    {
        if (AddFolderUI->objectName().isEmpty())
            AddFolderUI->setObjectName(QString::fromUtf8("AddFolderUI"));
        AddFolderUI->resize(392, 101);
        verticalLayout = new QVBoxLayout(AddFolderUI);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(AddFolderUI);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(AddFolderUI);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(AddFolderUI);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(AddFolderUI);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        hboxLayout->addWidget(cancelButton);


        verticalLayout->addLayout(hboxLayout);


        retranslateUi(AddFolderUI);
        QObject::connect(okButton, SIGNAL(clicked()), AddFolderUI, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), AddFolderUI, SLOT(reject()));

        QMetaObject::connectSlotsByName(AddFolderUI);
    } // setupUi

    void retranslateUi(QDialog *AddFolderUI)
    {
        AddFolderUI->setWindowTitle(QApplication::translate("AddFolderUI", "\346\267\273\345\212\240", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("AddFolderUI", "\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("AddFolderUI", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("AddFolderUI", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AddFolderUI: public Ui_AddFolderUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDFOLDER_H
