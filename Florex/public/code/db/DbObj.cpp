#include "../PubFun.h"
#include "Exception.h"
#include "DbObj.h"
#include <regex>
//#include "AutoMutex.h"
#include "tools/FunctionLog.h"
#include "tools/twiceLog.h"
#pragma comment(lib, "libmysql.lib")

CDbObj* CDbObj::g_db = nullptr;
map<std::thread::id, CDbObj*>* CDbObj::pDbMap = nullptr;
//recursive_mutex CDbObj::dbMutex;
const string CDbObj::logTag = "db";

CDbObj& CDbObj::instance()
{
	if (nullptr == pDbMap)
	{
		pDbMap = new map<std::thread::id, CDbObj*>;
	}

	std::thread::id threadId = std::this_thread::get_id();
	auto findRes = pDbMap->find(threadId);
	if (pDbMap->end() == findRes)
	{
		auto insertRes = pDbMap->insert(make_pair(threadId, new CDbObj));
		findRes = insertRes.first;
	}

	return *(findRes->second);
}

void CDbObj::release()
{
	std::thread::id threadId = std::this_thread::get_id();
	auto findRes = pDbMap->find(threadId);
	if (pDbMap->end() != findRes)
	{
		delete findRes->second;
		findRes->second = nullptr;
		pDbMap->erase(findRes);
	}
}

CDbObj::CDbObj(void) :log(CLogObj::instance())
{
	testLogInfo = newLogInfo2(logTag, log_noLog);
	dbLogInfo = newLogInfo(logTag);
	isMySqlInit = false;
}

CDbObj::~CDbObj(void)
{
	CFunctionLog funLog(testLogInfo, __FUNCTION__, __LINE__);
	mysql_close(&mysql);
}

void CDbObj::startTransaction()
{
	mysql_query(&mysql, "START TRANSACTION"); // �������� ���û�п���������ôЧ�ʻ��÷ǳ����£�
}

void CDbObj::commit()
{
	mysql_query(&mysql, "COMMIT"); // �ύ����
}

PRow CDbObj::selectOneData(const char* sql, PTableStruct tableStruct)
{
	string strLog = "selectData:" + string(sql);
	PRow row = nullptr;
	CTwiceLog logAgent(dbLogInfo, log_debug, strLog, string("select end"));
	//CAutoMutex localMutex(&dbMutex);
	CFunctionLog funLog(testLogInfo, __FUNCTION__, __LINE__);
	tryConnect();

	int nRes = mysql_query(&mysql, sql);
	string strMsg = "";
	if (0 == nRes)
	{
		MYSQL_ROW pRow = nullptr;
		MYSQL_RES* pRes = nullptr;
		pRes = mysql_store_result(&mysql);
		if (pRes == nullptr)
		{
			throwSqlError(sql);
		}
		while (pRow = mysql_fetch_row(pRes))
		{
			row = newRow(tableStruct);
			char* pDataValue = *pRow;
			auto fieldIter = tableStruct->begin();
			while (tableStruct->end() != fieldIter)
			{
				row->setAndaddValue(fieldIter->first, string(pDataValue));
				pDataValue = *(++pRow);
				fieldIter++;
			}

			row->setDataStatus(DATA_SAME);
			break;
		}
		mysql_free_result(pRes);
	}
	else
	{
		throwSqlError(sql);
	}

	return row;
}

void CDbObj::selectData(const char* sql, PTable resTable)
{
	string strLog = "selectData:" + string(sql);
	CTwiceLog logAgent(dbLogInfo, log_debug, strLog, string("select end"));
	resTable->clear();
	//CAutoMutex localMutex(&dbMutex);
	CFunctionLog funLog(testLogInfo, __FUNCTION__, __LINE__);
	log.ext(testLogInfo, PubFun::strFormat("%s::tryConnect", __FUNCTION__));
	tryConnect();

	log.ext(testLogInfo, PubFun::strFormat("%s::mysql_query", __FUNCTION__));
	int nRes = mysql_query(&mysql, sql);
	string strMsg = "";
	if (0 == nRes)
	{
		MYSQL_ROW pRow = nullptr;
		MYSQL_RES* pRes = nullptr;
		log.ext(testLogInfo, PubFun::strFormat("%s::mysql_store_result", __FUNCTION__));
		pRes = mysql_store_result(&mysql);
		if (pRes == nullptr)
		{
			throwSqlError(sql);
		}
		log.ext(testLogInfo, PubFun::strFormat("%s::mysql_fetch_row", __FUNCTION__));
		long nCount = 0;
		while (pRow = mysql_fetch_row(pRes))
		{
			log.ext(testLogInfo, PubFun::strFormat("%s::mysql_fetch_row count %d", __FUNCTION__, nCount++));
			PRow row = newRow(resTable->tableStruct);
			char* pDataValue = *pRow;
			auto fieldIter = resTable->tableStruct->begin();
			while (resTable->tableStruct->end() != fieldIter)
			{
				row->setAndaddValue(fieldIter->first, string(pDataValue));
				pDataValue = *(++pRow);
				fieldIter++;
			}
			row->setDataStatus(DATA_SAME);
			resTable->addRow(row);
		}
		log.ext(testLogInfo, PubFun::strFormat("%s::mysql_free_result", __FUNCTION__));
		mysql_free_result(pRes);
	}
	else
	{
		log.ext(testLogInfo, PubFun::strFormat("%s::throwSqlError", __FUNCTION__));
		throwSqlError(sql);
	}
}

