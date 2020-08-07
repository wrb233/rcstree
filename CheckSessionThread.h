#pragma once

#include "common.h"

class CheckSessionThread : public QThread
{
	Q_OBJECT

public:

	explicit CheckSessionThread(QObject *parent=0);
	~CheckSessionThread();

protected:
	virtual void run();

signals:
	void signalLoginOut();
};