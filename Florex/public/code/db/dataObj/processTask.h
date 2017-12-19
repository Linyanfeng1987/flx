#pragma once
#include "baseObj.h"

class CProcessTask : public CBaseObj
{
public:
	CProcessTask();
	~CProcessTask();

	static string fields[];

	string getTaskId();
	string getRateName();
	int getRateType();
	time_t getStartTime();
	time_t getEndTime();
	string getProcessTypeName();
	string getParamter();
	int getStatus();


	void setTaskId(string taskId);
	void setRateName(string rateName);
	void setRateType(int rateType);
	void setStartTime(time_t startTime);
	void setEndTime(time_t endTime);
	void setProcessTypeName(string processTypeName);
	void setParamter(string paramter);
	void setStatus(int status);
protected:
	string taskId;
	// ָ��Ԫ���ݵ�����
	string rateName;
	int rateType;
	time_t startTime;
	time_t endTime;

	// ָ������ʽ
	string processTypeName;
	// process�Ĳ������Զ��ŷָ�
	string paramter;
	// ״̬ 0.��ʼ���� 1.�����У�2. �������
	int status;  
};