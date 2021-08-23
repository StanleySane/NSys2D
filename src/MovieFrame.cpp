// MovieFrame.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "MovieFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMovieFrame

IMPLEMENT_DYNCREATE(CMovieFrame, CMDIChildWnd)

CMovieFrame::CMovieFrame()
{
}

CMovieFrame::~CMovieFrame()
{
}


BEGIN_MESSAGE_MAP(CMovieFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CMovieFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT BASED_CODE ToolBar[] = 
{
//внимание !!!
//Содержание данного массива должно совпадать с содержанием
//ToolBar-а Movie.bmp !!!
	ID_MOVIE_PREV_STEP,
	ID_MOVIE_RUN,
	ID_MOVIE_PAUSE,
	ID_MOVIE_STOP,
	ID_MOVIE_NEXT_STEP,
		ID_SEPARATOR,
	ID_MOVIE_AUTO_SCALE,
	ID_MOVIE_SCALE_INC,
	ID_MOVIE_SCALE_DEC,
	ID_MOVIE_MOVE_UP,
	ID_MOVIE_MOVE_DOWN,
	ID_MOVIE_MOVE_LEFT,
	ID_MOVIE_MOVE_RIGHT,
		ID_SEPARATOR,
	ID_SEPARATOR,//место для таймера
		ID_SEPARATOR,
	ID_MOVIE_PARAMS
};

/////////////////////////////////////////////////////////////////////////////
// CMovieFrame message handlers

int CMovieFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MOVIE)||
		!m_wndToolBar.SetButtons(ToolBar,sizeof(ToolBar)/sizeof(UINT)))
	{
		TRACE0("Failed to create toolbar for movie\n");
		return -1;      // fail to create
	}
	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	static int TextWidth = 150;//ширина поля вывода
	m_wndToolBar.SetButtonInfo( 14, ID_CURRENT_TIME, TBBS_SEPARATOR, TextWidth );
	m_wndToolBar.SetButtonInfo( 13, ID_SEPARATOR, TBBS_SEPARATOR, 12 );
	m_wndToolBar.SetButtonInfo( 15, ID_SEPARATOR, TBBS_SEPARATOR, 12 );
	CRect rect;
	m_wndToolBar.GetItemRect( 14, &rect );
	if( !m_CurrentTime.Create("Текущее время:",
		WS_CHILD|WS_VISIBLE|BS_TEXT|BS_LEFT|BS_FLAT,
		rect, &m_wndToolBar, ID_CURRENT_TIME) )
	{
		TRACE0("Failed to create static item for movie\n");
		return -1;      // fail to create
	}
	/*
	CFont fnt;
	if( !::GetSystemMetrics(SM_DBCSENABLED) )
	{
		LOGFONT logFont;
		memset( &logFont, 0, sizeof(logFont) );
		logFont.lfHeight = 80;
		logFont.lfPitchAndFamily = DEFAULT_PITCH|FF_SWISS;
		lstrcpy( logFont.lfFaceName, _T("MS Sans Serif") );
		if( !fnt.CreateFontIndirect( &logFont ) )
			TRACE0("Не возможно создание шрифта для списка\n");
		else
			m_CurrentTime.SetFont( &fnt );

	}
	else
	{
		fnt.Attach(::GetStockObject(SYSTEM_FONT));
		m_CurrentTime.SetFont( &fnt );
	}
	*/
	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	
	return 0;
}
