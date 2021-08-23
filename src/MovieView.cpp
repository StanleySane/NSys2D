// MovieView.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "MovieView.h"

#include "ShemeDoc.h"
#include "Sheme.h"
#include "MovieParams.h"

#include<limits>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef max
#undef max
#endif
/////////////////////////////////////////////////////////////////////////////
// CMovieView

IMPLEMENT_DYNCREATE(CMovieView, CScrollView)

CMovieView::CMovieView()
{
	m_pQuad = gluNewQuadric();
	m_bShowKnots = true;
	Reset();
	m_TimeStep = 1;
	m_Width = 0.0;
	m_StartTime = 0;
	m_TimeMax = 0;
	m_bIsFirstCreating = true;
	m_IntegrStep = 0.0;
}

CMovieView::~CMovieView()
{
	gluDeleteQuadric( m_pQuad );
}


BEGIN_MESSAGE_MAP(CMovieView, CScrollView)
	//{{AFX_MSG_MAP(CMovieView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_COMMAND(ID_MOVIE_RUN, OnMovieRun)
	ON_COMMAND(ID_MOVIE_STOP, OnMovieStop)
	ON_WM_TIMER()
	ON_UPDATE_COMMAND_UI(ID_MOVIE_RUN, OnUpdateMovieRun)
	ON_UPDATE_COMMAND_UI(ID_MOVIE_STOP, OnUpdateMovieStop)
	ON_COMMAND(ID_MOVIE_PARAMS, OnMovieParams)
	ON_UPDATE_COMMAND_UI(ID_MOVIE_PARAMS, OnUpdateMovieParams)
	ON_COMMAND(ID_MOVIE_MOVE_LEFT, OnMovieMoveLeft)
	ON_COMMAND(ID_MOVIE_MOVE_RIGHT, OnMovieMoveRight)
	ON_COMMAND(ID_MOVIE_SCALE_DEC, OnMovieScaleDec)
	ON_COMMAND(ID_MOVIE_SCALE_INC, OnMovieScaleInc)
	ON_COMMAND(ID_MOVIE_AUTO_SCALE, OnMovieAutoScale)
	ON_COMMAND(ID_MOVIE_MOVE_DOWN, OnMovieMoveDown)
	ON_COMMAND(ID_MOVIE_MOVE_UP, OnMovieMoveUp)
	ON_COMMAND(ID_MOVIE_PREV_STEP, OnMoviePrevStep)
	ON_COMMAND(ID_MOVIE_NEXT_STEP, OnMovieNextStep)
	ON_UPDATE_COMMAND_UI(ID_MOVIE_PREV_STEP, OnUpdateMoviePrevStep)
	ON_UPDATE_COMMAND_UI(ID_MOVIE_NEXT_STEP, OnUpdateMovieNextStep)
	ON_COMMAND(ID_MOVIE_PAUSE, OnMoviePause)
	ON_UPDATE_COMMAND_UI(ID_MOVIE_PAUSE, OnUpdateMoviePause)
	ON_UPDATE_COMMAND_UI(ID_CURRENT_TIME, OnUpdateCurrentTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMovieView drawing

void CMovieView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);

	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
}

void CMovieView::Draw()
{
	CShemeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code here
	if( ::wglMakeCurrent(m_pDC->GetSafeHdc(), m_hrc) == FALSE )
	{
		ASSERT(FALSE);
		return;
	}
	glClear(GL_COLOR_BUFFER_BIT);
	////////////////////////////////////////////////////////
	POSITION pos = pDoc->m_pSheme->listElem.GetHeadPosition();
	while( pos )
	{
		CElem *elem = pDoc->m_pSheme->listElem.GetNext(pos);
		elem->DrawGL( pDoc, m_Time );
	}

	glFlush();
	glFinish();
	////////////////////////////////////////////////////////
	//SwapBuffers(::wglGetCurrentDC());
	SwapBuffers( m_pDC->GetSafeHdc() );
}

