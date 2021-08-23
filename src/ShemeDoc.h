// ShemeDoc.h : interface of the CShemeDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHEMEDOC_H__09A14A90_BBAC_11D2_AF23_BB2B1C460D22__INCLUDED_)
#define AFX_SHEMEDOC_H__09A14A90_BBAC_11D2_AF23_BB2B1C460D22__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "listknot.h"
#include "elem.h"
#include "rod.h"
#include "Demf.h"
#include "Spring.h"
#include "Mass.h"
#include "knot.h"
#include "KnotPropertyFrame.h"
#include "ProgressDlg.h"
#include "FreqParam.h"
#include "ParamIntegr.h"
#include "listspectr.h"

class CShemeDoc : public CDocument
{
protected: // create from serialization only
	CShemeDoc();
	DECLARE_DYNCREATE(CShemeDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShemeDoc)
	public:
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	int DelFreeKnot();
	int SetBeginPosition();
	int SetMatrMDC(int Count, int Freq=0);
	int UpdateAllFree();
	void AfterCalc();
	void SetConnectElements();
	int Numark(int nStep);
	CProgressDlg* pProgressDlg;
	int Park(int nStep);
	int RungeKutt(int nStep);
	void OnProperties();
	int PreCalculated();
	CElem* AddMass(CKnot * knot1);
	CElem* AddSpring(CKnot *knot1, CKnot *knot2);
	void ClearElem();
	CElem* AddDemf(CKnot * knot1, CKnot * knot2);
//	CRod* GoRodDlg(CRod* pRod=0);
//	CKnot* GoKnotDlg(CKnot * pKnot);
	CElem* AddRod(CKnot *knot1, CKnot *knot2);
//	CKnot* AddKnot(CKnot &knot);
	CList<CElem*,CElem*> listElem;
	
	CListKnot listKnot;
	CListSpectr listspectrP, listspectrU;

	CParamView ParamView;
	CFreqParam ParamFreq;
	CFreqParam ParamSpectrOut;
	CParamIntegr ParamIntegr;

	CMatr matr_M, matr_C, matr_D, matr_M_1, matr_RezY1, matr_RezY2, matr_RezY3;
	CMatr matr_UM, matr_UC, matr_UD;
	BOOL UEnable;
	virtual ~CShemeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	CKnotPropertyFrame* m_pPropFrame;
	//{{AFX_MSG(CShemeDoc)
	afx_msg void OnCalc();
	afx_msg void OnListelem();
	afx_msg void OnFreeformCalc();
	afx_msg void OnScaleadd();
	afx_msg void OnScalesub();
	afx_msg void OnRefresh();
	afx_msg void OnTest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CShemeDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHEMEDOC_H__09A14A90_BBAC_11D2_AF23_BB2B1C460D22__INCLUDED_)
