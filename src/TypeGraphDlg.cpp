// TypeGraphDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "TypeGraphDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTypeGraphDlg dialog


CTypeGraphDlg::CTypeGraphDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTypeGraphDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTypeGraphDlg)
	m_SelectH = -1;
	m_SelectV = -1;
	//}}AFX_DATA_INIT
}


void CTypeGraphDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTypeGraphDlg)
	DDX_Radio(pDX, IDC_RADIO1, m_SelectH);
	DDX_Radio(pDX, IDC_RADIO8, m_SelectV);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTypeGraphDlg, CDialog)
	//{{AFX_MSG_MAP(CTypeGraphDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTypeGraphDlg message handlers

BOOL CTypeGraphDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_SelectH=9;
	m_SelectV=0;
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
