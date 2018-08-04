#pragma once
//任务基础类 可能被多线程调用

class CBaseTask
{
public:
	CBaseTask();
	~CBaseTask();

	int run(const char* argv);
protected:
	virtual void runInThread(const char* argv) = 0;
	virtual int completeTask() = 0;
private:
	
};
