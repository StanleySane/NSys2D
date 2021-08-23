// Complex.cpp: implementation of the Complex class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"
#include <math.h>
#include "Complex.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Complex::Complex()
{
	r=i=0;
}

Complex::~Complex()
{

}

Complex::Complex (double re)
{
    r = re;
    i = 0;
}


Complex::Complex (double re, double im)
{
    r = re;
    i = im;
}

Complex::Complex (const Complex& Copy)
{
    r = Copy.r;
    i = Copy.i;
}

Complex Complex::operator - () const
{
    Complex a(-r,-i);

    return a;
}

Complex & Complex::operator = (const Complex & Copy)
{
    r = Copy.r;
    i = Copy.i;

    return *this;
}

Complex & Complex::operator = (const double & rCopyAndi0)
{
    r = rCopyAndi0;
    i = 0.0;

    return *this;
}

Complex & Complex::operator += (const Complex& a)
{
    r += a.r;
    i += a.i;

    return *this;
}

Complex & Complex::operator -= (const Complex& a)
{
    r -= a.r;
    i -= a.i;

    return *this;
}

Complex & Complex::operator *= (const Complex& a)
{
    double
    rTmp = r * a.r - i * a.i;

    i    = r * a.i + i * a.r;
    r    = rTmp;

    return *this;
}

Complex & Complex::operator /= (const Complex& a)
{
    double rTmp;
    double Low = a.r * a.r + a.i * a.i;

	double Eps=1e-60;
    if (Low < Eps)
    {
		AfxMessageBox("Деление на 0");
		return *this;
    }
    rTmp = (r * a.r + i * a.i)/Low;
    i    = (i * a.r - r * a.i)/Low;
    r    = rTmp;

    return *this;
}

Complex operator + (const Complex& a, const Complex& b)
{
    Complex c (a.r + b.r, a.i + b.i);

    return c;
}

Complex operator - (const Complex & What, const Complex & Dec)
{
    Complex a (What.r - Dec.r, What.i - Dec.i);

    return a;
}

Complex operator * (const Complex & a, const Complex & b)
{
    Complex c (a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r);

    return c;
}

Complex operator * (double a,             const Complex & b)
{
    return Complex (a*b.r, a*b.i);
}

Complex operator * (const Complex & a,    double b)
{
    return b*a;
}

Complex operator / (const Complex & What, const Complex & Div)
{
    Complex a;
    double Low = Div.r * Div.r + Div.i * Div.i;

	double Eps=1e-60;
    if (Low < Eps)
    {
		AfxMessageBox("Деление на 0");
		return a;
    }
    a.r = (What.r * Div.r + What.i * Div.i)/Low;
    a.i = (What.i * Div.r - What.r * Div.i)/Low;

    return a;
}

int operator == (const Complex & a, const Complex & b)
{
	double Eps=1e-30;
    return (a.r < b.r + Eps) &&
           (a.r > b.r - Eps) &&
           (a.i < b.i + Eps) &&
           (a.i > b.i - Eps);
}

int operator == (const Complex & a, double b)
{
	double Eps=1e-30;
    return  (a.r < b + Eps) &&
            (a.r > b - Eps) &&
            (fabs (a.i) < Eps);
}

int operator == (double b, const Complex & a)
{
    return a == b;
}

int operator != (const Complex & a, const Complex & b)
{
	double Eps=1e-30;
    return (a.r > b.r + Eps) ||
           (a.r < b.r - Eps) ||
           (a.i > b.i + Eps) ||
           (a.i < b.i - Eps);
}

int operator != (const Complex & a, double b)
{
	double Eps=1e-30;
    return  (a.r > b + Eps) ||
            (a.r < b - Eps) ||
            (fabs (a.i) > Eps);
}

int operator != (double b, const Complex & a)
{
    return a != b;
}


double fabs(const Complex &a)
{
    return fabs(a.r) + fabs(a.i);
}

double Len (const Complex & a)
{
    return sqrt (a.r*a.r+a.i*a.i);
}

double Sqr (const Complex & a)
{
    return (a.r*a.r+a.i*a.i);
}

double& Complex::Re()
{
	return r;
}

double& Complex::Im()
{
	return i;
}
