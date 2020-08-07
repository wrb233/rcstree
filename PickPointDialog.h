#pragma once

#include "common.h"
#include "TreeUtil.h"
#include "ui_pickpoint.h"

class PickPointDialog: public CpsDialog
{
	Q_OBJECT
public:

	//构造函数
	PickPointDialog( QWidget* parent=0, Qt::WindowFlags flags=0 );

	void writeSelectPointToFile();//写选择的点到文件中
	//QMenu* popMenu;
	//QStandardItem* curItem;

	//析构函数
	~PickPointDialog();

private:
	Ui::PickPointUI ui;
	QStandardItemModel* model;
	void initDataPointTree();//初始化树
	void initDMSNode(QStandardItemModel* model );//初始化所有终端
	void initMVPoint(QStandardItem* parent );//初始化遥测点
	void initDSPPoint(QStandardItem* parent);//初始化遥信点

private slots:
	//void myExpanded(const QModelIndex  index);
	void treeItemChanged(QStandardItem * item);
};