// Matr.cpp: implementation of the CMatr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"
#include "Matr.h"
#include "AlgolMatr.h"

#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

void Balance( AlgolMatr &a, AlgolMatr &d, int &low, int &hi, int base = 2 );
void BalBack( int low, int hi, AlgolMatr d, AlgolMatr &z );

void ElmHes( int k, int l, AlgolMatr &a, int *inter );
void DirHes( int k, int l, AlgolMatr &a, int *inter );
void OrtHes( int k, int l, AlgolMatr &a, AlgolMatr &d );

void ElmTrans( int low, int upp, int *inter, AlgolMatr h, AlgolMatr &v );
void DirTrans( int low, int upp, int *inter, AlgolMatr h, AlgolMatr &v );
void OrtTrans( int low, int upp, AlgolMatr h, AlgolMatr d, AlgolMatr &v );

void HQR2( int low, int upp, AlgolMatr &h, AlgolMatr &vecs, 
		  AlgolMatr &wr, AlgolMatr &wi, int *cnt, int maxiter = 30 );

int ACCInverse( AlgolMatr &a, int &l );
bool SymDet( AlgolMatr &a, AlgolMatr &p, DETERMINANT &det );

/*****************CMatr class*******************************/
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMatr::CMatr()
{
	Data=0;
	SizeX=SizeY=0;
}

CMatr::~CMatr()
{
	Clear();
}

CMatr::CMatr(int ny, int nx)
{
	Data=0;
	SizeX=SizeY=0;

	ReSize(ny,nx);
}

double* CMatr::operator [](int n)
{
	ASSERT(Data);
	ASSERT(n<SizeY);

	return Data[n];
}

CMatr CMatr::operator !()
{
	CMatr Matr(SizeX,SizeY);
	
	for (int i=0;i<SizeX;i++)	
		for (int j=0;j<SizeY;j++)
			Matr[i][j]=Data[j][i];
	return Matr;
}

int CMatr::IsEmpty()
{
	if (Data) return 0;
	return 1;
}

void CMatr::Clear()
{
	if (Data)
	{
		for (int i=0;i<SizeY;i++)
		{
			delete [] Data[i];
			Data[i] = NULL;
		}
		delete [] Data;
		Data = NULL;
		SizeX = SizeY = 0;
	}
}

void CMatr::ReSize(int ny, int nx)
{
	ASSERT(nx>0);
	ASSERT(ny>0);
	if( (SizeX != nx)||(SizeY != ny) )
	{
		Clear();

		SizeX = nx;
		SizeY = ny;
	
		try
		{
			Data = new double*[SizeY];
		}
		catch( bad_alloc& )
		{
			Data = NULL;
			SizeX = SizeY = 0;
			return;
		}
		for (int i=0;i<SizeY;i++)
		{
			try
			{
				Data[i] = new double[SizeX];
			}
			catch( bad_alloc& )
			{
				Data[i] = NULL;
				Clear();
				return;
			}
		}
	}
	ClearData();
}

void CMatr::ClearData()
{
	for (int i=0;i<SizeY;i++)
		for (int j=0;j<SizeX;j++)
			Data[i][j]=0;
}

CMatr::CMatr(CMatr & matr)
{
	Data=0;
	SizeX=SizeY=0;

	ReSize(matr.SizeY,matr.SizeX);
	for (int i=0;i<SizeY;i++)
		for (int j=0;j<SizeX;j++)
			Data[i][j]=matr[i][j];
}

CMatr CMatr::operator *(CMatr & matr)
{
	ASSERT(SizeX==matr.SizeY);
	CMatr Matr(SizeY,matr.SizeX);

	for (int i=0;i<SizeY;i++)
		for (int j=0;j<matr.SizeX;j++)
		{
			Matr.Data[i][j]=0;
			for (int k=0;k<SizeX;k++)
				Matr.Data[i][j]+=Data[i][k]*matr.Data[k][j];
		}
	return Matr;
}

CMatr &CMatr::operator =(CMatr & matr)
{
	Clear();
	ReSize(matr.SizeY,matr.SizeX);
	for (int i=0;i<SizeY;i++)
		for (int j=0;j<SizeX;j++)
			Data[i][j]=matr[i][j];

	return *this;
}

void CMatr::SaveToFile(char * name)
{
	fstream OutMatr(name,ios::out);
	OutMatr << "Матрица    " << 
		"[" << SizeY << ";" << 
			SizeX << "]" << endl;
	for (int i=0; i<SizeY;i++)
	{
		for (int j=0;j<SizeX;j++)
		{
			//OutMatr.width(5);
			OutMatr.width(10);
			OutMatr.fill(' ');
			OutMatr.setf(ios::right);
			OutMatr.unsetf(ios::skipws);
			//ios::adjustfield=ios::right;
			double n=Data[i][j];
			OutMatr << (fabs(n)<10E-10?0:n) << "  ";
		}
		OutMatr << endl;
	}
}

void CMatr::CopyDownToUp()
{
	for (int i=0; i<SizeY;i++)
		for (int j=0;j<(i+1);j++)
			Data[j][i]=Data[i][j];
}

CMatr CMatr::GetInvert( int &flag, int iMethod )
{
	ASSERT(SizeX==SizeY);

	if( iMethod == 0 )
	{
		CMatr mC(SizeY,SizeX), mU(SizeY,SizeX), mR(SizeY,SizeX);
		mR.SetIdentity();

		mC=*this;
		flag=mC.SolveSystem(mR,mU);
	
		return mU;
	}
	else
	{
		AlgolMatr temp(SizeY,1,SizeX), inv(SizeY,1,SizeX);
		ConvertToAlgolMatr( temp );//АЛГОЛ версия м-цы

		AlgolMatr a_tmp(SizeY+1,1,SizeX);//м-ца в виде, необходимом для ACCInverse
		int r, c;

		for( r = 1; r <= SizeY; r++ )
			for( c = r; c <= SizeX; c++ )
				a_tmp(r,c) = temp(r,c);

		int l;
		int	res = ACCInverse( a_tmp, l );
		if( (res == 0)||(res == 2) )
		{
			//всё прошло удачно (res==0)
			//или м-ца не уточняется (res==2).
			for( r = 1; r <= SizeY; r++ )
				for( c = 1; c <= r; c++ )
					inv(c,r) = inv(r,c) = a_tmp(r+1,c);

			CMatr InvMatr( SizeY, SizeX );
			InvMatr.ConvertToCMatr( inv );
			flag = 1;
			if( res == 2 )
			{
				//проверяем м-цу на вырождение
				DETERMINANT det;
				AlgolMatr p(SizeY,1,1);
				//ВНИМАНИЕ!!! Ф-ция SymDet делает много лишних операций.
				bool positive = SymDet( temp, p, det );
				//если м-ца всё-таки вырождена меняем флаг
				if( positive == false )	flag = 0;
			}
			return InvMatr;
		}
		else
		{
			//если есть ошибка (м-ца неположительна),
			//то всё равно пытаемся
			//вычислить обратную м-цу старым методом.
			//(это сделано для сохранения преемственности).
			CMatr mC(SizeY,SizeX), mU(SizeY,SizeX), mR(SizeY,SizeX);
			mR.SetIdentity();
	
			mC = *this;
			flag = mC.SolveSystem(mR,mU);
	
			return mU;
		}
	}
}

int CMatr::SolveSystem(CMatr & mR, CMatr & mU)
{
	ASSERT(SizeY==mR.SizeY);
	ASSERT(SizeY==mU.SizeY);
	ASSERT(mU.SizeX==mR.SizeX);

	double Num;

	for(int i=0;i<(SizeY-1);i++)
	{
	  for(int j=SizeY-1;j>i;j--)
	  {
		 if (fabs(Data[j][i]) > 1.0e-20)
		 {
			 if (fabs(Data[j-1][i]) <1.0e-10)
			 {
				 for(int k=i;k<SizeX;k++)
					 Data[j-1][k]+=Data[j][k];
				 for(k=0;k<mR.SizeX;k++)
					 mR[j-1][k]+=mR[j][k];
			 }
			 Num=Data[j][i]/Data[j-1][i];
			 for(int k=i+1;k<SizeX;k++)
				  Data[j][k]-=Num*Data[j-1][k];
			 for(k=0;k<mR.SizeX;k++)
				  mR[j][k]-=Num*mR[j-1][k];
			 Data[j][i]=0;
		 }
	  }
	}
	for (int d=0;d<SizeY;d++)
		if (Data[d][d]==0) return 0;//ВАУ!!! Крутая проверочка double на равенство нулю !!?

	for (int t=0;t<mR.SizeX;t++)
	{
		for (int i=SizeY-1;i>=0;i--)
		{
			mU[i][t]=mR[i][t];
			for (int j=SizeY-1;j>i;j--)
				mU[i][t]-=mU[j][t]*Data[i][j];

			mU[i][t]/=Data[i][i];
		}
	}
	return 1;
}

