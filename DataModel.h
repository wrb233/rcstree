#pragma once

#include "common.h"
#include "MyEnum.h"

class ColumInfo
{
public:
	QString COLUMN_NAME;
	ColumDateTypeEnum DATA_TYPE;
	int DATA_LENGTH;
	int DATA_PRECISION;
	int DATA_SCALE;
	QString NULLABLE;

	ColumInfo()
	{
		this->COLUMN_NAME = "";
		this->DATA_TYPE = ENUM_UNKNOW;
		this->DATA_LENGTH = -1;
		this->DATA_PRECISION = -1;
		this->DATA_SCALE = -1;
		this->NULLABLE = "UNKNOW";		
	}
};

class InsertData
{
public:
	int id;
	ObId parentId;
	OType otype;
	QList<QStandardItem*> insertDatas;

	InsertData(int id,ObId parentId,OType otype,QList<QStandardItem*> insertDatas)
	{
		this->id = id;
		this->parentId = parentId;
		this->otype = otype;
		this->insertDatas = insertDatas;
	}
};
