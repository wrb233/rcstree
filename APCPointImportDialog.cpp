#include "APCPointImportDialog.h"
#include "RCSTreeMW.h"

APCPointImportDialog::APCPointImportDialog(QStandardItem* parentItem, QWidget* parent, Qt::WindowFlags flags ): CpsDialog( parent, flags )
{
	ui.setupUi(this);
	initTreeview();
	this->parentItem=parentItem;
}

APCPointImportDialog::~APCPointImportDialog()
{
	delete treeModel;
}

void APCPointImportDialog::initTreeview()
{
	treeModel = new QStandardItemModel(ui.treeView);
	ui.treeView->header()->hide();
	ui.treeView->setModel(treeModel);
	ui.treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.treeView->setSelectionMode(QTreeView::ExtendedSelection);//支持shift ctrl多选
	ui.treeView->setExpandsOnDoubleClick(false);//用于控制鼠标双击是否展开或折叠分支下的子项
	ui.treeView->setExpandsOnDoubleClick(false);
	//构造树start
	updateTreeModel();
	//构造树end
	ui.treeView->setStyleSheet("QTreeView::branch:open:has-children:!has-siblings,""QTreeView::branch:open:has-children:has-siblings {image: url(:images/treeopen2.png);}"
		"QTreeView::branch:has-children:!has-siblings:closed,""QTreeView::branch:closed:has-children:has-siblings {image: url(:images/treeclose4.png);}");
	ui.treeView->setContextMenuPolicy(Qt::CustomContextMenu); 
	connect(ui.treeView, SIGNAL(customContextMenuRequested(const QPoint)), this, SLOT(slotTreeContextMenu(const QPoint)));
	connect(ui.treeView,SIGNAL(expanded ( const QModelIndex)),this,SLOT(slotTreeExpanded(const QModelIndex)));
	connect(ui.treeView,SIGNAL(doubleClicked  (const QModelIndex)),this,SLOT(slotDoubleClickTreeNode(const QModelIndex)));
}

void APCPointImportDialog::updateTreeModel()
{
	treeModel->clear();

	ObId pmsRoot = DBUtil::getRootId();
	if (pmsRoot==0)
	{
		return;
	}
	QStandardItem* allPartitionRoot = new QStandardItem(QIcon(":/images/root.png"),tr("AllPartition"));
	allPartitionRoot->setData(pmsRoot,Qt::UserRole);//id
	allPartitionRoot->setData(1,Qt::UserRole+1);//type
	treeModel->appendRow(allPartitionRoot);
	ui.treeView->expand(allPartitionRoot->index());

	int numOfPartition = ToolUtil::databaseFind(GlobalInfo::OT_CPSPartition, NULL, 0);
	if (numOfPartition>0)
	{
		ObId *obIdOfPartition = new ObId[numOfPartition];
		ToolUtil::databaseFind(GlobalInfo::OT_CPSPartition, NULL, 0, obIdOfPartition, numOfPartition);
		AType AT_Name = ToolUtil::databaseMatchAType("Name");

		for(int i=0;i<numOfPartition;i++)
		{
			StringData nameData = "";
			ToolUtil::databaseRead(obIdOfPartition[i],AT_Name,&nameData);
			QString name = QString::fromUtf8(((std::string)nameData).c_str());
			if (name!=""&&name!="Default")
			{
				QStandardItem* child = new QStandardItem(QIcon(":/images/partition.png"),name);
				child->setData(obIdOfPartition[i],Qt::UserRole);
				child->setData(2,Qt::UserRole+1);
				allPartitionRoot->appendRow(child);
				addTreeItem(child);
			}
		}
	}
}



void APCPointImportDialog::addTreeItem(QStandardItem* parent)
{
	StringData nameData = "";
	StringData descriptionData = "";
	ContainerData childData;
		
	ObId obId = (ObId)(parent->data(Qt::UserRole).toULongLong());
	ToolUtil::databaseRead(obId,GlobalInfo::AT_ChildrenList,&childData);
	int numOfChildData = childData.getNumberOfElements();
	if (numOfChildData > 0) 
	{
		const ObId *obIdOfChild = childData.getObIds();
		for (int j=0;j<numOfChildData;j++)
		{
			ToolUtil::databaseRead(obIdOfChild[j],GlobalInfo::AT_Description,&descriptionData);
			QString description = QString::fromUtf8(((std::string)descriptionData).c_str());

			ToolUtil::databaseRead(obIdOfChild[j],GlobalInfo::AT_Name,&nameData);
			QString name = QString::fromUtf8(((std::string)nameData).c_str());
			
			if (description.startsWith("DS6000_IEDs"))
			{
				QStandardItem* son = new QStandardItem(QIcon(":/images/folder.png"),name);
				son->setData(obIdOfChild[j],Qt::UserRole);
				son->setData(3,Qt::UserRole+1);
				parent->appendRow(son);
			}else if (description.startsWith("GenerateAlarm")){
				QStandardItem* son = new QStandardItem(QIcon(":/images/folder.png"),name);
				son->setData(obIdOfChild[j],Qt::UserRole);
				son->setData(4,Qt::UserRole+1);
				parent->appendRow(son);
			}else if (description.startsWith("ProjectRoot")){//ProjectRoot

				QStandardItem* son = new QStandardItem(name);
				son->setData(obIdOfChild[j],Qt::UserRole);
				addTreeItem(son);
				if (son->hasChildren())
				{
					QStandardItem* grandson = new QStandardItem(QIcon(":/images/folder.png"),son->child(0)->text());
					grandson->setData(son->child(0)->data(Qt::UserRole),Qt::UserRole);
					grandson->setData(3,Qt::UserRole+1);
					parent->appendRow(son);
					parent->removeRow(0);
					parent->appendRow(grandson);
				}
			}
		}
	}				
}


