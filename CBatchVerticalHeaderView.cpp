#include "CBatchVerticalHeaderView.h"

#include <QDebug>
#include <QPainter>
#include <QStyle>
#include <QApplication>

static QRect CheckBoxRect(const QRect &rect)/*const*/
{
	//绘制按钮所需要的参数
	QStyleOptionButton checkBoxStyleOption;
	//按照给定的风格参数 返回元素子区域
	QRect checkBoxRect = QApplication::style()->subElementRect( QStyle::SE_CheckBoxIndicator, &checkBoxStyleOption);
	//返回QCheckBox坐标
	QPoint checkBoxPoint(rect.x() + rect.width() / 2 - checkBoxRect.width() / 2,
		rect.y() + rect.height() / 2 - checkBoxRect.height() / 2);
	//返回QCheckBox几何形状
	return QRect(checkBoxPoint, checkBoxRect.size());
}

CBatchVerticalHeaderView::CBatchVerticalHeaderView(QWidget *parent)
	:QHeaderView(Qt::Vertical,parent)
{
	//this->setSectionsClickable(true);//qt5
	this->setClickable(true);//qt4
	this->setMinimumWidth(24);

	connect(this,SIGNAL(sectionClicked(int)),this,SLOT(slotOnSectionClicked(int)));
}

void CBatchVerticalHeaderView::SetAllSelected()
{
	QAbstractItemModel *model = this->model();
	for(int section = 0;section < count();++section)
	{
		QModelIndex index = model->index(section,0);
		model->setData(index,Qt::Checked,CheckedRole);

		this->setVisible(false);
		this->setVisible(true);
	}
}

void CBatchVerticalHeaderView::SetAllUnselected()
{
	QAbstractItemModel *model = this->model();
	for(int section = 0;section < count();++section)
	{
		QModelIndex index = model->index(section,0);
		model->setData(index,Qt::Unchecked,CheckedRole);

		this->setVisible(false);
		this->setVisible(true);
	}
}

void CBatchVerticalHeaderView::SetSelected(int section, bool selected)
{
	if(section < 0 || section >= this->count())
		return;

	QAbstractItemModel *model = this->model();
	QModelIndex index = model->index(section,0);
	Qt::CheckState oppsite = (selected) ? Qt::Checked : Qt::Unchecked;
	model->setData(index,oppsite,CheckedRole);

	this->setVisible(false);
	this->setVisible(true);
}

bool CBatchVerticalHeaderView::IsSelected(int section)
{
	if(section < 0 || section >= this->count())
		return false;

	QAbstractItemModel *model = this->model();
	QModelIndex index = model->index(section,0);
	//Qt::CheckState checked = model->data(index,CheckedRole).value<Qt::CheckState>();
	Qt::CheckState checked = (Qt::CheckState)model->data(index,CheckedRole).toInt();
		

	return (checked == Qt::Checked) ? true : false;
}

void CBatchVerticalHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{  
#if 1
	QAbstractItemModel *model = this->model();
	QModelIndex index = model->index(logicalIndex,0);
	Qt::CheckState checkstate = (Qt::CheckState)model->data(index,CheckedRole).toInt();
	bool checked = (checkstate == Qt::Checked) ? true : false;

	QStyleOptionButton checkBoxStyleOption;
	checkBoxStyleOption.state |= QStyle::State_Enabled;
	checkBoxStyleOption.state |= checked? QStyle::State_On : QStyle::State_Off;
	checkBoxStyleOption.rect = CheckBoxRect(rect);

	QApplication::style()->drawControl(QStyle::CE_CheckBox,&checkBoxStyleOption,painter);
#else
	painter->setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);

	QAbstractItemModel *model = this->model();
	QModelIndex index = model->index(logicalIndex,0);
	Qt::CheckState checkstate = model->data(index,CheckedRole).value<Qt::CheckState>();
	bool checked = (checkstate == Qt::Checked) ? true : false;

	QString pic = checked ? "checked.png" : "unchecked.png";
	painter->drawPixmap(rect,QPixmap(pic));
#endif
}

void CBatchVerticalHeaderView::slotOnSectionClicked(int section)
{
	if(section < 0 || section >= this->count())
		return;

	QAbstractItemModel *model = this->model();
	QModelIndex index = model->index(section,0);
	Qt::CheckState checked = (Qt::CheckState)model->data(index,CheckedRole).toInt();
	Qt::CheckState oppsite = (checked == Qt::Checked) ? Qt::Unchecked : Qt::Checked;
	model->setData(index,oppsite,CheckedRole);
}
