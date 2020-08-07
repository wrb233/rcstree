#include "DBUtil.h"
#include "GlobalInfo.h"

DBUtil::DBUtil():QObject()
{

}

DBUtil::~DBUtil()
{

}

/************************************************************************/
/*      //连接历史库                                                                */
/************************************************************************/
bool DBUtil::connectDB(int argc, char *argv[])
{
	std::string user,password,dataserver;

	for(int i=0;i<argc;i++)
	{
		if(qstricmp(argv[i],"-u") == 0)
		{
			while (*(argv[i+1])!='\0')
			{
				user += *(argv[i+1]++);
			}
		}

		if(qstricmp(argv[i],"-p") == 0)
		{
			while (*(argv[i+1])!='\0')
			{
				password += *(argv[i+1]++);
			}
		}

		if(qstricmp(argv[i],"-d") == 0)
		{
			while (*(argv[i+1])!='\0')
			{
				dataserver += *(argv[i+1]++);
			}
		}
	}

	if(user == "")
		user = "sac";
	if(password == "")
		password = "sac";
	if(dataserver == "")
		//dataserver = "dataserver1+dataserver2";
	    dataserver = "dataserver1";
	QStringList dbList = QString::fromStdString(dataserver).split("+");
	CPS_ORM_Initialize();
	DBPoolConfig cfg;
	cfg.m_bAutoCommit=false;
	cfg.m_nPoolSize=dbList.size();
	cfg.m_strUser=user;
	cfg.m_strPassword=password;	

	for(int i=0;i<dbList.size();i++)
	{
		cfg.m_strTNS[i] = dbList.at(i).toStdString();	
	}
	GlobalInfo::g_DBPoolHandle = CPS_ORM_NewDBPoolbyConfig(cfg);
	
	if(CPS_ORM_Connect(GlobalInfo::g_DBPoolHandle))
	{
		CPS_ORM_SetAutoCommit(GlobalInfo::g_DBPoolHandle,false);
		CPS_ORM_SetStreamAutoCommit(GlobalInfo::g_DBPoolHandle,false);
		qDebug()<<"connect to sac database success";
		return true;
	}
	qDebug()<<"connect to sac database failure";
	return false;
}

/************************************************************************/
/*      //校验数据库连接，若失败重新连接历史库                                                                */
/************************************************************************/
bool DBUtil::UpdateConnectDB(bool isAutoCommit)
{
	CPS_ORM_UpdatePool(GlobalInfo::g_DBPoolHandle);
	if(CPS_ORM_GetDBPoolState(GlobalInfo::g_DBPoolHandle)!=DBS_ACTIVE)
	{	
		qDebug()<<"update sac database failure";
		return false;
	}
	CPS_ORM_SetAutoCommit(GlobalInfo::g_DBPoolHandle,isAutoCommit);
	CPS_ORM_SetStreamAutoCommit(GlobalInfo::g_DBPoolHandle,isAutoCommit);	
	qDebug()<<"update sac database success";
	return true;	
}

bool DBUtil::commit()
{
	if (CPS_ORM_Commit(GlobalInfo::g_DBPoolHandle)==1)
	{
		return true;
	}
	if (CPS_ORM_RollBack(GlobalInfo::g_DBPoolHandle)==-1)
	{
		qDebug()<<"commit rollback failure!";
	}
	return false;
}

bool DBUtil::readSQLFile(QString &filePath,QStringList &sqlList)
{
	QFile file(filePath);  
	if(file.open(QIODevice::ReadOnly | QIODevice::Text)) 
	{
		QTextStream in(&file);  

		QString line = in.readLine();  

		while (!line.isNull()) 
		{
			sqlList.append(line);
			line = in.readLine();
		}
		/*while(!file.atEnd())
		{  
		QByteArray line = file.readLine();  
		QString str(line);  
		sqlList.append(str);
		}   */
		in.flush();
		file.flush();
		file.close();
		return true;
	}  
	return false;
}

bool DBUtil::checkTable(QString tableName)
{
	if (UpdateConnectDB())
	{
		tableName = tableName.toUpper();
		int tableState = CPS_ORM_ExistTable(GlobalInfo::g_DBPoolHandle, tableName.trimmed().toStdString());
		if (0==tableState)//如果表不存在，则新建表
		{
			if (createTable(tableName))
			{
				if (createPrimaryKey(tableName))
				{
					return true;
				}
			}
		}else if (1==tableState)//表存在
		{
			return true;
		}
	}
	return false;
}

bool DBUtil::createTable(QString tableName)
{
	ORMColumnDescVector m_descVector;
	if(tableName=="C_COMCFG_TABLE")
	{
		setColoum(m_descVector, "ID", "bigint(19)", 0, 1, 1);
		setColoum(m_descVector, "PARENTID", "bigint(19)", 0);
		setColoum(m_descVector, "TYPE", "short");
		setColoum(m_descVector, "NAME", "char(1024)");
		setColoum(m_descVector, "ORDERNO", "short");
	}

	if(CPS_ORM_CreateTable(GlobalInfo::g_DBPoolHandle, tableName.toStdString(), m_descVector)==1)
	{
		qDebug()<<"CreateTable:"+tableName;
	}
	else {
		qDebug()<<"CreateTable:" + tableName + "err" + CPS_ORM_GetLastErrorDesc(GlobalInfo::g_DBPoolHandle).c_str();
		return false;
	}
	return true;
}

void DBUtil::setColoum(ORMColumnDescVector &m_descVector, std::string m_strName, std::string m_strType, bool m_bNullOK, bool m_bIndexed, bool m_bKey, bool m_bUnique)
{
	ORMColumnDesc columnDesc;
	columnDesc.m_strName = m_strName;
	columnDesc.m_strType = m_strType;
	columnDesc.m_bNullOK = m_bNullOK;
	columnDesc.m_bIndexed = m_bIndexed;
	columnDesc.m_bKey = m_bKey;
	columnDesc.m_bUnique = m_bUnique;
	m_descVector.push_back(columnDesc);
}

