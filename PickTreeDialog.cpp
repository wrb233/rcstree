#include "PickTreeDialog.h"

PickTreeDialog::PickTreeDialog( QStandardItemModel* treeModel, QWidget* parent, Qt::WindowFlags flags ): CpsDialog( parent, flags )
{
	ui.setupUi(this);
	ui.treeView->setModel(treeModel);
	this->treeModel = treeModel;
	ui.treeView->header()->hide();	
	ui.treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.treeView->setStyleSheet("QTreeView::branch:open:has-children:!has-siblings,""QTreeView::branch:open:has-children:has-siblings {image: url(:images/treeopen2.png);}"
		"QTreeView::branch:has-children:!has-siblings:closed,""QTreeView::branch:closed:has-children:has-siblings {image: url(:images/treeclose4.png);}");
	
	isClear = false;
	connect(ui.treeView,SIGNAL(expanded ( const QModelIndex)),this,SLOT(slotTreeExpanded(const QModelIndex)));
	connect(ui.clearButton,SIGNAL(clicked()),this,SLOT(clear()));

}

PickTreeDialog::~PickTreeDialog()
{
}

void PickTreeDialog::initMultiCheckTreeview(QString nameList,QString rootName,OType otype,QIcon icon)
{
	QStandardItem* rootItem = new QStandardItem(QIcon(":/images/root.png"),rootName);
	treeModel->appendRow(rootItem);
	ui.treeView->expand(rootItem->index());

	int numOfOtype = ToolUtil::databaseFind(otype, NULL, 0);
	if (numOfOtype>0)
	{
		ObId *obIdOfOtype = new ObId[numOfOtype];
		ToolUtil::databaseFind(otype, NULL, 0, obIdOfOtype, numOfOtype);

		QStringList names = nameList.split(QRegExp("[,]"), QString::KeepEmptyParts);

		for(int i=0;i<numOfOtype;i++)
		{
			StringData nameData = "";
			ToolUtil::databaseRead(obIdOfOtype[i],GlobalInfo::AT_Name,&nameData);
			QString name = QString::fromUtf8(((std::string)nameData).c_str());
			if (name!=""&&name!="Default")
			{
				QStandardItem* child = new QStandardItem(icon,name);
				child->setCheckable(true);
				if (names.contains(name))
				{
					child->setCheckState(Qt::Checked);
				}
				child->setData(obIdOfOtype[i],Qt::UserRole);
				rootItem->appendRow(child);
			}
		}
		delete[] obIdOfOtype;
	}
}

void PickTreeDialog::initSingleTreeview(QString rootName,OType otype,QIcon icon)
{
	QStandardItem* rootItem = new QStandardItem(QIcon(":/images/root.png"),rootName);
	treeModel->appendRow(rootItem);
	ui.treeView->expand(rootItem->index());

	int numOfOtype = ToolUtil::databaseFind(otype, NULL, 0);
	if (numOfOtype>0)
	{
		ObId *obIdOfOtype = new ObId[numOfOtype];
		ToolUtil::databaseFind(otype, NULL, 0, obIdOfOtype, numOfOtype);

		for(int i=0;i<numOfOtype;i++)
		{
			StringData nameData = "";
			ToolUtil::databaseRead(obIdOfOtype[i],GlobalInfo::AT_Name,&nameData);
			QString name = QString::fromUtf8(((std::string)nameData).c_str());
			if (name!=""&&name!="Default")
			{
				QStandardItem* child = new QStandardItem(icon,name);
				child->setData(obIdOfOtype[i],Qt::UserRole);
				rootItem->appendRow(child);
			}
		}
		delete[] obIdOfOtype;
	}
}

void PickTreeDialog::initDeviceTreeview()
{
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
				treeModel->appendRow(child);
				addTreeItem("DS6000_Devices",child);
			}
		}
		delete[] obIdOfPartition;
	}
}

