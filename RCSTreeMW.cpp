#include "RCSTreeMW.h"

RCSTreeMW::RCSTreeMW( QWidget* parent, Qt::WindowFlags flags ): CpsMainWindow( parent, flags )
{
	//resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
	ui.setupUi(this);//初始化界面	
	initMenuBar();//初始化菜单栏
	initToolBar();//初始化工具栏
	initStatusBar();//初始化状态栏

	initTreeview();//初始化树视图
	initTreeRootPopMenu();//初始化树根节点右键菜单
	initTreeFolderPopMenu();//初始化树目录右键菜单
	initTreeLeafPopMenu();//初始化树叶子右键菜单
	initTreePartitionPopMenu();//初始化分区树右键菜单

	ui.treeView->setParent(NULL);
	
	rcsCfgTreeView = new RCSCfgTreeView(this);
	rcsCfgTreeView->setMinimumWidth(100);
	ui.verticalLayout->addWidget(rcsCfgTreeView);

	centerWidget = new CenterTableView(this);
	ui.horizontalLayout->addWidget(centerWidget);

	connect(rcsCfgTreeView, SIGNAL(signalFreshTable(ObId)), centerWidget, SLOT(slotTableFresh(ObId)));
	connect(centerWidget, SIGNAL(signalFreshTree()), rcsCfgTreeView, SLOT(slotTreeFresh()));


	QPalette pal(this->palette());
	pal.setColor(QPalette::Background, Qt::white); //设置背景黑色
	this->setAutoFillBackground(true);
	this->setPalette(pal);
}

RCSTreeMW::~RCSTreeMW()
{
	delete treeModel;

	delete RCSEidtBar;

	delete msgLabel;
	delete treeRootPopMenu;
	delete treeFolderPopMenu;
	delete treeLeafPopMenu;
	delete treePartitionPopMenu;
	delete rcsCfgTreeView;
	delete centerWidget;
	//delete partitionTree;
	//delete partitionTable;
}


void RCSTreeMW::initMenuBar()
{
	QMenu *pMenuBarFile= new QMenu(QString(tr("help")+"(&H)"));
	QAction *pActionHelp = new QAction(QString("open"), this);
	pActionHelp->setIcon(QIcon(":/images/one.png"));
	pActionHelp->setShortcut(Qt::CTRL | Qt::Key_H);
	pMenuBarFile->addAction(pActionHelp);
	ui.menubar->addMenu(pMenuBarFile);
}
void RCSTreeMW::initToolBar()
{
	//数据挑点-工具栏
	QToolBar* pToolBar = addToolBar(tr("toolBar"));
	QFont font;
	font.setPixelSize(10);
	pToolBar->setFont(font);
	
	RCSEidtBar = new QToolButton(this);
	RCSEidtBar->setIcon(QIcon(":/images/rcsedit.png"));
	RCSEidtBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	RCSEidtBar->setText(tr("RCSEdit"));
	RCSEidtBar->setCheckable(true);
	RCSEidtBar->setChecked(true);
	RCSEidtBar->setAutoExclusive(true);
	
	pToolBar->addWidget(RCSEidtBar);
	pToolBar->addSeparator();
	connect(RCSEidtBar, SIGNAL(clicked()),this, SLOT(slotRCSEdit()));

	
}

void RCSTreeMW::initStatusBar()
{
	msgLabel = new QLabel; 
	//textStatusbar = tr("TotalNum:");
	QString text = QString("%1").arg(0);
	msgLabel->setText(textStatusbar+text);
	msgLabel->setMinimumSize(msgLabel->sizeHint()); 
	msgLabel->setAlignment(Qt::AlignRight); 
	ui.statusbar->setStyleSheet(QString("QStatusBar::item{border: 0px}"));
	ui.statusbar->addPermanentWidget(msgLabel);	
}

