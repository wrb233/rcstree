#pragma once

#include "common.h"
#include "DataModel.h"
#include "ui_centertable.h"

class CenterTableView: public CpsWidget
{
	Q_OBJECT
public:

	CenterTableView( QWidget* parent=0, Qt::WindowFlags flags=0 );

	~CenterTableView();

	void freshCommonTableview(QString tableName);
	Ui::CenterTableUI getUi();
	void freshTableview(ObId parentId);
	void freshFullTableview();
	void freshTableviewByList(QList<ObId> sonList);

private:
	Ui::CenterTableUI ui;
	QStandardItemModel* tableModel;
	
	QMenu *tablePopMenu;
	QAction *actionUpdateColum;
	QAction *actionInsertOneRow;
	QAction *actionDeleteSelectedRows;
	QAction *actionLoadAll;
	QList<QAction*> allActions;
	QStandardItem* curTableItem;

	QList<QTableView*> tableViewList;
	QMap<OType,QList<ObId> > displayMap;
	QList<ObId> currentListTemp;//当新增或删除时，临时保存变化
	QString currentTabText;

	QList<ObId> currentList;
	ObId currentParentId;
	int startNum;
	int endNum;
	int currentScollNum;

	QList<ColumInfo> columInfoList;

	void initTableview();
	void initPushButton();
	void initTablePopMenu();

signals:
	void signalFreshTree();


public slots:
	    
		void slotTableFresh(ObId parentId);
		void slotTableFreshByList(QList<ObId> sonList);
		void slotButtonSave();
		void slotButtonCancelSelectAll();
		void slotButtonImportBatch();
		void slotButtonExportBatch();
		void slotButtonDeleteBatch();
		void slotLoadAll();

		void sortByColumn(int column);
		
		void slotTableDataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight );
		void onMyScrollMoved(int num);
		void onTableBtnClicked(const QModelIndex  index);
		void slotTableContextMenu(const QPoint pos);
		void slotUpdateColum();
		void slotInsertOneRow();
		void slotDeleteSelectedRows();
		void choseItem(QModelIndex index);
	    bool eventFilter(QObject *obj, QEvent *e);

		void slotTabChanged(int index);
		//void slotMousePressEvent(QMouseEvent *event);
};