void APCPointImportDialog::slotTreeExpanded(const QModelIndex  index)
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	StringData name;
	char* env = getenv("CPS_ENV");
	QString pathName = QString( env ) + ("/resource/");

	//开始处理
	QStandardItem* parentItem = treeModel->itemFromIndex(index);
	int rowCount = parentItem->rowCount();
	for(int i=0;i<rowCount;i++)
	{
		qDebug()<<parentItem->rowCount();
		QStandardItem* childItem = parentItem->child(i);
		if (!childItem->hasChildren())
		{
			ObId obId = (ObId)(childItem->data(Qt::UserRole).toULongLong());

			//纯粹为了提升树节点展开速度，提升用户体验而增加的特殊逻辑
			if (ToolUtil::databaseExtractOType(obId)==GlobalInfo::OT_DMSCommunicateUnit)
			{
				QStandardItem* defaultItem = new QStandardItem("default");
				childItem->appendRow(defaultItem);
				ui.treeView->setExpanded(childItem->index(),false);
				continue;
			}
			QList<ObId> grandSonList;
			ObId parentObId = (ObId)(parentItem->data(Qt::UserRole).toULongLong());
			if (ToolUtil::databaseExtractOType(parentObId)==GlobalInfo::OT_DMSCommunicateUnit)
			{
				if (!ToolUtil::getChildrenList(parentObId,grandSonList))
				{
					QMessageBox::information( this, tr("error"), tr( "Read child error" ));
					return;
				}
				if (childItem->text()=="default")
				{
					parentItem->removeRow(childItem->row());
					childItem=NULL;
				}
			}else{
				if (!ToolUtil::getChildrenList(obId,grandSonList))
				{
					QMessageBox::information( this, tr("error"), tr( "Read child error" ));
					return;
				}
			}

			QList<ObId> mvpointIds;
			QList<ObId> dpspointIds;
			QList<ObId> dpcpointIds;
			QList<ObId> alarmInstanceIds;
			QList<ObId> obIds;
			foreach(ObId grandSon,grandSonList)
			{
				if (ToolUtil::databaseExtractOType(grandSon)==GlobalInfo::OT_AlarmInstance)
				{
					alarmInstanceIds.append(grandSon);
					//continue;
				}else if (ToolUtil::databaseExtractOType(grandSon)==GlobalInfo::OT_MVPoint)
				{
					mvpointIds.append(grandSon);
				}else if (ToolUtil::databaseExtractOType(grandSon)==GlobalInfo::OT_DPSPoint)
				{
					dpspointIds.append(grandSon);
				}else{
					obIds.append(grandSon);
				}
			}

			if (childItem!=NULL)
			{
				foreach(ObId obid,obIds)
				{
					ToolUtil::databaseRead(obid,GlobalInfo::AT_Name,&name);
					QStandardItem* grandSonItem = new QStandardItem(QString::fromUtf8(((std::string)name).c_str()));
					grandSonItem->setData(obid,Qt::UserRole);					

					if (ToolUtil::databaseExtractOType(obid)==GlobalInfo::OT_DMSCommunicateUnit)
					{
						grandSonItem->setIcon(QIcon(":/images/terminal.png"));
						grandSonItem->setData(4,Qt::UserRole+1);
					}else{
						grandSonItem->setIcon(QIcon(":/images/folder.png"));
						int type = childItem->data(Qt::UserRole+1).toInt();
						grandSonItem->setData(type,Qt::UserRole+1);
					}
					childItem->appendRow(grandSonItem);
				}

				foreach(ObId obid,alarmInstanceIds)
				{
					ToolUtil::databaseRead(obid,GlobalInfo::AT_Name,&name);
					QStandardItem* grandSonItem = new QStandardItem(QIcon(pathName+"AlarmInstance.png"),QString::fromUtf8(((std::string)name).c_str()));
					grandSonItem->setData(obid,Qt::UserRole);
					grandSonItem->setData(4,Qt::UserRole+1);
					childItem->appendRow(grandSonItem);
				}
			}else{
				

				if (mvpointIds.size()>0)
				{
					QStandardItem* mvPointItem = new QStandardItem(QIcon(":/images/folder.png"),tr("MVPoint"));
					mvPointItem->setData(1,Qt::UserRole);
					mvPointItem->setData(4,Qt::UserRole+1);
					parentItem->appendRow(mvPointItem);
					foreach(ObId obid,mvpointIds)
					{
						ToolUtil::databaseRead(obid,GlobalInfo::AT_Name,&name);
						QStandardItem* grandSonItem = new QStandardItem(QIcon(pathName+"MVPoint.png"),QString::fromUtf8(((std::string)name).c_str()));
						grandSonItem->setData(obid,Qt::UserRole);
						grandSonItem->setData(4,Qt::UserRole+1);
						mvPointItem->appendRow(grandSonItem);
					}
				}

				

				
			}
		}
	}
	QApplication::restoreOverrideCursor();
}



