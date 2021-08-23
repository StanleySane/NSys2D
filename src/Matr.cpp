// Matr.cpp: implementation of the CMatr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"
#include "Matr.h"

#include <fstream.h>
#include <math.h>
#include <iomanip.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

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
			delete [] Data[i];
		delete [] Data;
		Data=0;
		SizeX=SizeY=0;
	}
}

void CMatr::ReSize(int ny, int nx)
{
	ASSERT(nx>0);
	ASSERT(ny>0);

	Clear();

	SizeX=nx;
	SizeY=ny;
	
	Data=new double*[SizeY];
	for (int i=0;i<SizeY;i++)
		Data[i]=new double[SizeX];
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

CMatr CMatr::GetInvert(int &flag)
{
	ASSERT(SizeX==SizeY);

	CMatr mC(SizeY,SizeX), mU(SizeY,SizeX), mR(SizeY,SizeX);
	mR.SetIdentity();

	mC=*this;
	flag=mC.SolveSystem(mR,mU);
	
	return mU;
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
		if (Data[d][d]==0) return 0;

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
