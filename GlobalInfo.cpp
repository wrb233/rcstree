#include "GlobalInfo.h"
const QString PERIOD_unsave = "unsave";	///<不存储
const QString PERIOD_saveAll = "saveAllChange";	///<变化存储
const QString PERIOD_1Min = "1Min";	///<1分钟 
const QString PERIOD_5Min = "5Min";	///<5分钟
const QString PERIOD_15Min = "15Min";	///<15分钟
const QString PERIOD_60Min = "60Min";	///<60分钟
const ObId PERIOD_LINK_unsave = 0;	//不存储
const ObId PERIOD_LINK_saveAll =	 309237645324L;	//变化存储
const ObId PERIOD_LINK_1Min = 309237645313L;	//1分钟 
const ObId PERIOD_LINK_5Min = 309237645317L;	//5分钟
const ObId PERIOD_LINK_15Min =	309237645318L;	//15分钟
const ObId PERIOD_LINK_60Min = 309237645319L;	//60分钟

const ObId STATE_LINK_ON_OFF = 47244640485L;//分闸_合闸	
const ObId STATE_LINK_CLEAR_ALARM = 47244640486L;	//复归_告警	
const ObId STATE_LINK_CLEAR_CHG = 47244640940L;//复归_动作	
const ObId STATE_LINK_ENABLE_DISABLE = 47244642644L;//退出_投入	
const ObId STATE_LINK_LOCAL_REMOTE = 47244642645L;//就地_远方	
const ObId STATE_LINK_REMOTE_LOCAL = 47244642646L;//远方_就地	
const ObId STATE_LINK_CLEAR_LIMIT = 47244642647L;	//复归_越限	
const ObId STATE_LINK_NORMAL_DISCON = 47244642648L;//正常_中断	
const ObId STATE_LINK_CTRL_SUCC_FAIL = 47244643097L;	//遥控成功_失败 

const QString UNIT_A = "A";	///<安培
const QString UNIT_kV = "kV";	///<千伏
const QString UNIT_kW = "kW";	///<千瓦
const QString UNIT_kVar = "kVar";	///<千乏
const QString UNIT_Hz = "Hz";	///<赫兹
const QString UNIT_Degree = "Degree";	///<度		
const QString UNIT_V = "V";	///<伏
const QString UNIT_W = "W";	///<瓦
const QString UNIT_Var = "Var";	///<乏
const ObId ID_UNIT_A = 51539607983L;	//安培
const ObId ID_UNIT_kV = 51539607985L;	//千伏
const ObId ID_UNIT_kW = 51539607989L;	//千瓦
const ObId ID_UNIT_kVar = 51539607984L;	//千乏
const ObId ID_UNIT_Hz = 51539608100L;	//赫兹
const ObId ID_UNIT_Degree = 51539608172L;	//度		
const ObId ID_UNIT_V = 51539608635L;	//伏
const ObId ID_UNIT_W = 51539608636L;	//瓦
const ObId ID_UNIT_Var = 51539608637L;	//乏

const QString CTRL_MODEL_NomalSBO = "NomalSBO";///<选择执行
const QString CTRL_MODEL_NormalDirect = "NormalDiretc";///<直接执行
const QString CTRL_MODEL_EnhanceSBO = "EnhanceSBO";///<验证选择执行
const QString CTRL_MODEL_EnhanceDirect = "EnhanceDirect";///<验证直接执行
const QString CTRL_MODEL_StatusOnly = "StatusOnly";///<不遥控

const QString APC_VAL_Float = "Float";	///<浮点
const QString APC_VAL_Int = "Int";	///<整数
const QString APC_VAL_Enum = "Enum";	///<枚举

