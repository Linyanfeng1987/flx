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

	void init();

	void loadConfig();
	// ��ʱ����loadConfig���������е����ݳ�ʼ��
	void initDataInCode();

	CProcessType* getProcessType(string processId);

	// process���͵���Ϣ
	map<string, CProcessType> porcessTypes;

	// process���ͣ���Ӧ��rate����
	map<string, list<string> > processRates;

	void addProcessTaskInfo(CProcessTaskInfo cfg);
	CProcessTaskInfo* popProcessTaskInfo();

	map<string, CProcessInfo> porcessInfos;
protected:
	
	
	list<CProcessTaskInfo> tasks;
	recursive_mutex taskMutex; 
	CGlobalData();
};

