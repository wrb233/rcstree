#pragma once






enum ColumDateTypeEnum
{
	ENUM_LONG,//number����ϸ��
	ENUM_DOUBLE,//number����ϸ��
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
	ENUM_TABLE_MODE,//��ģʽ
	ENUM_TERMINAL_EDIT,//����ģʽ
	ENUM_STATE_EDIT,//״̬ģʽ
	ENUM_FILE_EDIT//�ļ�ģʽ
};