const ObId ALARM_ST_NSR		= 47244641893L; ///<告知信号_信号,返回/动作
const ObId ALARM_ST_NRD		= 47244640596L; ///<告知信号_压板,退出/投入
const ObId ALARM_ST_NRE		= 47244640622L; ///<告知信号_压板,投入/退出
const ObId ALARM_ST_NOR		= 47244640597L; ///<告知信号_操控,远方/就地
const ObId ALARM_ST_NOL		= 47244640587L; ///<告知信号_操控,就地/远方
const ObId ALARM_ST_CBO		= 47244640986L; ///<变位信号_开关,分闸/合闸_Breaker
const ObId ALARM_ST_CDO		= 47244641485L; ///<变位信号_刀闸,分闸/合闸
const ObId ALARM_ST_CGR		= 47244641978L; ///<变位信号_地线,拆除/挂接
const ObId ALARM_ST_AAR		= 47244640586L; ///<异常信号_异常,复归/告警
const ObId ALARM_ST_ALC		= 47244641914L; ///<异常信号_链路,正常/中断
const ObId ALARM_ST_FFR			= 47244640593L; ///<事故信号_事故,复归/动作
const ObId ALARM_ST_DDO		= 47244640480L; ///<双位遥信_双位遥信,分位/合位_Breaker
const ObId ALARM_ST_NSRC		= 47244642867L; ///<告知信号_信号,返回/动作（集控）
const ObId ALARM_ST_NRDC		= 47244642868L; ///<告知信号_压板,退出/投入（集控）
const ObId ALARM_ST_NREC		= 47244642869L; ///<告知信号_压板,投入/退出（集控）
const ObId ALARM_ST_NORC		= 47244642870L; ///<告知信号_操控,远方/就地（集控）
const ObId ALARM_ST_NOLC		= 47244642871L; ///<告知信号_操控,就地/远方（集控）
const ObId ALARM_ST_CBOC		= 47244642872L; ///<变位信号_开关,分闸/合闸（集控）_Breaker
const ObId ALARM_ST_CDOC		= 47244642873L; ///<变位信号_刀闸,分闸/合闸（集控）
const ObId ALARM_ST_CGRC		= 47244642874L; ///<变位信号_地线,拆除/挂接（集控）
const ObId ALARM_ST_AARC		= 47244642875L; ///<异常信号_异常,复归/告警（集控）
const ObId ALARM_ST_ALCC		= 47244642876L; ///<异常信号_链路,正常/中断（集控）
const ObId ALARM_ST_FFRC		= 47244642877L; ///<事故信号_事故,复归/动作（集控）
const ObId ALARM_ST_DDOC		= 47244642878L; ///<双位遥信_双位遥信,分位/合位（集控）_Breaker
const ObId ALARM_ST_AARA		= 47244643031L; ///<异常信号_异常,复归/告警(再次告警)
const ObId ALARM_ST_AARD		= 47244643099L; ///<异常信号_异常,复归/告警(延时告警)

DBPOOLHANDLE GlobalInfo::g_DBPoolHandle = 0;
Database* GlobalInfo::g_Database = NULL;
UserMSInterface* GlobalInfo::g_User = NULL;
OperationLog* GlobalInfo::g_DBLog = NULL;

QStringList  GlobalInfo::displayAttrList;
QList<InsertData> GlobalInfo::g_InsertDatas;
QList<QStandardItem*> GlobalInfo::g_WriteDatas;
QList<ObId> GlobalInfo::g_DeleteDatas;
QPushButton * GlobalInfo::g_SaveButton = NULL;
PickTreeDialog* GlobalInfo::deviceDialog = NULL;

QMap<ObId,QString> GlobalInfo::allStateContainerLinkCombox;
QMap<ObId,QString> GlobalInfo::allAlarmStateContainerLinkCombox;
QMap<ObId,QString> GlobalInfo::allGatewaySpecificationLinkCombox;
QMap<ObId,QString> GlobalInfo::allMeasurementTypeLinkCombox;	
QMap<ObId,QString> GlobalInfo::allUnitsLinkCombox;

QMap<QString,ObId> GlobalInfo::allGatewaySpecificationLink;
QMap<ObId,QString> GlobalInfo::allGatewaySpecificationLink_out;
QMap<QString,ObId> GlobalInfo::allMeasurementTypeLink;
QMap<ObId,QString> GlobalInfo::allMeasurementTypeLink_out;
QMap<QString,ObId> GlobalInfo::allUnitsLink;
QMap<ObId,QString> GlobalInfo::allUnitsLink_out;
QMap<QString,int> GlobalInfo::allControlMode;
QMap<int,QString> GlobalInfo::allControlMode_out;
QMap<QString,int> GlobalInfo::allAPCMode;
QMap<int,QString> GlobalInfo::allAPCMode_out;
QMap<QString,int> GlobalInfo::allDeviceProperty;
QMap<int,QString> GlobalInfo::allDeviceProperty_out;

