#pragma once

#include <string>

using namespace std;

const string tableTimeStepEnd_mm = "_mm";
const string tableTimeStepEnd_15m = "_15m";
const string tableTimeStepEnd_hh = "_hh";
const string tableTimeStepEnd_4h = "_4h";
const string tableTimeStepEnd_dd = "_dd";
const string tableTimeStepEnd_ww = "_ww";

const int timeStepStep_def = 0;
const int timeStepStep_mm = 1;
const int timeStepStep_15m = 2;
const int timeStepStep_hh = 3;
const int timeStepStep_4h = 4;
const int timeStepStep_dd = 5;
const int timeStepStep_ww = 6;

const string florexDbName = "florex";
const string coreDbName = "core";
const string calcDbName = "calc";

const static int maxLineRead = 10000;

const string rateNames[] = { "testRate","eurusd","usdjpy","xauusd","gbpusd","audusd" };

const double g_priveSetp1 = 0.1;
const double g_priveSetp2 = 0.0001;

const double goldenSection = 0.618;

const int basePoint = 1;
const int basePersentStep = 10000;

const string processType_average = "average";
const string processType_continue = "continue";
const string processType_baseCalc = "baseCalc";

const string typeInt = "int";
const string typeIndex = "index";
const string typeDouble = "double";
const string typeString = "char";
const string typeString2 = "string";
const string typeBigString = "bigString";
const string typeCount = "count";

// (前值-后置)*方向 要求为正
const int direct_up = -1;
const int direct_down = 1;

// lowDown level
const int lowDownLevel = 2;

// 随时间衰减系数 单位s
const double timeAttenuation = 0.9998;

typedef unsigned long indexType;

const size_t longSleepTime = 60000;
const size_t shortSleepTime = 1000;

const int gHisCalcStepTime = 60 * 60 * 4;

const int taskStatus_def = 0;
const int taskStatus_run = 1;
const int taskStatus_complate = 2;
const int taskStatus_error = 3;

#define DEBUG_CHECK