bool DBUtil::createPrimaryKey(QString tableName)
{
	//QThread::msleep(1000);
	ACE_OS::sleep(ACE_Time_Value(1,0));//睡眠1s
	// 增加主键
	ACE_Time_Value tv = ACE_OS::gettimeofday();
	timespec_t st = tv;
	char tmp[512];
	sprintf(tmp, "ind_%lld_%ld", st.tv_sec, st.tv_nsec);
	std::string indexName = tmp;

	QString sqlTemplate = "alter table %1 add constraint %2 primary key";
	QString sql = sqlTemplate.arg(tableName).arg(QString(indexName.c_str()));
	
	//if(tableName.startsWith("C_COMCFG_TABLE"))
	//{
	//	sql = sql + "(ID)";

	//}

	//if(-1==CPS_ORM_DirectExecuteSql(dbPoolHandle, sql.toUtf8().data(), 0))
	//{
	//	qDebug()<<"CreateTablePrimaryKey error:"+tableName;
	//	return false;
	//}
	return true;
}

bool DBUtil::executeSQL(QString sql)
{
	try
	{
		if (UpdateConnectDB())
		{
			if(CPS_ORM_DirectExecuteSql(GlobalInfo::g_DBPoolHandle,sql.toUtf8().data())>=0)
			{
				qDebug()<<sql;
				qDebug()<<"executeSQL  SUCCESS!";
				//CPS_ORM_Commit(dbPoolHandle);
				return true;
			}
		}
	}
	catch (Exception& e)
	{
		qDebug()<<"executeSQL FAILURE Exception!";
	}
	qDebug()<<"executeSQL  failure!";
	return false;
}

bool DBUtil::executeBatchSQL(QStringList sqlList)
{
	try
	{
		if (UpdateConnectDB())
		{
			foreach(QString sql,sqlList)
			{
				if(CPS_ORM_DirectExecuteSql(GlobalInfo::g_DBPoolHandle,sql.toUtf8().data())>=0)
				{
					QApplication::processEvents();
					qDebug()<<sql;
					//qDebug()<<"executeSQL  SUCCESS!";
					//CPS_ORM_Commit(dbPoolHandle);
				}else{
					if (CPS_ORM_RollBack(GlobalInfo::g_DBPoolHandle)<0)
					{
						qDebug()<<"executesql rollback failure!";
					}
					return false;
				}
			}
			return true;
		}
	}
	catch (Exception& e)
	{
		qDebug()<<"executeSQL FAILURE Exception!";
	}
	if (CPS_ORM_RollBack(GlobalInfo::g_DBPoolHandle)<0)
	{
		qDebug()<<"executesql rollback failure!";
	}
	qDebug()<<"executeSQL  failure!";
	return false;
}

bool DBUtil::executeStdSQL(std::string sql)
{
	try
	{
		if (UpdateConnectDB())
		{
			if(CPS_ORM_DirectExecuteSql(GlobalInfo::g_DBPoolHandle,sql)>=0)
			{
				qDebug()<<"executeSQL  SUCCESS!";
				return true;
			}
		}
	}
	catch (Exception& e)
	{
		qDebug()<<"executeSQL FAILURE Exception!";
	}
	qDebug()<<"executeSQL  failure!";
	return false;
}

QList<ColumInfo> DBUtil::getDBTableInfo(QString tableName)
{
	QList<ColumInfo> list;
	RECORDSETHANDLE recordsetHandle = CPS_ORM_RsNewRecordSet();
	try
	{
		if (UpdateConnectDB())
		{		
			tableName = tableName.toUpper();
			QString sql = "SELECT a.COLUMN_NAME,\
						  a.DATA_TYPE,\
						  a.DATA_LENGTH,\
						  a.DATA_PRECISION,\
						  a.DATA_SCALE,\
						  a.NULLABLE\
						  FROM USER_TAB_COLUMNS a, USER_COL_COMMENTS b\
						  WHERE a.TABLE_NAME = '"+tableName+"'\
						  and b.TABLE_NAME = '"+tableName+"'\
						  and a.COLUMN_NAME = b.COLUMN_NAME\
						  order by a.COLUMN_ID";
			
			int rows = CPS_ORM_RsLoadData(recordsetHandle, sql.toUtf8().data(), GlobalInfo::g_DBPoolHandle);
			if (rows>0)
			{
				for (int i=0;i<rows;i++)
				{
					ColumInfo colum;
					
					std::string columnName = CPS_ORM_RsGetStringValue(recordsetHandle, i, 0);
					std::string dataType = CPS_ORM_RsGetStringValue(recordsetHandle, i, 1);
					int dataLength = (int)CPS_ORM_RsGetNumberValue(recordsetHandle, i, 2);
					int dataPrecision = (int)CPS_ORM_RsGetNumberValue(recordsetHandle, i, 3);
					int dataScale = (int)CPS_ORM_RsGetNumberValue(recordsetHandle, i, 4);
					std::string nullAble = CPS_ORM_RsGetStringValue(recordsetHandle, i, 5);

					colum.COLUMN_NAME = QString::fromUtf8(columnName.c_str());
					colum.DATA_LENGTH = dataLength;
					colum.DATA_PRECISION = dataPrecision;
					colum.DATA_SCALE = dataScale;
					colum.NULLABLE = QString::fromUtf8(nullAble.c_str());

					QString dataTypeTemp = QString::fromUtf8(dataType.c_str()).toUpper();
					if (dataTypeTemp.startsWith("NUMBER"))
					{
						if (dataPrecision==0)
						{
							colum.DATA_TYPE = ENUM_DOUBLE;
						}else{
							if (dataScale==0)
							{
								colum.DATA_TYPE = ENUM_LONG;
							}else{
								colum.DATA_TYPE = ENUM_DOUBLE;
							}
						}
					}else if (dataTypeTemp.startsWith("VARCHAR"))
					{
						colum.DATA_TYPE = ENUM_VARCHAR;
					}else if (dataTypeTemp.startsWith("CHAR"))
					{
						colum.DATA_TYPE = ENUM_CHAR;		
					}else if (dataTypeTemp.startsWith("BLOB"))
					{
						colum.DATA_TYPE =ENUM_BLOB;		
					}else if (dataTypeTemp.startsWith("CLOB"))
					{
						colum.DATA_TYPE = ENUM_CLOB;		
					}else if (dataTypeTemp.startsWith("TIMESTAMP"))
					{
						colum.DATA_TYPE = ENUM_TIMESTAMP;		
					}else if (dataTypeTemp.startsWith("DATE"))
					{
						colum.DATA_TYPE = ENUM_DATE;		
					}else
					{
						colum.DATA_TYPE = ENUM_UNKNOW;		
					}

					list.append(colum);
				}
			}			
		}
	}
	catch (Exception& e)
	{
		qDebug()<<"getDBTableInfo FAILURE Exception!";
	}
	CPS_ORM_RsFreeRecordSet(recordsetHandle);
	return list;
}