AType GlobalInfo::AT_AccessPointList = 0;
AType GlobalInfo::AT_AlarmStateContainerLink = 0;
AType GlobalInfo::AT_AllowList = 0;
AType GlobalInfo::AT_ampRating = 0;
AType GlobalInfo::AT_APCMode = 0;
AType GlobalInfo::AT_APCPointLink = 0;
AType GlobalInfo::AT_AreaOfResponsibilityList = 0;
AType GlobalInfo::AT_BreakerType = 0;
AType GlobalInfo::AT_CC1 = 0;
AType GlobalInfo::AT_CC2 = 0;
AType GlobalInfo::AT_ChangeNum = 0;
AType GlobalInfo::AT_ChannelNumber = 0;
AType GlobalInfo::AT_ChannelState = 0;
AType GlobalInfo::AT_ChildrenList = 0;
AType GlobalInfo::AT_ClusterLink = 0;
AType GlobalInfo::AT_ClusterRole = 0;
AType GlobalInfo::AT_CommitSyncEnd = 0;
AType GlobalInfo::AT_ControlModel = 0;
AType GlobalInfo::AT_ControlResult = 0;
AType GlobalInfo::AT_Description = 0;
AType GlobalInfo::AT_DEVICEID = 0;
AType GlobalInfo::AT_DeviceProperty = 0;
AType GlobalInfo::AT_DMSCUID = 0;
AType GlobalInfo::AT_DPCPointLink = 0;
AType GlobalInfo::AT_DPSPointLink = 0;
AType GlobalInfo::AT_Factory = 0;
AType GlobalInfo::AT_FaultState = 0;
AType GlobalInfo::AT_FaultToleranceLink = 0;
AType GlobalInfo::AT_FeederLink = 0;
AType GlobalInfo::AT_GatewaySpecificationLink = 0;
AType GlobalInfo::AT_hLim = 0;
AType GlobalInfo::AT_hhLim = 0;
AType GlobalInfo::AT_hhhLim = 0;
AType GlobalInfo::AT_HouseKeeping_State = 0;
AType GlobalInfo::AT_IPAddrA = 0;
AType GlobalInfo::AT_IPAddrB = 0;
AType GlobalInfo::AT_IPAddress = 0;
AType GlobalInfo::AT_IsReversed = 0;
AType GlobalInfo::AT_IsyncPartitionList = 0;
AType GlobalInfo::AT_KeyName = 0;
AType GlobalInfo::AT_Limit = 0;
AType GlobalInfo::AT_lLim = 0;
AType GlobalInfo::AT_llLim = 0;
AType GlobalInfo::AT_lllLim = 0;
AType GlobalInfo::AT_McastAddrA = 0;
AType GlobalInfo::AT_McastAddrB = 0;
AType GlobalInfo::AT_McastLink = 0;
AType GlobalInfo::AT_McastPortA = 0;
AType GlobalInfo::AT_McastPortB = 0;
AType GlobalInfo::AT_MeasLink = 0;
AType GlobalInfo::AT_MeasurementTypeLink = 0;
AType GlobalInfo::AT_Model = 0;
AType GlobalInfo::AT_MVPointLink = 0;
AType GlobalInfo::AT_Name = 0;
AType GlobalInfo::AT_ObjOrder = 0;
AType GlobalInfo::AT_OnlineStatus = 0;
AType GlobalInfo::AT_OnlineTime = 0;
AType GlobalInfo::AT_ParamMva = 0;
AType GlobalInfo::AT_ParentClusterList = 0;
AType GlobalInfo::AT_ParentLink = 0;
AType GlobalInfo::AT_PartitionID = 0;
AType GlobalInfo::AT_PartitionList = 0;
AType GlobalInfo::AT_PreferredSyncFromList = 0;
AType GlobalInfo::AT_ProtocolAddress = 0;
AType GlobalInfo::AT_PSRLink = 0;
AType GlobalInfo::AT_RangeHigh = 0;
AType GlobalInfo::AT_RangeLow = 0;
AType GlobalInfo::AT_RTEnergized = 0;
AType GlobalInfo::AT_SerialAddr = 0;
AType GlobalInfo::AT_SerialNo = 0;
AType GlobalInfo::AT_ServiceTypeList = 0;
AType GlobalInfo::AT_State = 0;
AType GlobalInfo::AT_StateContainerLink = 0;
AType GlobalInfo::AT_TcpHostList = 0;
AType GlobalInfo::AT_UnitsLink = 0;
AType GlobalInfo::AT_Value = 0;

AType GlobalInfo::AT_SectionGroup = 0;//新增

OType GlobalInfo::OT_Analog = 0;
OType GlobalInfo::OT_AlarmInstance = 0;
OType GlobalInfo::OT_APCPoint = 0;
OType GlobalInfo::OT_AreaOfResponsibility = 0;
OType GlobalInfo::OT_BSCPoint = 0;
OType GlobalInfo::OT_CPSCluster = 0;
OType GlobalInfo::OT_CPSPartition = 0;
OType GlobalInfo::OT_CPSSession = 0;
OType GlobalInfo::OT_DCSwitch = 0;
OType GlobalInfo::OT_Disconnector = 0;
OType GlobalInfo::OT_Discrete = 0;
OType GlobalInfo::OT_DistributionTransformer = 0;
OType GlobalInfo::OT_DMSCommunicateUnit = 0;
OType GlobalInfo::OT_DPCPoint = 0;
OType GlobalInfo::OT_DPSPoint = 0;
OType GlobalInfo::OT_Feeder = 0;
OType GlobalInfo::OT_Folder = 0;
OType GlobalInfo::OT_GOS = 0;
OType GlobalInfo::OT_IncrementCommit = 0;
OType GlobalInfo::OT_LoadBreakSwitch = 0;
OType GlobalInfo::OT_Machine = 0;
OType GlobalInfo::OT_MeasurementType = 0;
OType GlobalInfo::OT_MVPoint = 0;
OType GlobalInfo::OT_Network = 0;
OType GlobalInfo::OT_PartitionCom = 0;
OType GlobalInfo::OT_PartitionMcast = 0;
OType GlobalInfo::OT_PMSBreaker = 0;
OType GlobalInfo::OT_PMSBusbar;
OType GlobalInfo::OT_PMSDoubleWindingTransformer = 0;
OType GlobalInfo::OT_PMSRoot = 0;
OType GlobalInfo::OT_PMSStation = 0;
OType GlobalInfo::OT_PMSTerminal = 0;
OType GlobalInfo::OT_PMSThreeWindingTransformer = 0;
OType GlobalInfo::OT_POMSCommChannel = 0;
OType GlobalInfo::OT_ProtocolType = 0;
OType GlobalInfo::OT_SerialChannel = 0;
OType GlobalInfo::OT_ServiceType = 0;
OType GlobalInfo::OT_SubControlArea = 0;
OType GlobalInfo::OT_TransformerWinding = 0;

