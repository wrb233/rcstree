#include "CheckSessionThread.h"



CheckSessionThread::CheckSessionThread(QObject *parent):QThread(parent)
{
	qDebug() << "CheckSessionThread Thread : " << QThread::currentThreadId();
}

CheckSessionThread::~CheckSessionThread()
{

}

void CheckSessionThread::run()  {
	qDebug() << "CheckSessionThread Run Thread : " << QThread::currentThreadId();
	while (true)
	{
		
		msleep(3000);//30s
		emit signalLoginOut();
	}
}