int DBUtil::createWiringord(ObId obId)
{
	int wringord = -1;
	RECORDSETHANDLE recordsetHandle = CPS_ORM_RsNewRecordSet();

	try
	{
		if (UpdateConnectDB())
		{
			QString sql = "select max(t.wiringord) from wiring t where t.objectid=%1 and t.attributetypeid=8";
			sql = sql.arg(QString::number(obId));

			int rows = CPS_ORM_RsLoadData(recordsetHandle, sql.toUtf8().data(), GlobalInfo::g_DBPoolHandle);
			if (rows>0)
			{
				wringord = (int)CPS_ORM_RsGetNumberValue(recordsetHandle, 0, 0);			
				wringord = wringord + 1;
			}
		}
	}
	catch (Exception& e)
	{
		wringord = -1;
		qDebug()<<"getWiringordOfWiring FAILURE Exception!";
	}

	CPS_ORM_RsFreeRecordSet(recordsetHandle);
	return wringord;
}

ObId DBUtil::getRootId()
{
	ObId pmsRoot = 0;
	RECORDSETHANDLE recordsetHandle = CPS_ORM_RsNewRecordSet();

	try
	{
		if (UpdateConnectDB())
		{
			QString sql = "select t.objectid from root t";

			int rows = CPS_ORM_RsLoadData(recordsetHandle, sql.toUtf8().data(), GlobalInfo::g_DBPoolHandle);
			if (rows>0)
			{
				pmsRoot = (ObId)CPS_ORM_RsGetNumberValue(recordsetHandle, 0, 0);
			}
		}
	}
	catch (Exception& e)
	{
		qDebug()<<"getPMSRootId FAILURE Exception!";
	}

	CPS_ORM_RsFreeRecordSet(recordsetHandle);
	return pmsRoot;
}

QString DBUtil::getInsertWiring(QString wiringord,QString objectid,QString attributetypeid,QString wiredobjectid,QString housekeeping_state)
{
	QString insertWiringSql = "insert into wiring(wiringord,objectid,attributetypeid,wiredobjectid,housekeeping_state) values(%1,%2,%3,%4,%5)";			
	insertWiringSql = insertWiringSql.arg(wiringord).arg(objectid).arg(attributetypeid).arg(wiredobjectid).arg(housekeeping_state);
	return insertWiringSql;
}

QString DBUtil::getInsertWiringStream(QString wiringord,QString objectid,QString attributetypeid,QString wiredobjectid,QString housekeeping_state)
{
	QString insertWiring = "%1,%2,%3,%4,%5";			
	insertWiring = insertWiring.arg(wiringord).arg(objectid).arg(attributetypeid).arg(wiredobjectid).arg(housekeeping_state);
	return insertWiring;
}

void DBUtil::getAORWiring(QStringList& sqlWireList,ObId objectId)
{
	ContainerData aorData;
	GlobalInfo::g_User->getCurrentAORS(aorData);

	int num = aorData.getNumberOfElements();
	if (num>0)
	{
		const ObId *aorObId = aorData.getObIds();
		for (int i=0;i<num;i++)
		{
			QString insertAORWiring = getInsertWiring(QString::number(i),QString::number(objectId),"10",QString::number(aorObId[i]),"1");
			sqlWireList.append(insertAORWiring);
		}
	}
}

void DBUtil::getAORWiringStream(QStringList& sqlWireList,ObId objectId)
{
	ContainerData aorData;
	GlobalInfo::g_User->getCurrentAORS(aorData);

	int num = aorData.getNumberOfElements();
	if (num>0)
	{
		const ObId *aorObId = aorData.getObIds();
		for (int i=0;i<num;i++)
		{
			QString insertAORWiring = getInsertWiringStream(QString::number(i),QString::number(objectId),"10",QString::number(aorObId[i]),"1");
			sqlWireList.append(insertAORWiring);
		}
	}
}

