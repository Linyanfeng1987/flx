#pragma once
//��������� ���ܱ����̵߳���

class CBaseTask
{
public:
	CBaseTask();
	~CBaseTask();

	virtual int run() = 0;
private:

};
