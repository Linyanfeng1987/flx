#pragma once
#include <memory>
#include "LogObj.h"
#include "db/DbObj.h"
#include "db/dataStruct/processTaskInfoStruct.h"

using namespace std;

enum TaskType
{
	// ӳ����㣬�ɿ����߳�
	task_calc_map,
	// ��̬���㣬���ɿ����̣߳�����˳��
	task_calc_stauts,
};

class CTaskInfo
{
public:
	CTaskInfo(PRow _porcessTaskInfo, TaskType _taskType);
	//CTaskInfo(string _taskName, TaskType _taskType);
	~CTaskInfo(){};
	void setTaskType(TaskType _taskType);
	bool threadAble(){return threadsAble;}
	PRow getRowData(){return porcessTaskInfo;}
private:
	bool threadsAble;
	TaskType taskType; 
	PRow porcessTaskInfo;
};

typedef shared_ptr<CTaskInfo> PTaskInfo;
#define newTaskInfo(T1,T2) make_shared<CTaskInfo>(T1,T2)
//#define newTaskInfo(T1) make_shared<CTaskInfo>(T1)

//��������� ���ܱ����̵߳���
class CBaseTask
{
public:
	CBaseTask(PTaskInfo _taskInfo);
	~CBaseTask();
	PTaskInfo getTaskInfo(){return taskInfo;}
	int getStatus(){return status;}

	int run(const char* argv);
protected:
	void baseRunInThread(const char* argv);
	virtual void runInThread(const char* argv) = 0;
	virtual int completeTask() = 0;

	int status;
	CLogObj& log;
	PTaskInfo taskInfo;
private:
	
};
