// ShemeVars.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "ShemeVars.h"

#include "ShemeVarNewDlg.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShemeVars dialog


CShemeVars::CShemeVars( CShemeVarsTable *p,
					   CWnd* pParent /*=NULL*/)
	: CDialog(CShemeVars::IDD, pParent), m_pVarsTable(p), m_bValidTable(true)
{
	m_bWasActions = false;
	//{{AFX_DATA_INIT(CShemeVars)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CShemeVars::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShemeVars)
	DDX_Control(pDX, IDC_VARS_LIST, m_VarList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShemeVars, CDialog)
	//{{AFX_MSG_MAP(CShemeVars)
	ON_BN_CLICKED(IDC_RECALC, OnRecalc)
	ON_BN_CLICKED(IDC_ADD_VAR, OnAddVar)
	ON_BN_CLICKED(IDC_DEL_VAR, OnDelVar)
	ON_BN_CLICKED(IDC_EDIT_VAR, OnEditVar)
	ON_WM_DESTROY()
	ON_NOTIFY(NM_DBLCLK, IDC_VARS_LIST, OnDblclkVarsList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//ON_NOTIFY( ON_EN_KILLFOCUS, ID_SHEME_VAR_EDIT, OnEndEdit )

/////////////////////////////////////////////////////////////////////////////
// CShemeVars message handlers

BOOL CShemeVars::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	/*
	ASSERT( ::IsWindow(m_VarList.m_hWnd) );
	DWORD dwStyle = GetWindowLong( m_VarList.m_hWnd, GWL_EXSTYLE );
	DWORD dwNewStyle = LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_REPORT;
	if( (dwStyle & LVS_TYPEMASK) != dwNewStyle )
		SetWindowLong( m_VarList.m_hWnd, GWL_EXSTYLE,
					(dwStyle & ~LVS_TYPEMASK)|dwNewStyle );
	*/

	m_VarList.InsertColumn( 
		0, _T("Имя переменной"), LVCFMT_LEFT, 140);
	m_VarList.InsertColumn( 
		1, _T("Выражение"), LVCFMT_LEFT, 380);
	m_VarList.InsertColumn( 
		2, _T("Текущее значение"), LVCFMT_LEFT, 130);

	ShemeVarsTable *pT = m_pVarsTable->GetVarsTable();
	ShemeVarsTable::iterator fin = pT->end(), it, beg = pT->begin();
	int pos = 0;
	for( it = beg; it != fin; ++it )
	{
		//SetItem( it, distance( beg, it ), true );
		if( !m_pVarsTable->IsReservedVarName( (*it).first ) )
		{
			SetItem( it, pos, true );
			pos++;
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

bool CShemeVars::SetItem( ShemeVarsTable::iterator &it, int index, bool insert/*=false*/)
{
	LV_ITEM item;
	item.iItem = index;
	item.mask = LVIF_TEXT;
	item.iImage = 0;
	CString csText;

	item.iSubItem = 0;
	csText = ((*it).first).c_str();
	item.pszText = (LPTSTR)(LPCTSTR)csText;
	if( insert )
		m_VarList.InsertItem( &item );
	else
		m_VarList.SetItem( &item );

	item.iSubItem = 1;
	csText = (((*it).second)->GetExpr()).c_str();
	item.pszText = (LPTSTR)(LPCTSTR)csText;
	m_VarList.SetItem( &item );

	bool flg = true;//флаг об успешности
	item.iSubItem = 2;
	ShemeExprErr er;
	double res = m_pVarsTable->GetVarValue( (*it).first, er );
	if( er == SEE_NOERR )
		csText.Format("%.16g", res );
	else
	{
		if( er == SEE_CERROR )
		{
			er = m_pVarsTable->GetCompileErrorCode((*it).first);
			flg = false;
		}
		csText = CShemeExpr::GetErrorMessage(er).c_str();
		string ec = m_pVarsTable->GetErrorCause( (*it).first );
		if( !ec.empty() )
			csText += CString(": ") + CString( ec.c_str() );
	}
	item.pszText = (LPTSTR)(LPCTSTR)csText;
	m_VarList.SetItem( &item );

	return flg;
}

bool CShemeVars::Recalc()
{
	m_bValidTable = true;
	ShemeVarsTable *pT = m_pVarsTable->GetVarsTable();
	ShemeVarsTable::iterator fin = pT->end(), it, beg = pT->begin();
	int pos = 0;
	for( it = beg; it != fin; ++it )
	{
		if( !m_pVarsTable->IsReservedVarName( (*it).first ) )
		{
			//if( SetItem( it, distance( beg, it ) ) == false )
			if( SetItem( it, pos ) == false )
				m_bValidTable = false;
			pos++;
		}
	}
	return m_bValidTable;
}

void CShemeVars::OnRecalc() 
{
	// TODO: Add your control notification handler code here
	Recalc();
}

void CShemeVars::OnOK() 
{
	// TODO: Add extra validation here
	if( Recalc() == false )
	{
		CString mes("Таблица переменных содержит одну или несколько ошибок !");
		mes += _T("\nИх необходимо исправить.\n");
		mes += _T("(проще удалить переменные, содержащие ошибки)");
		AfxMessageBox(mes);
		return;
	}
	
	CDialog::OnOK();
}

int CShemeVars::GetSelectedIndex()
{
	int s = m_VarList.GetItemCount();
	for( int i = 0; i < s; i++ )
	{
		if( m_VarList.GetItemState( i, LVIS_SELECTED ) == LVIS_SELECTED )
			return i;
	}
	return -1;
}

void CShemeVars::OnAddVar() 
{
	// TODO: Add your control notification handler code here
	ShemeVarNewDlg dlg( m_pVarsTable );
	if( dlg.DoModal() == IDOK )
	{
		string name( static_cast<LPCTSTR>(dlg.m_strName) );
		string expr( static_cast<LPCTSTR>(dlg.m_strExpr) );
		ShemeExprErr er = m_pVarsTable->AddVar( name, expr );
		ASSERT( er == SEE_NOERR );
		ShemeVarsTable *pT = m_pVarsTable->GetVarsTable();
		ShemeVarsTable::iterator it = pT->find(name);
		ASSERT( it != pT->end() );
		//SetItem( it, distance( pT->begin(), it ), true );
		SetItem( it, m_VarList.GetItemCount(), true );
		m_bWasActions = true;
	}
}

void CShemeVars::OnDelVar() 
{
	// TODO: Add your control notification handler code here
	int ind = GetSelectedIndex();
	if( ind < 0 )
		return;
	CString strName = m_VarList.GetItemText( ind, 0 );
	string name( static_cast<LPCTSTR>(strName) );
	bool flg = m_pVarsTable->DelVar(name);
	ASSERT( flg == true );
	BOOL res = m_VarList.DeleteItem(ind);
	ASSERT( res != FALSE );
	m_bWasActions = true;	
}

void CShemeVars::OnEditVar() 
{
	// TODO: Add your control notification handler code here
	EditVar();
}

void CShemeVars::EditVar()
{
	int ind = GetSelectedIndex();
	if( ind < 0 )
		return;
	BOOL flg = m_VarList.EnsureVisible( ind, FALSE );
	ASSERT(flg);
	ShemeVarNewDlg dlg( m_pVarsTable, false );
	dlg.m_strName = m_VarList.GetItemText( ind, 0 );
	dlg.m_strExpr = m_VarList.GetItemText( ind, 1 );
	if( dlg.DoModal() == IDOK )
	{
		string name( static_cast<LPCTSTR>(dlg.m_strName) );
		string expr( static_cast<LPCTSTR>(dlg.m_strExpr) );
		ShemeExprErr er = m_pVarsTable->ResetVar( name, expr );
		ASSERT( er == SEE_NOERR );
		ShemeVarsTable *pT = m_pVarsTable->GetVarsTable();
		ShemeVarsTable::iterator it = pT->find(name);
		ASSERT( it != pT->end() );
		//SetItem( it, distance( pT->begin(), it ), false );
		SetItem( it, ind );
		m_bWasActions = true;
	}
}



void CShemeVars::OnDblclkVarsList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	EditVar();
	
	*pResult = 0;
}
