#if !defined(AFX_SCRIPTDOC_H__8011A582_4F26_11D6_B89D_FE2BA355A53D__INCLUDED_)
#define AFX_SCRIPTDOC_H__8011A582_4F26_11D6_B89D_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ScriptDoc.h : header file
//
#include "OutputBuffer.h"

class COutputView;
class COutputFrame;
/////////////////////////////////////////////////////////////////////////////
// CScriptDoc document

class CScriptDoc : public CDocument
{
protected:
	CScriptDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CScriptDoc)

// Attributes
public:
	COutputBuffer m_Buf;
	CEvent m_Break;
	CWinThread *m_pOut;
	//флаг, для предотвращения создания нескольких окон вывода:
	//оно всегда одно! (если m_pView!=NULL, то окно уже есть)
	COutputView *m_pView;
	COutputFrame *m_pFrame;
	bool m_bIsExecuting;
// Operations
public:
	void StopThread();
	COutputView* MakeScript( COutputFrame* );
	void RunScript( const CString&, COutputView*, COutputFrame* );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScriptDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual void OnCloseDocument();
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CScriptDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CScriptDoc)
	afx_msg void OnUpdateRunScript(CCmdUI* pCmdUI);
	afx_msg void OnOutputBreak();
	afx_msg void OnUpdateOutputBreak(CCmdUI* pCmdUI);
	afx_msg void OnScriptFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCRIPTDOC_H__8011A582_4F26_11D6_B89D_FE2BA355A53D__INCLUDED_)
