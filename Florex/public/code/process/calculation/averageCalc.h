#include "baseCalc.h"
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

