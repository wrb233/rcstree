#include "RCSTreeApp.h"
#include "GlobalInfo.h"

//构造函数
RCSTreeApp::RCSTreeApp(int &argc, char **argv,SignalHandler sigtermHandler,const OptionList& optionList,
	EnvironmentScope environmentScope) : QtApplication(argc, argv, sigtermHandler, optionList, environmentScope)
{
	//database = getDatabase();

	std::string tns = argv[6];
	//std::string tns2 = "dataserver2";

	try
	{
		GlobalInfo::g_Database = new ORMDatabase("orm","sac","sac",&tns);
		//delete database;
		qDebug()<<"connet dataserver1 success";
	}
	catch (Exception& e)
	{
		qDebug()<<"connet dataserver1 failed";
		try
		{
			//database = new ORMDatabase("orm","sac","sac",&tns2);
			qDebug()<<"connet dataserver2 success";
		}
		catch (Exception& e)
		{
			qDebug()<<"connet dataserver2 failed";
		}
	}

	//初始化用户接口
	try{
		GlobalInfo::g_User = UserMSInterface::UserMS_Instance();
		GlobalInfo::g_User->initUserMSData( GlobalInfo::g_Database, CONFIG_ENVIRONMENT );
	}  catch (Exception &e)  {
		std::cout << "Init UserMsg Modal throw Exception:" << e.getDescription() << std::endl;
	}
	//_database = createDatabase();

	//初始化操作日志
	char* processName[1];
	processName[0]="rcstree";
	GlobalInfo::g_DBLog = OperationLog::Instance();
	if (GlobalInfo::g_DBLog != NULL)
		GlobalInfo::g_DBLog->init(processName, GlobalInfo::g_Database, CONFIG_ENVIRONMENT, GlobalInfo::g_User);
}


//析构函数
RCSTreeApp::~RCSTreeApp()
{

}

bool RCSTreeApp::UserCheck()
{
	if (GlobalInfo::g_User)
	{
		UserObjectData UserData;
		memset(&UserData, 0, sizeof(UserObjectData));
		std::string strPermission = "DbDefine";
		std::string strTitle = std::string(QObject::tr("Login").toUtf8().constData());

		bool bPass = false;
		bPass = (GlobalInfo::g_User && GlobalInfo::g_User->ds6k_checkUser(UserData, strPermission, NULL, strTitle));
		if (!bPass)
		{
			std::cout << "user check fail!" << std::endl;
			return false;
		}
		GlobalInfo::g_Database->setUser(UserData.objectID);

		ObId systemUser = UserData.objectID;
		if (systemUser == 0)
		{
			std::cout << "System User Id is error!" << std::endl;
			::exit(-1);
		}
		(static_cast<ORMDatabase*>(GlobalInfo::g_Database))->setSystemUserId(GlobalInfo::g_Database->extractOCell(systemUser));
	}
	else
	{
		std::cout << "init UserMS fault!" << std::endl;
		return false;
	}
	return true;
}