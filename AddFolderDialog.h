#pragma once

#include "common.h"
#include "ui_addfolder.h"

class AddFolderDialog: public CpsDialog
{
	Q_OBJECT
public:

	AddFolderDialog( QWidget* parent=0, Qt::WindowFlags flags=0 );

	~AddFolderDialog();

	QString getText();

	Ui::AddFolderUI ui;

private:

private slots:
};