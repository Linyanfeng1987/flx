// ShowSpace.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DataShow.h"
#include "ShowSpace.h"


// ShowSpace

IMPLEMENT_DYNAMIC(ShowSpace, CEdit)

ShowSpace::ShowSpace()
{

}

ShowSpace::~ShowSpace()
{
}


BEGIN_MESSAGE_MAP(ShowSpace, CEdit)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// ShowSpace ��Ϣ�������
void ShowSpace::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CPen pen(PS_SOLID,1,RGB(255,0,0)); //�������ƵĻ���
	CBrush *pbrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH)); //��������ʱ���Ļ�ˢ
	dc.SelectObject(&pen); //����ˢ�ͻ���ѡ���豸��������
	dc.SelectObject(pbrush);

	CPoint point1(0, 0);
	CPoint point2(1000, 500);
	dc.MoveTo(point1);
	dc.LineTo(point2);

	CRect rect;
	GetClientRect(&rect);

	CPaintDC* pDC = &dc;
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(rect.Width(),rect.Height());
	pDC->SetViewportExt(rect.Width(),-rect.Height());
	pDC->SetViewportOrg(rect.Width()/2,rect.Height()/2);
	rect.OffsetRect(-rect.Width()/2,-rect.Height()/2);
	CPoint ld,rt;//

	//�����ⲿ��ɫ��Բ
	ld=CPoint(-200,-150),rt=CPoint(200,150);
	CBrush NewBrush, *pOldBrush;
	NewBrush.CreateSolidBrush(RGB(0,0,0));
	pOldBrush=pDC->SelectObject(&NewBrush);
	pDC->Ellipse(CRect(ld,rt));
	pDC->SelectObject(pOldBrush);
	NewBrush.DeleteObject();
		// TODO: �ڴ˴������Ϣ����������
		// ��Ϊ��ͼ��Ϣ���� CEdit::OnPaint()
}
