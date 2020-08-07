#include "ToolUtil.h"

ToolUtil::ToolUtil():QObject()
{

}

ToolUtil::~ToolUtil()
{

}

ObId ToolUtil::getFolderObIdByDes(StringData des)
{
	ObId rootObId = 0;
	Condition condition(GlobalInfo::AT_Description, EQ, &des);
	int num = ToolUtil::databaseFind(GlobalInfo::OT_Folder, &condition, 1);
	if (num>0)
	{
		ObId *obId = new ObId[num];

		ToolUtil::databaseFind(GlobalInfo::OT_Folder, &condition, 1, obId, num);

		rootObId = obId[0];
		delete[] obId;
	}
	return rootObId;
}

bool ToolUtil::getChildrenList(ObId parentObId,QList<ObId>& list,bool isFilterDeleted)
{
	ContainerData childrenList;
	if (ToolUtil::databaseRead(parentObId, GlobalInfo::AT_ChildrenList, &childrenList))
	{
		int sonNum = childrenList.getNumberOfElements();
		if (sonNum > 0) 
		{
			const ObId *childrenObId = childrenList.getObIds();
			for (int i = 0; i < sonNum; i++) 
			{
				if (isFilterDeleted)
				{
					ChoiceData houseKeeping_StateData;
					if (ToolUtil::databaseRead(parentObId, GlobalInfo::AT_HouseKeeping_State, &houseKeeping_StateData))
					{
						int houseKeeping_State = (int)houseKeeping_StateData;
						if (houseKeeping_State<3)
						{
							list.append(childrenObId[i]);
						}
					}else{
						return false;
					}
				}else{
					list.append(childrenObId[i]);
				}				
			}
		}
	}else{
		return false;
	}
	return true;
}

bool ToolUtil::recursivegetAllChildrenList(ObId parentObId,QList<ObId>& list,bool isFilterDeleted)
{
	ContainerData childrenList;
	if (ToolUtil::databaseRead(parentObId, GlobalInfo::AT_ChildrenList, &childrenList))
	{
		int sonNum = childrenList.getNumberOfElements();
		if (sonNum > 0) 
		{
			const ObId *childrenObId = childrenList.getObIds();
			for (int i = 0; i < sonNum; i++) 
			{
				if (isFilterDeleted)
				{
					ChoiceData houseKeeping_StateData;
					if (ToolUtil::databaseRead(parentObId, GlobalInfo::AT_HouseKeeping_State, &houseKeeping_StateData))
					{
						int houseKeeping_State = (int)houseKeeping_StateData;
						if (houseKeeping_State<3)
						{
							list.append(childrenObId[i]);
						}
					}else{
						return false;
					}
				}else{
					recursivegetAllChildrenList(childrenObId[i],list);
					list.append(childrenObId[i]);
				}				
			}
		}
	}else{
		return false;
	}
	return true;
}

void ToolUtil::myDebug(QString content)
{
	//if ("on"==ToolUtil::getHisRecordConf("/Debug/config"))
	//{
		qDebug()<<content<< endl; ;
	//}
}

bool ToolUtil::databaseRead(ObId obId, AType aType, Data* data)
{
	try
	{
		GlobalInfo::g_Database->read(obId, aType, data);
	}
	catch (Exception& e)
	{
		ToolUtil::myDebug(QString::number(obId)+": DATABASE READ AT "+QString::number(aType)+" ERROR" + e.getStackTrace().c_str());
		return false;
	}
	return true;
}

bool ToolUtil::databaseReadTime(ObId obId, AType aType, Data* data, timespec_t &time)
{
	try
	{
		Request req;
		req.set(obId,aType,data,NULL,0,NORMAL_WRITE,&time);
		GlobalInfo::g_Database->read(&req);
	}
	catch (Exception& e)
	{
		ToolUtil::myDebug(QString::number(obId)+": DATABASE READ Time ERROR");
		return false;
	}
	return true;
}

bool ToolUtil::databaseWrite(ObId obId, AType aType, Data* data)
{
	try
	{
		GlobalInfo::g_Database->write(obId, aType, data);
	}
	catch (Exception& e)
	{
		ToolUtil::myDebug(QString::number(obId)+": DATABASE WriteAT "+QString::number(aType)+" ERROR" + e.getStackTrace().c_str());
		return false;
	}
	return true;
}