void RCSTreeMW::initTreeview()
{
	treeModel = new QStandardItemModel(ui.treeView);
	ui.treeView->header()->hide();
	ui.treeView->setModel(treeModel);
	ui.treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.treeView->setSelectionMode(QTreeView::ExtendedSelection);
	
	QStandardItem* allTable = new QStandardItem(tr("allTable"));//树根节点
	allTable->setData(0,Qt::UserRole);//id
	allTable->setData(0,Qt::UserRole+1);//type
	treeModel->appendRow(allTable);

	if (DBUtil::checkTable("C_COMCFG_TABLE"))
	{
		addTreeItem(allTable)	;
	}else{
		//弹出提示框
		QMessageBox::information( this, tr("error"), tr( "Table is not existed" ));
	}
	//ui.treeView->setExpandsOnDoubleClick(false);
	ui.treeView->expandAll();
	ui.treeView->setContextMenuPolicy(Qt::CustomContextMenu);  //设置枚举值
	connect(ui.treeView, SIGNAL(customContextMenuRequested(const QPoint)), this, SLOT(slotTreeContextMenu(const QPoint)));
	connect(ui.treeView,SIGNAL(doubleClicked  (const QModelIndex)),this,SLOT(slotDoubleClickTreeNode(const QModelIndex)));
	
}

void RCSTreeMW::addTreeItem(QStandardItem* item)
{
	RECORDSETHANDLE recordsetHandle = CPS_ORM_RsNewRecordSet();
	try
	{
		if (DBUtil::UpdateConnectDB())
		{
			QString sql = "select t.id,t.name,t.type from c_comcfg_table t where t.parentid=%1 order by t.orderno";
			sql = sql.arg((item->data(Qt::UserRole)).toLongLong());
			//qDebug()<<sql;

			int rows = CPS_ORM_RsLoadData(recordsetHandle, sql.toUtf8().data(), GlobalInfo::g_DBPoolHandle);
			if (rows>0)
			{
				for (int i=0;i<rows;i++)
				{
					qlonglong id = (qlonglong)CPS_ORM_RsGetNumberValue(recordsetHandle, i, 0);
					QString name = QString::fromUtf8(CPS_ORM_RsGetStringValue(recordsetHandle, i, 1).c_str());
					int type = (int)CPS_ORM_RsGetNumberValue(recordsetHandle, i, 2);

					QStandardItem* childItem = new QStandardItem(name);
					childItem->setData(id,Qt::UserRole);
					childItem->setData(type,Qt::UserRole+1);
					item->appendRow(childItem);
					addTreeItem(childItem);
				}
			}			
		}
	}
	catch (Exception& e)
	{
		qDebug()<<"addTreeItem FAILURE Exception!";
	}
	CPS_ORM_RsFreeRecordSet(recordsetHandle);
}

void RCSTreeMW::initTreeRootPopMenu()
{
	treeRootPopMenu = new QMenu(ui.treeView);
	QAction *actionAddFolder = new QAction(NULL);
	QAction *actionImportTable = new QAction(NULL);
	actionAddFolder ->setText(tr("AddFolder"));
	actionImportTable ->setText(tr("ImportTable"));
	connect(actionAddFolder, SIGNAL(triggered(bool)), this, SLOT(slotTreeAddFolder()));
	connect(actionImportTable, SIGNAL(triggered(bool)), this, SLOT(slotTreeImportTable()));
	treeRootPopMenu->addAction(actionAddFolder);
	treeRootPopMenu->addAction(actionImportTable);
}

void RCSTreeMW::initTreeFolderPopMenu()
{
	treeFolderPopMenu = new QMenu(ui.treeView);
	QAction *actionAddFolder = new QAction(NULL);
	QAction *actionImportTable = new QAction(NULL);
	QAction *actionDelete = new QAction(NULL);
	actionAddFolder ->setText(tr("AddFolder"));
	actionImportTable ->setText(tr("ImportTable"));
	actionDelete->setText(tr("Delete"));
	connect(actionAddFolder, SIGNAL(triggered(bool)), this, SLOT(slotTreeAddFolder()));
	connect(actionImportTable, SIGNAL(triggered(bool)), this, SLOT(slotTreeImportTable()));
	connect(actionDelete, SIGNAL(triggered(bool)), this, SLOT(slotTreeDelete()));
	treeFolderPopMenu->addAction(actionAddFolder);
	treeFolderPopMenu->addAction(actionImportTable);
	treeFolderPopMenu->addAction(actionDelete);
}

