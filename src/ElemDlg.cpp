// ElemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "ElemDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CElemDlg dialog


CElemDlg::CElemDlg(CList<CElem*,CElem*> *plistelem,
				   CListKnot *plistknot,
				   CWnd* pParent /*=NULL*/)
	: CDialog(CElemDlg::IDD, pParent)
{
	pListElem=plistelem;
	pListKnot=plistknot;
	//{{AFX_DATA_INIT(CElemDlg)
	//}}AFX_DATA_INIT
}


void CElemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CElemDlg)
	DDX_Control(pDX, IDC_LISTCONTROL, m_ListControl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CElemDlg, CDialog)
	//{{AFX_MSG_MAP(CElemDlg)
	ON_BN_CLICKED(IDC_BUTTONPROP, OnButtonprop)
	ON_BN_CLICKED(IDC_BUTTONDEL, OnButtondel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CElemDlg message handlers

BOOL CElemDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//m_ListBox.ModifyStyle(0,LBS_MULTICOLUMN);
	
	m_ListControl.InsertColumn( 
		0, _T("Тип элемента"), LVCFMT_LEFT, 120);
	m_ListControl.InsertColumn( 
		1, _T("№:"), LVCFMT_LEFT, 30);
	m_ListControl.InsertColumn( 
		2, _T("Узел 1"), LVCFMT_LEFT, 129);
	m_ListControl.InsertColumn( 
		3, _T("Узел 2"), LVCFMT_LEFT, 129);

	int count=0;
	POSITION pos=pListElem->GetHeadPosition();
	while (pos)
	{
		CElem *elem=pListElem->GetNext(pos);
		SetItem(elem,count++,TRUE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CElemDlg::OnButtonprop() 
{
	// TODO: Add your control notification handler code here
	int index=GetSelectIndex();
	if (index>=0)
	{
		CElem* elem=pListElem->GetAt(GetElemPosition(index));
		elem->GoDlg(pListKnot);
		SetItem(elem,index);
	}
}

void CElemDlg::OnButtondel() 
{
	// TODO: Add your control notification handler code here
	int index=GetSelectIndex();
	if (index>=0)
	{
		CElem* elem = pListElem->GetAt(GetElemPosition(index));
		delete elem;
//		elem->knot1->DelElemKnot(elem->knot2);
//		elem->knot2->DelElemKnot(elem->knot1);
		pListElem->RemoveAt(GetElemPosition(index));
		m_ListControl.DeleteItem(index);
	}
}

POSITION CElemDlg::GetElemPosition(int num)
{
	POSITION pos2,pos=pListElem->GetHeadPosition();
	int Count=0;
	while (pos)
	{
		pos2=pos;
		CElem *elem=pListElem->GetNext(pos);
		if (Count==num) return pos2;
		Count++;
	}
	return 0;
}

int CElemDlg::GetSelectIndex()
{
	int Count=m_ListControl.GetItemCount();
	for (int i=0;i<Count;i++)
		if (m_ListControl.GetItemState(i,LVIS_SELECTED)==LVIS_SELECTED) return i;
	return -1;
}

int CElemDlg::SetItem(CElem * elem, int index, BOOL insert/*=FALSE*/)
{
	LV_ITEM item;
	item.iItem=index;
	item.mask=LVIF_TEXT;
	item.iImage=0;
	CString csText;

	item.iSubItem=0;
	csText.LoadString(elem->TypeElem);
	item.pszText=(LPTSTR)(LPCTSTR)csText;
	if (insert) m_ListControl.InsertItem(&item);
	else m_ListControl.SetItem(&item);

	csText.Format("%d", elem->GetNumber() );
	item.iSubItem=1;
	item.pszText=(LPTSTR)(LPCTSTR)csText;
//	if (insert) m_ListControl.InsertItem(&item);
//	else 
	m_ListControl.SetItem(&item);

	item.iSubItem=2;
	csText=elem->knot1->GetName();
	item.pszText=(LPTSTR)(LPCTSTR)csText;
	m_ListControl.SetItem(&item);

	if (elem->TypeElem!=IDC_MASS)
	{
		item.iSubItem=3;
		csText=elem->knot2->GetName();
		item.pszText=(LPTSTR)(LPCTSTR)csText;
		m_ListControl.SetItem(&item);
	}
	return 1;
}