void CMovieView::OnDraw(CDC* pDC)
{
	CShemeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code here
	Draw();
}

/////////////////////////////////////////////////////////////////////////////
// CMovieView diagnostics

#ifdef _DEBUG
void CMovieView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMovieView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CShemeDoc* CMovieView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CShemeDoc)));
	return (CShemeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMovieView message handlers

void CMovieView::SetCurrentTime()
{
	if( m_Time < 0 )
		m_strCurrentTime = _T("Исходная схема");
	else
		m_strCurrentTime.Format("t=%g", m_Time*m_IntegrStep );
}

void CMovieView::Reset()
{
	m_Time = -1;
//	m_TimeMax = 0;
	m_bIsMoving = false;
	SetCurrentTime();
}

BOOL CMovieView::SetPixelFormat( HDC hdc )
{
	static PIXELFORMATDESCRIPTOR pfd = 
	{
		sizeof(PIXELFORMATDESCRIPTOR),	// размер структуры
		1,								// номер версии
		PFD_DRAW_TO_WINDOW |			// поддержка вывода в окно
		PFD_SUPPORT_OPENGL |			// поддержка OpenGL
		PFD_DOUBLEBUFFER,				// двойная буферизация
		PFD_TYPE_RGBA,					// цвета в режиме RGBA
		24,								// 24 разряда на цвет
		0, 0, 0, 0, 0, 0,				// биты цвета игнорируем
		0,								// не используется параметр alpha ( не поддерживается )
		0,								// смещение цветов игнорируется
		0,								// буфер аккумулятора не используется
		0, 0, 0, 0,						// биты аккумулятора игнорируются
		32,								// 32-разрядный буфер глубины
		0,								// буфер трафарета не используется
		0,								// вспомогательный буфер не используется
		PFD_MAIN_PLANE,					// основной слой
		0,								// зарегистрирован
		0, 0, 0							// маски слоя игнорируются
	};
	int pixelFormat;

	if( (pixelFormat = ::ChoosePixelFormat(hdc, &pfd)) == 0 )
	{
		AfxMessageBox("С заданным форматом пикселей работать нельзя");
		return FALSE;
	}
	if( ::SetPixelFormat(hdc, pixelFormat, &pfd) == FALSE )
	{
		AfxMessageBox("Ошибка при выполнении ::SetPixelFormat");
		return FALSE;
	}
	return TRUE;
}

BOOL CMovieView::CreateGLContext( HDC hdc )
{
	if( (m_hrc = ::wglCreateContext(hdc)) == NULL )
		return FALSE;
	if( ::wglMakeCurrent(hdc, m_hrc) == FALSE )
		return FALSE;
	return TRUE;
}

int CMovieView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_pDC = new CClientDC(this);
	ASSERT( m_pDC != NULL );
	HDC hdc = m_pDC->GetSafeHdc();

	if( SetPixelFormat(hdc) == FALSE )
		return -1;
	if( CreateGLContext(hdc) == FALSE )
		return -1;

	CShemeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	InitMatr(pDoc);

	return 0;
}

BOOL CMovieView::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style |= (WS_CLIPCHILDREN | WS_CLIPSIBLINGS);

	return CScrollView::PreCreateWindow(cs);
}

void CMovieView::OnDestroy() 
{
	CScrollView::OnDestroy();
	
	// TODO: Add your message handler code here
	CShemeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(m_hrc)
	{
		if( m_hrc == ::wglGetCurrentContext() )
			::wglMakeCurrent( NULL, NULL );
		::wglDeleteContext( m_hrc );
		m_hrc = NULL;
	}
	if( m_pDC )
		delete m_pDC;

	pDoc->m_pMovieView = NULL;
	if( m_bIsMoving )
	{
		KillTimer(10);
		Reset();
	}
}