bool ToolUtil::databaseDestroy(ObId obId)
{
	try
	{
		GlobalInfo::g_Database->destroy(obId);
	}
	catch (Exception& e)
	{
		ToolUtil::myDebug(QString::number(obId)+": DATABASE Delete  ERROR" + e.getStackTrace().c_str());
		return false;
	}
	return true;
}

bool ToolUtil::databaseCreate(ObId parent, OType oType,ObId& obId)
{
	obId = 0;
	try
	{
		obId = GlobalInfo::g_Database->create(parent,oType);
	}
	catch (Exception& e)
	{
		ToolUtil::myDebug(QString::number(parent)+": DATABASE Create  ERROR" + e.getStackTrace().c_str());
		return false;
	}
	if(obId==0)
	{
		return false;
	}
	return true;
}

ObId ToolUtil::databaseCopy(ObId newParent,  ObId originalObject)
{
	ObId obId = 0;
	try
	{
		obId = GlobalInfo::g_Database->copy(newParent,originalObject);
	}
	catch (Exception& e)
	{
		ToolUtil::myDebug(QString::number(originalObject)+": DATABASE Copy  ERROR" + e.getStackTrace().c_str());
	}

	return obId;
}

bool ToolUtil::databaseExtractPartitionId(ObId obId, ObId& partitionId)
{
	partitionId = 0;
	try
	{
		partitionId = GlobalInfo::g_Database->extractPartitionId(obId);
	}
	catch (Exception& e)
	{
		ToolUtil::myDebug(QString::number(obId)+": DATABASE ExtractPartitionId  ERROR" + e.getStackTrace().c_str());
		return false;
	}
	if(partitionId==0)
	{
		return false;
	}
	return true;
}

OType ToolUtil::databaseMatchOType(const char* name)
{
	OType oType = 0;
	try
	{
		oType = GlobalInfo::g_Database->matchOType(name);
	}
	catch (Exception& e)
	{
		ToolUtil::myDebug(QString::fromUtf8(name)+": DATABASE MATCH OTYPE OT ERROR");
	}
	return oType;
}

AType ToolUtil::databaseMatchAType(const char* name)
{
	AType aType = 0;
	try
	{
		aType = GlobalInfo::g_Database->matchAType(name);
	}
	catch (Exception& e)
	{
		ToolUtil::myDebug(QString::fromUtf8(name)+": DATABASE MATCH ATYPE OT ERROR");
	}
	return aType;
}

OType ToolUtil::databaseExtractOType(ObId obId)
{
	OType oType = 0;
	try
	{
		oType = GlobalInfo::g_Database->extractOType(obId);
	}
	catch (Exception& e)
	{
		ToolUtil::myDebug(QString::number(obId)+": DATABASE Extract OT ERROR");
	}
	return oType;
}

QString ToolUtil::databaseMatchOName(OType oType)
{
	QString oName = "";
	try
	{
		const char* name = GlobalInfo::g_Database->matchOName(oType);
		oName = QString::fromUtf8(name);
	}
	catch (Exception& e)
	{
		ToolUtil::myDebug(QString::number(oType)+": DATABASE MatchOName ERROR");
	}
	return oName;
}

QString ToolUtil::databaseMatchAName(AType aType)
{
	QString aName = "";
	try
	{
		const char* name = GlobalInfo::g_Database->matchAName(aType);
		aName = QString::fromUtf8(name);
	}
	catch (Exception& e)
	{
		ToolUtil::myDebug(QString::number(aType)+": DATABASE MatchAName ERROR");
	}
	return aName;
}

int ToolUtil::databaseFind(OType oType, const Condition* conditions, int numberOfConditions,
	ObId* objects, int maximumNumberOfObjects)
{
	int num = 0;
	try
	{
		num = GlobalInfo::g_Database->find(oType, conditions, numberOfConditions, objects, maximumNumberOfObjects);
	}
	catch (Exception& e)
	{
		ToolUtil::myDebug(QString::number(oType)+": DATABASE Find OT ERROR");
	}
	return num;
}

