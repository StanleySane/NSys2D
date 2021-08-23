// ConvertToDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "ConvertToDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConvertToDlg dialog


CConvertToDlg::CConvertToDlg( int oldType, CWnd* pParent /*=NULL*/)
	: CDialog(CConvertToDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConvertToDlg)
	m_strNewElemType = _T("");
	//}}AFX_DATA_INIT
	m_iType = oldType;

	CString type1, type2;
	type1.LoadString( oldType );
	int newType = (oldType==IDC_ROD)?(IDC_HARDROD):(IDC_ROD);
	type2.LoadString( newType );

	m_strNewElemType = _T("Конвертировать\"") + type1 + _T("\"в\"") + type2 + _T("\"");
}


void CConvertToDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConvertToDlg)
	DDX_Text(pDX, IDC_EDIT_NEW_ELEM_TYPE, m_strNewElemType);
	DDV_MaxChars(pDX, m_strNewElemType, 80);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConvertToDlg, CDialog)
	//{{AFX_MSG_MAP(CConvertToDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConvertToDlg message handlers
