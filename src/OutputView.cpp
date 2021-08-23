// OutputView.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "OutputView.h"

#include "ScriptDoc.h"
#include "ScriptHeader.h"
#include "OutputFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

UINT RunScriptThread( LPVOID lParam )
{
	CScriptDoc *pDoc = static_cast<CScriptDoc*>(lParam);
	ASSERT( pDoc->IsKindOf(RUNTIME_CLASS(CScriptDoc)) );
	
	CMenu *mn = pDoc->m_pFrame->GetSystemMenu(FALSE);
	ASSERT(mn);
	mn->EnableMenuItem( SC_CLOSE, MF_BYCOMMAND|MF_GRAYED );

	try
	{
		CScript scr;
		scr.Set( pDoc );
		scr.SetDebug( false );
		scr.Run();
	}
	catch(...)
	{
		AfxMessageBox("Произошло исключение при выполнении скрипта\nЗакройте приложение");
	}
	//if( scr.FatalCrash() )	return -1;
	pDoc->StopThread();
	return 0;
}

UINT OutputThread( LPVOID lParam )
{
	CScriptDoc *pDoc = static_cast<CScriptDoc*>(lParam);
	ASSERT( pDoc->IsKindOf(RUNTIME_CLASS(CScriptDoc)) );
	
	CSyncObject *pObj[] = 
	{	&pDoc->m_Break, &pDoc->m_Buf.m_NotFree };
	for(;;)
	{
		CMultiLock Lock( pObj, 2 );
		switch( Lock.Lock( INFINITE, FALSE ) )
		{
		case WAIT_OBJECT_0:
//			if( pDoc->m_pView )
				pDoc->m_pView->Show( pDoc->m_Buf.ReadOut() );
			return 0;
			break;
		case (WAIT_OBJECT_0+1):
//			if( pDoc->m_pView )
				pDoc->m_pView->Show( pDoc->m_Buf.ReadOut() );
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

COutputView::COutputView()
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
		pDoc->m_pView = NULL;
		return -1;
	}
	// TODO: Add your specialized creation code here	
	CScriptDoc* pDoc = (CScriptDoc*)GetDocument();
	ASSERT_VALID(pDoc);

	SetTabStops(5);
	CEdit *pEd = &GetEditCtrl();
	pEd->SetReadOnly();

	return 0;
}

void COutputView::OnDestroy() 
{
	CEditView::OnDestroy();	
	// TODO: Add your message handler code here
	CScriptDoc* pDoc = (CScriptDoc*)GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_pView = NULL;
	pDoc->m_pFrame = NULL;
	pDoc->m_Break.SetEvent();
	ASSERT( pDoc->m_pOut == NULL );
	//if( pDoc->m_pOut != NULL )	AfxMessageBox("View Error !!!");
}

void COutputView::OnOutputFileSave() 
{
	// TODO: Add your command handler code here
	CScriptDoc* pDoc = (CScriptDoc*)GetDocument();
	ASSERT_VALID(pDoc);

	CFileDialog dlg(FALSE);
	CString strName = pDoc->GetTitle();

	dlg.m_ofn.lpstrTitle = _T("Сохранить результат как...");
	CString str;
	str += "Text Files (*.txt)"; str += (TCHAR)NULL;
	str += "*.txt"; str += (TCHAR)NULL;
	str += "All Files (*.*)"; str += (TCHAR)NULL;
	str += "*.*"; str += (TCHAR)NULL;

	dlg.m_ofn.lpstrFilter = static_cast<LPCTSTR>(str);

	dlg.m_ofn.nFilterIndex = 1;
	dlg.m_ofn.lpstrDefExt = _T("txt");
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

void COutputView::Run( const CString &str, COutputFrame *pFrame )
{
	CScriptDoc* pDoc = (CScriptDoc*)GetDocument();
	ASSERT_VALID(pDoc);
	ASSERT( pDoc->m_pOut == NULL );

	AfxGetMainWnd()->GetSystemMenu(FALSE)->EnableMenuItem(SC_CLOSE, MF_BYCOMMAND|MF_GRAYED );

	pDoc->m_bIsExecuting = true;

	m_Text = str;
	m_Output.Empty();

	AfxBeginThread( static_cast<AFX_THREADPROC>(RunScriptThread), pDoc );
	pDoc->m_pOut = AfxBeginThread( static_cast<AFX_THREADPROC>(OutputThread), pDoc );
	pDoc->m_pOut->m_bAutoDelete = FALSE;	
}

void COutputView::Show( const CString &str )
{
	m_Output += str;
	CEdit *pEdit = &GetEditCtrl();
	LockWindowUpdate();
	pEdit->SetWindowText( m_Output.LockBuffer() );
	m_Output.UnlockBuffer();
//	Invalidate();
//	int min = 0, max = 0;
//	GetScrollRange( SB_VERT, &min, &max );
//	SetScrollPos( SB_VERT, max );
	int c = pEdit->GetLineCount();
	pEdit->LineScroll(c);
	UnlockWindowUpdate();
}

