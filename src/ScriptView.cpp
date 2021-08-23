// ScriptView.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "ScriptView.h"

#include"ScriptDoc.h"
#include"OutputView.h"

#include<new>
#include<string>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScriptView

IMPLEMENT_DYNCREATE(CScriptView, CEditView)

CScriptView::CScriptView()
{
}

CScriptView::~CScriptView()
{
}

BOOL CScriptView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
//	cs.style |= ES_AUTOHSCROLL|WS_HSCROLL|WS_VSCROLL|ES_AUTOVSCROLL|ES_MULTILINE;
	return CEditView::PreCreateWindow(cs);
}

BEGIN_MESSAGE_MAP(CScriptView, CEditView)
	//{{AFX_MSG_MAP(CScriptView)
	ON_WM_CREATE()
	ON_COMMAND(ID_RUN_SCRIPT, OnRunScript)
//	ON_COMMAND(ID_SCRIPT_FILE_SAVE_AS, OnScriptFileSaveAs)
	ON_COMMAND(ID_SCRIPT_FILE_OPEN, OnScriptFileOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptView diagnostics

#ifdef _DEBUG
void CScriptView::AssertValid() const
{
	CEditView::AssertValid();
}

void CScriptView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CScriptDoc* CScriptView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScriptDoc)));
	return (CScriptDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScriptView message handlers

int CScriptView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEditView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	/*
	CHARFORMAT cf;
	memset(&cf, 0, sizeof(CHARFORMAT));
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = CFM_BOLD|CFM_ITALIC|CFM_UNDERLINE|CFM_STRIKEOUT|
				CFM_PROTECTED|CFM_LINK|CFM_SIZE|CFM_COLOR|CFM_FACE|
				CFM_OFFSET|CFM_CHARSET;
	cf.yHeight = 200;
	cf.bCharSet = ANSI_CHARSET;
	cf.bPitchAndFamily = FIXED_PITCH|FF_ROMAN;
	strcpy( cf.szFaceName, "Courier");

	SetCharFormat(cf);
	BOOL res = GetRichEditCtrl().SetDefaultCharFormat(cf);
	ASSERT(res!=FALSE);
	*/
	SetTabStops(8);
	return 0;
}

void CScriptView::OnRunScript() 
{
	// TODO: Add your command handler code here
	CScriptDoc* pDoc = (CScriptDoc*)GetDocument();
	ASSERT_VALID(pDoc);

	CString str( LockBuffer() );
	UnlockBuffer();
	COutputFrame *pFrame = NULL;
	COutputView *pView = pDoc->MakeScript(pFrame);
	if( pView )
		pDoc->RunScript( str, pView, pFrame );
}

/*
void CScriptView::OnScriptFileSaveAs() 
{
	// TODO: Add your command handler code here
	CScriptDoc* pDoc = (CScriptDoc*)GetDocument();
	ASSERT_VALID(pDoc);

	CFileDialog dlg(FALSE);

	dlg.m_ofn.lpstrTitle = _T("Сохранить скрипт как...");
	CString str;
	str += "Script Files (*.scr)"; str += (TCHAR)NULL;
	str += "*.scr"; str += (TCHAR)NULL;
	str += "All Files (*.*)"; str += (TCHAR)NULL;
	str += "*.*"; str += (TCHAR)NULL;
	char Filter[256];
	int size = str.GetLength(), pos = 0;
	for( int i = 0; i < size; ++i )
	{
		if( i >= 256 )
		{
			pos = 256-2;
			break;
		}
		Filter[i] = str[i];
		pos = i;
	}
	Filter[pos+1] = '\0';
	dlg.m_ofn.lpstrFilter = Filter;

	dlg.m_ofn.nFilterIndex = 1;
	dlg.m_ofn.lpstrDefExt = _T("scr");
	dlg.m_ofn.Flags |= OFN_OVERWRITEPROMPT;

	CString strName = pDoc->GetTitle();
	char FileName[80];
	size = strName.GetLength();
	pos = 0;
	for( i = 0; i < size; ++i )
	{
		if( i >= 80 )
		{
			pos = 78;
			break;
		}
		FileName[i] = strName[i];
		pos = i;
	}
	FileName[pos+1] = '\0';
	dlg.m_ofn.lpstrFile = FileName;

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
			F.Write( LockBuffer(), GetBufferLength() );
			UnlockBuffer();
			pDoc->SetTitle( dlg.GetFileName() );
			F.Flush();
			F.Close();
		}
		catch( CFileException& )
		{
			AfxMessageBox("CFileException !!!");
			return;
		}

		pDoc->SetModifiedFlag(FALSE);
		pDoc->SetPathName( strPathName );
		break;
	}	
}
*/

void CScriptView::OnScriptFileOpen() 
{
	// TODO: Add your command handler code here
	CScriptDoc* pDoc = (CScriptDoc*)GetDocument();
	ASSERT_VALID(pDoc);

	CFileDialog dlg(TRUE);
	CString strName = pDoc->GetTitle();

	dlg.m_ofn.lpstrTitle = _T("Окрыть скрипт");
	CString str;
	str += "Script Files (*.scr)"; str += (TCHAR)NULL;
	str += "*.scr"; str += (TCHAR)NULL;
	str += "All Files (*.*)"; str += (TCHAR)NULL;
	str += "*.*"; str += (TCHAR)NULL;

	dlg.m_ofn.lpstrFilter = static_cast<LPCTSTR>(str);

	dlg.m_ofn.nFilterIndex = 1;
	dlg.m_ofn.lpstrDefExt = _T("scr");
	dlg.m_ofn.Flags |= OFN_OVERWRITEPROMPT;

	const int N = 80;
	char FileName[N];
	strncpy( FileName, strName.LockBuffer(), N );
	strName.UnlockBuffer();
	dlg.m_ofn.lpstrFile = FileName;
	dlg.m_ofn.nMaxFile = N;

	while( dlg.DoModal() == IDOK )
	{
		CString strPathName( dlg.GetPathName() );
		FILE *f;
		if( (f = fopen(strPathName.LockBuffer(), "rb")) == NULL )
		{
			strPathName.UnlockBuffer();
			AfxMessageBox("Не могу открыть файл");
			return;
		}
		strPathName.UnlockBuffer();
		int ch;
		string text;
		for( ch = getc(f); !feof(f); ch = getc(f) )
		{
			text += ch;
		}
		fclose(f);

		GetEditCtrl().SetWindowText( text.c_str() );
		pDoc->SetTitle( dlg.GetFileName() );
		pDoc->SetModifiedFlag(FALSE);
		pDoc->SetPathName( strPathName );
		break;
	}		
}

void CScriptView::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
	CScriptDoc* pDoc = (CScriptDoc*)GetDocument();
	ASSERT_VALID(pDoc);
		
}