OType GlobalInfo::OT_RemoteAPCPoint = 0;//新增
OType GlobalInfo::OT_RemoteDPCPoint = 0;//新增
OType GlobalInfo::OT_RemoteDPSPoint = 0;//新增
OType GlobalInfo::OT_RemoteMVPoint = 0;//新增
OType GlobalInfo::OT_RCS = 0;//新增
OType GlobalInfo::OT_Section = 0;//新增
OType GlobalInfo::OT_RemoteChannel = 0;//新增
OType GlobalInfo::OT_RemoteStation = 0;//新增



bool GlobalInfo::initOTypeAndAType()
{
	try
	{
		AT_AccessPointList = g_Database->matchAType("AccessPointList");
		AT_AlarmStateContainerLink = g_Database->matchAType("AlarmStateContainerLink");
		AT_AllowList = g_Database->matchAType("AllowList");
		AT_ampRating = g_Database->matchAType("ampRating");
		AT_APCMode = g_Database->matchAType("APCMode");
		AT_APCPointLink = g_Database->matchAType("APCPointLink");
		AT_AreaOfResponsibilityList = g_Database->matchAType("AreaOfResponsibilityList");
		AT_BreakerType = g_Database->matchAType("BreakerType");
		AT_CC1 = g_Database->matchAType("CC1");
		AT_CC2 = g_Database->matchAType("CC2");
		AT_ChangeNum = g_Database->matchAType("ChangeNum");
		AT_ChannelNumber = g_Database->matchAType("ChannelNumber");
		AT_ChannelState = g_Database->matchAType("ChannelState");
		AT_ChildrenList = g_Database->matchAType("ChildrenList");
		AT_ClusterLink = g_Database->matchAType("ClusterLink");
		AT_ClusterRole = g_Database->matchAType("ClusterRole");
		AT_CommitSyncEnd = g_Database->matchAType("CommitSyncEnd");
		AT_ControlModel = g_Database->matchAType("ControlModel");
		AT_ControlResult = g_Database->matchAType("ControlResult");
		AT_Description = g_Database->matchAType("Description");
		AT_DEVICEID = g_Database->matchAType("DEVICEID");
		AT_DeviceProperty = g_Database->matchAType("DeviceProperty");
		AT_DMSCUID = g_Database->matchAType("DMSCUID");
		AT_DPCPointLink = g_Database->matchAType("DPCPointLink");
		AT_DPSPointLink = g_Database->matchAType("DPSPointLink");
		AT_Factory = g_Database->matchAType("Factory");
		AT_FaultState = g_Database->matchAType("FaultState");
		AT_FaultToleranceLink = g_Database->matchAType("FaultToleranceLink");
		AT_FeederLink = g_Database->matchAType("FeederLink");
		AT_GatewaySpecificationLink = g_Database->matchAType("GatewaySpecificationLink");
		AT_hLim = g_Database->matchAType("hLim");
		AT_hhLim = g_Database->matchAType("hhLim");
		AT_hhhLim = g_Database->matchAType("hhhLim");
		AT_HouseKeeping_State = g_Database->matchAType("HouseKeeping_State");
		AT_IPAddrA = g_Database->matchAType("IPAddrA");
		AT_IPAddrB = g_Database->matchAType("IPAddrB");
		AT_IPAddress = g_Database->matchAType("IPAddress");
		AT_IsReversed = g_Database->matchAType("IsReversed");
		AT_IsyncPartitionList = g_Database->matchAType("IsyncPartitionList");
		AT_KeyName = g_Database->matchAType("KeyName");
		AT_Limit = g_Database->matchAType("Limit");
		AT_lLim = g_Database->matchAType("lLim");
		AT_llLim = g_Database->matchAType("llLim");
		AT_lllLim = g_Database->matchAType("lllLim");
		AT_McastAddrA = g_Database->matchAType("McastAddrA");
		AT_McastAddrB = g_Database->matchAType("McastAddrB");
		AT_McastLink = g_Database->matchAType("McastLink");
		AT_McastPortA = g_Database->matchAType("McastPortA");
		AT_McastPortB = g_Database->matchAType("McastPortB");
		AT_MeasLink = g_Database->matchAType("MeasLink");
		AT_MeasurementTypeLink = g_Database->matchAType("MeasurementTypeLink");
		AT_Model = g_Database->matchAType("Model");
		AT_MVPointLink = g_Database->matchAType("MVPointLink");
		AT_Name = g_Database->matchAType("Name");
		AT_ObjOrder = g_Database->matchAType("ObjOrder");
		AT_OnlineStatus = g_Database->matchAType("OnlineStatus");
		AT_OnlineTime = g_Database->matchAType("OnlineTime");
		AT_ParamMva = g_Database->matchAType("ParamMva");//额定视在功率AType
		AT_ParentClusterList = g_Database->matchAType("ParentClusterList");
		AT_ParentLink = g_Database->matchAType("ParentLink");
		AT_PartitionID = g_Database->matchAType("PartitionID");
		AT_PartitionList = g_Database->matchAType("PartitionList");
		AT_PreferredSyncFromList = g_Database->matchAType("PreferredSyncFromList");
		AT_ProtocolAddress = g_Database->matchAType("ProtocolAddress");
		AT_PSRLink = g_Database->matchAType("PSRLink");
		AT_RangeHigh = g_Database->matchAType("RangeHigh");
		AT_RangeLow = g_Database->matchAType("RangeLow");
		AT_RTEnergized = g_Database->matchAType("RTEnergized");//是否带电
		AT_SerialAddr = g_Database->matchAType("SerialAddr");
		AT_SerialNo = g_Database->matchAType("SerialNo");
		AT_ServiceTypeList = g_Database->matchAType("ServiceTypeList");
		AT_State = g_Database->matchAType("State");
		AT_StateContainerLink = g_Database->matchAType("StateContainerLink");
		AT_TcpHostList = g_Database->matchAType("TcpHostList");
		AT_UnitsLink = g_Database->matchAType("UnitsLink");
		AT_Value = g_Database->matchAType("Value");

		AT_SectionGroup = g_Database->matchAType("SectionGroup");//新增

		OT_Analog = g_Database->matchOType("Analog");
		OT_AlarmInstance =  g_Database->matchOType("AlarmInstance");
		OT_APCPoint = g_Database->matchOType("APCPoint");
		OT_AreaOfResponsibility = g_Database->matchOType("AreaOfResponsibility");
		OT_BSCPoint = g_Database->matchOType("BSCPoint");
		OT_CPSCluster = g_Database->matchOType("CPSCluster");
		OT_CPSPartition = g_Database->matchOType("CPSPartition");
		OT_CPSSession = g_Database->matchOType("CPSSession");
		OT_DCSwitch = g_Database->matchOType("DCSwitch");
		OT_Disconnector = g_Database->matchOType("Disconnector");
		OT_Discrete = g_Database->matchOType("Discrete");
		OT_DistributionTransformer = g_Database->matchOType("DistributionTransformer");
		OT_DMSCommunicateUnit = g_Database->matchOType("DMSCommunicateUnit");
		OT_DPCPoint = g_Database->matchOType("DPCPoint");
		OT_DPSPoint = g_Database->matchOType("DPSPoint");
		OT_Feeder = g_Database->matchOType("Feeder");
		OT_Folder = g_Database->matchOType("Folder");
		OT_GOS = g_Database->matchOType("GOS");
		OT_IncrementCommit = g_Database->matchOType("IncrementCommit");
		OT_LoadBreakSwitch = g_Database->matchOType("LoadBreakSwitch");
		OT_Machine = g_Database->matchOType("Machine");
		OT_MeasurementType = g_Database->matchOType("MeasurementType");
		OT_MVPoint = g_Database->matchOType("MVPoint");
		OT_Network = g_Database->matchOType("Network");
		OT_PartitionCom = g_Database->matchOType("PartitionCom");
		OT_PartitionMcast = g_Database->matchOType("PartitionMcast");
		OT_PMSBreaker = g_Database->matchOType("PMSBreaker");
		OT_PMSBusbar = g_Database->matchOType("PMSBusbar");
		OT_PMSDoubleWindingTransformer = g_Database->matchOType("PMSDoubleWindingTransformer");
		OT_PMSRoot = g_Database->matchOType("PMSRoot");
		OT_PMSStation =  g_Database->matchOType("PMSStation");
		OT_PMSTerminal = g_Database->matchOType("PMSTerminal");
		OT_PMSThreeWindingTransformer = g_Database->matchOType("PMSThreeWindingTransformer");
		OT_POMSCommChannel = g_Database->matchOType("POMSCommChannel");
		OT_ProtocolType = g_Database->matchOType("ProtocolType");
		OT_SerialChannel = g_Database->matchOType("SerialChannel");
		OT_ServiceType = g_Database->matchOType("ServiceType");
		OT_SubControlArea = g_Database->matchOType("SubControlArea");
		OT_TransformerWinding = g_Database->matchOType("TransformerWinding");

		OT_RemoteAPCPoint = g_Database->matchOType("RemoteAPCPoint");//新增
		OT_RemoteDPCPoint = g_Database->matchOType("RemoteDPCPoint");//新增
		OT_RemoteDPSPoint = g_Database->matchOType("RemoteDPSPoint");//新增
		OT_RemoteMVPoint = g_Database->matchOType("RemoteMVPoint");//新增
		OT_RCS = g_Database->matchOType("RCS");//新增
		OT_Section = g_Database->matchOType("Section");//新增
		OT_RemoteChannel = g_Database->matchOType("RemoteChannel");//新增
		OT_RemoteStation = g_Database->matchOType("RemoteStation");//新增
	}
	catch (Exception& e)
	{
		return false;
	}
	return true;
}


