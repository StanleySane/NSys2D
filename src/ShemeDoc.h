// ShemeDoc.h : interface of the CShemeDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHEMEDOC_H__09A14A90_BBAC_11D2_AF23_BB2B1C460D22__INCLUDED_)
#define AFX_SHEMEDOC_H__09A14A90_BBAC_11D2_AF23_BB2B1C460D22__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//#include "ListKnot.h"
#include "elem.h"
#include "rod.h"
#include "HardRod.h"
#include "Demf.h"
#include "Spring.h"
#include "Mass.h"
#include "knot.h"
#include "KnotPropertyFrame.h"
#include "ProgressDlg.h"
//#include "FreqParam.h"
//#include "ParamIntegr.h"
//#include "ListSpectr.h"
//#include "ShemeGroup.h"


class CSheme;
class CShemeGroup;

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
//	int SetBeginPosition();
//	int SetMatrMDC(int Count, int Freq=0);
//	int UpdateAllFree();
//	void AfterCalc();
//	void SetConnectElements();
	int Numark(int nStep);
	int Park(int nStep);
	int RungeKutt(int nStep);
	void OnProperties();
	int PreCalculated();

	CElem* AddDemf(CKnot * knot1, CKnot * knot2);
	CElem* AddMass(CKnot * knot1);
	CElem* AddSpring(CKnot *knot1, CKnot *knot2);
	CElem* AddRod(CKnot *knot1, CKnot *knot2);
	CElem* AddHardRod(CKnot *knot1, CKnot *knot2);
//	void ClearElem();
//	CRod* GoRodDlg(CRod* pRod=0);
//	CKnot* GoKnotDlg(CKnot * pKnot);
//	CKnot* AddKnot(CKnot &knot);

	CProgressDlg* pProgressDlg;
	//m_bIsView нужна для исключения повторного создания
	//окна с формами
	bool m_bIsView;
	bool m_bMakeBar;//создавать ли в заголовке CDialogBar

	CParamView ParamView;

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
	afx_msg void OnShemeParams();
	afx_msg void OnViewStyles();
	afx_msg void OnUpdateFreeformCalc(CCmdUI* pCmdUI);
	afx_msg void OnGroupNew();
	afx_msg void OnGroupList();
	afx_msg void OnGroupElemDel();
	afx_msg void OnGroupElemProp();
	afx_msg void OnGroupPreview();
	afx_msg void OnAllDemf();
	afx_msg void OnAllHardRods();
	afx_msg void OnAllMasses();
	afx_msg void OnAllRods();
	afx_msg void OnAllSprings();
	afx_msg void OnGroupConvertTo();
	afx_msg void OnGroupClickElems();
	afx_msg void OnGroupClickKnots();
	afx_msg void OnUpdateGroupClickElems(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGroupClickKnots(CCmdUI* pCmdUI);
	afx_msg void OnButtonDelFreeKnots();
	afx_msg void OnUpdateAllDemf(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAllHardrods(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAllMasses(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAllRods(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAllSprings(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCalc(CCmdUI* pCmdUI);
	afx_msg void OnUpdateButtonDelFreeKnots(CCmdUI* pCmdUI);
	afx_msg void OnUpdateListelem(CCmdUI* pCmdUI);
	afx_msg void OnUpdateElemgroupDel(CCmdUI* pCmdUI);
	afx_msg void OnUpdateElemgroupProp(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGroupConvertTo(CCmdUI* pCmdUI);
	afx_msg void OnUpdateShemeParams(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGroupNew(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGroupList(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGroupPreview(CCmdUI* pCmdUI);
	afx_msg void OnFileSaveAs();
	afx_msg void OnAutoCorrect();
	afx_msg void OnUpdateAutoCorrect(CCmdUI* pCmdUI);
	afx_msg void OnFreeNums();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CShemeDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
private:
//	void CorrectGroups();
//	bool IsShemeContainsHardRod();
	void GroupClicking( int );
//	int DelFreeKnot();
//	void ClearAllSelectings();
//	void CreateGroupForAllObjects( int type );
//	int GetRealPosInGroup( const ARRAY&, int );
//	int IsGroupContainsNotexistingObject( bool bElem, CShemeGroup& gr, CString& ErrorMsg, ARRAY& vec );
	void PreviewGroup( bool bElem );
//	ARRAY::iterator GetElemIteratorInGroup( const CElem* elem, ARRAY& vec );
//	ARRAY::iterator GetKnotIteratorInGroup( const CKnot* knot, ARRAY& vec );
//	bool IsElemGroupOfOneType( const ARRAY& vec );
//	void ReNumElems();

public:
	CSheme *m_pSheme;
//	bool IsElemContainsInGroup( const CElem* elem, const ARRAY& vec );
//	bool IsKnotContainsInGroup( const CKnot* knot, const ARRAY& vec );
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHEMEDOC_H__09A14A90_BBAC_11D2_AF23_BB2B1C460D22__INCLUDED_)
