#pragma once
#include "baseObj.h"

class CProcessTask : public CBaseObj
{
public:
	CProcessTask();
	~CProcessTask();

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