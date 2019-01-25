#pragma once
#include "process/obj/rateValue.h"
#include <memory>

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
};

typedef shared_ptr<CContinueValue> PContinueValue;
#define newContinueValue() make_shared<CContinueValue>()