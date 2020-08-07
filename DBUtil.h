#pragma once

#include "common.h"
#include "DataModel.h"
#include "ToolUtil.h"

class DBUtil:public QObject
{
	Q_OBJECT
public:
	DBUtil();
	~DBUtil();

	static bool connectDB(int argc, char *argv[]);
	static bool UpdateConnectDB(bool isAutoCommit = false);
	static bool commit();

	static bool checkTable(QString tableName);
	static bool createTable(QString tableName);
	static void setColoum(ORMColumnDescVector &m_descVector, std::string m_strName, std::string m_strType, bool m_bNullOK=1, bool m_bIndexed=0, bool m_bKey=0, bool m_bUnique=0);
	static bool createPrimaryKey(QString tableName);
	static bool readSQLFile(QString &filePath,QStringList &sqlList);
	static bool executeSQL(QString sql);
	static bool executeBatchSQL(QStringList sqlList);
	static bool executeStdSQL(std::string sql);
	
	static QList<ColumInfo> getDBTableInfo(QString tableName); 
	static ObId getRootId();
	static ObId getPartitionId(ObId obId);	
	static int createWiringord(ObId obId);	
	static ObId createObId(ObId partitionId,OType oType);
	static ObId getMinObId(ObId partitionId,OType oType);//构造某一分区otype的最小id
	static ObId getMaxObId(ObId partitionId,OType oType);//构造某一分区otype的最大id
	static QString getInsertWiring(QString wiringord,QString objectid,QString attributetypeid,QString wiredobjectid,QString housekeeping_state);
	static QString getInsertWiringStream(QString wiringord,QString objectid,QString attributetypeid,QString wiredobjectid,QString housekeeping_state);
	static void getDeleteSql(QStringList& deleteSqlList,ObId obId,int houseKeeping_State);
	static void getBatchSqlList(QStringList& sqlWireList,int wiringord,ObId parentId,ObId objectId);
	static void getBatchSqlListStream(QStringList& sqlWireList,QStringList& sqlLogList,int wiringord,ObId parentId,ObId objectId);//拼接插入一个otype对象所需要的所有sql，返回一个qstringlist
	
	static void getAORWiring(QStringList& sqlWireList,ObId objectId);
	static void getAORWiringStream(QStringList& sqlWireList,ObId objectId);

	static bool executeBatchMsStream();
	static bool executeBatchSingleStream();

	static bool executeBatchDMS(QStringList list);
	static bool executeBatchMV(QStringList list);
	static bool executeBatchDPS(QStringList list);
	static bool executeBatchDPC(QStringList list);
	static bool executeBatchAPC(QStringList list);
	static bool executeBatchWIRE(QStringList list);
	static bool executeBatchLOG(QStringList list);

	static bool getFastChildrenList(ObId parentObId,QList<ObId>& list);

	static int registParentIncrement(ObId obId);

	//锁增量提交
	static bool lockIncrement();
};