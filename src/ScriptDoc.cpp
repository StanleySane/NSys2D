// ScriptDoc.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "ScriptDoc.h"

#include "OutputFrame.h"
#include "OutputView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScriptDoc

IMPLEMENT_DYNCREATE(CScriptDoc, CDocument)

CScriptDoc::CScriptDoc():
m_pOut(NULL), m_Break(FALSE,TRUE)
{
	m_pView = NULL;
	m_pFrame = NULL;
	m_bIsExecuting = false;
}

BOOL CScriptDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CScriptDoc::~CScriptDoc()
{
}


BEGIN_MESSAGE_MAP(CScriptDoc, CDocument)
	//{{AFX_MSG_MAP(CScriptDoc)
	ON_UPDATE_COMMAND_UI(ID_RUN_SCRIPT, OnUpdateRunScript)
	ON_COMMAND(ID_OUTPUT_BREAK, OnOutputBreak)
	ON_UPDATE_COMMAND_UI(ID_OUTPUT_BREAK, OnUpdateOutputBreak)
	ON_COMMAND(ID_SCRIPT_FILE_OPEN, OnScriptFileOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptDoc diagnostics

#ifdef _DEBUG
void CScriptDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CScriptDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScriptDoc serialization

void CScriptDoc::Serialize(CArchive& ar)
{
	if( ar.IsStoring() )
	{
		// TODO: add storing code here
		POSITION pos = GetFirstViewPosition();
		CEditView *pView = static_cast<CEditView*>(GetNextView( pos ));
		CString text = pView->LockBuffer();
		pView->UnlockBuffer();
		int s = text.GetLength();
		for( int i = 0; i < s; i++ )
			ar << text[i];
	}
	else
	{
		// TODO: add loading code here
		CString str;
		int s = ar.GetFile()->GetLength();
		char tmp;
		for( int i = 0; i < s; i++ )
		{
			ar >> tmp;
			str += tmp;
		}
		POSITION pos = GetFirstViewPosition();
		CEditView *pView = static_cast<CEditView*>(GetNextView( pos ));
		pView->GetEditCtrl().SetWindowText( str.LockBuffer() );
		str.UnlockBuffer();
	}
}

/////////////////////////////////////////////////////////////////////////////
// CScriptDoc commands
COutputView* CScriptDoc::MakeScript( COutputFrame *pFrame )
{
	if( m_pView != NULL )
	{
		ASSERT( m_pOut == NULL );
		m_pView->GetEditCtrl().SetWindowText("");
		pFrame = m_pFrame;
		return m_pView;
	}

	CString str;
	str = GetTitle();

	str = _T("Результат выполнения скрипта <") + str;
	str += _T(">");

	CNSys2DApp *pApp = static_cast<CNSys2DApp*>(AfxGetApp());

	POSITION pos = pApp->GetFirstDocTemplatePosition();
	pApp->GetNextDocTemplate(pos);
	pApp->GetNextDocTemplate(pos);
	pApp->GetNextDocTemplate(pos);
	pApp->GetNextDocTemplate(pos);
	CDocTemplate *pTemplate = pApp->GetNextDocTemplate(pos);

	//CMDIChildWnd* 
	COutputFrame *pNewFrame	= static_cast<COutputFrame*>(pTemplate->CreateNewFrame(this, NULL));
	ASSERT(pNewFrame);
	
	pTemplate->InitialUpdateFrame( pNewFrame, this );

	//COutputView *pOutputView = static_cast<COutputView*>(pNewFrame->GetActiveView());
	m_pView = static_cast<COutputView*>(pNewFrame->GetActiveView());
	ASSERT(m_pView);
	pNewFrame->SetWindowText(str);
	pFrame = pNewFrame;
	m_pFrame = pNewFrame;

	return m_pView;
}

void CScriptDoc::RunScript( const CString &text, COutputView *pView,  COutputFrame *pFrame )
{
	ASSERT(pView);
	m_Break.ResetEvent();
	pView->Run( text, pFrame );
}

void CScriptDoc::OnUpdateRunScript(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( !m_bIsExecuting );	
}

void CScriptDoc::StopThread()
{
	m_Break.SetEvent();
	if( m_pOut )
	{
		WaitForSingleObject( m_pOut->m_hThread, INFINITE );
		delete m_pOut;
		m_pOut = NULL;
	}
	m_Break.ResetEvent();
	m_bIsExecuting = false;
	ASSERT( m_pFrame );
	m_pFrame->GetSystemMenu(FALSE)->EnableMenuItem(SC_CLOSE, MF_BYCOMMAND|MF_ENABLED );
	AfxGetMainWnd()->GetSystemMenu(FALSE)->EnableMenuItem(SC_CLOSE, MF_BYCOMMAND|MF_ENABLED );
}

void CScriptDoc::OnOutputBreak() 
{
	// TODO: Add your command handler code here
	m_Break.SetEvent();	
}

void CScriptDoc::OnUpdateOutputBreak(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( m_pOut != NULL );
}

void CScriptDoc::OnCloseDocument() 
{
	// TODO: Add your specialized code here and/or call the base class
	if( m_pOut )
	{
		AfxMessageBox("Сначала прервите выполнение скрипта!");
		return;
	}
	if( m_pOut )
		::TerminateThread( m_pOut->m_hThread, 0 );
	CDocument::OnCloseDocument();
}


void CScriptDoc::OnScriptFileOpen() 
{
	// TODO: Add your command handler code here
	CFileDialog dlg(TRUE);

	dlg.m_ofn.lpstrTitle = _T("Загрузить текст скрипта");

	CString strName = GetTitle();
	CString str;
	str += "Script Files (*.scr)"; str += (TCHAR)NULL;
	str += "*.scr"; str += (TCHAR)NULL;
	str += "All Files (*.*)"; str += (TCHAR)NULL;
	str += "*.*"; str += (TCHAR)NULL;

	dlg.m_ofn.lpstrFilter = static_cast<LPCTSTR>(str);

	dlg.m_ofn.nFilterIndex = 1;
	dlg.m_ofn.lpstrDefExt = _T("scr");
//	dlg.m_ofn.Flags |= OFN_OVERWRITEPROMPT;

/*	const int N = 80;
	char FileName[N];
	strncpy( FileName, strName.LockBuffer(), N );
	strName.UnlockBuffer();
	dlg.m_ofn.lpstrFile = FileName;
	dlg.m_ofn.nMaxFile = N;
*/

	if( dlg.DoModal() == IDOK )
	{
		try
		{
			CString strPathName( dlg.GetPathName() );
			CFile F( strPathName, CFile::modeRead );
			CArchive ar( &F, CArchive::load );
		
			Serialize( ar );
			SetTitle( dlg.GetFileName() );
			SetModifiedFlag(FALSE);
			SetPathName( strPathName );
		}
		catch( CException &ex )
		{
			ex.ReportError();
			return;
		}
	}	
}
