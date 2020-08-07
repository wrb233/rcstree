#ifndef MYQPROGRESSDIALOG_H
#define MYQPROGRESSDIALOG_H

#include "common.h"

class MyQProgressDialog: public QProgressDialog
{
public:
	MyQProgressDialog(int maxnum, QString text, QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~MyQProgressDialog();
	
private:
};

#endif