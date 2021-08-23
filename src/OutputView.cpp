// OutputView.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "OutputView.h"

#include "ScriptDoc.h"
#include "ScriptHeader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

UINT RunScriptThread( LPVOID lParam )
{
	COutputView *pView = static_cast<COutputView*>(lParam);
	ASSERT( pView->IsKindOf(RUNTIME_CLASS(COutputView)) );
	
	CScript scr;
	scr.Set( pView );
	scr.SetDebug( false );
	scr.Run();
	//if( scr.FatalCrash() )	return -1;
	pView->StopThread();
	return 0;
}

UINT OutputThread( LPVOID lParam )
{
	COutputView *pView = static_cast<COutputView*>(lParam);
	ASSERT( pView->IsKindOf(RUNTIME_CLASS(COutputView)) );
	
	CSyncObject *pObj[] = 
	{	&pView->m_Break, &pView->m_Buf.m_NotFree };
	for(;;)
	{
		CMultiLock Lock( pObj, 2 );
		switch( Lock.Lock( INFINITE, FALSE ) )
		{
		case WAIT_OBJECT_0:
			pView->Show( pView->m_Buf.ReadOut() );
			return 0;
			break;
		case (WAIT_OBJECT_0+1):
			pView->Show( pView->m_Buf.ReadOut() );
			break;
		default:
			return -1;
		}
	}
	return 0;
}
/////////////////////////////////////////////////////////////////////////////
// COutputView

IMPLEMENT_DYNCREATE(COutputView, CEditView)

COutputView::COutputView():
m_pOut(NULL), m_Break(FALSE,TRUE), m_pIsExecuting(NULL)
{
}

COutputView::~COutputView()
{
}


BEGIN_MESSAGE_MAP(COutputView, CEditView)
	//{{AFX_MSG_MAP(COutputView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_OUTPUT_FILE_SAVE, OnOutputFileSave)
	ON_COMMAND(ID_OUTPUT_BREAK, OnOutputBreak)
	ON_UPDATE_COMMAND_UI(ID_OUTPUT_BREAK, OnUpdateOutputBreak)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutputView drawing

void COutputView::OnDraw(CDC* pDC)
{
//	CScriptDoc* pDoc = (CScriptDoc*)GetDocument();
//	ASSERT_VALID(pDoc);
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// COutputView diagnostics

#ifdef _DEBUG
void COutputView::AssertValid() const
{
	CEditView::AssertValid();
}

void COutputView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CScriptDoc* COutputView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScriptDoc)));
	return (CScriptDoc*)m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COutputView message handlers

int COutputView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEditView::OnCreate(lpCreateStruct) == -1)
	{
		CScriptDoc* pDoc = (CScriptDoc*)GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->m_bIsView = false;
		return -1;
	}
	// TODO: Add your specialized creation code here	
	CScriptDoc* pDoc = (CScriptDoc*)GetDocument();
	ASSERT_VALID(pDoc);
	m_pIsExecuting = &pDoc->m_bIsExecuting;

	return 0;
}

void COutputView::OnDestroy() 
{
	CEditView::OnDestroy();
	
	// TODO: Add your message handler code here
	CScriptDoc* pDoc = (CScriptDoc*)GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_bIsView = false;

	StopThread();
}

void COutputView::OnOutputFileSave() 
{
	// TODO: Add your command handler code here
	CScriptDoc* pDoc = (CScriptDoc*)GetDocument();
	ASSERT_VALID(pDoc);

	CFileDialog dlg(FALSE);

	dlg.m_ofn.lpstrTitle = _T("Сохранить результат как...");
	CString str;
	str += "Text Files (*.txt)"; str += (TCHAR)NULL;
	str += "*.txt"; str += (TCHAR)NULL;
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
	dlg.m_ofn.lpstrDefExt = _T("txt");
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
		CString strPathName( dlg.GetPathName() );
		try
		{
			CFile F( strPathName, CFile::modeCreate|CFile::modeWrite );
			F.Write( LockBuffer(), GetBufferLength() );
			UnlockBuffer();
			F.Flush();
			F.Close();
		}
		catch( CFileException& )
		{
			AfxMessageBox("CFileException !!!");
			return;
		}
		break;
	}	
}

void COutputView::Run( const CString &str )
{
	ASSERT( m_pOut == NULL );
	CScriptDoc* pDoc = (CScriptDoc*)GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_bIsExecuting = true;

	m_Text = str;
	m_Output.Empty();

	AfxBeginThread( static_cast<AFX_THREADPROC>(RunScriptThread), this );
	m_pOut = AfxBeginThread( static_cast<AFX_THREADPROC>(OutputThread), this );
	m_pOut->m_bAutoDelete = FALSE;	
}

void COutputView::Show( const CString &str )
{
	m_Output += str;
	GetEditCtrl().SetWindowText( m_Output.LockBuffer() );
	m_Output.UnlockBuffer();
//	Invalidate();
//	int min = 0, max = 0;
//	GetScrollRange( SB_VERT, &min, &max );
//	SetScrollPos( SB_VERT, max );
}

void COutputView::StopThread()
{
	m_Break.SetEvent();
	if( m_pOut )
	{
		WaitForSingleObject( m_pOut->m_hThread, INFINITE );
		delete m_pOut;
		m_pOut = NULL;
	}
	m_Break.ResetEvent();
	ASSERT(m_pIsExecuting);
	(*m_pIsExecuting) = false;
}

void COutputView::OnOutputBreak() 
{
	// TODO: Add your command handler code here
	m_Break.SetEvent();
}

void COutputView::OnUpdateOutputBreak(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( m_pOut != NULL );
}
