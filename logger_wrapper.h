#ifndef _LOG4CPLUS_WRAPPER_H_
#define _LOG4CPLUS_WRAPPER_H_

#include <iostream>
#include<fstream>
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/stringhelper.h>
#include <log4cplus/helpers/sleep.h>
#include <log4cplus/loggingmacros.h>
using std::string;
using namespace log4cplus;
using namespace log4cplus::helpers;
inline void createDefaultLogConfigFile(string fileName, string LoggerName)
{
	char* cpsenv = getenv("CPS_ENV");
	string logFilePath = cpsenv;
	logFilePath += "/data/log/";
	logFilePath += LoggerName + ".log";

	string  content;
	content.clear();
	content.append("log4cplus.rootLogger=ERROR, STDOUT\n");
	content.append("log4cplus.logger." + LoggerName + "=ERROR,R\n");
	content.append("log4cplus.appender.STDOUT=log4cplus::ConsoleAppender\n");
	content.append("log4cplus.appender.STDOUT.layout=log4cplus::PatternLayout\n");
	content.append("log4cplus.appender.STDOUT.layout.ConversionPattern=%D{%m/%d/%y %H:%M:%S} [%t] %-5p %c{2} %%%x%% - %m [%l]%n\n");
	content.append("log4cplus.appender.R=log4cplus::RollingFileAppender\n");	
	content.append("log4cplus.appender.R.File = " + logFilePath + "\n");
	content.append("log4cplus.appender.R.MaxFileSize=5000KB\n");
	content.append("log4cplus.appender.R.MaxBackupIndex=10\n");
	content.append("log4cplus.appender.R.layout=log4cplus::PatternLayout\n");
	content.append("log4cplus.appender.R.layout.ConversionPattern=%D{%m/%d/%y %H:%M:%S} [%t] %-5p %c{2} %%%x%% - %m [%l]%n\n");

    std::ofstream outputFile;
    outputFile.open(fileName.c_str(),ios::app);
	if (!outputFile)
		return;
	outputFile << content << std::endl;
	outputFile.close();
}

inline Logger initLogger(log4cplus::ConfigureAndWatchThread *logCfgWatcher, string cfgFileName)
{
	char* cpsenv = getenv("CPS_ENV");
	string cfgPath = cpsenv;
	cfgPath += "/etc/logConfig/";
	cfgPath += cfgFileName + ".properties";
    std::ifstream inputFile(cfgPath.c_str());
    if (!inputFile.is_open()) {
		createDefaultLogConfigFile(cfgPath, cfgFileName);
	}
	log4cplus::initialize();
	LogLog::getLogLog()->setInternalDebugging(true);
	Logger root = Logger::getRoot();
	logCfgWatcher = new ConfigureAndWatchThread(cfgPath.c_str(), 5 * 1000);
	return  Logger::getInstance(LOG4CPLUS_TEXT(cfgFileName));
}

inline void freeLogger(log4cplus::ConfigureAndWatchThread *logCfgWatcher)
{
	if (logCfgWatcher != NULL)
		delete logCfgWatcher;
	logCfgWatcher = NULL;
}


inline string getProcessName(char *argv[])
{
	string filename = argv[0];
	const size_t last_slash_idx = filename.find_last_of("\\/");
	if (std::string::npos != last_slash_idx)
		filename.erase(0, last_slash_idx + 1);
	const size_t period_idx = filename.rfind('.');
	if (std::string::npos != period_idx)
		filename.erase(period_idx);
	return filename;
}

/*example
//add the lib log4cplus in project file
inline int test(int argc, char *argv[])
{
	log4cplus::ConfigureAndWatchThread *logCfgWatcher;	
	string  appname = getProcessName(argv);	//logger for lib,add line : appname +="_libname";
	Logger applogger=initLogger(logCfgWatcher, appname);

	LOG4CPLUS_TRACE(applogger, "Start to run ."<<1<<"hello.");
	LOG4CPLUS_DEBUG(applogger, "Start to run .");
	LOG4CPLUS_INFO(applogger, "Start to run .");
	LOG4CPLUS_WARN(applogger, "Start to run .");
	LOG4CPLUS_ERROR(applogger, "Start to run.");
	LOG4CPLUS_FATAL(applogger, "Start to run.");
	freeLogger(logCfgWatcher);
}
*/

#endif 