GlobalInfo::GlobalInfo()
{
}

GlobalInfo::~GlobalInfo()
{
}

void GlobalInfo::init()
{
	initDisplayAttributes();//初始化显示的属性atype
	initGatewaySpecificationLink();//初始化历史存储5分钟
	initGatewaySpecificationLinkCombox();
	initAllMeasurementTypeLink();//初始化量测
	initAllStateContainerLinkCombox();//初始化状态链接
	initAllAlarmStateContainerLinkCombox();//初始化告警状态链接
	initAllUnitsLink();//初始化单位
	initAllUnitsLinkCombox();
	initAllControlMode();//初始化控制模式
	initAllAPCMode();//初始化遥调模式
	initAllDeviceProperty();//初始化设备属性类型
}

void GlobalInfo::initDisplayAttributes()
{
	char* cpsenv = getenv("CPS_ENV");
	QString cfgPath = QString::fromUtf8(cpsenv) + "/etc/rcstree/rcstree.ini";
	QFile cfgFile(cfgPath);
	if (!cfgFile.exists())
	{
		displayAttrList << "Name" <<"ObjOrder"<< "ProtocolAddress" << "DPCPointLink" << "IsReversed" << "MeasurementTypeLink" \
			<< "CC1" << "CC2" << "Factor" << "GatewaySpecificationLink" << "lllLim" << "llLim" << "lLim" << "hLim" << "hhLim" << "hhhLim"\
			<< "RangeHigh" << "RangeLow" << "DPSPointLink" <<"AlarmStateContainerLink"<<"SignalType"<< "Description"\
			<<"DEVICEID"<<"StateContainerLink"<<"DeviceProperty"<<"AlarmMode"<<"IPAddrA"<<"IPAddrB"<<"PortA"<<"PortB"<<"FaultToleranceLink"\
			<<"TerminalAddress"<<"AreaAddress"<<"ComDeviceType"<<"SingleChannelFlag"<<"MVPointLink"<<"APCPointLink"<<"ResumeMode"\
			<<"MonitorMode"<<"PreferredSyncFromList"<<"ClusterLink"<<"ParentClusterList"<<"NodeRole"<<"ServiceTypeList"<<"SyncMethod"\
			<<"AllowList"<<"AccessPointList"<<"PartitionList"<<"TcpHostList"<<"IsyncPartitionList"<<"ClusterRole"<<"KeyName"<<"UnitsLink"\
			<<"CommMode"<<"Type"<<"SerialAddr"<<"ServerIP"<<"ClientIP"\
			<<"APCPointLink"<<"ASDUType"<<"DPCPointLink"<<"ObjectLink"<<"AutoCreateSOE"<<"RemoteValueMode";
	}else{
		QSettings settings(cfgPath, QSettings::IniFormat);
		settings.beginGroup("DisplayAttributeList");
		QStringList strAttrList = settings.childKeys();
		int attrEnable = 0;
		for (int i = 0; i < strAttrList.size(); i++)
		{
			attrEnable = settings.value(strAttrList.at(i), "0").toInt();
			if (attrEnable) 
			{
				displayAttrList << strAttrList.at(i);
			}
		}
		settings.endGroup();
	}
	cfgFile.flush();
	cfgFile.close();
}

