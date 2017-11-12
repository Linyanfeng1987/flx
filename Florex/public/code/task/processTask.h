#pragma once
#include <string>
#include "table/TableStruct.h"
#include "table/Field.h"
#include "table/Row.h"

using namespace std;
class CProcessTask
{
public:
	CProcessTask();
	~CProcessTask();

	static CTableStruct tableStruct;
	static string fields[];

	void load(CRow *pRow);

	string getTaskId();
	string getRateName();
	int getRateType();
	time_t getStartTime();
	time_t getEndTime();
	string getProcessName();
	string getParamter();
	int getStatus();

protected:
	string taskId;
	// ָ��Ԫ���ݵ�����
	string rateName;
	int rateType;
	time_t startTime;
	time_t endTime;

	// ָ������ʽ
	string processName;
	// process�Ĳ������Զ��ŷָ�
	string paramter;
	// ״̬ 0.��ʼ���� 1.�����У�2. �������
	int status;  

	CRow* pRow;
};