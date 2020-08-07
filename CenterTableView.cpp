#include "CenterTableView.h"
#include "TableDelegate.h"
#include "CBatchVerticalHeaderView.h"
#include "MyEnum.h"
#include "DBUtil.h"
#include "GlobalInfo.h"
#include "BatchComboxDialog.h"
#include "BatchLineEditDialog.h"
#include "MyQProgressDialog.h"

CenterTableView::CenterTableView( QWidget* parent, Qt::WindowFlags flags ): CpsWidget( parent, flags )
{
	ui.setupUi(this);
	GlobalInfo::g_SaveButton = ui.saveButton;
	GlobalInfo::g_SaveButton->hide();
	initPushButton();
	initTableview();
	initTablePopMenu();



	/*ui.tabWidget->setStyleSheet("QTabWidget::pane{border-width:1px;border-color:rgb(48, 104, 151);\
								border-style: outset;background-color: rgb(132, 171, 208);\
								background: transparent;} \
								QTabWidget::tab-bar{border-width:0px;}\
								QTabBar::tab{border-bottom-color: #C2C7CB;\
								border-top-left-radius: 0px;\
								border-top-right-radius: 0px;\
								max-width: 75px; min-width:75px; min-height:25px;\
								font:14px Times New Roman;\
								padding: 0px;\
								}\
								QTabBar::scroller {\
								width:25;\
								border:0;\
								padding: 0px;\
								}\
								QTabBar QToolButton::right-arrow {\
								background-color:rgb(132, 171, 208);\
								border-width: 0;\
								background-image: url(:/images/tab/rightbtn.png);\
								}\
								QTabBar QToolButton::right-arrow:hover {\
								background-color:rgb(132, 171, 208);\
								border-width: 0;\
								background-image: url(:/images/tab/hoverrightbtn.png);\
								}\
								QTabBar QToolButton::right-arrow:disabled {\
								background-color:rgb(132, 171, 208);\
								border-width: 0;\
								background-image: url(:/images/tab/grayrightbtn.png);\
								}\
								QTabBar QToolButton::left-arrow {\
								background-color:rgb(132, 171, 208);\
								border-width: 0;\
								background-image: url(:/images/tab/leftbtn.png);\
								}\
								QTabBar QToolButton::left-arrow:hover {\
								background-color:rgb(132, 171, 208);\
								border-width: 0;\
								background-image: url(:/images/tab/hoverleftbtn.png);\
								}\
								QTabBar QToolButton::left-arrow:disabled {\
								background-color:rgb(132, 171, 208);\
								border-width: 0;\
								background-image: url(:/images/tab/grayleftbtn.png);\
								}\
								QTabBar::tab:first:selected {\
								margin-left: 30; margin-right: 0;\
								color: white;\
								border-image: url(:/images/tab/sel3.png);\
								}\
								QTabBar::tab:first:!selected {\
								color: black;\
								margin-left: 30; margin-right: 0;\
								border-image: url(:/images/tab/normal3.png);\
								}\
								QTabBar::tab:first:hover:!selected {\
								color: black;\
								margin-left: 30; margin-right: 0;\
								border-image: url(:/images/tab/hover3.png);\
								}\
								QTabBar::tab:middle:selected {\
								margin-top: 0; margin-left: -15; margin-right: 8;\
								color: white;\
								border-image: url(:/images/tab/sel3.png);\
								}\
								QTabBar::tab:middle:!selected {\
								color: black;\
								margin-top: 0; margin-left: -15; margin-right: 8;\
								border-image: url(:/images/tab/normal3.png);\
								}\
								QTabBar::tab:middle:hover:!selected {\
								color: black;\
								margin-top: 0; margin-left: -15; margin-right: 8;\
								border-image: url(:/images/tab/hover3.png);\
								}\
								QTabBar::tab:last:selected {\
								margin-top: 0px; margin-left: 0; margin-right: 0;\
								color: white;\
								border-image: url();\
								}\
								QTabBar::tab:last:!selected {\
								color: black;\
								margin-top: 0; margin-left: 0; margin-right: 0;\
								border-image: url();\
								}\
								QTabBar::tab:last:hover:!selected {\
								color: black;\
								margin-top: 0; margin-left: 0; margin-right: 0;\
								border-image: url();\
								}\
								QTabBar::tab:only-one {\
								margin: 0;\
								}");*/

	QString tabBarStyle = "QTabWidget::pane{border-width:1px;border-top-width:0px;border-color:rgb(48, 104, 151);\
						   border-style: outset;background: white;} \
                           QTabWidget::tab-bar{\
                           alignment:left;}\
                           QTabBar::tab{\
                           background:rgb(18,133,237);\
                           min-width:100px;color: white;border: 1.5px solid;border-color: rgb(188,199,216);\
						   border-bottom: 0px solid;border-top-left-radius: 10px;\
						   border-top-right-radius: 10px;padding:5px;\
                           border-style: outset;}\
                           QTabBar::tab:hover{\
						   background:rgb(124,171,249);}\
						   QTabBar::tab:!selected {margin-top: 5px;color:white} \
                           QTabBar::tab:selected{\
	                       border-color: rgb(48, 104, 151);\
                           background:rgb(18,133,237);\
                           color:white;}";
	ui.tabWidget->setStyleSheet(tabBarStyle);
	
}

Ui::CenterTableUI CenterTableView::getUi()
{
	return ui;
}

CenterTableView::~CenterTableView()
{
	if (tableModel!=NULL)
	{
		tableModel->clear();
		delete tableModel;
		tableModel=NULL;
	}	
	delete tablePopMenu;
	delete actionUpdateColum;
	delete actionInsertOneRow;
	delete actionDeleteSelectedRows;
	delete actionLoadAll;
}

void CenterTableView::initTableview()
{
	tableModel = new QStandardItemModel(this);
	//ui.tableView->verticalHeader()->hide();
	//ui.tableView->setVerticalHeader(new CBatchVerticalHeaderView());
	
	//ui.tableView->setEditTriggers(QAbstractItemView::SelectedClicked);
	//ui.tableView->setEditTriggers(QAbstractItemView::SelectedClicked|QAbstractItemView::CurrentChanged);


	//Delegate* userIDDelegate = new Delegate(tableModel,ui.tableView); 
	//userIDDelegate->setColomBoxValue("hello");
	//ui.tableView->setItemDelegate(userIDDelegate);
	/*ui.tableView->setItemDelegateForColumn(0, userIDDelegate); 
	ui.tableView->setItemDelegateForColumn(1, userIDDelegate); 
	ui.tableView->setItemDelegateForColumn(1, NULL); */
	//ui.tableView->setSortingEnabled(true);

	//connect(ui.tableView, SIGNAL(clicked(const QModelIndex)), this, SLOT(onTableBtnClicked(const QModelIndex)));

	//connect(ui.tableView, SIGNAL(mousePressEvent(QMouseEvent *event)), this, SLOT(slotMousePressEvent(QMouseEvent *event)));

	//ui.tableView->viewport()->installEventFilter(this);//安装事件过滤器
	//ui.tableView->viewport()->setMouseTracking(true);//true鼠标移动触发 false关闭移动触发
	//QToolTip::showText(QCursor::pos(),text);
	//ui.tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	
	//ui.progressBar->setVisible(false);
	//connect(ui.tableView->verticalScrollBar(), SIGNAL(sliderMoved(int)), this, SLOT(onMyScrollMoved(int)));

	/*ui.tableView->setStyleSheet("QTableView{background-color: rgb(250, 250, 115);" 
		"alternate-background-color: rgb(141, 163, 215);}"); */

	//ui.tableView->horizontalHeader()->setClickable(true);
	//ui.tableView->horizontalHeader()->setSortIndicator(0, Qt::AscendingOrder);
	//ui.tableView->horizontalHeader()->setSortIndicatorShown(true);
	//ui.tableView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
	//connect(ui.tableView->horizontalHeader(),SIGNAL(sectionClicked ( int)),this,SLOT(sortByColumn(int)));
}

