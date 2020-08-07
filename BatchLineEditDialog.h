#ifndef BATCHLINEEDITDIALOG_H
#define BATCHLINEEDITDIALOG_H

#include "common.h"
#include "ui_batchlineedit.h"

class BatchLineEditDialog: public CpsDialog
{
	Q_OBJECT
public:
	BatchLineEditDialog( QWidget* parent=0, Qt::WindowFlags flags=0 );
	~BatchLineEditDialog();

	Ui::BatchLineEditUI ui;

private:
	


private slots:
};

#endif