void DBUtil::getDeleteSql(QStringList& deleteSqlList,ObId obId,int houseKeeping_State)
{
	OType oType = ToolUtil::databaseExtractOType(obId);
	QString tableName = ToolUtil::databaseMatchOName(oType);
	QString deleteObject = "update %1 set housekeeping_state=3,housekeeping_previousstate=%2,housekeeping_previoususerid=0 where objectid= %3";
	deleteObject = deleteObject.arg(tableName).arg(QString::number(houseKeeping_State)).arg(QString::number(obId));
	QString deleteWiring = "update wiring set housekeeping_state=3,housekeeping_previousstate=%1 where objectid=%2 or wiredobjectid=%2";
	deleteWiring = deleteWiring.arg(QString::number(houseKeeping_State)).arg(QString::number(obId));
	QString deleteIncrementLog = "delete cpsincrementlog where objectid=%1";
	deleteIncrementLog = deleteIncrementLog.arg(QString::number(obId));
	QString insertIncrementLog = "insert into cpsincrementlog (objectid,objecttypeid,incrementtype)values(%1,%2,%3)";
	insertIncrementLog = insertIncrementLog.arg(QString::number(obId)).arg(QString::number(oType)).arg("1");
	deleteSqlList.append(deleteObject);
	deleteSqlList.append(deleteWiring);
	deleteSqlList.append(deleteIncrementLog);
	deleteSqlList.append(insertIncrementLog);
}


ObId DBUtil::getPartitionId(ObId obId)//后续要改成database read的方式
{
	ObId parttionId = 0;
	RECORDSETHANDLE recordsetHandle = CPS_ORM_RsNewRecordSet();

	try
	{
		if (UpdateConnectDB())
		{
			OType oType = ToolUtil::databaseExtractOType(obId);
			QString tableName = ToolUtil::databaseMatchOName(oType);
			QString sql = "select t.partitionid from %1 t where t.objectid=%2";
			sql = sql.arg(tableName).arg(QString::number(obId));

			int rows = CPS_ORM_RsLoadData(recordsetHandle, sql.toUtf8().data(), GlobalInfo::g_DBPoolHandle);
			if (rows>0)
			{
				parttionId = (ObId)CPS_ORM_RsGetNumberValue(recordsetHandle, 0, 0);
			}
		}
	}
	catch (Exception& e)
	{
		qDebug()<<"getPartitionId FAILURE Exception!";
	}

	CPS_ORM_RsFreeRecordSet(recordsetHandle);

	return parttionId;
}

ObId DBUtil::createObId(ObId partitionId,OType oType)
{
	ObId minObId = getMinObId(partitionId,oType);
	ObId maxObId = getMaxObId(partitionId,oType);
	if (minObId==0||maxObId==0)
	{
		return 0;
	}
	ObId obId = 0;

	RECORDSETHANDLE recordsetHandle = CPS_ORM_RsNewRecordSet();

	try
	{
		if (UpdateConnectDB())
		{
			QString tableName = ToolUtil::databaseMatchOName(oType);
			if (partitionId!=0&&!tableName.isEmpty())
			{
				QString sql = "select max(t.objectid) from %1 t where t.objectid>=%2 and t.objectid<=%3";
				//select  * from dmscommunicateunit t where bitand(t.objectid,4290772992)=62914560;
				sql = sql.arg(tableName).arg(QString::number(minObId)).arg(QString::number(maxObId));
				int rows = CPS_ORM_RsLoadData(recordsetHandle, sql.toUtf8().data(), GlobalInfo::g_DBPoolHandle);
				if (rows>0)
				{
					obId = (ObId)CPS_ORM_RsGetNumberValue(recordsetHandle, 0, 0);
					if (obId==0)
					{
						obId = minObId;
					}else{
						obId = obId+1;
					}
				}
			}
		}
	}
	catch (Exception& e)
	{
		qDebug()<<"createObId FAILURE Exception!";
	}

	CPS_ORM_RsFreeRecordSet(recordsetHandle);

	if (ToolUtil::databaseExtractOType(obId)==oType)//校验生成id正确性
	{
		return obId;
	}

	return 0;
}

ObId DBUtil::getMinObId(ObId partitionId,OType oType)
{
	partitionId = partitionId&0x00000000ffffffff;
	unsigned long long  data33_64 = (unsigned long long)oType<<32;
	unsigned long long  data23_32 = partitionId-1<<22;
	unsigned long long  data1_22_min = 1;
	unsigned long long data_min = data33_64+data23_32+data1_22_min;
	//qDebug()<<QString::number(data_min);
	ObId obId_min = (ObId)data_min;
	if (ToolUtil::databaseExtractOType(obId_min)==oType)//校验生成id正确性
	{
		return obId_min;
	}
	return 0;
}

ObId DBUtil::getMaxObId(ObId partitionId,OType oType)
{
	partitionId = partitionId&0x00000000ffffffff;
	unsigned long long  data33_64 = (unsigned long long)oType<<32;
	unsigned long long  data23_32 = partitionId-1<<22;
	unsigned long long  data1_22_max = 4194303;
	unsigned long long data_max = data33_64+data23_32+data1_22_max;
	//qDebug()<<QString::number(data_max);
	ObId obId_max = (ObId)data_max;
	if (ToolUtil::databaseExtractOType(obId_max)==oType)//校验生成id正确性
	{
		return obId_max;
	}
	return 0;
}

void DBUtil::getBatchSqlList(QStringList& sqlList,int wiringord,ObId parentId,ObId objectId)
{
	QString insertWiringChild = DBUtil::getInsertWiring(QString::number(wiringord),QString::number(parentId),"8",QString::number(objectId),"1");
	QString insertWiringFather = DBUtil::getInsertWiring("0",QString::number(objectId),"9",QString::number(parentId),"1");
	QString insertIncrementLog = "insert into cpsincrementlog (objectid,objecttypeid,incrementtype)values(%1,%2,%3)";
	OType oType =ToolUtil::databaseExtractOType(objectId);
	insertIncrementLog = insertIncrementLog.arg(QString::number(objectId)).arg(QString::number(oType)).arg("0");
	sqlList.append(insertWiringChild);
	sqlList.append(insertWiringFather);
	sqlList.append(insertIncrementLog);
}

