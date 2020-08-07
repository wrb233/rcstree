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

	//ͨ��������Ϣ��ȡ�ڵ�id������Folder
	static ObId getFolderObIdByDes(StringData des);

	//�ݹ��Һ��ӽڵ�
	static bool getChildrenList(ObId parentObId,QList<ObId>& list,bool isFilterDeleted = false);
	
	//�ݹ��ҵ����е���������ڵ㣬һ�������н�80���
	static bool recursivegetAllChildrenList(ObId parentObId,QList<ObId>& list,bool isFilterDeleted = false);

	//��־���
	static void myDebug(QString content);

	// ʵʱ��read����try catch�쳣ͳһ����
	static bool databaseRead(ObId obId, AType aType, Data* data);

	// ʵʱ��read/req����try catch�쳣ͳһ����
	static bool databaseReadTime(ObId obId, AType aType, Data* data, timespec_t &time);

	// ʵʱ��write����try catch�쳣ͳһ����
	static bool databaseWrite(ObId obId, AType aType, Data* data);

	// ʵʱ��destroy����try catch�쳣ͳһ����
	static bool databaseDestroy(ObId obId);

	// ʵʱ��create����try catch�쳣ͳһ����
	static bool databaseCreate(ObId parent, OType oType,ObId& obId);

	// ʵʱ��copy����try catch�쳣ͳһ����
	static ObId databaseCopy(ObId newParent,  ObId originalObject);

	// ʵʱ���ȡ����id����try catch�쳣ͳһ����
	static bool databaseExtractPartitionId(ObId obId, ObId& partitionId);

	//ʵʱ��matchOtype����try catch�쳣ͳһ����
	static OType databaseMatchOType(const char* name);

	//ʵʱ��matchAtype����try catch�쳣ͳһ����
	static AType databaseMatchAType(const char* name);

	//ʵʱ��extractOType����try catch�쳣ͳһ����
	static OType databaseExtractOType(ObId obId);

	//ʵʱ��matchOName����try catch�쳣ͳһ����
	static QString databaseMatchOName(OType oType);

	//ʵʱ��matchAname����try catch�쳣ͳһ����
	static QString databaseMatchAName(AType aType);

	//ʵʱ��find����try catch�쳣ͳһ����
	static int databaseFind(OType oType, const Condition* conditions, int numberOfConditions,
		ObId* objects = NULL, int maximumNumberOfObjects = 0);

	// ����ĳObId�ݹ����ϲ���ĳOType��ObId
	//static ObId findOTypeByObId(ObId obId, OType toFindOType, OType stopOType=OT_PMSRoot);

	static int findOTypeFromChildList(ObId obId, OType toFindOType, ContainerData &obIds);

	// ����ĳObId�ݹ����²���ĳOType��ObIds
	static int findOTypeByObId(ObId obId, QList<OType> toFindOTypes, ContainerData &obIds);
	
	// ͬ�����������Լ��������ˣ������Ƿ���ObId��
	static ObId ObIdfindOTypeByObIdUP(ObId obId, OType toFindOType, OType stopOType);

	//�����ң�̫�ķ�ʱ����
	static ObId ObIdfindOTypeByObIdDOWN(ObId obId, OType toFindOType, OType stopOType);

	//��timespec��ʽת��Ϊ����ff6�����ʽ��QDatetime
	static QDateTime convertTimespecToQDatetime(timespec_t ts);

	//��map����ת��Ϊjson�ַ���
	static QString convertQMapToJson(QList<QMap<QString,QString> > list);

	//��json�ַ���д���ض�·���ļ���
	static void writeJsonFileByInfo(QString json, QString fileName);

	//дINI�����ļ�
	static void writeIniFileByInfo(QMap<QString,QVariant> map, QString filePath);

	//��qstringlistд���ļ�
	static void writeFileByInfo(QList<QString> list, QString filePath);

	//��ȡָ��·���ļ����ж�ȡ��QStringList��,�Զ��ӵ�2�ж�
	static QStringList readFile(QString filePath);

	//��ȡ��������,������tableview��ʾ����
	static bool readObjectAttributes(QList<ObId> &currentList,ObId currentParentId,int startNum,int endNum,QStandardItemModel* tableModel,MyQProgressDialog* progressDialog=NULL);

	//�������޸����ݣ��޸������ݿ���Ч����
	static void tableSave(QList<QStandardItem*> writeDatas);

	//����combox���Ի�
	static void setComboxCustomData(QComboBox *combox, QString displayValue, AType atype, ObId obId);

	//�ж�obid�Ƿ���������
	static bool isObjectInUserAORSet(ObId obId);

	//����atype�б���װģ���ַ���
	static QString joinTemplate(QList<AType> atypeList,ObId obId,OType otype,int& index,QMap<ObId,int> mvMap,QMap<ObId,int> dpsMap,ChoiceData deviceProperty,QString description);

	//��ȡĳЩ�ڵ�ĸ��ڵ㣬�ø��ڵ��޹ؼ��ֿɶ�λ�����ʹ�ø÷���
	static ObId getParentByOType(OType otype);

	//����obid��ȡname
	static QString getNameByObId(ObId obId);

	static StringData QStringTostdstring(QString strData);
	static QString StringDataToQString(StringData str);
};