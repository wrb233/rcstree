#include "MVPointImportDialog.h"
#include "RCSTreeMW.h"

MVPointImportDialog::MVPointImportDialog(QStandardItem* parentItem, QWidget* parent, Qt::WindowFlags flags ): CpsDialog( parent, flags )
{
	ui.setupUi(this);
	initTreeview();
	this->parentItem=parentItem;
}

MVPointImportDialog::~MVPointImportDialog()
{
	delete treeModel;
}

void MVPointImportDialog::initTreeview()
{
	treeModel = new QStandardItemModel(ui.treeView);
	ui.treeView->header()->hide();
	ui.treeView->setModel(treeModel);
	ui.treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.treeView->setSelectionMode(QTreeView::ExtendedSelection);//支持shift ctrl多选
	ui.treeView->setExpandsOnDoubleClick(false);//用于控制鼠标双击是否展开或折叠分支下的子项
	//构造树start
	updateTreeModel();
	//构造树end
	ui.treeView->setStyleSheet("QTreeView::branch:open:has-children:!has-siblings,""QTreeView::branch:open:has-children:has-siblings {image: url(:images/treeopen2.png);}"
		"QTreeView::branch:has-children:!has-siblings:closed,""QTreeView::branch:closed:has-children:has-siblings {image: url(:images/treeclose4.png);}");
	connect(ui.treeView,SIGNAL(expanded(const QModelIndex)),this,SLOT(slotTreeExpanded(const QModelIndex)));
}

void MVPointImportDialog::updateTreeModel()
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

		for(int i=0;i<numOfPartition;i++)
		{
			StringData nameData = "";
			ToolUtil::databaseRead(obIdOfPartition[i],GlobalInfo::AT_Name,&nameData);
			QString name = QString::fromUtf8(((std::string)nameData).c_str());
			if (name!=""&&name!="Default")
			{
				QStandardItem* child = new QStandardItem(QIcon(":/images/partition.png"),name);
				child->setData(obIdOfPartition[i],Qt::UserRole);
				child->setData(2,Qt::UserRole+1);
				allPartitionRoot->appendRow(child);
				//ui.treeView->expand(child->index());
				addTreeItem(child);
			}
		}
		delete[] obIdOfPartition;
	}
}

void MVPointImportDialog::addTreeItem(QStandardItem* parent)
{
	ContainerData childData;

	ObId obId = (ObId)(parent->data(Qt::UserRole).toULongLong());
	ToolUtil::databaseRead(obId,GlobalInfo::AT_ChildrenList,&childData);
	int numOfChildData = childData.getNumberOfElements();
	if (numOfChildData > 0) 
	{
		const ObId *obIdOfChild = childData.getObIds();
		for (int j=0;j<numOfChildData;j++)
		{
			if (!ToolUtil::isObjectInUserAORSet(obIdOfChild[j]))
			{
				continue;
			}

			StringData nameData = "";
			StringData descriptionData = "";
			ToolUtil::databaseRead(obIdOfChild[j],GlobalInfo::AT_Description,&descriptionData);
			QString description = QString::fromUtf8(((std::string)descriptionData).c_str());
			if (description=="")
			{
				continue;
			}

			ToolUtil::databaseRead(obIdOfChild[j],GlobalInfo::AT_Name,&nameData);
			QString name = QString::fromUtf8(((std::string)nameData).c_str());
			if (name=="")
			{
				continue;
			}
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
			}

			if (description.startsWith("ProjectRoot"))
			{
				QStandardItem* son = new QStandardItem(name);
				son->setData(obIdOfChild[j],Qt::UserRole);
				addTreeItem(son);
				if (son->hasChildren())
				{
					for (int i=0;i<son->rowCount();i++)
					{
						QStandardItem* grandson = new QStandardItem(QIcon(":/images/folder.png"),son->child(i)->text());
						grandson->setData(son->child(i)->data(Qt::UserRole),Qt::UserRole);
						grandson->setData(son->child(i)->data(Qt::UserRole+1),Qt::UserRole+1);				
						parent->appendRow(grandson);
					}
					delete son;
				}
			}	
		}
	}				
}

void MVPointImportDialog::slotTreeExpanded(const QModelIndex  index)
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
			ObId parentObId = (ObId)(parentItem->data(Qt::UserRole).toULongLong());
			//纯粹为了提升树节点展开速度，提升用户体验而增加的特殊逻辑
			QList<ObId> grandSonList;
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

void MVPointImportDialog::on_okButton_clicked()
{
	//获取用户挑到的点
	QList<ObId> obIds = getListOfMVPointObId();
	createRemoteTree(parentItem,parentItem->data(Qt::UserRole).toULongLong(),obIds);
	qDebug()<<obIds.length();
	QMessageBox::information( this, tr("yes"), obIds.length()+tr("add yaoce success"));

}

QList<ObId> MVPointImportDialog::getListOfMVPointObId()
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

void MVPointImportDialog::createRemoteTree(QStandardItem *parentItem,ObId parentId,QList<ObId> lstObid)
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
					writeAttribute(tmpId,_creatObid);
					appendTreeItem(parentItem,_creatObid);

				}
			}
			else if (GlobalInfo::OT_MVPoint = GlobalInfo::g_Database->extractOType(tmpId))
			{
				ObId _creatObid = GlobalInfo::g_Database->create(parentId,GlobalInfo::OT_RemoteMVPoint);
				if (_creatObid!=0)
				{
					GlobalInfo::g_Database->markObject(_creatObid);
					writeAttribute(tmpId,_creatObid);
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

void MVPointImportDialog::appendTreeItem(QStandardItem *parentItem,ObId curId)
{
	StringData nameData;
	ToolUtil::databaseRead(curId,GlobalInfo::AT_Name,&nameData);
	QString childName = QString::fromUtf8(((std::string)nameData).c_str());

	QStandardItem* childItem = new QStandardItem(childName);
	childItem->setData(curId,Qt::UserRole);

	parentItem->appendRow(childItem);


}

void MVPointImportDialog::writeAttribute(ObId sourceId, ObId dstId)
{

	StringData nameData;
	StringData descriptionData;
	//LinkData PSRLinkData;

	try
	{
		GlobalInfo::g_Database->read(sourceId,GlobalInfo::AT_Name,&nameData);
		GlobalInfo::g_Database->write(dstId,GlobalInfo::AT_Name,&nameData);

		GlobalInfo::g_Database->read(sourceId,GlobalInfo::AT_Description,&descriptionData);
		GlobalInfo::g_Database->write(dstId,GlobalInfo::AT_Description,&descriptionData);

		//database->read(sourceId,AT_PSRLink,&PSRLinkData);
		//database->write(dstId,AT_ObjectLink,&PSRLinkData);
		

	}
	catch(Exception &e)
	{
		std::cout<<"get exception:"<<e.getDescription()<<std::endl;
		return;
	}

}	

