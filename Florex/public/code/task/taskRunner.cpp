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
	PProcessTaskInfoStruct taskInfoStruct = CProcessTaskInfoStruct::instence();
	string sql = taskInfoStruct->getSelectSql("status = 0");
	PTable table = newTable(taskInfoStruct);
	db.SelectData(sql.c_str(), table);

	for(auto it : *table)
	{
		it.second->setStringValue(CProcessTaskInfoStruct::key_status, "1");
		it.second->save();
		gData.addProcessTaskInfo(it.second);

		hasData = true;
	}
	return hasData;
}

void CtaskRunner::rangTaskList()
{
	// ִ������
	PRow processTaskInfo = gData.popProcessTaskInfo();
	if(nullptr != processTaskInfo)
	{
		PProcessTask task = getProcessTask(processTaskInfo);
		if(nullptr != task)
		{
			string param = processTaskInfo->getStringValue(CProcessTaskInfoStruct::key_paramter);
			task->run(param.c_str());
		}
		runingTasks.insert(make_pair(task->getTaskId(), task));
	}
	else
	{	if (!reloadTaskList())
		{
			::Sleep(1000);
		}
	}
}

// ͨ��info���ɶ�Ӧ�����process
PBaseProcess CtaskRunner::getProcess( PRow taskInfo )
{
	PBaseProcess process = nullptr;
	if (taskInfo->getStringValue(CProcessTaskInfoStruct::key_processTypeName) == "average")
	{
		process = newAverageProcess(); 
	}
	return process;
}

PProcessTask CtaskRunner::getProcessTask( PRow taskInfo )
{
	PBaseProcess pProcess = getProcess(taskInfo);
	PRow processStatus = CDbFunc::getProcessStatusLine(taskInfo->getStringValue(CProcessTaskInfoStruct::key_processTypeName));

	PProcessTask task = newProcessTask(taskInfo, processStatus, pProcess);

	return task;
}


