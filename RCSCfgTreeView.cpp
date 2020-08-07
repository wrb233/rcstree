#include "RCSCfgTreeView.h"
#include "ToolUtil.h"
#include "DBUtil.h"
#include "AddFolderDialog.h"
#include "TreeUtil.h"

#include "MVPointImportDialog.h"

RCSCfgTreeView::RCSCfgTreeView( QWidget* parent, Qt::WindowFlags flags ): QWidget( parent, flags )
{
	ui.setupUi(this);
	initTreeview();
	initTreePopMenu();
}

RCSCfgTreeView::~RCSCfgTreeView()
{
	if (treeModel!=NULL)
	{
		treeModel->clear();
		delete treeModel;
		treeModel=NULL;
	}	
	delete treePopMenu;
	
	delete actionFresh;
	
	delete actionDelete;

	delete actionAddRemoteStation;
	delete actionAddRemoteAPCPointSection;
	delete actionAddRemoteDPCPointSection;
	delete actionAddRemoteDPSPointSection;
	delete actionAddRemoteMVPointSection;
	delete actionAddRemoteAPCPoint;
	delete actionAddRemoteDPCPoint;
	delete actionAddRemoteDPSPoint;
	delete actionAddRemoteMVPoint;

}

void RCSCfgTreeView::initTreeview()
{
	treeModel = new QStandardItemModel(ui.treeView);
	ui.treeView->header()->hide();
	ui.treeView->setModel(treeModel);
	ui.treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.treeView->setExpandsOnDoubleClick(false);

	//���������start
	updateTreeModel();
	//���������end

	ui.treeView->setStyleSheet("QTreeView::branch:open:has-children:!has-siblings,""QTreeView::branch:open:has-children:has-siblings {image: url(:images/treeopen2.png);}"
		"QTreeView::branch:has-children:!has-siblings:closed,""QTreeView::branch:closed:has-children:has-siblings {image: url(:images/treeclose4.png);}");
	ui.treeView->setContextMenuPolicy(Qt::CustomContextMenu); 
	connect(ui.treeView, SIGNAL(customContextMenuRequested(const QPoint)), this, SLOT(slotTreeContextMenu(const QPoint)));
	connect(ui.treeView,SIGNAL(expanded ( const QModelIndex)),this,SLOT(slotTreeExpanded(const QModelIndex)));
	connect(ui.treeView,SIGNAL(doubleClicked  (const QModelIndex)),this,SLOT(slotDoubleClickTreeNode(const QModelIndex)));
}

