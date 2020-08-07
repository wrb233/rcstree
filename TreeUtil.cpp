#include "TreeUtil.h"

TreeUtil::TreeUtil():QObject()
{

}

TreeUtil::~TreeUtil()
{

}

QStringList TreeUtil::traverseModelRows(QStandardItemModel* model)
{
	QStringList obIds;

	for(int i = 0;i < model->rowCount() ;i++)
	{
		QStandardItem *item = model->item(i);
		qDebug() <<"item = " << item->text();	
		traverseTreeNodes(model->item(i), obIds);
	}
	return obIds;
}

void TreeUtil::traverseTreeNodes(QStandardItem *item, QStringList &obIds)
{
	if(item->hasChildren())
	{
		for(int i = 0;i < item->rowCount() ;i++)
		{
			QStandardItem * childitem = item->child(i);
			if (childitem->checkState()==Qt::Checked)
			{
				qDebug() << "childitem = " << childitem->text();
				qDebug() << "childitem = " << childitem->data(Qt::UserRole).toString();
				obIds.append(childitem->data(Qt::UserRole).toString());
			}
			traverseTreeNodes(childitem, obIds);
		}
	}
}

QStandardItem* TreeUtil::addItem(const QString& treeNodeName, ObId obId, QIcon icon, QStandardItem* parent, bool isLeaf)
{
	QStandardItem* item = new QStandardItem(treeNodeName);
	item->setCheckable(true);
	if (!isLeaf)
	{
		item->setTristate(true);
	}

	item->setData(obId,Qt::UserRole);
	parent->appendRow(item);

	return item;
}

void TreeUtil::treeItem_checkAllChild(QStandardItem * item, bool check)
{
	if(item == NULL)
		return;
	int rowCount = item->rowCount();
	for(int i=0;i<rowCount;++i)
	{
		QStandardItem* childItems = item->child(i);
		treeItem_checkAllChild_recursion(childItems,check);
	}
	if(item->isCheckable())
		item->setCheckState(check ? Qt::Checked : Qt::Unchecked);
}
void TreeUtil::treeItem_checkAllChild_recursion(QStandardItem * item,bool check)
{
	if(item == NULL)
		return;
	int rowCount = item->rowCount();
	for(int i=0;i<rowCount;++i)
	{
		QStandardItem* childItems = item->child(i);
		treeItem_checkAllChild_recursion(childItems,check);
	}
	if(item->isCheckable())
		item->setCheckState(check ? Qt::Checked : Qt::Unchecked);
}

void TreeUtil::treeItem_CheckChildChanged(QStandardItem * item)
{
	if(NULL == item)
		return;
	Qt::CheckState siblingState = checkSibling(item);
	QStandardItem * parentItem = item->parent();
	if(NULL == parentItem)
		return;
	if(Qt::PartiallyChecked == siblingState)
	{
		if(parentItem->isCheckable() && parentItem->isTristate())
			parentItem->setCheckState(Qt::PartiallyChecked);
	}
	else if(Qt::Checked == siblingState)
	{
		if(parentItem->isCheckable())
			parentItem->setCheckState(Qt::Checked);
	}
	else
	{
		if(parentItem->isCheckable())
			parentItem->setCheckState(Qt::Unchecked);
	}
	treeItem_CheckChildChanged(parentItem);
}

Qt::CheckState TreeUtil::checkSibling(QStandardItem * item)
{
	//先通过父节点获取兄弟节点
	QStandardItem * parent = item->parent();
	if(NULL == parent)
		return item->checkState();
	int brotherCount = parent->rowCount();
	int checkedCount(0),unCheckedCount(0);
	Qt::CheckState state;
	for(int i=0;i<brotherCount;++i)
	{
		QStandardItem* siblingItem = parent->child(i);
		state = siblingItem->checkState();
		if(Qt::PartiallyChecked == state)
			return Qt::PartiallyChecked;
		else if(Qt::Unchecked == state)
			++unCheckedCount;
		else
			++checkedCount;
		if(checkedCount>0 && unCheckedCount>0)
			return Qt::PartiallyChecked;
	}
	if(unCheckedCount>0)
		return Qt::Unchecked;
	return Qt::Checked;
}

bool TreeUtil::getAllObIdsByCurrentItem(ObId parentObId, QList<ObId> &obIds)
{
	QApplication::processEvents();
	obIds.append(parentObId);
	QList<ObId> childObIds;
	if (ToolUtil::getChildrenList(parentObId,childObIds))
	{
		foreach(ObId childObId,childObIds)
		{
			if(getAllObIdsByCurrentItem(childObId, obIds))
			{
				continue;
			}else{
				return false;
			}
		}
		return true;
	}else{
		return false;
	}	
}