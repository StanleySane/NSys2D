// ScriptFrame.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "ScriptFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScriptFrame

IMPLEMENT_DYNCREATE(CScriptFrame, CMDIChildWnd)

CScriptFrame::CScriptFrame()
{
}

CScriptFrame::~CScriptFrame()
{
}


BEGIN_MESSAGE_MAP(CScriptFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CScriptFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptFrame message handlers

int CScriptFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_SCRIPT))
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

BOOL CScriptFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	//cs.style |= ES_AUTOHSCROLL|WS_HSCROLL;

	return CMDIChildWnd::PreCreateWindow(cs);
}
