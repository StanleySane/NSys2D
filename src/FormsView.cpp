// FormsView.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "FormsView.h"
#include "ShemeDoc.h"

#include "Sheme.h"
#include "EqualDegrees.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormsView

IMPLEMENT_DYNCREATE(CFormsView, CScrollView)

CFormsView::CFormsView()
{
	ViewEnable=false;
	m_bCalculated = false;

	MultMove=1.0;
	MultAngl=1.0;
	NumForm=0;
}

CFormsView::~CFormsView()
{
	CShemeDoc* pDoc = (CShemeDoc*)GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_bIsView = false;
}


BEGIN_MESSAGE_MAP(CFormsView, CScrollView)
	//{{AFX_MSG_MAP(CFormsView)
	ON_COMMAND(ID_MOVEADD, OnMoveadd)
	ON_COMMAND(ID_MOVESUB, OnMovesub)
	ON_COMMAND(ID_FREQNEXT, OnFreqnext)
	ON_COMMAND(ID_FREQPREW, OnFreqprew)
	ON_COMMAND(ID_UPDATEFORMS, OnUpdateforms)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormsView drawing

void CFormsView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 10;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

void CFormsView::OnDraw(CDC* pDC)
{
	CShemeDoc* pDoc = (CShemeDoc*)GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code here
	if( !ViewEnable )
	{
		(m_DlgBar.GetDlgItem(IDC_BAR_FREQ))->SetWindowText( _T("(нет данных)") );
		(m_DlgBar.GetDlgItem(IDC_BAR_T))->SetWindowText( _T("(нет данных)") );
		return;
	}

	double oldMove=pDoc->ParamView.MultMove;
	double oldAngl=pDoc->ParamView.MultAngl;
	
	pDoc->ParamView.Gray=true;
	POSITION pos=pDoc->m_pSheme->listElem.GetHeadPosition();
	while (pos)
	{
		CElem *elem=pDoc->m_pSheme->listElem.GetNext(pos);
		elem->Draw(pDC,&(pDoc->ParamView));
	}
	pDoc->ParamView.Gray=false;
	
	pDoc->ParamView.MultMove=MultMove;
	pDoc->ParamView.MultAngl=MultAngl;

	pos=pDoc->m_pSheme->listElem.GetHeadPosition();
	while (pos)
	{
		CElem *elem=pDoc->m_pSheme->listElem.GetNext(pos);
		elem->Draw(pDC,&(pDoc->ParamView));
	}
	pDoc->ParamView.MultMove=oldMove;
	pDoc->ParamView.MultAngl=oldAngl;

	if( m_bBar )
	{
		CString strFreq, strT;
		double PI2 = 2.0*CNSys2DApp::M_PI;
		strFreq.Format("%d(%d): %.16g 1/рад (%.16g Гц)", NumForm+1, matr_Freq.SizeX, matr_Freq[0][NumForm], matr_Freq[0][NumForm]/PI2 );
		double T=(matr_Freq[0][NumForm]!=0?PI2/matr_Freq[0][NumForm]:0);
		strT.Format("%d(%d): %.16g c",     NumForm+1, matr_Freq.SizeX, T);

		(m_DlgBar.GetDlgItem(IDC_BAR_FREQ))->SetWindowText(strFreq);
		(m_DlgBar.GetDlgItem(IDC_BAR_T))->SetWindowText(strT);
	}

	if( pDoc->ParamView.m_bTextOut )
	{
//		CFont font1;
//		font1.CreatePointFont(100,_T("Times New Roman"), 0);//MS Sans Serif
		pDC->SetBkColor(GetSysColor(COLOR_WINDOW));
		pDC->SetTextAlign(TA_LEFT|TA_TOP);	
//		CFont *pOldFont=pDC->SelectObject(&font1);
		CFont *pOldFont = pDC->SelectObject(&(pDoc->ParamView.m_fntFree));
		COLORREF oldClr = pDC->SetTextColor(pDoc->ParamView.m_clrFree);

		CString str;
		double PI2 = 2.0*CNSys2DApp::M_PI;
		str.Format("Частота колебаний %d(%d): %.16lg 1/рад (%.16g Гц)", NumForm+1, matr_Freq.SizeX, matr_Freq[0][NumForm], matr_Freq[0][NumForm]/PI2 );
		pDC->TextOut(2, 5, str);
		double T=(matr_Freq[0][NumForm]!=0?2*CNSys2DApp::M_PI/matr_Freq[0][NumForm]:0);
		str.Format("Период колебаний  %d(%d): %.16g c",     NumForm+1, matr_Freq.SizeX, T);
		pDC->TextOut(2, 25, str);

		pDC->SetTextColor(oldClr);
		pDC->SelectObject(pOldFont);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFormsView diagnostics

#ifdef _DEBUG
void CFormsView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CFormsView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFormsView message handlers

void CFormsView::SetForm(int n)
{
	CShemeDoc* pDoc = (CShemeDoc*)GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code here

	POSITION pos=pDoc->m_pSheme->listKnot.GetHeadPosition();
	while (pos)
	{
		CKnot *kn=pDoc->m_pSheme->listKnot.GetNext(pos);
		if (kn->nXRez>=0) 
			kn->MoveX = matr_Forms(kn->nXRez,n);
		else 
			kn->MoveX = 0;

		if (kn->nYRez>=0) 
			kn->MoveY = matr_Forms(kn->nYRez,n);
		else 
			kn->MoveY = 0;

		for (int i=0;i<kn->CntAngle;i++)
			if (kn->nARez[i]>=0)
				kn->MoveA[i] = matr_Forms(kn->nARez[i],n);
			else 
				kn->MoveA[i] = 0;
	}
	NumForm=n;
}

void CFormsView::OnMoveadd() 
{
	// TODO: Add your command handler code here
	MultMove*=1.5;	
	MultAngl*=1.5;
	Invalidate();
}

void CFormsView::OnMovesub() 
{
	// TODO: Add your command handler code here
	MultMove/=1.5;
	MultAngl/=1.5;
	Invalidate();
}

void CFormsView::OnFreqnext() 
{
	// TODO: Add your command handler code here
	if( matr_Forms.SizeX == 0 )	return;
	SetForm((NumForm+1)%matr_Forms.SizeX);
	Invalidate();
}

void CFormsView::OnFreqprew() 
{
	// TODO: Add your command handler code here
	if( matr_Forms.SizeX == 0 )	return;
	SetForm((NumForm-1+matr_Forms.SizeX)%matr_Forms.SizeX);
	Invalidate();
}


void CFormsView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CShemeDoc* pDoc = (CShemeDoc*)GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: Add your specialized code here and/or call the base class
	if( m_bCalculated )	return;

	BeginWaitCursor();

	if( !pDoc->m_pSheme->GetEigen( matr_Freq, matr_Forms ) )
	{
		ViewEnable = false;
		EndWaitCursor();
		Invalidate();
		return;
	}
	if( NumForm >= matr_Forms.SizeX )	NumForm = 0;
	SetForm( NumForm );
	ViewEnable = true;

	EndWaitCursor();
	Invalidate();
/*
	int Count = pDoc->m_pSheme->UpdateAllFree();
	if( Count == 0 )
	{
		EndWaitCursor();
		return;
	}
	int code = pDoc->m_pSheme->SetMatrMDC(Count);
	if( code )
	{
		EndWaitCursor();
		return;
	}

	//Копируем данные
	matr_Forms.ReSize(pDoc->m_pSheme->matr_C.SizeY, pDoc->m_pSheme->matr_C.SizeY);
	matr_Freq.ReSize (pDoc->m_pSheme->matr_C.SizeY, pDoc->m_pSheme->matr_C.SizeY);
	matr_Freq=pDoc->m_pSheme->matr_M_1*pDoc->m_pSheme->matr_C;

	if( Count > 1 )
	{
		EV_METHOD EVm = pDoc->m_pSheme->m_EVMethod;

		if( EVm == EVM_JACOBY )
		{
			//Вычисление собственных частот и форм колебаний методом Якоби
			code=matr_Freq.Eigen(&matr_Forms);
			if (code<0) 
			{
		//		AfxMessageBox( _T("Процесс нахождения собственных частот не сходится."),MB_OK|MB_ICONSTOP);
				//////////////////////////////////////////////////////////
				//демодификация форм если надо
				if( pDoc->m_pSheme->m_bIsHardRod )
				{
					pDoc->m_pSheme->m_pEqDeg->DeModifyMatrix( matr_Forms );
				}
				//////////////////////////////////////////////////////////
				ViewEnable=false;
				EndWaitCursor();
				Invalidate();
				return;
			}
		}
		else
		{
			//вычисление собств.значений и форм QR-методом
			code = matr_Freq.GetEigenVecs( matr_Forms, EVm );
			if (code<0) 
			{
				//////////////////////////////////////////////////////////
				//демодификация форм если надо
				if( pDoc->m_pSheme->m_bIsHardRod )
				{
					pDoc->m_pSheme->m_pEqDeg->DeModifyMatrix( matr_Forms );
				}
				//////////////////////////////////////////////////////////
				ViewEnable=false;
				EndWaitCursor();
				Invalidate();
				return;
			}
		}//if(EVm==EVM_JACOBY)

////////////////////////////////////////////
#ifdef _DEBUG
			TRACE0("Before demodify:\n");
			for( int r = 0; r < matr_Forms.SizeY; r++ )
			{
				for( int c = 0; c < matr_Forms.SizeX; c++ )
				{
					TRACE1("%.5lf ", matr_Forms[r][c] );
				}
				TRACE0("\n");
			}
#endif
////////////////////////////////////////////
		//////////////////////////////////////////////////////////
		//демодификация форм если надо
		if( pDoc->m_pSheme->m_bIsHardRod )
		{
			pDoc->m_pSheme->m_pEqDeg->DeModifyMatrix( matr_Forms );
		}
		//////////////////////////////////////////////////////////
////////////////////////////////////////////
#ifdef _DEBUG
			TRACE0("After demodify:\n");
			for( r = 0; r < matr_Forms.SizeY; r++ )
			{
				for( int c = 0; c < matr_Forms.SizeX; c++ )
				{
					TRACE1("%.5lf ", matr_Forms[r][c] );
				}
				TRACE0("\n");
			}
#endif
////////////////////////////////////////////

		//Нормирование форм
		for (int i=0;i<matr_Forms.SizeX;i++)
		{
			double maxU=0;
			POSITION pos=pDoc->m_pSheme->listKnot.GetHeadPosition();
			while (pos)
			{
				CKnot *kn=pDoc->m_pSheme->listKnot.GetNext(pos);
				if (kn->nXRez>=0) 
				{
					double uu=matr_Forms[kn->nXRez][i];
					if (fabs(uu)>fabs(maxU)) maxU=uu;
				}
				if (kn->nYRez>=0)
				{
					double uu=matr_Forms[kn->nYRez][i];
					if (fabs(uu)>fabs(maxU)) maxU=uu;
				}
			}
			if ( (maxU!=0) && (fabs(maxU)>0.4) )
				for (int j=0;j<matr_Forms.SizeY;j++)
					matr_Forms[j][i]*=30.0/pDoc->ParamView.Scale/maxU;
		}
		//Извлекаем корень из квадратов частот и записываем в первую строку
		for (i=0;i<matr_Freq.SizeY;i++)
			matr_Freq[0][i]=sqrt(fabs(matr_Freq[i][i]));

		//Сортируем формы по возрастанию частот
		for (i=0;i<matr_Freq.SizeX-1;i++)
			for (int j=i+1;j<matr_Freq.SizeX;j++)
				if ( matr_Freq[0][i]>matr_Freq[0][j] )
				{
					double tmp=matr_Freq[0][i];
					matr_Freq[0][i]=matr_Freq[0][j];
					matr_Freq[0][j]=tmp;
					for( int k = 0; k < matr_Forms.SizeY; k++ )
					{
						tmp=matr_Forms[k][i];
						matr_Forms[k][i]=matr_Forms[k][j];
						matr_Forms[k][j]=tmp;
					}
				}
////////////////////////////////////////////
#ifdef _DEBUG
			TRACE0("After sort:\n");
			for( r = 0; r < matr_Forms.SizeY; r++ )
			{
				for( int c = 0; c < matr_Forms.SizeX; c++ )
				{
					TRACE1("%.5lf ", matr_Forms[r][c] );
				}
				TRACE0("\n");
			}
#endif
////////////////////////////////////////////
	}
	else
	{
		ASSERT( matr_Forms.SizeX == 1 );
		matr_Freq[0][0] = sqrt(pDoc->m_pSheme->matr_C[0][0]/pDoc->m_pSheme->matr_M[0][0]);
		matr_Forms[0][0] = 30.0/pDoc->ParamView.Scale;
	}
	if( NumForm >= matr_Forms.SizeX )	NumForm = 0;
	SetForm(NumForm);
	ViewEnable=true;

	EndWaitCursor();
	Invalidate();
	*/
}

void CFormsView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	CRect clrect;
	GetClientRect(&clrect);
	pDC->SetMapMode(MM_ISOTROPIC);

	pDC->SetWindowExt(clrect.Width(), clrect.Height());
	pDC->SetWindowOrg(0,0);
	
	CSize sizePaper=CSize(pDC->GetDeviceCaps(HORZRES),
						  pDC->GetDeviceCaps(VERTRES));

	CRect rect(0,0,sizePaper.cx,sizePaper.cy);
	pDC->SetViewportExt(rect.Width(), rect.Height());

//	pDC->LPtoDP(&rect);
	pInfo->m_rectDraw=rect;
	OnDraw(pDC);
//	CScrollView::OnPrint(pDC, pInfo);
}

BOOL CFormsView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	// TODO: call DoPreparePrinting to invoke the Print dialog box
	pInfo->SetMinPage(1);
	pInfo->SetMaxPage(1);
	return DoPreparePrinting(pInfo);
//	return CScrollView::OnPreparePrinting(pInfo);
}

void CFormsView::OnUpdateforms() 
{
	// TODO: Add your command handler code here
	OnUpdate(0,0,0);
}

int CFormsView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CShemeDoc* pDoc = (CShemeDoc*)GetDocument();
	ASSERT_VALID(pDoc);
	m_bBar = pDoc->m_bMakeBar;
	
	// TODO: Add your specialized creation code here
	if( m_bBar )
	{
		if (!m_DlgBar.Create( GetOwner(),
			IDD_FORMS_BAR,
			CBRS_TOP|CBRS_TOOLTIPS|CBRS_FLYBY, 
			IDD_FORMS_BAR))
		{
			TRACE0("Ошибка при создании панели \n");
			return -1; 
		}
	}

	return 0;
}
