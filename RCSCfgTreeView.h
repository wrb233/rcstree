#ifndef RCSCFGTREEVIEW_H
#define RCSCFGTREEVIEW_H

#include "common.h"
#include "ui_rcsconfigtree.h"

class RCSCfgTreeView: public QWidget
{
	Q_OBJECT
public:
	RCSCfgTreeView( QWidget* parent=0, Qt::WindowFlags flags=0 );
	~RCSCfgTreeView();

	void updateTreeModel();
private:
	Ui::RCSConfigTreeUI ui;
	QStandardItemModel* treeModel;

	QMenu *treePopMenu;
	
	QAction *actionFresh;
	
	QAction *actionDelete;

	QAction *actionAddRemoteStation;

	//新建远传通道动作
	QAction *actionAddRemoteChannel;
	//新建远传遥调点动作
	QAction *actionAddRemoteAPCPointSection;
	//新建远传遥控点动作
	QAction *actionAddRemoteDPCPointSection;
	//新建远传遥信点动作
	QAction *actionAddRemoteDPSPointSection;
	//新建远传遥测点动作
	QAction *actionAddRemoteMVPointSection;

	//新建遥调点动作
	QAction *actionAddRemoteAPCPoint;
	//新建遥控点动作
	QAction *actionAddRemoteDPCPoint;
	//新建遥信点动作
	QAction *actionAddRemoteDPSPoint;
	//新建遥测点动作
	QAction *actionAddRemoteMVPoint;


	QList<QAction*> allActions;
	QStandardItem* curTreeItem;

	void initTreeview();
	void initTreePopMenu();
	void addTreeItem(QStandardItem* parent);


	bool judgeRemoteAPCPointSection(ObId obidOfRemoteStationObid);
	bool judgeRemoteDPCPointSection(ObId obidOfRemoteStationObid);
	bool judgeRemoteDPSPointSection(ObId obidOfRemoteStationObid);
	bool judgeRemoteMVPointSection(ObId obidOfRemoteStationObid);


signals:
	void signalFreshTable(ObId parentId);

private slots:
	void slotTreeContextMenu(const QPoint pos);
	
	void slotTreeFresh();
	
	void slotTreeDelete();

	void slotAddRemoteAPCPointSection();
	void slotAddRemoteDPCPointSection();
	void slotAddRemoteDPSPointSection();
	void slotAddRemoteMVPointSection();


	void slotAddRemoteAPCPoint();
	void slotAddRemoteDPCPoint();
	void slotAddRemoteDPSPoint();
	void slotAddRemoteMVPoint();


	void slotTreeExpanded(const QModelIndex  index);
	void slotDoubleClickTreeNode(const QModelIndex index);
};

#endif