#pragma once
#include "process/obj/rateValue.h"
#include "table/Row.h"
#include <memory>
#include "ConstDef.h"
#include "db/dataStruct/continueValueStruct.h"

using namespace std;

// ������ֵ
class CContinueValue
{
public:
	CContinueValue();
	void setValue(PRateValue startRateValue, PRateValue endRateValue, PRateValue stopRateValue, int direct);
	void setJudgeValue(double _curRetrcementValue, double _retrcementValue, double _judgeRetrcementValue)
	{
		curRetrcementValue = _curRetrcementValue;
		retrcementValue = _retrcementValue;
		judgeRetrcementValue = _judgeRetrcementValue;
	}
	void setLevels(list<int> &nLevels);
	
	PRow buildDbRow(int groupId, PContinueValueStruct pSt);
	
	PRateValue startRateValue;
	PRateValue endRateValue;
	// ֹͣ�����Ϣ
	PRateValue stopRateValue;
	
	// ֹͣ���ж���Ϣ�������ݶ�
	string stopType;

	// ������� 
	double startValue;
	double endValue;
	double stopValue;
	double stepValue;

	double minValue;

	double startTime;
	double stepTime;
	
	int direct;

	int startLevel;
	int maxLevel;
	int stopLevel;
	string levels;

	string groupId;

	double curRetrcementValue;
	double retrcementValue;
	double judgeRetrcementValue;
protected:
	void calc();
};

typedef shared_ptr<CContinueValue> PContinueValue;
#define newContinueValue() make_shared<CContinueValue>()