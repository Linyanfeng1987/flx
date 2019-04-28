#pragma once
#include <memory>
#include "LogObj.h"
#include "db/DbObj.h"

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
	CTaskInfo(string _taskName, TaskType _taskType);
	~CTaskInfo(){};
	void setTaskType(TaskType _taskType);
	bool threadAble(){return threadsAble;}
	string getTaskName(){return taskName;}
private:
	bool threadsAble;
	TaskType taskType; 
	string taskName;
};

typedef shared_ptr<CTaskInfo> PTaskInfo;
#define newTaskInfo(T1,T2) make_shared<CTaskInfo>(T1,T2)

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
