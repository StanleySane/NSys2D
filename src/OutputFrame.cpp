// OutputFrame.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "OutputFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputFrame

IMPLEMENT_DYNCREATE(COutputFrame, CMDIChildWnd)

COutputFrame::COutputFrame()
{
}

COutputFrame::~COutputFrame()
{
}


BEGIN_MESSAGE_MAP(COutputFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(COutputFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutputFrame message handlers

int COutputFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//ModifyStyle( (DWORD)(WS_SYSMENU|WS_MINIMIZEBOX|WS_MAXIMIZEBOX), (DWORD)0 );

	// TODO: Add your specialized creation code here
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_OUTPUT))
	{
		TRACE0("Failed to create toolbar for script\n");
		return -1;      // fail to create
	}
	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}