void PickTreeDialog::initCommonTreeview()
{
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
				treeModel->appendRow(child);
				


				ContainerData childData;

				ObId obId = (ObId)(child->data(Qt::UserRole).toULongLong());
				ToolUtil::databaseRead(obId,GlobalInfo::AT_ChildrenList,&childData);
				int numOfChildData = childData.getNumberOfElements();
				if (numOfChildData > 0) 
				{
					const ObId *obIdOfChild = childData.getObIds();
					for (int j=0;j<numOfChildData;j++)
					{
						StringData nameData = "";
						ToolUtil::databaseRead(obIdOfChild[j],GlobalInfo::AT_Name,&nameData);
						QString name = QString::fromUtf8(((std::string)nameData).c_str());
						if (name=="")
						{
							continue;
						}

						QStandardItem* son = new QStandardItem(QIcon(":/images/folder.png"),name);
						son->setData(obIdOfChild[j],Qt::UserRole);
						child->appendRow(son);
					}
				}	
			}
		}
		delete[] obIdOfPartition;
	}
}

void PickTreeDialog::initMeasurementTypeLinkTreeview(OType otype)
{
	ObId obId = 0;
	if (otype==GlobalInfo::OT_MVPoint)
	{
		obId = YC;
	}else if (otype==GlobalInfo::OT_DPSPoint)
	{
		obId = YX;
	}else if (otype==GlobalInfo::OT_DPCPoint)
	{
		obId = YK;
	}else if (otype==GlobalInfo::OT_APCPoint)
	{
		obId = YT;
	}

	if (obId!=0)
	{
		StringData nameData = "";
		ToolUtil::databaseRead(obId,GlobalInfo::AT_Name,&nameData);
		QString name = QString::fromUtf8(((std::string)nameData).c_str());
		QStandardItem* item = new QStandardItem(QIcon(":/images/folder.png"),name);
		item->setData(obId,Qt::UserRole);
		treeModel->appendRow(item);
		ui.treeView->expand(item->index());
		recursiveTreeItem(item);
	}
}

void PickTreeDialog::initPointLink(ObId parentId,OType otype)
{
	char* env = getenv("CPS_ENV");
	QString pathName = QString( env ) + ("/resource/");

	ContainerData childData;
	ToolUtil::databaseRead(parentId,GlobalInfo::AT_ChildrenList,&childData);
	int numOfChildData = childData.getNumberOfElements();
	if (numOfChildData > 0) 
	{
		const ObId *obIdOfChild = childData.getObIds();
		for (int j=0;j<numOfChildData;j++)
		{
			if (otype==GlobalInfo::OT_DPCPoint)
			{
				if (ToolUtil::databaseExtractOType(obIdOfChild[j])==GlobalInfo::OT_DPSPoint)
				{
					StringData nameData = "";
					ToolUtil::databaseRead(obIdOfChild[j],GlobalInfo::AT_Name,&nameData);
					QString name = QString::fromUtf8(((std::string)nameData).c_str());
					if (name=="")
					{
						continue;
					}

					QStandardItem* child = new QStandardItem(QIcon(pathName+"DPSPoint.png"),name);
					child->setData(obIdOfChild[j],Qt::UserRole);
					treeModel->appendRow(child);
				}
			}else if (otype==GlobalInfo::OT_DPSPoint){
				if (ToolUtil::databaseExtractOType(obIdOfChild[j])==GlobalInfo::OT_DPCPoint)
				{
					StringData nameData = "";
					ToolUtil::databaseRead(obIdOfChild[j],GlobalInfo::AT_Name,&nameData);
					QString name = QString::fromUtf8(((std::string)nameData).c_str());
					if (name=="")
					{
						continue;
					}
					QStandardItem* child = new QStandardItem(QIcon(pathName+"DPCPoint.png"),name);
					child->setData(obIdOfChild[j],Qt::UserRole);
					treeModel->appendRow(child);
				}
			}else if (otype==GlobalInfo::OT_APCPoint){
				if (ToolUtil::databaseExtractOType(obIdOfChild[j])==GlobalInfo::OT_MVPoint)
				{
					StringData nameData = "";
					ToolUtil::databaseRead(obIdOfChild[j],GlobalInfo::AT_Name,&nameData);
					QString name = QString::fromUtf8(((std::string)nameData).c_str());
					if (name=="")
					{
						continue;
					}
					QStandardItem* child = new QStandardItem(QIcon(pathName+"MVPoint.png"),name);
					child->setData(obIdOfChild[j],Qt::UserRole);
					treeModel->appendRow(child);
				}
			}else if (otype==GlobalInfo::OT_MVPoint){
				if (ToolUtil::databaseExtractOType(obIdOfChild[j])==GlobalInfo::OT_APCPoint)
				{
					StringData nameData = "";
					ToolUtil::databaseRead(obIdOfChild[j],GlobalInfo::AT_Name,&nameData);
					QString name = QString::fromUtf8(((std::string)nameData).c_str());
					if (name=="")
					{
						continue;
					}
					QStandardItem* child = new QStandardItem(QIcon(pathName+"APCPoint.png"),name);
					child->setData(obIdOfChild[j],Qt::UserRole);
					treeModel->appendRow(child);
				}
			}else{
				if (ToolUtil::databaseExtractOType(obIdOfChild[j])==otype)
				{
					StringData nameData = "";
					ToolUtil::databaseRead(obIdOfChild[j],GlobalInfo::AT_Name,&nameData);
					QString name = QString::fromUtf8(((std::string)nameData).c_str());
					if (name=="")
					{
						continue;
					}
					QStandardItem* child = new QStandardItem(QIcon(pathName+ToolUtil::databaseMatchOName(otype)+".png"),name);
					child->setData(obIdOfChild[j],Qt::UserRole);
					treeModel->appendRow(child);
				}
			}
		}
	}
}