void DBUtil::getBatchSqlListStream(QStringList& sqlWireList,QStringList& sqlLogList,int wiringord,ObId parentId,ObId objectId)
{
	QString insertWiringChild = DBUtil::getInsertWiringStream(QString::number(wiringord),QString::number(parentId),"8",QString::number(objectId),"1");
	QString insertWiringFather = DBUtil::getInsertWiringStream("0",QString::number(objectId),"9",QString::number(parentId),"1");
	QString insertIncrementLog = "%1,%2,%3";
	OType oType =ToolUtil::databaseExtractOType(objectId);
	insertIncrementLog = insertIncrementLog.arg(QString::number(objectId)).arg(QString::number(oType)).arg("0");
	sqlWireList.append(insertWiringChild);
	sqlWireList.append(insertWiringFather);
	sqlLogList.append(insertIncrementLog);
}

//test
bool DBUtil::executeBatchMsStream()
{
	//CPS_ORM_SetStreamAutoCommit(dbPoolHandle,2);
	std::string fieldNameList = "OBJECTID,NAME,CC1";
	std::string fieldAndDataTypeList = ":OBJECTID<bigint>,:NAME<char[256]>,:CC1<float>";
	STREAMHANDLE streamHandle = CPS_ORM_msNewInsertStream(GlobalInfo::g_DBPoolHandle, "MVPOINT",fieldNameList,fieldAndDataTypeList,20480);
	if(streamHandle==-1)
	{
		std::cout<<"Insert CPSPARTITION failed!"<<std::endl;
		return -1;
	}

	//ObId obId = 1404454305793l;
	ObId obId = 141826195459l;
	std::string name="fenqutest";
	for(int i=0;i<1;i++)
	{
		float a = 0.100000;
		qDebug()<<CPS_ORM_msWriteLongLong(streamHandle,obId);
		qDebug()<<CPS_ORM_msWriteString(streamHandle, name);
		qDebug()<<CPS_ORM_msWriteFloat(streamHandle, a);
		obId++;
	}
	
	qDebug()<<CPS_ORM_msFlush(streamHandle, 1);//刷新流
	CPS_ORM_msFreeStream(streamHandle);//释放流
	qDebug()<<CPS_ORM_Commit(GlobalInfo::g_DBPoolHandle);


}
//test
bool DBUtil::executeBatchSingleStream()
{
	std::string fieldNameList = "OBJECTID,NAME";
	std::string fieldAndDataTypeList = ":OBJECTID<bigint>,:NAME<char[256]>";
	if(-1==CPS_ORM_SetInsertStream(GlobalInfo::g_DBPoolHandle, "CPSPARTITION",fieldNameList,fieldAndDataTypeList, 1024))
	{
		std::cout<<"Insert sqllog failed!"<<std::endl;
		return -1;
	}


	ObId obId = 1404454305793l;
	//ObId obId = 1504454305793l;
	std::string name="fenqutest";
	for(int i=0;i<5;i++)
	{
		qDebug()<<CPS_ORM_WriteLongLong(GlobalInfo::g_DBPoolHandle,obId);
		qDebug()<<CPS_ORM_WriteString(GlobalInfo::g_DBPoolHandle, name.c_str());
		obId++;
	}

	//qDebug()<<CPS_ORM_Flush(dbPoolHandle, 0);//刷新流
	//qDebug()<<CPS_ORM_Commit(dbPoolHandle);


}

bool DBUtil::executeBatchDMS(QStringList list)
{
	std::string fieldNameList = "OBJECTID,PARTITIONID,OBJORDER,NAME,IPADDRA,IPADDRB,PORTA,PORTB,HOUSEKEEPING_STATE,HOUSEKEEPING_USERID,DEVICEPROPERTY";
	std::string fieldAndDataTypeList = ":OBJECTID<bigint>,:PARTITIONID<bigint>,:OBJORDER<int>,:NAME<char[256]>,:IPADDRA<char[256]>,:IPADDRB<char[256]>,:PORTA<short>,:PORTB<short>,:HOUSEKEEPING_STATE<short>,:HOUSEKEEPING_USERID<int>,:DEVICEPROPERTY<short>";
	STREAMHANDLE streamHandle = CPS_ORM_msNewInsertStream(GlobalInfo::g_DBPoolHandle, "DMSCOMMUNICATEUNIT",fieldNameList,fieldAndDataTypeList,20480);
	if(streamHandle==-1)
	{
		qDebug()<<"Insert DMSCOMMUNICATEUNIT failed!";
		CPS_ORM_RollBack(GlobalInfo::g_DBPoolHandle);
		return false;
	}

	foreach(QString object,list)
	{
		QStringList attribute = object.split(QRegExp("[,;\t]"), QString::KeepEmptyParts);
		CPS_ORM_msWriteLongLong(streamHandle,attribute[0].toLongLong());
		CPS_ORM_msWriteLongLong(streamHandle,attribute[1].toLongLong());
		CPS_ORM_msWriteInt(streamHandle,attribute[2].toInt());
		CPS_ORM_msWriteString(streamHandle,attribute[3].toUtf8().data());
		CPS_ORM_msWriteString(streamHandle,attribute[4].toUtf8().data());
		CPS_ORM_msWriteString(streamHandle,attribute[5].toUtf8().data());
		CPS_ORM_msWriteShort(streamHandle,attribute[6].toShort());
		CPS_ORM_msWriteShort(streamHandle,attribute[7].toShort());
		CPS_ORM_msWriteShort(streamHandle,attribute[8].toShort());
		CPS_ORM_msWriteInt(streamHandle,attribute[9].toInt());
		CPS_ORM_msWriteShort(streamHandle,attribute[10].toShort());
	}

	if (CPS_ORM_msFlush(streamHandle, 1)==1)
	{
		CPS_ORM_msFreeStream(streamHandle);//释放流
		return true;
	}else{
		CPS_ORM_msFreeStream(streamHandle);//释放流
		CPS_ORM_RollBack(GlobalInfo::g_DBPoolHandle);
		return false;
	}
}