void RCSTreeMW::initTreeLeafPopMenu()
{
	treeLeafPopMenu = new QMenu(ui.treeView);
	QAction *actionLoadTable = new QAction(NULL);
	QAction *actionDelete = new QAction(NULL);
	actionLoadTable ->setText(tr("LoadTable"));
	actionDelete->setText(tr("Delete"));
	connect(actionLoadTable, SIGNAL(triggered(bool)), this, SLOT(slotTreeLoadTable()));
	connect(actionDelete, SIGNAL(triggered(bool)), this, SLOT(slotTreeDelete()));
	treeLeafPopMenu->addAction(actionLoadTable);
	treeLeafPopMenu->addAction(actionDelete);
}

void RCSTreeMW::initTreePartitionPopMenu()
{
	treePartitionPopMenu = new QMenu(ui.treeView);
	QAction *actionSetPartition = new QAction(NULL);
	QAction *actionBatchImportNew = new QAction(NULL);
	QAction *actionCopy = new QAction(NULL);
	QAction *actionPaste = new QAction(NULL);
	QAction *actionBatchPaste = new QAction(NULL);
	QAction *actionPartitionExport = new QAction(NULL);
	QAction *actionPartitionImport = new QAction(NULL);
	actionSetPartition ->setText(tr("SetPartition"));
	actionBatchImportNew ->setText(tr("BatchImportNew"));
	actionCopy ->setText(tr("Copy"));
	actionPaste ->setText(tr("Paste"));
	actionBatchPaste ->setText(tr("BatchPaste"));
	actionPartitionExport ->setText(tr("PartitionExport"));
	actionPartitionImport ->setText(tr("PartitionImport"));
	connect(actionSetPartition, SIGNAL(triggered(bool)), this, SLOT(slotTreeAddFolder()));
	connect(actionBatchImportNew, SIGNAL(triggered(bool)), this, SLOT(slotTreeAddFolder()));
	connect(actionCopy, SIGNAL(triggered(bool)), this, SLOT(slotTreeAddFolder()));
	connect(actionPaste, SIGNAL(triggered(bool)), this, SLOT(slotTreeAddFolder()));
	connect(actionBatchPaste, SIGNAL(triggered(bool)), this, SLOT(slotTreeAddFolder()));
	connect(actionPartitionExport, SIGNAL(triggered(bool)), this, SLOT(slotTreeAddFolder()));
	connect(actionPartitionImport, SIGNAL(triggered(bool)), this, SLOT(slotTreeAddFolder()));
	treePartitionPopMenu->addAction(actionSetPartition);
	treePartitionPopMenu->addAction(actionBatchImportNew);
	treePartitionPopMenu->addAction(actionCopy);
	treePartitionPopMenu->addAction(actionPaste);
	treePartitionPopMenu->addAction(actionBatchPaste);
	treePartitionPopMenu->addAction(actionPartitionExport);
	treePartitionPopMenu->addAction(actionPartitionImport);
}

void RCSTreeMW::freshStatusBar(int dataNum)
{
	QString text = QString("%1").arg(dataNum);
	msgLabel->setText(textStatusbar+text);
}

bool RCSTreeMW::insertTreeNodesToDB()
{
	return true;
}

bool RCSTreeMW::deleteTreeNodeFromDB()
{
	return true;
}

void RCSTreeMW::slotRCSEdit()
{
	if(checkNumOfRCS()==0)
	{
		QMessageBox::warning(NULL, tr("warning"), tr("RCS node not found, please add RCS node in appropriate directory!"), QMessageBox::Yes, QMessageBox::Yes);
	}
	else if(checkNumOfRCS()==1)
	{
		
	}
	else if(checkNumOfRCS()>=2)
	{
		QMessageBox::warning(NULL, tr("warning"), tr("There are two or more RCS objects in all partition, please check the configuration library!"), QMessageBox::Yes, QMessageBox::Yes);
	}
	
	ui.verticalLayout->addWidget(rcsCfgTreeView);
	rcsCfgTreeView->updateTreeModel();
	centerWidget->freshTableview(0);
}

