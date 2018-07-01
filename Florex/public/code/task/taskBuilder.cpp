#include "taskBuilder.h"
#include "ConstDef.h"
#include "db/dataObj/processTaskInfo.h"
#include "db/dataStruct/processTaskInfoStruct.h"
#include "db/dataStruct/curRateStruct.h"

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
		for (auto& rateIter : gData.processRates)
		{
			runOneRate(rateIter.first, rateIter.second);
		}
		::Sleep(1000);
	}
}

void CTaskBuilder::runOneRate( string rateName, list<string>& processTypeNames )
{
	for(string& processTypeName :processTypeNames)
	{
		CProcessType* pPorcessType = gData.getProcessType(processTypeName);
		if(pPorcessType != nullptr)
		{
			runOneProcessInfo(rateName, *pPorcessType);
		}	
	}
}

void CTaskBuilder::runOneProcessInfo(string rateName, CProcessType& processType )
{
	time_t rateLastTime = getRateLastTime(rateName);
	string porcessName = processType.getProcessName();
	time_t processLastTime = getProcessLastTime(porcessName);
	time_t timeStep = rateLastTime - processLastTime;
	CProcessInfo processInfo;
	processInfo.init(&processType, rateName);
	if (timeStep > processType.timeStep )
	{
		CProcessTaskInfo taskInfo;
		taskInfo.setTaskId( PubFun::get14CurTimeString() + "_" + PubFun::intToString(rand()));
		taskInfo.setprocessInfo(processInfo);
		taskInfo.setStatus(0);
		gData.addProcessTaskInfo(taskInfo);
	}
}


bool CTaskBuilder::reloadTaskList()
{
	taskConfigs.clear();
	bool hasData = false;
	// �����ݿ��м���δִ�е�����
	CProcessTaskInfoStruct processTaskInfoStruct;
	string sql = processTaskInfoStruct.getSelectSql("status = 0");
	CTable table(&processTaskInfoStruct);
	db.SelectData(sql.c_str(), table);

	for(auto it : table)
	{
		CProcessTaskInfo processTaskInfo;	
		processTaskInfo.load(&(it.second));
		processTaskInfo.setStatus(1);
		db.ExecuteSql(processTaskInfo.pRow->getUpdateSql().c_str());
		gData.addProcessTaskInfo(processTaskInfo);
		taskConfigs.insert(make_pair(processTaskInfo.getTaskId(), processTaskInfo));

		hasData = true;
	}
	return hasData;
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
	CCurRateStruct rateStruct;
	CTable resTable(&rateStruct);
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
	CCurRateStruct rateStruct;
	CTable resTable(&rateStruct);
	db.SelectData(chSql, resTable);

	CTable::iterator iter = resTable.begin();
	if (iter != resTable.end())
	{
		//��ȡ��һ�е�ֵ
		lastTime = PubFun::stringToInt(iter->second.getValue("curTime"));
	}
	return lastTime;
}