void RCSCfgTreeView::initTreePopMenu()
{
	treePopMenu = new QMenu(this);
	
	actionFresh = new QAction(QIcon(":/images/fresh.png"),tr("Fresh"),this); 
	
	actionDelete = new QAction(QIcon(":/images/batchdelete.png"),tr("Delete"),this);


	actionAddRemoteStation =  new QAction(QIcon(":/images/RemoteStation.png"),tr("AddRemoteStation"),this);
	
    //�½�Զ��ͨ������
	actionAddRemoteChannel = new QAction(QIcon(":/images/addremotechannel.png"),tr("AddRemoteChannel"),this);
	
	//�½�Զ��ң���㶯��
	actionAddRemoteAPCPointSection = new QAction(QIcon(":/images/folder.png"),tr("AddRemoteAPCPoint_Section"),this);
	//�½�Զ��ң�ص㶯��
	actionAddRemoteDPCPointSection = new QAction(QIcon(":/images/folder.png"),tr("AddRemoteDPCPoint_Section"),this);
	//�½�Զ��ң�ŵ㶯��
	actionAddRemoteDPSPointSection = new QAction(QIcon(":/images/folder.png"),tr("AddRemoteDPSPoint_Section"),this);
	//�½�Զ��ң��㶯��
	actionAddRemoteMVPointSection = new QAction(QIcon(":/images/folder.png"),tr("AddRemoteMVPoint_Section"),this);



	//�½�Զ��ң���㶯��
	actionAddRemoteAPCPoint = new QAction(QIcon(":/images/RemoteAPCPoint.png"),tr("AddRemoteAPCPoint"),this);
	//�½�Զ��ң�ص㶯��
	actionAddRemoteDPCPoint = new QAction(QIcon(":/images/RemoteDPCPoint.png"),tr("AddRemoteDPCPoint"),this);
	//�½�Զ��ң�ŵ㶯��
	actionAddRemoteDPSPoint = new QAction(QIcon(":/images/RemoteDPSPoint.png"),tr("AddRemoteDPSPoint"),this);
	//�½�Զ��ң��㶯��
	actionAddRemoteMVPoint = new QAction(QIcon(":/images/RemoteMVPoint.png"),tr("AddRemoteMVPoint"),this);


	
	allActions.append(actionFresh);
	
	allActions.append(actionDelete);

	allActions.append(actionAddRemoteStation);
	allActions.append(actionAddRemoteChannel);
	allActions.append(actionAddRemoteAPCPointSection);
	allActions.append(actionAddRemoteDPCPointSection);
	allActions.append(actionAddRemoteDPSPointSection);
	allActions.append(actionAddRemoteMVPointSection);


	allActions.append(actionAddRemoteAPCPoint);
	allActions.append(actionAddRemoteDPCPoint);
	allActions.append(actionAddRemoteDPSPoint);
	allActions.append(actionAddRemoteMVPoint);


	
	connect(actionFresh, SIGNAL(triggered(bool)), this, SLOT(slotTreeFresh()));
	
	connect(actionDelete, SIGNAL(triggered(bool)), this, SLOT(slotTreeDelete()));

	connect(actionAddRemoteAPCPointSection, SIGNAL(triggered(bool)), this, SLOT(slotAddRemoteAPCPointSection()));
	connect(actionAddRemoteDPCPointSection, SIGNAL(triggered(bool)), this, SLOT(slotAddRemoteDPCPointSection()));
	connect(actionAddRemoteDPSPointSection, SIGNAL(triggered(bool)), this, SLOT(slotAddRemoteDPSPointSection()));
	connect(actionAddRemoteMVPointSection, SIGNAL(triggered(bool)), this, SLOT(slotAddRemoteMVPointSection()));

	connect(actionAddRemoteAPCPoint, SIGNAL(triggered(bool)), this, SLOT(slotAddRemoteAPCPoint()));
	connect(actionAddRemoteDPCPoint, SIGNAL(triggered(bool)), this, SLOT(slotAddRemoteDPCPoint()));
	connect(actionAddRemoteDPSPoint, SIGNAL(triggered(bool)), this, SLOT(slotAddRemoteDPSPoint()));
	connect(actionAddRemoteMVPoint, SIGNAL(triggered(bool)), this, SLOT(slotAddRemoteMVPoint()));

}

void RCSCfgTreeView::addTreeItem(QStandardItem* parent)
{
	ObId obId = (ObId)(parent->data(Qt::UserRole).toULongLong());//�����ڵ�
	//����RCS�ڵ�
	int numOfRCS = ToolUtil::databaseFind(GlobalInfo::OT_RCS, NULL, 0);
	if (numOfRCS>0)
	{
		ObId *obIdOfRCS = new ObId[numOfRCS];
		ToolUtil::databaseFind(GlobalInfo::OT_RCS, NULL, 0, obIdOfRCS, numOfRCS);

		for(int i=0;i<numOfRCS;i++)
		{
			/*if (!ToolUtil::isObjectInUserAORSet(obIdOfPartition[i]))
			{
				continue;
			}*/

			StringData nameData = "";
			ToolUtil::databaseRead(obIdOfRCS[i],GlobalInfo::AT_Name,&nameData);
			QString name = QString::fromUtf8(((std::string)nameData).c_str());
			if (name!=""&&name!="Default")
			{
				//ȷ����RCS�ڵ������ڸ÷����µĽڵ�
				if(obId == ToolUtil::ObIdfindOTypeByObIdUP(obIdOfRCS[i],GlobalInfo::OT_CPSPartition,GlobalInfo::OT_CPSPartition))
				{
					QStandardItem* child = new QStandardItem(QIcon(":/images/RCS.png"),name);
					child->setData(obIdOfRCS[i],Qt::UserRole);
					child->setData(3,Qt::UserRole+1);
					//allPartitionRoot->appendRow(child);
					//addTreeItem(child);
					parent->appendRow(child);
				}				
			}
		}
	}
}

void RCSCfgTreeView::updateTreeModel()
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

