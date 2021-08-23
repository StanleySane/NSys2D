// FreqViewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "FreqViewDlg.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFreqViewDlg dialog


CFreqViewDlg::CFreqViewDlg(CMatr &f, CWnd* pParent /*=NULL*/)
	: CDialog(CFreqViewDlg::IDD, pParent)
{
	F.ReSize(f.SizeY,1);
	for (int i=0;i<f.SizeY;i++)
	{
		double a=f[i][i];
		if (a>0)	F[i][0]=sqrt(a);
		else F[i][0]=0;
	}
	//{{AFX_DATA_INIT(CFreqViewDlg)
	//}}AFX_DATA_INIT
}


void CFreqViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFreqViewDlg)
	DDX_Control(pDX, IDC_LIST1, m_ListFreq);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFreqViewDlg, CDialog)
	//{{AFX_MSG_MAP(CFreqViewDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFreqViewDlg message handlers

BOOL CFreqViewDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ListFreq.ResetContent();
	for (int i=0;i<F.SizeY;i++)
	{
		CString str;
		str.Format("%lf",F[i][0]);
		m_ListFreq.AddString(str);
	}
	m_ListFreq.SetCurSel(0);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
