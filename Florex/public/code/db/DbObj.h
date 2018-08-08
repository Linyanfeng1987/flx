#pragma once
#include "VspdCToMySQL.h"
#include "../table/Table.h"
#include <mutex>

class CDbObj
{

protected:
	 CDbObj(void);

	 static CDbObj* g_db;

public:
	~CDbObj(void);
	
	static CDbObj& instance();

	PRow SelectOneData(const char * SQL, PTableStruct tableStruct);

	void SelectData(const char * SQL, PTable resTable);

	bool ExecuteSql(const char * SQL);

	void insertDatas(list<string> sqls);

	void ConnectDb();

private:
	bool isConnect;
	std::mutex dbMutex;
	VspdCToMySQL db;
};