void RCSTreeMW::slotDoubleClickTreeNode(const QModelIndex index)
{
	//QStandardItemModel *model= static_cast<QStandardItemModel*>(ui.treeView->model());
	qDebug()<<treeModel->itemFromIndex(index)->text();
	curTreeItem = treeModel->itemFromIndex(index);
	//((CenterTableWidget*)this->centralWidget())->freshTableviewData(curTreeItem->text());
	switch(currentType)
	{
	case ENUM_TABLE_MODE:
		{
			centerWidget->freshCommonTableview(curTreeItem->text());break;
		}
	case ENUM_TERMINAL_EDIT:
		{
			//int currentIndex = partition->getUi().tabWidget->currentIndex();
			//CenterTableWidget* table = (CenterTableWidget*)(partition->getUi().tabWidget->widget(currentIndex));
			//table->freshTableviewData(curTreeItem->text());
			break;
		}
	}
	
}

void RCSTreeMW::slotTreeContextMenu(const QPoint pos)
{
	QModelIndex index = ui.treeView->indexAt(pos);
    curTreeItem = treeModel->itemFromIndex(index);
	switch(currentType)
	{
	case ENUM_TABLE_MODE:
		{
			if (index.isValid())
			{
				int typeOfNode = curTreeItem->data(Qt::UserRole+1).toInt();
				switch(typeOfNode)
				{
				case 0:treeRootPopMenu->exec(QCursor::pos()); break;
				case 1:treeFolderPopMenu->exec(QCursor::pos()); break;
				case 2:treeLeafPopMenu->exec(QCursor::pos()); break;
				}
			}
			break;
		}
	case ENUM_TERMINAL_EDIT:
		{
			treePartitionPopMenu->exec(QCursor::pos());
			break;
		}
	}
}

void RCSTreeMW::slotTreeAddFolder()
{
	AddFolderDialog dialog(this);
	dialog.show();
	if (dialog.exec()==QDialog::Accepted)
	{
		curTreeItem->appendRow(new QStandardItem(dialog.getText()));
		QString sql = "insert into C_COMCFG_TABLE (id,parentid,type,name,orderno) values(%1,%2,%3,%4,%5)";
		sql = sql.arg("1").arg("0").arg("0").arg("'"+dialog.getText()+"'").arg("0");

		DBUtil::executeSQL(sql);
	}
}


void RCSTreeMW::slotTreeLoadTable()
{
	//((CenterTableWidget*)this->centralWidget())->freshTableviewData(curTreeItem->text());
	centerWidget->freshCommonTableview(curTreeItem->text());
}

void RCSTreeMW::slotTreeDelete()
{
	curTreeItem->parent()->removeRow(curTreeItem->row());
}

void RCSTreeMW::slotTreeExpanded(const QModelIndex  index)
{
	QStandardItem* parentItem = treeModel->itemFromIndex(index);
	for(int i=0;i<parentItem->rowCount();i++)
	{
		QStandardItem* childItem = parentItem->child(i);
		if (!childItem->hasChildren())
		{
			ObId obId = (ObId)(childItem->data(Qt::UserRole).toLongLong());
			QList<ObId> grandSonList;
			ToolUtil::getChildrenList(obId,grandSonList);
			foreach(ObId grandSon,grandSonList)
			{
				StringData name;
				AType AT_Name = ToolUtil::databaseMatchAType("Name");
				ToolUtil::databaseRead(grandSon,AT_Name,&name);
				QStandardItem* grandSonItem = new QStandardItem(QString::fromUtf8(((std::string)name).c_str()));
				grandSonItem->setData(grandSon,Qt::UserRole);
				childItem->appendRow(grandSonItem);
			}
		}
	}
}

void RCSTreeMW::closeTab()
{
	
	if(this->UserCheck())
	{
		qDebug()<<1;
	}
	
	//ui.tabWidget->clear();
	//delete ui.treeView;
	
	//ui.tabWidget->removeTab(index);
}

void RCSTreeMW::keyPressEvent(QKeyEvent *e)
{
	if (e->modifiers() == (Qt::ShiftModifier | Qt::ControlModifier) && e->key() == Qt::Key_A)
	{
		qDebug()<<"ctrl+shif+A";
	}
	if (e->modifiers() == Qt::ControlModifier&& e->key() == Qt::Key_Z)
	{
		qDebug()<<"ctrl+Z";
	}	
}

