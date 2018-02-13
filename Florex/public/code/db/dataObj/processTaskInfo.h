#pragma once
#include "baseObj.h"
#include "process/processInfo.h"

/*
CProcessTask = config + srcdata + timestep
*/
// ���������Ϣ����������Ĳ�����Ϣ
class CProcessTaskInfo : public CBaseObj
{
public:
	CProcessTaskInfo();
	~CProcessTaskInfo();

	static string fields[];

	string getTaskId();
	string getRate();
	int getRateType();
	time_t getStartTime();
	time_t getEndTime();
	string getProcessTypeName();
	string getParamter();
	int getStatus();


	void setTaskId(string taskId);
	void setRate(string rate);
	void setRateType(int rateType);
	void setStartTime(time_t startTime);
	void setEndTime(time_t endTime);
	void setProcessTypeName(string processTypeName);
	void setParamter(string paramter);
	void setStatus(int status);

	void setprocessInfo(CProcessInfo config);
	CProcessInfo getprocessInfo(){return this->config;}

protected:
	CProcessInfo config;
	string taskId;
	// ָ��Ԫ���ݵ����� 
	string rate;

	string dataSrc;
	time_t startTime;
	time_t endTime;

	// ָ������ʽ
	string processTypeName;
	// process�Ĳ������Զ��ŷָ�
	string paramter;
	// ״̬ 0.��ʼ���� 1.�����У�2. �������
	int status;  
};