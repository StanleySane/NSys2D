// KnotPropertyFrame.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "KnotPropertyFrame.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKnotPropertyFrame

IMPLEMENT_DYNCREATE(CKnotPropertyFrame, CMiniFrameWnd)

CKnotPropertyFrame::CKnotPropertyFrame()
{
	m_pModelessPropSheet = NULL;
}

CKnotPropertyFrame::~CKnotPropertyFrame()
{
}


BEGIN_MESSAGE_MAP(CKnotPropertyFrame, CMiniFrameWnd)
	//{{AFX_MSG_MAP(CKnotPropertyFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_SETFOCUS()
	ON_WM_ACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CKnotPropertyFrame message handlers

int CKnotPropertyFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMiniFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_pModelessPropSheet = new CKnotPropertySheet(0,this,true);
	if (!m_pModelessPropSheet->Create(this, 
		WS_CHILD | WS_VISIBLE, 0))
	{
		delete m_pModelessPropSheet;
		m_pModelessPropSheet = NULL;
		return -1;
	}

	// Resize the mini frame so that it fits around the child property
	// sheet.
	CRect rectClient, rectWindow;
	m_pModelessPropSheet->GetWindowRect(rectClient);
	rectWindow = rectClient;

	// CMiniFrameWnd::CalcWindowRect adds the extra width and height
	// needed from the mini frame.
	CalcWindowRect(rectWindow);
	SetWindowPos(NULL, rectWindow.left, rectWindow.top,
		rectWindow.Width(), rectWindow.Height(),
		SWP_NOZORDER | SWP_NOACTIVATE);
	m_pModelessPropSheet->SetWindowPos(NULL, 0, 0,
		rectClient.Width(), rectClient.Height(),
		SWP_NOZORDER | SWP_NOACTIVATE);

	return 0;
}

void CKnotPropertyFrame::OnClose() 
{
	// Instead of closing the modeless property sheet, just hide it.
	ShowWindow(SW_HIDE);
}

void CKnotPropertyFrame::OnSetFocus(CWnd* pOldWnd) 
{
	CMiniFrameWnd::OnSetFocus(pOldWnd);
}

void CKnotPropertyFrame::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CMiniFrameWnd::OnActivate(nState, pWndOther, bMinimized);

	// Forward any WM_ACTIVATEs to the property sheet...
	// Like the dialog manager itself, it needs them to save/restore the focus.
	ASSERT_VALID(m_pModelessPropSheet);

	// Use GetCurrentMessage to get unmodified message data.
	const MSG* pMsg = GetCurrentMessage();
	ASSERT(pMsg->message == WM_ACTIVATE);
	m_pModelessPropSheet->SendMessage(pMsg->message, pMsg->wParam,
		pMsg->lParam);
}
