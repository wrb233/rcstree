#pragma once

#include "common.h"
#include "ToolUtil.h"
#include "GlobalInfo.h"
#include "ui_picktree.h"
#include "DBUtil.h"

class PickTreeDialog: public CpsDialog
{
	Q_OBJECT
public:
	PickTreeDialog( QStandardItemModel* treeModel, QWidget* parent=0, Qt::WindowFlags flags=0 );
	~PickTreeDialog();

	void initMultiCheckTreeview(QString nameList,QString rootName,OType otype,QIcon icon);
	void initSingleTreeview(QString rootName,OType otype,QIcon icon);
	void initDeviceTreeview();
	void initCommonTreeview();
	void initMeasurementTypeLinkTreeview(OType otype);
	void initPointLink(ObId parentId,OType otype);
	void recursiveTreeItem(QStandardItem* parentItem);
	void addTreeItem(QString filter, QStandardItem* parent);

	Ui::PickTreeUI ui;
	bool isClear;
	
private:		
	QStandardItemModel* treeModel;

private slots:
	void slotTreeExpanded(const QModelIndex  index);
	void clear();
};
