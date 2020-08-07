#pragma once

#include "common.h"
#include "TreeUtil.h"
#include "ToolUtil.h"
#include "DBUtil.h"
//#include "OTypeAndATypeInit.h"
#include "GlobalInfo.h"

#include "APCPointImportDialog.h"
#include "DPCPointImportDialog.h"
#include "DPSPointImportDialog.h"
#include "MVPointImportDialog.h"
#include "ui_apcpointimport.h"

class APCPointImportDialog: public CpsDialog
{
	Q_OBJECT
public:

	APCPointImportDialog(QStandardItem* parentItem, QWidget* parent=0, Qt::WindowFlags flags=0 );

	~APCPointImportDialog();

	QList<ObId> getListOfAPCPointObId();

public slots:

	void on_okButton_clicked();

private:
	Ui::APCPointImportDialog ui;
	QStandardItemModel* treeModel;
	QStandardItem* parentItem;
	
	void initTreeview();
	void updateTreeModel();
	void addTreeItem(QStandardItem* parent);
	void createRemoteTree(QStandardItem *parentItem,ObId parentId,QList<ObId> lstObid);
	void appendTreeItem(QStandardItem *parentItem,ObId curId);
	void writeAttribute(ObId sourceId, ObId dstId, int next);
private slots:
	
	void slotTreeExpanded(const QModelIndex  index);

};