// EVMDialog.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "EVMDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEVMDialog dialog


CEVMDialog::CEVMDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CEVMDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEVMDialog)
	m_Method = 2;
	m_HardMethod = 0;
	m_bIntegrTest = FALSE;
	m_InvertMethod = -1;
	m_bValidateExpr = FALSE;
	//}}AFX_DATA_INIT
}


void CEVMDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEVMDialog)
	DDX_Radio(pDX, IDC_RADIO_JACOBY, m_Method);
	DDX_Radio(pDX, IDC_RADIO_HARDMETHOD_0, m_HardMethod);
	DDX_Check(pDX, IDC_CHECK_INTEGR_TEST, m_bIntegrTest);
	DDX_Radio(pDX, IDC_RADIO_INVERT_0, m_InvertMethod);
	DDX_Check(pDX, IDC_CHECK_VALIDATE_EXPR, m_bValidateExpr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEVMDialog, CDialog)
	//{{AFX_MSG_MAP(CEVMDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEVMDialog message handlers
