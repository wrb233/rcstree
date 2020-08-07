/********************************************************************************
** Form generated from reading UI file 'dpspointimport.ui'
**
** Created: Thu Aug 6 13:38:28 2020
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DPSPOINTIMPORT_H
#define UI_DPSPOINTIMPORT_H

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

class Ui_DPSPointImportDialog
{
public:
    QGridLayout *gridLayout;
    QTreeView *treeView;
    QHBoxLayout *_2;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *DPSPointImportDialog)
    {
        if (DPSPointImportDialog->objectName().isEmpty())
            DPSPointImportDialog->setObjectName(QString::fromUtf8("DPSPointImportDialog"));
        DPSPointImportDialog->resize(521, 552);
        gridLayout = new QGridLayout(DPSPointImportDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        treeView = new QTreeView(DPSPointImportDialog);
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

        okButton = new QPushButton(DPSPointImportDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        _2->addWidget(okButton);

        cancelButton = new QPushButton(DPSPointImportDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        _2->addWidget(cancelButton);


        gridLayout->addLayout(_2, 1, 0, 1, 1);


        retranslateUi(DPSPointImportDialog);
        QObject::connect(okButton, SIGNAL(clicked()), DPSPointImportDialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), DPSPointImportDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(DPSPointImportDialog);
    } // setupUi

    void retranslateUi(QDialog *DPSPointImportDialog)
    {
        DPSPointImportDialog->setWindowTitle(QApplication::translate("DPSPointImportDialog", "\345\257\274\345\205\245\351\201\245\344\277\241", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("DPSPointImportDialog", "\347\241\256\350\256\244", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("DPSPointImportDialog", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DPSPointImportDialog: public Ui_DPSPointImportDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DPSPOINTIMPORT_H
