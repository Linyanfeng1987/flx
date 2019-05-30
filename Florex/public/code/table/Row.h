#pragma once
#include <map>
#include <list>
#include <string>
#include <memory>

#include "TableStruct.h"
#include "Field.h"
#include "Value.h"
#include "LogObj.h"

using namespace std;


class CRow : public Linked_map<string, PValue>
{
public:
	// ���Խ���sql������
	CRow(PTableStruct tableStruct);
	~CRow(void);

	void init(PTableStruct tableStruct);

	void setTableStruct(PTableStruct tableStruct){this->tableStruct = tableStruct;}
	PTableStruct getTableStruct(){return tableStruct;}

	bool save();
	bool save2();

	bool isExit();

	void setDataStatus(DATA_STATUS status);

	PValue emptyFind(string key);

	string getSql();
	string getInsertSql();
	string getUpdateSql();
	string getDeleteSql();

	void setAndaddValue(string& strKey, string& strValue);
	void addByList(list<string> valueList);
	string getValue(string& strKey);
	void setValue(string& strKey, string& strValue);
	void setValue(string& strKey, double dValue);


	string getStringValue(string& strKey);
	long getIntValue(string& strKey);
	time_t getTimeValue(string& strKey);
	double getDoubleValue(string& strKey);

	void setStringValue(string& strKey, string& strValue);
	void setIntValue(string& strKey, long lValue);
	void setIndexValue(string& strKey, indexType iValue);
	void setTimeValue(string& strKey, time_t tValue);
	void setDoubleValue(string& strKey, double dValue);

	DATA_STATUS m_dataStatus;

protected:
	CLogObj &log;
	string getCondition();
	PTableStruct tableStruct;
};

typedef shared_ptr<CRow> PRow;
#define newRow(T) make_shared<CRow>(T)

