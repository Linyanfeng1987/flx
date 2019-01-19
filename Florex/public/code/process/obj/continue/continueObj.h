#include <list>
#include <map>
#include "process/obj/rateValue.h"
#include "continueValue.h"
#include "LinkedHashMap.h"
#include <memory>
#include "continueJudgeGroup.h"

using namespace std;
// �����и����A
// �����з��� 
// �������ж���1�س��ķ��ȣ�

// ��һ��ʱ��Σ�һ�������ϣ�������
// ��ʼ����жϣ���һ�����յ㣿�ǲ�ͬ����ֵ��������ͬ���յ㣿
// ���Զ����ֵ�� ��ֵ��׼ȷ�ԣ� 
// ����������л�ƽ�ʣ�
// ��ζ��巽�����ȷ�ԣ�
// �Ƿ����ͳ�ƣ�manager�� �Ȳ�����manager����

// ˼·��
// 1. Ҫ��ɳɳ�����¼�ɳ����̣�
// 2. �Ǿ�Ҫ֪���ɳ��ı�׼
// 3. �Ƿ���ںϲ���һ˵���ϲ���ԭ��ʱ������������������ǰ���жϣ��ϲ��߼���Ϊ����
// 4. �����߳ɳ����ģ��˼·�Ϻ�
// 5. �ɳ��ı�׼���������У�
// 6. �����Ա��CContinueObj��������¼�����֣��ɳ�
//				��׼�����飺�������ɣ��洢���л�
//				��׼�����ж���ʼ�������жϣ��ɳ���׼������ֱ�ӱ��ⲿ���ʣ������õ�level
//				builder����׼�ļ��ϣ���ʼ�����ж�+obj����
//				continus�����obj�Ĵ洢


class CContinueObj
{
public:
	CContinueObj(PContinueJudgeGroup pJudgeGroup);
	void init(CRateValue& startValue, CRateValue& tryEndValue, int& curDirect, int& judegLevel);

	void setId(long objId){this->objId = objId;}
	long getId(){ return objId;}

	bool isContinueGoOn(const CRateValue& curValue);

	PContinueValue getContinueValue(){return pContinueValue;}
protected:
	long objId;

	// ���� +1 �� -1
	int curDirect;
	CRateValue startValue;
	// ͬ������Զ��ֵ
	CRateValue tryEndValue;
	// �����ȼ� 
	int judegLevel;
	// �ϴ��ϱ���ֵ
	//CRateValue lastValue;

	PContinueValue pContinueValue;
	PContinueJudgeGroup pJudgeGroup;
};

typedef shared_ptr<CContinueObj> PContinueObj;
#define newContinueObj(T) make_shared<CContinueObj>(T);