void PickTreeDialog::recursiveTreeItem(QStandardItem* parentItem)
{
	char* env = getenv("CPS_ENV");
	QString pathName = QString( env ) + ("/resource/");

	ObId parentObId = parentItem->data(Qt::UserRole).toULongLong();
	QList<ObId> list;
	ToolUtil::getChildrenList(parentObId, list);
	foreach(ObId obId, list)
	{
		StringData nameData = "";
		ToolUtil::databaseRead(obId,GlobalInfo::AT_Name,&nameData);
		QString name = QString::fromUtf8(((std::string)nameData).c_str());

		QStandardItem* item;
		if (ToolUtil::databaseExtractOType(obId)==GlobalInfo::OT_MeasurementType)
		{
			item = new QStandardItem(QIcon(pathName+"MeasurementType.png"),name);
		}else{
			item = new QStandardItem(QIcon(":/images/folder.png"),name);
		}
		item->setData(obId,Qt::UserRole);
		parentItem->appendRow(item);
		recursiveTreeItem(item);
	}
}

void PickTreeDialog::addTreeItem(QString filter, QStandardItem* parent)
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

			if (description.startsWith(filter))
			{
				QStandardItem* son = new QStandardItem(QIcon(":/images/folder.png"),name);
				son->setData(obIdOfChild[j],Qt::UserRole);
				parent->appendRow(son);
			}else if (description.startsWith("ProjectRoot")){//ProjectRoot
				QStandardItem* son = new QStandardItem(name);
				son->setData(obIdOfChild[j],Qt::UserRole);
				addTreeItem(filter,son);
				if (son->hasChildren())
				{
					QStandardItem* grandson = new QStandardItem(QIcon(":/images/folder.png"),son->child(0)->text());
					grandson->setData(son->child(0)->data(Qt::UserRole),Qt::UserRole);
					parent->appendRow(son);
					parent->removeRow(0);
					parent->appendRow(grandson);
				}
			}
		}
	}				
}

void PickTreeDialog::slotTreeExpanded(const QModelIndex  index)
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

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

			QList<ObId> grandSonList;
			if (!ToolUtil::getChildrenList(obId,grandSonList))
			{
				QApplication::restoreOverrideCursor();
				QMessageBox::information( this, tr("error"), tr( "Read child error" ));
				return;
			}

			foreach(ObId grandSon,grandSonList)
			{
				StringData nameData = "";
				ToolUtil::databaseRead(grandSon,GlobalInfo::AT_Name,&nameData);
				QString name = QString::fromUtf8(((std::string)nameData).c_str());
				if (name=="")
				{
					continue;
				}

				OType otype = ToolUtil::databaseExtractOType(grandSon);
				QStandardItem* grandSonItem = new QStandardItem(QIcon(pathName+ToolUtil::databaseMatchOName(otype)+".png"),name);
				grandSonItem->setData(grandSon,Qt::UserRole);
				childItem->appendRow(grandSonItem);
			}
		}
	}
	QApplication::restoreOverrideCursor();
}

void PickTreeDialog::clear()
{
	isClear = true;
	accept();
	this->close();
}