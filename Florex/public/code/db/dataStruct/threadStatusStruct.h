#pragma once
#include "table/TableStruct.h"

class CThreadStatusStruct;
typedef shared_ptr<CThreadStatusStruct> PThreadStatusStruct;

class CThreadStatusStruct : public CTableStruct
{
protected:
	CThreadStatusStruct();
public:
	static PThreadStatusStruct instence();
	
	~CThreadStatusStruct();

	static string key_threadId; 
	static string key_rateName; 
	static string key_threadTypeName; 
	static string key_threadStatus; 
	
	//static string key_step; 

	// �����������ʼʱ�䣬��ֹʱ��
	static string key_buildTaskStartTimeDesc;
	static string key_buildTaskEndTimeDesc;

	// ���һ�������������ʼʱ��
	static string key_buildTaskLastTime; 
	static string key_buildTaskLastTimeDesc;
	// ���һ����ɵ�������ʼʱ��
	static string key_completeTaskLastTime; 
	static string key_completeTaskLastTimeDesc; 
	
	int idCount;
};

