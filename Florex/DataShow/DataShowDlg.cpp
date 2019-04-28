
// DataShowDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DataShow.h"
#include "DataShowDlg.h"
#include "afxdialogex.h"

#include <afxpriv.h>
#include "windows.h"


#ifdef _DEBUGshowSpace
#define new DEBUG_NEW
#endif

#include "PubFun.h"
#include "db/DbObj.h"
#include "LogObj.h"

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDataShowDlg �Ի���



CDataShowDlg::CDataShowDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDataShowDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDataShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, showTypeBox);
	DDX_Control(pDX, IDC_EDIT2, showSpace);
	DDX_Control(pDX, IDC_EDIT1, SqlEdit);
}

BEGIN_MESSAGE_MAP(CDataShowDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CDataShowDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CDataShowDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDataShowDlg ��Ϣ�������

BOOL CDataShowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	showSpace.SetReadOnly(TRUE);

	//CRect rect;
	//showSpace.GetRect(&rect);
	//showSpace.setShowRect(rect.Width(), rect.Height());

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//MoveWindow(100, 100, 1200, 600);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDataShowDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDataShowDlg::OnPaint()
{
	CPaintDC dc(this); // ���ڻ��Ƶ��豸������
	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDataShowDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDataShowDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//%%%%
}


void CDataShowDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	USES_CONVERSION;
	CString cstr;
	SqlEdit.GetWindowTextW(cstr);
	
	string userStr = T2A(cstr);	

	list<string> strRows = PubFun::split(userStr, string("\n"));
	PTableStruct tableStruct = nullptr;
	for (string strRow : strRows)
	{
		list<string> oneInfo = PubFun::split(strRow, string(";"));
		auto iter = oneInfo.begin();
		string tagName = *iter;
		iter++;
		string strType = *iter;
		iter++;
		string sql = *iter;
		if (strType == "average")
		{
			tableStruct = CCurRateAverageStruct::instence();
		}
		else
		{
			tableStruct = CCurRateStruct::instence();
		}
		getSqlData(sql.c_str(), tagName, tableStruct);
	}

	showSpace.spOnPaint();
}

void CDataShowDlg::getSqlData( const char* sql, string tagName, PTableStruct tableStruct )
{
	PTable resTable = newTable(tableStruct);
	CDbObj& db = CDbObj::instance();
	try
	{
		db.selectData(sql, resTable);
		showSpace.addRateValueTable(tagName, resTable);
	}
	catch (CStrException &e)
	{
		CLogObj::instance().error(string(e.what()));	
		//MessageBox(_T(e.what),NULL,MB_OK); //��ʾ��Ϣ��
	}
}