void CMatr::SetIdentity()
{
	ASSERT(SizeX==SizeY);

	for (int i=0;i<SizeY;i++)
		for (int j=0;j<SizeX;j++)
			Data[i][j]=0;

	for (i=0;i<SizeY;i++)
			Data[i][i]=1;
}


CMatr CMatr::MultOnCol(CMatr & matr, int col)
{
	ASSERT(SizeX==matr.SizeY);

	CMatr RezMatr(SizeY,1);

	for (int i=0;i<SizeY;i++)
		for (int j=0;j<SizeX;j++)
			RezMatr[i][0]+=Data[i][j]*matr[j][col];

	return RezMatr;
}

CMatr CMatr::operator +(CMatr & matr)
{
	ASSERT(SizeY==matr.SizeY);
	ASSERT(SizeX==matr.SizeX);

	CMatr RezM(SizeY,SizeX);

	for (int i=0;i<SizeY;i++)
		for (int j=0;j<SizeX;j++)
			RezM[i][j]=Data[i][j]+matr[i][j];

	return RezM;
}

CMatr CMatr::operator *(double num)
{
	CMatr RezM(SizeY,SizeX);

	for (int i=0;i<SizeX;i++)
		for (int j=0;j<SizeY;j++)
			RezM[j][i]=Data[j][i]*num;

	return RezM;
}

CMatr CMatr::operator -(CMatr & matr)
{
	ASSERT(SizeY==matr.SizeY);
	ASSERT(SizeX==matr.SizeX);

	CMatr RezM(SizeY,SizeX);

	for (int i=0;i<SizeY;i++)
		for (int j=0;j<SizeX;j++)
			RezM[i][j]=Data[i][j]-matr[i][j];

	return RezM;
}

void CMatr::CopyVectTo(CMatr & matr, int num)
{
	ASSERT(SizeY==matr.SizeY);
	ASSERT(num<SizeX);

	for (int i=0;i<SizeY;i++)
		Data[i][num]=matr[i][0];
}

double* CMatr::GetRow(int i)
{
	//ASSERT(i<SizeY);
	if (i>=SizeY) return 0;

	return Data[i];
}

/*
// Приведение Матрицы A к трёхдиагональной форме
// методом элементарных преобразований
CMatr& CMatr::TreeDiagForm()
{
	ASSERT(SizeY==SizeY);

    int i, j, q;
    double tmp;

    double * v = new double[SizeY];

    // Первый ход - приведение исходной матрицы
    // к верхней почти треугольной форме
    for (q = 1; q < SizeX-1; q++)
    {
       // Поиск максимального поддиагонального элемента q-1 столбца
       int MaxElIndex = q;
       for (i = q+1; i < SizeY; i++)
         if (fabs (Data[i][q-1]) > fabs (Data[MaxElIndex][q-1]))
	   MaxElIndex = i;
       //----------------------------------------------------------


       // Переставляем строки матрицы (q и MaxElIndex), если надо
       if (MaxElIndex != q)
       {
           double tmp;
		   for (int i=0;i<SizeX;i++)
		   {
				tmp = Data[MaxElIndex][i];
				Data[MaxElIndex][i] = Data[q][i];
                Data[q][i] = tmp;
		   }
       }//---------------------------------------------------------
       // A -> P * A

       // Проверка возможности продолжения дальнейших вычислений
       if (Data[q][q-1] == 0)
       {
          AfxMessageBox("Матрица вырождена");
          delete v;
		  return *this;
       }//------------------------------------------------------

       // Вектор v на q-ом шаге
       tmp = Data[q][q-1];
       for (i = q+1; i < SizeY; i++)
          v[i] = Data[i][q-1] / tmp;
       //----------------------

       // Умножение N(-v) на (P * A)
       for (i = q+1; i < SizeY; i++)
         for (j = 0; j < SizeX; j++)
           Data[i][j] = Data[i][j] - v[i] * Data[q][j];
       //---------------------------
       // A -> N(-v) * (P * A)

       // Перестановка столбцов, если нужно
       if (MaxElIndex != q)
			 for (int i = 0; i < SizeY; i++)
			 {
				tmp = Data[i][MaxElIndex];
				Data[i][MaxElIndex] = Data[i][q];
				Data[i][q] = tmp;
			 }
       //----------------------------------
       // A -> (N(-v) * (P * A)) * P

       // Умножение ((N(-v) * (P * A)) * P) на N(v)
       for (i = 0; i < SizeY; i++)
         for (j = q+1; j < SizeX; j++)
           Data[i][q] += v[j] * Data[i][j];
       //---------------------------
       // A -> ((N(-v) * (P * A)) * P) * N(v)

    }// конец первого хода

    delete v;
    return *this;
}

CMatr CMatr::QRSolvingEigenProblem()
{
	ASSERT(SizeX==SizeY);	
	
	//CMatr A(SizeY,1);
    int i, j, k;
    int n = SizeY;
    const double eps = pow (2, -24);

    int l = n-1;
    int NonZeroCount;

    char * Is0 = new char[l];

    memset (Is0, 0, l);

	CMatr C(n,n);
	CMatr &H=C;
	CMatr &x=C;
    
	
	//ComplexMatrix * C = new ComplexMatrix (n, n);
    //ComplexMatrix & H = * C;
    //ComplexMatrix & x = * C;
    H = *this;

    CMatr R(n,n);
	CMatr Q(n,n);
	//ComplexMatrix R (n, n);
    //ComplexMatrix Q (n, n);

    double tmp;
	//complex tmp;


    for (i = 0; i < n*100; i++)
    {
       // Сдвиг по Рэлею
       double tau = H[l][l];
	   //Complex tau = H[l][l];

       // Инициализация R значением H
       R = H;
       for (k = 0; k < n; k++) R[k][k] -= tau;

       // Формируем R - правую треугольную матрицу, а также Q
       Q.SetIdentity();
	   //Q.MakeDiag (1.0);
       for (j = 0; j < l; j++)
       {
          if (!Is0[j])
          {
             // Параметры матрицы поворота
             double L = sqrt (pow(R[j][j],2) + pow(R[j+1][j],2));
//             double L = sqrt (qabs(R[j][j]) + qabs(R[j+1][j]));
             double Cos = R[j][j] / L;
             double Sin = R[j+1][j] / L;
//             double Cos = Len (R[j][j]) / L;
//             double Sin = Len (R[j+1][j]) / L;

			double M_PI=acos(-1);

             tmp = R[j][j];
//             tmp = complex (R[j][j].r,   R[j][j].i);
             double ar = (tmp>=0?0:acos(-1));
//             double ar = arg (tmp);
             if (ar > M_PI) ar -=  2.0 * M_PI;
             double f1=cos(- ar);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//             complex f1 (0.0, - ar);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

             tmp = R[j+1][j];
//             tmp = complex (R[j+1][j].r, R[j+1][j].i);
             ar = (tmp>=0?0:acos(-1));
//             ar = arg (tmp);
             if (ar > M_PI) ar -=  2.0 * M_PI;
             double f2 = sin(M_PI - ar);//!!!!!!!!!!!!!!!!!!!!!!!!!
//             complex f2 (0.0, M_PI - ar);//!!!!!!!!!!!!!!!!!!!!!!!!!

             tmp = exp (f1);
//             tmp = exp (f1);
             double a = tmp;
//             Complex a (real (tmp), imag (tmp));
             a*=Cos;

             tmp = exp (f2);
             double b=tmp;
//             Complex b (real (tmp), imag (tmp));
             b*=-Sin;

             tmp = exp (-f2);
             double c = tmp;
//             Complex c (real (tmp), imag (tmp));
             c*=Sin;

             tmp = exp (-f1);
             double d = tmp;
//             Complex d (real (tmp), imag (tmp));
             d*=Cos;

             // Умножение матриц поворота на H слева - получаем R
             for (k = j; k < n; k++)
             {
                double Rjk = R[j][k];
                double Rj1k = R[j+1][k];
//                Complex Rjk = R[j][k];
//                Complex Rj1k = R[j+1][k];

                R[j][k]   = a * Rjk + b * Rj1k;
                R[j+1][k] = c * Rjk + d * Rj1k;
             }

             // Получаем Q
             Q[j+1][j] = b;
             Q[j+1][j+1] = d;
             for (k = 0; k < j+1; k++)
             {
                double Qkj = Q[k][j];
//                Complex Qkj = Q[k][j];
                Q[k][j] = a * Qkj;
                Q[k][j+1] = c * Qkj;
             }
          }
       }
       H = R * Q;
       for (k = 0; k < n; k++) H[k][k] += tau;
       NonZeroCount = 0;
       for (j = 0; j < l; j++)
         if (fabs(H[j+1][j]) < (fabs (H[j][j]) + fabs (H[j+1][j+1])) * eps)
         {
            // нулевой поддиагональный элемент!
            Is0[j] = 1;
	 }
         else
         {
            Is0[j] = 0;
            NonZeroCount++;
         }
       if (! NonZeroCount) break;
    }
//    cout << i << endl;
    *this = H;

    for (i = 0; i < n; i++)
    {
      for (j = i+1; j < n; j++)
        x[j][i] = 0.0;
      x[i][i] = 1.0;
    }

    for (i = 0; i < n; i++)
      for (j = i-1; j >= 0; j--)
      {
        double s = 0.0;
//        Complex s = 0.0;
        for (k = j+1; k <= i; k++)
          s+=Data[j][k]*x[k][i];
        x[j][i] = - s / (Data[j][j] - Data[i][i]);
      }

    return H;
}*/

