#include "taskBuilder.h"
#include "ConstDef.h"
#include "db/dataObj/processTaskInfo.h"

CDbObj& CTaskBuilder::db = CDbObj::instance();
CGlobalData& CTaskBuilder::gData = CGlobalData::instance();

// ˼·����
// ��ȡһ�����õ�process��Ϣ����ȡ���process��Ӧ��rate��rates
// ��ȡһ��rate�����±���
// ����porcess�Ļ�����Ϣ����porcessStatus���л�ȡ��ʷ�����´���ʱ�䣬�������ʱ�䣬�Լ�step�ж��Ƿ���Ҫ�½�task
// ��Ҫ�����µ�task���������porcessTask����
// �����������дprocessStatus���ʱ�䣬��ֹ���²�������
CTaskBuilder::CTaskBuilder()
{
}

CTaskBuilder::~CTaskBuilder()
{
}

void CTaskBuilder::run()
{
	while (true)
	{
		for (auto& iter : gData.porcessConfigs)
		{
			runOneProcessType(iter.second);
		}
		::Sleep(1000);
	}
}

void CTaskBuilder::runOneProcessType( CProcessInfo& porcessConfig )
{
	auto iter = gData.processRates.find(porcessConfig.rate);
	if (iter != gData.processRates.end())
	{
		list<string> rates =iter->second;
		for (string rate : rates)
		{
			runOneRate(rate, porcessConfig);
		}
	}
}

void CTaskBuilder::runOneRate( string rateName, CProcessInfo& porcessConfig )
{
	time_t rateLastTime = getRateLastTime(rateName);
	string porcessName = porcessConfig.getProcessName();
	time_t processLastTime = getProcessLastTime(porcessName);
	time_t timeStep = rateLastTime - processLastTime;
	if (timeStep > porcessConfig.timeStep )
	{
		CProcessTaskInfo taskInfo;
		taskInfo.setRate(rateName);
		taskInfo.setTaskId( PubFun::get14CurTimeString() + "_" + PubFun::intToString(rand()));
		taskInfo.setprocessInfo(porcessConfig);
		gData.addprocessInfo(taskInfo);
	}
}


void CTaskBuilder::reLoadTask()
{
	taskConfigs.clear();
	string strSqlFormat = "select * from %s;";
	string strTableName = coreDbName + ".";
	strTableName += "processtask";

	char chSql[2048] = {0};
	memset(chSql, 0, sizeof(chSql));
	sprintf_s(chSql, strSqlFormat.c_str(), strTableName.c_str());
	CTable resTable;
	db.SelectData(chSql, resTable);

	CTable::iterator iter = resTable.begin();
	for (; iter != resTable.end(); iter++)
	{
		CProcessTaskInfo processTask;
		processTask.load(&(iter->second));
		processTask.getTaskId();
		taskConfigs.insert(make_pair(processTask.getTaskId(), processTask));
	}
}

time_t CTaskBuilder::getRateLastTime( string rateName )
{
	string strSqlFormat = "select * from %s order by curTime desc, curMsec desc limit 1;";
	string strTableName = florexDbName + ".";
	strTableName += "currency_pair_";
	strTableName += rateName;
	time_t lastTime = 0;

	char chSql[2048] = {0};
	memset(chSql, 0, sizeof(chSql));
	sprintf_s(chSql, strSqlFormat.c_str(), strTableName.c_str());
	CTable resTable;
	db.SelectData(chSql, resTable);

	CTable::iterator iter = resTable.begin();
	if (iter != resTable.end())
	{
		//��ȡ��һ�е�ֵ
		lastTime = PubFun::stringToInt(iter->second.getValue("curTime"));
	}
	return lastTime;
}

time_t CTaskBuilder::getProcessLastTime( string processName )
{
	string strSqlFormat = "select * from %s order by lastTime desc limit 1;";
	string strTableName = florexDbName + ".";
	strTableName += "processstatus";
	time_t lastTime = 0;

	char chSql[2048] = {0};
	memset(chSql, 0, sizeof(chSql));
	sprintf_s(chSql, strSqlFormat.c_str(), strTableName.c_str());
	CTable resTable;
	db.SelectData(chSql, resTable);

	CTable::iterator iter = resTable.begin();
	if (iter != resTable.end())
	{
		//��ȡ��һ�е�ֵ
		lastTime = PubFun::stringToInt(iter->second.getValue("curTime"));
	}
	return lastTime;
}



