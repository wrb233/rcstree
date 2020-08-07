#pragma once

#include "common.h"
#include "ui_rcstree.h"
#include "DBUtil.h"
#include "ToolUtil.h"
#include "MyEnum.h"
#include "PickPointDialog.h"
//#include "ImportTableDialog.h"
#include "AddFolderDialog.h"
//#include "PartitionCfgWidget.h"
#include "CenterTableView.h"
#include "ConfigExplorer_export.h"
//#include "DMSCfgTreeView.h"
//#include "DeviceCfgTreeView.h"
//#include "NodeCfgTreeView.h"
#include "RCSCfgTreeView.h"

class RCSTreeMW : public CpsMainWindow
{
	Q_OBJECT

public:
	RCSTreeMW(QWidget *parent = 0, Qt::WindowFlags flags=0 );
	~RCSTreeMW();

private:
	Ui::MainWindow ui;
	QStandardItemModel* treeModel;
	
	QToolButton *RCSEidtBar;
	QLabel *msgLabel;
	QString textStatusbar;

	RCSCfgTreeView* rcsCfgTreeView;
	CenterTableView* centerWidget;
	QWidget* partitionTree;
	QWidget* partitionTable;

	MainWidowTypeEnum currentType;


	
	QMenu *treeRootPopMenu;
	QMenu *treeFolderPopMenu;
	QMenu *treeLeafPopMenu;
	QMenu *treePartitionPopMenu;
	QStandardItem* curTreeItem;

	void initMenuBar();
	void initToolBar();
	void initStatusBar();
	void initTreeview();

	void initTreeRootPopMenu();
	void initTreeFolderPopMenu();
	void initTreeLeafPopMenu();
	void initTreePartitionPopMenu();

	void addTreeItem(QStandardItem* item);
	bool insertTreeNodesToDB();
	bool deleteTreeNodeFromDB();

	void freshStatusBar(int dataNum);

	void keyPressEvent(QKeyEvent *e);
	void closeEvent(QCloseEvent* event);
	//void mousePressEvent(QMouseEvent *e);
	//bool eventFilter(QObject *obj, QEvent *e);

	bool UserCheck();

	int checkNumOfRCS();


private slots:


	
	void slotRCSEdit();
	void slotDoubleClickTreeNode(const QModelIndex index);

	void slotTreeContextMenu(const QPoint pos);
	void slotTreeAddFolder();
	//void slotTreeImportTable();
	void slotTreeLoadTable();
	void slotTreeDelete();
	void slotTreeExpanded(const QModelIndex  index);

	void closeTab();
};
