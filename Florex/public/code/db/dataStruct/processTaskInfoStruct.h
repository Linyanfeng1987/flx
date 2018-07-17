#pragma once
#include "table/TableStruct.h"


class CProcessTaskInfoStruct : public CTableStruct
{
protected:
	CProcessTaskInfoStruct();
public:
	static CProcessTaskInfoStruct* instence();
	~CProcessTaskInfoStruct();

	// Ψһid
	static string key_taskId; 
	// ����ʹ�õ�rate�Ǵ�ʱ���
	static string key_rate; 
	// ��ͨrate
	static string key_rateType; 
	static string key_startTime; 
	static string key_endTime; 
	// ����������
	static string key_processTypeName; 
	static string key_paramter; 
	static string key_status; 
};