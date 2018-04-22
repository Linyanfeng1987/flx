#include "baseCalc.h"
#include "process/obj/sum.h"

class CAverageCalc : public CBaseCalc
{
public:
	CAverageCalc(int cycle);
	~CAverageCalc();

	double addValue(double curValue);
protected:
	// ����
	int cycle;
	// 
	// �������
	CSum sum;
};

