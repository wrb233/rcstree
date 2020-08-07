#pragma once

#include "common.h"
#include "GlobalInfo.h"
#include "MyQProgressDialog.h"

class ToolUtil:public QObject
{
	Q_OBJECT
public:
	ToolUtil();
	~ToolUtil();

	//通过描述信息获取节点id，类型Folder
	static ObId getFolderObIdByDes(StringData des);

	//递归找孩子节点
	static bool getChildrenList(ObId parentObId,QList<ObId>& list,bool isFilterDeleted = false);
	
	//递归找到所有的子子孙孙节点，一个分区有近80万点
	static bool recursivegetAllChildrenList(ObId parentObId,QList<ObId>& list,bool isFilterDeleted = false);

	//日志输出
	static void myDebug(QString content);

	// 实时库read，加try catch异常统一捕获
	static bool databaseRead(ObId obId, AType aType, Data* data);

	// 实时库read/req，加try catch异常统一捕获
	static bool databaseReadTime(ObId obId, AType aType, Data* data, timespec_t &time);

	// 实时库write，加try catch异常统一捕获
	static bool databaseWrite(ObId obId, AType aType, Data* data);

	// 实时库destroy，加try catch异常统一捕获
	static bool databaseDestroy(ObId obId);

	// 实时库create，加try catch异常统一捕获
	static bool databaseCreate(ObId parent, OType oType,ObId& obId);

	// 实时库copy，加try catch异常统一捕获
	static ObId databaseCopy(ObId newParent,  ObId originalObject);

	// 实时库获取分区id，加try catch异常统一捕获
	static bool databaseExtractPartitionId(ObId obId, ObId& partitionId);

	//实时库matchOtype，加try catch异常统一捕获
	static OType databaseMatchOType(const char* name);

	//实时库matchAtype，加try catch异常统一捕获
	static AType databaseMatchAType(const char* name);

	//实时库extractOType，加try catch异常统一捕获
	static OType databaseExtractOType(ObId obId);

	//实时库matchOName，加try catch异常统一捕获
	static QString databaseMatchOName(OType oType);

	//实时库matchAname，加try catch异常统一捕获
	static QString databaseMatchAName(AType aType);

	//实时库find，加try catch异常统一捕获
	static int databaseFind(OType oType, const Condition* conditions, int numberOfConditions,
		ObId* objects = NULL, int maximumNumberOfObjects = 0);

	// 依据某ObId递归向上查找某OType的ObId
	//static ObId findOTypeByObId(ObId obId, OType toFindOType, OType stopOType=OT_PMSRoot);

	static int findOTypeFromChildList(ObId obId, OType toFindOType, ContainerData &obIds);

	// 依据某ObId递归向下查找某OType的ObIds
	static int findOTypeByObId(ObId obId, QList<OType> toFindOTypes, ContainerData &obIds);
	
	// 同名函数，我自己改名字了，反正是返回ObId的
	static ObId ObIdfindOTypeByObIdUP(ObId obId, OType toFindOType, OType stopOType);

	//向下找，太耗费时间了
	static ObId ObIdfindOTypeByObIdDOWN(ObId obId, OType toFindOType, OType stopOType);

	//将timespec格式转换为带有ff6毫秒格式的QDatetime
	static QDateTime convertTimespecToQDatetime(timespec_t ts);

	//将map对象转换为json字符串
	static QString convertQMapToJson(QList<QMap<QString,QString> > list);

	//将json字符串写入特定路径文件夹
	static void writeJsonFileByInfo(QString json, QString fileName);

	//写INI配置文件
	static void writeIniFileByInfo(QMap<QString,QVariant> map, QString filePath);

	//将qstringlist写入文件
	static void writeFileByInfo(QList<QString> list, QString filePath);

	//读取指定路径文件逐行读取到QStringList中,自动从第2行读
	static QStringList readFile(QString filePath);

	//读取对象属性,并构造tableview显示界面
	static bool readObjectAttributes(QList<ObId> &currentList,ObId currentParentId,int startNum,int endNum,QStandardItemModel* tableModel,MyQProgressDialog* progressDialog=NULL);

	//保存表格修改数据，修改与数据库生效分离
	static void tableSave(QList<QStandardItem*> writeDatas);

	//设置combox个性化
	static void setComboxCustomData(QComboBox *combox, QString displayValue, AType atype, ObId obId);

	//判断obid是否在责任区
	static bool isObjectInUserAORSet(ObId obId);

	//根据atype列表组装模板字符串
	static QString joinTemplate(QList<AType> atypeList,ObId obId,OType otype,int& index,QMap<ObId,int> mvMap,QMap<ObId,int> dpsMap,ChoiceData deviceProperty,QString description);

	//获取某些节点的父节点，该父节点无关键字可定位的情况使用该方法
	static ObId getParentByOType(OType otype);

	//根据obid获取name
	static QString getNameByObId(ObId obId);

	static StringData QStringTostdstring(QString strData);
	static QString StringDataToQString(StringData str);
};