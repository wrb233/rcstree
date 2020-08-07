/********************************************************************************
** Form generated from reading UI file 'centertable.ui'
**
** Created: Thu Aug 6 10:57:07 2020
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CENTERTABLE_H
#define UI_CENTERTABLE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CenterTableUI
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *saveButton;

    void setupUi(QWidget *CenterTableUI)
    {
        if (CenterTableUI->objectName().isEmpty())
            CenterTableUI->setObjectName(QString::fromUtf8("CenterTableUI"));
        CenterTableUI->resize(445, 345);
        verticalLayout = new QVBoxLayout(CenterTableUI);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(CenterTableUI);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));

        verticalLayout->addWidget(tabWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        saveButton = new QPushButton(CenterTableUI);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));

        horizontalLayout_2->addWidget(saveButton);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(CenterTableUI);

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(CenterTableUI);
    } // setupUi

    void retranslateUi(QWidget *CenterTableUI)
    {
        CenterTableUI->setWindowTitle(QApplication::translate("CenterTableUI", "Form", 0, QApplication::UnicodeUTF8));
        saveButton->setText(QApplication::translate("CenterTableUI", "\344\277\235\345\255\230", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CenterTableUI: public Ui_CenterTableUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CENTERTABLE_H
