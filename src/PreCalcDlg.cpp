// PreCalcDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "PreCalcDlg.h"

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
	m_Method = -1;
	m_EditTime = 0.0;
	m_EditStep = 0.0;
	//}}AFX_DATA_INIT
}


void CPreCalcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPreCalcDlg)
	DDX_Radio(pDX, IDC_RADIO1, m_Method);
	DDX_Text(pDX, IDC_EDIT1, m_EditTime);
	DDX_Text(pDX, IDC_EDIT2, m_EditStep);
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
	m_EditTime = pParam->Time;
	m_EditStep = pParam->Step;
	m_Method = pParam->TypeMethod;
	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPreCalcDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	
	pParam->Time = m_EditTime;
	pParam->Step = m_EditStep;
	pParam->TypeMethod=m_Method;

	CDialog::OnOK();
}


