#pragma once
#include "rateValue.h"
#include "rate/rateInfo.h"
using namespace std;

// �����ڵ�
class CBasePipelineNode
{
public:
	CBasePipelineNode(){}
	virtual ~CBasePipelineNode(){}
	virtual PRateValue add(PRateValue value) = 0;

protected:

};
typedef shared_ptr<CBasePipelineNode> PBasePipelineNode;
