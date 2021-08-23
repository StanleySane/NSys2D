// KnotPropertyPage1.h : header file
//

#ifndef __KNOTPROPERTYPAGE1_H__
#define __KNOTPROPERTYPAGE1_H__

#include "ComboBox_FixedType.h"
#include "Knot.h"

#include "ListKnot.h"
#include "ListSpectr.h"
/////////////////////////////////////////////////////////////////////////////
// CKnotPropertyPage1 dialog

class CKnotPropertyPage1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CKnotPropertyPage1)

// Construction
public:
	void SetData();
	BOOL VerifyInfo();
	CKnotPropertyPage1();
	~CKnotPropertyPage1();
	CKnot *pKnot;
// Dialog Data
	//{{AFX_DATA(CKnotPropertyPage1)
	enum { IDD = IDD_KNOTPAGE1 };
	CComboBox_FixedType	m_FixedType;
	CString	m_EditX;
	CString	m_EditY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CKnotPropertyPage1)
	public:
	virtual void OnOK();
	virtual BOOL OnKillActive();
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CKnotPropertyPage1)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEdit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
// CKnotPropertyPage2 dialog

class CKnotPropertyPage2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CKnotPropertyPage2)

// Construction
public:
	void SetData();
	BOOL VerifyInfo();
	CKnotPropertyPage2();
	~CKnotPropertyPage2();
	CKnot *pKnot;
// Dialog Data
	//{{AFX_DATA(CKnotPropertyPage2)
	enum { IDD = IDD_KNOTPAGE2 };
	CString	m_EditUx;
	CString	m_EditUy;
	CString	m_EditUa;
	CString	m_EditUxp;
	CString	m_EditUyp;
	CString	m_EditUap;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CKnotPropertyPage2)
	public:
	virtual void OnOK();
	virtual BOOL OnKillActive();
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CKnotPropertyPage2)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEdit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};



#endif // __KNOTPROPERTYPAGE1_H__
/////////////////////////////////////////////////////////////////////////////
// CKnotPropertyPage3 dialog

class CKnotPropertyPage3 : public CPropertyPage
{
	DECLARE_DYNCREATE(CKnotPropertyPage3)

// Construction
public:
	void SetData();
	BOOL VerifyInfo();
	void SetState();
	CKnot *pKnot;
	CKnotPropertyPage3();
	~CKnotPropertyPage3();

	CListKnot *pListKnot;
	CListSpectr *pListSpectr;

// Dialog Data
	//{{AFX_DATA(CKnotPropertyPage3)
	enum { IDD = IDD_KNOTPAGE3 };
	CButton	m_CheckViewPy;
	CButton	m_CheckViewPx;
	CButton	m_ButCPy;
	CButton	m_ButCPx;
	CButton	m_RadPy3;
	CButton	m_RadPy2;
	CButton	m_RadPy1;
	CButton	m_RadPx3;
	CButton	m_RadPx2;
	CButton	m_RadPx1;
	CButton	m_ButPy;
	CButton	m_ButPx;
	CEdit	m_EditFiy;
	CEdit	m_EditWy;
	CEdit	m_EditAy;
	CEdit	m_EditPy;
	CEdit	m_EditPx;
	CEdit	m_EditFix;
	CEdit	m_EditWx;
	CEdit	m_EditAx;
	BOOL	m_CheckPx;
	BOOL	m_CheckPy;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CKnotPropertyPage3)
	public:
	virtual void OnOK();
	virtual BOOL OnKillActive();
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CKnotPropertyPage3)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	afx_msg void OnCheckPx();
	afx_msg void OnCheckPy();
	afx_msg void OnSpectrpx();
	afx_msg void OnRadio5();
	afx_msg void OnRadio6();
	afx_msg void OnSpectrpy();
	afx_msg void OnCspecpx();
	afx_msg void OnCspecpy();
	afx_msg void OnChangeEdit();
	afx_msg void OnDoubleclickedCheck3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
/////////////////////////////////////////////////////////////////////////////
// CKnotPropertyPage4 dialog

class CKnotPropertyPage4 : public CPropertyPage
{
	DECLARE_DYNCREATE(CKnotPropertyPage4)

// Construction
public:
	void SetData();
	CKnot *pKnot;

	CKnotPropertyPage4();
	~CKnotPropertyPage4();

	BOOL VerifyInfo();
	void SetState();

	CListKnot *pListKnot;
	CListSpectr *pListSpectr;
// Dialog Data
	//{{AFX_DATA(CKnotPropertyPage4)
	enum { IDD = IDD_KNOTPAGE4 };
	CButton	m_ButCUy;
	CButton	m_ButCUx;
	CButton	m_CheckViewUy;
	CButton	m_CheckViewUx;
	CButton	m_RadUy3;
	CButton	m_RadUx3;
	CButton	m_ButUy;
	CButton	m_ButUx;
	CEdit	m_EditUy;
	CEdit	m_EditFiy;
	CEdit	m_EditWy;
	CEdit	m_EditAy;
	CEdit	m_EditUx;
	CEdit	m_EditFix;
	CEdit	m_EditWx;
	CEdit	m_EditAx;
	CButton	m_RadUy2;
	CButton	m_RadUy1;
	CButton	m_RadUx2;
	CButton	m_RadUx1;
	BOOL	m_CheckUx;
	BOOL	m_CheckUy;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CKnotPropertyPage4)
	public:
	virtual void OnOK();
	virtual BOOL OnKillActive();
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CKnotPropertyPage4)
	afx_msg void OnCheckUx();
	afx_msg void OnCheckUy();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	virtual BOOL OnInitDialog();
	afx_msg void OnRadio5();
	afx_msg void OnRadio6();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnChangeEdit();
	afx_msg void OnCspecux();
	afx_msg void OnCspecuy();
	afx_msg void OnDoubleclickedCheck3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
