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

	//�½�Զ��ͨ������
	QAction *actionAddRemoteChannel;
	//�½�Զ��ң���㶯��
	QAction *actionAddRemoteAPCPointSection;
	//�½�Զ��ң�ص㶯��
	QAction *actionAddRemoteDPCPointSection;
	//�½�Զ��ң�ŵ㶯��
	QAction *actionAddRemoteDPSPointSection;
	//�½�Զ��ң��㶯��
	QAction *actionAddRemoteMVPointSection;

	//�½�ң���㶯��
	QAction *actionAddRemoteAPCPoint;
	//�½�ң�ص㶯��
	QAction *actionAddRemoteDPCPoint;
	//�½�ң�ŵ㶯��
	QAction *actionAddRemoteDPSPoint;
	//�½�ң��㶯��
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