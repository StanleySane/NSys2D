// GroupEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "GroupEditDlg.h"

#include "StdAfxMy.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGroupEditDlg dialog


CGroupEditDlg::CGroupEditDlg( const CShemeGroup *gr, CWnd* pParent /*=NULL*/)
	: CDialog(CGroupEditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGroupEditDlg)
	m_strGroup = _T("");
	m_strGroupName = _T("");
	m_strGroupSet = _T("");
	m_strGroupType = _T("");
	//}}AFX_DATA_INIT
	gr->GetName( m_strGroupName );
	gr->GetGroup( m_strGroup );

	m_iGrType = gr->GetType();

	if( m_iGrType == 0 )
	{
		m_strGroupType = _T("Ёлементы");
	}
	else
	{
		m_strGroupType = _T("”злы");
	}

	CShemeGroup tmpgr( m_strGroup, m_strGroupName, m_iGrType );
	//здесь не вызываем ф-цию Analize,
	//т.к. полагаем, что указатель *gr уже был корректный.
	//это значит, что Analize надо вызывать об€зательно
	//ещЄ при создании новой группы.
	ARRAY vec;
	if( !tmpgr.GetNumSet( vec ) )
	{
		CString em;
		tmpgr.GetErrorMessage( em );
		AfxMessageBox(em);
		vec.clear();
	}
		
	CString str;
	int s = vec.size();
	for( int i = 0; i < s; i++ )
	{
		CString tmp;
		tmp.Format("%d", vec[i] );
		str += tmp;
		if( i != (s-1) )
			str += _T(',');
	}

	m_strGroupSet = str;
}


void CGroupEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGroupEditDlg)
	DDX_Text(pDX, IDC_EDIT_GROUP_INEDIT, m_strGroup);
	DDV_MaxChars(pDX, m_strGroup, 90);
	DDX_Text(pDX, IDC_EDIT_GROUP_NAME_INEDIT, m_strGroupName);
	DDV_MaxChars(pDX, m_strGroupName, 30);
	DDX_Text(pDX, IDC_EDIT_GROUP_SET, m_strGroupSet);
	DDX_Text(pDX, IDC_EDIT_GROUP_TYPE_INEDIT, m_strGroupType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGroupEditDlg, CDialog)
	//{{AFX_MSG_MAP(CGroupEditDlg)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, OnButtonRefresh)
	ON_BN_CLICKED(IDC_BUTTON_PACK, OnButtonPack)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGroupEditDlg message handlers

void CGroupEditDlg::OnButtonRefresh() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CShemeGroup gr( m_strGroup, m_strGroupName, m_iGrType );

	if( !gr.Analize() )
	{
		CString str;
		gr.GetErrorMessage( str );
		AfxMessageBox( str );
	}
	else
	{
		ARRAY vec;
		if( !gr.GetNumSet(vec) )
		{
			CString str;
			gr.GetErrorMessage( str );
			AfxMessageBox( str );
		}
		else
		{
			CString str;
			int s = vec.size();
			for( int i = 0; i < s; i++ )
			{
				CString tmp;
				tmp.Format("%d", vec[i] );
				str += tmp;
				if( i != (s-1) )
					str += _T(',');
			}
			m_strGroupSet = str;
		}
	}
	UpdateData(FALSE);
}

void CGroupEditDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	CShemeGroup gr( m_strGroup, m_strGroupName, m_iGrType );

	if( !gr.Analize() )
	{
		CString str;
		gr.GetErrorMessage( str );
		AfxMessageBox( str );
		return;
	}
	else
	{
		ARRAY vec;
		if( !gr.GetNumSet(vec) )
		{
			CString str;
			gr.GetErrorMessage( str );
			AfxMessageBox( str );
			return;
		}
	}
	
	CDialog::OnOK();
}

void CGroupEditDlg::OnButtonPack() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CShemeGroup gr( m_strGroup, m_strGroupName, m_iGrType );

	if( !gr.Analize() )
	{
		CString str;
		gr.GetErrorMessage( str );
		AfxMessageBox( str );
	}
	else
	{
		ARRAY vec;
		if( !gr.GetNumSet(vec) )
		{
			CString str;
			gr.GetErrorMessage( str );
			AfxMessageBox( str );
		}
		else
		{
			CString str;
			int s = vec.size();
			for( int i = 0; i < s; i++ )
			{
				CString tmp;
				tmp.Format("%d", vec[i] );
				str += tmp;
				if( i != (s-1) )
					str += _T(',');
			}
			m_strGroupSet = str;
			m_strGroup = CShemeGroup::GetPackedGroup( vec );
		}
	}
	UpdateData(FALSE);
}
