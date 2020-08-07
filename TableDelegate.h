#pragma once

#include <QStyledItemDelegate>
#include <QItemDelegate>
#include <QModelIndex>
#include <QPainter>
#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QTimeEdit>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QTableView>
#include <QStandardItemModel>
#include "common.h"
#include "GlobalInfo.h"
#include "CellDelegateWidget.h"
#include "MyEnum.h"
#include "AddFolderDialog.h"
class TableDelegate : public QItemDelegate
{
	Q_OBJECT
public:
	TableDelegate(QObject *parent = NULL);
	~TableDelegate();

	void paint(QPainter *painter, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
private:
	
private slots:
	void test();
}; 