void RCSCfgTreeView::slotTreeContextMenu(const QPoint pos)
{
	QModelIndex index = ui.treeView->indexAt(pos);
	curTreeItem = treeModel->itemFromIndex(index);

	//��ȡ�û��������obid
	ObId obId= curTreeItem->data(Qt::UserRole).toULongLong();



	if (index.isValid())
	{
		foreach(QAction* action,allActions)
		{
			treePopMenu->removeAction(action);
		}
		int typeOfNode = curTreeItem->data(Qt::UserRole+1).toInt();
		switch(typeOfNode)
		{
		case 1:// ���ڵ�
			{
				treePopMenu->addAction(actionFresh);
				treePopMenu->exec(QCursor::pos());
				break;
			}
		case 2://�����ڵ�
			{
				//treePopMenu->addAction(actionAddDevices);
				//treePopMenu->addAction(actionAddSchematics);
				//treePopMenu->exec(QCursor::pos());
				break;
			}
		case 3: //RCS
			{
				treePopMenu->addAction(actionAddRemoteStation);
				treePopMenu->exec(QCursor::pos());
				break;
			}
		case 4://RemoteStation
			{
				treePopMenu->addAction(actionAddRemoteChannel);

				treePopMenu->addAction(actionAddRemoteAPCPointSection);
				treePopMenu->addAction(actionAddRemoteDPCPointSection);
				treePopMenu->addAction(actionAddRemoteDPSPointSection);
				treePopMenu->addAction(actionAddRemoteMVPointSection);
				//treePopMenu->addAction(actionDelete);
				treePopMenu->exec(QCursor::pos());
				break;
			}
		case 5://Section��Ҫ����ң����ң�ء�ң�š�ң��
			{

				if(ToolUtil::databaseExtractOType(obId) == GlobalInfo::OT_Section)
				{
					IntegerData SectionGroupData;
					ToolUtil::databaseRead(obId,GlobalInfo::AT_SectionGroup,&SectionGroupData);
					if(SectionGroupData == 3){

						treePopMenu->addAction(actionAddRemoteAPCPoint);

						

						treePopMenu->exec(QCursor::pos());
						break;
						
					}

				}

				if(ToolUtil::databaseExtractOType(obId) == GlobalInfo::OT_Section)
				{
					IntegerData SectionGroupData;
					ToolUtil::databaseRead(obId,GlobalInfo::AT_SectionGroup,&SectionGroupData);
					if(SectionGroupData == 2){

						

						treePopMenu->addAction(actionAddRemoteDPCPoint);

						treePopMenu->exec(QCursor::pos());
						break;

					}

				}

				if(ToolUtil::databaseExtractOType(obId) == GlobalInfo::OT_Section)
				{
					IntegerData SectionGroupData;
					ToolUtil::databaseRead(obId,GlobalInfo::AT_SectionGroup,&SectionGroupData);
					if(SectionGroupData == 1){

						

						treePopMenu->addAction(actionAddRemoteDPSPoint);

						treePopMenu->exec(QCursor::pos());
						break;

					}

				}

				if(ToolUtil::databaseExtractOType(obId) == GlobalInfo::OT_Section)
				{
					IntegerData SectionGroupData;
					ToolUtil::databaseRead(obId,GlobalInfo::AT_SectionGroup,&SectionGroupData);
					if(SectionGroupData == 0){


						treePopMenu->addAction(actionAddRemoteMVPoint);

						treePopMenu->exec(QCursor::pos());
						break;

					}

				}


				
			}
		}
	}
}



void RCSCfgTreeView::slotTreeFresh()
{
	updateTreeModel();
}





