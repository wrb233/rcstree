#include "CellDelegateWidget.h"

CellDelegateWidget::CellDelegateWidget(QString displayValue,AType atype, OType otype, ObId parentId, QWidget* parent, Qt::WindowFlags flags ): CpsWidget( parent, flags )
{
	ui.setupUi(this);
	ui.lineEdit->setText(displayValue);
	ui.lineEdit->setEnabled(false);
	this->atype = atype;
	this->otype = otype;
	this->parentId = parentId;
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(slotCellDialog()));
}


CellDelegateWidget::~CellDelegateWidget()
{
}


void CellDelegateWidget::slotCellDialog()
{
	QStandardItemModel treeModel;
	PickTreeDialog dialog(&treeModel, this);	
	if (atype==GlobalInfo::AT_DPSPointLink||atype==GlobalInfo::AT_DPCPointLink||atype==GlobalInfo::AT_MVPointLink||atype==GlobalInfo::AT_APCPointLink)
	{
		dialog.initPointLink(parentId,otype);
		if (dialog.exec()==QDialog::Accepted)
		{
			if (dialog.isClear)
			{
				obId = 0;
				ui.lineEdit->setText("");
				return;
			}
			obId = 0;
			QModelIndexList indexs = dialog.ui.treeView->selectionModel()->selectedIndexes();
			foreach(QModelIndex index,indexs)
			{
				obId = index.data(Qt::UserRole).toULongLong();
			}

			if (obId!=0)
			{
				StringData nameData = "";
				ToolUtil::databaseRead(obId,GlobalInfo::AT_Name,&nameData);
				QString name = QString::fromUtf8(((std::string)nameData).c_str());
				ui.lineEdit->setText(name);
			}			
		}
	}else if (atype==GlobalInfo::AT_AreaOfResponsibilityList){
		dialog.initMultiCheckTreeview(ui.lineEdit->text(),tr("AllAreaOfRes"),GlobalInfo::OT_AreaOfResponsibility,QIcon(":/images/areaofres.png"));
		if (dialog.exec()==QDialog::Accepted)
		{
			if (dialog.isClear)
			{
				obIds.clear();
				ui.lineEdit->setText("");
				return;
			}

			obIds.clear();
			for(int i = 0;i < treeModel.rowCount() ;i++)
			{
				QStandardItem *item = treeModel.item(i);
				TreeUtil::traverseTreeNodes(item, obIds);
			}
			QStringList nameList;
			foreach(QString obId, obIds)
			{
				StringData nameData = "";
				ToolUtil::databaseRead(obId.toULongLong(),GlobalInfo::AT_Name,&nameData);
				QString name = QString::fromUtf8(((std::string)nameData).c_str());
				nameList.append(name);
			}
			ui.lineEdit->setText(nameList.join(","));
		}
	}else if (atype==GlobalInfo::AT_PartitionList||atype==GlobalInfo::AT_IsyncPartitionList){
		dialog.initMultiCheckTreeview(ui.lineEdit->text(),tr("AllPartition"),GlobalInfo::OT_CPSPartition,QIcon(":/images/partition.png"));
		if (dialog.exec()==QDialog::Accepted)
		{
			if (dialog.isClear)
			{
				obIds.clear();
				ui.lineEdit->setText("");
				return;
			}

			obIds.clear();
			for(int i = 0;i < treeModel.rowCount() ;i++)
			{
				QStandardItem *item = treeModel.item(i);
				TreeUtil::traverseTreeNodes(item, obIds);
			}
			QStringList nameList;
			foreach(QString obId, obIds)
			{
				StringData nameData = "";
				ToolUtil::databaseRead(obId.toULongLong(),GlobalInfo::AT_Name,&nameData);
				QString name = QString::fromUtf8(((std::string)nameData).c_str());
				nameList.append(name);
			}
			ui.lineEdit->setText(nameList.join(","));
		}
	}else if (atype==GlobalInfo::AT_ParentClusterList){
		dialog.initMultiCheckTreeview(ui.lineEdit->text(),tr("AllCluster"),GlobalInfo::OT_CPSCluster,QIcon(":/images/cluster.png"));
		if (dialog.exec()==QDialog::Accepted)
		{
			if (dialog.isClear)
			{
				obIds.clear();
				ui.lineEdit->setText("");
				return;
			}

			obIds.clear();
			for(int i = 0;i < treeModel.rowCount() ;i++)
			{
				QStandardItem *item = treeModel.item(i);
				TreeUtil::traverseTreeNodes(item, obIds);
			}
			QStringList nameList;
			foreach(QString obId, obIds)
			{
				StringData nameData = "";
				ToolUtil::databaseRead(obId.toULongLong(),GlobalInfo::AT_Name,&nameData);
				QString name = QString::fromUtf8(((std::string)nameData).c_str());
				nameList.append(name);
			}
			ui.lineEdit->setText(nameList.join(","));
		}
	}else if (atype==GlobalInfo::AT_ServiceTypeList){
		dialog.initMultiCheckTreeview(ui.lineEdit->text(),tr("AllService"),GlobalInfo::OT_ServiceType,QIcon(":/images/servicetype.png"));
		if (dialog.exec()==QDialog::Accepted)
		{
			if (dialog.isClear)
			{
				obIds.clear();
				ui.lineEdit->setText("");
				return;
			}

			obIds.clear();
			for(int i = 0;i < treeModel.rowCount() ;i++)
			{
				QStandardItem *item = treeModel.item(i);
				TreeUtil::traverseTreeNodes(item, obIds);
			}
			QStringList nameList;
			foreach(QString obId, obIds)
			{
				StringData nameData = "";
				ToolUtil::databaseRead(obId.toULongLong(),GlobalInfo::AT_Name,&nameData);
				QString name = QString::fromUtf8(((std::string)nameData).c_str());
				nameList.append(name);
			}
			ui.lineEdit->setText(nameList.join(","));
		}
	}else if (atype==GlobalInfo::AT_TcpHostList||atype==GlobalInfo::AT_PreferredSyncFromList||atype==GlobalInfo::AT_AllowList||atype==GlobalInfo::AT_AccessPointList){
		dialog.initMultiCheckTreeview(ui.lineEdit->text(),tr("AllMachine"),GlobalInfo::OT_Machine,QIcon(":/images/machine.png"));
		if (dialog.exec()==QDialog::Accepted)
		{
			if (dialog.isClear)
			{
				obIds.clear();
				ui.lineEdit->setText("");
				return;
			}

			obIds.clear();
			for(int i = 0;i < treeModel.rowCount() ;i++)
			{
				QStandardItem *item = treeModel.item(i);
				TreeUtil::traverseTreeNodes(item, obIds);
			}
			QStringList nameList;
			foreach(QString obId, obIds)
			{
				StringData nameData = "";
				ToolUtil::databaseRead(obId.toULongLong(),GlobalInfo::AT_Name,&nameData);
				QString name = QString::fromUtf8(((std::string)nameData).c_str());
				nameList.append(name);
			}
			ui.lineEdit->setText(nameList.join(","));
		}
	}else if (atype==GlobalInfo::AT_FaultToleranceLink){
		dialog.initSingleTreeview(tr("AllProtocol"),GlobalInfo::OT_ProtocolType,QIcon(":/images/protocol.png"));
		if (dialog.exec()==QDialog::Accepted)
		{
			if (dialog.isClear)
			{
				obId = 0;
				ui.lineEdit->setText("");
				return;
			}
			obId = 0;
			QModelIndexList indexs = dialog.ui.treeView->selectionModel()->selectedIndexes();
			foreach(QModelIndex index,indexs)
			{
				obId = index.data(Qt::UserRole).toULongLong();
			}

			if (obId!=0)
			{
				StringData nameData = "";
				ToolUtil::databaseRead(obId,GlobalInfo::AT_Name,&nameData);
				QString name = QString::fromUtf8(((std::string)nameData).c_str());
				ui.lineEdit->setText(name);
			}		
		}
	}else if (atype==GlobalInfo::AT_GatewaySpecificationLink){
		dialog.initSingleTreeview(tr("AllSave"),GlobalInfo::OT_GOS,QIcon(":/images/protocol.png"));
		if (dialog.exec()==QDialog::Accepted)
		{
			if (dialog.isClear)
			{
				obId = 0;
				ui.lineEdit->setText("");
				return;
			}
			obId = 0;
			QModelIndexList indexs = dialog.ui.treeView->selectionModel()->selectedIndexes();
			foreach(QModelIndex index,indexs)
			{
				obId = index.data(Qt::UserRole).toULongLong();
			}

			if (obId!=0)
			{
				StringData nameData = "";
				ToolUtil::databaseRead(obId,GlobalInfo::AT_Name,&nameData);
				QString name = QString::fromUtf8(((std::string)nameData).c_str());
				ui.lineEdit->setText(name);
			}		
		}
	}else if (atype==GlobalInfo::AT_ClusterLink){
		dialog.initSingleTreeview(tr("AllCluster"),GlobalInfo::OT_CPSCluster,QIcon(":/images/cluster.png"));
		if (dialog.exec()==QDialog::Accepted)
		{
			if (dialog.isClear)
			{
				obId = 0;
				ui.lineEdit->setText("");
				return;
			}
			obId = 0;
			QModelIndexList indexs = dialog.ui.treeView->selectionModel()->selectedIndexes();
			foreach(QModelIndex index,indexs)
			{
				obId = index.data(Qt::UserRole).toULongLong();
			}

			if (obId!=0)
			{
				StringData nameData = "";
				ToolUtil::databaseRead(obId,GlobalInfo::AT_Name,&nameData);
				QString name = QString::fromUtf8(((std::string)nameData).c_str());
				ui.lineEdit->setText(name);
			}		
		}
	}else if (atype==GlobalInfo::AT_DEVICEID){
		if (GlobalInfo::deviceDialog==NULL)
		{
			GlobalInfo::deviceDialog = new PickTreeDialog(new QStandardItemModel());
		}
		GlobalInfo::deviceDialog->initDeviceTreeview();
		if (GlobalInfo::deviceDialog->exec()==QDialog::Accepted)
		{
			if (GlobalInfo::deviceDialog->isClear)
			{
				obId = 0;
				ui.lineEdit->setText("");
				return;
			}
			obId = 0;
			QModelIndexList indexs = GlobalInfo::deviceDialog->ui.treeView->selectionModel()->selectedIndexes();
			foreach(QModelIndex index,indexs)
			{
				obId = index.data(Qt::UserRole).toULongLong();
			}

			if (obId!=0)
			{
				StringData nameData = "";
				ToolUtil::databaseRead(obId,GlobalInfo::AT_Name,&nameData);
				QString name = QString::fromUtf8(((std::string)nameData).c_str());
				ui.lineEdit->setText(name);
			}			
		}
	}else if (atype==GlobalInfo::AT_MeasurementTypeLink){
		dialog.initMeasurementTypeLinkTreeview(otype);
		if (dialog.exec()==QDialog::Accepted)
		{
			if (dialog.isClear)
			{
				obId = 0;
				ui.lineEdit->setText("");
				return;
			}
			obId = 0;
			QModelIndexList indexs = dialog.ui.treeView->selectionModel()->selectedIndexes();
			foreach(QModelIndex index,indexs)
			{
				obId = index.data(Qt::UserRole).toULongLong();
			}

			if (obId!=0)
			{
				StringData nameData = "";
				ToolUtil::databaseRead(obId,GlobalInfo::AT_Name,&nameData);
				QString name = QString::fromUtf8(((std::string)nameData).c_str());
				ui.lineEdit->setText(name);
			}		
		}
	}else{
		dialog.initCommonTreeview();
		if (dialog.exec()==QDialog::Accepted)
		{
			if (dialog.isClear)
			{
				obId = 0;
				ui.lineEdit->setText("");
				return;
			}
			obId = 0;
			QModelIndexList indexs = dialog.ui.treeView->selectionModel()->selectedIndexes();
			foreach(QModelIndex index,indexs)
			{
				obId = index.data(Qt::UserRole).toULongLong();
			}

			if (obId!=0)
			{
				StringData nameData = "";
				ToolUtil::databaseRead(obId,GlobalInfo::AT_Name,&nameData);
				QString name = QString::fromUtf8(((std::string)nameData).c_str());
				ui.lineEdit->setText(name);
			}			
		}
	}
}