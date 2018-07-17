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
	CProcessTaskInfoStruct *pTaskInfoStruct = CProcessTaskInfoStruct::instence();
	string sql = pTaskInfoStruct->getSelectSql("status = 0");
	CTable table(pTaskInfoStruct);
	db.SelectData(sql.c_str(), table);

	for(auto it : table)
	{
		it.second.setIntValue(CProcessTaskInfoStruct::key_status, 1);
		db.ExecuteSql(it.second.getUpdateSql().c_str());
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
		CBaseProcess* pProcess = getProcess(*processTaskInfo);
		if(nullptr != pProcess)
		{
			string param = processTaskInfo->getStringValue(CProcessTaskInfoStruct::key_paramter);
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
CBaseProcess* CtaskRunner::getProcess( CRow& taskInfo )
{
	if (taskInfo.getStringValue(CProcessTaskInfoStruct::key_processTypeName) == "acb")
	{
	}
	return nullptr;
}


