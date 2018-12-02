#pragma once
#include "LogObj.h"
#include "db/DbObj.h"
//��������� ���ܱ����̵߳���

class CBaseTask
{
public:
	CBaseTask(string taskName);
	~CBaseTask();
	int getStatus(){return status;}

	int run(const char* argv);
protected:
	void baseRunInThread(const char* argv);
	virtual void runInThread(const char* argv) = 0;
	virtual int completeTask() = 0;

	int status;
	CLogObj& log;
	string taskName;
private:
	
};
