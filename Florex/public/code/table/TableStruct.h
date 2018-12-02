#pragma once
#include <list>
#include "Field.h"
#include "LinkedHashMap.h"
/*
��¼���ֶ���Ϣ����Ϊ��ṹ�����sql����

��Ҫ��¼�ֶ���Ϣ����sql�����Ľӿ�
*/

class KeyList: public list<string>
{
public:

};


class CTableStruct: public Linked_map<string, CField>
{
public:
	CTableStruct(string strName);
	CTableStruct();
	~CTableStruct();

	void setName(string strName);

	string getCreateTableSql();
	string getDeleteTableSql();

	string getBaseInsertSqlFormat();
	string getBaseUpdateSqlFormat();

	string getSelectSql(string conditicon);

	string getFieldsStr(string split = ",");

	bool tableExist();

	void ensureExist();

// 	string getSql();
// 	string getInsertSql();
// 	string getUpdateSql();
// 	string getDeleteSql();
// 
// 	string getInsertSqlFormat();
// 	string getUpdateSqlFormat();
// 	string getCondition();

	string tableName;

	//KeyList& getKeyFields(){return m_keyFiled;}
	
	//void setKeyField(KeyList tmpList){std::copy(tmpList.begin(), tmpList.end(), std::back_inserter(m_keyFiled)); }

protected:
	//KeyList m_keyFiled;

	string strInsertSqlFormat;
	string strUpdateSqlFormat;
};

typedef shared_ptr<CTableStruct> PTableStruct;
#define newTableStruct(T) make_shared<CTableStruct>(T);