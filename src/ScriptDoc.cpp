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

CScriptDoc::CScriptDoc()
{
	m_bIsView = m_bIsExecuting = false;
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
	ON_UPDATE_COMMAND_UI(ID_COMPILE_SCRIPT, OnUpdateCompileScript)
	ON_UPDATE_COMMAND_UI(ID_RUN_SCRIPT, OnUpdateRunScript)
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
COutputView* CScriptDoc::MakeScript()
{
	if( m_bIsView )
		return NULL;
	m_bIsView = true;

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
	
	/*
	CRect rect;
	pos = GetFirstViewPosition();
	CView *pView = GetNextView(pos);
	pView->GetOwner()->GetWindowRect(&rect);
	rect.OffsetRect(rect.Width()/2,0);
	if( rect.Width() < 325 ) 
		rect.right = rect.left + 325;
	rect.bottom += 100;
	pNewFrame->MoveWindow(&rect);
	*/
	
	pTemplate->InitialUpdateFrame( pNewFrame, this );

	COutputView *pOutputView = static_cast<COutputView*>(pNewFrame->GetActiveView());
	ASSERT(pOutputView);
	pNewFrame->SetWindowText(str);

	return pOutputView;
}

void CScriptDoc::RunScript( const CString &text, COutputView *pView )
{
	ASSERT(pView);
	pView->Run(text);
}

void CScriptDoc::OnUpdateCompileScript(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( !m_bIsExecuting );
}

void CScriptDoc::OnUpdateRunScript(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( !m_bIsExecuting );	
}