//ObId ToolUtil::findOTypeByObId(ObId obId, OType toFindOType, OType stopOType)
//{
//	ObId toFindObId = 0;
//	LinkData parentLinkData = 0;
//	AType AT_ParentLink = ToolUtil::databaseMatchAType("ParentLink");
//	ToolUtil::databaseRead(obId, AT_ParentLink, &parentLinkData);
//	if (parentLinkData!=0)
//	{
//		OType oType = ToolUtil::databaseExtractOType((ObId)parentLinkData);
//		if (oType==toFindOType)
//		{
//			toFindObId = (ObId)parentLinkData;
//		}else if (oType!=stopOType)
//		{
//			ObId tempObId = ToolUtil::findOTypeByObId((ObId)parentLinkData, toFindOType, stopOType);
//			if (0!=tempObId)
//			{
//				toFindObId = tempObId;
//			}
//		}
//	}
//	return toFindObId;
//}

int ToolUtil::findOTypeFromChildList(ObId obId, OType toFindOType, ContainerData &obIds)
{
	ContainerData childrenList;
	AType AT_ChildrenList = ToolUtil::databaseMatchAType("ChildrenList");
	ToolUtil::databaseRead(obId, AT_ChildrenList, &childrenList);
	int sonNum = childrenList.getNumberOfElements();
	if (sonNum > 0) {
		const ObId *childrenObId = childrenList.getObIds();
		for (int i = 0; i < sonNum; i++) {
			OType sonOType = ToolUtil::databaseExtractOType(childrenObId[i]);
			if (sonOType == toFindOType) {
				obIds.add(childrenObId[i]);
			}
		}
	}
	return obIds.getNumberOfElements();
}

int ToolUtil::findOTypeByObId(ObId obId, QList<OType> toFindOTypes, ContainerData &obIds)
{
	ContainerData find_obids;
	find_obids.add(obId);
	foreach(OType otype, toFindOTypes) {
		int findNum = find_obids.getNumberOfElements();
		if (findNum <= 0)  continue;
		const ObId *obid = find_obids.getObIds();
		ContainerData child_obids;
		for (int i = 0; i < findNum; i++) {
			findOTypeFromChildList(obid[i], otype, child_obids);
		}
		find_obids = child_obids;
	}
	obIds = find_obids;
	return obIds.getNumberOfElements();
}


//从上面找到指定的OType就停下来
ObId ToolUtil::ObIdfindOTypeByObIdUP(ObId obId, OType toFindOType, OType stopOType)
{
	ObId toFindObId = 0;
	LinkData parentLinkData = 0;
	ToolUtil::databaseRead(obId, GlobalInfo::AT_ParentLink, &parentLinkData);
	if (parentLinkData!=0)
	{
		OType oType = ToolUtil::databaseExtractOType((ObId)parentLinkData);
		if (oType==toFindOType)
		{
			toFindObId = (ObId)parentLinkData;
		}else if (oType!=stopOType)
		{
			ObId tempObId = ToolUtil::ObIdfindOTypeByObIdUP((ObId)parentLinkData, toFindOType, stopOType);
			if (0!=tempObId)
			{
				toFindObId = tempObId;
			}
		}
	}
	return toFindObId;
}
//从下面找到指定的OType就停下来
//目前还有问题，待完善
ObId ToolUtil::ObIdfindOTypeByObIdDOWN(ObId obId, OType toFindOType, OType stopOType)
{
	ObId toFindObId = 0;
	ContainerData childrenLinkData;
	
	ToolUtil::databaseRead(obId, GlobalInfo::AT_ChildrenList, &childrenLinkData);

	int numberOfChildren = childrenLinkData.getNumberOfElements();
	const ObId* ChildrenObid = childrenLinkData.getObIds();

	for(int k=0;k<numberOfChildren;k++)
	{

		OType oType = ToolUtil::databaseExtractOType(ChildrenObid[k]);
		if (oType==toFindOType)
		{
			toFindObId = ChildrenObid[k];
		}else if (oType!=stopOType)
		{
			ObId tempObId = ToolUtil::ObIdfindOTypeByObIdDOWN(ChildrenObid[k], toFindOType, stopOType);
			if (0!=tempObId)
			{
				toFindObId = tempObId;
			}
		}

	}
	return toFindObId;
}