void RCSCfgTreeView::slotTreeDelete()
{
	ObId currentId = (ObId)(curTreeItem->data(Qt::UserRole).toULongLong());
	int deleteRow = curTreeItem->row();
	actionDelete->setEnabled(false);
	if (currentId==0)
	{
		QMessageBox::information( this, tr("error"), tr( "CurTreeItemId is  invalid!" ));
		actionDelete->setEnabled(true);
		return;
	}

	QMessageBox::StandardButton reply;
	reply = QMessageBox::information(this, tr("save"), tr("Are you sure to delete from DB"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
	if (reply == QMessageBox::No)
	{
		actionDelete->setEnabled(true);
		return;
	}
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	QProgressDialog progressDialog(this);
	QFont font("ZYSong 18030",12);
	progressDialog.setFont(font);
	progressDialog.setWindowModality(Qt::WindowModal);
	progressDialog.setMinimumDuration(5);
	progressDialog.setWindowTitle(tr("Please Wait..."));
	progressDialog.setLabelText(tr("preparing...need to wait a moment"));
	//progressDialog.setCancelButtonText(tr("Cancel"));
	progressDialog.setCancelButton(NULL);
	progressDialog.setRange(0,100);
	progressDialog.show();
	progressDialog.setValue(0);

	QList<ObId> obIds;
	if(!TreeUtil::getAllObIdsByCurrentItem(currentId,obIds))
	{
		QApplication::restoreOverrideCursor();
		QMessageBox::information( this, tr("error"), tr( "Database read id failure!" ));
		actionDelete->setEnabled(true);	
		return;
	}

	int size = obIds.size();
	progressDialog.setRange(0,size);
	progressDialog.setLabelText(tr("deleteting..."));

	int num=1;
	for (int i=size-1;i>=0;i--)
	{
		//qDebug()<<QString::number(obIds[i]);	
		if (ToolUtil::databaseDestroy(obIds[i]))
		{		
			QApplication::processEvents();
			progressDialog.setValue(num);
			num++;
		}else{	

			QApplication::restoreOverrideCursor();
			QMessageBox::information( this, tr("error"), tr( "delete  Failuer!" ));
			updateTreeModel();
			actionDelete->setEnabled(true);
			return;
		}
	}
	curTreeItem->parent()->removeRow(deleteRow);
	actionDelete->setEnabled(true);
	QApplication::restoreOverrideCursor();
	QMessageBox::information( this, tr("info"), tr( "Delete Success!" ));
}




//����Զ��ң����
void RCSCfgTreeView::slotAddRemoteAPCPointSection()
{
	ObId obidOfRemoteStationObid = curTreeItem->data(Qt::UserRole).toULongLong();
	//�ж��ӽڵ��Ƿ��Ѿ���Զ��ң����
	if(!judgeRemoteAPCPointSection(obidOfRemoteStationObid))
	{
		ObId creatRemoteAPCPointObid = GlobalInfo::g_Database->create(obidOfRemoteStationObid,GlobalInfo::OT_Section);
		if (creatRemoteAPCPointObid!=0)
		{
			GlobalInfo::g_Database->markObject(creatRemoteAPCPointObid);

			//д��name����
			QString name = "";
			name = QString::fromLocal8Bit("ң�����");
			StringData nameData = "";
			nameData = name.toUtf8().data();
			GlobalInfo::g_Database->write(creatRemoteAPCPointObid,GlobalInfo::AT_Name,&nameData);
			//д��description����
			StringData descriptionData = "APCPoint_Section";
			GlobalInfo::g_Database->write(creatRemoteAPCPointObid,GlobalInfo::AT_Description,&descriptionData);
			//д��SectionGroup������������
			IntegerData SectionGroupData = 3;//ң��
			GlobalInfo::g_Database->write(creatRemoteAPCPointObid,GlobalInfo::AT_SectionGroup,&SectionGroupData);
		}
	}
	
	initTreeview();	
}
//����Զ��ң�ص�
void RCSCfgTreeView::slotAddRemoteDPCPointSection()
{
	ObId obidOfRemoteStationObid = curTreeItem->data(Qt::UserRole).toULongLong();
	//�ж��ӽڵ��Ƿ��Ѿ���Զ��ң����
	if(!judgeRemoteDPCPointSection(obidOfRemoteStationObid))
	{
		ObId creatRemoteDPCPointObid = GlobalInfo::g_Database->create(obidOfRemoteStationObid,GlobalInfo::OT_Section);
		if (creatRemoteDPCPointObid!=0)
		{
			GlobalInfo::g_Database->markObject(creatRemoteDPCPointObid);

			//д��name����
			QString name = "";
			name = QString::fromLocal8Bit("ң�ص��");
			StringData nameData = "";
			nameData = name.toUtf8().data();
			GlobalInfo::g_Database->write(creatRemoteDPCPointObid,GlobalInfo::AT_Name,&nameData);
			//д��description����
			StringData descriptionData = "DPCPoint_Section";
			GlobalInfo::g_Database->write(creatRemoteDPCPointObid,GlobalInfo::AT_Description,&descriptionData);
			//д��SectionGroup������������
			IntegerData SectionGroupData = 2;//ң��
			GlobalInfo::g_Database->write(creatRemoteDPCPointObid,GlobalInfo::AT_SectionGroup,&SectionGroupData);
		}
	}	
	initTreeview();	
}

//����Զ��ң�ŵ�
void RCSCfgTreeView::slotAddRemoteDPSPointSection()
{
	ObId obidOfRemoteStationObid = curTreeItem->data(Qt::UserRole).toULongLong();
	//�ж��ӽڵ��Ƿ��Ѿ���Զ��ң����
	if(!judgeRemoteDPSPointSection(obidOfRemoteStationObid))
	{
		ObId creatRemoteDPSPointObid = GlobalInfo::g_Database->create(obidOfRemoteStationObid,GlobalInfo::OT_Section);
		if (creatRemoteDPSPointObid!=0)
		{
			GlobalInfo::g_Database->markObject(creatRemoteDPSPointObid);

			//д��name����
			QString name = "";
			name = QString::fromLocal8Bit("ң�ŵ��");
			StringData nameData = "";
			nameData = name.toUtf8().data();
			GlobalInfo::g_Database->write(creatRemoteDPSPointObid,GlobalInfo::AT_Name,&nameData);
			//д��description����
			StringData descriptionData = "DPSPoint_Section";
			GlobalInfo::g_Database->write(creatRemoteDPSPointObid,GlobalInfo::AT_Description,&descriptionData);
			//д��SectionGroup������������
			IntegerData SectionGroupData = 1;//ң��
			GlobalInfo::g_Database->write(creatRemoteDPSPointObid,GlobalInfo::AT_SectionGroup,&SectionGroupData);
		}

	}
	
	initTreeview();	
}

//����Զ��ң���
void RCSCfgTreeView::slotAddRemoteMVPointSection()
{
	ObId obidOfRemoteStationObid = curTreeItem->data(Qt::UserRole).toULongLong();
	//�ж��ӽڵ��Ƿ��Ѿ���Զ��ң����
	if(!judgeRemoteMVPointSection(obidOfRemoteStationObid))
	{
		ObId creatRemoteMVPointObid = GlobalInfo::g_Database->create(obidOfRemoteStationObid,GlobalInfo::OT_Section);
		if (creatRemoteMVPointObid!=0)
		{
			GlobalInfo::g_Database->markObject(creatRemoteMVPointObid);

			//д��name����
			QString name = "";
			name = QString::fromLocal8Bit("ң����");
			StringData nameData = "";
			nameData = name.toUtf8().data();
			GlobalInfo::g_Database->write(creatRemoteMVPointObid,GlobalInfo::AT_Name,&nameData);
			//д��description����
			StringData descriptionData = "MVPoint_Section";
			GlobalInfo::g_Database->write(creatRemoteMVPointObid,GlobalInfo::AT_Description,&descriptionData);
			//д��SectionGroup������������
			IntegerData SectionGroupData = 0;//ң��
			GlobalInfo::g_Database->write(creatRemoteMVPointObid,GlobalInfo::AT_SectionGroup,&SectionGroupData);
		}


	}
	
	initTreeview();	
}

void RCSCfgTreeView::slotAddRemoteAPCPoint()
{	
	APCPointImportDialog dialog(curTreeItem);
	if (dialog.exec()==QDialog::Accepted)
	{
		initTreeview();
	}
}
void RCSCfgTreeView::slotAddRemoteDPCPoint()
{	
	DPCPointImportDialog dialog(curTreeItem);
	if (dialog.exec()==QDialog::Accepted)
	{
		initTreeview();
	}
}
void RCSCfgTreeView::slotAddRemoteDPSPoint()
{	
	DPSPointImportDialog dialog(curTreeItem);
	if (dialog.exec()==QDialog::Accepted)
	{
		initTreeview();
	}
}
void RCSCfgTreeView::slotAddRemoteMVPoint()
{	
	MVPointImportDialog dialog(curTreeItem);
	if (dialog.exec()==QDialog::Accepted)
	{
		initTreeview();
	}
}

void RCSCfgTreeView::slotTreeExpanded(const QModelIndex  index)
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	char* env = getenv("CPS_ENV");
	QString pathName = QString( env ) + ("/resource/");

	//��ʼ����
	QStandardItem* parentItem = treeModel->itemFromIndex(index);
	int rowCount = parentItem->rowCount();
	for(int i=0;i<rowCount;i++)
	{
		qDebug()<<parentItem->rowCount();
		QStandardItem* childItem = parentItem->child(i);
		if (!childItem->hasChildren())
		{
			ObId obId = (ObId)(childItem->data(Qt::UserRole).toULongLong());

			QList<ObId> grandSonList;
			if (!ToolUtil::getChildrenList(obId,grandSonList))
			{
				QApplication::restoreOverrideCursor();
				QMessageBox::information( this, tr("error"), tr( "Read child error" ));
				return;
			}

			foreach(ObId obid,grandSonList)
			{
				StringData nameData = "";
				ToolUtil::databaseRead(obid,GlobalInfo::AT_Name,&nameData);
				QString name = QString::fromUtf8(((std::string)nameData).c_str());
				if (name=="")
				{
					continue;
				}
				QStandardItem* grandSonItem = new QStandardItem(name);
				grandSonItem->setData(obid,Qt::UserRole);					

				if (ToolUtil::databaseExtractOType(obid)==GlobalInfo::OT_RemoteStation)
				{
					grandSonItem->setIcon(QIcon(pathName+"RemoteStation.png"));
					int type = childItem->data(Qt::UserRole+1).toInt()+1; //4
					grandSonItem->setData(type,Qt::UserRole+1);
					childItem->appendRow(grandSonItem);
				}else if (ToolUtil::databaseExtractOType(obid)==GlobalInfo::OT_Section){
					grandSonItem->setIcon(QIcon(":/images/folder.png"));
					int type = childItem->data(Qt::UserRole+1).toInt()+1; //5
					grandSonItem->setData(type,Qt::UserRole+1);
					childItem->appendRow(grandSonItem);
				}else if (ToolUtil::databaseExtractOType(obid)==GlobalInfo::OT_RemoteChannel){
					grandSonItem->setIcon(QIcon(pathName+"RemoteChannel.png"));
					//int type = childItem->data(Qt::UserRole+1).toInt();
					//grandSonItem->setData(type,Qt::UserRole+1);
					childItem->appendRow(grandSonItem);
				}else if (ToolUtil::databaseExtractOType(obid)==GlobalInfo::OT_RemoteAPCPoint){
					grandSonItem->setIcon(QIcon(pathName+"RemoteAPCPoint.png"));
					//int type = childItem->data(Qt::UserRole+1).toInt();
					//grandSonItem->setData(type,Qt::UserRole+1);
					childItem->appendRow(grandSonItem);
				}else if (ToolUtil::databaseExtractOType(obid)==GlobalInfo::OT_RemoteDPCPoint){
					grandSonItem->setIcon(QIcon(pathName+"RemoteDPCPoint.png"));
					//int type = childItem->data(Qt::UserRole+1).toInt();
					//grandSonItem->setData(type,Qt::UserRole+1);
					childItem->appendRow(grandSonItem);
				}else if (ToolUtil::databaseExtractOType(obid)==GlobalInfo::OT_RemoteDPSPoint){
					grandSonItem->setIcon(QIcon(pathName+"RemoteDPSPoint.png"));
					//int type = childItem->data(Qt::UserRole+1).toInt();
					//grandSonItem->setData(type,Qt::UserRole+1);
					childItem->appendRow(grandSonItem);
				}else if (ToolUtil::databaseExtractOType(obid)==GlobalInfo::OT_RemoteMVPoint){
					grandSonItem->setIcon(QIcon(pathName+"RemoteMVPoint.png"));
					//int type = childItem->data(Qt::UserRole+1).toInt();
					//grandSonItem->setData(type,Qt::UserRole+1);
					childItem->appendRow(grandSonItem);
				}
			}
		}
	}
	QApplication::restoreOverrideCursor();
}

void RCSCfgTreeView::slotDoubleClickTreeNode(const QModelIndex index)
{
	QStandardItem* item = treeModel->itemFromIndex(index);
	ObId obId = item->data(Qt::UserRole).toULongLong();
	if (obId==0)
	{
		return;
	}

	emit signalFreshTable(obId);
}



//�жϽڵ�������Զ��ң��
bool RCSCfgTreeView::judgeRemoteAPCPointSection(ObId obidOfRemoteStationObid)
{
	//�ж��ӽڵ��Ƿ��Ѿ���Զ��ң����
	QList<ObId> grandSonList;//ֻ�Һ��ӽڵ�
	ToolUtil::getChildrenList(obidOfRemoteStationObid,grandSonList);
	foreach(ObId obId, grandSonList)
	{
		if(ToolUtil::databaseExtractOType(obId) == GlobalInfo::OT_Section)
		{
			IntegerData SectionGroupData;
			ToolUtil::databaseRead(obId,GlobalInfo::AT_SectionGroup,&SectionGroupData);
			if(SectionGroupData == 3){
				qDebug()<<obId;
				QMessageBox::warning(NULL, tr("warning"), tr("It is not allowed to add more RemoteAPCPiontSection."), QMessageBox::Yes, QMessageBox::Yes);
				return true;
			}
		
		}
	}
	return false;
}
//�жϽڵ�������Զ��ң��
bool RCSCfgTreeView::judgeRemoteDPCPointSection(ObId obidOfRemoteStationObid)
{
	//�ж��ӽڵ��Ƿ��Ѿ���Զ��ң����
	QList<ObId> grandSonList;//ֻ�Һ��ӽڵ�
	ToolUtil::getChildrenList(obidOfRemoteStationObid,grandSonList);
	foreach(ObId obId, grandSonList)
	{
		if(ToolUtil::databaseExtractOType(obId) == GlobalInfo::OT_Section)
		{
			IntegerData SectionGroupData;
			ToolUtil::databaseRead(obId,GlobalInfo::AT_SectionGroup,&SectionGroupData);
			if(SectionGroupData == 2){
				qDebug()<<obId;
				QMessageBox::warning(NULL, tr("warning"), tr("It is not allowed to add more RemoteDPCPiontSection."), QMessageBox::Yes, QMessageBox::Yes);
				return true;
			}
		
		}
	}
	return false;
}
//�жϽڵ�������Զ��ң��
bool RCSCfgTreeView::judgeRemoteDPSPointSection(ObId obidOfRemoteStationObid)
{
	//�ж��ӽڵ��Ƿ��Ѿ���Զ��ң����
	QList<ObId> grandSonList;//ֻ�Һ��ӽڵ�
	ToolUtil::getChildrenList(obidOfRemoteStationObid,grandSonList);
	foreach(ObId obId, grandSonList)
	{
		if(ToolUtil::databaseExtractOType(obId) == GlobalInfo::OT_Section)
		{
			IntegerData SectionGroupData;
			ToolUtil::databaseRead(obId,GlobalInfo::AT_SectionGroup,&SectionGroupData);
			if(SectionGroupData == 1){
				qDebug()<<obId;
				QMessageBox::warning(NULL, tr("warning"), tr("It is not allowed to add more RemoteDPSPiontSection."), QMessageBox::Yes, QMessageBox::Yes);
				return true;
			}
		}
	}
	return false;
}
//�жϽڵ�������Զ��ң��
bool RCSCfgTreeView::judgeRemoteMVPointSection(ObId obidOfRemoteStationObid)
{
	//�ж��ӽڵ��Ƿ��Ѿ���Զ��ң����
	QList<ObId> grandSonList;//ֻ�Һ��ӽڵ�
	ToolUtil::getChildrenList(obidOfRemoteStationObid,grandSonList);
	foreach(ObId obId, grandSonList)
	{
		if(ToolUtil::databaseExtractOType(obId) == GlobalInfo::OT_Section)
		{
			IntegerData SectionGroupData;
			ToolUtil::databaseRead(obId,GlobalInfo::AT_SectionGroup,&SectionGroupData);
			if(SectionGroupData == 0){
				qDebug()<<obId;
				QMessageBox::warning(NULL, tr("warning"), tr("It is not allowed to add more RemoteMVPiontSection."), QMessageBox::Yes, QMessageBox::Yes);
				return true;
			}
		}
		
	}
	return false;
}