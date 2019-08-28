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

CTaskBuilder::CTaskBuilder() :log(CLogObj::instance()), gData(CGlobalData::instance())
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
	for (auto& rateIter : gData.processRates)
	{
		buildThreadByRate(rateIter.first, rateIter.second);
	}

	bool hasTask = false;
	while (true)
	{
		hasTask = buildByThread();
		if (!hasTask)
		{
			::Sleep(longSleepTime);
			//::Sleep(shortSleepTime);
		}
	}
}

void CTaskBuilder::buildThreadByRate(string rateName, list<string>& processTypeNames)
{
	for (string& processTypeName : processTypeNames)
	{
		CProcessType* pPorcessType = gData.getProcessType(processTypeName);
		if (pPorcessType != nullptr)
		{
			buildThreadByType(rateName, *pPorcessType);
		}
	}
}

void CTaskBuilder::buildThreadByType(string rateName, CProcessType& processType)
{
	//string tableName = PubFun::strFormat("%s.currency_pair_%s", florexDbName.c_str(), rateName.c_str());
	string porcessTypeName = processType.getProcessName();
	PRow threadStatusInfo = CDbFunc::getThreadStatusLine(rateName, porcessTypeName);
	int lastThreadId = CDbFunc::getThreadLastId();
	//��ȡ��һ�е�ֵ
	time_t processBuildLastTime = 0;
	time_t taskBuildEndTime = 0;
	if (nullptr == threadStatusInfo)
	{
		// ��ȡrate����ʼʱ�����
		processBuildLastTime = getRateStartTime(rateName);
		log.debug(logInfo, PubFun::strFormat("get buildLastTime from rateStartTime %ld", processBuildLastTime));

		auto tableSt = CThreadStatusStruct::instence();
		threadStatusInfo = newRow(tableSt);
		threadStatusInfo->setIntValue(CThreadStatusStruct::key_threadId, ++(lastThreadId));
		threadStatusInfo->setStringValue(CThreadStatusStruct::key_rateName, rateName);
		threadStatusInfo->setStringValue(CThreadStatusStruct::key_threadTypeName, porcessTypeName);
		threadStatusInfo->setIntValue(CThreadStatusStruct::key_threadStatus, 0);
		threadStatusInfo->setTimeValue(CThreadStatusStruct::key_stepTime, processType.timeStep);
		threadStatusInfo->setTimeValue(CThreadStatusStruct::key_buildTaskLastTime, processBuildLastTime);
		threadStatusInfo->setTimeValue(CThreadStatusStruct::key_completeTaskLastTime, 0);

		threadStatusInfo->save();
	}
}