QDateTime ToolUtil::convertTimespecToQDatetime(timespec_t ts)
{
	/*time_t t = ts.tv_sec;
	long tn = ts.tv_nsec;
	QDateTime timeTemp = QDateTime::fromTime_t(t);
	QString timeS = timeTemp.toString("yyyy-MM-dd hh:mm:ss");
	QString timeM = QString::number(tn/1000000);
	QString timeString = timeS + "." + timeM;
	QDateTime time = QDateTime::fromString(timeString, "yyyy-MM-dd hh:mm:ss.zzz");
	qDebug()<<time;
	qDebug()<<time.toString("yyyy-MM-dd hh:mm:ss.zzz");
	return time;*/
	int year, month, day, hour, minute, second, ms;
	OMSTime omT = OMSTime( ts );
	omT.getDateTimeFields( &year, &month, &day, &hour, &minute, &second, &ms );

	QTime q_tm = QTime( hour, minute, second, ms/1000	);
	QDate q_dt = QDate( year, month, day );
	QDateTime datetime = QDateTime( q_dt, q_tm );
	QString strtime = datetime.toString("yyyy-MM-dd hh:mm:ss.zzz");
	qDebug()<<strtime;

	return datetime;

}

QString ToolUtil::convertQMapToJson(QList<QMap<QString,QString> > list)
{
	QString json = "";

	QString jsonArrayStart = "[";
	QString jsonArrayEnd = "]";	
	QString jsonObjectStart = "{";
	QString jsonObjectEnd = "}";
	QString jsonObject = "\"%1\":\"%2\"";

	for (int i=0;i<list.size();i++)
	{
		QMap<QString,QString>::iterator it; 
		QString jsonTemp = "";
		for ( it = list[i].begin(); it != list[i].end(); ++it )
		{
			jsonTemp = jsonTemp.append(jsonObject.arg(it.key()).arg(it.value())).append(",");
		}
		jsonTemp = jsonTemp.left(jsonTemp.length()-1);
		json = json.append(jsonObjectStart).append(jsonTemp).append(jsonObjectEnd).append(",");
	}
	json = json.left(json.length()-1);	
	json = jsonArrayStart.append(json).append(jsonArrayEnd);
	
	return json;
}

void ToolUtil::writeJsonFileByInfo(QString json, QString fileName)
{
	ToolUtil::myDebug("MethodName:writeJsonFileByInfo start");
	char* cpsenv = getenv("CPS_ENV");
	QString sqlFileFolderPath = QDir::fromNativeSeparators(QString::fromUtf8(cpsenv)) + "/data/share/monitor/json/"; 
	QDir dir(sqlFileFolderPath);
	if(!dir.exists())
	{
		dir.mkpath(sqlFileFolderPath);
	}
	ToolUtil::myDebug(sqlFileFolderPath);

	fileName = fileName.append(QDateTime::currentDateTime().toString("_yyyyMMddhhmmsszzz")).append(".json");
	QFile f(sqlFileFolderPath+fileName);  
	if(!f.open(QIODevice::WriteOnly | QIODevice::Text))  
	{  
		ToolUtil::myDebug("Open failed");
		return;
	}  

	QTextStream datOutput(&f); 
	datOutput.setCodec("UTF-8");
	datOutput << json<< endl; 

	datOutput.flush();
	f.flush();
	f.close();
	ToolUtil::myDebug("MethodName:writeJsonFileByInfo end");
}

void ToolUtil::writeCSVFileByInfo(QList<QString> list, QString filePath)
{
	QFile f(filePath);  
	if(!f.open(QIODevice::WriteOnly | QIODevice::Text))  
	{  
		return;
	}  

	QTextStream datOutput(&f); 
	datOutput.setCodec("UTF-8");

	foreach(QString info,list)
	{
		datOutput << info<< endl; 
	}

	datOutput.flush();
	f.flush();
	f.close();
}

QStringList ToolUtil::readFile(QString filePath)
{
	QStringList list;
	if (!filePath.isEmpty())
	{
		QFile file(filePath); 
		if(file.open(QIODevice::ReadOnly | QIODevice::Text)) 
		{
			QTextStream in(&file);  
			in.setCodec("UTF-8");
			QString line = in.readLine();  
			while (!line.isNull()) 
			{
				qDebug()<<line;
				line = in.readLine();
				if (!line.isEmpty())
				{
					list.append(line);
				}
			}
			in.flush();
			file.flush();
			file.close();	
		}	
	}
	return list;
}