bool DBUtil::executeBatchMV(QStringList list)
{
	std::string fieldNameList = "OBJECTID,PARTITIONID,OBJORDER,PROTOCOLADDRESS,NAME,CC1,CC2,RANGEHIGH,RANGELOW,HLIM,LLIM,HHLIM,LLLIM,HHHLIM,LLLLIM,HOUSEKEEPING_STATE,HOUSEKEEPING_USERID,DMSCUID,DESCRIPTION";
	std::string fieldAndDataTypeList = ":OBJECTID<bigint>,:PARTITIONID<bigint>,:OBJORDER<int>,:PROTOCOLADDRESS<char[256]>,:NAME<char[256]>,:CC1<float>,:CC2<float>,:RANGEHIGH<float>,:RANGELOW<float>,:HLIM<float>,:LLIM<float>,:HHLIM<float>,:LLLIM<float>,:HHHLIM<float>,:LLLLIM<float>,:HOUSEKEEPING_STATE<short>,:HOUSEKEEPING_USERID<int>,:DMSCUID<bigint>,:DESCRIPTION<char[256]>";
	STREAMHANDLE streamHandle = CPS_ORM_msNewInsertStream(GlobalInfo::g_DBPoolHandle, "MVPOINT",fieldNameList,fieldAndDataTypeList,20480);
	if(streamHandle==-1)
	{
		qDebug()<<"Insert MVPOINT failed!";
		CPS_ORM_RollBack(GlobalInfo::g_DBPoolHandle);
		return false;
	}

	foreach(QString object,list)
	{
		QStringList attribute = object.split(QRegExp("[,;\t]"), QString::KeepEmptyParts);
		CPS_ORM_msWriteLongLong(streamHandle,attribute[0].toLongLong());
		CPS_ORM_msWriteLongLong(streamHandle,attribute[1].toLongLong());
		CPS_ORM_msWriteInt(streamHandle,attribute[2].toInt());
		CPS_ORM_msWriteString(streamHandle,attribute[3].toUtf8().data());
		CPS_ORM_msWriteString(streamHandle,attribute[4].toUtf8().data());
		CPS_ORM_msWriteFloat(streamHandle,attribute[5].toFloat());
		CPS_ORM_msWriteFloat(streamHandle,attribute[6].toFloat());
		CPS_ORM_msWriteFloat(streamHandle,attribute[7].toFloat());
		CPS_ORM_msWriteFloat(streamHandle,attribute[8].toFloat());
		CPS_ORM_msWriteFloat(streamHandle,attribute[9].toFloat());
		CPS_ORM_msWriteFloat(streamHandle,attribute[10].toFloat());
		CPS_ORM_msWriteFloat(streamHandle,attribute[11].toFloat());
		CPS_ORM_msWriteFloat(streamHandle,attribute[12].toFloat());
		CPS_ORM_msWriteFloat(streamHandle,attribute[13].toFloat());
		CPS_ORM_msWriteFloat(streamHandle,attribute[14].toFloat());
		CPS_ORM_msWriteShort(streamHandle,attribute[15].toShort());
		CPS_ORM_msWriteInt(streamHandle,attribute[16].toInt());
		CPS_ORM_msWriteLongLong(streamHandle,attribute[17].toLongLong());
		CPS_ORM_msWriteString(streamHandle,attribute[18].toUtf8().data());
	}

	if (CPS_ORM_msFlush(streamHandle, 1)==1)
	{
		CPS_ORM_msFreeStream(streamHandle);//释放流
		return true;
	}else{
		CPS_ORM_msFreeStream(streamHandle);//释放流
		CPS_ORM_RollBack(GlobalInfo::g_DBPoolHandle);
		return false;
	}
}
bool DBUtil::executeBatchDPS(QStringList list)
{
	std::string fieldNameList = "OBJECTID,PARTITIONID,OBJORDER,PROTOCOLADDRESS,NAME,ISREVERSED,HOUSEKEEPING_STATE,HOUSEKEEPING_USERID,DMSCUID,DESCRIPTION";
	std::string fieldAndDataTypeList = ":OBJECTID<bigint>,:PARTITIONID<bigint>,:OBJORDER<int>,:PROTOCOLADDRESS<char[256]>,:NAME<char[256]>,:ISREVERSED<short>,:HOUSEKEEPING_STATE<short>,:HOUSEKEEPING_USERID<int>,:DMSCUID<bigint>,:DESCRIPTION<char[256]>";
	STREAMHANDLE streamHandle = CPS_ORM_msNewInsertStream(GlobalInfo::g_DBPoolHandle, "DPSPOINT",fieldNameList,fieldAndDataTypeList,20480);
	if(streamHandle==-1)
	{
		qDebug()<<"Insert DPSPOINT failed!";
		CPS_ORM_RollBack(GlobalInfo::g_DBPoolHandle);
		return false;
	}

	foreach(QString object,list)
	{
		QStringList attribute = object.split(QRegExp("[,;\t]"), QString::KeepEmptyParts);
		CPS_ORM_msWriteLongLong(streamHandle,attribute[0].toLongLong());
		CPS_ORM_msWriteLongLong(streamHandle,attribute[1].toLongLong());
		CPS_ORM_msWriteInt(streamHandle,attribute[2].toInt());
		CPS_ORM_msWriteString(streamHandle,attribute[3].toUtf8().data());
		CPS_ORM_msWriteString(streamHandle,attribute[4].toUtf8().data());
		CPS_ORM_msWriteShort(streamHandle,attribute[5].toShort());
		CPS_ORM_msWriteShort(streamHandle,attribute[6].toShort());
		CPS_ORM_msWriteInt(streamHandle,attribute[7].toInt());
		CPS_ORM_msWriteLongLong(streamHandle,attribute[8].toLongLong());
		CPS_ORM_msWriteString(streamHandle,attribute[9].toUtf8().data());
	}

	if (CPS_ORM_msFlush(streamHandle, 1)==1)
	{
		CPS_ORM_msFreeStream(streamHandle);//释放流
		return true;
	}else{
		CPS_ORM_msFreeStream(streamHandle);//释放流
		CPS_ORM_RollBack(GlobalInfo::g_DBPoolHandle);
		return false;
	}
}

