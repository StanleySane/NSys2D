// NSys2D.h : main header file for the NSYS2D application
//

#if !defined(AFX_NSYS2D_H__09A14A87_BBAC_11D2_AF23_BB2B1C460D22__INCLUDED_)
#define AFX_NSYS2D_H__09A14A87_BBAC_11D2_AF23_BB2B1C460D22__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CNSys2DApp:
// See NSys2D.cpp for the implementation of this class
//

class CNSys2DApp : public CWinApp
{
public:
	CNSys2DApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNSys2DApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CNSys2DApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NSYS2D_H__09A14A87_BBAC_11D2_AF23_BB2B1C460D22__INCLUDED_)
