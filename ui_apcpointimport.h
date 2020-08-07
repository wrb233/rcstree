/********************************************************************************
** Form generated from reading UI file 'apcpointimport.ui'
**
** Created: Thu Aug 6 13:38:20 2020
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APCPOINTIMPORT_H
#define UI_APCPOINTIMPORT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTreeView>

QT_BEGIN_NAMESPACE

class Ui_APCPointImportDialog
{
public:
    QGridLayout *gridLayout;
    QTreeView *treeView;
    QHBoxLayout *_2;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *APCPointImportDialog)
    {
        if (APCPointImportDialog->objectName().isEmpty())
            APCPointImportDialog->setObjectName(QString::fromUtf8("APCPointImportDialog"));
        APCPointImportDialog->resize(521, 552);
        gridLayout = new QGridLayout(APCPointImportDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        treeView = new QTreeView(APCPointImportDialog);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        treeView->viewport()->setProperty("cursor", QVariant(QCursor(Qt::ArrowCursor)));
        treeView->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(treeView, 0, 0, 1, 1);

        _2 = new QHBoxLayout();
#ifndef Q_OS_MAC
        _2->setSpacing(6);
#endif
        _2->setContentsMargins(0, 0, 0, 0);
        _2->setObjectName(QString::fromUtf8("_2"));
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        _2->addItem(spacerItem);

        okButton = new QPushButton(APCPointImportDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        _2->addWidget(okButton);

        cancelButton = new QPushButton(APCPointImportDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        _2->addWidget(cancelButton);


        gridLayout->addLayout(_2, 1, 0, 1, 1);


        retranslateUi(APCPointImportDialog);
        QObject::connect(okButton, SIGNAL(clicked()), APCPointImportDialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), APCPointImportDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(APCPointImportDialog);
    } // setupUi

    void retranslateUi(QDialog *APCPointImportDialog)
    {
        APCPointImportDialog->setWindowTitle(QApplication::translate("APCPointImportDialog", "\345\257\274\345\205\245\351\201\245\350\260\203", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("APCPointImportDialog", "\347\241\256\350\256\244", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("APCPointImportDialog", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class APCPointImportDialog: public Ui_APCPointImportDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APCPOINTIMPORT_H
