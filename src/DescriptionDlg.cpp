// DescriptionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "DescriptionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDescriptionDlg dialog


CDescriptionDlg::CDescriptionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDescriptionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDescriptionDlg)
	m_strDescr = _T("");
	//}}AFX_DATA_INIT
}


void CDescriptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDescriptionDlg)
	DDX_Text(pDX, IDC_EDIT_DESCRIPTION, m_strDescr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDescriptionDlg, CDialog)
	//{{AFX_MSG_MAP(CDescriptionDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDescriptionDlg message handlers
