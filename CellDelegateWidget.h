#pragma once

#include "common.h"
#include "ui_celldelegate.h"
#include "PickTreeDialog.h"
#include "GlobalInfo.h"
#include "TreeUtil.h"
#include "ToolUtil.h"

class CellDelegateWidget: public CpsWidget
{
	Q_OBJECT
public:
	CellDelegateWidget( QString displayValue,AType atype, OType otype, ObId parentId,QWidget* parent=0, Qt::WindowFlags flags=0 );
	~CellDelegateWidget();

	QStringList obIds;
	ObId obId;
	Ui::CellDelegateUI ui;

private:
	AType atype;
	OType otype;
	ObId parentId;

public slots:
	void slotCellDialog();
};