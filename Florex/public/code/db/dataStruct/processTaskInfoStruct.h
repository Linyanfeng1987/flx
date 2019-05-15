#pragma once
#include "table/TableStruct.h"

class CProcessTaskInfoStruct;
typedef shared_ptr<CProcessTaskInfoStruct> PProcessTaskInfoStruct;

class CProcessTaskInfoStruct : public CTableStruct
{
protected:
	CProcessTaskInfoStruct();
public:
	static PProcessTaskInfoStruct instence();
	~CProcessTaskInfoStruct();

	// Ψһid
	static string key_taskId; 
	// ����ʹ�õ�rate�Ǵ�ʱ���
	static string key_rate; 
	// ��ͨrate
	static string key_rateType; 
	static string key_startTime; 
	static string key_startTimeDesc; 
	static string key_endTime; 
	static string key_endTimeDesc; 
	// ����������
	static string key_processId; 
	static string key_paramter; 
	// ����״̬��
	//0�����񱻷���
	//1�������ѷ���
	//2������������
	//3�����������
	//-1������ʧ��
	static string key_status; 
};

