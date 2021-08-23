// GraphProp.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "GraphProp.h"

#include "GraphDlg.h"

#include <iterator>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphProp dialog


CGraphProp::CGraphProp( CGraphicView *pView, CWnd* pParent /*=NULL*/)
	: CDialog(CGraphProp::IDD, pParent), m_pView(pView)
{
	//{{AFX_DATA_INIT(CGraphProp)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CGraphProp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGraphProp)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGraphProp, CDialog)
	//{{AFX_MSG_MAP(CGraphProp)
	ON_LBN_DBLCLK(IDC_GRAPH_LIST, OnDblclkGraphList)
	ON_BN_CLICKED(IDC_GRAPH_EDIT, OnGraphEdit)
	ON_BN_CLICKED(IDC_GRAPH_NEW, OnGraphNew)
	ON_BN_CLICKED(IDC_GRAPH_DEL, OnGraphDel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphProp message handlers

BOOL CGraphProp::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	VERIFY( m_GraphList.SubclassDlgItem( IDC_GRAPH_LIST, this ) );
	m_GraphList.Fill( m_pView );
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGraphProp::OnDblclkGraphList() 
{
	// TODO: Add your control notification handler code here
	EditItem();
}

void CGraphProp::EditItem()
{
	int ind = m_GraphList.GetCurSel();
	if( ind == LB_ERR )
		return;
	DWORD dat = m_GraphList.GetItemData(ind);
	if( dat == LB_ERR )
		return;
	CGraphData *pGr = reinterpret_cast<CGraphData*>(dat);
	CGraphDlg dlg(pGr);
	dlg.DoModal();
	Invalidate();
}

void CGraphProp::OnGraphEdit() 
{
	// TODO: Add your control notification handler code here
	EditItem();
}

void CGraphProp::OnGraphNew() 
{
	// TODO: Add your control notification handler code here
	CGraphData Gr;
	CGraphDlg dlg(&Gr);
	if( dlg.DoModal() == IDOK )
	{
		m_pView->m_Graphs.push_back(Gr);
		m_GraphList.Fill(m_pView);
	}
}

void CGraphProp::OnOK() 
{
	// TODO: Add extra validation here
	GraphList::iterator beg = m_pView->m_Graphs.begin(), fin = m_pView->m_Graphs.end();
	for( GraphList::iterator it = beg; it != fin; ++it )
	{
		(*it).m_bEnable = (m_GraphList.GetCheck( distance(beg,it) ) == 1);
	}
	
	CDialog::OnOK();
}

void CGraphProp::OnGraphDel() 
{
	// TODO: Add your control notification handler code here
	int ind = m_GraphList.GetCurSel();
	if( ind == LB_ERR )
		return;
	if( ind >= m_pView->m_Graphs.size() )
		return;
	GraphList::iterator it = m_pView->m_Graphs.begin();
	advance( it, ind );
	m_pView->m_Graphs.erase(it);
	m_GraphList.Fill(m_pView);
}
