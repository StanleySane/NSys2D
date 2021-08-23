// ShemeVarNewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "ShemeVarNewDlg.h"

#include "ShemeVarsTable.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ShemeVarNewDlg dialog


ShemeVarNewDlg::ShemeVarNewDlg( CShemeVarsTable *p, bool flg/*=true*/, CWnd* pParent /*=NULL*/)
	: CDialog(ShemeVarNewDlg::IDD, pParent), m_pVarsTable(p)
{
	//{{AFX_DATA_INIT(ShemeVarNewDlg)
	m_strExpr = _T("0.0");
	m_strName = _T("");
	//}}AFX_DATA_INIT
	m_bNewVar = flg;
}


void ShemeVarNewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ShemeVarNewDlg)
	DDX_Text(pDX, IDC_EDIT_EXPR, m_strExpr);
	DDV_MaxChars(pDX, m_strExpr, 200);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDV_MaxChars(pDX, m_strName, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ShemeVarNewDlg, CDialog)
	//{{AFX_MSG_MAP(ShemeVarNewDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ShemeVarNewDlg message handlers

void ShemeVarNewDlg::OnOK() 
{
	// TODO: Add extra validation here
	if( UpdateData() == FALSE )
		return;
	string name(static_cast<LPCTSTR>(m_strName));
	if( m_bNewVar )
	{
		if( m_pVarsTable->IsReservedVarName(name) )
		{
			AfxMessageBox("Нельзя использовать зарезервированное имя переменной");
			return;
		}
		if( !m_pVarsTable->IsValidVarName(name) )
		{
			AfxMessageBox("Некорректное имя переменной");
			return;
		}
		if( m_pVarsTable->IsVarName(name) )
		{
			AfxMessageBox("Переменная с таким имененем уже существует");
			return;
		}
	}
	string ec;
	ShemeExprErr err = m_pVarsTable->IsValidExpr(string(static_cast<LPCTSTR>(m_strExpr)), ec );
	if( err != SEE_NOERR )
	{
		CString mes("Ошибка в выражении:\n");
		mes += CShemeExpr::GetErrorMessage(err).c_str();
		if( !ec.empty() )
		{
			mes += CString(": ") + CString( ec.c_str() );
		}
		AfxMessageBox(mes);
		return;
	}
	CDialog::OnOK();
}

BOOL ShemeVarNewDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if( !m_bNewVar )
	{
		//если открываем в режиме не ввода новой переменной,
		//а редактирования уже существующей.
		GetDlgItem(IDC_EDIT_NAME)->EnableWindow( FALSE );
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