bool ToolUtil::readObjectAttributes(QList<ObId> &currentList,ObId currentParentId,int startNum,int endNum,QStandardItemModel* tableModel,MyQProgressDialog* progressDialog)
{
	if (startNum==endNum)
	{
		return true;
	}

	Request* requests = NULL;
	try
	{
		OType otype = GlobalInfo::g_Database->extractOType(currentList.at(0));
		const ObjectType* objectType = GlobalInfo::g_Database->getObjectType(otype);
		int numOfObjectAttributes = objectType->getNumberOfObjectAttributes();
		const ObjectAttribute* objectAttributes = objectType->getObjectAttributes();
		int numberOfRequests = 0;
		requests = new Request[(endNum-startNum)*numOfObjectAttributes];
		for (int i=startNum;i<endNum;i++)
		{
			for (int j = 0; j < numOfObjectAttributes; j++)
			{
				const ObjectAttribute* objectAttribute = objectAttributes +j;
				QString attrName = objectAttribute->getName();
				if (!GlobalInfo::displayAttrList.contains(attrName))
				{
					continue;
				}
				ObId obId = currentList.at(i);
				Data* data = objectAttribute->createEditData(GlobalInfo::g_Database);
				AType atype = objectAttribute->getAType();
				requests[numberOfRequests].set(obId, atype, data);

				if (i==0)
				{
					const char*trans = translateAName(atype);
					QString columName = QString::fromUtf8(trans);
					if (columName.isEmpty())
					{
						columName = attrName;
					}
					tableModel->setHorizontalHeaderItem(numberOfRequests, new QStandardItem(columName));
				}
				numberOfRequests++;
			}
		}

		ORMDatabase* ormDatabase =  dynamic_cast<ORMDatabase*>(GlobalInfo::g_Database);
		ormDatabase->reads(requests,numberOfRequests,endNum-startNum);
		int objNum = endNum-startNum;
		int numberOfDisplay = numberOfRequests/objNum;
		for (int i=0;i<objNum;i++)
		{
			for (int k = 0; k < numberOfDisplay; k++)
			{
				Data* data =NULL;
				data = requests[i*numberOfDisplay+k].getData();
				ObId obId = requests[i*numberOfDisplay+k].getObId();
				AType at = requests[i*numberOfDisplay+k].getAType();
				DBDataType db = data->getDBDataType();
				QStandardItem* item = NULL;
				switch (db)
				{
				case DB_STRING_DATA:
					{
						StringData* strdata = (StringData*) data;
						std::string stdData = (std::string)(*strdata);
						item= new QStandardItem(QString::fromUtf8(stdData.c_str()));					
						break;
					}
				case DB_COMPLETE_INTEGER_DATA:
					{
						IntegerData* id = (IntegerData*)data;
						int idInt = (int)(*id);
						item= new QStandardItem(QString::number(idInt));
						break;
					}
				case DB_CHOICE_LINK_DATA:
				case DB_COMPLETE_LINK_DATA:
					{
						LinkData* ld = (LinkData*)data;
						ObId obIdLink = (ObId)(*ld);
						StringData sd = "";
						ToolUtil::databaseRead(obIdLink,GlobalInfo::AT_Name,&sd);
						QString name = QString::fromUtf8(((std::string)sd).c_str());
						item= new QStandardItem(name);
						item->setData(obIdLink,Qt::UserRole+2);
						break;
					}
				case DB_COMPLETE_FLOAT_DATA:
					{
						FloatData* fd = (FloatData*)data;
						float fdFloat = (float)(*fd);
						item= new QStandardItem(QString::number(fdFloat,'f',6));
						break;
					}
				case DB_CHOICE_DATA:
					{
						ChoiceData* cd = (ChoiceData*)data;
						int cdInt = (int)(*cd);
						const OMString* nameOMS = cd->getStrings();
						QString name = QString::fromUtf8((nameOMS+cdInt)->c_str());					
						item= new QStandardItem(name);
						break;
					}
				case DB_COMPLETE_CONTAINER_DATA:
					{
						ContainerData* cd = (ContainerData*)data;
						int num = cd->getNumberOfElements();
						const ObId* obIds = cd->getObIds();
						QStringList container;
						QStringList obIdList;
						for (int i=0;i<num;i++)
						{
							StringData sd = "";
							ToolUtil::databaseRead(obIds[i],GlobalInfo::AT_Name,&sd);
							QString name = QString::fromUtf8(((std::string)sd).c_str());
							container.append(name);
							obIdList.append(QString::number(obIds[i]));
						}
						item= new QStandardItem(container.join(","));
						item->setData(obIdList,Qt::UserRole+2);
						break;
					}
				case DB_COMPLETE_LONGLONG_DATA:
					{
						LongLongData* ld = (LongLongData*)data;
						ObId obIdLink = (ObId)(*ld);
						StringData sd = "";
						ToolUtil::databaseRead(obIdLink,GlobalInfo::AT_Name,&sd);
						QString name = QString::fromUtf8(((std::string)sd).c_str());
						item= new QStandardItem(name);
						item->setData(obIdLink,Qt::UserRole+2);
						break;
					}
				}

				if (item!=NULL)
				{
					tableModel->setItem(startNum+i,k, item);
					tableModel->setData(item->index(),obId,Qt::UserRole);
					tableModel->setData(item->index(),at,Qt::UserRole+1);
					tableModel->setData(item->index(),currentParentId,Qt::UserRole+3);
					tableModel->setData(item->index(),otype,Qt::UserRole+4);
				}
				if (data!=NULL)
				{
					delete data;
					data=NULL;
				}
			}

			if (progressDialog!=NULL)
			{
				progressDialog->setValue(i+1);
				progressDialog->setLabelText(tr("Reading..."));
			}	
		}
		delete[] requests;
		requests = NULL;
	}
	catch (Exception& e)
	{
		qDebug()<<QString::fromUtf8(e.getDescription().c_str());

		if (requests!=NULL)
		{
			delete[] requests;
			requests = NULL;
		}
		tableModel->clear();
		return false;
	}
	return true;
}

