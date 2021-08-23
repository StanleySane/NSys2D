// ViewStyles.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "ViewStyles.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewStyles dialog


CViewStyles::CViewStyles(CWnd* pParent /*=NULL*/)
	: CDialog(CViewStyles::IDD, pParent)
{
	//{{AFX_DATA_INIT(CViewStyles)
	m_bNumElems = FALSE;
	m_bNumKnots = TRUE;
	m_bTextOut = FALSE;
	m_strFreeFont = _T("(no data)");
	m_strNumElems = _T("(no data)");
	m_strNumKnots = _T("(no data)");
	m_ZeroRot = 0.0;
	//}}AFX_DATA_INIT
	m_clrFree = RGB(0,0,0);
	m_clrNumElems = RGB(0,0,0);
	m_clrNumKnots = RGB(0,0,0);

	m_strFreeFont.Format("%s , %d", m_lfFree.lfFaceName, m_lfFree.lfHeight );
	m_strNumElems.Format("%s , %d", m_lfNumElems.lfFaceName, m_lfNumElems.lfHeight );
	m_strNumKnots.Format("%s , %d", m_lfNumKnots.lfFaceName, m_lfNumKnots.lfHeight );

	m_bFreeFontModified = m_bNumElemsFontModified = m_bNumKnotsFontModified = false;
}


void CViewStyles::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewStyles)
	DDX_Check(pDX, IDC_CHECK_NUM_ELEMS, m_bNumElems);
	DDX_Check(pDX, IDC_CHECK_NUM_KNOTS, m_bNumKnots);
	DDX_Check(pDX, IDC_TEXT_OUT, m_bTextOut);
	DDX_Text(pDX, IDC_FREE_FONT, m_strFreeFont);
	DDV_MaxChars(pDX, m_strFreeFont, 30);
	DDX_Text(pDX, IDC_NUM_ELEMS, m_strNumElems);
	DDV_MaxChars(pDX, m_strNumElems, 30);
	DDX_Text(pDX, IDC_NUM_KNOTS, m_strNumKnots);
	DDV_MaxChars(pDX, m_strNumKnots, 30);
	DDX_Text(pDX, IDC_EDIT_ZERO_ROT, m_ZeroRot);
	DDV_MinMaxDouble(pDX, m_ZeroRot, 0., 1.);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewStyles, CDialog)
	//{{AFX_MSG_MAP(CViewStyles)
	ON_BN_CLICKED(IDC_BUTTON_FREE_FONT, OnButtonFreeFont)
	ON_BN_CLICKED(IDC_BUTTON_NUM_ELEMS_FONT, OnButtonNumElemsFont)
	ON_BN_CLICKED(IDC_BUTTON_NUM_KNOTS_FONT, OnButtonNumKnotsFont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewStyles message handlers

void CViewStyles::OnButtonFreeFont() 
{
	// TODO: Add your control notification handler code here
	CFontDialog dlg( &m_lfFree );
	dlg.m_cf.Flags = CF_BOTH|CF_APPLY|CF_LIMITSIZE|CF_INITTOLOGFONTSTRUCT|CF_ENABLEHOOK;
	dlg.m_cf.rgbColors = m_clrFree;
	dlg.m_cf.nSizeMin = 8;
	dlg.m_cf.nSizeMax = 12;
	dlg.m_cf.Flags |= CF_EFFECTS;

	if( dlg.DoModal() == IDOK )
	{
		m_clrFree = dlg.GetColor();
		m_strFreeFont = dlg.GetFaceName();
		m_strFreeFont += _T(" , ");
		CString num;
		num.Format("%d", dlg.GetSize()/10 );
		m_strFreeFont += num;

		m_lfFree = (*dlg.m_cf.lpLogFont);

		SetDlgItemText(IDC_FREE_FONT, m_strFreeFont);
		m_bFreeFontModified = true;
	}
}

void CViewStyles::OnButtonNumElemsFont() 
{
	// TODO: Add your control notification handler code here
	CFontDialog dlg( &m_lfNumElems );
	dlg.m_cf.Flags = CF_BOTH|CF_APPLY|CF_LIMITSIZE|CF_INITTOLOGFONTSTRUCT|CF_ENABLEHOOK;
	dlg.m_cf.rgbColors = m_clrNumElems;
	dlg.m_cf.nSizeMin = 8;
	dlg.m_cf.nSizeMax = 12;
	dlg.m_cf.Flags |= CF_EFFECTS;

	if( dlg.DoModal() == IDOK )
	{
		m_clrNumElems = dlg.GetColor();
		m_strNumElems = dlg.GetFaceName();
		m_strNumElems += _T(" , ");
		CString num;
		num.Format("%d", dlg.GetSize()/10 );
		m_strNumElems += num;

		m_lfNumElems = (*dlg.m_cf.lpLogFont);

		SetDlgItemText(IDC_NUM_ELEMS, m_strNumElems);
		m_bNumElemsFontModified = true;
	}	
}

void CViewStyles::OnButtonNumKnotsFont() 
{
	// TODO: Add your control notification handler code here
	CFontDialog dlg( &m_lfNumKnots );
	dlg.m_cf.Flags = CF_BOTH|CF_APPLY|CF_LIMITSIZE|CF_INITTOLOGFONTSTRUCT|CF_ENABLEHOOK;
	dlg.m_cf.rgbColors = m_clrNumKnots;
	dlg.m_cf.nSizeMin = 8;
	dlg.m_cf.nSizeMax = 12;
	dlg.m_cf.Flags |= CF_EFFECTS;

	if( dlg.DoModal() == IDOK )
	{
		m_clrNumKnots = dlg.GetColor();
		m_strNumKnots = dlg.GetFaceName();
		m_strNumKnots += _T(" , ");
		CString num;
		num.Format("%d", dlg.GetSize()/10 );
		m_strNumKnots += num;

		m_lfNumKnots = (*dlg.m_cf.lpLogFont);

		SetDlgItemText(IDC_NUM_KNOTS, m_strNumKnots);
		m_bNumKnotsFontModified = true;
	}		
}
