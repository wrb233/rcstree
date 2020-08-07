#include "PickPointDialog.h"

//构造函数
PickPointDialog::PickPointDialog( QWidget* parent, Qt::WindowFlags flags ): CpsDialog( parent, flags )
{
	ui.setupUi(this);//初始化界面
	//setAttribute(Qt::WA_DeleteOnClose,true);
	initDataPointTree();

	//ui.treeView->setContextMenuPolicy(Qt::CustomContextMenu);  //设置枚举值
	//connect(ui.treeView, SIGNAL(customContextMenuRequested(const QPoint&)),this, SLOT(sltShowPopMenu(const QPoint&)));
}

//void PickPointDialog::sltShowPopMenu(const QPoint& pos)//槽函数
//{
//	QStandardItemModel *model= static_cast<QStandardItemModel*>(ui.treeView->model());
//	QModelIndex index = ui.treeView->indexAt(pos);  //获取当前被点击的节点
//	/*QModelIndex index1 = ui.treeView->currentIndex();
//	qDebug()<<index.row();
//	qDebug()<<index1.row();*/
//	curItem = model->itemFromIndex(index);
//	//QModelIndex index2  = curItem->index();
//	//qDebug()<<index2.row();
//
//	//如果没有点击到节点
//	if (!curItem)
//	{
//		return;
//	}
//	//如果是一级节点，可以弹出右键
//	else if(!curItem->parent())
//	{
//		popMenu = new QMenu(ui.treeView);
//		//添加右键的选项
//		QAction* act = popMenu->addAction("get first name of children");
//		connect(act, SIGNAL(triggered(bool)), this, SLOT(getname1()));
//		popMenu->exec(QCursor::pos());
//	}
//	//是二级节点
//	else
//	{
//		popMenu = new QMenu(ui.treeView);
//		//添加右键的选项
//		QAction* act = popMenu->addAction("get name of node");
//		connect(act, SIGNAL(triggered(bool)), this, SLOT(getname2()));
//		popMenu->exec(QCursor::pos());
//	}
//}	
//
////右键选项的执行函数
//void PickPointDialog::getname1()
//{
//	QModelIndex index = curItem->index();
//	qDebug()<<index.row();
//	QStandardItem *parent = curItem->parent();
//	parent->removeRow(index.row());
//	//curItem->removeRow(curItem->index().row());
//	//ui.lineEdit->clear();
//	//QString name = curItem->child(0)->text();
//	//qDebug() << name << endl;
//	//ui.lineEdit->setText(name);
//}
//
////右键选项的执行函数
//void PickPointDialog::getname2()
//{
//	QString name = curItem->text();
//	qDebug() << name << endl;
//	QModelIndex index = curItem->index();
//	qDebug()<<index.row();
//	QStandardItem *parent = curItem->parent();
//	parent->removeRow(index.row());
//
//	QStandardItem* item = new QStandardItem("hello");
//	item->setCheckable(true);
//	/*if (!isLeaf)
//	{
//	item->setTristate(true);
//	}*/
//
//	item->setData(123,Qt::UserRole);
//
//	parent->insertRow(1,item);
//	//ui.lineEdit_2->clear();
//	//QString name = curItem->text();
//	//qDebug() << name << endl;
//	//ui.lineEdit_2->setText(name);
//}


//析构函数
PickPointDialog::~PickPointDialog()
{
	if (model!=NULL)
	{
		model->clear();
		delete model;
		model=NULL;
	}	
}

//void PickPointDialog::myExpanded(const QModelIndex  index)
//{
//	QStandardItemModel *model= static_cast<QStandardItemModel*>(ui.treeView->model());
//
//	QStandardItem* curItem = model->itemFromIndex(index);
//	qDebug()<<curItem->text();
//
//}

void PickPointDialog::treeItemChanged(QStandardItem * item)
{
	if ( item == NULL )
		return ;
	if ( item->isCheckable ())
	{
		//如果条目是存在复选框的，那么就进行下面的操作
        Qt::CheckState state = item->checkState (); //获取当前的选择状态
		if ( item->isTristate ())
		{
			//如果条目是三态的，说明可以对子目录进行全选和全不选的设置
			if ( state != Qt::PartiallyChecked )
			{
				//当前是选中状态，需要对其子项目进行全选
				TreeUtil::treeItem_checkAllChild ( item , state == Qt::Checked ? true : false );
			}
		}
		else
		{
			//说明是两态的，两态会对父级的三态有影响
			//判断兄弟节点的情况
			TreeUtil::treeItem_CheckChildChanged ( item );
		}
	}
}

void PickPointDialog::initDataPointTree()
{
	model = new QStandardItemModel(ui.treeView);
	initDMSNode(model);
	connect(model,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(treeItemChanged(QStandardItem*)));
	
	ui.treeView->header()->hide();
	ui.treeView->setModel(model);
	ui.treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	//connect(ui.treeView,SIGNAL(expanded ( const QModelIndex)),this,SLOT(myExpanded(const QModelIndex)));
	//connect(ui.treeView,SIGNAL(doubleClicked  ( const QModelIndex)),this,SLOT(myExpanded(const QModelIndex)));
}

