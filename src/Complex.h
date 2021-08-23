// Complex.h: interface for the Complex class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMPLEX_H__AA8EC943_70CC_11D3_980F_BF05434AD432__INCLUDED_)
#define AFX_COMPLEX_H__AA8EC943_70CC_11D3_980F_BF05434AD432__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class Complex  
{
	double r, i;
public:
	double &Re();
	double &Im();
	virtual ~Complex();

    Complex ();
    Complex (double re);
    Complex (double re, double im);
    Complex (const Complex & Copy);


    Complex   operator  - () const;

    Complex & operator  = (const Complex & Copy);
    Complex & operator  = (const double & rCopyAndi0);
    Complex & operator += (const Complex & a);
    Complex & operator -= (const Complex & a);
    Complex & operator *= (const Complex & a);
    Complex & operator /= (const Complex & a);

    friend Complex operator + (const Complex & a,    const Complex & b);
    friend Complex operator - (const Complex & What, const Complex & Dec);
    friend Complex operator * (const Complex & a,    const Complex & b);
    friend Complex operator * (double a,             const Complex & b);
    friend Complex operator * (const Complex & a,    double b);
    friend Complex operator / (const Complex & What, const Complex & Div);

    friend int   operator == (const Complex & a,    const Complex & b);
    friend int   operator == (const Complex & a,    double b);
    friend int   operator == (double b,            const Complex & a);
    friend int   operator != (const Complex & a,    const Complex & b);
    friend int   operator != (const Complex & a,    double b);
    friend int   operator != (double b,            const Complex & a);

    friend double qabs (const Complex & a)
    {
       return a.r * a.r + a.i * a.i;
    }

    friend double fabs (const Complex & a); ///!!!!!! return fabs(r)+fabs(i)
    friend double Len  (const Complex & a); ///!!!!!! return sqrt(r^2+i^2)
    friend double Sqr  (const Complex & a); ///!!!!!! return (r^2+i^2)

    friend double Re (const Complex & a)
    {
       return a.r;
    }

    friend double Im (const Complex & a)
    {
       return a.i;
    }

    friend Complex Co  (const Complex & a)
    {
       return Complex (a.r, -a.i);
    }
};

#endif // !defined(AFX_COMPLEX_H__AA8EC943_70CC_11D3_980F_BF05434AD432__INCLUDED_)