bool DBUtil::executeBatchDPC(QStringList list)
{
	std::string fieldNameList = "OBJECTID,PARTITIONID,OBJORDER,PROTOCOLADDRESS,NAME,CONTROLMODEL,HOUSEKEEPING_STATE,HOUSEKEEPING_USERID,DMSCUID,DESCRIPTION";
	std::string fieldAndDataTypeList = ":OBJECTID<bigint>,:PARTITIONID<bigint>,:OBJORDER<int>,:PROTOCOLADDRESS<char[256]>,:NAME<char[256]>,:CONTROLMODEL<short>,:HOUSEKEEPING_STATE<short>,:HOUSEKEEPING_USERID<int>,:DMSCUID<bigint>,:DESCRIPTION<char[256]>";
	STREAMHANDLE streamHandle = CPS_ORM_msNewInsertStream(GlobalInfo::g_DBPoolHandle, "DPCPOINT",fieldNameList,fieldAndDataTypeList,20480);
	if(streamHandle==-1)
	{
		qDebug()<<"Insert DPCPOINT failed!";
		CPS_ORM_RollBack(GlobalInfo::g_DBPoolHandle);
		return false;
	}

	foreach(QString object,list)
	{
		QStringList attribute = object.split(QRegExp("[,;\t]"), QString::KeepEmptyParts);
		CPS_ORM_msWriteLongLong(streamHandle,attribute[0].toLongLong());
		CPS_ORM_msWriteLongLong(streamHandle,attribute[1].toLongLong());
		CPS_ORM_msWriteInt(streamHandle,attribute[2].toInt());
		CPS_ORM_msWriteString(streamHandle,attribute[3].toUtf8().data());
		CPS_ORM_msWriteString(streamHandle,attribute[4].toUtf8().data());
		CPS_ORM_msWriteShort(streamHandle,attribute[5].toShort());
		CPS_ORM_msWriteShort(streamHandle,attribute[6].toShort());
		CPS_ORM_msWriteInt(streamHandle,attribute[7].toInt());
		CPS_ORM_msWriteLongLong(streamHandle,attribute[8].toLongLong());
		CPS_ORM_msWriteString(streamHandle,attribute[9].toUtf8().data());
	}

	if (CPS_ORM_msFlush(streamHandle, 1)==1)
	{
		CPS_ORM_msFreeStream(streamHandle);//释放流
		return true;
	}else{
		CPS_ORM_msFreeStream(streamHandle);//释放流
		CPS_ORM_RollBack(GlobalInfo::g_DBPoolHandle);
		return false;
	}
}

bool DBUtil::executeBatchAPC(QStringList list)
{
	std::string fieldNameList = "OBJECTID,PARTITIONID,OBJORDER,PROTOCOLADDRESS,NAME,CONTROLMODEL,HOUSEKEEPING_STATE,HOUSEKEEPING_USERID,APCMODE,RANGEHIGH,RANGELOW,DESCRIPTION";
	std::string fieldAndDataTypeList = ":OBJECTID<bigint>,:PARTITIONID<bigint>,:OBJORDER<int>,:PROTOCOLADDRESS<char[256]>,:NAME<char[256]>,:CONTROLMODEL<short>,:HOUSEKEEPING_STATE<short>,:HOUSEKEEPING_USERID<int>,:APCMODE<short>,:RANGEHIGH<float>,:RANGELOW<float>,:DESCRIPTION<char[256]>";
	STREAMHANDLE streamHandle = CPS_ORM_msNewInsertStream(GlobalInfo::g_DBPoolHandle, "APCPOINT",fieldNameList,fieldAndDataTypeList,20480);
	if(streamHandle==-1)
	{
		qDebug()<<"Insert APCPOINT failed!";
		CPS_ORM_RollBack(GlobalInfo::g_DBPoolHandle);
		return false;
	}

	foreach(QString object,list)
	{
		QStringList attribute = object.split(QRegExp("[,;\t]"), QString::KeepEmptyParts);
		CPS_ORM_msWriteLongLong(streamHandle,attribute[0].toLongLong());
		CPS_ORM_msWriteLongLong(streamHandle,attribute[1].toLongLong());
		CPS_ORM_msWriteInt(streamHandle,attribute[2].toInt());
		CPS_ORM_msWriteString(streamHandle,attribute[3].toUtf8().data());
		CPS_ORM_msWriteString(streamHandle,attribute[4].toUtf8().data());
		CPS_ORM_msWriteShort(streamHandle,attribute[5].toShort());
		CPS_ORM_msWriteShort(streamHandle,attribute[6].toShort());
		CPS_ORM_msWriteInt(streamHandle,attribute[7].toInt());
		CPS_ORM_msWriteShort(streamHandle,attribute[8].toShort());
		CPS_ORM_msWriteFloat(streamHandle,attribute[9].toFloat());
		CPS_ORM_msWriteFloat(streamHandle,attribute[10].toFloat());
		CPS_ORM_msWriteString(streamHandle,attribute[11].toUtf8().data());
	}

	if (CPS_ORM_msFlush(streamHandle, 1)==1)
	{
		CPS_ORM_msFreeStream(streamHandle);//释放流
		return true;
	}else{
		CPS_ORM_msFreeStream(streamHandle);//释放流
		CPS_ORM_RollBack(GlobalInfo::g_DBPoolHandle);
		return false;
	}
}

