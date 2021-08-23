// FreqView.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "FreqView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFreqView dialog


CFreqView::CFreqView(CWnd* pParent /*=NULL*/)
	: CDialog(CFreqView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFreqView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFreqView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFreqView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFreqView, CDialog)
	//{{AFX_MSG_MAP(CFreqView)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFreqView message handlers