void GlobalInfo::initGatewaySpecificationLink()
{
	//allGatewaySpecificationLink.insert(PERIOD_unsave,PERIOD_LINK_unsave);
	allGatewaySpecificationLink.insert(PERIOD_saveAll,PERIOD_LINK_saveAll);
	allGatewaySpecificationLink.insert(PERIOD_1Min,PERIOD_LINK_1Min);
	allGatewaySpecificationLink.insert(PERIOD_5Min,PERIOD_LINK_5Min);
	allGatewaySpecificationLink.insert(PERIOD_15Min,PERIOD_LINK_15Min);
	allGatewaySpecificationLink.insert(PERIOD_60Min,PERIOD_LINK_60Min);

	allGatewaySpecificationLink_out.insert(PERIOD_LINK_saveAll,PERIOD_saveAll);
	allGatewaySpecificationLink_out.insert(PERIOD_LINK_1Min,PERIOD_1Min);
	allGatewaySpecificationLink_out.insert(PERIOD_LINK_5Min,PERIOD_5Min);
	allGatewaySpecificationLink_out.insert(PERIOD_LINK_15Min,PERIOD_15Min);
	allGatewaySpecificationLink_out.insert(PERIOD_LINK_60Min,PERIOD_60Min);
}

void GlobalInfo::initGatewaySpecificationLinkCombox()
{
	QList<ObId> obIds;
	obIds<<PERIOD_LINK_unsave<<PERIOD_LINK_saveAll<<PERIOD_LINK_1Min<<PERIOD_LINK_5Min<<PERIOD_LINK_15Min<<PERIOD_LINK_60Min;
	for(int i=0;i<obIds.size();i++)
	{
		StringData name = "";
		ToolUtil::databaseRead(obIds[i],AT_Name,&name);
		allGatewaySpecificationLinkCombox.insert(obIds[i],QString::fromUtf8(((std::string)name).c_str()));
	}
}