void APCPointImportDialog::on_okButton_clicked()
{
	//获取用户挑到的点

	QList<ObId> obIds = getListOfAPCPointObId();
	createRemoteTree(parentItem,parentItem->data(Qt::UserRole).toULongLong(),obIds);
	qDebug()<<obIds.length();
	QMessageBox::information( this, tr("yes"), obIds.length()+tr("add yaoce success"));

}


QList<ObId> APCPointImportDialog::getListOfAPCPointObId()
{	

	QList<ObId> lstObidofdpspoint;
	QModelIndexList indexs = ui.treeView->selectionModel()->selectedIndexes();
	foreach(QModelIndex index,indexs)
	{
		ObId obid = index.data(Qt::UserRole).toULongLong();

		lstObidofdpspoint.append(obid);


	}

	return lstObidofdpspoint;
}




void APCPointImportDialog::createRemoteTree(QStandardItem *parentItem,ObId parentId,QList<ObId> lstObid)
{
	

	try
	{
		

		for(int i=0;i<lstObid.count();i++)
		{
			ObId tmpId = lstObid.at(i);
			if (GlobalInfo::OT_DPSPoint == GlobalInfo::g_Database->extractOType(tmpId))
			{
				ObId _creatObid = GlobalInfo::g_Database->create(parentId,GlobalInfo::OT_RemoteDPSPoint);
				if (_creatObid!=0)
				{
					GlobalInfo::g_Database->markObject(_creatObid);
					writeAttribute(tmpId,_creatObid,lstObid.count());
					appendTreeItem(parentItem,_creatObid);

				}
			}
			else if (GlobalInfo::OT_MVPoint = GlobalInfo::g_Database->extractOType(tmpId))
			{
				ObId _creatObid = GlobalInfo::g_Database->create(parentId,GlobalInfo::OT_RemoteMVPoint);
				if (_creatObid!=0)
				{
					GlobalInfo::g_Database->markObject(_creatObid);
					writeAttribute(tmpId,_creatObid,lstObid.count());
					appendTreeItem(parentItem,_creatObid);
				}
			}
			
		}
	}
	catch(Exception &e)
	{
		std::cout<<"get exception:"<<e.getDescription()<<std::endl;
		return;
	}
}

void APCPointImportDialog::appendTreeItem(QStandardItem *parentItem,ObId curId)
{
	StringData nameData;
	ToolUtil::databaseRead(curId,GlobalInfo::AT_Name,&nameData);
	QString childName = QString::fromUtf8(((std::string)nameData).c_str());

	QStandardItem* childItem = new QStandardItem(childName);
	childItem->setData(curId,Qt::UserRole);

	parentItem->appendRow(childItem);


}

void APCPointImportDialog::writeAttribute(ObId sourceId, ObId dstId, int next)
{

	StringData nameData;
	StringData descriptionData;
	//LinkData PSRLinkData;

	IntegerData j = next+1;
	try
	{
		GlobalInfo::g_Database->read(sourceId,GlobalInfo::AT_Name,&nameData);
		GlobalInfo::g_Database->write(dstId,GlobalInfo::AT_Name,&nameData);

		GlobalInfo::g_Database->read(sourceId,GlobalInfo::AT_Description,&descriptionData);
		GlobalInfo::g_Database->write(dstId,GlobalInfo::AT_Description,&descriptionData);

		//database->read(sourceId,AT_PSRLink,&PSRLinkData);
		//database->write(dstId,AT_ObjectLink,&PSRLinkData);
		GlobalInfo::g_Database->write(dstId,GlobalInfo::AT_ObjOrder,&j);

	}
	catch(Exception &e)
	{
		std::cout<<"get exception:"<<e.getDescription()<<std::endl;
		return;
	}

}	