void ToolUtil::tableSave(QList<QStandardItem*> writeDatas)
{
	ORMDatabase* database = dynamic_cast<ORMDatabase*>(GlobalInfo::g_Database);	
	if (database==0)
	{
		QMessageBox::information( NULL, tr("error"), tr( "SAC is disconnect" ));
		return;
	}
	DBPOOLHANDLE dbhandle = database->getORMInterface()->getDBPoolHandle();
	CPS_ORM_UpdatePool(dbhandle);
	if(CPS_ORM_GetDBPoolState(dbhandle)!=DBS_ACTIVE)
	{	
		QMessageBox::information( NULL, tr("error"), tr( "SAC is disconnect" ));
		return;
	}

	foreach(QStandardItem* item,writeDatas)
	{
		qDebug()<<item->text();
		ObId obId =item->data(Qt::UserRole).toULongLong();
		AType atype = item->data(Qt::UserRole+1).toInt();
		OType otype = item->data(Qt::UserRole+4).toUInt();
		DataType db = GlobalInfo::g_Database->getObjectType(otype)->getObjectAttribute(atype)->getDataType();
		QString text = item->data(Qt::DisplayRole).toString();	

		switch(db)
		{
		case STRING_DATA:
			{
				StringData writeName = text.toUtf8().data();
				ToolUtil::databaseWrite(obId,atype,&writeName);
				break;
			}
		case LONGLONG_DATA:
			{
				LongLongData longlongData = item->data(Qt::UserRole+2).toULongLong();
				ToolUtil::databaseWrite(obId,atype,&longlongData);
				break;
			}
		case CONTAINER_DATA:
			{
				QStringList obIdContainers = item->data(Qt::UserRole+2).toStringList();
				ContainerData container;
				foreach(QString obIdContainer,obIdContainers)
				{
					container.add(obIdContainer.toULongLong());
				}
				ToolUtil::databaseWrite(obId,atype,&container);	
				break;
			}
		case MULTIPLE_CHOICE_DATA:
		case BOOLEAN_DATA:
			{
				IntegerData choiceData = item->data(Qt::UserRole+2).toInt();
				ToolUtil::databaseWrite(obId,atype,&choiceData);	
				break;
			}
		case LINK_DATA:
			{
				LinkData link = item->data(Qt::UserRole+2).toULongLong();
				ToolUtil::databaseWrite(obId,atype,&link);	

				if (link!=0)
				{
					if (atype==GlobalInfo::AT_DPCPointLink)
					{
						ObId dpcId = (ObId)link;
						LinkData dpsLink = (LinkData)obId;
						ToolUtil::databaseWrite(dpcId,GlobalInfo::AT_DPSPointLink,&dpsLink);

					}else if (atype==GlobalInfo::AT_DPSPointLink){
						ObId dpsId = (ObId)link;
						LinkData dpcLink = (LinkData)obId;
						ToolUtil::databaseWrite(dpsId,GlobalInfo::AT_DPCPointLink,&dpcLink);

					}else if (atype==GlobalInfo::AT_MVPointLink){
						ObId mvId = (ObId)link;
						LinkData apcLink = (LinkData)obId;
						ToolUtil::databaseWrite(mvId,GlobalInfo::AT_APCPointLink,&apcLink);

					}else if (atype==GlobalInfo::AT_APCPointLink){
						ObId apcId = (ObId)link;
						LinkData mvLink = (LinkData)obId;
						ToolUtil::databaseWrite(apcId,GlobalInfo::AT_MVPointLink,&mvLink);
					}	
				}			
				break;
			}
		case INTEGER_DATA:
		case SHORT_DATA:
			{
				IntegerData intdate = text.toInt();
				ToolUtil::databaseWrite(obId,atype,&intdate);	
				break;
			}
		case FLOAT_DATA:
			{
				FloatData fdate = text.toFloat();
				ToolUtil::databaseWrite(obId,atype,&fdate);	
				break;
			}
		default:
			{

				break;
			}
		}



		QBrush brush(QColor(0,0,0));
		item->setForeground(brush);
	}
}