void CDbObj::executeSql(const char* sql)
{
	string strLog = "excecuteSql:";
	strLog += sql;
	CTwiceLog logAgent(dbLogInfo, log_debug, strLog, string("excecuteSql end"));
	//CAutoMutex localMutex(&dbMutex);
	CFunctionLog funLog(testLogInfo, __FUNCTION__, __LINE__);
	log.ext(testLogInfo, PubFun::strFormat("%s::tryConnect", __FUNCTION__));
	tryConnect();
	log.ext(testLogInfo, PubFun::strFormat("%s::baseExecuteSql", __FUNCTION__));
	baseExecuteSql(sql);
}

void CDbObj::baseExecuteSql(const char* sql)
{
	if (mysql_query(&mysql, sql) == 0)
	{
		MYSQL_RES* pRes = nullptr;
		pRes = mysql_store_result(&mysql);
		if (pRes != nullptr)
		{
			mysql_free_result(pRes);
		}
	}
	else
	{
		throwSqlError(sql);
	}
}

void CDbObj::tryConnect()
{
	if (!isMySqlInit)
	{
		initMySQL();
	}

	// 0Ϊ��������
	int pinRes = mysql_ping(&mysql);
	string strMsg = mysql_error(&mysql);
	log.ext(testLogInfo, PubFun::strFormat("%s::mysql_ping, res:%d", __FUNCTION__, pinRes));
	if (0 != pinRes)
	{
		connectDefDb();
	}
}

void CDbObj::connectDefDb()
{
	char* host = "localhost";
	char* user = "root";
	unsigned int port = 3306;
	char* passwd = "101050";
	char* dbname = "";
	char* charset = "GBK";//֧������
	string strMsg = "";//��Ϣ����
	char* Msg = "";

	connectMySQL(host, port, dbname, user, passwd, charset, strMsg);
	printf("���ӳɹ�\r\n");
}

void CDbObj::connectMySQL(char* host, unsigned int port, char* Db, char* user, char* passwd, char* charset, string& strMsg)
{
	log.ext(testLogInfo, PubFun::strFormat("%s::connectMySQL", __FUNCTION__));
	if (nullptr == mysql_real_connect(&mysql, host, user, passwd, NULL, port, NULL, 0))
	{
		throwSqlError();
	}
}

void CDbObj::initMySQL()
{
	//CAutoMutex localMutex(&dbMutex);
	CFunctionLog funLog(testLogInfo, __FUNCTION__, __LINE__);
	bool bRes = false;
	log.ext(testLogInfo, PubFun::strFormat("%s::mysql_library_init", __FUNCTION__));
	int nRes = mysql_library_init(0, NULL, NULL);
	if (0 == nRes) {
		log.ext(testLogInfo, PubFun::strFormat("%s::mysql_init", __FUNCTION__));
		if (NULL != mysql_init(&mysql))
		{
			log.ext(testLogInfo, PubFun::strFormat("%s::connectDefDb", __FUNCTION__));
			connectDefDb();
			log.ext(testLogInfo, PubFun::strFormat("%s::mysql_set_character_set", __FUNCTION__));
			if (0 == mysql_set_character_set(&mysql, "GBK"))
			{
				bRes = true;
				isMySqlInit = true;
			}
		}
	}

	if (!bRes)
	{
		log.ext(testLogInfo, PubFun::strFormat("%s::throwSqlError", __FUNCTION__));
		throwSqlError();
	}
}

void CDbObj::insertDatas(list<string> sqls)
{
	//CAutoMutex localMutex(&dbMutex);
	CFunctionLog funLog(testLogInfo, __FUNCTION__, __LINE__);
	tryConnect();

	startTransaction();
	for (string sql : sqls)
	{
		baseInsert(sql);;
	}
	commit();
}

void CDbObj::insertData(string sql)
{
	tryConnect();
	baseInsert(sql);
}

void CDbObj::baseInsert(string sql)
{
	string strLog = "insertSql:";
	strLog += sql;
	PubFun::log(strLog);
	{
		try
		{
			baseExecuteSql(sql.c_str());
		}
		catch (CStrException& e)
		{
			// ������ͻ����ʱ��������
			string msg = e.what();
			regex reg1("^Duplicate entry.*?for key 'PRIMARY'$");
			smatch r1;
			if (!regex_match(msg, r1, reg1))
			{
				//����������ͻ
				throw e;
			}
		}
	}
}

void CDbObj::throwSqlError(string sql)
{
	string strMsg = mysql_error(&mysql);
	unsigned int errorNo = mysql_errno(&mysql);
	log.error(dbLogInfo, PubFun::strFormat("ִ��sqlʧ��:sql:\"%s\", errorMsg=\"%s\"", sql.c_str(), strMsg.c_str()));
	throw CStrException((int)errorNo, strMsg);
}