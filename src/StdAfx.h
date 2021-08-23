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
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#ifdef _DEBUG
	//	отключаем предупреждение о слишком длинном декорированном имени
	#pragma warning (disable:4786)
#endif

//	методы поиска собств.форм и значений
typedef enum{EVM_JACOBY = 0, EVM_QR_ELM, EVM_QR_DIR, EVM_QR_ORT}	EV_METHOD;
//	ошибки поиска собств.значений
typedef enum{ EVE_NOERR = 0, EVE_NOSOLUT, EVE_DIMERR } EV_EXCEPT;

//наименьшее число в ЭВМ, для которого выполняется
//условие: 1+MACHEPS>1.
#define MACHEPS 1e-250
#define MACH_EPS 5.24e-20
//наименьшее положительное число
#define ETA 1.7e-308
#define ZERO 1e-300
#define TOL (ETA/MACH_EPS)

typedef enum{ BME_NOERR = 0, BME_NULLONDIAG, BME_DIMERR } SBM_EXCEPT;
typedef enum{ BMC_SOLVE = 0, BMC_GETDET }	SBM_ERRCONTROL;
typedef enum{ BMI_FULL = 0, BMI_ONE }	SBM_ITERAT;

typedef struct _det_
{
//представление определителя в виде mant*2^power.
	double mant;
	int power;
}	DETERMINANT;

#include<vector>
typedef std::vector<int>	ARRAY;
typedef std::vector<double>	DOUBLE_ARRAY;

//	right_move = left_move + rotate*L
typedef struct __TRIPLE__
{
	int right_move;
	int left_move;
	int rotate;
	double L;
}	Triple;

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__09A14A8A_BBAC_11D2_AF23_BB2B1C460D22__INCLUDED_)