void PickPointDialog::writeSelectPointToFile()
{
	QStringList obIds = TreeUtil::traverseModelRows(model);

	char* cpsenv = getenv("CPS_ENV");
	QString sqlFileFolderPath = QDir::fromNativeSeparators(QString::fromUtf8(cpsenv)) + "/data/share/"; 
	QDir dir(sqlFileFolderPath);
	if(!dir.exists())
	{
		dir.mkpath(sqlFileFolderPath);
	}

	QFile f(sqlFileFolderPath+"datapoint.txt");  
	if(!f.open(QIODevice::WriteOnly | QIODevice::Text))  
	{ 
		return;
	}  

	QTextStream datOutput(&f); 
	datOutput.setCodec("UTF-8");

	foreach(QString obId, obIds)
	{
		datOutput << obId<< endl; 
	}
	datOutput.flush();
	f.flush();
	f.close();
}

void PickPointDialog::initDMSNode(QStandardItemModel* model )
{
	QStandardItem* alldmsRoot = new QStandardItem(tr("alldms"));
	alldmsRoot->setCheckable(true);
	alldmsRoot->setTristate(true);
	model->appendRow(alldmsRoot);

	RECORDSETHANDLE recordsetHandle = CPS_ORM_RsNewRecordSet();
	QString sql ="select a.objectid, a.name\
				 from DMSCOMMUNICATEUNIT a\
				 where EXISTS (select *\
				 from (select *\
				 from (select * from wiring where ATTRIBUTETYPEID = 8)\
				 start with objectid = (select t.objectid from folder t where t.description='DS6000_IEDs')\
				 connect by prior WIREDOBJECTID = objectid) b\
				 where a.OBJECTID = b.WIREDOBJECTID)";
	int rows = CPS_ORM_RsLoadData(recordsetHandle, sql.toUtf8().data(), GlobalInfo::g_DBPoolHandle);
	if (rows>0)
	{
		for (int i=0;i<rows;i++)
		{
			qDebug()<<i;
			ObId id = (ObId)CPS_ORM_RsGetNumberValue(recordsetHandle, i, 0);
			std::string name = CPS_ORM_RsGetStringValue(recordsetHandle, i, 1);
			QStandardItem* dms = TreeUtil::addItem(QString::fromUtf8(name.c_str()), id, QIcon(":/images/tree.png"), alldmsRoot, false);
			initMVPoint(dms);
			initDSPPoint(dms);
		}
	}
	CPS_ORM_RsFreeRecordSet(recordsetHandle);
}

void PickPointDialog::initMVPoint(QStandardItem* parent)
{
	RECORDSETHANDLE recordsetHandle = CPS_ORM_RsNewRecordSet();

	QString obId = parent->data(Qt::UserRole).toString();
	QString sql ="select a.objectid, a.name\
				 from MVPOINT a\
				 where EXISTS (select *\
				 from (select *\
				 from (select * from wiring where ATTRIBUTETYPEID = 8)\
				 start with objectid = "+obId+"\
				 connect by prior WIREDOBJECTID = objectid) b\
				 where a.OBJECTID = b.WIREDOBJECTID)";
	int rows = CPS_ORM_RsLoadData(recordsetHandle, sql.toUtf8().data(), GlobalInfo::g_DBPoolHandle);
	if (rows>0)
	{
		for (int i=0;i<rows;i++)
		{
			ObId id = (ObId)CPS_ORM_RsGetNumberValue(recordsetHandle, i, 0);
			std::string name = CPS_ORM_RsGetStringValue(recordsetHandle, i, 1);
			TreeUtil::addItem(QString::fromUtf8(name.c_str()), id, QIcon(":/images/tree.png"), parent, true);
		}
	}
	CPS_ORM_RsFreeRecordSet(recordsetHandle);
}

void PickPointDialog::initDSPPoint(QStandardItem* parent)
{
	RECORDSETHANDLE recordsetHandle = CPS_ORM_RsNewRecordSet();
	QString obId = parent->data(Qt::UserRole).toString();
	QString sql ="select a.objectid, a.name\
				 from DPSPOINT a\
				 where EXISTS (select *\
				 from (select *\
				 from (select * from wiring where ATTRIBUTETYPEID = 8)\
				 start with objectid = "+obId+"\
				 connect by prior WIREDOBJECTID = objectid) b\
				 where a.OBJECTID = b.WIREDOBJECTID)";
	int rows = CPS_ORM_RsLoadData(recordsetHandle, sql.toUtf8().data(), GlobalInfo::g_DBPoolHandle);
	if (rows>0)
	{
		for (int i=0;i<rows;i++)
		{
			ObId id = (ObId)CPS_ORM_RsGetNumberValue(recordsetHandle, i, 0);
			std::string name = CPS_ORM_RsGetStringValue(recordsetHandle, i, 1);
			TreeUtil::addItem(QString::fromUtf8(name.c_str()), id, QIcon(":/images/tree.png"), parent, true);
		}
	}
	CPS_ORM_RsFreeRecordSet(recordsetHandle);
}