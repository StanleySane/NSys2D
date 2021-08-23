// GraphTimeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "GraphTimeDlg.h"
#include "expression.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphTimeDlg dialog


CGraphTimeDlg::CGraphTimeDlg(CParamTime *pparam, CWnd* pParent /*=NULL*/)
	: CDialog(CGraphTimeDlg::IDD, pParent)
{
	pParam=pparam;
	//{{AFX_DATA_INIT(CGraphTimeDlg)
	m_TimeBeg = _T("");
	m_TimeEnd = _T("");
	m_TimeStep = _T("");
	//}}AFX_DATA_INIT
}


void CGraphTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGraphTimeDlg)
	DDX_Text(pDX, IDC_EDIT1, m_TimeBeg);
	DDX_Text(pDX, IDC_EDIT2, m_TimeEnd);
	DDX_Text(pDX, IDC_EDIT3, m_TimeStep);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGraphTimeDlg, CDialog)
	//{{AFX_MSG_MAP(CGraphTimeDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphTimeDlg message handlers

void CGraphTimeDlg::OnOK() 
{
	// TODO: Add extra validation here
	if (!VerifyInfo()) return;
	
	pParam->strT0=m_TimeBeg;
	pParam->strT1=m_TimeEnd;
	pParam->strdT=m_TimeStep;

	CExpression e;
	e.IsNum(m_TimeBeg,&(pParam->T0));
	e.IsNum(m_TimeEnd,&(pParam->T1));
	e.IsNum(m_TimeStep,&(pParam->dT));

	CDialog::OnOK();
}

BOOL CGraphTimeDlg::VerifyInfo()
{
	UpdateData();

	double Beg, End, Step;
	CExpression e;
	int ret=e.IsNum(m_TimeBeg,&Beg);
	if (ret)
	{
		CString str;
		str.LoadString(ret);
		MessageBox(str,"Ошибка в выражении 'от'"
			,MB_OK|MB_ICONERROR);
		return false;
	}
	ret=e.IsNum(m_TimeEnd,&End);
	if (ret)
	{
		CString str;
		str.LoadString(ret);
		MessageBox(str,"Ошибка в выражении 'до'"
			,MB_OK|MB_ICONERROR);
		return false;
	}
	ret=e.IsNum(m_TimeStep,&Step);
	if (ret)
	{
		CString str;
		str.LoadString(ret);
		MessageBox(str,"Ошибка в выражении 'шаг'"
			,MB_OK|MB_ICONERROR);
		return false;
	}
	if (Beg>=End)
	{
		MessageBox("Значение 'от' больше чем 'до'","Ошибка"
			,MB_OK|MB_ICONERROR);
		return false;
	}
	if (Beg<0)
	{
		MessageBox("Значение 'от' меньше нуля","Ошибка"
			,MB_OK|MB_ICONERROR);
		return false;
	}
	if (End<0)
	{
		MessageBox("Значение 'до' меньше нуля","Ошибка"
			,MB_OK|MB_ICONERROR);
		return false;
	}
	if (Step<0)
	{
		MessageBox("Значение 'шаг' меньше нуля","Ошибка"
			,MB_OK|MB_ICONERROR);
		return false;
	}

	return true;
}

BOOL CGraphTimeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_TimeBeg =pParam->strT0;
	m_TimeEnd =pParam->strT1;
	m_TimeStep=pParam->strdT;
	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
