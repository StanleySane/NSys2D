#if !defined(AFX_SCRIPTDOC_H__8011A582_4F26_11D6_B89D_FE2BA355A53D__INCLUDED_)
#define AFX_SCRIPTDOC_H__8011A582_4F26_11D6_B89D_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ScriptDoc.h : header file
//

class COutputView;
/////////////////////////////////////////////////////////////////////////////
// CScriptDoc document

class CScriptDoc : public CDocument
{
protected:
	CScriptDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CScriptDoc)

// Attributes
public:
	//флаг, для предотвращения создания нескольких окон вывода:
	//оно всегда одно!
	bool m_bIsView;
	bool m_bIsExecuting;
// Operations
public:
	COutputView* MakeScript();
	void RunScript( const CString&, COutputView* );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScriptDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
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
	afx_msg void OnUpdateCompileScript(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRunScript(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCRIPTDOC_H__8011A582_4F26_11D6_B89D_FE2BA355A53D__INCLUDED_)
