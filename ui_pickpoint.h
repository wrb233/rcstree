/********************************************************************************
** Form generated from reading UI file 'pickpoint.ui'
**
** Created: Thu Aug 6 10:57:07 2020
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PICKPOINT_H
#define UI_PICKPOINT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PickPointUI
{
public:
    QVBoxLayout *verticalLayout;
    QTreeView *treeView;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *PickPointUI)
    {
        if (PickPointUI->objectName().isEmpty())
            PickPointUI->setObjectName(QString::fromUtf8("PickPointUI"));
        PickPointUI->resize(322, 563);
        verticalLayout = new QVBoxLayout(PickPointUI);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        treeView = new QTreeView(PickPointUI);
        treeView->setObjectName(QString::fromUtf8("treeView"));

        verticalLayout->addWidget(treeView);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(PickPointUI);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(PickPointUI);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        hboxLayout->addWidget(cancelButton);


        verticalLayout->addLayout(hboxLayout);


        retranslateUi(PickPointUI);
        QObject::connect(okButton, SIGNAL(clicked()), PickPointUI, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), PickPointUI, SLOT(reject()));

        QMetaObject::connectSlotsByName(PickPointUI);
    } // setupUi

    void retranslateUi(QDialog *PickPointUI)
    {
        PickPointUI->setWindowTitle(QApplication::translate("PickPointUI", "\351\200\211\345\217\226\346\225\260\346\215\256\347\202\271", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("PickPointUI", "\344\277\235\345\255\230", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("PickPointUI", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PickPointUI: public Ui_PickPointUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PICKPOINT_H