void CMovieView::OnSize(UINT nType, int cx, int cy) 
{
	CScrollView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	m_width = cx;
	m_height = cy;

	CShemeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if( ::wglMakeCurrent(m_pDC->GetSafeHdc(), m_hrc) == FALSE )
	{
		ASSERT(FALSE);
		return;
	}

	double minx = 0, miny = 0;
	double maxx = 0, maxy = 0;
	POSITION pos = pDoc->m_pSheme->listElem.GetHeadPosition();
	if( pos )
	{
		CElem *elem = pDoc->m_pSheme->listElem.GetNext(pos);
		CCoordD c1 = elem->knot1->GetCoord(), c2 = elem->knot2->GetCoord();
		minx = (c1.x<c2.x)?c1.x:c2.x;
		miny = (c1.y<c2.y)?c1.y:c2.y;
		maxx = (c1.x>c2.x)?c1.x:c2.x;
		maxy = (c1.y>c2.y)?c1.y:c2.y;
		while( pos )
		{
			elem = pDoc->m_pSheme->listElem.GetNext(pos);
			c1 = elem->knot1->GetCoord();
			if( c1.x < minx )	minx = c1.x;
			if( c1.x > maxx )	maxx = c1.x;
			if( c1.y < miny )	miny = c1.y;
			if( c1.y > maxy )	maxy = c1.y;
			c1 = elem->knot2->GetCoord();
			if( c1.x < minx )	minx = c1.x;
			if( c1.x > maxx )	maxx = c1.x;
			if( c1.y < miny )	miny = c1.y;
			if( c1.y > maxy )	maxy = c1.y;
		}
	}
	ASSERT( (minx <= maxx)&&(miny <= maxy) );

	double wx = maxx - minx, wy = maxy - miny;
	double W2 = (wx > wy)?(wx/2):(wy/2);//половина ширины квадрата вывода
	m_Width = W2*2;
	//glViewport( 0, 0, m_height, m_height );
	glViewport( 0, 0, m_width, m_width );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D( minx - W2, maxx + W2, miny - W2, maxy + W2 );
	glMatrixMode(GL_MODELVIEW);
	glViewport( 0, 0, m_width, m_width );
	if( (m_bIsFirstCreating)&&(cx != 0)&&(cy != 0) )
	{
		glTranslatef( 0.0, -3.0*m_Width/10.0, 0.0 );	
		GLfloat sc = static_cast<GLfloat>(cy)/static_cast<GLfloat>(cx);
		glScalef( sc, sc, 1.0 );
//		glScalef( 0.5, 0.5, 1.0 );
		m_bIsFirstCreating = false;
	}
}

void CMovieView::OnMovieRun() 
{
	// TODO: Add your command handler code here
	CShemeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	m_Time = m_StartTime;
	m_bIsMoving = true;
	SetCurrentTime();
	SetTimer( 10, m_TimeStep, NULL );
	Invalidate();
}

void CMovieView::OnMovieStop() 
{
	// TODO: Add your command handler code here
	KillTimer( 10 );
	Reset();
	Invalidate();
}

void CMovieView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if( nIDEvent == 10 )
	{
		if( m_Time >= m_TimeMax )
		{
			KillTimer(10);
			Reset();
		}
		Draw();
		if( m_Time >= 0 )
			m_Time++;
		SetCurrentTime();
	}	
	CScrollView::OnTimer(nIDEvent);
}

void CMovieView::OnUpdateMovieRun(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( m_bIsMoving );
	pCmdUI->Enable( !m_bIsMoving && (m_TimeMax >= 0) );
}

void CMovieView::OnUpdateMovieStop(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( m_bIsMoving );
}

void CMovieView::OnMovieParams() 
{
	// TODO: Add your command handler code here
	CShemeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CMovieParams dlg;
	dlg.m_uTimerElapse = m_TimeStep;
	dlg.m_StartTime = m_StartTime;
	dlg.m_bShowKnots = m_bShowKnots;

	while( dlg.DoModal() == IDOK )
	{
		if( dlg.m_StartTime > (pDoc->m_pSheme->matr_RezY1.SizeX - 1) )
		{
			CString str;
			str.Format("Начальное время не может быть больше %d",
				pDoc->m_pSheme->matr_RezY1.SizeX - 1 );
			AfxMessageBox(str);
			continue;
		}
		m_bShowKnots = (dlg.m_bShowKnots == FALSE)?(false):(true);
		m_StartTime = dlg.m_StartTime;
		m_TimeStep = dlg.m_uTimerElapse;
		break;
	}
	Invalidate();
}

