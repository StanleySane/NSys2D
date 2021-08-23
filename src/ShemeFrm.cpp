// ShemeFrm.cpp : implementation of the CShemeFrame class
//

#include "stdafx.h"
#include "NSys2D.h"

#include "ShemeFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShemeFrame

IMPLEMENT_DYNCREATE(CShemeFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CShemeFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CShemeFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR//,           // status line indicator
//	ID_SEPARATOR
};

/////////////////////////////////////////////////////////////////////////////
// CShemeFrame construction/destruction

CShemeFrame::CShemeFrame()
{
	// TODO: add member initialization code here
	
}

CShemeFrame::~CShemeFrame()
{
}

BOOL CShemeFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	//cs.style&=FWS_ADDTOTITLE;
	cs.cx=400;
	cs.cy=250;

	return CMDIChildWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CShemeFrame diagnostics

#ifdef _DEBUG
void CShemeFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CShemeFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CShemeFrame message handlers


int CShemeFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
/*	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetPaneInfo(
		0,
		m_wndStatusBar.GetItemID(0),
		SBPS_NOBORDERS,
		85);
	m_wndStatusBar.SetPaneStyle(0,SBPS_NORMAL);*/


/*	int f=m_wndStatusBar.GetPaneStyle(0);
	int a=SBPS_NORMAL;
	int b=SBPS_STRETCH;
	int c=SBPS_DISABLED;
	int d=SBPS_POPOUT;
	int e=SBPS_NOBORDERS;*/
	
	return 0;
}