int CMatr::Eigen(CMatr * T)
{
	int n=SizeY;
	BOOL mark=false;
	BOOL left=false;
	BOOL right=false;

	if (T)
	{
		right=true;
		T->SetIdentity();
	}
	double ep=1E-20;
	double eps=sqrt(ep);

	int nless_1=n-1;
	for (int it=0;it<55;it++)
	{
		if (mark) return it;

		for (int i=0;i<nless_1;i++)
		{
			double aii=Data[i][i];
			for (int j=i+1;j<n;j++)
			{
				double aij=Data[i][j];
				double aji=Data[j][i];

				if ( (fabs(aij+aji)>eps)||(fabs(aii-Data[j][j])>eps) )
				{
					mark=true;
					for (int k=0;k<nless_1;k++)
						for (int m=k+1;m<n;m++)
						{
							double h=0;
							double g=0;
							double hj=0;
							double yh=0;
							for (int i=0;i<n;i++)
							{
								double aik=Data[i][k];
								double aim=Data[i][m];
								double te=aik*aik;
								double tee=aim*aim;
								yh+=te-tee;
								if ((i!=k)&&(i!=m))
								{
									double aki=Data[k][i];
									double ami=Data[m][i];
									h+=aki*ami-aik*aim;
									double tep=te+ami*ami;
									double tem=tee+aki*aki;
									g+=tep+tem;
									hj=hj-tep+tem;
								}
							}
							h*=2;
							double d=Data[k][k]-Data[m][m];
							double akm=Data[k][m];
							double amk=Data[m][k];
							double c=akm+amk;
							double e=akm-amk;
							double cx,sx;
							if (fabs(c)<=ep)
							{
								cx=1;
								sx=0;
							}
							else
							{
								double cot2x=d/c;
								double sig=(cot2x<0?-1:1);
								double cotx=cot2x+(sig*sqrt(1+cot2x*cot2x));
								sx=sig/sqrt(1+cotx*cotx);
								cx=sx*cotx;
							}
							if (yh<0) { double tem=cx; cx=sx; sx=-tem; }
							double cos2x=cx*cx-sx*sx;
							double sin2x=2*sx*cx;
							d=d*cos2x+c*sin2x;
							h=h*cos2x-hj*sin2x;
							double den=g+2*(e*e+d*d);
							double tanhy=(e*d-h/2.0)/den;
							double chy, shy;
							if (fabs(tanhy)<=ep)  {	chy=1;   shy=0;	}
							else
							{
								chy=1.0/sqrt(1-tanhy*tanhy);
								shy=chy*tanhy;
							}
							double c1=chy*cx-shy*sx;
							double c2=chy*cx+shy*sx;
							double s1=chy*sx+shy*cx;
							double s2=-chy*sx+shy*cx;
							if ( (fabs(s1)>ep)||(fabs(s2)>ep) )
							{
								mark=false;
								for (int i=0;i<n;i++)
								{
									double aki=Data[k][i];
									double ami=Data[m][i];
									Data[k][i]=c1*aki+s1*ami;
									Data[m][i]=s2*aki+c2*ami;
									if (left)
									{
										double tki=(*T)[k][i];
										double tmi=(*T)[m][i];
										(*T)[k][i]=c1*tki+s1*tmi;
										(*T)[m][i]=s2*tki+c2*tmi;
									}
								}
								for (i=0;i<n;i++)
								{
									double aik=Data[i][k];
									double aim=Data[i][m];
									Data[i][k]=c2*aik-s2*aim;
									Data[i][m]=-s1*aik+c1*aim;
									if (right)
									{
										double tik=(*T)[i][k];
										double tim=(*T)[i][m];
										(*T)[i][k]=c2*tik-s2*tim;
										(*T)[i][m]=-s1*tik+c1*tim;
									}
								}
							}

						}


				}
			}
			////////////////////////////////////////

			////////////////////////////////////////

		}

	}
	return -1;
}

int CMatr::Eigen_QR(CMatr * T)
{
	double tol=1E-10;
	
	//Преобразование к трехдиагональному виду
	CMatr z(SizeY, SizeX);
	
	double *e=new double [SizeY];
	double *d=new double [SizeY];
	
	for (int i=0;i<SizeY;i++)
		for (int j=0;j<=i;j++) z[i][j]=Data[i][j];

	for (i=SizeY-1;i>=1;i--)
	{
		int l=i-2;
		double f=z[i][i-1];
		double g=0;
		for (int k=0;k<=l;k++)
			g+=z[i][k]*z[i][k];
		double h=g+f*f;
		if (g<tol)
		{
			e[i]=f;		
			h=0;
			d[i]=h;
			continue;
		}
		l+=1;
		g=e[i]=(f>=0?-sqrt(h):sqrt(h));
		h-=f*g;
		z[i][i-1]=f-g;
		f=0;
		for (int j=0;j<=l;j++)
		{
			z[j][i]=z[i][j]/h;
			g=0;
			for (int k=0;k<=j;k++)	g+=z[j][k]*z[i][k];
			for (k=j+1;k<=l;k++)	g+=z[k][j]*z[i][k];
			e[j]=g/h;
			f+=g*z[j][i];
		}
		double hh=f/(h+h);
		for(j=0;j<=l;j++)
		{
			f=z[i][j];
			g=e[j]=e[j]-hh*f;
			for (int k=0;k<=j;k++)
				z[j][k]-=f*e[k]+g*z[i][k];
		}
		d[i]=h;
	}
	d[0]=e[0]=0;
	for (i=0;i<SizeY;i++)
	{
		double l=i-1;
		if (d[i]!=0)
			for (int j=0;j<=l;j++)
			{
				double g=0;
				for (int k=0;k<=l;k++) g+=z[i][k]*z[k][j];
				for (k=0;k<=l;k++) z[k][j]-=g*z[k][i];
			}
		d[i]=z[i][i];
		z[i][i]=1;
		for (int j=0;j<=l;j++)
		{
			z[i][j]=z[j][i]=0;
		}
	}

	//Преобразование к трехдиагональному виду закончено

	delete [] d;
	delete [] e;

	return 0;
}

void CMatr::ConvertToAlgolMatr( AlgolMatr &AM )
{
	AlgolMatr temp( SizeY, 1, SizeX );
	for( int r = 1; r <= SizeY; r++ )
	{
		for( int c = 1; c <= SizeX; c++ )
		{
			temp(r,c) = Data[r-1][c-1];
		}
	}
	AM = temp;
}
void CMatr::ConvertToCMatr( AlgolMatr AM )
{
	int rows = (int)AM.GetRow(), cols = AM.GetWidth();
	Clear();
	ReSize( rows, cols );
	for( int r = 0; r < SizeY; r++ )
	{
		for( int c = 0; c < SizeX; c++ )
		{
			Data[r][c] = AM(r+1,c+1);
		}
	}
}

