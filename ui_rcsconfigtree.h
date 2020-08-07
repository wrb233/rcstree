/********************************************************************************
** Form generated from reading UI file 'rcsconfigtree.ui'
**
** Created: Thu Aug 6 10:57:07 2020
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RCSCONFIGTREE_H
#define UI_RCSCONFIGTREE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RCSConfigTreeUI
{
public:
    QVBoxLayout *verticalLayout;
    QTreeView *treeView;

    void setupUi(QWidget *RCSConfigTreeUI)
    {
        if (RCSConfigTreeUI->objectName().isEmpty())
            RCSConfigTreeUI->setObjectName(QString::fromUtf8("RCSConfigTreeUI"));
        RCSConfigTreeUI->resize(385, 497);
        verticalLayout = new QVBoxLayout(RCSConfigTreeUI);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        treeView = new QTreeView(RCSConfigTreeUI);
        treeView->setObjectName(QString::fromUtf8("treeView"));

        verticalLayout->addWidget(treeView);


        retranslateUi(RCSConfigTreeUI);

        QMetaObject::connectSlotsByName(RCSConfigTreeUI);
    } // setupUi

    void retranslateUi(QWidget *RCSConfigTreeUI)
    {
        RCSConfigTreeUI->setWindowTitle(QApplication::translate("RCSConfigTreeUI", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class RCSConfigTreeUI: public Ui_RCSConfigTreeUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RCSCONFIGTREE_H
