#pragma once
#include <mutex>

#include "PubFun.h"
#include "ConstDef.h"
#include "process/processType.h"
#include "db/dataStruct/processTaskInfoStruct.h"
#include "table/Table.h"

class CGlobalData
{
public:
	static CGlobalData& instance();
	
	~CGlobalData();

	void init();

	void loadConfig();
	// ��ʱ����loadConfig���������е����ݳ�ʼ��
	void initDataInCode();

	void initDataInXml();

	CProcessType* getProcessType(string processId);

	// process���͵���Ϣ
	map<string, CProcessType> porcessTypes;

	// process���ͣ���Ӧ��rate����
	map<string, list<string> > processRates;

	void addProcessTaskInfo(PRow cfg);
	PRow popProcessTaskInfo();

	map<string, PRow> porcessInfos;
protected:
	//map<string, PTableStruct> 
	
	PTable tasks;
	recursive_mutex taskMutex; 
	CGlobalData();
};