int CMatr::GetEigenVecs( CMatr &M, EV_METHOD EVm )
{
	int n = SizeY;

	ASSERT( SizeX == n );

	AlgolMatr A(n,1,n), vecs(n,1,n), wr(n,1,1), wi(n,1,1);
	ConvertToAlgolMatr( A );

	int low = 1, hi = n;
	int *cnt, *inter;

	cnt = new int[n];
	inter = new int[n];

	AlgolMatr d(n,1,1);

	Balance( A, d, low, hi );
	if( low > hi )	
	{
		delete [] cnt;
		delete [] inter;
		return -1;
	}

	switch( EVm )
	{
	case EVM_QR_ELM:
		ElmHes( low, hi, A, inter );
		ElmTrans( low, hi, inter, A, vecs );
		break;
	case EVM_QR_DIR:
		DirHes( low, hi, A, inter );
		DirTrans( low, hi, inter, A, vecs );
		break;
	case EVM_QR_ORT:
		{
			AlgolMatr d_ort(n,1,1);
			OrtHes( low, hi, A, d_ort );
			OrtTrans( low, hi, A, d_ort, vecs );
		}
		break;
	default:
		ElmHes( low, hi, A, inter );
		ElmTrans( low, hi, inter, A, vecs );
		break;
	}

	int maxiter = 30;
	AlgolMatr H, wr_temp, wi_temp, vecs_temp;
	H = A;
	wr_temp = wr;
	wi_temp = wi;
	vecs_temp = vecs;
	for(;;)
	{
		try
		{
			HQR2( low, hi, H, vecs_temp, wr_temp, wi_temp, cnt, maxiter );
		}
		catch( EV_EXCEPT ex )
		{
			if( ex != EVE_NOERR )
			{
				H = A;
				wr_temp = wr;
				wi_temp = wi;
				vecs_temp = vecs;	
				if( maxiter >= 30000 )
				{
					delete [] cnt;
					delete [] inter;
					return -1;
				}
				maxiter *= 2;
				continue;
			}
		}
		wr = wr_temp;
		wi = wi_temp;
		vecs = vecs_temp;
		break;
	}

	//проверяем полученные собств.значения
	for( int r = 1; r <= n; r++ )
	{
		if( fabs(wi(r,1)) >= ZERO )
		{
			delete [] cnt;
			delete [] inter;
			return -1;
		}
//		if( wr(r,1) < 0.0 )	return -1;
	}

	BalBack( low, hi, d, vecs );

	ClearData();
	for( r = 0; r < n; r++ )
	{
		Data[r][r] = wr(r+1,1);
	}
	M.ConvertToCMatr( vecs );

	delete [] cnt;
	delete [] inter;

	return 1;
}

/*
	Нахождение собственных значений и векторов для действительных
	несимметричных плотных матриц.
	Из книги
		Уилкинсон, Райнш
		"Справочник алгоритмов на языке АЛГОЛ. Линейная алгебра."
*/

/*
	Реализован QR-алгоритм и метод Якоби.
	Приведение исходной м-цы к форме Хессенберга ( ElmHes-ElmTrans, OrtHes-OrtTrans или DirHes-DirTrans )
	с последующим применением HQR2.
	Если предварительно использовалась Balance, то собств.векторы исходной
	м-цы востанавливаются BalBack.
		Преимущества ElmHes проявляются в полной мере, когда A имеет нулевые эл-ты 
	и если она является очень редкой, то только эту процедуру и следует применять.
		В DirHes реализовано накопление скалярного произведения при приведении к форме Хессенберга,
	поэтому влияние ошибок округления в этом случае минимально.	Преимущества особо ощутимы при работе
	с м-цами высокого порядка, но на некоторых машинах операция накопления ск.произв. неэффективна
	( это замечание существенно с точки зрения 1976 года !!! )
	и время, затрачиваемое на DirHes, оказывается недопустимо большим.
		Преимущество процедуры OrtHes в том, что она сохраняет числа обусловленности
	отдельных собственных значений неизменными, поэтому её можно использовать
	при изучении числовых св-в м-цы. Но объём вычислений здесь вдвое больше 
	по сравнению с процедурами DirHes и ElmHes, поэтому её не следует использовать
	как процедуру общего назначения.
		HQR2 очень экономно использует память.
	Рекомендованные последовательности вычислений:
	1:	Balance - ElmHes - ElmTrans - HQR2 - BalBack
	2:	Balance - DirHes - DirTrans - HQR2 - BalBack
	3:	Balance - OrtHes - OrtTrans - HQR2 - BalBack
*/
void CDiv( double xr, double xi, double yr, double yi, double &zr, double &zi )
{
/*
	операция комплексного деления
	zr + i*zi = (xr + i*xi)/(yr + i*yi);
	к ф-ции нельзя обращаться, если yr == yi == 0
*/
	ASSERT( !((fabs(yr) <= ZERO)&&(fabs(yi) <= ZERO)) );

	double h;
	if( fabs(yr) > fabs(yi) )
	{
		h = yi/yr;
		yr = h*yi + yr;
		zr = (xr + h*xi)/yr;
		zi = (xi - h*xr)/yr;
	}
	else
	{
		h = yr/yi;
		yi = h*yr + yi;
		zr = (h*xr + xi)/yi;
		zi = (h*xi - xr)/yi;
	}
}

void Balance( AlgolMatr &a, AlgolMatr &d, int &low, int &hi, int base )
{
/*
	понижение нормы м-цы a (n,n) с помощью точного преобразования подобия,
	информация о котором выдаётся в d (n) (перестановки и масштабные коэф-ты).
	base - основание системы счисления в машине с плавающей запятой.
	low, hi - числа, такие что a[i,j]==0, если i > j, и j = 1,...,low-1
	или i = hi+1,...,n.
*/
	int n = a.GetRow();

	ASSERT( base >= 2 );
	ASSERT( n == a.GetWidth() );
	ASSERT( d.GetRow() == n );
	ASSERT( d.GetWidth() == 1 );

	int i, j, k = n, l = 1;
	double b2 = base*base, c, f, g, r, s;
	bool noconv;
	
	//выделение строк, содержащих собств значения, и сдвиг их вниз
	bool L1 = true;
	do
	{
		L1 = false;
		for( j = k; j >= 1; j-- )
		{
			r = 0.0;
			int j1 = j-1;
			for( i = 1; i <= j1; i++ )
				r += fabs( a(j,i) );
			for( i = j+1; i <= k; i++ )
				r += fabs( a(j,i) );
			if( fabs(r) < ZERO )
			{
				//exc
				d(k,1) = j;
				if( j != k )
				{
					for( i = 1; i <= k; i++ )
					{
						f = a(i,j);
						a(i,j) = a(i,k);
						a(i,k) = f;
					}
					for( i = 1; i <= n; i++ )
					{
						f = a(j,i);
						a(j,i) = a(k,i);
						a(k,i) = f;
					}
				}
				//exc
				k--;
				L1 = true;
				break;
			}
		}
	}	while( L1 );
	//выделение столбцов, содержащих собств значения, и сдвиг их влево

	bool L2 = true;
	do
	{
		L2 = false;
		for( j = l; j <= k; j++ )
		{
			c = 0.0;
			int j1 = j-1;
			for( i = l; i <= j1; i++ )
				c += fabs( a(i,j) );
			for( i = j+1; i <= k; i++ )
				c += fabs( a(i,j) );
			if( fabs(c) < ZERO )
			{
				//exc
				d(l,1) = j;
				if( j != l )
				{
					for( i = 1; i <= k; i++ )
					{
						f = a(i,j);
						a(i,j) = a(i,l);
						a(i,l) = f;
					}
					for( i = 1; i <= n; i++ )
					{
						f = a(j,i);
						a(j,i) = a(l,i);
						a(l,i) = f;
					}
				}
				//exc
				l++;
				L2 = true;
				break;
			}
		}
	}	while( L2 );
	//масштабирование подматрицы, размещённой в строках с номерами от l до k
	low = l;
	hi = k;
	for( i = 1; i <= k; i++ )	d(i,1) = 1;

	do
	{
		noconv = false;
		for( i = l; i <= k; i++ )
		{
			c = r = 0.0;
			int i1 = i-1;
			for( j = l; j <= i1; j++ )
			{
				c += fabs( a(j,i) );
				r += fabs( a(i,j) );
			}
			for( j = i+1; j <= k; j++ )
			{
				c += fabs( a(j,i) );
				r += fabs( a(i,j) );
			}

			//вычисление такой степени sig, что
			//sqrt(r/(c*base))<=b^sig<=sqrt(r*base/c)
			g = r/base;
			f = 1.0;
			s = c + r;
			while( c < g )
			{
				f *= base;
				c *= b2;
				if( fabs(c) < ZERO )	break;
			}
			g = r*base;
			while( c >= g )
			{
				f /= base;
				c /= b2;
				if( fabs(c) < ZERO )	break;
			}

			//масштабирование
			if( ((c+r)/f) < (0.95*s) )
			{
				g = 1/f;
				d(i,1) *= f;
				noconv = true;
				for( j = l; j <= n; j++ )
					a(i,j) *= g;
				for( j = 1; j <= k; j++ )
					a(j,i) *= f;
			}
		}

	}	while( noconv );

}