void RCSTreeMW::closeEvent(QCloseEvent* event)
{
	qDebug()<<"normal exit";
	//当文档内容被修改时.
	//if (ui.textEdit->document()->isModified())
	//{
	//	//跳出信息框，你是否要关闭.
	//	auto temp = QMessageBox::information(this, "tooltip", QString::fromLocal8Bit("你是否要关闭?"), QMessageBox::Yes | QMessageBox::No);
	//	if (temp == QMessageBox::Yes)
	//	{
	//		// 接受了 要关闭这个窗口的事件. accept和ignore只是作为一个标志.
	//		event->accept();
	//	}
	//	else
	//	{
	//		//忽略了 要关闭这个窗口的事件.当前窗口就不会被关闭.
	//		event->ignore();
	//	}
	//}
	//else
	//{
	//	event->accept();
	//}

	if (GlobalInfo::g_WriteDatas.size()>0||GlobalInfo::g_InsertDatas.size()>0||GlobalInfo::g_DeleteDatas.size()>0)
	{
		QMessageBox::StandardButton reply;
		reply = QMessageBox::information(this, tr("save"), tr("You have changed data ,save?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		if (reply == QMessageBox::Yes)
		{
			//保存新增
			int i=0;
			foreach(InsertData insertData, GlobalInfo::g_InsertDatas)
			{
				ObId newId = GlobalInfo::g_Database->create(insertData.parentId,insertData.otype);
				insertData.insertDatas.at(i)->setData(newId,Qt::UserRole);
			}

			foreach(InsertData insertData, GlobalInfo::g_InsertDatas)
			{
				ToolUtil::tableSave(insertData.insertDatas);	
			}

			//保存修改
			ToolUtil::tableSave(GlobalInfo::g_WriteDatas);	

			//保存删除
			foreach(ObId deleteObId,GlobalInfo::g_DeleteDatas)
			{
				ToolUtil::databaseDestroy(deleteObId);
			}
		}
	}
}

bool RCSTreeMW::UserCheck()
{
	if (GlobalInfo::g_User)
	{
		GlobalInfo::g_User->initUserMSData(GlobalInfo::g_Database, CONFIG_ENVIRONMENT);

		UserObjectData UserData;
		memset(&UserData, 0, sizeof(UserObjectData));
		std::string strPermission = "DbDefine";
		std::string strTitle = std::string(QObject::tr("Login").toUtf8().constData());

		bool bPass = false;
		bPass = (GlobalInfo::g_User && GlobalInfo::g_User->ds6k_checkUser(UserData, strPermission, NULL, strTitle));
		if (!bPass)
		{
			std::cout << "user check fail!" << std::endl;
			return false;
		}
		GlobalInfo::g_Database->setUser(UserData.objectID);

		ObId systemUser = UserData.objectID;
		if (systemUser == 0)
		{
			std::cout << "System User Id is error!" << std::endl;
			::exit(-1);
		}
		(static_cast<ORMDatabase*>(GlobalInfo::g_Database))->setSystemUserId(GlobalInfo::g_Database->extractOCell(systemUser));
	}
	else
	{
		std::cout << "init UserMS fault!" << std::endl;
		return false;
	}
	return true;
}


int RCSTreeMW::checkNumOfRCS()
{
	int k = 0;//记录某一分区下的RCS节点数量
	int numOfRCS = ToolUtil::databaseFind(GlobalInfo::OT_RCS, NULL, 0);
	if (numOfRCS>0)
	{
		ObId *obIdOfRCS = new ObId[numOfRCS];
		ToolUtil::databaseFind(GlobalInfo::OT_RCS, NULL, 0, obIdOfRCS, numOfRCS);
		for(int i=0;i<numOfRCS;i++)
		{
			/*StringData nameData = "";
			ToolUtil::databaseRead(obIdOfRCS[i],GlobalInfo::AT_Name,&nameData);
			QString name = QString::fromUtf8(((std::string)nameData).c_str());
			if (name=="RCS")
			{
				k++;
			}*/
			if(ToolUtil::databaseExtractOType(obIdOfRCS[i]) == GlobalInfo::OT_RCS)
			{
				k++;
			}
		}
	}
	return k;
}