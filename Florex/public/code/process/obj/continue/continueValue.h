#pragma once
#include "process/obj/rateValue.h"
#include <memory>
#include "ConstDef.h"

using namespace std;

// ������ֵ
class CContinueValue
{
public:
	CContinueValue();


	PRateValue startValue;
	PRateValue endValue;

	// ֹͣ�����Ϣ
	PRateValue stopValue;
	// ֹͣ���ж���Ϣ�������ݶ�
	string stopType;
};

typedef shared_ptr<CContinueValue> PContinueValue;
#define newContinueValue() make_shared<CContinueValue>()