void GlobalInfo::initAllMeasurementTypeLink()
{
	int num = ToolUtil::databaseFind(OT_MeasurementType, NULL, 0);
	if (num>0)
	{
		ObId *obIds = new ObId[num];
		ToolUtil::databaseFind(OT_MeasurementType,NULL, 0, obIds, num);
		for(int i=0;i<num;i++)
		{
			StringData keyName = "";
			ToolUtil::databaseRead(obIds[i],AT_KeyName,&keyName);
			allMeasurementTypeLink.insert(QString::fromUtf8(((std::string)keyName).c_str()),obIds[i]);
			allMeasurementTypeLink_out.insert(obIds[i],QString::fromUtf8(((std::string)keyName).c_str()));
		}
		delete[] obIds;
	}
}

void GlobalInfo::initAllStateContainerLinkCombox()
{
	QList<ObId> obIds;
	obIds<<STATE_LINK_ON_OFF<<STATE_LINK_CLEAR_ALARM<<STATE_LINK_CLEAR_CHG<<STATE_LINK_ENABLE_DISABLE<<STATE_LINK_LOCAL_REMOTE
		<<STATE_LINK_REMOTE_LOCAL<<STATE_LINK_CLEAR_LIMIT<<STATE_LINK_NORMAL_DISCON<<STATE_LINK_CTRL_SUCC_FAIL;
	for(int i=0;i<obIds.size();i++)
	{
		StringData name = "";
		ToolUtil::databaseRead(obIds[i],AT_Name,&name);
		allStateContainerLinkCombox.insert(obIds[i],QString::fromUtf8(((std::string)name).c_str()));
	}
}

void GlobalInfo::initAllAlarmStateContainerLinkCombox()
{
	QList<ObId> obIds;
	obIds<<ALARM_ST_NSR<<ALARM_ST_NRD<<ALARM_ST_NRE<<ALARM_ST_NOR<<ALARM_ST_NOL<<ALARM_ST_CBO<<ALARM_ST_CDO
		<<ALARM_ST_CGR<<ALARM_ST_AAR<<ALARM_ST_ALC<<ALARM_ST_FFR<<ALARM_ST_DDO<<ALARM_ST_NSRC<<ALARM_ST_NRDC
		<<ALARM_ST_NREC<<ALARM_ST_NORC<<ALARM_ST_NOLC<<ALARM_ST_CBOC<<ALARM_ST_CDOC<<ALARM_ST_CGRC<<ALARM_ST_AARC
		<<ALARM_ST_ALCC<<ALARM_ST_FFRC<<ALARM_ST_DDOC<<ALARM_ST_AARA<<ALARM_ST_AARD;
	for(int i=0;i<obIds.size();i++)
	{
		StringData name = "";
		ToolUtil::databaseRead(obIds[i],AT_Name,&name);
		allAlarmStateContainerLinkCombox.insert(obIds[i],QString::fromUtf8(((std::string)name).c_str()));
	}
}

