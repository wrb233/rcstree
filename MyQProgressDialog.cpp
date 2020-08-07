#include "MyQProgressDialog.h"

MyQProgressDialog::MyQProgressDialog(int maxnum, QString text, QWidget* parent, Qt::WindowFlags flags ): QProgressDialog( parent, flags )
{
	QFont font("ZYSong 18030",12);
	this->setFont(font);
	this->setWindowModality(Qt::WindowModal);
	this->setMinimumDuration(5);
	this->setWindowTitle(tr("Please Wait"));
	this->setLabelText(text);
	//this->setCancelButtonText(tr("Cancel"));
	this->setCancelButton(NULL);
	this->setRange(0,maxnum);
	this->show();
	this->setValue(0);
}

MyQProgressDialog::~MyQProgressDialog()
{
}