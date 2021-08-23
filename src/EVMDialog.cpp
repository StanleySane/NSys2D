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
	m_Method = 0;
	m_HardMethod = 0;
	m_bCondenceMass = FALSE;
	//}}AFX_DATA_INIT
}


void CEVMDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEVMDialog)
	DDX_Radio(pDX, IDC_RADIO_JACOBY, m_Method);
	DDX_Radio(pDX, IDC_RADIO_HARDMETHOD_0, m_HardMethod);
	DDX_Check(pDX, IDC_CHECK_CONDMASS, m_bCondenceMass);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEVMDialog, CDialog)
	//{{AFX_MSG_MAP(CEVMDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEVMDialog message handlers
