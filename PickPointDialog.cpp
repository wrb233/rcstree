#include "PickPointDialog.h"

//���캯��
PickPointDialog::PickPointDialog( QWidget* parent, Qt::WindowFlags flags ): CpsDialog( parent, flags )
{
	ui.setupUi(this);//��ʼ������
	//setAttribute(Qt::WA_DeleteOnClose,true);
	initDataPointTree();

	//ui.treeView->setContextMenuPolicy(Qt::CustomContextMenu);  //����ö��ֵ
	//connect(ui.treeView, SIGNAL(customContextMenuRequested(const QPoint&)),this, SLOT(sltShowPopMenu(const QPoint&)));
}

//void PickPointDialog::sltShowPopMenu(const QPoint& pos)//�ۺ���
//{
//	QStandardItemModel *model= static_cast<QStandardItemModel*>(ui.treeView->model());
//	QModelIndex index = ui.treeView->indexAt(pos);  //��ȡ��ǰ������Ľڵ�
//	/*QModelIndex index1 = ui.treeView->currentIndex();
//	qDebug()<<index.row();
//	qDebug()<<index1.row();*/
//	curItem = model->itemFromIndex(index);
//	//QModelIndex index2  = curItem->index();
//	//qDebug()<<index2.row();
//
//	//���û�е�����ڵ�
//	if (!curItem)
//	{
//		return;
//	}
//	//�����һ���ڵ㣬���Ե����Ҽ�
//	else if(!curItem->parent())
//	{
//		popMenu = new QMenu(ui.treeView);
//		//����Ҽ���ѡ��
//		QAction* act = popMenu->addAction("get first name of children");
//		connect(act, SIGNAL(triggered(bool)), this, SLOT(getname1()));
//		popMenu->exec(QCursor::pos());
//	}
//	//�Ƕ����ڵ�
//	else
//	{
//		popMenu = new QMenu(ui.treeView);
//		//����Ҽ���ѡ��
//		QAction* act = popMenu->addAction("get name of node");
//		connect(act, SIGNAL(triggered(bool)), this, SLOT(getname2()));
//		popMenu->exec(QCursor::pos());
//	}
//}	
//
////�Ҽ�ѡ���ִ�к���
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
////�Ҽ�ѡ���ִ�к���
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


//��������
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
		//�����Ŀ�Ǵ��ڸ�ѡ��ģ���ô�ͽ�������Ĳ���
        Qt::CheckState state = item->checkState (); //��ȡ��ǰ��ѡ��״̬
		if ( item->isTristate ())
		{
			//�����Ŀ����̬�ģ�˵�����Զ���Ŀ¼����ȫѡ��ȫ��ѡ������
			if ( state != Qt::PartiallyChecked )
			{
				//��ǰ��ѡ��״̬����Ҫ��������Ŀ����ȫѡ
				TreeUtil::treeItem_checkAllChild ( item , state == Qt::Checked ? true : false );
			}
		}
		else
		{
			//˵������̬�ģ���̬��Ը�������̬��Ӱ��
			//�ж��ֵܽڵ�����
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