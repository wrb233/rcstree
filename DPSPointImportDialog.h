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
#include "ui_dpspointimport.h"

class DPSPointImportDialog: public CpsDialog
{
	Q_OBJECT
public:

	DPSPointImportDialog(QStandardItem* parentItem, QWidget* parent=0, Qt::WindowFlags flags=0 );

	~DPSPointImportDialog();

	QList<ObId> getListOfDPSPointObId();

public slots:
	
	void on_okButton_clicked();

private:
	Ui::DPSPointImportDialog ui;
	QStandardItemModel* treeModel;
	QStandardItem* parentItem;

	void initTreeview();
	void updateTreeModel();
	void addTreeItem(QStandardItem* parent);
	void createRemoteTree(QStandardItem *parentItem,ObId parentId,QList<ObId> lstObid);
	void appendTreeItem(QStandardItem *parentItem,ObId curId);
	void writeAttribute(ObId sourceId, ObId dstId);
private slots:

	void slotTreeExpanded(const QModelIndex  index);

};