void BalBack( int low, int hi, AlgolMatr d, AlgolMatr &z )
{
/*
	Обратное преобразование правых собств.векторов сбалансированной м-цы
	в собств.векторы исх. м-цы, из которой была получена данная с помощью Balance.
	low, hi, d (n) - выходные пар-ры Balance.
	z (n,m) - собств.векторы (или действительные, или мнимые их части) масштабированной
	м-цы. Сюда заносятся векторы исх.м-цы.
*/
	int n = z.GetRow(), m = z.GetWidth();

	ASSERT( z.GetRow() == n );
	ASSERT( d.GetRow() == n );
	ASSERT( d.GetWidth() == 1 );
	ASSERT( (low>0)&&(low<=n)&&(hi>0)&&(hi<=n) );

	int i, j, k;
	double s;

	for( i = low; i <= hi; i++ )
	{
		s = d(i,1);
		//можно востановить левые векторы если предыдущую строку
		//заменить на s = 1/d(i,1)
		for( j = 1; j <= m; j++ )
			z(i,j) *= s;
	}
	for( i = low-1; i >= 1; i-- )
	{
		k = (int)d(i,1);
		if( k != i )
		{
			for( j = 1; j <= m; j++ )
			{
				s = z(i,j);
				z(i,j) = z(k,j);
				z(k,j) = s;
			}
		}
	}
	for( i = hi+1; i <= n; i++ )
	{
		k = (int)d(i,1);
		if( k != i )
		{
			for( j = 1; j <= m; j++ )
			{
				s = z(i,j);
				z(i,j) = z(k,j);
				z(k,j) = s;
			}
		}
	}
}

void ElmHes( int k, int l, AlgolMatr &a, int *inter )
{
/*
	Приведение произвольной м-цы a (n,n) к форме Хессенберга с помощью элементарных
	неортогональных преобразований.
	Приведение к форме Хессенберга подматрицу порядка (l-k+1),
	первый эл-т которой есть a[k,k], а последний - a[l,l].
	Информация о перестановках записана в оставшейся части массива a и inter(k:l).
	( inter - номера переставленных строк и столбцов ).
	k, l (и обычно a(n,n)) - выходные пар-ры Balance.
	Если м-ца a не масштабируется, то k = 1, l = n.
*/
	int n = a.GetRow();

	ASSERT( (k>0)&&(k<=n)&&(l>0)&&(l<=n) );
	ASSERT( n == a.GetWidth() );
	ASSERT( inter );

	int i, j, la = l-1, m;
	double x, y;

	for( m = k+1; m <= la; m++ )
	{
		i = m;
		x = 0.0;
		for( j = m; j <= l; j++ )
		{
			if( fabs(a(j,m-1)) > fabs(x) )
			{
				x = a(j,m-1);
				i = j;
			}
		}
		inter[m-1] = i;

		if( i != m )
		{
			//перестановка строк и столбцов массива a
			for( j = m-1; j <= n; j++ )
			{
				y = a(i,j);
				a(i,j) = a(m,j);
				a(m,j) = y;
			}
			for( j = 1; j <= l; j++ )
			{
				y = a(j,i);
				a(j,i) = a(j,m);
				a(j,m) = y;
			}
		}

		if( fabs(x) >= ZERO )
		{
			for( i = m+1; i <= l; i++ )
			{
				y = a(i,m-1);
				if( fabs(y) >= ZERO )
				{
					y = a(i,m-1) = y/x;
					for( j = m; j <= n; j++ )
						a(i,j) -= y*a(m,j);
					for( j = 1; j <= l; j++ )
						a(j,m) += y*a(j,i);
				}
			}
		}
	}//m
}

void DirHes( int k, int l, AlgolMatr &a, int *inter )
{
/*
	Приведение произвольной м-цы a (n,n) к форме Хессенберга согласно соотношению AN=NH.
	H размещена в части a, а N в оставшейся части.
	Приведение к форме Хессенберга подматрицы порядка (l-k+1),
	первый эл-т которой есть a[k,k], а последний - a[l,l].
	Информация о перестановках записана в оставшейся части массива a и inter(k:l).
	( inter - номера переставленных строк и столбцов ).
	k, l (и обычно a(n,n)) - выходные пар-ры Balance.
	Если м-ца a не масштабируется, то k = 1, l = n.
	Использована процедура накопления скалярного произведения с повышенной точностью.
*/

	int n = a.GetRow();

	ASSERT( (k>0)&&(k<=n)&&(l>0)&&(l<=n) );
	ASSERT( n == a.GetWidth() );
	ASSERT( inter );

	int i, j, m;
	double x, y, z;

	for( j = k+1; j <= l; j++ )
	{
		m = j;
		x = 0.0;
		for( i = j; i <= l; i++ )
		{
			if( fabs(a(i,j-1)) > fabs(x) )
			{
				x = a(i,j-1);
				m = i;
			}
		}
		inter[j-1] = m;

		if( m != j )
		{
			//перестановка строк и столбцов массива a
			for( i = k; i <= n; i++ )
			{
				y = a(m,i);
				a(m,i) = a(j,i);
				a(j,i) = y;
			}
			for( i = 1; i <= l; i++ )
			{
				y = a(i,m);
				a(i,m) = a(i,j);
				a(i,j) = y;
			}
		}

		if( fabs(x) >= ZERO )
		{
			for( i = j+1; i <= l; i++ )
				a(i,j-1) /= x;
		}

		for( i = 1; i <= l; i++ )
		{
			y = a(i,j);
			if( fabs(x) >= ZERO )
			{
				//innerprod:
				long double s1s2 = (long double)(y);
				for( m = j+1; m <= l; m++ )
					s1s2 += (long double)a(i,m)*(long double)a(m,j-1);
				y = (double)s1s2;
				z = (double)( s1s2 - (long double)y );
			}
			else
			{
				z = 0.0;
			}
			//innerprod:
			long double s1s2 = (long double)(-y-z);
			int lll = ((i<=j)?(i-1):(j));
			for( m = k+1; m <= lll; m++ )
				s1s2 += (long double)a(i,m-1)*(long double)a(m,j);
			y = (double)s1s2;
			z = (double)( s1s2 - (long double)y );

			a(i,j) = -y;
		}
	}//m
}

void OrtHes( int k, int l, AlgolMatr &a, AlgolMatr &d )
{
/*
	Приведение произвольной м-цы a (n,n) к форме Хессенберга с помощью элементарных 
	ортогональных преобразований.
	H размещена в части a, а информация о м-це преобразования 
	в оставшейся части и векторе d (n).
	Приведение к форме Хессенберга подматрицы порядка (l-k+1),
	первый эл-т которой есть a[k,k], а последний - a[l,l].
	Информация о перестановках записана в оставшейся части массива a и d(k:l).
	( inter - номера переставленных строк и столбцов ).
	k, l (и обычно a(n,n)) - выходные пар-ры Balance.
	Если м-ца a не масштабируется, то k = 1, l = n.
	Преимущество процедуры в том, что она сохраняет числа обусловленности
	отдельных собственных значений неизменными, поэтому её можно
	использовать при изучении числовых св-в м-цы. Но объём вычислений
	здесь вдвое больше по сравнению с процедурами DirHes и ElmHes,
	поэтому её не следует использовать как процедуру общего назначения.
*/
	int n = a.GetRow();

	ASSERT( (k>0)&&(k<=n)&&(l>0)&&(l<=n) );
	ASSERT( (n==a.GetWidth())&&(d.GetMinCol()==1)&&(d.GetRow()==n) );

	int i, j, m, la = l - 1;
	double f, g, h;

	for( m = k+1; m <= la; m++ )
	{
		h = 0.0;
		for( i = l; i >= m; i-- )
		{
			f = d(i,1) = a(i,m-1);
			h += f*f;
		}
		if( h <= TOL )
		{
			g = 0.0;
		}
		else
		{
			g = (f>=ZERO)?(-sqrt(h)):(sqrt(h));
			h -= f*g;
			d(m,1) = f - g;
			//формирование м-цы (I-(u*u`)/h)*a, где u` - транспонирование.
			for( j = m; j <= n; j++ )
			{
				f = 0.0;
				for( i = l; i >= m; i-- )
					f += d(i,1)*a(i,j);
				f /= h;
				for( i = m; i <= l; i++ )
					a(i,j) -= f*d(i,1);
			}
			//формирование м-цы (I-(u*u`)/h)*a*(I-(u*u`)/h), где u` - транспонирование.
			for( i = 1; i <= l; i++ )
			{
				f = 0.0;
				for( j = l; j >= m; j-- )
					f += d(j,1)*a(i,j);
				f /= h;
				for( j = m; j <= l; j++ )
					a(i,j) -= f*d(j,1);
			}
		}
//skip:
		a(m,m-1) = g;
	}//m
}

void ElmTrans( int low, int upp, int *inter, AlgolMatr h, AlgolMatr &v )
{
/*
	формирование м-цы преобразования подобия от A к H в массиве v (n,n) на основании информации,
	полученной в ElmHes в массиве h (n,n) и inter (n).
	low, upp - выходные пар-ры Balance, иначе low = 1, upp = n.
*/
	int n = h.GetRow();

	ASSERT( (low>0)&&(low<=n)&&(upp>0)&&(upp<=n) );
	ASSERT( n == h.GetWidth() );
	ASSERT( inter );
	ASSERT( v.GetRow() == n );
	ASSERT( v.GetWidth() == n );

	int i, j, k;

	for( i = 1; i <= n; i++ )
	{
		for( j = 1; j <= n; j++ )	v(i,j) = 0.0;
		v(i,i) = 1.0;
	}

	int low1 = low + 1;
	for( i = upp-1; i >= low1; i-- )
	{
		j = inter[i-1];
		for( k = i+1; k <= upp; k++ )	v(k,i) = h(k,i-1);
		if( i != j )
		{
			for( k = i; k <= upp; k++ )
			{
				v(i,k) = v(j,k);
				v(j,k) = 0.0;
			}
			v(j,i) = 1.0;
		}//i!=j
	}
}