bool CTaskBuilder::buildByThread()
{
	bool hasTask = false;
	list<PThreadInfo> threadInfos;
	CDbFunc::getThreadInfos(threadInfos);

	for (PThreadInfo threadInfo : threadInfos)
	{
		//��ȡ��һ�е�ֵ
		time_t processBuildLastTime = 0;
		time_t taskBuildEndTime = 0;
		PRow threadInfoRow = threadInfo->getRowData();
		string rateName = threadInfoRow->getStringValue(CThreadStatusStruct::key_rateName);
		int threadId = threadInfoRow->getIntValue(CThreadStatusStruct::key_threadId);

		processBuildLastTime = threadInfoRow->getTimeValue(CThreadStatusStruct::key_buildTaskLastTime);
		log.debug(logInfo, PubFun::strFormat("get buildLastTime from threadStatusInfo %ld", processBuildLastTime));
		// ��ȡ��ֹʱ��
		string formartEndTime = threadInfoRow->getStringValue(CThreadStatusStruct::key_buildTaskEndTimeDesc);
		log.debug(logInfo, PubFun::strFormat("get buildTaskEndTimeDesc from threadStatusInfo %%s", formartEndTime.c_str()));
		taskBuildEndTime = PubFun::formartTimeToDatetime(formartEndTime.c_str());

		if (0 == processBuildLastTime || -1 == processBuildLastTime)
		{
			// ͨ���ⲿ���õ���ʼʱ�䣬����processBuildLastTime
			string formatStartTime = threadInfoRow->getStringValue(CThreadStatusStruct::key_buildTaskStartTimeDesc);
			processBuildLastTime = PubFun::formartTimeToDatetime(formatStartTime.c_str());
			if (0 == processBuildLastTime || -1 == processBuildLastTime)
			{
				//  ͨ��rate��ʼʱ�乹��
				processBuildLastTime = getRateStartTime(rateName);
			}
			threadInfoRow->setTimeValue(CThreadStatusStruct::key_buildTaskLastTime, processBuildLastTime);
			threadInfoRow->setStringValue(CThreadStatusStruct::key_buildTaskLastTimeDesc, PubFun::getTimeFormat(processBuildLastTime));
			threadInfoRow->save();
		}

		if (0 == taskBuildEndTime || -1 == taskBuildEndTime)
		{
			// ʹ��rate��ʱ���滻
			taskBuildEndTime = getRateLastTime(rateName);
			log.debug(logInfo, PubFun::strFormat("get rateLastTime by rate:%s value:%ld", rateName.c_str(), taskBuildEndTime));
		}

		PProcessTaskInfoStruct taskInfoStruct = CProcessTaskInfoStruct::instence();
		time_t timeStep = taskBuildEndTime - processBuildLastTime;
		while (processBuildLastTime + gHisCalcStepTime < taskBuildEndTime)
		{
			hasTask = true;
			PRow taskInfo = newRow(taskInfoStruct);
			taskInfo->setStringValue(CProcessTaskInfoStruct::key_rate, rateName);
			taskInfo->setStringValue(CProcessTaskInfoStruct::key_rateType, rateName);
			taskInfo->setStringValue(CProcessTaskInfoStruct::key_taskId, PubFun::get14CurTimeString() + "_" + PubFun::intToString(rand()));
			taskInfo->setTimeValue(CProcessTaskInfoStruct::key_startTime, processBuildLastTime);
			taskInfo->setStringValue(CProcessTaskInfoStruct::key_startTimeDesc, PubFun::getTimeFormat(processBuildLastTime));
			processBuildLastTime += gHisCalcStepTime;
			taskInfo->setTimeValue(CProcessTaskInfoStruct::key_endTime, processBuildLastTime);
			taskInfo->setStringValue(CProcessTaskInfoStruct::key_endTimeDesc, PubFun::getTimeFormat(processBuildLastTime));
			taskInfo->setIntValue(CProcessTaskInfoStruct::key_threadId, threadId);
			//string strParam = PubFun::strFormat("timeStep=%d", processType.timeStep);
			taskInfo->setStringValue(CProcessTaskInfoStruct::key_paramter, string(""));
			taskInfo->setIntValue(CProcessTaskInfoStruct::key_status, taskStatus_def);
			taskInfo->save();

			threadInfoRow->setTimeValue(CThreadStatusStruct::key_buildTaskLastTime, processBuildLastTime);
			threadInfoRow->setStringValue(CThreadStatusStruct::key_buildTaskLastTimeDesc, PubFun::getTimeFormat(processBuildLastTime));
			//threadStatusInfo->setStringValue(CThreadStatusStruct::key_buildTaskLastTimeDesc, PubFun::getTimeFormat(endTime));
			threadInfoRow->save();
		}
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
		it.second->setStringValue(CProcessTaskInfoStruct::key_status, taskStatus_run);
		db.ExecuteSql(it.second->getUpdateSql().c_str());
		gData.addProcessTaskInfo(*(it.second));
		taskConfigs.insert(make_pair(it.second->getStringValue(CProcessTaskInfoStruct::key_taskId), *(it.second)));

		hasData = true;
	}
	return hasData;
}*/

time_t CTaskBuilder::getRateLastTime(string strTableName)
{
	return getRateTime(strTableName, "order by curTime desc, curMsec desc limit 1");
}

time_t CTaskBuilder::getRateStartTime(string strTableName)
{
	return getRateTime(strTableName, "order by curTime, curMsec limit 1");
}

time_t CTaskBuilder::getRateTime(string strTableName, string orderSql)
{
	string strSqlFormat = "select * from %s %s;";
	time_t lastTime = -1;

	char chSql[2048] = { 0 };
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