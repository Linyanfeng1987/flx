#include "taskRunner.h"
#include "process/averageProcess.h"
#include "db/DbFunc.h"

// �������ݿ⣬������Ӧ�̴߳�������

CDbObj& CtaskRunner::db = CDbObj::instance();
CGlobalData& CtaskRunner::gData = CGlobalData::instance();

void processRun(int value)
{
	CtaskRunner taskRunner;
	taskRunner.run();
}

CtaskRunner::CtaskRunner()
{
	maxProcessCount = 10;
}

CtaskRunner::~CtaskRunner()
{
}

void CtaskRunner::run()
{
	while (true)
	{
		rangTaskList();	
	}
}

bool CtaskRunner::reloadTaskList()
{
	bool hasData = false;
	// �����ݿ��м���δִ�е�����
	CProcessTaskInfoStruct *pTaskInfoStruct = CProcessTaskInfoStruct::instence();
	string sql = pTaskInfoStruct->getSelectSql("status = 0");
	CTable table(pTaskInfoStruct);
	db.SelectData(sql.c_str(), table);

	for(auto it : table)
	{
		it.second.setStringValue(CProcessTaskInfoStruct::key_status, "1");
		it.second.save();
		gData.addProcessTaskInfo(it.second);

		hasData = true;
	}
	return hasData;
}

void CtaskRunner::rangTaskList()
{
	// ִ������
	CRow* processTaskInfo = gData.popProcessTaskInfo();
	if(nullptr != processTaskInfo)
	{
		CProcessTask* pTask = getProcessTask(*processTaskInfo);
		if(nullptr != pTask)
		{
			string param = processTaskInfo->getStringValue(CProcessTaskInfoStruct::key_paramter);
			pTask->run(param.c_str());
		}
		runingTasks.insert(make_pair(pTask->getTaskId(), pTask));
	}
	else
	{	if (!reloadTaskList())
		{
			::Sleep(1000);
		}
	}
}

// ͨ��info���ɶ�Ӧ�����process
CBaseProcess* CtaskRunner::getProcess( CRow& taskInfo )
{
	CBaseProcess* pProcess = nullptr;
	if (taskInfo.getStringValue(CProcessTaskInfoStruct::key_processTypeName) == "average")
	{
		pProcess = new CAverageProcess(); 
	}
	return pProcess;
}

CProcessTask* CtaskRunner::getProcessTask( CRow& taskInfo )
{
	CBaseProcess* pProcess = getProcess(taskInfo);
	CRow processStatus = CDbFunc::getProcessStatusLine(taskInfo.getStringValue(CProcessTaskInfoStruct::key_processTypeName));

	CProcessTask *pTask = new CProcessTask(taskInfo, processStatus, pProcess);

	return pTask;
}