void DirTrans( int low, int upp, int *inter, AlgolMatr h, AlgolMatr &v )
{
/*
	формирование м-цы преобразования подобия от A к H в массиве v (n,n) на основании информации,
	полученной в DirHes в массиве h (n,n) и inter (n).
	low, upp - выходные пар-ры Balance, иначе low = 1, upp = n.
*/

	int n = h.GetRow();

	ASSERT( (low>0)&&(low<=n)&&(upp>0)&&(upp<=n) );
	ASSERT( n == h.GetWidth() );
	ASSERT( inter );
	ASSERT( v.GetRow() == n );
	ASSERT( v.GetWidth() == n );

	int i, j, m;
	double x;

	for( i = 1; i <= n; i++ )
	{
		for( j = 1; j <= n; j++ )	v(i,j) = 0.0;
		v(i,i) = 1.0;
	}

	int low1 = low + 1;
	for( i = upp; i >= low1; i-- )
	{
		int im1 = i - 1;
		for( j = low1; j <= im1; j++ )	v(i,j) = h(i,j-1);
		m = inter[i-1];
		if( m != i )
		{
			for( j = low1; j <= upp; j++ )
			{
				x = v(m,j);
				v(m,j) = v(i,j);
				v(i,j) = x;
			}
		}//i!=j
	}
}

void OrtTrans( int low, int upp, AlgolMatr h, AlgolMatr d, AlgolMatr &v )
{
/*
	формирование м-цы преобразования подобия от A к H в массиве v (n,n) на основании информации,
	полученной в OrtHes в массиве h (n,n) и d (n).
	low, upp - выходные пар-ры Balance, иначе low = 1, upp = n.
*/
	int n = h.GetRow();

	ASSERT( (low>0)&&(low<=n)&&(upp>0)&&(upp<=n) );
	ASSERT( (n==h.GetWidth())&&(d.GetMinCol()==1)&&(d.GetRow()==n)&&(v.GetRow()==n)&&(v.GetWidth()==n) );

	int i, j, k, m;
	double x, y;

	for( i = 1; i <= n; i++ )
	{
		for( j = 1; j <= n; j++ )	v(i,j) = 0.0;
		v(i,i) = 1.0;
	}

	for( k = upp-2; k >= low; k-- )
	{
		m = k + 1;
		y = h(m,k);
		if( fabs(y) <= ZERO )	continue;
		y *= d(m,1);
		for( i = k+2; i <= upp; i++ )	d(i,1) = h(i,k);
		for( j = m; j <= upp; j++ )
		{
			x = 0.0;
			for( i = m; i <= upp; i++ )
				x += d(i,1)*v(i,j);
			x /= y;
			for( i = m; i <= upp; i++ )
				v(i,j) += x*d(i,1);
		}
//skip:
	}
}

