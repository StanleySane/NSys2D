// GroupPreviewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "GroupPreviewDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGroupPreviewDlg dialog


CGroupPreviewDlg::CGroupPreviewDlg( CWnd* pParent /*=NULL*/)
	: CDialog(CGroupPreviewDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGroupPreviewDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CGroupPreviewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGroupPreviewDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGroupPreviewDlg, CDialog)
	//{{AFX_MSG_MAP(CGroupPreviewDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGroupPreviewDlg message handlers

BOOL CGroupPreviewDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CRect rect;
	GetWindowRect(&rect);
	MoveWindow( 0, 100, rect.Width(), rect.Height() );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
