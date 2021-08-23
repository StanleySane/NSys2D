// NewGroupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "NewGroupDlg.h"
#include "ShemeGroup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewGroupDlg dialog


CNewGroupDlg::CNewGroupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewGroupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewGroupDlg)
	m_strGroup = _T("");
	m_strGroupName = _T("");
	m_iGroupType = 0;
	//}}AFX_DATA_INIT
}


void CNewGroupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewGroupDlg)
	DDX_Text(pDX, IDC_EDIT_GROUP, m_strGroup);
	DDV_MaxChars(pDX, m_strGroup, 90);
	DDX_Text(pDX, IDC_EDIT_GROUP_NAME, m_strGroupName);
	DDV_MaxChars(pDX, m_strGroupName, 30);
	DDX_Radio(pDX, IDC_RADIO_GROUP_TYPE, m_iGroupType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewGroupDlg, CDialog)
	//{{AFX_MSG_MAP(CNewGroupDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewGroupDlg message handlers
