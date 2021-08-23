// KnotPropertySheet.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "KnotPropertySheet.h"
#include "ListKnot.h"
#include "ListSpectr.h"

#include "shemedoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKnotPropertySheet

IMPLEMENT_DYNAMIC(CKnotPropertySheet, CPropertySheet)

CKnotPropertySheet::CKnotPropertySheet(
					CKnot *pKn, 
					CWnd* pWndParent)
	 : CPropertySheet(IDS_PROPSHT_CAPTION1, pWndParent)
{
	// Add all of the property pages here.  Note that
	// the order that they appear in here will be
	// the order they appear in on screen.  By default,
	// the first page of the set is the active one.
	// One way to make a different property page the 
	// active one is to call SetActivePage().
	
	//m_psh.dwFlags|=PSH_NOAPPLYNOW;

	CString str;
	str.Format("Свойства узла №%d",pKn->Num);
	SetTitle(str);

	pKnot=pKn;
	AddPage(&m_Page1);
	AddPage(&m_Page2);
	AddPage(&m_Page3);
	AddPage(&m_Page4);

/*	pListKnot=_pListKnot;
	pListSpectr=_pListSpectr;*/
}

CKnotPropertySheet::~CKnotPropertySheet()
{
}


BEGIN_MESSAGE_MAP(CKnotPropertySheet, CPropertySheet)
	//{{AFX_MSG_MAP(CKnotPropertySheet)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CKnotPropertySheet message handlers

void CKnotPropertySheet::PostNcDestroy()
{
	CPropertySheet::PostNcDestroy();
	delete this;
}



int CKnotPropertySheet::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	
	if (CPropertySheet::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	//CWnd::ModifyStyle(GetTabControl()->m_hWnd,TCS_MULTILINE|PSH_NOAPPLYNOW, TCS_SINGLELINE,0);
	//lpCreateStruct->style|=!PSH_NOAPPLYNOW;

	m_Page1.pKnot=pKnot;
	m_Page2.pKnot=pKnot;
	m_Page3.pKnot=pKnot;
	m_Page4.pKnot=pKnot;

	CShemeDoc *pDoc=(CShemeDoc*)(((CMDIFrameWnd*)AfxGetMainWnd())->MDIGetActive()->GetActiveDocument());
	m_Page3.pListKnot=&(pDoc->listKnot);
	m_Page3.pListSpectr=&(pDoc->listspectrP);
	m_Page4.pListKnot=&(pDoc->listKnot);
	m_Page4.pListSpectr=&(pDoc->listspectrU);

	CString str;
	str.Format("узла №%d",pKnot->Num);
	SetTitle(str,PSH_PROPTITLE);
	
	return 0;
}

