#if !defined(AFX_MESHELEMDLG_H__6466A0E2_7BA7_11D5_B89C_FE2BA355A53D__INCLUDED_)
#define AFX_MESHELEMDLG_H__6466A0E2_7BA7_11D5_B89C_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MeshElemDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMeshElemDlg dialog

class CMeshElemDlg : public CDialog
{
// Construction
public:
	CMeshElemDlg( int elemType, CWnd* pParent = NULL);   // standard constructor

	void SetState();
	void SetData();

	int m_ElemType;
// Dialog Data
	//{{AFX_DATA(CMeshElemDlg)
	enum { IDD = IDD_DIALOG_MESH_ELEM };
	int		m_iElemsCount;
	int		m_iWay;
	CString	m_strLeftKnot;
	CString	m_strRightKnot;
	int		m_iLeftProc;
	int		m_iRightProc;
	double	m_dLeftLength;
	double	m_dRightLength;
	double	m_dLength;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMeshElemDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMeshElemDlg)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnChangeEditLeftLength();
	afx_msg void OnChangeEditRightLength();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESHELEMDLG_H__6466A0E2_7BA7_11D5_B89C_FE2BA355A53D__INCLUDED_)