void CenterTableView::freshTableview(ObId parentId)
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	if (GlobalInfo::g_WriteDatas.size()>0||GlobalInfo::g_InsertDatas.size()>0||GlobalInfo::g_DeleteDatas.size()>0)
	{
		QApplication::restoreOverrideCursor();
		QMessageBox::StandardButton reply;
		reply = QMessageBox::information(this, tr("save"), tr("You have changed data ,save?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		if (reply == QMessageBox::Yes)
		{
			slotButtonSave();
		}
		GlobalInfo::g_InsertDatas.clear();
		GlobalInfo::g_WriteDatas.clear();
		GlobalInfo::g_DeleteDatas.clear();
		GlobalInfo::g_SaveButton->hide();
		QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	}

	//清理断面开始
	displayMap.clear();
	foreach(QTableView* t,tableViewList)//避免内存溢出
	{
		delete t;
		t = NULL;
	}
	tableViewList.clear();

	tableModel->clear();

	disconnect(ui.tabWidget, SIGNAL(currentChanged(int)), this, SLOT(slotTabChanged(int)));
	ui.tabWidget->clear();	

	if (parentId==0)
	{
		QApplication::restoreOverrideCursor();
		return;
	}
	//清理断面结束


	QList<ObId> sonList;
	if (!ToolUtil::getChildrenList(parentId,sonList))
	{
		QApplication::restoreOverrideCursor();
		QMessageBox::information( this, tr("error"), tr( "Read child error" ));
		return;
	}
	this->currentParentId = parentId;
	int objNum = sonList.size();
	if (objNum>0)
	{
		foreach(ObId son,sonList)
		{
			OType otype = ToolUtil::databaseExtractOType(son);
			if (displayMap.contains(otype))
			{
				displayMap[otype].append(son);
			}else{
				QList<ObId> obIds;
				obIds.append(son);
				displayMap.insert(otype, obIds);
			}
		}

		int index = 0;
		QMap<OType,QList<ObId> >::iterator iter = displayMap.begin();
		while (iter != displayMap.end())
		{
			qDebug() << "Iterator " << iter.key() << ":" << iter.value(); 
			
			QTableView* tableView = new QTableView(this);
			tableView->setAlternatingRowColors(true); 
			tableView->setModel(tableModel);
			tableView->setItemDelegate(new TableDelegate(this));
			tableView->setContextMenuPolicy(Qt::CustomContextMenu);
			connect(tableView, SIGNAL(customContextMenuRequested(const QPoint)), this, SLOT(slotTableContextMenu(const QPoint)));
			//connect(tableView->horizontalHeader(),SIGNAL(sectionClicked ( int)),this,SLOT(sortByColumn(int)));
			QScrollBar *scrolbar = tableView->verticalScrollBar();
			connect((QWidget*)scrolbar, SIGNAL(valueChanged(int)),this,  SLOT(onMyScrollMoved(int)));

			const char*trans = translateOName(iter.key());
			ui.tabWidget->addTab(tableView,QString::fromUtf8(trans));

			tableViewList.append(tableView);

			if (index==0)
			{
				currentList.clear();
				currentList = iter.value();
				currentListTemp.clear();
				currentListTemp = iter.value();
				currentTabText = QString::fromUtf8(trans);
			}
			index++;

			iter++;



			///test
			//tableView->setFocusPolicy(Qt::NoFocus);
			//tableView->verticalHeader()->hide();
			//tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
			//tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
			//test
		}
			
		connect(ui.tabWidget, SIGNAL(currentChanged(int)), this, SLOT(slotTabChanged(int)));

		//加载数据
		currentScollNum = 0;
		startNum=0;
		if (currentList.size()>50)
		{
			endNum=50;
		}else{
			endNum = currentList.size();
		}

		if (!ToolUtil::readObjectAttributes(currentList,currentParentId,startNum,endNum,tableModel,NULL))
		{
			QMessageBox::information( this, tr("error"), tr( "Read Data error" ));
		}		
		((QTableView*)(ui.tabWidget->currentWidget()))->resizeColumnsToContents();
	}
	QApplication::restoreOverrideCursor();
}

void CenterTableView::freshFullTableview()
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	if (GlobalInfo::g_WriteDatas.size()>0||GlobalInfo::g_InsertDatas.size()>0||GlobalInfo::g_DeleteDatas.size()>0)
	{
		QApplication::restoreOverrideCursor();
		QMessageBox::StandardButton reply;
		reply = QMessageBox::information(this, tr("save"), tr("You have changed data ,save?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		if (reply == QMessageBox::Yes)
		{
			slotButtonSave();
		}
		GlobalInfo::g_InsertDatas.clear();
		GlobalInfo::g_WriteDatas.clear();
		GlobalInfo::g_DeleteDatas.clear();
		GlobalInfo::g_SaveButton->hide();
		QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	}

	//加载数据
	//tableModel->clear();
	startNum=endNum;
	endNum = currentList.size();

	MyQProgressDialog progressDialog(endNum,tr("preparing...need to wait a moment"),this);
	if (!ToolUtil::readObjectAttributes(currentList,currentParentId,startNum,endNum,tableModel,&progressDialog))
	{
		QMessageBox::information( this, tr("error"), tr( "Read Data error" ));
	}
	QApplication::restoreOverrideCursor();
}

void CenterTableView::freshTableviewByList(QList<ObId> sonList)
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	if (GlobalInfo::g_WriteDatas.size()>0||GlobalInfo::g_InsertDatas.size()>0||GlobalInfo::g_DeleteDatas.size()>0)
	{
		QApplication::restoreOverrideCursor();
		QMessageBox::StandardButton reply;
		reply = QMessageBox::information(this, tr("save"), tr("You have changed data ,save?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		if (reply == QMessageBox::Yes)
		{
			slotButtonSave();
		}
		GlobalInfo::g_InsertDatas.clear();
		GlobalInfo::g_WriteDatas.clear();
		GlobalInfo::g_DeleteDatas.clear();
		GlobalInfo::g_SaveButton->hide();
		QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	}

	//清理断面开始
	displayMap.clear();
	foreach(QTableView* t,tableViewList)//避免内存溢出
	{
		delete t;
		t = NULL;
	}
	tableViewList.clear();

	tableModel->clear();

	disconnect(ui.tabWidget, SIGNAL(currentChanged(int)), this, SLOT(slotTabChanged(int)));
	ui.tabWidget->clear();	

	if (sonList.size()==0)
	{
		QApplication::restoreOverrideCursor();
		return;
	}
	//清理断面结束


	this->currentParentId = 0;
	int objNum = sonList.size();
	if (objNum>0)
	{
		foreach(ObId son,sonList)
		{
			OType otype = ToolUtil::databaseExtractOType(son);
			if (displayMap.contains(otype))
			{
				displayMap[otype].append(son);
			}else{
				QList<ObId> obIds;
				obIds.append(son);
				displayMap.insert(otype, obIds);
			}
		}

		int index = 0;
		QMap<OType,QList<ObId> >::iterator iter = displayMap.begin();
		while (iter != displayMap.end())
		{
			qDebug() << "Iterator " << iter.key() << ":" << iter.value(); 

			QTableView* tableView = new QTableView(this);
			tableView->setAlternatingRowColors(true); 
			tableView->setModel(tableModel);
			tableView->setItemDelegate(new TableDelegate(this));
			tableView->setContextMenuPolicy(Qt::CustomContextMenu);
			connect(tableView, SIGNAL(customContextMenuRequested(const QPoint)), this, SLOT(slotTableContextMenu(const QPoint)));
			//connect(tableView->horizontalHeader(),SIGNAL(sectionClicked ( int)),this,SLOT(sortByColumn(int)));
			//QScrollBar *scrolbar = tableView->verticalScrollBar();
			//connect((QWidget*)scrolbar, SIGNAL(valueChanged(int)),this,  SLOT(onMyScrollMoved(int)));

			const char*trans = translateOName(iter.key());
			ui.tabWidget->addTab(tableView,QString::fromUtf8(trans));

			tableViewList.append(tableView);

			if (index==0)
			{
				currentList.clear();
				currentList = iter.value();
				currentListTemp.clear();
				currentListTemp = iter.value();
				currentTabText = QString::fromUtf8(trans);
			}
			index++;

			iter++;
		}

		//connect(ui.tabWidget, SIGNAL(currentChanged(int)), this, SLOT(slotTabChanged(int)));

		//加载数据
		//currentScollNum = 0;
		startNum=0;
		endNum = currentList.size();

		if (!ToolUtil::readObjectAttributes(currentList,currentParentId,startNum,endNum,tableModel,NULL))
		{
			QMessageBox::information( this, tr("error"), tr( "Read Data error" ));
		}	

		//拼接机器节点和集群节点下的视图
		try
		{
			OType otype = GlobalInfo::g_Database->extractOType(currentList.at(0));
			const ObjectType* objectType = GlobalInfo::g_Database->getObjectType(otype);
			int numOfObjectAttributes = objectType->getNumberOfObjectAttributes();
			const ObjectAttribute* objectAttributes = objectType->getObjectAttributes();

			int displayNum = 0;
			for (int j = 0; j < numOfObjectAttributes; j++)
			{
				const ObjectAttribute* objectAttribute = objectAttributes +j;
				QString attrName = objectAttribute->getName();
				if (!GlobalInfo::displayAttrList.contains(attrName))
				{
					continue;
				}
				displayNum++;
			}
			
			for (int i=0;i<currentList.size();i++)
			{
				ObId obId = currentList.at(i);
				QList<ObId> sonList;
				ToolUtil::getChildrenList(obId,sonList);
				if (otype==GlobalInfo::OT_Machine)
				{
					if (i==0)
					{
						const char*trans = translateAName(GlobalInfo::AT_IPAddress);
						QString columName = QString::fromUtf8(trans);
						
						tableModel->setHorizontalHeaderItem(displayNum, new QStandardItem(tr("A_")+columName));
						tableModel->setHorizontalHeaderItem(displayNum+1, new QStandardItem(tr("B_")+columName));
					}

					QStandardItem* nameItem = tableModel->item(i,0);//名称修改禁用
					nameItem->setEditable(false);
					foreach(ObId sonId, sonList)
					{
						if (ToolUtil::databaseExtractOType(sonId)==GlobalInfo::OT_POMSCommChannel)
						{
							AType at = GlobalInfo::AT_IPAddress;
							StringData ipData = "";
							ToolUtil::databaseRead(sonId,at,&ipData);
							OType otype = ToolUtil::databaseExtractOType(sonId);
							std::string stdData = (std::string)ipData;
							QStandardItem* item= new QStandardItem(QString::fromUtf8(stdData.c_str()));	

							ChoiceData channnelNum;
							if (ToolUtil::databaseRead(sonId,GlobalInfo::AT_ChannelNumber,&channnelNum))
							{
								int index = (int)channnelNum;
								tableModel->setItem(i,displayNum+index, item);
								tableModel->setData(item->index(),sonId,Qt::UserRole);
								tableModel->setData(item->index(),at,Qt::UserRole+1);
								tableModel->setData(item->index(),currentParentId,Qt::UserRole+3);
								tableModel->setData(item->index(),otype,Qt::UserRole+4);
							}
						}
					}
				}else if (otype==GlobalInfo::OT_CPSCluster)
				{
					if (i==0)
					{
						const char*transMcastAddrA = translateAName(GlobalInfo::AT_McastAddrA);
						const char*transMcastPortA = translateAName(GlobalInfo::AT_McastPortA);
						const char*transMcastAddrB = translateAName(GlobalInfo::AT_McastAddrB);
						const char*transMcastPortB = translateAName(GlobalInfo::AT_McastPortB);

						tableModel->setHorizontalHeaderItem(displayNum, new QStandardItem(QString::fromUtf8(transMcastAddrA)));
						tableModel->setHorizontalHeaderItem(displayNum+1, new QStandardItem(QString::fromUtf8(transMcastPortA)));
						tableModel->setHorizontalHeaderItem(displayNum+2, new QStandardItem(QString::fromUtf8(transMcastAddrB)));
						tableModel->setHorizontalHeaderItem(displayNum+3, new QStandardItem(QString::fromUtf8(transMcastPortB)));
					}
					if (sonList.size()>0)
					{
						QList<ObId> grandSonList;
						ToolUtil::getChildrenList(sonList.at(0),grandSonList);
						if (grandSonList.size()>0)
						{
							ObId grandSonId = grandSonList.at(0);
							OType otype = ToolUtil::databaseExtractOType(grandSonId);

							StringData addrAData = "";
							ToolUtil::databaseRead(grandSonId,GlobalInfo::AT_McastAddrA,&addrAData);
							QStandardItem* addrAItem= new QStandardItem(QString::fromUtf8(((std::string)addrAData).c_str()));	
							tableModel->setItem(i,displayNum, addrAItem);
							tableModel->setData(addrAItem->index(),grandSonId,Qt::UserRole);
							tableModel->setData(addrAItem->index(),GlobalInfo::AT_McastAddrA,Qt::UserRole+1);
							tableModel->setData(addrAItem->index(),currentParentId,Qt::UserRole+3);
							tableModel->setData(addrAItem->index(),otype,Qt::UserRole+4);

							IntegerData portAData = 0;
							ToolUtil::databaseRead(grandSonId,GlobalInfo::AT_McastPortA,&portAData);
							QStandardItem* portAItem= new QStandardItem(QString::number((int)portAData));	
							tableModel->setItem(i,displayNum+1, portAItem);
							tableModel->setData(portAItem->index(),grandSonId,Qt::UserRole);
							tableModel->setData(portAItem->index(),GlobalInfo::AT_McastPortA,Qt::UserRole+1);
							tableModel->setData(portAItem->index(),currentParentId,Qt::UserRole+3);
							tableModel->setData(portAItem->index(),otype,Qt::UserRole+4);
							
							StringData addrBData = "";
							ToolUtil::databaseRead(grandSonId,GlobalInfo::AT_McastAddrB,&addrBData);
							QStandardItem* addrBItem= new QStandardItem(QString::fromUtf8(((std::string)addrBData).c_str()));	
							tableModel->setItem(i,displayNum+2, addrBItem);
							tableModel->setData(addrBItem->index(),grandSonId,Qt::UserRole);
							tableModel->setData(addrBItem->index(),GlobalInfo::AT_McastAddrB,Qt::UserRole+1);
							tableModel->setData(addrBItem->index(),currentParentId,Qt::UserRole+3);
							tableModel->setData(addrBItem->index(),otype,Qt::UserRole+4);

							IntegerData portBData = 0;
							ToolUtil::databaseRead(grandSonId,GlobalInfo::AT_McastPortB,&portBData);
							QStandardItem* portBItem= new QStandardItem(QString::number((int)portBData));	
							tableModel->setItem(i,displayNum+3, portBItem);
							tableModel->setData(portBItem->index(),grandSonId,Qt::UserRole);
							tableModel->setData(portBItem->index(),GlobalInfo::AT_McastPortB,Qt::UserRole+1);
							tableModel->setData(portBItem->index(),currentParentId,Qt::UserRole+3);
							tableModel->setData(portBItem->index(),otype,Qt::UserRole+4);
						}
					}
				}
			}
		}
		catch (Exception& e)
		{
			qDebug()<<QString::fromUtf8(e.getDescription().c_str());
		}
		
		((QTableView*)(ui.tabWidget->currentWidget()))->resizeColumnsToContents();
	}
	QApplication::restoreOverrideCursor();
}

void CenterTableView::freshCommonTableview(QString tableName)
{
	//if (ui.tableView->itemDelegate()!=NULL)
	//{
	//	delete ui.tableView->itemDelegate();
	//}
	//disconnect(tableModel, SIGNAL(dataChanged (const QModelIndex &, const QModelIndex &)), this, SLOT(slotTableDataChanged(const QModelIndex &, const QModelIndex & )));
	//tableModel->clear();
	///*foreach (QPushButton* a,list)
	//{
	//	if (a!=NULL)
	//	{
	//		disconnect(a, SIGNAL(clicked()), this, SLOT(onTableBtnClicked()));
	//		delete a;	
	//	}		
	//	
	//}
	//list.clear();*/
	//TableDelegate* userIDDelegate = new TableDelegate(ui.tableView); 

	//ui.tableView->setItemDelegate(userIDDelegate);


	//

	////QStringList columnTitles;
	////columnTitles << "id" << "name" << "status" << "action";
	////tableModel->setHorizontalHeaderLabels(columnTitles);
	//columInfoList.clear();
	//columInfoList = DBUtil::getDBTableInfo(tableName);
	//for(int i=0;i<columInfoList.size();i++)
	//{
	//	tableModel->setHorizontalHeaderItem(i, new QStandardItem(columInfoList.at(i).COLUMN_NAME) );
	//}
	//
	//RECORDSETHANDLE recordsetHandle = CPS_ORM_RsNewRecordSet();
	//try
	//{
	//	if (DBUtil::UpdateConnectDB())
	//	{		
	//		tableName = tableName.toUpper();
	//		QString sql = "select * from "+tableName;

	//		int rows = CPS_ORM_RsLoadData(recordsetHandle, sql.toUtf8().data(), dbPoolHandle);
	//		if (rows>0)
	//		{
	//			for (int i=0;i<rows;i++)
	//			{
	//				for (int j=0;j<columInfoList.size();j++)
	//				{
	//					switch(columInfoList.at(j).DATA_TYPE)
	//					{
	//					case ENUM_LONG:
	//						{
	//							QStandardItem* item= new QStandardItem(QString::number((qlonglong)CPS_ORM_RsGetNumberValue(recordsetHandle, i, j)));
	//						    qlonglong itemData = (qlonglong)CPS_ORM_RsGetNumberValue(recordsetHandle, i, j);
	//						    //item->setData(itemData,Qt::UserRole);
	//						    tableModel->setItem(i, j, item);
	//						    break;
	//						}
	//					case ENUM_DOUBLE:
	//						{
	//							QStandardItem* item= new QStandardItem(QString::number(CPS_ORM_RsGetNumberValue(recordsetHandle, i, j)));
	//							double itemData = CPS_ORM_RsGetNumberValue(recordsetHandle, i, j);
	//							item->setData(itemData,Qt::UserRole);
	//							tableModel->setItem(i, j, item);
	//							break;
	//						}
	//					case ENUM_VARCHAR:
	//					case ENUM_CHAR:
	//						{
	//							{
	//							QStandardItem* item= new QStandardItem(QString::fromUtf8(CPS_ORM_RsGetStringValue(recordsetHandle, i, j).c_str()));
	//							
	//							//item->setData(100,Qt::UserRole);
	//							//item->setEditable(false);
	//							tableModel->setItem(i, j, item);
	//							break;
	//						}
	//						}
	//					case ENUM_BLOB:
	//					case ENUM_CLOB:
	//						{
	//							QStandardItem* item= new QStandardItem(QString::fromUtf8(CPS_ORM_RsGetStringValue(recordsetHandle, i, j).c_str()));
	//							//QStandardItem* item= new QStandardItem(QString::fromStdString(CPS_ORM_RsGetStringValue(recordsetHandle, i, j)));
	//							tableModel->setItem(i, j, item);

	//							//读取blob到文件再写入start
	//							//QString name = QString::fromUtf8(CPS_ORM_RsGetStringValue(recordsetHandle, i, 2).c_str());
	//							//qDebug()<<name;
	//							//std::string as = CPS_ORM_RsGetStringValue(recordsetHandle, i, j);
	//							//char* cpsenv = getenv("CPS_ENV");
	//							//QString sqlFileFolderPath = QDir::fromNativeSeparators(QString::fromUtf8(cpsenv)) + "/data/share/monitor/json/"; 

	//							////写出去
	//							//QFile fileW(sqlFileFolderPath+"mytest");
	//							//if (!fileW.open(QIODevice::WriteOnly))
	//							//{}
	//							//fileW.write(as.c_str(),as.length());
	//							////fileW.flush();
	//							//fileW.close();
	//
	//							////读进来
	//							//QFile fileR(sqlFileFolderPath+"mytest");
	//							//if (!fileR.open(QIODevice::ReadOnly))
	//							//{}
	//							//QByteArray qba = fileR.readAll();
	//							//int len = qba.size();
	//							//std::string re;
	//							//for (int i=0;i<len;i++)
	//							//{
	//							//	re = re+qba.at(i);
	//							//}
	//							//fileR.close();

	//							//if (re!="")
	//							//{
	//							//	std::string condition="NAME='MYTEST.sod'";
	//							//	CPS_ORM_SetAutoCommit(dbPoolHandle,false);//要关闭自动提交CPS_ORM_UpdateLob才生效
	//							//	CPS_ORM_SetStreamAutoCommit(dbPoolHandle,false);//要关闭自动提交CPS_ORM_UpdateLob才生效
	//							//	qDebug()<<CPS_ORM_UpdateLob(dbPoolHandle, "REPORT","SODFILE", re.c_str(),len,condition);
	//							//	qDebug()<<CPS_ORM_Commit(dbPoolHandle);
	//							//}
	//							//读取blob到文件再写入end
	//							
	//							//备选start
	//							//std::string sql = "update report t set t.sodfile=to_blob(rawtohex('"+re+"')) where name='MYTEST.sod'";
	//							//std::string sql = "update report t set t.sodfile=UTL_RAW.cast_to_raw('"+re+"') where name='MYTEST.sod'";
	//							
	//							//if (re!="")
	//							//{
	//							//	QFile fileW(sqlFileFolderPath+"mytest");
	//							//	if (!fileW.open(QIODevice::WriteOnly))
	//							//	{}
	//							//	fileW.write(sql.c_str(),sql.length());
	//							//	//fileW.flush();
	//							//	fileW.close();
	//							//	DBUtil::executeStdSQL(sql);
	//							//}
	//							//备选end
	//							
	//							break;
	//						}
	//					case ENUM_TIMESTAMP:
	//					case ENUM_DATE:
	//						/*QStandardItem* item= new QStandardItem(QString::fromUtf8(CPS_ORM_RsGetTimeValue(recordsetHandle, i, j).c_str()));
	//						tableModel->setItem(i, j, item);
	//						ORMTimeStamp*/
	//						break;
	//					case ENUM_UNKNOW:
	//						break;

	//					}
	//				}	
	//			}
	//		}			
	//	}
	//}
	//catch (Exception& e)
	//{
	//	qDebug()<<"querytabledata FAILURE Exception!";
	//}
	//CPS_ORM_RsFreeRecordSet(recordsetHandle);
	//connect(tableModel, SIGNAL(dataChanged (const QModelIndex &, const QModelIndex &)), this, SLOT(slotTableDataChanged(const QModelIndex &, const QModelIndex & )));
	////tableModel->setHorizontalHeaderItem(0, new QStandardItem(QString::fromUtf8(dataType.c_str())) );
	////tableModel->setHorizontalHeaderItem(1, new QStandardItem("num"));
	////tableModel->setHorizontalHeaderItem(2, new QStandardItem("sex"));
	////tableModel->setHorizontalHeaderItem(3, new QStandardItem("age"));
	////model->setHorizontalHeaderItem(4, new QStandardItem("collage"));
	////model->setHorizontalHeaderItem(5, new QStandardItem("intrest"));
	//
	//
	///*设置行字段名*/
	////model->setRowCount(3);
	////model->setHeaderData(0,Qt::Vertical, "行0");
	////model->setHeaderData(1,Qt::Vertical, "行1");
	////model->setHeaderData(2,Qt::Vertical, "行2");
	////ui.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	////QProgressDialog *progressDialog = new QProgressDialog(this);
	////progressDialog->setValue(0);                               //初始化值为0
	////progressDialog->setMinimumDuration(5);                     //设置对话框出现需要等待的时间
	////progressDialog->setRange(0, 100);                          //设置步进值的范围
	////progressDialog->setWindowTitle("Please wait");
	////progressDialog->setLabelText("copying......");
	//////progressDialog->setAutoClose(true);
	////progressDialog->setCancelButton(NULL);
	////for (int i = 0; i < 100; i ++)
	////{
	////	               //模拟进度
	////	if(progressDialog->wasCanceled())
	////	{                 //当点击取消按钮时,关闭对话框
	////		return ;
	////	}
	////}

	////ui.progressBar->setValue(0);
	// //ui.progressBar->setVisible(true);
	////ui.tableView->setUpdatesEnabled(false);
	////for(int i = 0; i < 100; i++)
	////{
	//   //progressDialog->setValue(i);     

	//    //ui.progressBar->setValue(i);
	//	//QStandardItem* a= new QStandardItem(QString::number(i + 1));
	//	//int aData = i+1;
	//	//a->setData(aData,Qt::UserRole);
	//	//tableModel->setItem(i, 0, a);
	//	//tableModel->setItem(i, 1, new QStandardItem(QString("hello qt tablview %1").arg(i)));
	//	//tableModel->setItem(i, 2, new QStandardItem("normal"));
	//	// add button to the last column
	//	//QPushButton *delBtn = new QPushButton;
	//	//QPushButton *edtBtn = new QPushButton;
	//	//list.append(delBtn);

	//	// set custom property
	//	//delBtn->setProperty("id", i); // set custom property
	//	//delBtn->setProperty("name", QString("hello qt tablview %1").arg(i));
	//	//button->setProperty("status", "normal");
	//	//delBtn->setIcon(QIcon(":/images/delete.png"));
	//	//delBtn->setToolTip(tr("delete"));
	//	//edtBtn->setIcon(QIcon(":/images/delete.png"));
	//	//edtBtn->setToolTip(tr("delete"));

	//	// set click event
	//	//connect(delBtn, SIGNAL(clicked()), this, SLOT(onTableBtnClicked()));

	//	// notice every time insert the button at the last line
	//	//int row = tableModel->rowCount() - 1;
	///*	QHBoxLayout *h_box_layout = new QHBoxLayout();
	//	QHBoxLayout *h_box_layout1 = new QHBoxLayout();
	//	h_box_layout->addLayout(h_box_layout1);*/
	//	//QWidget *widget = new QWidget();
	//	//h_box_layout->addWidget(delBtn);
	//	//h_box_layout->addWidget(edtBtn);
	//	//h_box_layout->setContentsMargins(0, 0, 0, 0);
	//	//h_box_layout->setSpacing(1);
	//	//widget->setLayout(h_box_layout);
	//	//ui.tableView->setIndexWidget(tableModel->index(row, 3), widget);

	//	/*	ui.tableView->setColumnWidth(0, 100);
	//	ui.tableView->setColumnWidth(1, 150);
	//	ui.tableView->setColumnWidth(2, 50);
	//	ui.tableView->setColumnWidth(3, 5);*/
	////}
	////ui.tableView->setUpdatesEnabled(true);
	////progressDialog->close();
	////delete progressDialog;
}

void CenterTableView::initPushButton()
{
	ui.saveButton->setIcon(QIcon(":/images/selectall.png"));
	//ui.cancelSelectAllPushButton->setIcon(QIcon(":/images/unselectall.png"));
	//ui.importBatchPushButton->setIcon(QIcon(":/images/batchimport.png"));
	//ui.exportBatchPushButton->setIcon(QIcon(":/images/batchexport.png"));
	//ui.deleteBatchPushButton->setIcon(QIcon(":/images/batchdelete.png"));
	//ui.selectAllPushButton->setFlat(true);
	//ui.selectAllPushButton->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
	connect(ui.saveButton, SIGNAL(pressed ()), this, SLOT(slotButtonSave()));
	/*connect(ui.cancelSelectAllPushButton, SIGNAL(pressed ()), this, SLOT(slotButtonCancelSelectAll()));
	connect(ui.importBatchPushButton, SIGNAL(pressed ()), this, SLOT(slotButtonImportBatch()));
	connect(ui.exportBatchPushButton, SIGNAL(pressed ()), this, SLOT(slotButtonExportBatch()));
	connect(ui.deleteBatchPushButton, SIGNAL(pressed ()), this, SLOT(slotButtonDeleteBatch()));*/
}

void CenterTableView::initTablePopMenu()
{
	tablePopMenu = new QMenu(this);
	actionUpdateColum = new QAction(tr("UpdateColum"), this);
	actionInsertOneRow = new QAction(tr("InsertOneRow"), this);
	actionDeleteSelectedRows = new QAction(tr("DeleteSelectedColums"), this);
	actionLoadAll = new QAction(tr("LoadAll"), this);

	connect(actionUpdateColum, SIGNAL(triggered(bool)), this, SLOT(slotUpdateColum()));
	connect(actionInsertOneRow, SIGNAL(triggered(bool)), this, SLOT(slotInsertOneRow()));
	connect(actionDeleteSelectedRows, SIGNAL(triggered(bool)), this, SLOT(slotDeleteSelectedRows()));
	connect(actionLoadAll, SIGNAL(triggered(bool)), this, SLOT(slotLoadAll()));
	
	allActions.append(actionUpdateColum);
	allActions.append(actionInsertOneRow);
	allActions.append(actionDeleteSelectedRows);
	allActions.append(actionLoadAll);
}

void CenterTableView::slotTableFresh(ObId parentId)
{
	freshTableview(parentId);
}

void CenterTableView::slotTableFreshByList(QList<ObId> sonList)
{
	freshTableviewByList(sonList);
}

void CenterTableView::slotButtonSave()
{
	//保存新增
	foreach(ObId obidtest,currentListTemp)
	{
		qDebug()<<QString::number(obidtest);
	}
	foreach(InsertData insertData, GlobalInfo::g_InsertDatas)
	{
		ObId newId = GlobalInfo::g_Database->create(insertData.parentId,insertData.otype);
		ObId partitionId = DBUtil::getPartitionId(insertData.parentId);
		LongLongData longlongData = partitionId;
		ToolUtil::databaseWrite(newId,GlobalInfo::AT_PartitionID,&longlongData);

		
		for (int i=0;i<insertData.insertDatas.size();i++)
		{
			insertData.insertDatas.at(i)->setData(newId,Qt::UserRole);
		}
		int insertId = insertData.id;
		for (int i=0;i<currentListTemp.size();i++)
		{
			if (currentListTemp[i]==insertId)
			{
				currentListTemp[i] = newId;
				break;
			}
		}
		foreach(ObId obidtest,currentListTemp)
		{
			qDebug()<<QString::number(obidtest);
		}
	}
	foreach(ObId obidtest,currentListTemp)
	{
		qDebug()<<QString::number(obidtest);
	}

	foreach(InsertData insertData, GlobalInfo::g_InsertDatas)
	{
		
		for (int i=0;i<insertData.insertDatas.size();i++)
		{
			ObId obId =insertData.insertDatas.at(i)->data(Qt::UserRole+2).toULongLong();
			qDebug()<<insertData.insertDatas.at(i)->text();
		}
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
		if (ToolUtil::databaseDestroy(deleteObId))
		{
		}
	}

	QMap<OType,QList<ObId> >::iterator iter = displayMap.begin();
	while (iter != displayMap.end())
	{
		const char*trans = translateOName(iter.key());
		if (QString::fromUtf8(trans)==currentTabText)
		{
			displayMap[iter.key()] = currentListTemp;			

			foreach(ObId obidtest,currentList)
			{
				qDebug()<<QString::number(obidtest);
			}
			foreach(ObId obidtest,currentListTemp)
			{
				qDebug()<<QString::number(obidtest);
			}

			break;
		}
		iter++;
	}

	GlobalInfo::g_InsertDatas.clear();
	GlobalInfo::g_WriteDatas.clear();
	GlobalInfo::g_DeleteDatas.clear();
	GlobalInfo::g_SaveButton->hide();
}

void CenterTableView::slotTabChanged(int index)
{
	if (GlobalInfo::g_WriteDatas.size()>0||GlobalInfo::g_InsertDatas.size()>0||GlobalInfo::g_DeleteDatas.size()>0)
	{
		QMessageBox::StandardButton reply;
		reply = QMessageBox::information(this, tr("save"), tr("You have changed data ,save?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		if (reply == QMessageBox::Yes)
		{
			slotButtonSave();
		}
		GlobalInfo::g_InsertDatas.clear();
		GlobalInfo::g_WriteDatas.clear();
		GlobalInfo::g_DeleteDatas.clear();
		GlobalInfo::g_SaveButton->hide();
	}

	currentTabText = ui.tabWidget->tabText(index);
	QMap<OType,QList<ObId> >::iterator iter = displayMap.begin();
	while (iter != displayMap.end())
	{
		const char*trans = translateOName(iter.key());
		if (QString::fromUtf8(trans)==currentTabText)
		{
			qDebug() << "Iterator " << iter.key() << ":" << iter.value(); 

			tableModel->clear();
			currentList.clear();
			currentList = iter.value();
			currentListTemp.clear();
			currentListTemp = iter.value();
			currentScollNum = 0;
			startNum=0;
			if (currentList.size()>50)
			{
				endNum=50;
			}else{
				endNum = currentList.size();
			}

			if (!ToolUtil::readObjectAttributes(currentList,currentParentId,startNum,endNum,tableModel,NULL))
			{
				QMessageBox::information( this, tr("error"), tr( "Read Data error" ));
			}
			((QTableView*)(ui.tabWidget->currentWidget()))->resizeColumnsToContents();
			break;
		}
		iter++;
	}
}

void CenterTableView::slotButtonCancelSelectAll()
{
	//((CBatchVerticalHeaderView*)ui.tableView->verticalHeader())->SetAllUnselected();
	
}

void CenterTableView::slotButtonImportBatch()
{
	QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"), "D:/user/myqtwork","input(*.csv);;input(*.csv *.json)", 0);
	qDebug()<<fileName;
}

void CenterTableView::slotButtonExportBatch()
{
	QString fileName = QFileDialog::getSaveFileName(this,tr("Save Result"),"",tr("Result Files (*.csv)"));
	qDebug()<<fileName;
}

void CenterTableView::slotButtonDeleteBatch()
{

}

void CenterTableView::onTableBtnClicked(const QModelIndex  index)
{
	//ui.tableView->edit(ui.tableView->currentIndex());
	QPushButton *button = (QPushButton *)sender();
	qDebug() << button->property("id").toInt() << endl;
	qDebug() << button->property("name").toString() << endl;
	qDebug() << button->property("status").toString() << endl;
}

void CenterTableView::slotTableContextMenu(const QPoint pos)
{
	//QToolTip::showText(QCursor::pos(),"hello");
	QTableView* tableView = (QTableView*)(ui.tabWidget->widget(ui.tabWidget->currentIndex()));
	QModelIndex index = tableView->indexAt(pos);
	
	if (index.isValid())
	{
		curTableItem = tableModel->itemFromIndex(index);
		//qDebug()<<curTableItem->text();
		foreach(QAction* action,allActions)
		{
			tablePopMenu->removeAction(action);
		}
		//先删除，再根据需求个性化选择加载action，为以后扩展
		OType otype = index.data(Qt::UserRole+4).toULongLong();
		if (otype==GlobalInfo::OT_CPSPartition||otype==GlobalInfo::OT_Machine||otype==GlobalInfo::OT_CPSCluster||otype==GlobalInfo::OT_POMSCommChannel||otype==GlobalInfo::OT_PartitionMcast)
		{
			AType atype = curTableItem->data(Qt::UserRole+1).toUInt();
			if (otype!=GlobalInfo::OT_Machine||atype!=GlobalInfo::AT_Name)
			{
				tablePopMenu->addAction(actionUpdateColum);
			}
			
		}else{
			tablePopMenu->addAction(actionUpdateColum);
			tablePopMenu->addAction(actionInsertOneRow);
			tablePopMenu->addAction(actionDeleteSelectedRows);
			tablePopMenu->addAction(actionLoadAll);
		}
		

		tablePopMenu->exec(QCursor::pos()); 
	}
}

void CenterTableView::slotTableDataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight )
{
	QStandardItem* item = tableModel->itemFromIndex(topLeft);
	//item->setForeground(brush);
	//WriteDataModel data;
	//data.writeObId = item->data(Qt::UserRole).toULongLong();
	//data.writeAtype = item->data(Qt::UserRole+1).toInt();
	//data.writeData = item->data(Qt::DisplayRole).toString();
	//data.item = item;
	//data.writeData = item->data(Qt::UserRole+2).toString();
	//writeDatas.append(data);
}

void CenterTableView::onMyScrollMoved(int num)
{
	int currentIndex = ui.tabWidget->currentIndex();
	qDebug()<<currentIndex;
	if (currentIndex==-1)
	{
		return;
	}
	QTableView* tableView = (QTableView*)(ui.tabWidget->widget(ui.tabWidget->currentIndex()));
	QScrollBar *scrolbar = tableView->verticalScrollBar();
	//scrolbar->setSliderPosition(10);
	//scrolbar->setValue(1);
	if (scrolbar->value()>3)
	{
		/*QStandardItem* ab= new QStandardItem(QString::number(scrolbar->value()));
		tableModel->appendRow(ab);*/
		//tableModel->insertRow(0,ab);


		
		if (currentScollNum<num)
		{
			currentScollNum = num;

			startNum = endNum;
			endNum = endNum+30;
			if (endNum>=currentList.size())
			{
				endNum = currentList.size();
			}

			foreach(ObId obidtest,currentList)
			{
				qDebug()<<QString::number(obidtest);
			}
			foreach(ObId obidtest,currentListTemp)
			{
				qDebug()<<QString::number(obidtest);
			}

			if (!ToolUtil::readObjectAttributes(currentList,currentParentId,startNum,endNum,tableModel))
			{
				QMessageBox::information( this, tr("error"), tr( "Read Data error" ));
			}
		}
	}
}

void CenterTableView::slotUpdateColum()
{
	QTableView* tableView = (QTableView*)(ui.tabWidget->widget(ui.tabWidget->currentIndex()));
	QModelIndexList indexList = tableView->selectionModel()->selectedIndexes();
	//首先做格式检查
	foreach(QModelIndex index,indexList)
	{
		if (curTableItem->column()!=index.column())
		{
			QMessageBox::information( this, tr("error"), tr( "Select must be the same colum" ));
			return;
		}
	}
	
	ObId currentObId = curTableItem->model()->data(curTableItem->index(),Qt::UserRole).toULongLong();
	ObId parentId = curTableItem->model()->data(curTableItem->index(),Qt::UserRole+3).toULongLong();
	QString displayValue =  curTableItem->model()->data(curTableItem->index(),Qt::DisplayRole).toString();
	AType atype = curTableItem->model()->data(curTableItem->index(),Qt::UserRole+1).toInt();
	OType otype = curTableItem->model()->data(curTableItem->index(),Qt::UserRole+4).toInt();
	DataType db = GlobalInfo::g_Database->getObjectType(otype)->getObjectAttribute(atype)->getDataType();

	QStringList obIds;
	ObId obId = 0;
	QString text = "";

	switch(db)
	{
	case STRING_DATA:
		{
			if (atype==GlobalInfo::AT_IPAddrA||atype==GlobalInfo::AT_IPAddrB||atype==GlobalInfo::AT_IPAddress||atype==GlobalInfo::AT_McastAddrA||atype==GlobalInfo::AT_McastAddrB)
			{
				BatchLineEditDialog dialog;
				QLineEdit* lineEdit = dialog.ui.lineEdit;
				lineEdit->setValidator(new QRegExpValidator(QRegExp("(\\d{1,3})(\\.)(\\d{1,3})(\\.)(\\d{1,3})(\\.)(\\d{1,3})")));
				if (dialog.exec()==QDialog::Accepted)
				{
					text = lineEdit->text();		
				}else{
					return;
				}
			}else{
				BatchLineEditDialog dialog;
				QLineEdit* lineEdit = dialog.ui.lineEdit;
				lineEdit->setValidator(new QRegExpValidator(QRegExp("^(\\w|\\.){1,80}$")));
				if (dialog.exec()==QDialog::Accepted)
				{
					text = lineEdit->text();		
				}else{
					return;
				}
			}			
			break;
		}
	case INTEGER_DATA:
		{
			BatchLineEditDialog dialog;
			QLineEdit* lineEdit = dialog.ui.lineEdit;
			lineEdit->setValidator(new QRegExpValidator(QRegExp("[0-9]{1,10}$")));
			if (dialog.exec()==QDialog::Accepted)
			{
				text = lineEdit->text();		
			}else{
				return;
			}
			break;
		}
	case SHORT_DATA:
		{
			BatchLineEditDialog dialog;
			QLineEdit* lineEdit = dialog.ui.lineEdit;
			lineEdit->setValidator(new QRegExpValidator(QRegExp("^(\\d{1,5})$")));
			if (dialog.exec()==QDialog::Accepted)
			{
				text = lineEdit->text();		
			}else{
				return;
			}
			break;
		}
	case FLOAT_DATA:
		{
			BatchLineEditDialog dialog;
			QLineEdit* lineEdit = dialog.ui.lineEdit;
			lineEdit->setValidator(new QRegExpValidator(QRegExp("^(-?\\d{1,12})(\\.\\d{1,6})?$")));
			if (dialog.exec()==QDialog::Accepted)
			{
				text = lineEdit->text();		
			}else{
				return;
			}
			break;
		}
	case LINK_DATA:
	case LONGLONG_DATA:
	case CONTAINER_DATA:
		{
			if (atype==GlobalInfo::AT_AlarmStateContainerLink||atype==GlobalInfo::AT_StateContainerLink)
			{
				BatchComboxDialog dialog;
				QComboBox* comboBox = dialog.ui.comboBox;
				ToolUtil::setComboxCustomData(comboBox, displayValue, atype,currentObId);
				if (dialog.exec()==QDialog::Accepted)
				{
					text = comboBox->currentText();  
					obId = comboBox->itemData(comboBox->currentIndex(),Qt::UserRole).toULongLong();		
				}else{
					return;
				}				
			}else if(atype==GlobalInfo::AT_AreaOfResponsibilityList){
				QStandardItemModel treeModel;
				PickTreeDialog dialog(&treeModel, this);	
				dialog.initMultiCheckTreeview("",tr("AllAreaOfRes"),GlobalInfo::OT_AreaOfResponsibility,QIcon(":/images/areaofres.png"));
				if (dialog.exec()==QDialog::Accepted)
				{
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
					text = nameList.join(",");

					if (dialog.isClear)
					{
						obIds.clear();
						text = "";
					}

				}else{
					return;
				}
			}else if(atype==GlobalInfo::AT_PartitionList||atype==GlobalInfo::AT_IsyncPartitionList){
				QStandardItemModel treeModel;
				PickTreeDialog dialog(&treeModel, this);	
				dialog.initMultiCheckTreeview("",tr("AllPartition"),GlobalInfo::OT_CPSPartition,QIcon(":/images/partition.png"));
				if (dialog.exec()==QDialog::Accepted)
				{
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
					text = nameList.join(",");

					if (dialog.isClear)
					{
						obIds.clear();
						text = "";
					}

				}else{
					return;
				}
			}else if(atype==GlobalInfo::AT_ParentClusterList){
				QStandardItemModel treeModel;
				PickTreeDialog dialog(&treeModel, this);	
				dialog.initMultiCheckTreeview("",tr("AllCluster"),GlobalInfo::OT_CPSCluster,QIcon(":/images/cluster.png"));
				if (dialog.exec()==QDialog::Accepted)
				{
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
					text = nameList.join(",");

					if (dialog.isClear)
					{
						obIds.clear();
						text = "";
					}

				}else{
					return;
				}
			}else if(atype==GlobalInfo::AT_ServiceTypeList){
				QStandardItemModel treeModel;
				PickTreeDialog dialog(&treeModel, this);	
				dialog.initMultiCheckTreeview("",tr("AllService"),GlobalInfo::OT_ServiceType,QIcon(":/images/servicetype.png"));
				if (dialog.exec()==QDialog::Accepted)
				{
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
					text = nameList.join(",");

					if (dialog.isClear)
					{
						obIds.clear();
						text = "";
					}

				}else{
					return;
				}
			}else if (atype==GlobalInfo::AT_TcpHostList||atype==GlobalInfo::AT_PreferredSyncFromList||atype==GlobalInfo::AT_AllowList||atype==GlobalInfo::AT_AccessPointList){
				QStandardItemModel treeModel;
				PickTreeDialog dialog(&treeModel, this);	
				dialog.initMultiCheckTreeview("",tr("AllMachine"),GlobalInfo::OT_Machine,QIcon(":/images/machine.png"));
				if (dialog.exec()==QDialog::Accepted)
				{
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
					text = nameList.join(",");

					if (dialog.isClear)
					{
						obIds.clear();
						text = "";
					}

				}else{
					return;
				}
			}else if(atype==GlobalInfo::AT_DEVICEID){
				QStandardItemModel treeModel;
				PickTreeDialog dialog(&treeModel, this);	
				dialog.initDeviceTreeview();
				if (dialog.exec()==QDialog::Accepted)
				{
					QModelIndexList indexs = dialog.ui.treeView->selectionModel()->selectedIndexes();
					foreach(QModelIndex index,indexs)
					{
						obId = index.data(Qt::UserRole).toULongLong();
					}

					if (obId!=0)
					{
						StringData nameData = "";
						ToolUtil::databaseRead(obId,GlobalInfo::AT_Name,&nameData);
						text = QString::fromUtf8(((std::string)nameData).c_str());
					}		

					if (dialog.isClear)
					{
						obId = 0;
						text = "";
					}
				}else{
					return;
				}
			}else if(atype==GlobalInfo::AT_MeasurementTypeLink){
				QStandardItemModel treeModel;
				PickTreeDialog dialog(&treeModel, this);	
				dialog.initMeasurementTypeLinkTreeview(otype);
				if (dialog.exec()==QDialog::Accepted)
				{
					QModelIndexList indexs = dialog.ui.treeView->selectionModel()->selectedIndexes();
					foreach(QModelIndex index,indexs)
					{
						obId = index.data(Qt::UserRole).toULongLong();
					}

					if (obId!=0)
					{
						StringData nameData = "";
						ToolUtil::databaseRead(obId,GlobalInfo::AT_Name,&nameData);
						text = QString::fromUtf8(((std::string)nameData).c_str());
					}

					if (dialog.isClear)
					{
						obId = 0;
						text = "";
					}
				}else{
					return;
				}
			}else if(atype==GlobalInfo::AT_FaultToleranceLink){
				QStandardItemModel treeModel;
				PickTreeDialog dialog(&treeModel, this);	
				dialog.initSingleTreeview(tr("AllProtocol"),GlobalInfo::OT_ProtocolType,QIcon(":/images/protocol.png"));
				if (dialog.exec()==QDialog::Accepted)
				{
					QModelIndexList indexs = dialog.ui.treeView->selectionModel()->selectedIndexes();
					foreach(QModelIndex index,indexs)
					{
						obId = index.data(Qt::UserRole).toULongLong();
					}

					if (obId!=0)
					{
						StringData nameData = "";
						ToolUtil::databaseRead(obId,GlobalInfo::AT_Name,&nameData);
						text = QString::fromUtf8(((std::string)nameData).c_str());
					}

					if (dialog.isClear)
					{
						obId = 0;
						text = "";
					}
				}else{
					return;
				}
			}else if(atype==GlobalInfo::AT_GatewaySpecificationLink){
				QStandardItemModel treeModel;
				PickTreeDialog dialog(&treeModel, this);	
				dialog.initSingleTreeview(tr("AllSave"),GlobalInfo::OT_GOS,QIcon(":/images/protocol.png"));
				if (dialog.exec()==QDialog::Accepted)
				{
					QModelIndexList indexs = dialog.ui.treeView->selectionModel()->selectedIndexes();
					foreach(QModelIndex index,indexs)
					{
						obId = index.data(Qt::UserRole).toULongLong();
					}

					if (obId!=0)
					{
						StringData nameData = "";
						ToolUtil::databaseRead(obId,GlobalInfo::AT_Name,&nameData);
						text = QString::fromUtf8(((std::string)nameData).c_str());
					}

					if (dialog.isClear)
					{
						obId = 0;
						text = "";
					}
				}else{
					return;
				}
			}else if(atype==GlobalInfo::AT_ClusterLink){
				QStandardItemModel treeModel;
				PickTreeDialog dialog(&treeModel, this);	
				dialog.initSingleTreeview(tr("AllCluster"),GlobalInfo::OT_CPSCluster,QIcon(":/images/cluster.png"));
				if (dialog.exec()==QDialog::Accepted)
				{
					QModelIndexList indexs = dialog.ui.treeView->selectionModel()->selectedIndexes();
					foreach(QModelIndex index,indexs)
					{
						obId = index.data(Qt::UserRole).toULongLong();
					}

					if (obId!=0)
					{
						StringData nameData = "";
						ToolUtil::databaseRead(obId,GlobalInfo::AT_Name,&nameData);
						text = QString::fromUtf8(((std::string)nameData).c_str());
					}

					if (dialog.isClear)
					{
						obId = 0;
						text = "";
					}
				}else{
					return;
				}
			}else if(atype==GlobalInfo::AT_DPSPointLink||atype==GlobalInfo::AT_DPCPointLink||atype==GlobalInfo::AT_MVPointLink||atype==GlobalInfo::AT_APCPointLink){
				QStandardItemModel treeModel;
				PickTreeDialog dialog(&treeModel, this);	
				dialog.initPointLink(parentId,otype);
				if (dialog.exec()==QDialog::Accepted)
				{
					QModelIndexList indexs = dialog.ui.treeView->selectionModel()->selectedIndexes();
					foreach(QModelIndex index,indexs)
					{
						obId = index.data(Qt::UserRole).toULongLong();
					}

					if (obId!=0)
					{
						StringData nameData = "";
						ToolUtil::databaseRead(obId,GlobalInfo::AT_Name,&nameData);
						text = QString::fromUtf8(((std::string)nameData).c_str());
					}	

					if (dialog.isClear)
					{
						obId = 0;
						text = "";
					}
				}else{
					return;
				}
			}else{
				QStandardItemModel treeModel;
				PickTreeDialog dialog(&treeModel, this);	
				dialog.initCommonTreeview();
				if (dialog.exec()==QDialog::Accepted)
				{
					QModelIndexList indexs = dialog.ui.treeView->selectionModel()->selectedIndexes();
					foreach(QModelIndex index,indexs)
					{
						obId = index.data(Qt::UserRole).toULongLong();
					}

					if (obId!=0)
					{
						StringData nameData = "";
						ToolUtil::databaseRead(obId,GlobalInfo::AT_Name,&nameData);
						text = QString::fromUtf8(((std::string)nameData).c_str());
					}		

					if (dialog.isClear)
					{
						obId = 0;
						text = "";
					}
				}else{
					return;
				}
			}
			break;
		}
	case MULTIPLE_CHOICE_DATA:
	case BOOLEAN_DATA:
		{
			BatchComboxDialog dialog;
			QComboBox* comboBox = dialog.ui.comboBox;
			ToolUtil::setComboxCustomData(comboBox, displayValue, atype,currentObId);
			if (dialog.exec()==QDialog::Accepted)
			{
				text = comboBox->currentText();  
				obId = comboBox->currentIndex();		
			}else{
				return;
			}
			break;
		}
	}
	
	foreach(QModelIndex index, indexList)
	{
		switch(db)
		{
		case STRING_DATA:
			{
				tableModel->setData(index, text, Qt::DisplayRole); 
				break;
			}
		case INTEGER_DATA:
		case SHORT_DATA:
			{
				tableModel->setData(index, text.toInt(), Qt::DisplayRole); 
				break;
			}
		case FLOAT_DATA:
			{
				tableModel->setData(index, QString::number(text.toFloat(),'f',6), Qt::DisplayRole); 
				break;
			}
		case CONTAINER_DATA:
			{
				tableModel->setData(index, text, Qt::DisplayRole); 
				tableModel->setData(index, obIds, Qt::UserRole+2); 
				break;
			}
		case LINK_DATA:
		case LONGLONG_DATA:
		case MULTIPLE_CHOICE_DATA:
		case BOOLEAN_DATA:
			{
				tableModel->setData(index, text, Qt::DisplayRole); 
				tableModel->setData(index, obId, Qt::UserRole+2); 
				break;
			}
		}

		tableModel->setData(index, QBrush(QColor(255, 0, 0)), Qt::TextColorRole);
		GlobalInfo::g_WriteDatas.append(tableModel->itemFromIndex(index));
		GlobalInfo::g_SaveButton->show();
	}
	
	

	//((CBatchVerticalHeaderView*)ui.tableView->verticalHeader())->SetAllSelected();

	/*QAbstractItemModel *model = ui.tableView->verticalHeader()->model();
	for(int section = 0;section < ui.tableView->verticalHeader()->count();++section)
	{
	QModelIndex index = model->index(section,0);
	QVariant a = model->data(index,CheckedRole);
	qDebug()<<a.toInt();
	qDebug()<<model->data(index,Qt::DisplayRole);
	}

	QModelIndexList indexList = ui.tableView->selectionModel()->selectedIndexes();
	foreach(QModelIndex index, indexList)
	{
	qDebug()<<tableModel->itemFromIndex(index)->text();

	}*/

	//QStandardItemModel* model = static_cast<QStandardItemModel*>(ui.tableView->model());
	//int row = ui.tableView->currentIndex().row();
	//int column = ui.tableView->currentIndex().column();
	//QStandardItem* a = model->item(row,column);
	//QStandardItem* a = model->itemFromIndex( ui.tableView->currentIndex());
	//model->insertColumn(1);
	//model->setItem(0,1,new QStandardItem(QString::number(1000)));
	//model->setItem(1,1,new QStandardItem(QString::number(1001)));
	//model->removeRow(2);

	//ui.tableView->edit(ui.tableView->currentIndex());
	//ui.tableView->edit(model->indexFromItem(model->item(0,1)));
	//ui.tableView->edit(model->indexFromItem(model->item(1,1)));
	//qDebug()<<a->text();
}
//Qt::UserRole);//该记录obid
//Qt::UserRole+1);//该条记录atype
//Qt::UserRole+2);//该item是link类属性obid
//Qt::UserRole+3);//该条记录的父obid
void CenterTableView::slotInsertOneRow()
{
	int row = curTableItem->row();
	ObId parentId = curTableItem->data(Qt::UserRole+3).toULongLong();
	OType otype = curTableItem->data(Qt::UserRole+4).toULongLong();
	if (parentId==0)
	{
		QMessageBox::information( this, tr("error"), tr( "ParentId or currentobid is Empty" ));
		return;
	}
	int colomCount = tableModel->columnCount();

	int insertId;//未保存前临时id
	if (GlobalInfo::g_InsertDatas.size()==0)
	{
		insertId = -1;
	}else{
		insertId = GlobalInfo::g_InsertDatas[GlobalInfo::g_InsertDatas.size()-1].id-1;
	}

	QList<QStandardItem*> rowItemList;
	for (int j=0;j<colomCount;j++)
	{
		QModelIndex index = tableModel->index(row,j);
		QStandardItem* item = new QStandardItem(index.data(Qt::DisplayRole).toString());
		item->setData(insertId,Qt::UserRole);//该记录obid
		item->setData(index.data(Qt::UserRole+1),Qt::UserRole+1);//该条记录atype
		item->setData(index.data(Qt::UserRole+2),Qt::UserRole+2);//该item是link类属性obid
		item->setData(parentId,Qt::UserRole+3);//该条记录的父obid
		item->setData(otype,Qt::UserRole+4);//该条记录的otype
		item->setData(QBrush(QColor(255, 0, 0)),Qt::TextColorRole);
		
		rowItemList.append(item);
	}
	InsertData insertData(insertId,parentId,otype,rowItemList);
	GlobalInfo::g_InsertDatas.append(insertData);
	tableModel->insertRow(row+1,rowItemList);
	currentListTemp.insert(row+1,insertId);
	qDebug()<<currentListTemp;
	GlobalInfo::g_SaveButton->show();
	foreach(InsertData a,GlobalInfo::g_InsertDatas)
	{
		qDebug()<<a.id;
		qDebug()<<a.parentId;
	}
}

void CenterTableView::slotDeleteSelectedRows()
{
	QTableView* tableView = (QTableView*)(ui.tabWidget->widget(ui.tabWidget->currentIndex()));
	QModelIndexList indexList = tableView->selectionModel()->selectedIndexes();
	
	//首先做格式检查,并保存
	QList<QModelIndex> deleteIndexs;
	foreach(QModelIndex index,indexList)
	{
		if (curTableItem->column()!=index.column())
		{
			QMessageBox::information( this, tr("error"), tr( "Select must be the same colum" ));
			return;
		}

		qDebug()<<index.data(Qt::UserRole);
		qDebug()<<index.data(Qt::DisplayRole);
		deleteIndexs.append(index);
	}

	for (int i=deleteIndexs.size()-1;i>=0;i--)
	{
		qlonglong deleteObId = tableModel->data(deleteIndexs[i],Qt::UserRole).toLongLong();//用longlong是为判断是否为负值
		if (deleteObId<0)//负值表示是新增的，未保存就删除的情况
		{
			for (int i=0;i<GlobalInfo::g_InsertDatas.size();i++)
			{
				if (GlobalInfo::g_InsertDatas[i].id==deleteObId)
				{
					GlobalInfo::g_InsertDatas.removeAt(i);
					break;
				}
			}
		}else{
			//判断是否有孩子节点
			QList<ObId> list;		
			ToolUtil::getChildrenList(deleteObId,list);
			if (list.size()>0)
			{
				QMessageBox::information( this, tr("error"), tr( "Have child node ,you can not delete this node" ));
				break;
			}

			//判断是否已修改，修改后删除的话，需清理修改队列
			for (int i=GlobalInfo::g_WriteDatas.size()-1;i>=0;i--)
			{
				ObId writeId = GlobalInfo::g_WriteDatas[i]->data(Qt::UserRole).toULongLong();
				if (writeId==deleteObId)
				{
					GlobalInfo::g_WriteDatas.removeAt(i);
				}
			}

			GlobalInfo::g_DeleteDatas.append(deleteObId);
		}

		tableModel->removeRow(deleteIndexs[i].row());
		currentListTemp.removeAt(deleteIndexs[i].row());
	}
	foreach(InsertData a,GlobalInfo::g_InsertDatas)
	{
		qDebug()<<a.id;
		qDebug()<<a.parentId;
	}
	foreach(ObId a,GlobalInfo::g_DeleteDatas)
	{
		qDebug()<<QString::number(a);
	}
	//qDebug()<<insertDatas;
	//qDebug()<<deleteDatas;
	GlobalInfo::g_SaveButton->show();
}

void CenterTableView::sortByColumn(int column)
{
	qDebug()<<1;
	//Q_D(QTableView);

	//if (!tableModel)
	//	return;
	//bool ascending = (ui.tableView->horizontalHeader()->sortIndicatorSection()==column&& ui.tableView->horizontalHeader()->sortIndicatorOrder()==Qt::DescendingOrder);
	//Qt::SortOrder order = ascending ? Qt::AscendingOrder : Qt::DescendingOrder;
	//ui.tableView->horizontalHeader()->setSortIndicator(column, order);
	//tableModel->setSortRole(Qt::UserRole);
	//tableModel->sort(column, order);
	//tableModel->sort(column, Qt::AscendingOrder);
}

void CenterTableView::slotLoadAll()
{
	freshFullTableview();
}

//void CenterTableWidget::slotMousePressEvent(QMouseEvent *event)
//{
//	if(event->button() == Qt::LeftButton)
//	{
//		qDebug()<<1;
//	}
//}

bool CenterTableView::eventFilter(QObject *obj, QEvent *e)
{
	//if(obj == ui.tableView->viewport())
	//{
	if(e->type() == QEvent::MouseMove)
	{
		//choseItem(ui.tableView->indexAt(ui.tableView->mapFromGlobal(QCursor::pos())));
	}
	/*if(e->type() == QEvent::MouseButtonPress)
	{
	choseItem(ui.tableView->indexAt(ui.tableView->mapFromGlobal(QCursor::pos())));
	}*/
	//}
	return QWidget::eventFilter(obj,e);
}

void CenterTableView::choseItem(QModelIndex index)
{
	if(!index.isValid())
		return;
	QString text = QString("(%1,%2) %3").arg(QString::number(index.row()),QString::number(index.column()),index.data().toString());
	if(text.isEmpty())
		return;
	QToolTip::showText(QCursor::pos(),text);
}


