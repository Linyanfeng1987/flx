#include "../PubFun.h"
#include "DbObj.h"

CDbObj* CDbObj::g_db = nullptr;

CDbObj::CDbObj(void)
{
	isConnect = false;
}


CDbObj::~CDbObj(void)
{
	if (isConnect)
	{
		db.CloseMySQLConn();
	}
}

void CDbObj::SelectData(const char * SQL,CTable& table )
{
	dbMutex.lock();
	string strLog = "selectData:";
	strLog += SQL;
	PubFun::log(strLog);
	if (!isConnect)
	{
		ConnectDb();
	}
	char* Msg = "";
	int cNum = (int)table.m_tableStruct->size();
	string strRes = db.SelectData(SQL, cNum, Msg);

	list<string> rows = PubFun::split(strRes, "\n");
	list<string>::iterator rowIter = rows.begin();
	for(;rowIter != rows.end(); rowIter++)
	{
		CRow rowObj(table.m_tableStruct);
		list<string> values = PubFun::split(*rowIter, ",");
		rowObj.addByList(values);
		
		table.addRow(rowObj);
	}
	dbMutex.unlock();
}

bool CDbObj::ExecuteSql( const char * SQL )
{
	dbMutex.lock();
	string strLog = "excecuteSql:";
	strLog += SQL;
	PubFun::log(strLog);
	if(!isConnect)
	{
		ConnectDb();
		isConnect = true;
	}

	bool bRes = db.ExecuteSql(SQL);
	dbMutex.unlock();
	return bRes;
}

void CDbObj::ConnectDb()
{
	char* host="localhost";
	char* user="root";
	char* port ="3306";
	char* passwd="101050";
	char* dbname=""; 
	char* charset = "GBK";//֧������
	string strMsg = "";//��Ϣ����
	char* Msg = "";

	if(db.ConnMySQL(host,port,dbname,user,passwd,charset,strMsg))
		printf("���ӳɹ�\r\n");
	else
		printf(Msg);

}

CDbObj& CDbObj::instance()
{
	if(g_db == nullptr)
	{
		g_db = new CDbObj;
	}
	return *g_db;
}

void CDbObj::insertDatas( list<string> sqls )
{
	dbMutex.lock();
	if(!isConnect)
	{
		ConnectDb();
		isConnect = true;
	}

	db.startTransaction();
	for (string sql : sqls)
	{
		db.ExecuteSql(sql.c_str());;
	}
	db.commit();
	dbMutex.unlock();
}


