#ifndef BATCHCOMBOXDIALOG_H
#define BATCHCOMBOXDIALOG_H

#include "common.h"
#include "ui_batchcombox.h"

class BatchComboxDialog: public CpsDialog
{
	Q_OBJECT
public:
	BatchComboxDialog( QWidget* parent=0, Qt::WindowFlags flags=0 );
	~BatchComboxDialog();

	Ui::BatchComboxUI ui;

private:
	



private slots:
};

#endif