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

	static QStringList traverseModelRows(QStandardItemModel* model);//����model��
	static void traverseTreeNodes(QStandardItem *item, QStringList &obIds);//�������ڵ�

	static QStandardItem* addItem(const QString& treeNodeName, ObId obId, QIcon icon, QStandardItem* parent, bool isLeaf);//������ڵ�

	//���ڵ㸴ѡ��
	static void treeItem_checkAllChild(QStandardItem * item, bool check);
	static void treeItem_checkAllChild_recursion(QStandardItem * item,bool check);
	static void treeItem_CheckChildChanged(QStandardItem * item);
	static Qt::CheckState checkSibling(QStandardItem * item);

	//���ݵ�ǰitem��ȡ�������������нڵ�obid��һ����������ɾ��
	static bool getAllObIdsByCurrentItem(ObId parentObId, QList<ObId> &obIds);
};