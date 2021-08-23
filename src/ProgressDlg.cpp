// ProgressDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "ProgressDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgressDlg dialog

CProgressDlg::CProgressDlg(int Count, CString tit,
						   CWnd* pParent /*=NULL*/)
	: CDialog(CProgressDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProgressDlg)
	m_strDetails = _T("");
	//}}AFX_DATA_INIT
	maxValue=Count;
	title=tit;
	Create(IDD_PROGRESSDIALOG,pParent);
}


void CProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProgressDlg)
	DDX_Control(pDX, IDCANCEL, m_Button);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
	DDX_Text(pDX, IDC_DETAILS, m_strDetails);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProgressDlg, CDialog)
	//{{AFX_MSG_MAP(CProgressDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgressDlg message handlers

BOOL CProgressDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetWindowText(title);
	m_Progress.SetRange(0, maxValue);
	m_Progress.SetPos(0);
	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CProgressDlg::SetPos(int i)
{
	m_Progress.SetPos(i);
	UpdateData(false);
}

void CProgressDlg::SetDetails( const CString &str )
{
	m_strDetails = str;
	UpdateData(FALSE);
}
