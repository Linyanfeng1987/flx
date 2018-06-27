#include "taskRunner.h"
#include "db/dataStruct/processTaskInfoStruct.h"

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
	CProcessTaskInfoStruct processTaskInfoStruct;
	string sql = processTaskInfoStruct.getSelectSql("status = 0");
	CTable table;
	db.SelectData(sql.c_str(), table);

	for(auto it : table)
	{
		CProcessTaskInfo processTaskInfo;	
		processTaskInfo.load(&(it.second));
		processTaskInfo.setStatus(1);
		db.ExecuteSql(processTaskInfo.pRow->getUpdateSql().c_str());
		gData.addProcessTaskInfo(processTaskInfo);

		hasData = true;
	}
	return hasData;
}

void CtaskRunner::rangTaskList()
{
	// ִ������
	CProcessTaskInfo* processTaskInfo = gData.popProcessTaskInfo();
	if(nullptr != processTaskInfo)
	{
		CBaseProcess* pProcess = getProcess(*processTaskInfo);
		if(nullptr != pProcess)
		{
			string param = processTaskInfo->getParamter();
			pProcess->detach(param.c_str());
		}
	}
	else
	{	if (!reloadTaskList())
		{
			::Sleep(1000);
		}
	}
}

// ͨ��info���ɶ�Ӧ�����process
CBaseProcess* CtaskRunner::getProcess( CProcessTaskInfo& taskInfo )
{
	if (taskInfo.getProcessTypeName() == "acb")
	{
	}
	return nullptr;
}


