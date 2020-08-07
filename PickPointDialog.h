#pragma once

#include "common.h"
#include "TreeUtil.h"
#include "ui_pickpoint.h"

class PickPointDialog: public CpsDialog
{
	Q_OBJECT
public:

	//���캯��
	PickPointDialog( QWidget* parent=0, Qt::WindowFlags flags=0 );

	void writeSelectPointToFile();//дѡ��ĵ㵽�ļ���
	//QMenu* popMenu;
	//QStandardItem* curItem;

	//��������
	~PickPointDialog();

private:
	Ui::PickPointUI ui;
	QStandardItemModel* model;
	void initDataPointTree();//��ʼ����
	void initDMSNode(QStandardItemModel* model );//��ʼ�������ն�
	void initMVPoint(QStandardItem* parent );//��ʼ��ң���
	void initDSPPoint(QStandardItem* parent);//��ʼ��ң�ŵ�

private slots:
	//void myExpanded(const QModelIndex  index);
	void treeItemChanged(QStandardItem * item);
};