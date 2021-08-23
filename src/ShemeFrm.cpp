// ShemeFrm.cpp : implementation of the CShemeFrame class
//

#include "stdafx.h"
#include "NSys2D.h"
#include "CoordD.h"

#include "ShemeFrm.h"
#include "ShemeDoc.h"

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
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_NUM, OnUpdateIndicatorNum )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_NUM
};
extern CCoordD MousePos;

/////////////////////////////////////////////////////////////////////////////
// CShemeFrame construction/destruction

CShemeFrame::CShemeFrame()
{
	// TODO: add member initialization code here
	MousePos = CCoordD(0.0,0.0);	
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

void CShemeFrame::OnUpdateIndicatorNum( CCmdUI *pCmdUI )
{
	CString str;
	str.Format("%.3lf,%.3lf", MousePos.x, MousePos.y );
	pCmdUI->SetText(str);
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
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetPaneInfo(1, ID_INDICATOR_NUM, SBPS_STRETCH, 20 );


/*	int f=m_wndStatusBar.GetPaneStyle(0);
	int a=SBPS_NORMAL;
	int b=SBPS_STRETCH;
	int c=SBPS_DISABLED;
	int d=SBPS_POPOUT;
	int e=SBPS_NOBORDERS;*/
	
	return 0;
}

