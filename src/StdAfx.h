// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__09A14A8A_BBAC_11D2_AF23_BB2B1C460D22__INCLUDED_)
#define AFX_STDAFX_H__09A14A8A_BBAC_11D2_AF23_BB2B1C460D22__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC OLE automation classes

#include<gl\gl.h>
#include<gl\glu.h>
//#include<gl\glaux.h>

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#ifdef _DEBUG
//	отключаем предупреждение о слишком длинном декорированном имени
#pragma warning (disable:4786)

#pragma warning (disable:4305)
#pragma warning (disable:4244)
#pragma warning (disable:4136)
#pragma warning (disable:4051)
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__09A14A8A_BBAC_11D2_AF23_BB2B1C460D22__INCLUDED_)