bool DBUtil::executeBatchWIRE(QStringList list)
{
	std::string fieldNameList = "WIRINGORD,OBJECTID,ATTRIBUTETYPEID,WIREDOBJECTID,HOUSEKEEPING_STATE";
	std::string fieldAndDataTypeList = ":WIRINGORD<int>,:OBJECTID<bigint>,:ATTRIBUTETYPEID<int>,:WIREDOBJECTID<bigint>,:HOUSEKEEPING_STATE<short>";
	STREAMHANDLE streamHandle = CPS_ORM_msNewInsertStream(GlobalInfo::g_DBPoolHandle, "WIRING",fieldNameList,fieldAndDataTypeList,20480);
	if(streamHandle==-1)
	{
		qDebug()<<"Insert WIRING failed!";
		CPS_ORM_RollBack(GlobalInfo::g_DBPoolHandle);
		return false;
	}

	foreach(QString object,list)
	{
		QStringList attribute = object.split(QRegExp("[,;\t]"), QString::KeepEmptyParts);
		CPS_ORM_msWriteInt(streamHandle,attribute[0].toInt());
		CPS_ORM_msWriteLongLong(streamHandle,attribute[1].toLongLong());
		CPS_ORM_msWriteInt(streamHandle,attribute[2].toInt());
		CPS_ORM_msWriteLongLong(streamHandle,attribute[3].toLongLong());
		CPS_ORM_msWriteShort(streamHandle,attribute[4].toShort());
	}

	if (CPS_ORM_msFlush(streamHandle, 1)==1)
	{
		CPS_ORM_msFreeStream(streamHandle);//释放流
		return true;
	}else{
		CPS_ORM_msFreeStream(streamHandle);//释放流
		CPS_ORM_RollBack(GlobalInfo::g_DBPoolHandle);
		return false;
	}
}

bool DBUtil::executeBatchLOG(QStringList list)
{
	std::string fieldNameList = "OBJECTID,OBJECTTYPEID,INCREMENTTYPE";
	std::string fieldAndDataTypeList = ":OBJECTID<bigint>,:OBJECTTYPEID<int>,:INCREMENTTYPE<short>";
	STREAMHANDLE streamHandle = CPS_ORM_msNewInsertStream(GlobalInfo::g_DBPoolHandle, "CPSINCREMENTLOG",fieldNameList,fieldAndDataTypeList,20480);
	if(streamHandle==-1)
	{
		qDebug()<<"Insert CPSINCREMENTLOG failed!";
		CPS_ORM_RollBack(GlobalInfo::g_DBPoolHandle);
		return false;
	}

	foreach(QString object,list)
	{
		QStringList attribute = object.split(QRegExp("[,;\t]"), QString::KeepEmptyParts);
		
		CPS_ORM_msWriteLongLong(streamHandle,attribute[0].toLongLong());
		CPS_ORM_msWriteInt(streamHandle,attribute[1].toInt());
		CPS_ORM_msWriteShort(streamHandle,attribute[2].toShort());
	}

	if (CPS_ORM_msFlush(streamHandle, 1)==1)
	{
		CPS_ORM_msFreeStream(streamHandle);//释放流
		return true;
	}else{
		CPS_ORM_msFreeStream(streamHandle);//释放流
		CPS_ORM_RollBack(GlobalInfo::g_DBPoolHandle);
		return false;
	}
}

bool DBUtil::getFastChildrenList(ObId parentObId,QList<ObId>& list)
{
	RECORDSETHANDLE recordsetHandle = CPS_ORM_RsNewRecordSet();

	try
	{
		if (UpdateConnectDB())
		{
			QString sql = "select t.wiredobjectid from wiring t where t.housekeeping_state<2 and t.attributetypeid=8 and t.objectid=%1";
			sql = sql.arg(parentObId);
			int rows = CPS_ORM_RsLoadData(recordsetHandle, sql.toUtf8().data(), GlobalInfo::g_DBPoolHandle);
			if (rows>0)
			{
				for (int i=0;i<rows;i++)
				{
					ObId sonObId = (ObId)CPS_ORM_RsGetNumberValue(recordsetHandle, i, 0);
					if (sonObId!=0)
					{
						list.append(sonObId);
					}
				}
			}
		}
	}
	catch (Exception& e)
	{
		qDebug()<<"getFastChildrenList FAILURE Exception!";
	}

	CPS_ORM_RsFreeRecordSet(recordsetHandle);
	return true;
}

bool DBUtil::lockIncrement()
{
	QString sql = "LOCK TABLE CPSINCREMENTLOG IN EXCLUSIVE MODE";
	
	if (executeSQL(sql))
	{
		return true;
	}else{
		return false;
	}
}

int DBUtil::registParentIncrement(ObId obId)
{
	int rows = -1;
	RECORDSETHANDLE recordsetHandle = CPS_ORM_RsNewRecordSet();

	try
	{
		if (UpdateConnectDB())
		{
			QString sql = "select * from CPSINCREMENTLOG t where t.objectid=%1 and t.INCREMENTTYPE!=1";

			sql = sql.arg(QString::number(obId));
			rows = CPS_ORM_RsLoadData(recordsetHandle, sql.toUtf8().data(), GlobalInfo::g_DBPoolHandle);
		}
	}
	catch (Exception& e)
	{
		qDebug()<<"registParentIncrement FAILURE Exception!";
	}

	CPS_ORM_RsFreeRecordSet(recordsetHandle);

	return rows;
}
