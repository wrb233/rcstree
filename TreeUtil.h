#pragma once

#include "common.h"
#include "ToolUtil.h"
#include "DBUtil.h"

class TreeUtil:public QObject
{
	Q_OBJECT
public:
	TreeUtil();
	~TreeUtil();

	static QStringList traverseModelRows(QStandardItemModel* model);//遍历model行
	static void traverseTreeNodes(QStandardItem *item, QStringList &obIds);//遍历树节点

	static QStandardItem* addItem(const QString& treeNodeName, ObId obId, QIcon icon, QStandardItem* parent, bool isLeaf);//添加树节点

	//树节点复选框
	static void treeItem_checkAllChild(QStandardItem * item, bool check);
	static void treeItem_checkAllChild_recursion(QStandardItem * item,bool check);
	static void treeItem_CheckChildChanged(QStandardItem * item);
	static Qt::CheckState checkSibling(QStandardItem * item);

	//根据当前item获取自身及其子孙所有节点obid，一般用于批量删除
	static bool getAllObIdsByCurrentItem(ObId parentObId, QList<ObId> &obIds);
};