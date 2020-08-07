#include "AddFolderDialog.h"

AddFolderDialog::AddFolderDialog( QWidget* parent, Qt::WindowFlags flags ): CpsDialog( parent, flags )
{
	ui.setupUi(this);
	ui.lineEdit->setValidator(new QRegExpValidator(QRegExp("^\\w{1,80}$")));
}

AddFolderDialog::~AddFolderDialog()
{
}

QString AddFolderDialog::getText()
{
	return ui.lineEdit->text();
}