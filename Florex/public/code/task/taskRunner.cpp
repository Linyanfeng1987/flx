#include "taskRunner.h"

// �������ݿ⣬������Ӧ�̴߳�������

CtaskRunner::CtaskRunner()
{
}

CtaskRunner::~CtaskRunner()
{
}

void CtaskRunner::run()
{
	while (true)
	{
		reloadTaskList();
		rangTaskList();
		
		::Sleep(1000);
	}
}

void CtaskRunner::reloadTaskList()
{

}

void CtaskRunner::rangTaskList()
{

}
