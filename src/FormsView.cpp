// FormsView.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "FormsView.h"
#include "ShemeDoc.h"

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

	MultMove=1.0;
	MultAngl=1.0;
	NumForm=0;
}

CFormsView::~CFormsView()
{
}


BEGIN_MESSAGE_MAP(CFormsView, CScrollView)
	//{{AFX_MSG_MAP(CFormsView)
	ON_COMMAND(ID_MOVEADD, OnMoveadd)
	ON_COMMAND(ID_MOVESUB, OnMovesub)
	ON_COMMAND(ID_FREQNEXT, OnFreqnext)
	ON_COMMAND(ID_FREQPREW, OnFreqprew)
	ON_COMMAND(ID_UPDATEFORMS, OnUpdateforms)
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
	if (!ViewEnable) return;

	double oldMove=pDoc->ParamView.MultMove;
	double oldAngl=pDoc->ParamView.MultAngl;
	
	pDoc->ParamView.Gray=true;
	POSITION pos=pDoc->listElem.GetHeadPosition();
	while (pos)
	{
		CElem *elem=pDoc->listElem.GetNext(pos);
		elem->Draw(pDC,&(pDoc->ParamView));
	}
	pDoc->ParamView.Gray=false;
	
	pDoc->ParamView.MultMove=MultMove;
	pDoc->ParamView.MultAngl=MultAngl;

	pos=pDoc->listElem.GetHeadPosition();
	while (pos)
	{
		CElem *elem=pDoc->listElem.GetNext(pos);
		elem->Draw(pDC,&(pDoc->ParamView));
	}
	pDoc->ParamView.MultMove=oldMove;
	pDoc->ParamView.MultAngl=oldAngl;


	CFont font1;
	font1.CreatePointFont(100,_T("Times New Roman"), 0);//MS Sans Serif
	pDC->SetBkColor(GetSysColor(COLOR_WINDOW));
	pDC->SetTextAlign(TA_LEFT|TA_TOP);	
	CFont *pOldFont=pDC->SelectObject(&font1);

	CString str;
	str.Format("Частота колебаний %d(%d): %.8lg 1/рад", NumForm+1, matr_Freq.SizeX, matr_Freq[0][NumForm]);
	pDC->TextOut(2, 5, str);
	double T=(matr_Freq[0][NumForm]!=0?2*acos(-1)/matr_Freq[0][NumForm]:0);
	str.Format("Период колебаний  %d(%d): %.8lg c",     NumForm+1, matr_Freq.SizeX, T);
	pDC->TextOut(2, 25, str);

	pDC->SelectObject(pOldFont);
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

	POSITION pos=pDoc->listKnot.GetHeadPosition();
	while (pos)
	{
		CKnot *kn=pDoc->listKnot.GetNext(pos);
		if (kn->nXRez>=0) 
			kn->MoveX=matr_Forms[kn->nXRez][n];
		else 
			kn->MoveX=0;

		if (kn->nYRez>=0) 
			kn->MoveY=matr_Forms[kn->nYRez][n];
		else 
			kn->MoveY=0;

		for (int i=0;i<kn->CntAngle;i++)
			if (kn->nARez[i]>=0)
				kn->MoveA[i]=matr_Forms[kn->nARez[i]][n];
			else 
				kn->MoveA[i]=0;
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
	SetForm((NumForm+1)%matr_Forms.SizeX);
	Invalidate();
}

void CFormsView::OnFreqprew() 
{
	// TODO: Add your command handler code here
	SetForm((NumForm-1+matr_Forms.SizeX)%matr_Forms.SizeX);
	Invalidate();
}


void CFormsView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CShemeDoc* pDoc = (CShemeDoc*)GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: Add your specialized code here and/or call the base class
	BeginWaitCursor();

	int Count=pDoc->UpdateAllFree();
	if (!Count) 
	{
		EndWaitCursor();
		return;
	}
	int code=pDoc->SetMatrMDC(Count);
	if (code) 
	{
		EndWaitCursor();
		return;
	}

	//Копируем данные
	matr_Forms.ReSize(pDoc->matr_C.SizeY, pDoc->matr_C.SizeY);
	matr_Freq.ReSize (pDoc->matr_C.SizeY, pDoc->matr_C.SizeY);
	matr_Freq=pDoc->matr_M_1*pDoc->matr_C;

	//Вычисление собственных частот и форм колебений методом Якоби
	if (Count>1)
	{
		code=matr_Freq.Eigen(&matr_Forms);
		if (code<0) 
		{
	//		AfxMessageBox( _T("Процесс нахождения собственных частот не сходится."),MB_OK|MB_ICONSTOP);
			ViewEnable=false;
			EndWaitCursor();
			return;
		}

		//Нормирование форм
		for (int i=0;i<matr_Forms.SizeY;i++)
		{
			double maxU=0;
			POSITION pos=pDoc->listKnot.GetHeadPosition();
			while (pos)
			{
				CKnot *kn=pDoc->listKnot.GetNext(pos);
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
					for (int k=0;k<matr_Forms.SizeY;k++)
					{
						tmp=matr_Forms[k][i];
						matr_Forms[k][i]=matr_Forms[k][j];
						matr_Forms[k][j]=tmp;
					}
				}
		ViewEnable=true;

		if (NumForm>=matr_Forms.SizeY) NumForm=0;
		SetForm(NumForm);
		Invalidate();
	}
	else
	{
		matr_Freq[0][0]=sqrt(pDoc->matr_C[0][0]/pDoc->matr_M[0][0]);
		matr_Forms[0][0]=30.0/pDoc->ParamView.Scale;
		NumForm=0;
		SetForm(NumForm);
		ViewEnable=true;
		Invalidate();
	}
	EndWaitCursor();
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
