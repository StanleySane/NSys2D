// PreCalcDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "PreCalcDlg.h"

#include "Expression.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPreCalcDlg dialog


CPreCalcDlg::CPreCalcDlg(CParamIntegr *pParamIntegr, CWnd* pParent /*= NULL*/)
	: CDialog(CPreCalcDlg::IDD, pParent)
{
	pParam=pParamIntegr;
//	m_strStep=strstep;
//	m_strTime=strtime;
//	m_MethodDef=Method;

	//{{AFX_DATA_INIT(CPreCalcDlg)
	m_EditStep = _T("");
	m_EditTime = _T("");
	m_Method = -1;
	//}}AFX_DATA_INIT
}


void CPreCalcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPreCalcDlg)
	DDX_Text(pDX, IDC_EDIT2, m_EditStep);
	DDV_MaxChars(pDX, m_EditStep, 100);
	DDX_Text(pDX, IDC_EDIT1, m_EditTime);
	DDV_MaxChars(pDX, m_EditTime, 100);
	DDX_Radio(pDX, IDC_RADIO1, m_Method);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPreCalcDlg, CDialog)
	//{{AFX_MSG_MAP(CPreCalcDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPreCalcDlg message handlers

BOOL CPreCalcDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_EditTime=pParam->strTime;
	m_EditStep=pParam->strStep;
	m_Method=pParam->TypeMethod;
	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPreCalcDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	
	CExpression e;
	int ret;
	double time, step;
	if (ret=e.IsNum(m_EditTime,&time))
	{
		CString mes;
		mes.LoadString(ret);
		
		MessageBox(mes,"Время интегрирования",
			 MB_OK|MB_ICONERROR );
		
		return;
	}

	if (ret=e.IsNum(m_EditStep,&step))
	{
		CString mes;
		mes.LoadString(ret);
		
		MessageBox(mes,"Шаг интегрирования",
			 MB_OK|MB_ICONERROR );
		
		return;
	}
	pParam->strTime=m_EditTime;
	pParam->strStep=m_EditStep;
	pParam->TypeMethod=m_Method;
	pParam->Time=time;
	pParam->Step=step;

	CDialog::OnOK();
}


