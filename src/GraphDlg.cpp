// GraphDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "GraphDlg.h"

#include<fstream>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphDlg dialog


CGraphDlg::CGraphDlg( CGraphData *pGr, CWnd* pParent /*=NULL*/)
	: CDialog(CGraphDlg::IDD, pParent), m_pGraphData(pGr)
{
	m_GraphData = (*m_pGraphData);
	//{{AFX_DATA_INIT(CGraphDlg)
	m_strCaption = _T("");
	m_strFileName = _T("");
	m_Scale = 0.0;
	//}}AFX_DATA_INIT
}


void CGraphDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGraphDlg)
	DDX_Text(pDX, IDC_CAPTION, m_strCaption);
	DDV_MaxChars(pDX, m_strCaption, 80);
	DDX_Text(pDX, IDC_GRAPH_FILE_NAME, m_strFileName);
	DDX_Text(pDX, IDC_GRAPH_SCALE, m_Scale);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGraphDlg, CDialog)
	//{{AFX_MSG_MAP(CGraphDlg)
	ON_BN_CLICKED(IDC_EDIT_GRAPH_COLOR, OnEditGraphColor)
	ON_BN_CLICKED(IDC_GRAPH_LOAD, OnGraphLoad)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphDlg message handlers


void CGraphDlg::OnEditGraphColor() 
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg( m_GraphData.m_Clr );
	if( dlg.DoModal() == IDOK )
	{
		m_GraphData.m_Clr = dlg.GetColor();
		m_Color.m_Clr = m_GraphData.m_Clr;
		m_Color.Invalidate();
	}
}

void CGraphDlg::OnGraphLoad() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE);

	dlg.m_ofn.lpstrTitle = _T("Загрузить дополнительный график из...");

	CString str;
	str += "Файлы данных (*.rez)"; str += (TCHAR)NULL;
	str += "*.rez"; str += (TCHAR)NULL;
	str += "Файлы данных короткого формата (*.rez)"; str += (TCHAR)NULL;
	str += "*.rez"; str += (TCHAR)NULL;
	str += "All Files (*.*)"; str += (TCHAR)NULL;
	str += "*.*"; str += (TCHAR)NULL;

	dlg.m_ofn.lpstrFilter = static_cast<LPCTSTR>(str);

	dlg.m_ofn.nFilterIndex = 1;
	dlg.m_ofn.lpstrDefExt = _T("rez");

	if( dlg.DoModal() == IDOK )
	{
		if( dlg.m_ofn.nFilterIndex == 2 )
		{
			//короткий формат. оставлен для поддержки старого формата.
			fstream fin( dlg.GetPathName(), ios::in );
			if( !fin )
				return;
			//Считаем размер данных
			double tmp; 
			int cnt = 0;
			while( !fin.eof() )
			{
				fin >> tmp >> tmp;
				cnt++;
			}
			if( cnt < 2 )
				return;
			if( !m_GraphData.m_Data.ReSize( 2, cnt-1 ) )
				return;
			fin.close();
			//читаем данные
			fin.open( dlg.GetPathName(), ios::in );
			for( int i = 0; i < m_GraphData.m_Data.SizeX; i++ )
			{
				fin >> tmp;
				m_GraphData.m_Data(0,i) = tmp;
				fin >> tmp;
				m_GraphData.m_Data(1,i) = tmp;
			}
			fin.close();
		}
		else
		{
			fstream fin( dlg.GetPathName(), ios::in );
			if( !fin )
				return;
			//Считаем размер данных
			int cnt = 0;
			fin >> cnt;
			if( cnt < 2 )
				return;
			if( !m_GraphData.m_Data.ReSize( 2, cnt ) )
				return;
			//читаем данные
			for( int i = 0; i < m_GraphData.m_Data.SizeX; i++ )
			{
				double tmp;
				fin >> tmp;
				m_GraphData.m_Data(0,i) = tmp;
				fin >> tmp;
				m_GraphData.m_Data(1,i) = tmp;
			}
			fin.close();
		}
		m_strFileName = dlg.GetPathName();
		UpdateData(FALSE);
	}
}

void CGraphDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();

	if( m_strCaption.IsEmpty() )
	{
		AfxMessageBox("Задайте название графика");
		GetDlgItem(IDC_CAPTION)->SetFocus();
		return;
	}
	m_pGraphData->m_Clr = m_GraphData.m_Clr;
	m_pGraphData->m_strCaption = m_strCaption;
	m_pGraphData->m_strFileName = m_strFileName;
	m_pGraphData->m_Scale = m_Scale;
	m_pGraphData->m_Data = m_GraphData.m_Data;

	CDialog::OnOK();
}

BOOL CGraphDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	VERIFY( m_Color.SubclassDlgItem( IDC_GRAPH_COLOR, this ) );
	m_Color.m_Clr = m_GraphData.m_Clr;

	m_strCaption = m_GraphData.m_strCaption;
	m_strFileName = m_GraphData.m_strFileName;
	m_Scale = m_GraphData.m_Scale;

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
