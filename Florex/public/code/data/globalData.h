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

	CProcessType* getProcessType(string processId);

	// process���͵���Ϣ
	map<string, CProcessType> porcessTypes;

	// process���ͣ���Ӧ��rate����
	map<string, list<string> > processRates;

	void addProcessTaskInfo(CRow cfg);
	CRow* popProcessTaskInfo();

	map<string, CRow> porcessInfos;
protected:
	//map<string, CTableStruct> 
	
	CTable tasks;
	recursive_mutex taskMutex; 
	CGlobalData();
};

