#include "taskBuilder.h"
#include "db/DbFunc.h"

//CGlobalData& CTaskBuilder::gData = CGlobalData::instance();

// ˼·����
// ��ȡһ�����õ�process��Ϣ����ȡ���process��Ӧ��rate��rates
// ��ȡһ��rate�����±���
// ����porcess�Ļ�����Ϣ����porcessStatus���л�ȡ��ʷ�����´���ʱ�䣬�������ʱ�䣬�Լ�step�ж��Ƿ���Ҫ�½�task
// ��Ҫ�����µ�task���������porcessTask����
// �����������дprocessStatus���ʱ�䣬��ֹ���²�������

const string CTaskBuilder::logTag = "taskBuilder";

CTaskBuilder::CTaskBuilder():log(CLogObj::instance()),gData(CGlobalData::instance())
{
	logInfo = newLogInfo(logTag);
}

CTaskBuilder::~CTaskBuilder()
{
	int a = 0;
	a++;
	CDbObj::release();
}

void CTaskBuilder::run()
{
	bool hasTask = false;
	while (true)
	{
		hasTask = false;
		for (auto& rateIter : gData.processRates)
		{
			if(runOneRate(rateIter.first, rateIter.second) && !hasTask)
			{
				hasTask = true;
			}
		}
		if (!hasTask)
		{
			::Sleep(longSleepTime);
			//::Sleep(shortSleepTime);
		}
	}
}

bool CTaskBuilder::runOneRate( string rateName, list<string>& processTypeNames )
{
	bool hasTask = false;
	for(string& processTypeName :processTypeNames)
	{
		CProcessType* pPorcessType = gData.getProcessType(processTypeName);
		if(pPorcessType != nullptr)
		{
			if (runOneProcessType(rateName, *pPorcessType) && !hasTask)
			{
				hasTask = true;
			}
		}	
	}
	return hasTask;
}

bool CTaskBuilder::runOneProcessType(string rateName, CProcessType& processType )
{
	bool hasTask = false;
	string tableName = PubFun::strFormat("%s.currency_pair_%s", florexDbName.c_str(), rateName.c_str());
	time_t rateLastTime = getRateLastTime(rateName);
	string porcessTypeName = processType.getProcessName();
	PRow processStatusInfo = CDbFunc::getProcessStatusLine(rateName, porcessTypeName);
	//��ȡ��һ�е�ֵ
	time_t processBuildLastTime = 0;
	if(nullptr != processStatusInfo)
	{
		processBuildLastTime = PubFun::stringToInt(processStatusInfo->getValue(CProcessStatusStruct::key_buildTaskLastTime));
	}
	else
	{
		auto tableSt = CProcessStatusStruct::instence();
		processStatusInfo = newRow(tableSt);
		processStatusInfo->setIntValue(CProcessStatusStruct::key_processId, ++(tableSt->idCount));
		processStatusInfo->setStringValue(CProcessStatusStruct::key_rateName, rateName);
		processStatusInfo->setStringValue(CProcessStatusStruct::key_processTypeName, porcessTypeName);
		processStatusInfo->setIntValue(CProcessStatusStruct::key_processStatus, 0);
		processStatusInfo->setTimeValue(CProcessStatusStruct::key_buildTaskLastTime, 0);
		processStatusInfo->setTimeValue(CProcessStatusStruct::key_completeTaskLastTime, 0);
		// ��ȡrate����ʼʱ�����
		processBuildLastTime = getRateStartTime(rateName);
		processStatusInfo->save();
	}

	time_t timeStep = rateLastTime - processBuildLastTime;
	if (timeStep > processType.timeStep )
	{
		hasTask = true;
		PProcessTaskInfoStruct taskInfoStruct = CProcessTaskInfoStruct::instence();
		PRow taskInfo = newRow(taskInfoStruct);
		taskInfo->setStringValue(CProcessTaskInfoStruct::key_rate, rateName);
		taskInfo->setStringValue(CProcessTaskInfoStruct::key_rateType, rateName);
		taskInfo->setStringValue( CProcessTaskInfoStruct::key_taskId, PubFun::get14CurTimeString() + "_" + PubFun::intToString(rand()));
		taskInfo->setTimeValue(CProcessTaskInfoStruct::key_startTime, processBuildLastTime);
		taskInfo->setStringValue(CProcessTaskInfoStruct::key_startTimeDesc, PubFun::getTimeFormat(processBuildLastTime));
		time_t endTime = processBuildLastTime + timeStep/processType.timeStep * processType.timeStep;
		taskInfo->setTimeValue(CProcessTaskInfoStruct::key_endTime, endTime);
		taskInfo->setStringValue(CProcessTaskInfoStruct::key_endTimeDesc, PubFun::getTimeFormat(endTime));
		taskInfo->setStringValue(CProcessTaskInfoStruct::key_processTypeName, processType.getType());
		string strParam = PubFun::strFormat("timeStep=%d", processType.timeStep);
		taskInfo->setStringValue(CProcessTaskInfoStruct::key_paramter, strParam);
		taskInfo->setStringValue(CProcessTaskInfoStruct::key_status, string("0"));
		taskInfo->save();

		processStatusInfo->setTimeValue(CProcessStatusStruct::key_buildTaskLastTime, endTime);
		//processStatusInfo->setStringValue(CProcessStatusStruct::key_buildTaskLastTimeDesc, PubFun::getTimeFormat(endTime));
		processStatusInfo->save();
	}
	return hasTask;
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