void HQR2( int low, int upp, AlgolMatr &h, AlgolMatr &vecs, 
		  AlgolMatr &wr, AlgolMatr &wi, int *cnt, int maxiter )
{
/*
	Определение собств.значений и собств.векторов действительной м-цы,
	приведённой к верхней форме Хессенберга h (n,n). Соответствующая м-ца
	преобразования записана в vecs(n,n).
	Действительная и мнимая части собств.значений формируются в wr(n) и wi (n),
	а ненормированные собств.векторы в vecs. Действительному собств.значению соотвествует один столбец.
	cnt (n) - фиксирует число итераций, затраченных для вычисления собств значений.
	Если два собств.значения найдены одновременно(парой), то число итераций записано с положительным знаком
	для первого и с отрицательным для второго собств.значения.
	Комплексно-сопряжённым значениям (lambda[+/-]i*mu) соответствуют два соседних столбца a,b м-цы .
	В верхней части h размещены собств.векторы квазитреугольной м-цы, вычисленной по QR-алгоритму.
	При этом (a[+/-]i*b)- векторы, соответствующие (lambda[+/-]i*mu).
	low, upp - выходные пар-ры Balance иначе low = 1, upp = n.
	Собств.значения являются диагональными эл-ми строк с 1 по low-1 и с upp+1 по n.
	Если для отыскания собств.значений необходимо более maxiter итераций,
	то возбуждается исключение EVE_NOSOLUT.
*/
	int n = h.GetRow();

//	ВНИМАНИЕ:	ф-ция неправильно считает собств.векторы
//				для соответствующих комплексных собств.значений
	ASSERT( (low>0)&&(low<=n)&&(upp>0)&&(upp<=n) );
	ASSERT( n == h.GetWidth() );
	ASSERT( cnt );
	ASSERT( maxiter > 0 );
	ASSERT( vecs.GetRow() == n );
	ASSERT( vecs.GetWidth() == n );
	ASSERT( wr.GetRow() == n );
	ASSERT( wr.GetWidth() == 1 );
	ASSERT( wi.GetRow() == n );
	ASSERT( wi.GetWidth() == 1 );

	int i, j, k, l, m, na, its, en;
	double p, q, r, s, t, w, x, y, z, ra, sa, vr, vi, norm;
	bool notlast;

	int low1 = low - 1;
	for( i = 1; i <= low1; i++ )
	{
		wr(i,1) = h(i,i);
		wi(i,1) = 0.0;
		cnt[i-1] = 0;
	}
	for( i = upp+1; i <= n; i++ )
	{
		wr(i,1) = h(i,i);
		wi(i,1) = 0.0;
		cnt[i-1] = 0;
	}
	en = upp;
	t = 0.0;

	for(;;)
	{
//nextw:
		if( en < low )	break;
		its = 0;
		na = en - 1;
		for(;;)
		{
			//выделение единственного малого поддиагонального элемента
//nextit:
			bool is = false;
			int low1 = low + 1;
			for( l = en; l >= low1; l-- )
			{
				int l1 = l - 1;
				if( fabs(h(l,l1)) <= ( MACHEPS*( fabs(h(l1,l1))+fabs(h(l,l)) ) ) )
				{
					is = true;
					break;
				}
			}
			if( !is )	l = low;
//cont1:
			x = h(en,en);

			if( l == en )
			{
				//определение единственного собств.значения
//onew:
				wr(en,1) = h(en,en) = x + t;
				wi(en,1) = 0.0;
				cnt[en-1] = its;
				en = na;
				break;
			}
	
			y = h(na,na);
			w = h(en,na)*h(na,en);

			if( l == na )
			{
				//определение пары собств.значений
//twow:
				p = (y - x)/2;
				q = p*p + w;
				z = sqrt(fabs(q));
				x = h(en,en) = x + t;
				h(na,na) = y + t;
				cnt[en-1] = -its;
				cnt[na-1] = its;

				if( q > 0.0 )
				{
					//действительная пара
					z = (p<0.0)?(p-z):(p+z);
					wr(na,1) = x + z;
					wr(en,1) = s = x - w/z;
					wi(na,1) = wi(en,1) = 0.0;
					x = h(en,na);
					r = sqrt(x*x+z*z);
					p = x/r;
					q = z/r;
					//изменение строк
					for( j = na; j <= n; j++ )
					{
						z = h(na,j);
						h(na,j) = q*z + p*h(en,j);
						h(en,j) = q*h(en,j) - p*z;
					}
					//изменение столбцов
					for( i = 1; i <= en; i++ )
					{
						z = h(i,na);
						h(i,na) = q*z + p*h(i,en);
						h(i,en) = q*h(i,en) - p*z;
					}
					//накопление преобразований
					for( i = low; i <= upp; i++ )
					{
						z = vecs(i,na);
						vecs(i,na) = q*z + p*vecs(i,en);
						vecs(i,en) = q*vecs(i,en) - p*z;
					}
				}
				else
				{
					//комплексная пара
					wr(na,1) = wr(en,1) = x + p;
					wi(na,1) = z;
					wi(en,1) = -z;
				}
				en -= 2;
				break;
			}

			if( its == maxiter )
			{
				cnt[en-1] = maxiter + 1;
				throw EVE_NOSOLUT;
			}

			if( (its>0)&&((its%10) == 0) )
			{
				//формирование дополнительного сдвига
				t += x;
				for( i = low; i <= en; i++ )
					h(i,i) -= x;
				s = fabs(h(en,na)) + fabs(h(na,en-2));
				x = y = 0.75*s;
				w = 0.4375*s*s;
			}

			its++;

			for( m = en-2; m >= l; m-- )
			{
				//выделение двух последовательных малых поддиагональных эл-ов
				z = h(m,m);
				r = x - z;
				s = y - z;
				int m1 = m + 1;
				p = (r*s - w)/h(m1,m) + h(m,m1);
				q = h(m1,m1) - z - r - s;
				r = h(m+2,m1);
				s = fabs(p) + fabs(q) + fabs(r);
				p /= s;
				q /= s;
				r /= s;
				if( m == l )	break;
				int mm1 = m - 1;
				if( (fabs(h(m,mm1))*(fabs(q)+fabs(r))) <= 
					( MACHEPS*fabs(p)*( fabs(h(mm1,mm1))+fabs(z)+fabs(h(m1,m1)) ) ))
					break;
			}
//cont2:
			for( i = m+2; i <= en; i++ )	h(i,i-2) = 0.0;
			for( i = m+3; i <= en; i++ )	h(i,i-3) = 0.0;
			//двойной шаг QR-алгоритма для строк с номерами от l до en
			//и столбцов с номерами от m до en всего массива
			for( k = m; k <= na; k++ )
			{
				notlast = (k!=na);
				int km1 = k - 1, kp1 = k + 1, kp2 = k + 2;
				if( k != m )
				{
					p = h(k,km1);
					q = h(kp1,km1);
					r = (notlast)?(h(kp2,km1)):(0.0);
					x = fabs(p) + fabs(q) + fabs(r);
					if( fabs(x) < ZERO )	continue;
					p /= x;
					q /= x;
					r /= x;
				}
				s = sqrt(p*p+q*q+r*r);
				if( p < 0.0 )	s = -s;
				if( k != m )	h(k,km1) = -s*x;
				else	if( l != m )	h(k,km1) = -h(k,km1);
				p += s;
				x = p/s;
				y = q/s;
				z = r/s;
				q /= p;
				r /= p;
				//изменение строк
				for( j = k; j <= n; j++ )
				{
					p = h(k,j) + q*h(kp1,j);
					if( notlast )
					{
						p += r*h(kp2,j);
						h(kp2,j) -= p*z;
					}
					h(kp1,j) -= p*y;
					h(k,j) -= p*x;
				}
				int kp3 = k + 3;
				j = ( (kp3)<en )?(kp3):(en);
				//изменение столбцов
				for( i = 1; i <= j; i++ )
				{
					p = x*h(i,k) + y*h(i,kp1);
					if( notlast )
					{
						p += z*h(i,kp2);
						h(i,kp2) -= p*r;
					}
					h(i,kp1) -= p*q;
					h(i,k) -= p;
				}
				//накопление преобразований
				for( i = low; i <= upp; i++ )
				{
					p = x*vecs(i,k) + y*vecs(i,kp1);
					if( notlast )
					{
						p += z*vecs(i,kp2);
						vecs(i,kp2) -= p*r;
					}
					vecs(i,kp1) -= p*q;
					vecs(i,k) -= p;
				}
//cont3:
			}//for(k = m)
		}//for(;;)
	}//for(;;)

	//все собств.значения найденны.
	//теперь выполняется обратная подстановка.
//fin:
	norm = 0.0;
	k = 1;
	for( i = 1; i <= n; i++ )
	{
		for( j = k; j <= n; j++ )	norm += fabs(h(i,j));
		k = i;
	}
	//обратная подстановка
	for( en = n; en >= 1; en-- )
	{
		p = wr(en,1);
		q = wi(en,1);
		na = en - 1;

		if( fabs(q) < ZERO )
		{
			//вычисление действительного вектора
			m = en;
			h(en,en) = 1.0;
			for( i = na; i >= 1; i-- )
			{
				w = h(i,i) - p;
				r = h(i,en);
				for( j = m; j <= na; j++ )
					r += h(i,j)*h(j,en);
				if( wi(i,1) < 0.0 )
				{
					z = w;
					s = r;
				}
				else
				{
					m = i;
					if( fabs(wi(i,1)) < ZERO )
					{
						h(i,en) = -r/((fabs(w)>=ZERO)?(w):(MACHEPS*norm));
					}
					else
					{
						//решение системы ур-ий
						/*
							{w*h(i,en) + x*h(i+1,en) = -r;
							{y*h(i,en) + z*h(i+1,en) = -s;
						*/
						int ip1 = i + 1;
						x = h(i,ip1);
						y = h(ip1,i);
						double temp1 = wr(i,1), temp2 = temp1 - p, wii = wi(i,1);
						q = temp2*temp2 + wii*wii;
						h(i,en) = t = (x*s-z*r)/q;
						h(ip1,en) = (fabs(x)>fabs(z))?( (-r-w*t)/x ):( (-s-y*t)/z );
					}
				}
			}
		}
		else
		{
			if( q < 0.0 )
			{
				//вычисление компл.вектора, соответсвующего
				//собств.значению lambda = p - i*q; q < 0;
				m  = na;
				if( fabs(h(en,na)) > fabs(h(na,en)) )
				{
					h(na,na) = -(h(en,en)-p)/h(en,na);
					h(na,en) = -q/h(en,na);
				}
				else
				{
					CDiv(-h(na,en), 0.0, h(na,na)-p, q, h(na,na), h(na,en));
				}
				h(en,na) = 1.0;
				h(en,en) = 0.0;
				for( i = na-1; i >= 1; i-- )
				{
					w = h(i,i) - p;
					ra = h(i,en);
					sa = 0.0;
					for( j = m; j <= na; j++ )
					{
						double hij = h(i,j);
						ra += hij*h(j,na);
						sa += hij*h(j,en);
					}
					if( wi(i,1) < 0.0 )
					{
						z = w;
						r = ra;
						s = sa;
					}
					else
					{
						m = i;
						if( fabs(wi(i,1)) < ZERO )
						{
							CDiv( -ra, -sa, w, q, h(i,na), h(i,en) );
						}
						else
						{
							//решение системы ур-ий
							/*
								{(w+q*i)*(h(i,na)+h(i,en)*i) + x*(h(i+1,na)+h(i+1,en)*i) = -ra-sa*i;
								{y*(h(i,na)+h(i,en)*i) + (z+q*i)*(h(i+1,na)+h(i+1,en)*i) = -r-s*i;
							*/
							int ip1 = i + 1;
							x = h(i,ip1);
							y = h(ip1,i);
							double wri = wr(i,1), temp = wri - p, wii = wi(i,1);
							vr = temp*temp + wii*wii - q*q;
							vi = temp*2.0*q;
							if( (fabs(vr)<ZERO)&&(fabs(vi)<ZERO) )
								vr = MACHEPS*norm*(fabs(w)+fabs(q)+fabs(x)+fabs(y)+fabs(z));

							CDiv( x*r-z*ra+q*sa, x*s-z*sa-q*ra, vr, vi, h(i,na), h(i,en) );

							if( fabs(x) > (fabs(z)+fabs(q)) )
							{
								h(ip1,na) = (-ra-w*h(i,na)+q*h(i,en))/x;
								h(ip1,en) = (-sa-w*h(i,en)-q*h(i,na))/x;
							}
							else
							{
								CDiv(-r-y*h(i,na), -s-y*h(i,en), z, q, h(ip1,na), h(ip1,en) );
							}
						}
					}
				}//for(i)
			}//if(q<0)
		}
	}//обратная подстановка

	//вычисление собственных векторов для изолированных собств.значений
	low1 = low - 1;
	for( i = 1; i <= low1; i++ )
		for( j = i+1; j <= n; j++ )
			vecs(i,j) = h(i,j);
	for( i = upp+1; i <= n; i++ )
		for( j = i+1; j <= n; j++ )
			vecs(i,j) = h(i,j);

	//умножение на матрицу преобразования для получения 
	//собств.векторов исходной матрицы:
	for( j = n; j >= low; j-- )
	{
		m = (j<=upp)?(j):(upp);
		l = j - 1;
		if( wi(j,1) < 0.0 )
		{
			for( i = low; i <= upp; i++ )
			{
				y = z = 0.0;
				for( k = low; k <= m; k++ )
				{
					double tmp = vecs(i,k);
					y += tmp*h(k,l);
					z += tmp*h(k,j);
				}
				vecs(i,l) = y;
				vecs(i,j) = z;
			}
		}
		else
		{
			if( fabs(wi(j,1)) < ZERO )
			{
				for( i = low; i <= upp; i++ )
				{
					z = 0.0;
					for( k = low; k <= m; k++ )
						z += vecs(i,k)*h(k,j);
					vecs(i,j) = z;
				}
			}
		}
	}//j=n;
}

