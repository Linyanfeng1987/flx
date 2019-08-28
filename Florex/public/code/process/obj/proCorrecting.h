#pragma once
#include "PubFun.h"
#include "ConstDef.h"
// ������У�����ݣ�����������ֵ����step��

class CProCorrecting
{
public:
	CProCorrecting();
	~CProCorrecting();

	void setStep(int step) { this->step = step; }
	bool calc(double curTime, double curValue, map<double, double>& valueMap);

protected:
	// ������ ��λ ��
	int step;
	// �����ֵ�Ͷ�Ӧʱ��
	double lastValue;
	double lastTime;
	double curValue;
	double curTime;
};
