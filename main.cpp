#include "RCSTreeApp.h"
#include "RCSTreeMW.h"
#include "DBUtil.h"
#include "version.h"
#include "CheckSessionThread.h"
#include "GlobalInfo.h"
#include "PluginInterface.h"
typedef PluginInterface* (*getObj)();



void loadTranslator()
{
	char path[256] = { 0 };
	char* env = getenv("CPS_ENV");
	if (env) {
		strncat(path, env, 256);
	}
	strncat(path, "/resource/", 256);
	QString locale = QLocale::system().name();
	QString strTranslate = path;

	QString absPath = strTranslate + QString("DeviceExplorer_") + locale;
	QTranslator* translator = new QTranslator;
	if (translator->load(absPath)) {
		qApp->installTranslator(translator);
	}

	absPath = strTranslate + QString("qt_") + locale;
	QTranslator* qtTranslator = new QTranslator;
	if (qtTranslator->load(absPath)) {
		qApp->installTranslator(qtTranslator);
	}

	std::string strLocal = locale.toStdString();
	bool rev = initializeModelTranslate(strLocal);
}
int main(int argc, char *argv[])
{
	
	//打印版本信息
	if (echoVersion(argc, argv)) 
	{
		return 0;
	}

	if (argc == 1)
	{
		argc = 7;
		argv[1] = "-u";
		argv[2] = "sac";
		argv[3] = "-p";
		argv[4] = "sac";
		argv[5] = "-d";
		argv[6] = "dataserver1";
		//argv[7] = "-e";
		//argv[8] = "config";
	}

	

	StringOption stropt( "initstyle", "Database Testing,  yes | no", CPS_PERMITTED, CPS_PROHIBITED, "yes");
	StringOption*       pstringoption[1];
	pstringoption[0] = &stropt;
	OptionList optionList( (Option **)pstringoption, 1);

	RCSTreeApp* rcstreeApp = new RCSTreeApp(argc, argv,  (SignalHandler)0,optionList,CONFIG_SCOPE);
	
	//先把翻译注释掉
	
	QLocale locale = QLocale::system();
	QString sz = locale.name();

	QTranslator translator;
	QString qmName = "rcstree_" + sz;

	char* env = getenv("CPS_ENV");
	QString pathName = QString( env ) + ("/resource/");
	translator.load( pathName+qmName  );
	rcstreeApp->installTranslator(&translator);

	QTranslator translator_qt;
	translator_qt.load( QString( env ) + QString("/resource/qt_zh_CN.qm")  );
	rcstreeApp->installTranslator(&translator_qt);
	
	QTranslator translator_user;
	translator_user.load( QString( env ) + QString("/resource/UserMS_zh_CN.qm")  );
	rcstreeApp->installTranslator(&translator_user);


	QTranslator translator_windows;
	translator_windows.load("rcstree_zh_CN.qm");
	rcstreeApp->installTranslator(&translator_windows);



	rcstreeApp->setWindowIcon(QIcon(":/images/rcstree.png"));

	//获取历史库指针
	if (!DBUtil::connectDB(argc, argv))
	{
		std::cout<<"connect sacdatabase failed"<<std::endl;
		return 0;
	}
	//先注释掉
	/*if (!rcstreeApp->UserCheck())
	{
		return 0;
	}*/
	

	

	if (!GlobalInfo::initOTypeAndAType())
	{
		std::cout<<"initOTypeAndAType failed"<<std::endl;
		return 0;
	}

	GlobalInfo::init();
	
	loadTranslator();
	
	
	
	RCSTreeMW* rcstreeMW = new RCSTreeMW;
	//rcstreeMW->setWindowState(Qt::WindowMaximized);
	rcstreeMW->show();


	
	

	rcstreeApp->svc();
	delete rcstreeMW;
	delete rcstreeApp;
	return 1;
}