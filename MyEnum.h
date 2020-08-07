#pragma once






enum ColumDateTypeEnum
{
	ENUM_LONG,//number类型细分
	ENUM_DOUBLE,//number类型细分
	ENUM_VARCHAR,
	ENUM_CHAR,
	ENUM_BLOB,
	ENUM_CLOB,
	ENUM_TIMESTAMP,
	ENUM_DATE,
	ENUM_UNKNOW
};

enum MainWidowTypeEnum
{
	ENUM_TABLE_MODE,//表模式
	ENUM_TERMINAL_EDIT,//对象模式
	ENUM_STATE_EDIT,//状态模式
	ENUM_FILE_EDIT//文件模式
};