#pragma once

#include "resource.h"
#include <math.h>
#include <afxtempl.h>

typedef CMap<CString, const CString &, double, double> CIDValuesMap;
 /** ��� ������ ��� �������� ������ �������� ����������,
	������������ ������������� */
UINT AFXAPI HashKey (const CString & str);

typedef double (*LPMATHFUNC)(double);
typedef CMap<CString, const CString &, LPMATHFUNC, LPMATHFUNC> CFunctionsMap;


extern UINT AFXAPI HashKey (const CString & str);

class CExpression //: public CString
 /**	���� ����� �������� ���������, �������� �������� �� �����
		���������. ����������� ���������� � ��������� ��������:
		��������, ���������, ���������, �������, ������, �������,
		�������� �������������� ������� � ���� ��������������� 
		���������� -- PI � e.
		��� ���������� ��������� � ����������� ���������� ��������
		������ �������� ���������� ��� ������ ������� CIDValuesMap*/
{
private: static CIDValuesMap PredefinedIDMap;
private: static CFunctionsMap FunctionMap;
private: double dVal;
	/**	���� �������������� ������� ������ ����������� ��������
		����� InitStaticData ��� ������������� ����������� ������ */
private: static void InitStaticData();


public: CExpression (const CExpression & e):dVal(e.dVal)
		{if (FunctionMap.GetCount() == 0) InitStaticData();}
public: CExpression (double d = 0):dVal(d) 
		{if (FunctionMap.GetCount() == 0) InitStaticData();}
public:	~CExpression(){}

public: CExpression& operator = (const CExpression &e) {dVal = e.dVal; return *this;}
public: CExpression& operator = (const double d) {dVal = d; return *this;}
public: operator const double	()const	{return dVal;}
public: operator double&		()		{return dVal;}

public: UINT IsNum(CString &str, double *val = NULL, const CIDValuesMap * IDValues = NULL);

		UINT Evaluate (LPCTSTR * pcsPos, const CIDValuesMap * IDValues = NULL)
		{return EvaluateAdd(&dVal, pcsPos, IDValues);}
	/** ������� ���������� 0 � ������ ������ 
		��� ����� �������-������ � ��������� ������ � �������� ������.
		���� ��������� �������������� ������� � ��������� ����������.
		(�������� -- sqrt(-1)) ������� ����� HUGE_VAL ��� -HUGE_VAL.*/

protected: virtual BOOL GetSign (TCHAR * c, LPCTSTR * pcsPos)const;
protected: virtual BOOL GetNumber (double * num, LPCTSTR * pcsPos)const;
protected: virtual BOOL GetID (CString * str, LPCTSTR * pcsPos)const;
protected: virtual void PassSpaces(LPCTSTR * pcsPos)const;

	/** ������� ���������� 0 � ������ ������ 
		��� ����� �������-������ � ��������� ������ � �������� ������.*/
protected: virtual UINT EvaluateAdd (double * val, LPCTSTR * pcsPos, const CIDValuesMap * m_IDValues = NULL)const;
protected: virtual UINT EvaluateMul (double * val, LPCTSTR * pcsPos, const CIDValuesMap * m_IDValues = NULL)const;
protected: virtual UINT EvaluatePow (double * val, LPCTSTR * pcsPos, const CIDValuesMap * m_IDValues = NULL)const;
protected: virtual UINT EvaluateToken (double * val, LPCTSTR * pcsPos, const CIDValuesMap * m_IDValues = NULL)const;
};

UINT EvaluateExpression(CString &str, double * val, const CIDValuesMap * IDValues = NULL);