void ToolUtil::setComboxCustomData(QComboBox *combox, QString displayValue, AType atype, ObId obId)
{
	QMap<ObId,QString> map;
	QList<QString> optionList;

	if (atype==GlobalInfo::AT_AlarmStateContainerLink)
	{
		map = GlobalInfo::allAlarmStateContainerLinkCombox;
	}else if (atype==GlobalInfo::AT_StateContainerLink){
		map = GlobalInfo::allStateContainerLinkCombox;
	}else if (atype==GlobalInfo::AT_GatewaySpecificationLink){
		map = GlobalInfo::allGatewaySpecificationLinkCombox;
	}else{
		ChoiceData choiceData;
		if (ToolUtil::databaseRead(obId,atype,&choiceData))
		{
			int num = choiceData.getNumberOfChoices();
			for (int i=0;i<num;i++)
			{
				const OMString* nameOMS = choiceData.getStrings();
				QString name = QString::fromUtf8((nameOMS+i)->c_str());
				optionList.append(name);
			}
		}
	}

	QMap<ObId,QString>::const_iterator i;
	int index = 0;
	for (i = map.constBegin(); i != map.constEnd(); ++i) 
	{
		combox->addItem(i.value() );
		combox->setItemData(index,i.key(),Qt::UserRole);
		index++;
	}

	foreach (QString option,optionList)
	{
		combox->addItem(option);
	}

	combox->setCurrentIndex(combox->findText(displayValue)); 
}

bool ToolUtil::isObjectInUserAORSet(ObId obId)
{
	ObId loginUser = GlobalInfo::g_User->getSystemUser();
	StringData desData = "";
	databaseRead(loginUser,GlobalInfo::AT_Description,&desData);
	if (!(std::string(desData)=="SuperUser"))
	{
		if (!GlobalInfo::g_User->ds6k_isObjectInUserAORSet(obId))
		{
			return false;
		}
	}
	return true;
}

