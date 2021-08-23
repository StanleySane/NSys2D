#if !defined(AFX_MOVIEPARAMS_H__429F7D22_5F71_11D6_B89E_FE2BA355A53D__INCLUDED_)
#define AFX_MOVIEPARAMS_H__429F7D22_5F71_11D6_B89E_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MovieParams.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMovieParams dialog

class CMovieParams : public CDialog
{
// Construction
public:
	CMovieParams(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMovieParams)
	enum { IDD = IDD_MOVIE_STYLES };
	UINT	m_uTimerElapse;
	int		m_StartTime;
	BOOL	m_bShowKnots;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMovieParams)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMovieParams)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOVIEPARAMS_H__429F7D22_5F71_11D6_B89E_FE2BA355A53D__INCLUDED_)