bool CholInversion1( AlgolMatr &a )
{
/*
	Эл-ты положительно определённой симметричной м-цы A размещены в массиве
	a (1:n+1,1:n). Используется верхний треугольник.
	Ф-ция реализует разложение вида A=LU, где U - м-ца, транспонированная L.
	В процессе обращения на место м-цы L записывают ей обратную, а на место обратной L
	и м-цы D, в свою очередь, записываются эл-ты м-цы, обратной A.
	М-ца a сохранена (диагональ и выше) для возможного уточнения решения.
	Если из-за ошибок округления м-ца неположительна,
	то возвращается false. Иначе true.
	Например если A (n*n), а Q=A^(-1) то после выполнения ф-ции массив a будет иметь вид:
	|a11  a12  a13  a14|
	|q11  a22  a23  a24|
	|q21  q22  a33  a34|
	|q31  q32  q33  a44|
	|q41  q42  q43  q44|

*/
//copyright©2001 Буравилин.С.С. 96ДПМП БГТУ
	int n = a.GetRow() - 1;

	ASSERT( (a.GetMinCol()==1)&&(a.GetWidth()==n) );

	int i, j, k, i1, j1;
	double x, xx, y;

	//формирование м-цы L
	for( i = 1; i <= n; i++ )
	{
		i1 = i + 1;
		for( j = i; j <= n; j++ )
		{
			j1 = j + 1;
			//innerprod:
			long double s1s2 = (long double)(-a(i,j));
			int im1 = i - 1;
			for( k = 1; k <= im1; k++ )
				s1s2 += (long double)(a(i1,k))*(long double)(a(j1,k));
			x = (double)s1s2;
			xx = (double)( s1s2 - (long double)x );
			//-------------------------------------
			x = -x;
			if( i == j )
			{
				if( x <= ZERO )	return false;
				a(i1,i) = y = 1/sqrt(x);
			}
			else
			{
				a(j1,i) = x*y;
			}
		}
	}
	//обращение м-цы L
	for( i = 1; i <= n; i++ )
	{
		for( j = i+1; j <= n; j++ )
		{
			j1 = j + 1;
			//innerprod:
			long double s1s2 = 0.0;
			int jm1 = j - 1;
			for( k = i; k <= jm1; k++ )
				s1s2 += (long double)(a(j1,k))*(long double)(a(k+1,i));
			x = (double)(s1s2);
			xx = (double)( s1s2 - (long double)x );
			//-------------------------------------
			a(j1,i) = -x*a(j1,j);
		}
	}
	//вычисление м-цы, обратной A
	for( i = 1; i <= n; i++ )
	{
		for( j = i; j <= n; j++ )
		{
			//innerprod:
			long double s1s2 = 0.0;
			int np1 = n + 1;
			for( k = j+1; k <= np1; k++ )
				s1s2 += (long double)(a(k,j))*(long double)(a(k,i));
			a(j+1,i) = x = (double)(s1s2);
			xx = (double)( s1s2 - (long double)x );
			//-------------------------------------
		}
	}
	return true;
}

int ACCInverse( AlgolMatr &a, int &l )
{
/*
	Итерационное уточнение обратной м-цы. Элементы положительно определённой
	симметричной м-цы A, расположенные в верхнем треугольники, размещают в верхнем
	треугольнике массива a (n+1,n). М-ца X, обратная A, сформирована в оставшейся
	части массива a с помощью процедуры CholInversion1.
	Итерационное уточнение рез-та обращения реализовано согласно соотношению X=X+Z и
	продолжается до тех пор пока fabs(z(i,j)) не станет меньше 2*MACHEPS*fabs(x(i,j)),
	где Z=XB и B=I-AX, b (n,n), z (n). М-ца X вычисляется по строкам.
	Если м-ца A неположительна, то возвращается 1. Если не происходит уточнения, то 2.
	Иначе 0.
	l фиксирует число уточнений.
*/
//copyright©2001 Буравилин.С.С. 96ДПМП БГТУ
	int n = a.GetRow() - 1;

	ASSERT( (a.GetMinCol()==1)&&(a.GetWidth()==n) );

	int i, j, k, j1;
	double c, d, xmax, zmax, e = 1.0;
	AlgolMatr b(n,1,n), z(n,1,1);

	l = 0;

	if( !CholInversion1(a) )	return 1;

	do
	{
		for( i = 1; i <= n; i++ )
		{
			for( j = 1; j <= n; j++ )
			{
				j1 = j + 1;
				if( j >= i )
				{
					//innerprod:
					long double s1s2 = (long double)((i==j)?(-1.0):(0.0));
					for( k = 1; k <= i; k++ )
						s1s2 += (long double)a(k,i)*(long double)a(j1,k);
					//------------------------------------------
					for( k = i+1; k <= j; k++ )
						s1s2 += (long double)a(i,k)*(long double)a(j1,k);
					//------------------------------------------
					for( k = j1; k <= n; k++ )
						s1s2 += (long double)a(i,k)*(long double)a(k+1,j);
					c = (double)s1s2;
					d = (double)( s1s2 - (long double)c );
					//------------------------------------------
				}
				else
				{
					//innerprod:
					long double s1s2 = 0.0;
					for( k = 1; k <= j; k++ )
						s1s2 += (long double)a(k,i)*(long double)a(j1,k);
					//------------------------------------------
					for( k = j1; k <= i; k++ )
						s1s2 += (long double)a(k,i)*(long double)a(k+1,j);
					//------------------------------------------
					for( k = i+1; k <= n; k++ )
						s1s2 += (long double)a(i,k)*(long double)a(k+1,j);
					c = (double)s1s2;
					d = (double)( s1s2 - (long double)c );
					//------------------------------------------					
				}
				b(i,j) = -c;
			}
		}
		xmax = zmax = 0.0;
		for( i = 1; i <= n; i++ )
		{
			int ip1 = i + 1;
			for( j = 1; j <= i; j++ )
			{
				//innerprod:
				long double s1s2 = 0.0;
				for( k = 1; k <= i; k++ )
					s1s2 += (long double)a(ip1,k)*(long double)b(k,j);
				//------------------------------------------
				for( k = ip1; k <= n; k++ )
					s1s2 += (long double)a(k+1,i)*(long double)b(k,j);
				z(j,1) = c = (double)s1s2;
				d = (double)( s1s2 - (long double)c );
				//------------------------------------------
			}
			for( j = 1; j <= i; j++ )
			{
				double zj = z(j,1);
				c = fabs(a(ip1,j));
				d = fabs(zj);
				if( c > xmax )	xmax = c;
				if( d > zmax )	zmax = d;
				a(ip1,j) += zj;
			}
		}
		l++;
		d = zmax/xmax;
		if( d > (e/2) )	return 2;
		e = d;

	}	while( d > (2*MACHEPS) );
	return 0;
}

bool SymDet( AlgolMatr &a, AlgolMatr &p, DETERMINANT &det )
{
/*
	Эл-ты положительно определённой симметричной м-цы A размещены в массиве
	a (1:n,1:n). Ф-ция реализует разложение вида A=LDU, где U - м-ца, транспонированная L.
	Здесь L - нижняя треугольная м-ца с единичной диагональю, D - диагональная м-ца.
	Эл-ты м-цы, за исключением единичной диагонали, размещены в массиве a.
	Величины, обратные эл-ам м-цы D, размещены в массиве p (1:n). 
	М-ца a сохранена (диагональ и выше) для возможного уточнения решения.
	В det заносится определитель.
	Если из-за ошибок округления эл-т диагональной м-цы D оказалсы равным
	нулю (м-ца a вырождена), то возвращается false. Иначе true.
*/
//copyright©2001 Буравилин.С.С. 96ДПМП БГТУ
	int n = a.GetRow();

	ASSERT( (a.GetMinCol()==1)&&(a.GetWidth()==n)&&(p.GetRow()==n)&&(p.GetMinCol()==1) );

	int i, j, k;
	double x, y, z;

	det.mant = 1.0;
	det.power = 0;

	for( i = 1; i <= n; i++ )
	{
		for( j = 1; j <= n; j++ )
		{
			x = a(i,j);
			if( i == j )
			{
				for( k = j-1; k >= 1; k-- )
				{
					y = a(i,k);
					z = a(i,k) = y*p(k,1);
					x -= y*z;
				}
				det.mant *= x;
				if( fabs(x) < ZERO )
				{
					det.power = 0;
					return false;
				}
				
				while( fabs(det.mant) >= 1.0 )
				{
					det.power += 4;
					det.mant *= 0.0625;
				}
				while( fabs(det.mant) < 0.0625 )
				{
					det.power -= 4;
					det.mant *= 16;
				}
				p(j,1) = 1/x;
			}
			else
			{
				for( k = j-1; k >= 1; k-- )
					x -= a(i,k)*a(j,k);
				a(i,j) = x;
			}
		}
	}
	return true;
}
