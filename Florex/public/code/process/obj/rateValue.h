#pragma once
#include <list>
#include <map>
#include <string>
#include <memory>
#include "LinkedHashMap.h"

using namespace std;

class CRateValue
{
public:
	CRateValue() :time(0), value(0) {}
	CRateValue(double _time, double _value) :time(_time), value(_value) {}
	CRateValue(double _time, double _value, std::string& _timeDesc) :time(_time), value(_value), timeDesc(_timeDesc) {}

	bool isValid() const { return time != 0; }
	double time;
	double value;
	string timeDesc;
};

typedef shared_ptr<CRateValue> PRateValue;
#define newRateValue() make_shared<CRateValue>()
#define newRateValueP2(T1,T2) make_shared<CRateValue>(T1,T2)
#define newRateValueP3(T1,T2,T3) make_shared<CRateValue>(T1,T2,T3)
#define newRateValueCopy(T1) make_shared<CRateValue>(T1)
//const CRateValue zeroRateValue;
