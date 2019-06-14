// ShowSpace.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DataShow.h"
#include "ShowSpace.h"



// ShowSpace
const int deviation = 30;
const int deviationHf = deviation/2;
	
IMPLEMENT_DYNAMIC(ShowSpace, CEdit)

ShowSpace::ShowSpace()
{
	maxRateValue = 0;
	minRateValue = 0;
	maxTime = 0;
	minTime = 0;
	borderInit = false;

	maxShowW = 1000;
	maxShowH = 250;
}

ShowSpace::~ShowSpace()
{
}


BEGIN_MESSAGE_MAP(ShowSpace, CEdit)
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// ShowSpace ��Ϣ�������
void ShowSpace::OnPaint()
{
// 	CPaintDC dc(this); // device context for painting
// 	CPen pen(PS_SOLID,1,RGB(255,0,0)); //�������ƵĻ���
// 	CBrush *pbrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH)); //��������ʱ���Ļ�ˢ
// 	dc.SelectObject(&pen); //����ˢ�ͻ���ѡ���豸��������
// 	dc.SelectObject(pbrush);
// 
// 	CPoint point1(0, 0);
// 	CPoint point2(1000, 500);
// 	dc.MoveTo(point1);
// 	dc.LineTo(point2);
// 
// 	CRect rect;
// 	GetClientRect(&rect);
// 
// 	CPaintDC* pDC = &dc;
// 	pDC->SetMapMode(MM_ANISOTROPIC);
// 	pDC->SetWindowExt(rect.Width(),rect.Height());
// 	pDC->SetViewportExt(rect.Width(),-rect.Height());
// 	pDC->SetViewportOrg(rect.Width()/2,rect.Height()/2);
// 	rect.OffsetRect(-rect.Width()/2,-rect.Height()/2);
// 	CPoint ld,rt;//
// 
// 	//�����ⲿ��ɫ��Բ
// 	ld=CPoint(-200,-150),rt=CPoint(200,150);
// 	CBrush NewBrush, *pOldBrush;
// 	NewBrush.CreateSolidBrush(RGB(0,0,0));
// 	pOldBrush=pDC->SelectObject(&NewBrush);
// 	pDC->Ellipse(CRect(ld,rt));
// 	pDC->SelectObject(pOldBrush);
// 	NewBrush.DeleteObject();
		// TODO: �ڴ˴������Ϣ����������
		// ��Ϊ��ͼ��Ϣ���� CEdit::OnPaint()
	spOnPaint();
	CEdit::OnPaint();
}

void ShowSpace::spOnPaint()
{
	CRect rect;
	GetWindowRect(&rect);
	maxShowW = rect.right - rect.left - deviation;
	maxShowH = rect.bottom - rect.top - deviation;
	CPaintDC dc(this);
	CBrush brush(RGB(0, 0, 0));
	dc.FillRect(&rect, &brush);
	if (0 != maxRateValue)
	{
		int lineSize = averageRateTables.size();
		int step = 30;
		int color = 0;
		for (auto tablePair : averageRateTables)
		{
			color += step;
			CPen pen(PS_SOLID,1,RGB(color/5,color/4,color));
			dc.SelectObject(pen);
			PTable table = tablePair.second;
			paintRateValue(CCalcRateStruct::curValue, CCalcRateStruct::curTime, table, dc);
		}
	}
	//InvalidateRect(&rect);
	//Invalidate(TRUE);
}

void ShowSpace::clear()
{
	rateTables.clear();
	averageRateTables.clear();
	optTables.clear();
	OnPaint();
}
/*
void ShowSpace::addRateValueTable( string tagName, PTable rateValueTable )
{
	auto pr = rateTables.insert(make_pair(tagName, rateValueTable));
	if (pr.second)
	{
		loadValueBorder(CCurRateStruct::priceBuy, CCurRateStruct::curTime, rateValueTable);
	}
}
*/
void ShowSpace::addRateValueTable( string tagName, PTable rateValueTable )
{
	auto pr = averageRateTables.insert(make_pair(tagName, rateValueTable));
	if (pr.second)
	{
		loadValueBorder(CCalcRateStruct::curValue, CCalcRateStruct::curTime, rateValueTable);
	}
}

void ShowSpace::addOptValueTable( string tagName, PTable optValueTable )
{
	optTables.insert(make_pair(tagName, optValueTable));
}

void ShowSpace::loadValueBorder( string rateValueField, string timeField, PTable table )
{
	for (auto rowPr : *table)
	{
		PRow row = rowPr.second;
		double curValue = row->getDoubleValue(rateValueField);
		double curTime = row->getDoubleValue(timeField);
		if (!borderInit)
		{
			borderInit = true;
			maxRateValue = minRateValue = curValue;
			maxTime = minTime = curTime;
		}
		else
		{
			maxRateValue = maxRateValue < curValue ? curValue : maxRateValue;
			minRateValue = minRateValue > curValue ? curValue : minRateValue;
			maxTime = maxTime < curTime ? curTime : maxTime; 
			minTime = minTime > curTime ? curTime : minTime;
		}
	}
	if (borderInit)
	{
		bigValueStep = maxRateValue - minRateValue;
		bigTimeStep = maxTime - minTime;
	}
}

void ShowSpace::paintRateValue( string rateValueField, string timeField, PTable table, CPaintDC &dc )
{
	shared_ptr<CPoint> point = nullptr;
	shared_ptr<CPoint> pointTo = nullptr;
	for (auto rowPr : *table)
	{
		PRow row = rowPr.second;
		double curValue = row->getDoubleValue(rateValueField);
		double curTime = row->getDoubleValue(timeField);

		int x = deviationHf+(curTime - minTime)/bigTimeStep * maxShowW;
		int y = deviationHf+(1-(curValue - minRateValue)/bigValueStep) * maxShowH;
		
		if (nullptr == point)
		{
			point = make_shared<CPoint>(x, y);
			dc.MoveTo(*point);
		}
		else
		{
			point = make_shared<CPoint>(x, y);
			dc.LineTo(*point);
		}
	}

// 	int w = (maxTime - minTime)/bigTimeStep * maxShowW;
// 	int h = (1-(maxRateValue - minRateValue)/bigValueStep) * maxShowH;
// 
// 	CPoint t1(0, h);
// 	CPoint t2(w, 0);
// 	dc.MoveTo(t1);
// 	dc.LineTo(t2);
}


// void ShowSpace::OnPaint()
// {
// 	CPaintDC dc(this); // device context for painting
//	spOnPaint();
// 	CEdit::OnPaint();
// 		// TODO: �ڴ˴������Ϣ����������
// 		// ��Ϊ��ͼ��Ϣ���� CEdit::OnPaint()
// }


void ShowSpace::OnSize(UINT nType, int cx, int cy)
{
	CEdit::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
}
