#pragma once
#include "db/dataObj/processTaskInfo.h"

// task����������
class CProcessTask
{
public:
	CProcessTask();
	~CProcessTask();

	void setProcessTaskConfig(CProcessTaskInfo* pConfig){this->pConfig = pConfig;}
	int run();
protected:
	CProcessTaskInfo* pConfig;

};
