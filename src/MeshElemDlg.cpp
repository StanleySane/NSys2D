// MeshElemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "MeshElemDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMeshElemDlg dialog


CMeshElemDlg::CMeshElemDlg( int elemType, CWnd* pParent /*=NULL*/)
	: CDialog(CMeshElemDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMeshElemDlg)
	m_iElemsCount = 2;
	m_iWay = 0;
	m_strLeftKnot = _T("");
	m_strRightKnot = _T("");
	m_iLeftProc = 1;
	m_iRightProc = 99;
	m_dLeftLength = 0.0;
	m_dRightLength = 0.0;
	m_dLength = 0.0;
	//}}AFX_DATA_INIT
	m_ElemType = elemType;
	if( elemType == IDC_HARDROD )	m_iWay = 1;
}


void CMeshElemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMeshElemDlg)
	DDX_Text(pDX, IDC_EDIT_ELEMS_COUNT, m_iElemsCount);
	DDV_MinMaxInt(pDX, m_iElemsCount, 2, 100);
	DDX_Radio(pDX, IDC_RADIO1, m_iWay);
	DDX_Text(pDX, IDC_EDIT_LEFT_KNOT, m_strLeftKnot);
	DDV_MaxChars(pDX, m_strLeftKnot, 80);
	DDX_Text(pDX, IDC_EDIT_RIGHT_KNOT, m_strRightKnot);
	DDV_MaxChars(pDX, m_strRightKnot, 80);
	DDX_Text(pDX, IDC_EDIT_LEFT_PROC, m_iLeftProc);
	DDV_MinMaxInt(pDX, m_iLeftProc, 0, 100);
	DDX_Text(pDX, IDC_EDIT_RIGHT_PROC, m_iRightProc);
	DDV_MinMaxInt(pDX, m_iRightProc, 0, 100);
	DDX_Text(pDX, IDC_EDIT_LEFT_LENGTH, m_dLeftLength);
	DDV_MinMaxDouble(pDX, m_dLeftLength, 0., 10000.);
	DDX_Text(pDX, IDC_EDIT_RIGHT_LENGTH, m_dRightLength);
	DDV_MinMaxDouble(pDX, m_dRightLength, 0., 10000.);
	DDX_Text(pDX, IDC_EDIT_LENGTH, m_dLength);
	DDV_MinMaxDouble(pDX, m_dLength, 0., 10000.);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMeshElemDlg, CDialog)
	//{{AFX_MSG_MAP(CMeshElemDlg)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_EN_CHANGE(IDC_EDIT_LEFT_LENGTH, OnChangeEditLeftLength)
	ON_EN_CHANGE(IDC_EDIT_RIGHT_LENGTH, OnChangeEditRightLength)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMeshElemDlg message handlers

void CMeshElemDlg::SetState()
{
	UpdateData();

	GetDlgItem(IDC_EDIT_ELEMS_COUNT)->EnableWindow(m_iWay==0);

	GetDlgItem(IDC_EDIT_LEFT_PROC)->EnableWindow(m_iWay==1);
	GetDlgItem(IDC_EDIT_RIGHT_PROC)->EnableWindow(m_iWay==1);
	GetDlgItem(IDC_EDIT_LEFT_LENGTH)->EnableWindow(m_iWay==1);
	GetDlgItem(IDC_EDIT_RIGHT_LENGTH)->EnableWindow(m_iWay==1);
	GetDlgItem(IDC_SLIDER1)->EnableWindow(m_iWay==1);
}

void CMeshElemDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default

	if( pScrollBar->GetDlgCtrlID() == IDC_SLIDER1 )
	{
		m_iLeftProc = ((CSliderCtrl*)pScrollBar)->GetPos();
		SetData();
	}
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

BOOL CMeshElemDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	GetDlgItem(IDC_RADIO1)->EnableWindow( m_ElemType == IDC_ROD );

	((CSliderCtrl*)GetDlgItem(IDC_SLIDER1))->SetRange( 0, 100 );
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER1))->SetPos( 1 );
	m_dLeftLength = m_dLength*0.01;
	m_dRightLength = m_dLength*0.99;
	m_iLeftProc = 1;
	m_iRightProc = 99;

	SetState();
	SetData();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMeshElemDlg::SetData()
{
	UpdateData();

	m_iLeftProc = ((CSliderCtrl*)GetDlgItem(IDC_SLIDER1))->GetPos();
	m_iRightProc = 100 - m_iLeftProc;
	m_dLeftLength = m_dLength*m_iLeftProc/100;
	m_dRightLength = m_dLength*m_iRightProc/100;

	UpdateData(FALSE);
}

void CMeshElemDlg::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	SetState();	
}

void CMeshElemDlg::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	SetState();
}

void CMeshElemDlg::OnChangeEditLeftLength() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();

	if( (m_dLeftLength<0.0)||(m_dLeftLength>m_dLength) )	return;

	m_iLeftProc = static_cast<int>(m_dLeftLength/(m_dLength*0.01));
	m_iRightProc = 100 - m_iLeftProc;
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER1))->SetPos(m_iLeftProc);
	m_dRightLength = m_dLength - m_dLeftLength;

	UpdateData(FALSE);	
}

void CMeshElemDlg::OnChangeEditRightLength() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();

	if( (m_dRightLength<0.0)||(m_dRightLength>m_dLength) )	return;

	m_iRightProc = static_cast<int>(m_dRightLength/(m_dLength*0.01));
	m_iLeftProc = 100 - m_iRightProc;
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER1))->SetPos(m_iLeftProc);
	m_dLeftLength = m_dLength - m_dRightLength;

	UpdateData(FALSE);		
}
