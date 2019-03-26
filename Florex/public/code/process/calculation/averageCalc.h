#pragma once
#include "baseCalc.h"
#include "process/obj/rateValue.h"
#include "process/obj/sumByTime.h"

class CAverageCalc : public CBaseCalc
{
public:
	CAverageCalc(double cycle);
	~CAverageCalc();

	double addValue(double time, double curValue);
protected:
	// ����
	double cycle;
	// 
	// �������
	CSumByTime sum;
};

typedef shared_ptr<CAverageCalc> PAverageCalc;
#define newAverageCalc(T) make_shared<CAverageCalc>(T)
