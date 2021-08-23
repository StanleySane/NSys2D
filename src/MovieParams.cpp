// MovieParams.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "MovieParams.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMovieParams dialog


CMovieParams::CMovieParams(CWnd* pParent /*=NULL*/)
	: CDialog(CMovieParams::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMovieParams)
	m_uTimerElapse = 1;
	m_StartTime = 0;
	m_bShowKnots = TRUE;
	//}}AFX_DATA_INIT
}


void CMovieParams::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMovieParams)
	DDX_Text(pDX, IDC_EDIT_TIMER_ELAPSE, m_uTimerElapse);
	DDV_MinMaxUInt(pDX, m_uTimerElapse, 1, 1000);
	DDX_Text(pDX, IDC_EDIT_START_TIME, m_StartTime);
	DDV_MinMaxInt(pDX, m_StartTime, 0, 1000000);
	DDX_Check(pDX, IDC_CHECK_SHOW_KNOTS, m_bShowKnots);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMovieParams, CDialog)
	//{{AFX_MSG_MAP(CMovieParams)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMovieParams message handlers