void CMovieView::InitMatr( CShemeDoc *pDoc )
{
//ф-ция заполняет м-цы m_KnotCoords, m_Res по данным документа pDoc
	BeginWaitCursor();
	m_IntegrStep = pDoc->m_pSheme->ParamIntegr.Step;
	m_TimeMax = pDoc->m_pSheme->matr_RezY1.SizeX - 1;
	if( !m_KnotCoords.Resize( pDoc->m_pSheme->matr_RezY1.SizeY, 1 ) )
	{
		EndWaitCursor();
		AfxMessageBox("Ошибка создания вектора координат!");
		return;
	}
	POSITION pos = pDoc->m_pSheme->listKnot.GetHeadPosition();
	while(pos)
	{
		CKnot *kn = pDoc->m_pSheme->listKnot.GetNext(pos);
		if( (kn->nXRez < 0)&&(kn->nYRez < 0)&&(kn->nARez[0] < 0) )
			continue;
		CCoordD c = kn->GetCoord();		
		if( kn->nXRez >= 0 )
		{
			ASSERT( kn->nXRez < pDoc->m_pSheme->matr_RezY1.SizeY );
			m_KnotCoords( kn->nXRez + 1, 0 ) = c.x;
		}
		if( kn->nYRez >= 0 )
		{
			ASSERT( kn->nYRez < pDoc->m_pSheme->matr_RezY1.SizeY );
			m_KnotCoords( kn->nYRez + 1, 0 ) = c.y;
		}
		/*
		if( kn->nARez[0] >= 0 )
		{
			ASSERT( kn->nARez[0] < pDoc->m_pSheme->matr_RezY1.SizeY );
			m_KnotCoords( kn->nARez[0] + 1, 0 ) = 0.0;
		}
		*/
	}
	pDoc->m_pSheme->matr_RezY1.ConvertToAlgolMatr( m_Res );
	m_Res.SetMinCol(0);

	int r, c;
	for( r = 1; r <= pDoc->m_pSheme->matr_RezY1.SizeY; r++ )
	{
		for( c = 0; c < pDoc->m_pSheme->matr_RezY1.SizeX; c++ )
		{
			m_Res( r, c ) += m_KnotCoords( r, 0 );
		}
	}
	//проверка на расходимость. если в OpenGL подсунуть некорректные величины
	//типа double (т.е. +INF и т.п.), то он "загибается".
	bool bIsError = false;
	double MaxD = std::numeric_limits<double>::max();
	int rows = m_Res.GetRow(), cols = m_Res.GetMaxCol();
	for( r = 1; r <= rows; r++ )
	{
		for( c = 0; c <= cols; c++ )
		{
			double val = m_Res( r, c );
			if( (val < -MaxD)||(val > MaxD) )
			{
				bIsError = true;
				m_Res( r, c ) = 0.0;
			}
		}
	}
	//Определение локальных перемещений гибких стержней
	m_RodMoves.clear();
	//CMatr Ugl(6,1), Uloc(6,1);
	CMatr U(6,1);
	CMatr T(6,6);
	CMatr mM(6,6), A(6,1);
	CMatr T1(2,2), T_1(2,2);
	//CMatr Uu(2,1), U(2,1);
	CMatr u(2,1);
	const int N = 10;//число прямолинейных кусков, из которых строится
	//гибкий стержень
	double tStep = 1.0/static_cast<double>(N);
	pos = pDoc->m_pSheme->listElem.GetHeadPosition();
	while(pos)
	{
		CElem *elem = pDoc->m_pSheme->listElem.GetNext(pos);
		if( elem->TypeElem == IDC_ROD )
		{
			//бежим по стержням:
			CRod *rd = static_cast<CRod*>(elem);

//			Ugl.ClearData();
//			Uloc.ClearData();
//			T.ClearData();
//			A.ClearData();

			rd->GetMatrT( T1, 2);
			rd->GetMatrT( T, 6 );
			T_1 = !T1;

			CCoordD c1 = rd->knot1->GetCoord(), c2 = rd->knot2->GetCoord();
			double L = rd->GetLength(), L2 = L*L, L3 = L2*L;
			double dx = c2.x - c1.x, dy = c2.y - c1.y;
			RodMoves::referent_type vec1;
			for( int i = 0; i < pDoc->m_pSheme->matr_RezY1.SizeX; i++ )
			{
				//бежим по моментам времени (i):
				U[0][0] = (rd->knot1->nXRez >= 0)?(pDoc->m_pSheme->matr_RezY1[rd->knot1->nXRez][i]):(0.0);
				U[1][0] = (rd->knot1->nYRez >= 0)?(pDoc->m_pSheme->matr_RezY1[rd->knot1->nYRez][i]):(0.0);
				U[2][0] = (rd->knot1->nARez[0] >= 0)?(pDoc->m_pSheme->matr_RezY1[rd->knot1->nARez[0]][i]):(0.0);

				U[3][0] = (rd->knot2->nXRez >= 0)?(pDoc->m_pSheme->matr_RezY1[rd->knot2->nXRez][i]):(0.0);
				U[4][0] = (rd->knot2->nYRez >= 0)?(pDoc->m_pSheme->matr_RezY1[rd->knot2->nYRez][i]):(0.0);
				U[5][0] = (rd->knot2->nARez[0] >= 0)?(pDoc->m_pSheme->matr_RezY1[rd->knot2->nARez[0]][i]):(0.0);

				//Uloc = T*Ugl;//получили локальные перемещения для стержня
				U = T*U;//получили локальные перемещения для стержня

				mM.ClearData();
//				mM[0][0] = mM[1][1] = mM[2][1] = mM[1][2] = mM[2][2] = mM[1][4] = mM[2][5] = mM[5][5] = 0.0;
				mM[0][3] = mM[3][3] = mM[2][4] = mM[5][4] = mM[1][5] = mM[4][5] = 1.0;
				mM[3][0] = mM[4][4] = L;
				mM[4][1] = L3;
				mM[5][1] = 3*L2;
				mM[4][2] = L2;
				mM[5][2] = 2*L;

				if( !mM.SolveSystem( U, A ) )
					A.ClearData();
		
				RodMoves::referent_type::value_type vec2;
				for( double t = 0.0; t <= 1.0; t += tStep )
				{
					double tl = t*L, tl2 = tl*tl;
					u[0][0] = A[0][0]*tl + A[3][0];
					u[1][0] = A[1][0]*tl2*tl + A[2][0]*tl2 + A[4][0]*tl + A[5][0];
					u = T_1*u;
					//glVertex2f( x+(c2.x-c1.x)*t+c1.x, y+(c2.y-c1.y)*t+c1.y );
					tl = u[0][0] + dx*t + c1.x;
					if( (tl < -MaxD)||(tl > MaxD) )
					{
						bIsError = true;
						tl = 0.0;
					}
					tl2 = u[1][0] + dy*t + c1.y;
					if( (tl2 < -MaxD)||(tl2 > MaxD) )
					{
						bIsError = true;
						tl2 = 0.0;
					}
					vec2.push_back( make_pair( tl, tl2 ) );
				}
				vec1.push_back( vec2 );
			}//for(i)
			m_RodMoves.insert( RodMoves::value_type(rd,vec1) );
		}//if(IDC_ROD)
	}//while(pos)
	EndWaitCursor();
	if( bIsError )
	{
		AfxMessageBox("Данные содержали некорректные значения и были исправлены.\n(Вероятно, метод интегрирования расходится)");
	}
}

