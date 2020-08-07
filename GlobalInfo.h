#pragma once

#include "common.h"
#include "ToolUtil.h"
#include "DataModel.h"

const ObId YX = 47244642879L;
const ObId YC = 47244642880L;
const ObId YK = 47244642881L;
const ObId YT = 47244642882L;

const ObId DefaultAlarmFormat		= 73014444138L; 
const ObId DefaultAlarmBehavior		= 85899345981L; 
const ObId DefaultAlarmType		= 1030792151164L; 

class PickTreeDialog;

class GlobalInfo
{
public:
	GlobalInfo();
	~GlobalInfo();

	static DBPOOLHANDLE g_DBPoolHandle;
	static Database *g_Database;
	static UserMSInterface* g_User;
	static OperationLog *g_DBLog;

	static QStringList  displayAttrList;
	static QList<InsertData> g_InsertDatas;
	static QList<QStandardItem*> g_WriteDatas;
	static QList<ObId> g_DeleteDatas;
	static QPushButton *g_SaveButton;
	static PickTreeDialog* deviceDialog;

	static QMap<ObId,QString> allStateContainerLinkCombox;
	static QMap<ObId,QString> allAlarmStateContainerLinkCombox;
	static QMap<ObId,QString> allGatewaySpecificationLinkCombox;
	static QMap<ObId,QString> allMeasurementTypeLinkCombox;	
	static QMap<ObId,QString> allUnitsLinkCombox;

	static QMap<QString,ObId> allGatewaySpecificationLink;
	static QMap<ObId,QString> allGatewaySpecificationLink_out;
	static QMap<QString,ObId> allMeasurementTypeLink;	
	static QMap<ObId,QString> allMeasurementTypeLink_out;
	static QMap<QString,ObId> allUnitsLink;
	static QMap<ObId,QString> allUnitsLink_out;
	static QMap<QString,int> allControlMode;
	static QMap<int,QString> allControlMode_out;
	static QMap<QString,int> allAPCMode;
	static QMap<int,QString> allAPCMode_out;
	static QMap<QString,int> allDeviceProperty;
	static QMap<int,QString> allDeviceProperty_out;

	static AType AT_AccessPointList;
	static AType AT_AlarmStateContainerLink;
	static AType AT_AllowList;
	static AType AT_ampRating;
	static AType AT_APCMode;
	static AType AT_APCPointLink;
	static AType AT_AreaOfResponsibilityList;
	static AType AT_BreakerType;
	static AType AT_CC1;
	static AType AT_CC2;
	static AType AT_ChangeNum;
	static AType AT_ChannelNumber;
	static AType AT_ChannelState;
	static AType AT_ChildrenList;
	static AType AT_ClusterLink;
	static AType AT_ClusterRole;
	static AType AT_CommitSyncEnd;
	static AType AT_ControlModel;
	static AType AT_ControlResult;
	static AType AT_Description;
	static AType AT_DEVICEID;
	static AType AT_DeviceProperty;
	static AType AT_DMSCUID;
	static AType AT_DPCPointLink;
	static AType AT_DPSPointLink;
	static AType AT_Factory;
	static AType AT_FaultState;
	static AType AT_FaultToleranceLink;
	static AType AT_FeederLink;
	static AType AT_GatewaySpecificationLink;
	static AType AT_hLim;
	static AType AT_hhLim;
	static AType AT_hhhLim;
	static AType AT_HouseKeeping_State;
	static AType AT_IPAddrA;
	static AType AT_IPAddrB;
	static AType AT_IPAddress;
	static AType AT_IsReversed;
	static AType AT_IsyncPartitionList;
	static AType AT_KeyName;
	static AType AT_Limit;
	static AType AT_lLim;
	static AType AT_llLim;
	static AType AT_lllLim;
	static AType AT_McastAddrA;
	static AType AT_McastAddrB;
	static AType AT_McastLink;
	static AType AT_McastPortA;
	static AType AT_McastPortB;
	static AType AT_MeasLink;
	static AType AT_MeasurementTypeLink;
	static AType AT_Model;
	static AType AT_MVPointLink;
	static AType AT_Name;
	static AType AT_ObjOrder;
	static AType AT_OnlineStatus;
	static AType AT_OnlineTime;
	static AType AT_ParamMva;
	static AType AT_ParentClusterList;
	static AType AT_ParentLink;
	static AType AT_PartitionID;
	static AType AT_PartitionList;
	static AType AT_PreferredSyncFromList;
	static AType AT_ProtocolAddress;
	static AType AT_PSRLink;
	static AType AT_RangeHigh;
	static AType AT_RangeLow;
	static AType AT_RTEnergized;
	static AType AT_SerialAddr;
	static AType AT_SerialNo;
	static AType AT_ServiceTypeList;
	static AType AT_State;
	static AType AT_StateContainerLink;
	static AType AT_TcpHostList;
	static AType AT_UnitsLink;
	static AType AT_Value;

	static AType AT_SectionGroup;

	static OType OT_Analog;
	static OType OT_AlarmInstance;
	static OType OT_APCPoint;
	static OType OT_AreaOfResponsibility;
	static OType OT_BSCPoint;
	static OType OT_CPSCluster;
	static OType OT_CPSPartition;
	static OType OT_CPSSession;
	static OType OT_DCSwitch;
	static OType OT_Disconnector;
	static OType OT_Discrete;
	static OType OT_DistributionTransformer;
	static OType OT_DMSCommunicateUnit;
	static OType OT_DPCPoint;
	static OType OT_DPSPoint;
	static OType OT_Feeder;
	static OType OT_Folder;
	static OType OT_GOS;
	static OType OT_IncrementCommit;
	static OType OT_LoadBreakSwitch;
	static OType OT_Machine;
	static OType OT_MeasurementType;
	static OType OT_MVPoint;
	static OType OT_Network;
	static OType OT_PartitionCom;
	static OType OT_PartitionMcast;
	static OType OT_PMSBreaker;
	static OType OT_PMSBusbar;
	static OType OT_PMSDoubleWindingTransformer;
	static OType OT_PMSRoot;
	static OType OT_PMSStation;
	static OType OT_PMSTerminal;
	static OType OT_PMSThreeWindingTransformer;
	static OType OT_POMSCommChannel;
	static OType OT_ProtocolType;
	static OType OT_SerialChannel;
	static OType OT_ServiceType;
	static OType OT_SubControlArea;
	static OType OT_TransformerWinding;

	static OType OT_RemoteAPCPoint;//新增
	static OType OT_RemoteDPCPoint;//新增
	static OType OT_RemoteDPSPoint;//新增
	static OType OT_RemoteMVPoint;//新增
	static OType OT_RCS;//新增
	static OType OT_Section;//新增
	static OType OT_RemoteChannel;//新增
	static OType OT_RemoteStation;//新增

	static bool initOTypeAndAType();
	static void init();
	static ObId getDefaultStateContainerLink(QString measurementType);
	static ObId getDefaultAlarmStateContainerLink(QString measurementType);

private:

	static void initDisplayAttributes();
	static void initGatewaySpecificationLink();
	static void initGatewaySpecificationLinkCombox();
	static void initAllMeasurementTypeLink();
	static void initAllStateContainerLinkCombox();
	static void initAllAlarmStateContainerLinkCombox();
	static void initAllUnitsLink();
	static void initAllUnitsLinkCombox();
	static void initAllControlMode();
	static void initAllAPCMode();
	static void initAllDeviceProperty();
};
