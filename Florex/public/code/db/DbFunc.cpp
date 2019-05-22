#include "DbFunc.h"
#include "DbObj.h"
#include "LogObj.h"


//CGlobalData& CDbFunc::gData = CGlobalData::instance();
CDbFunc::CDbFunc(void)
{
}


CDbFunc::~CDbFunc(void)
{

}


PRow CDbFunc::getThreadStatusLine( string rateName, string processTypeName )
{
	PThreadStatusStruct tableSt = CThreadStatusStruct::instence();
	string sql = tableSt->getSelectSql(PubFun::strFormat("%s = '%s' and %s = '%s'",
		CThreadStatusStruct::key_rateName.c_str(), rateName.c_str(),
		CThreadStatusStruct::key_processTypeName.c_str(),  processTypeName.c_str()));

	return CDbObj::instance().selectOneData(sql.c_str(), tableSt);
}

int CDbFunc::getThreadLastId()
{
	int lastThreadId = 0;
	PThreadStatusStruct tableSt = CThreadStatusStruct::instence();
	string sql = tableSt->getSelectSqlLimit1(string(""), PubFun::strFormat(" order by %s desc", CThreadStatusStruct::key_threadId.c_str()));

	PRow row = CDbObj::instance().selectOneData(sql.c_str(), tableSt);
	if (nullptr != row)
	{
		lastThreadId = row->getIntValue(CThreadStatusStruct::key_threadId);
	}

	return lastThreadId;
}

void CDbFunc::zeroThreadStatus()
{
	try{
		// �����ݿ��м���δִ�е�����
		PThreadStatusStruct processSt = CThreadStatusStruct::instence();
		string sql = processSt->getSelectSql();
		PTable table = newTable(processSt);
		CDbObj::instance().selectData(sql.c_str(), table);

		for(auto it : *table)
		{
			// ���������߳�״̬
			it.second->setIntValue(CThreadStatusStruct::key_processStatus, 0);
		}
		table->save();
	}
	catch (CStrException& e)
	{
		CLogObj::instance().error(string("firstRun ʧ�ܣ�msg:").append(e.what()));
	}
}