void CMovieView::OnUpdateMovieParams(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here	
	pCmdUI->Enable( !m_bIsMoving );
}

void CMovieView::OnMovieMoveLeft() 
{
	// TODO: Add your command handler code here
	if( ::wglMakeCurrent(m_pDC->GetSafeHdc(), m_hrc) == FALSE )
	{
		ASSERT(FALSE);
		return;
	}
	glTranslatef( -(m_Width/10.0), 0.0f, 0.0f );
	Invalidate();
}

void CMovieView::OnMovieMoveRight() 
{
	// TODO: Add your command handler code here
	if( ::wglMakeCurrent(m_pDC->GetSafeHdc(), m_hrc) == FALSE )
	{
		ASSERT(FALSE);
		return;
	}
	glTranslatef( m_Width/10.0, 0.0f, 0.0f );	
	Invalidate();
}

void CMovieView::OnMovieScaleDec() 
{
	// TODO: Add your command handler code here
	if( ::wglMakeCurrent(m_pDC->GetSafeHdc(), m_hrc) == FALSE )
	{
		ASSERT(FALSE);
		return;
	}
	glScalef( 0.8f, 0.8f, 1.0f );
	Invalidate();
}

void CMovieView::OnMovieScaleInc() 
{
	// TODO: Add your command handler code here
	if( ::wglMakeCurrent(m_pDC->GetSafeHdc(), m_hrc) == FALSE )
	{
		ASSERT(FALSE);
		return;
	}
	glScalef( 1.25f, 1.25f, 1.0f );	
	Invalidate();
}