QString ToolUtil::joinTemplate(QList<AType> atypeList,ObId obId,OType otype,int& index,QMap<ObId,int> mvMap,QMap<ObId,int> dpsMap,ChoiceData deviceProperty)
{
	QString deviceProperty_s = "";
	if (GlobalInfo::allDeviceProperty_out.contains((int)deviceProperty))
	{
		deviceProperty_s = GlobalInfo::allDeviceProperty_out.value((int)deviceProperty);
	}
	QString data = "";
	data.append(QString::number(++index)).append(";").append("").append(";").append(deviceProperty_s).append(";").append("");

	foreach(AType atype,atypeList)
	{
		try
		{
			DataType db = GlobalInfo::g_Database->getObjectType(otype)->getObjectAttribute(atype)->getDataType();

			switch (db)
			{
			case STRING_DATA:
				{
					StringData strdata = "";
					ToolUtil::databaseRead(obId,atype,&strdata);
					std::string stdData = (std::string)strdata;	
					QString text = QString::fromUtf8(stdData.c_str());
					data.append(";").append(text);
					break;
				}
			case INTEGER_DATA:
			case SHORT_DATA:
				{
					IntegerData id = 0;
					ToolUtil::databaseRead(obId,atype,&id);
					int idInt = (int)id;
					data.append(";").append(QString::number(idInt));
					break;
				}
			case MULTIPLE_CHOICE_DATA:
			case BOOLEAN_DATA:
				{
					ChoiceData cd;
					ToolUtil::databaseRead(obId,atype,&cd);
					int cdInt = (int)cd;
					data.append(";");
					if (atype==GlobalInfo::AT_ControlModel)
					{
						if (GlobalInfo::allControlMode_out.contains(cdInt))
						{
							data.append(GlobalInfo::allControlMode_out.value(cdInt));
						}
					}else if (atype==GlobalInfo::AT_APCMode)
					{
						if (GlobalInfo::allAPCMode_out.contains(cdInt))
						{
							data.append(GlobalInfo::allAPCMode_out.value(cdInt));
						}
					}else if (atype==GlobalInfo::AT_IsReversed)
					{
						if (cdInt==0)
						{
							data.append("No");
						}else{
							data.append("Yes");
						}
					}
					break;
				}
			case LINK_DATA:
				{
					LinkData ld = 0;
					ToolUtil::databaseRead(obId,atype,&ld);
					ObId obIdLink = (ObId)ld;
					data.append(";");
					if (atype==GlobalInfo::AT_GatewaySpecificationLink)
					{
						if (GlobalInfo::allGatewaySpecificationLink_out.contains(obIdLink))
						{
							data.append(GlobalInfo::allGatewaySpecificationLink_out.value(obIdLink));
						}
					}else if (atype==GlobalInfo::AT_MeasurementTypeLink)
					{
						if (GlobalInfo::allMeasurementTypeLink_out.contains(obIdLink))
						{
							data.append(GlobalInfo::allMeasurementTypeLink_out.value(obIdLink));
						} 
					}else if (atype==GlobalInfo::AT_UnitsLink)
					{
						if (GlobalInfo::allUnitsLink_out.contains(obIdLink))
						{
							data.append(GlobalInfo::allUnitsLink_out.value(obIdLink));
						}
					}else if (atype==GlobalInfo::AT_DPSPointLink)
					{
						if (dpsMap.contains(obIdLink))
						{
							data.append(QString::number(dpsMap.value(obIdLink)));
						}
					}else if (atype==GlobalInfo::AT_MVPointLink)
					{
						if (mvMap.contains(obIdLink))
						{
							data.append(QString::number(mvMap.value(obIdLink)));
						}
					}
					break;
				}
			case FLOAT_DATA:
				{
					FloatData fd = 0;
					ToolUtil::databaseRead(obId,atype,&fd);
					float fdFloat = (float)fd;
					data.append(";").append(QString::number(fdFloat));
					break;
				}
			}
		}
		catch (Exception& e)
		{
			qDebug()<<QString::fromUtf8(e.getDescription().c_str());
		}
	}

	return data;
}

ObId ToolUtil::getParentByOType(OType otype)
{
	ObId obId = 0;
	try
	{
		const IntegerData condVal = 2;
		const Condition cond(GlobalInfo::AT_HouseKeeping_State, LE, &condVal);
		ObId defaultID = GlobalInfo::g_Database->getDefaultObject(otype);
		ObId ObIds[2];
		int nSum = GlobalInfo::g_Database->find(otype, &cond, 1, ObIds, 2);
		for (int i = 0; i < 2; i++)
		{
			if (ObIds[i] == defaultID)
			{
				continue;
			}
			LinkData parentId = 0;
			GlobalInfo::g_Database->read(ObIds[i], GlobalInfo::AT_ParentLink, &parentId);
			obId = (ObId)parentId;
		}
	}
	catch (Exception& e)
	{
		ToolUtil::myDebug("DATABASE getParentByOType  ERROR" + QString::fromUtf8(e.getDescription().c_str()));
	}

	return obId;
}

QString ToolUtil::getNameByObId(ObId obId)
{
	StringData nameData = "";
	ToolUtil::databaseRead(obId,GlobalInfo::AT_Name,&nameData);
	return QString::fromUtf8(((std::string)nameData).c_str());
}