#include "process/obj/rateValue.h"
#include <memory.h>


using namespace std;

// ������ֵ
class CContinueValue
{
public:
	CContinueValue();


	CRateValue startValue;
	CRateValue endValue;

	// ֹͣ�����Ϣ
	CRateValue stopValue;
	// ֹͣ���ж���Ϣ�������ݶ�
	string stopType;
	double stopValue;
};

typedef shared_ptr<CContinueValue> PContinueValue;
#define newContinueValue() make_shared<CContinueValue>();