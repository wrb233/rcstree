/********************************************************************************
** Form generated from reading UI file 'picktree.ui'
**
** Created: Thu Aug 6 10:57:07 2020
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PICKTREE_H
#define UI_PICKTREE_H

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

class Ui_PickTreeUI
{
public:
    QVBoxLayout *verticalLayout;
    QTreeView *treeView;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *clearButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *PickTreeUI)
    {
        if (PickTreeUI->objectName().isEmpty())
            PickTreeUI->setObjectName(QString::fromUtf8("PickTreeUI"));
        PickTreeUI->resize(322, 530);
        verticalLayout = new QVBoxLayout(PickTreeUI);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        treeView = new QTreeView(PickTreeUI);
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

        okButton = new QPushButton(PickTreeUI);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout->addWidget(okButton);

        clearButton = new QPushButton(PickTreeUI);
        clearButton->setObjectName(QString::fromUtf8("clearButton"));

        hboxLayout->addWidget(clearButton);

        cancelButton = new QPushButton(PickTreeUI);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        hboxLayout->addWidget(cancelButton);


        verticalLayout->addLayout(hboxLayout);


        retranslateUi(PickTreeUI);
        QObject::connect(okButton, SIGNAL(clicked()), PickTreeUI, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), PickTreeUI, SLOT(reject()));

        QMetaObject::connectSlotsByName(PickTreeUI);
    } // setupUi

    void retranslateUi(QDialog *PickTreeUI)
    {
        PickTreeUI->setWindowTitle(QApplication::translate("PickTreeUI", "\351\200\211\347\202\271", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("PickTreeUI", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        clearButton->setText(QApplication::translate("PickTreeUI", "\346\270\205\351\231\244", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("PickTreeUI", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PickTreeUI: public Ui_PickTreeUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PICKTREE_H
