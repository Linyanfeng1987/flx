#pragma once
#include <mutex>

#include "PubFun.h"
#include "ConstDef.h"
#include "process/processInfo.h"
#include "db/dataObj/processTaskInfo.h"


class CGlobalData
{
public:
	static CGlobalData& instance();
	
	~CGlobalData();

	void loadConfig();

	CProcessType* getProcessType(string processId);

	// process���͵���Ϣ
	map<string, CProcessType> porcessTypes;

	// process���ͣ���Ӧ��rate����
	map<string, list<string> > processRates;

	void addprocessInfo(CProcessTaskInfo cfg);
	CProcessTaskInfo* popprocessInfo();

	map<string, CProcessInfo> porcessConfigs;
protected:
	
	
	list<CProcessTaskInfo> tasks;
	recursive_mutex taskMutex; 
	CGlobalData();
};

