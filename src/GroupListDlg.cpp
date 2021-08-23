// GroupListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "GroupListDlg.h"
#include "GroupEditDlg.h"

#include<string>
#include<algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGroupListDlg dialog


CGroupListDlg::CGroupListDlg( const Groups &vecElGr,
	const Groups &vecKnGr, bool flag, CWnd* pParent /*=NULL*/)
	: CDialog(CGroupListDlg::IDD, pParent), m_arDel(vecElGr.size()+vecKnGr.size()), m_arMod(vecElGr.size()+vecKnGr.size()), m_DlgType(flag)
{
	//{{AFX_DATA_INIT(CGroupListDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_SelDlgItem = 0;
	m_vecElGr = vecElGr;
	m_vecKnGr = vecKnGr;
}


void CGroupListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGroupListDlg)
	DDX_Control(pDX, IDC_GRLIST, m_ListBox);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGroupListDlg, CDialog)
	//{{AFX_MSG_MAP(CGroupListDlg)
	ON_BN_CLICKED(IDC_BUTTON_EDIT_GROUP, OnEditGroup)
	ON_BN_CLICKED(IDC_BUTTON_DEL_GROUP, OnButtonDelGroup)
	ON_BN_CLICKED(IDC_BUTTON_GROUP_SHOW, OnButtonGroupShow)
	ON_BN_CLICKED(IDC_BUTTON_GROUP_SAVE, OnButtonGroupSave)
	ON_LBN_DBLCLK(IDC_GRLIST, OnEditGroup)
	ON_BN_CLICKED(IDC_BUTTON_GROUP_OPEN, OnButtonGroupOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGroupListDlg message handlers

BOOL CGroupListDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	if( m_DlgType == false )
	{
		GetDlgItem(IDC_BUTTON_DEL_GROUP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_EDIT_GROUP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_GROUP_SHOW)->EnableWindow(FALSE);
	}
	// TODO: Add extra initialization here
	int n = m_vecElGr.size();
	for( int i = 0; i < n; i++ )
	{
		if( m_arDel[i] == 1 )	continue;
		CString str, gr;
		(m_vecElGr[i]).GetName( str );
		(m_vecElGr[i]).GetGroup( gr );
		str += _T("<element>(") + gr + _T(")");
		m_ListBox.AddString( str );
	}
	int m = m_vecKnGr.size();
	for( i = 0; i < m; i++ )
	{
		if( m_arDel[i+n] == 1 )	continue;
		CString str, gr;
		(m_vecKnGr[i]).GetName( str );
		(m_vecKnGr[i]).GetGroup( gr );
		str += _T("<knot>(") + gr + _T(")");
		m_ListBox.AddString( str );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGroupListDlg::OnEditGroup() 
{
	// TODO: Add your control notification handler code here
	int sel = m_ListBox.GetCurSel();
	if( m_DlgType == false )
	{
		if( sel != LB_ERR )
			m_SelDlgItem = sel;
		else
			m_SelDlgItem = -1;
		EndDialog( IDOK );
	}
	else
	{
		if( sel == LB_ERR )
		{
			AfxMessageBox( "Не выбрана группа.",
				MB_OK|MB_TASKMODAL|MB_ICONEXCLAMATION );
			return;
		}
		int p = -1, n = m_vecElGr.size()+m_vecKnGr.size();

		for( int i = 0; i < n; i++ )
		{
			if( m_arDel[i] == 1 )	continue;
			p++;
			if( p == sel )	
			{
				p = i;
				break;
			}
		}

		CString group, name;
		int type;
		if( p >= m_vecElGr.size() )
		{
			//выбран узел
			type = 1;
			int m = p - m_vecElGr.size();
			m_vecKnGr[m].GetGroup( group );
			m_vecKnGr[m].GetName( name );
		}
		else
		{
			//элемент
			type = 0;
			m_vecElGr[p].GetGroup( group );
			m_vecElGr[p].GetName( name );
		}

		CShemeGroup gr( group, name, type );
		CGroupEditDlg dlg( &gr );

		if( dlg.DoModal() == IDOK )
		{
			//здесь полагаем, что группа была проверена
			//в dlg и является корректной,
			//поэтому не осуществляем накладных проверок
			CString str;
			str += dlg.m_strGroupName;
			if( p >= m_vecElGr.size() )
			{
				//узел
				int m = p - m_vecElGr.size();
				(m_vecKnGr[m]).SetName( dlg.m_strGroupName );
				(m_vecKnGr[m]).SetGroup( dlg.m_strGroup );
				str += _T("<knot>(");
			}
			else
			{
				//элемент
				(m_vecElGr[p]).SetName( dlg.m_strGroupName );
				(m_vecElGr[p]).SetGroup( dlg.m_strGroup );
				str += _T("<element>(");
			}
			str += dlg.m_strGroup + _T(")");
			m_ListBox.DeleteString( sel );
			m_ListBox.InsertString( sel, str );
			m_arMod[p] = 1;
		}
	}//else
}

void CGroupListDlg::OnButtonDelGroup() 
{
	// TODO: Add your control notification handler code here
	if( m_ListBox.GetCount() == 0 )	return;
	int sel = m_ListBox.GetCurSel();
	if( sel == LB_ERR )
	{
		AfxMessageBox( "Не выбрана группа.",
			MB_OK|MB_TASKMODAL|MB_ICONEXCLAMATION );
		return;
	}

	int n = m_arDel.size(), p = 0;
	
	for( int i = 0; i < n; i++ )
	{
		if( m_arDel[i] == 1 )	continue;
		if( sel == p )	
		{
			p = i;
			break;
		}
		p++;
	}
	m_arDel[p] = 1;

	m_ListBox.DeleteString( sel );
}

void CGroupListDlg::OnOK() 
{
	// TODO: Add extra validation here
	int sel = m_ListBox.GetCurSel();
	if( m_DlgType == false )
	{
		if( sel != LB_ERR )
			m_SelDlgItem = sel;
		else
			m_SelDlgItem = -1;
	}

	CDialog::OnOK();
}

void CGroupListDlg::OnButtonGroupShow() 
{
	// TODO: Add your control notification handler code here
	int sel = m_ListBox.GetCurSel();

	if( sel == LB_ERR )	
	{
		m_SelDlgItem = -1;
		return;
	}
	m_SelDlgItem = sel;

	EndDialog( IDC_BUTTON_GROUP_SHOW );
}

void CGroupListDlg::OnButtonGroupSave() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(FALSE);

	dlg.m_ofn.lpstrTitle = _T("Сохранить группы в текстовый файл");
	CString str;
	str += "ShemeGroups Files (*.txt)"; str += (TCHAR)NULL;
	str += "*.txt"; str += (TCHAR)NULL;
	str += "All Files (*.*)"; str += (TCHAR)NULL;
	str += "*.*"; str += (TCHAR)NULL;
	dlg.m_ofn.lpstrFilter = str;

	dlg.m_ofn.nFilterIndex = 1;
	dlg.m_ofn.lpstrDefExt = _T("txt");
	dlg.m_ofn.Flags |= OFN_OVERWRITEPROMPT;

	while( dlg.DoModal() == IDOK )
	{
		if( dlg.m_ofn.Flags & OFN_EXTENSIONDIFFERENT )
		{
			int ret = AfxMessageBox("Набрано некорректное расширение.\nСохранить с таким расширением?",
								MB_YESNOCANCEL|MB_TASKMODAL|MB_ICONQUESTION);
			if( ret == IDNO )
			{
				continue;
			}
			else	if( ret = IDCANCEL )	return;
		}

		CString strPathName( dlg.GetPathName() );
		try
		{
			CFile F( strPathName, CFile::modeCreate|CFile::modeWrite );
			F.SeekToBegin();
			char signature[_MAX_PATH];
			CString strSig;
			strSig.LoadString( IDS_GROUP_SIGNATURE );
			strSig = _T('[') + strSig + _T(']');
			strcpy( signature, (LPCTSTR)strSig );
			F.Write( (const void*)signature, strlen(signature) );
			strcpy( signature, "\r\xA$Sheme Groups File\r\xA" );
			F.Write( (const void*)signature, strlen(signature) );
			
			int n = m_vecElGr.size(), pos = 0;
			for( int i = 0; i < n; i++ )
			{
				if( m_arDel[pos++] == 0 )
				{
					CString name, group;
					m_vecElGr[i].GetName( name );
					m_vecElGr[i].GetGroup( group );
					CString type = CShemeGroup::GetTypeName( m_vecElGr[i].GetType() );
					type.MakeUpper();
					name += _T('<') + type + _T(">(") + group + _T(")\r\xA");
					char buf[_MAX_PATH];
					strcpy( buf, (LPCTSTR)name );
					F.Write( (const void*)buf, strlen(buf) );
				}
			}
			n = m_vecKnGr.size();
			for( i = 0; i < n; i++ )
			{
				if( m_arDel[pos++] == 0 )
				{
					CString name, group;
					m_vecKnGr[i].GetName( name );
					m_vecKnGr[i].GetGroup( group );
					CString type = CShemeGroup::GetTypeName( m_vecKnGr[i].GetType() );
					type.MakeUpper();
					name += _T('<') + type + _T(">(") + group + _T(")\r\xA");
					char buf[_MAX_PATH];
					strcpy( buf, (LPCTSTR)name );
					F.Write( (const void*)buf, strlen(buf) );
				}
			}
			
			F.Flush();
			F.Close();
		}
		catch( CFileException &fe )
		{
			char mes[_MAX_PATH];
			if( fe.GetErrorMessage( mes,  _MAX_PATH ) )
			{
				AfxMessageBox( mes, MB_OK|MB_TASKMODAL|MB_ICONEXCLAMATION );
			}
			throw;
		}
		break;
	}
}

void CGroupListDlg::OnButtonGroupOpen() 
{
	using namespace std;
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE);

	dlg.m_ofn.lpstrTitle = _T("Загрузить группы из текстового файла");
	CString str;
	str += "ShemeGroups Files (*.txt)"; str += (TCHAR)NULL;
	str += "*.txt"; str += (TCHAR)NULL;
	str += "All Files (*.*)"; str += (TCHAR)NULL;
	str += "*.*"; str += (TCHAR)NULL;
	dlg.m_ofn.lpstrFilter = str;

	dlg.m_ofn.nFilterIndex = 1;

	while( dlg.DoModal() == IDOK )
	{
		CString strPathName( dlg.GetPathName() );
		try
		{
			CFile F( strPathName, CFile::modeRead );
			F.SeekToBegin();
			int len = F.GetLength();
			if( len < 1 )	break;

			char *buf;
			try
			{
				buf = new char[len+1];
			}
			catch( bad_alloc& )
			{
				break;
			}

			len = F.Read( (void*)buf, len );
			F.Close();
			buf[len] = '\0';

			char *p = strchr( buf, '[' );
			int f = -1, l = -1;
			if( p )	f = p - buf + 1;
			p = strchr( buf, ']' );
			if( p )	l = p - buf;

			
			CString str, sig;
			if( (f>0)&&(l>0) )
			{
				for( int i = f; i < l; i++ )
				{
					str += TCHAR(buf[i]);
				}
			}
			sig.LoadString( IDS_GROUP_SIGNATURE );
			if( sig.Compare(str) &&
				(AfxMessageBox( "Возможно файл не содержит групп.\nПрочитать его?",
					MB_YESNO|MB_TASKMODAL|MB_ICONQUESTION ) == IDNO) )
			{
				delete [] buf;
				break;
			}
			string buffer( buf );
			delete [] buf;
			//////////////////////////////////////////////
			buffer.erase( 0, l+3 );
			bool bBadFormat = false, bBadGroup = false, end = false;
			vector<CShemeGroup> vecGr;
			for(;;)
			{
				int pos;
				if( (pos = buffer.find("\r\xA")) == string::npos )
				{
					int len = buffer.length();
					if( len == 0 )	break;
					pos = len;
					end = true;
				}
				string gr;
				gr.assign( buffer, 0, pos );
				if( !end )	buffer.erase( 0, pos+2 );
				else	buffer.erase( 0, pos );
				pos = 0;
				while( gr[pos] == ' ' )	pos++;
				if( pos )	gr.erase( 0, pos );
				// теперь gr должен содержать группу
				if( gr[0] == '$' )
				{
					// это закоментированная строка
					continue;
				}
				if( (pos = gr.find("<")) == string::npos )
				{
					bBadFormat = true;
					break;
				}
				string name;
				name.assign( gr, 0, pos );
				gr.erase( 0, pos+1 );
				if( (pos = gr.find(">")) == string::npos )
				{
					bBadFormat = true;
					break;
				}
				string type;
				type.assign( gr, 0, pos );
				gr.erase( 0, pos+1 );
				if( (pos = gr.find("(")) == string::npos )
				{
					bBadFormat = true;
					break;
				}
				gr.erase( 0, pos+1 );
				if( (pos = gr.find(")")) == string::npos )
				{
					bBadFormat = true;
					break;
				}
				string group;
				group.assign( gr, 0, pos );

				CString strGroup( group.c_str(), group.length() ), 
					strName( name.c_str(), name.length() ), 
					strType( type.c_str(), type.length() );
				int iType = CShemeGroup::WhatType( strType );
				if( iType < 0 )
				{
					bBadFormat = true;
					break;
				}

				CShemeGroup ShGr( strGroup, strName, iType );
				if( !ShGr.Analize() )
				{
					bBadGroup = true;
					ShGr.GetErrorMessage( str );
					break;
				}
				vecGr.push_back( ShGr );
				if( end )	break;
			}// for(;;)
			if( bBadFormat )
			{
				AfxMessageBox( "Некорректный формат файла", MB_OK|MB_TASKMODAL|MB_ICONEXCLAMATION );
				break;
			}
			if( bBadGroup )
			{
				AfxMessageBox( str, MB_OK|MB_TASKMODAL|MB_ICONEXCLAMATION );
				break;
			}
			//////////////////////////////////////////////
			if( m_arDel.size() > 0 )
			{
				ARRAY::iterator it = find( m_arDel.begin(), m_arDel.end(), 0 );
				if( it != m_arDel.end() )
				{
					if( AfxMessageBox("Удалить старые группы?",MB_YESNO|MB_TASKMODAL|MB_ICONQUESTION) == IDYES )
					{
						// ??? удалить старые группы
					}
				}
			}
			// ??? добавить новые группы
		}
		catch( CFileException &fe )
		{
			char mes[_MAX_PATH];
			if( fe.GetErrorMessage( mes,  _MAX_PATH ) )
			{
				AfxMessageBox( mes, MB_OK|MB_TASKMODAL|MB_ICONEXCLAMATION );
			}
			throw;
		}
		break;
	}	
}
