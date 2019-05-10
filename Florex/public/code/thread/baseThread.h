#pragma once
#include <memory>
#include "LogObj.h"
#include "db/DbObj.h"
#include "db/dataStruct/processTaskInfoStruct.h"

using namespace std;

enum CalcThreadType
{
	// ӳ����㣬�ɿ����߳�
	thread_calc_map,
	// ��̬���㣬���ɿ����̣߳�����˳��
	thread_calc_stauts,
};

class CThreadInfo
{
public:
	CThreadInfo(PRow _porcessTaskInfo, CalcThreadType _ThreadType);
	//CThreadInfo(string _taskName, ThreadType _ThreadType);
	~CThreadInfo(){};
	void setThreadType(CalcThreadType _ThreadType);
	bool threadAble(){return threadsAble;}
	PRow getRowData(){return porcessTaskInfo;}
private:
	bool threadsAble;
	CalcThreadType ThreadType; 
	PRow porcessTaskInfo;
};

typedef shared_ptr<CThreadInfo> PThreadInfo;
#define newThreadInfo(T1,T2) make_shared<CThreadInfo>(T1,T2)
//#define newThreadInfo(T1) make_shared<CThreadInfo>(T1)

//��������� ���ܱ����̵߳���
class CBaseThread
{
public:
	CBaseThread(PThreadInfo _taskInfo);
	~CBaseThread();
	PThreadInfo getTaskInfo(){return taskInfo;}
	int getStatus(){return status;}

	int run(const char* argv);
protected:
	void baseRunInThread(const char* argv);
	virtual void runInThread(const char* argv) = 0;
	virtual int completeTask() = 0;

	int status;
	CLogObj& log;
	PThreadInfo taskInfo;
private:
	
};