void CMovieView::OnMovieAutoScale() 
{
	// TODO: Add your command handler code here
	if( ::wglMakeCurrent(m_pDC->GetSafeHdc(), m_hrc) == FALSE )
	{
		ASSERT(FALSE);
		return;
	}
	glLoadIdentity();
	Invalidate();
}

void CMovieView::OnMovieMoveDown() 
{
	// TODO: Add your command handler code here
	if( ::wglMakeCurrent(m_pDC->GetSafeHdc(), m_hrc) == FALSE )
	{
		ASSERT(FALSE);
		return;
	}
	glTranslatef( 0.0f, -m_Width/10.0, 0.0f );	
	Invalidate();
}

void CMovieView::OnMovieMoveUp() 
{
	// TODO: Add your command handler code here
	if( ::wglMakeCurrent(m_pDC->GetSafeHdc(), m_hrc) == FALSE )
	{
		ASSERT(FALSE);
		return;
	}
	glTranslatef( 0.0f, m_Width/10.0, 0.0f );	
	Invalidate();	
}

void CMovieView::OnMoviePrevStep() 
{
	// TODO: Add your command handler code here
	m_Time--;
	if( m_Time < -1 )
		m_Time = -1;
	m_StartTime = (m_Time >= 0)?(m_Time):(0);
	SetCurrentTime();
	Invalidate();
}

void CMovieView::OnMovieNextStep() 
{
	// TODO: Add your command handler code here
	m_Time++;
	if( m_Time > m_TimeMax )
		m_Time = m_TimeMax;
	m_StartTime = m_Time;
	SetCurrentTime();
	Invalidate();
}

void CMovieView::OnUpdateMoviePrevStep(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( (!m_bIsMoving)&&(m_Time >= 0) );
}

void CMovieView::OnUpdateMovieNextStep(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( (!m_bIsMoving)&&(m_Time < m_TimeMax) );
}

void CMovieView::OnMoviePause() 
{
	// TODO: Add your command handler code here
	KillTimer( 10 );
	m_bIsMoving = false;
	m_StartTime = (m_Time >= 0)?(m_Time):(0);
	SetCurrentTime();
	Invalidate();
}

void CMovieView::OnUpdateMoviePause(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( m_bIsMoving );
}

void CMovieView::OnUpdateCurrentTime(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetText( m_strCurrentTime );
}
