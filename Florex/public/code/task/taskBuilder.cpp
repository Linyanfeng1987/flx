#include "taskBuilder.h"
#include "db/DbFunc.h"

CGlobalData& CTaskBuilder::gData = CGlobalData::instance();

// ˼·����
// ��ȡһ�����õ�process��Ϣ����ȡ���process��Ӧ��rate��rates
// ��ȡһ��rate�����±���
// ����porcess�Ļ�����Ϣ����porcessStatus���л�ȡ��ʷ�����´���ʱ�䣬�������ʱ�䣬�Լ�step�ж��Ƿ���Ҫ�½�task
// ��Ҫ�����µ�task���������porcessTask����
// �����������дprocessStatus���ʱ�䣬��ֹ���²�������
CTaskBuilder::CTaskBuilder():log(CLogObj::instance())
{
	
}

CTaskBuilder::~CTaskBuilder()
{
	int a = 0;
	a++;
	CDbObj::release();
}

void CTaskBuilder::run()
{
	CLogInfo logInfo("taskBuilder");
	log.addLogInfo(logInfo);
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
			runOneProcessType(rateName, *pPorcessType);
		}	
	}
}

void CTaskBuilder::runOneProcessType(string rateName, CProcessType& processType )
{
	string tableName = PubFun::strFormat("%s.currency_pair_%s", florexDbName.c_str(), rateName.c_str());
	time_t rateLastTime = getRateLastTime(rateName);
	string porcessName = processType.getProcessName();
	PRow processStatusInfo = CDbFunc::getProcessStatusLine(porcessName);
	//��ȡ��һ�е�ֵ
	time_t processBuildLastTime = 0;
	if(nullptr != processStatusInfo)
	{
		processBuildLastTime = PubFun::stringToInt(processStatusInfo->getValue(CProcessStatusStruct::key_buildTaskLastTime));
	}
	else
	{
		processStatusInfo = newRow(CProcessStatusStruct::instence());
		processStatusInfo->setStringValue(CProcessStatusStruct::key_processName, porcessName);
		processStatusInfo->setIntValue(CProcessStatusStruct::key_processStatus, 0);
		processStatusInfo->setTimeValue(CProcessStatusStruct::key_buildTaskLastTime, 0);
		processStatusInfo->setTimeValue(CProcessStatusStruct::key_completeTaskLastTime, 0);
		// ��ȡrate����ʼʱ�����
		processBuildLastTime = getRateStartTime(rateName);
	}

	time_t timeStep = rateLastTime - processBuildLastTime;
	if (timeStep > processType.timeStep )
	{
		PProcessTaskInfoStruct taskInfoStruct = CProcessTaskInfoStruct::instence();
		PRow taskInfo = newRow(taskInfoStruct);
		taskInfo->setStringValue(CProcessTaskInfoStruct::key_rate, rateName);
		taskInfo->setStringValue(CProcessTaskInfoStruct::key_rateType, rateName);
		taskInfo->setStringValue( CProcessTaskInfoStruct::key_taskId, PubFun::get14CurTimeString() + "_" + PubFun::intToString(rand()));
		taskInfo->setTimeValue(CProcessTaskInfoStruct::key_startTime, processBuildLastTime);
		time_t endTime = processBuildLastTime + timeStep/processType.timeStep * processType.timeStep;
		taskInfo->setTimeValue(CProcessTaskInfoStruct::key_endTime, endTime);
		taskInfo->setStringValue(CProcessTaskInfoStruct::key_processTypeName, processType.getType());
		string strParam = PubFun::strFormat("timeStep=%d", processType.timeStep);
		taskInfo->setStringValue(CProcessTaskInfoStruct::key_paramter, strParam);
		taskInfo->setStringValue(CProcessTaskInfoStruct::key_status, string("0"));
		taskInfo->save();

		processStatusInfo->setTimeValue(CProcessStatusStruct::key_buildTaskLastTime, endTime);
		processStatusInfo->save();
	}
}

/*
bool CTaskBuilder::reloadTaskList_delete()
{
	taskConfigs.clear();
	bool hasData = false;
	// �����ݿ��м���δִ�е�����
	CProcessTaskInfoStruct* pTaskInfo = CProcessTaskInfoStruct::instence();
	string sql = pTaskInfo->getSelectSql("status = 0");
	PTable table(pTaskInfo);
	db.SelectData(sql.c_str(), table)111;

	for(auto it : table)
	{
		it.second->setStringValue(CProcessTaskInfoStruct::key_status, "1");
		db.ExecuteSql(it.second->getUpdateSql().c_str());
		gData.addProcessTaskInfo(*(it.second));
		taskConfigs.insert(make_pair(it.second->getStringValue(CProcessTaskInfoStruct::key_taskId), *(it.second)));

		hasData = true;
	}
	return hasData;
}*/

time_t CTaskBuilder::getRateLastTime( string strTableName )
{
	return getRateTime(strTableName, "order by curTime desc, curMsec desc limit 1");
}

time_t CTaskBuilder::getRateStartTime( string strTableName )
{
	return getRateTime(strTableName, "order by curTime, curMsec limit 1");
}

time_t CTaskBuilder::getRateTime( string strTableName, string orderSql )
{
	string strSqlFormat = "select * from %s %s;";
	time_t lastTime = -1;

	char chSql[2048] = {0};
	memset(chSql, 0, sizeof(chSql));
	PCurRateStruct rateStruct = newCurRateStruct(strTableName);
	sprintf_s(chSql, strSqlFormat.c_str(), rateStruct->tableName.c_str(), orderSql.c_str());
	PTable resTable = newTable(rateStruct);

	CDbObj::instance().selectData(chSql, resTable);
	auto iter = resTable->begin();
	if (iter != resTable->end())
	{
		//��ȡ��һ�е�ֵ
		lastTime = PubFun::stringToInt(iter->second->getValue(string("curTime")));
	}
	
	return lastTime;
}


