#pragma once
#include <mutex>

#include "PubFun.h"
#include "ConstDef.h"
#include "process/processType.h"
#include "table/Table.h"
#include "LogObj.h"
#include "Exception.h"


#include "db/dataStruct/processTaskInfoStruct.h"
#include "db/dataStruct/processStatusStruct.h"
#include "db/dataStruct/testDbInfoStruct.h"

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

	void initDataStruct();

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

	CLogObj& log;
};

