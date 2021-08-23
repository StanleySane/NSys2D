#pragma once

#include "resource.h"
#include <math.h>
#include <afxtempl.h>

typedef CMap<CString, const CString &, double, double> CIDValuesMap;
 /** тип данных для хранения списка значений переменных,
	определяемых пользователем */
UINT AFXAPI HashKey (const CString & str);

typedef double (*LPMATHFUNC)(double);
typedef CMap<CString, const CString &, LPMATHFUNC, LPMATHFUNC> CFunctionsMap;


extern UINT AFXAPI HashKey (const CString & str);

class CExpression //: public CString
 /**	Этот класс содержит выражение, значение которого он может
		вычислять. Допустимыми операциями в выражении являются:
		сложение, вычитание, умножение, деление, скобки, степень,
		основные математические функции и пара предопределённых 
		переменных -- PI и e.
		Для вычисления выражения с переменными неоюходимо передать
		классу значения переменных при помощи объекта CIDValuesMap*/
{
private: static CIDValuesMap PredefinedIDMap;
private: static CFunctionsMap FunctionMap;
private: double dVal;
	/**	Пред использованием функций класса обязательно вызовите
		метод InitStaticData для инициализации статических данных */
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
	/** Функция возвращает 0 в случае успеха 
		или номер ресурса-строки с описанием ошибки в обратном случае.
		Если результат математической функции в выражении неопределён.
		(например -- sqrt(-1)) функция вернёт HUGE_VAL или -HUGE_VAL.*/

protected: virtual BOOL GetSign (TCHAR * c, LPCTSTR * pcsPos)const;
protected: virtual BOOL GetNumber (double * num, LPCTSTR * pcsPos)const;
protected: virtual BOOL GetID (CString * str, LPCTSTR * pcsPos)const;
protected: virtual void PassSpaces(LPCTSTR * pcsPos)const;

	/** Функции возвращают 0 в случае успеха 
		или номер ресурса-строки с описанием ошибки в обратном случае.*/
protected: virtual UINT EvaluateAdd (double * val, LPCTSTR * pcsPos, const CIDValuesMap * m_IDValues = NULL)const;
protected: virtual UINT EvaluateMul (double * val, LPCTSTR * pcsPos, const CIDValuesMap * m_IDValues = NULL)const;
protected: virtual UINT EvaluatePow (double * val, LPCTSTR * pcsPos, const CIDValuesMap * m_IDValues = NULL)const;
protected: virtual UINT EvaluateToken (double * val, LPCTSTR * pcsPos, const CIDValuesMap * m_IDValues = NULL)const;
};

UINT EvaluateExpression(CString &str, double * val, const CIDValuesMap * IDValues = NULL);