void GlobalInfo::initAllUnitsLink()
{
	allUnitsLink.insert(UNIT_A,ID_UNIT_A);
	allUnitsLink.insert(UNIT_kV,ID_UNIT_kV);
	allUnitsLink.insert(UNIT_kW,ID_UNIT_kW);
	allUnitsLink.insert(UNIT_kVar,ID_UNIT_kVar);
	allUnitsLink.insert(UNIT_Hz,ID_UNIT_Hz);
	allUnitsLink.insert(UNIT_Degree,ID_UNIT_Degree);
	allUnitsLink.insert(UNIT_V,ID_UNIT_V);
	allUnitsLink.insert(UNIT_W,ID_UNIT_W);
	allUnitsLink.insert(UNIT_Var,ID_UNIT_Var);

	allUnitsLink_out.insert(ID_UNIT_A,UNIT_A);
	allUnitsLink_out.insert(ID_UNIT_kV,UNIT_kV);
	allUnitsLink_out.insert(ID_UNIT_kW,UNIT_kW);
	allUnitsLink_out.insert(ID_UNIT_kVar,UNIT_kVar);
	allUnitsLink_out.insert(ID_UNIT_Hz,UNIT_Hz);
	allUnitsLink_out.insert(ID_UNIT_Degree,UNIT_Degree);
	allUnitsLink_out.insert(ID_UNIT_V,UNIT_V);
	allUnitsLink_out.insert(ID_UNIT_W,UNIT_W);
	allUnitsLink_out.insert(ID_UNIT_Var,UNIT_Var);
}

void GlobalInfo::initAllUnitsLinkCombox()
{
	ObId unitRootId = ToolUtil::getFolderObIdByDes("Units");
	QList<ObId> obIds;
	ToolUtil::getChildrenList(unitRootId,obIds);

	for(int i=0;i<obIds.size();i++)
	{
		StringData name = "";
		ToolUtil::databaseRead(obIds[i],AT_Name,&name);
		allUnitsLinkCombox.insert(obIds[i],QString::fromUtf8(((std::string)name).c_str()));
	}
}

void GlobalInfo::initAllControlMode()
{
	allControlMode.insert(CTRL_MODEL_NomalSBO,0);
	allControlMode.insert(CTRL_MODEL_NormalDirect,1);
	allControlMode.insert(CTRL_MODEL_EnhanceSBO,2);
	allControlMode.insert(CTRL_MODEL_EnhanceDirect,3);
	allControlMode.insert(CTRL_MODEL_StatusOnly,4);

	allControlMode_out.insert(0,CTRL_MODEL_NomalSBO);
	allControlMode_out.insert(1,CTRL_MODEL_NormalDirect);
	allControlMode_out.insert(2,CTRL_MODEL_EnhanceSBO);
	allControlMode_out.insert(3,CTRL_MODEL_EnhanceDirect);
	allControlMode_out.insert(4,CTRL_MODEL_StatusOnly);
}

void GlobalInfo::initAllAPCMode()
{
	allAPCMode.insert(APC_VAL_Float,0);
	allAPCMode.insert(APC_VAL_Int,1);
	allAPCMode.insert(APC_VAL_Enum,2);

	allAPCMode_out.insert(0,APC_VAL_Float);
	allAPCMode_out.insert(1,APC_VAL_Int);
	allAPCMode_out.insert(2,APC_VAL_Enum);
}

void GlobalInfo::initAllDeviceProperty()
{
	allDeviceProperty.insert("FTU",0);
	allDeviceProperty.insert("DTU",1);
	allDeviceProperty.insert("RTU",4);
	allDeviceProperty.insert("TTU",5);
	allDeviceProperty.insert("DPU",6);

	allDeviceProperty_out.insert(0,"FTU");
	allDeviceProperty_out.insert(1,"DTU");
	allDeviceProperty_out.insert(4,"RTU");
	allDeviceProperty_out.insert(5,"TTU");
	allDeviceProperty_out.insert(6,"DPU");
}

ObId GlobalInfo::getDefaultStateContainerLink(QString measurementType)
{
	ObId stateLink = 0;
	if (measurementType=="INF_ALARM")
	{
		stateLink=STATE_LINK_CLEAR_ALARM;
	}else if (measurementType=="CB")
	{
		stateLink=STATE_LINK_ON_OFF;
	}else if (measurementType=="DS")
	{
		stateLink=STATE_LINK_ON_OFF;
	}else if (measurementType=="INF_REMOTE")
	{
		stateLink=STATE_LINK_LOCAL_REMOTE;
	}else{
		stateLink=STATE_LINK_CLEAR_CHG;
	}
	return stateLink;
}

ObId GlobalInfo::getDefaultAlarmStateContainerLink(QString measurementType)
{
	ObId alarmStateLink = 0;
	if (measurementType=="INF_ALARM")
	{
		alarmStateLink=ALARM_ST_AAR;
	}else if (measurementType=="CB")
	{
		alarmStateLink=ALARM_ST_CBO;
	}else if (measurementType=="DS")
	{
		alarmStateLink=ALARM_ST_CDO;
	}else if (measurementType=="INF_EVENT")
	{
		alarmStateLink=ALARM_ST_FFR;
	}else if (measurementType=="INF_REMOTE")
	{
		alarmStateLink=ALARM_ST_NOL;
	}else{
		alarmStateLink=ALARM_ST_NSR;
	}
	return alarmStateLink;
}