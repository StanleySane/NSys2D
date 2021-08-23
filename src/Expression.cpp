// Expression.cpp: implementation of the CExpression class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Expression.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

double hev(double x)
{
	return (x>=0?1:0);
}

UINT AFXAPI HashKey (const CString & str)
{
	union	{	UINT i;
				struct {TCHAR a; TCHAR b;} st; 
			};
	i = 0;
	st.b = str[0];
	return i;
}

//////////////////////////////////////////////////////////////////////
// Static Data:

CIDValuesMap CExpression::PredefinedIDMap;
CFunctionsMap CExpression::FunctionMap;

void CExpression::InitStaticData()
{
	PredefinedIDMap.SetAt(_T("PI"), atan2(0, -1));
	PredefinedIDMap.SetAt(_T("e"), exp(1));

	FunctionMap.SetAt(_T("sin"), sin);
	FunctionMap.SetAt(_T("cos"), cos);
	FunctionMap.SetAt(_T("asin"), asin);
	FunctionMap.SetAt(_T("acos"), acos);
	FunctionMap.SetAt(_T("sinh"), sinh);
	FunctionMap.SetAt(_T("cosh"), cosh);
	FunctionMap.SetAt(_T("tan"), tan);
	FunctionMap.SetAt(_T("atan"), atan);
	FunctionMap.SetAt(_T("exp"), exp);
	FunctionMap.SetAt(_T("log"), log);
	FunctionMap.SetAt(_T("log10"), log10);
	FunctionMap.SetAt(_T("sqrt"), sqrt);
	FunctionMap.SetAt(_T("abs"), fabs);
	FunctionMap.SetAt(_T("fabs"), fabs);
	FunctionMap.SetAt(_T("hev"), hev);
}

void CExpression::PassSpaces (LPCTSTR * pcsPos)const
{
	while (1)
	{
		switch (**pcsPos)
		{
		case _T(' '):
		case _T('\t'):
		case _T('\n'):
		case _T('\r'):
			(*pcsPos)++;
			break;
		default:
			return;
		}
	}
}

BOOL CExpression::GetSign(TCHAR * c, LPCTSTR * pcsPos)const
{
	ASSERT(pcsPos);
	ASSERT(c);

	PassSpaces(pcsPos);
	switch (**pcsPos)
	{
	case _T('+'):
	case _T('-'):
	case _T('*'):
	case _T('/'):
	case _T('^'):
	case _T('('):
	case _T(')'):

	case _T('<'):
	case _T('>'):
	case _T('['):
	case _T(']'):
	case _T('{'):
	case _T('}'):
	case _T('='):
	case _T(':'):
	case _T('.'):
	case _T(','):
	case _T(';'):
	case _T('!'):
	case _T('&'):
		*c = *((*pcsPos)++);
		break;
	case _T('\0'):
		*c = **pcsPos;
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

BOOL CExpression::GetNumber(double * val, LPCTSTR * pcsPos)const
{
	PassSpaces(pcsPos);
		//Заводим лишний объект для
	LPCTSTR pEnd = NULL;
	*val = _tcstod (
		*pcsPos, 
		const_cast <TCHAR**>(&pEnd));
	if (*pcsPos == pEnd) return FALSE;

#ifdef _DEBUG
	if (pEnd == NULL) 
	{
		ASSERT(0);		//по спецификации _tcstod не может вернуть NULL!
		return FALSE;
	}
#endif

	*pcsPos = pEnd;
	return TRUE;
}

BOOL CExpression::GetID(CString * str, LPCTSTR * pcsPos)const
{
	ASSERT(pcsPos && str);
	PassSpaces(pcsPos);
	LPCTSTR pcsEnd = *pcsPos;

	if (!_istalpha(*pcsEnd)) return FALSE;
		//ID начинается с буквы...

	while (_istalnum(*(++pcsEnd)));
	*str = CString (*pcsPos, pcsEnd - *pcsPos);
	*pcsPos = pcsEnd;
	return TRUE;
}

UINT CExpression::EvaluateToken(double * val, LPCTSTR * pcsPos, const CIDValuesMap * m_IDValues /*=NULL*/)const
{
	TCHAR t = _T('\0');
	UINT retval = 0;
	double num = 0;
	CString str;

	if (GetSign(&t, pcsPos))
	{
		switch (t)
		{
		case _T('('):
			retval = EvaluateAdd(val, pcsPos, m_IDValues);
			if (retval)
				return retval;
			if (!GetSign(&t, pcsPos) || t != _T(')') )
				return IDS_EE_MISSING_CLOSE_BRACKET;
			break;
		case _T('+'):
			retval = EvaluateToken(val, pcsPos, m_IDValues);
			if (retval)
				return retval;
			break;
		case _T('-'):
			retval = EvaluateToken(val, pcsPos, m_IDValues);
			if (retval)
				return retval;
			*val = -(*val);
			break;
		default:
			return IDS_EE_UNEXPECTED_SIGN;
		}
	}
	else
	{
		if (GetNumber(val, pcsPos));
		else if (/*m_IDValues && */GetID(&str, pcsPos))
		{
			//Возможно имеем дело с функцией...
			LPCTSTR csPos2 = *pcsPos;
			TCHAR t = _T('\0');
			if (GetSign(&t, &csPos2) && t == _T('(') )
			{
				//Обрабатываем вызов нужной функции...
				LPMATHFUNC pFunc = NULL;
				if (!FunctionMap.Lookup(str, pFunc))
					return IDS_EE_UNKNOWN_FUNCTION;
				double val2 = 0;
				retval = EvaluateToken(&val2, pcsPos, m_IDValues);
				if (retval) return retval;
				*val = (*pFunc)(val2);
			}
			//Найдём переменную в списке пользовательских переменных...
			else if (m_IDValues && m_IDValues->Lookup (str, *val));
			//Найдём перемнную в списке предопределённыых переменных...
			else if (!PredefinedIDMap.Lookup(str, *val))
				return IDS_EE_UNDEFINED_ID;
		}
		else
			return IDS_EE_BAD_CHAR;
			
	}
	return 0;
}

UINT CExpression::EvaluateAdd(double * val, LPCTSTR * pcsPos, const CIDValuesMap * m_IDValues /*=NULL*/)const
{
	ASSERT (val && pcsPos);

	TCHAR t = _T('\0');
	double num = 0, sum = 0;
	UINT retval = EvaluateMul(&sum, pcsPos, m_IDValues);
//	CString str;
 
	if (!retval)
	{
		LPCTSTR psPos2 = *pcsPos;
		while (GetSign(&t, &psPos2))
		{
			switch (t)
			{
			case _T('+'):
				if (!(retval = EvaluateMul(&num, &psPos2, m_IDValues)))
				{
					sum += num;
				}
				else
					return retval;
				*pcsPos = psPos2;
				break;
			case _T('-'):
				if (!(retval = EvaluateMul(&num, &psPos2, m_IDValues)))
				{
					sum -= num;
				}
				else
					return retval;
				*pcsPos = psPos2;
				break;
			default:
				*val = sum;
				return 0;
			}
		}
		*val = sum;
	}
	else return retval;
	return 0;
}

UINT CExpression::EvaluateMul(double * val, LPCTSTR * pcsPos, const CIDValuesMap * m_IDValues /*=NULL*/)const
{
	ASSERT (val && pcsPos);

	TCHAR t = _T('\0');
	double num = 0, sum = 0;
	UINT retval = EvaluatePow(&sum, pcsPos, m_IDValues);
//	CString str;
 
	if (!retval)
	{
		LPCTSTR psPos2 = *pcsPos;
		while (GetSign(&t, &psPos2))
		{
			switch (t)
			{
			case _T('*'):
				if (!(retval = EvaluatePow(&num, &psPos2, m_IDValues)))
				{
					sum *= num;
				}
				else
					return retval;
				*pcsPos = psPos2;
				break;
			case _T('/'):
				if (!(retval = EvaluatePow(&num, &psPos2, m_IDValues)))
				{
					if (num == 0) return IDS_EE_DIVISION_BY_ZERO;
					sum /= num;
				}
				else
					return retval;
				*pcsPos = psPos2;
				break;
			default:
				*val = sum;
				return 0;
			}
		}
		*val = sum;
	}
	else return retval;
	return 0;
}

UINT CExpression::EvaluatePow(double * val, LPCTSTR * pcsPos, const CIDValuesMap * m_IDValues /*=NULL*/)const
{
	ASSERT (val && pcsPos);

	TCHAR t = _T('\0');
	double num = 0, sum = 0;
	UINT retval = EvaluateToken(&sum, pcsPos, m_IDValues);
//	CString str;
 
	if (!retval)
	{
		LPCTSTR psPos2 = *pcsPos;
		while (GetSign(&t, &psPos2))
		{
			switch (t)
			{
			case _T('^'):
				if (!(retval = EvaluateToken(&num, &psPos2, m_IDValues)))
				{
					sum = pow (sum, num);
				}
				else
					return retval;
				*pcsPos = psPos2;
				break;
			default:
				*val = sum;
				return 0;
			}
		}
		*val = sum;
	}
	else return retval;
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////
UINT EvaluateExpression(CString &str, double * val, const CIDValuesMap * IDValues /*= NULL*/)
{
	ASSERT(str && val);

	const char *pcsPos[1];
	pcsPos[0]=(LPCTSTR)str;

	CExpression e;
	
	UINT ret = e.Evaluate(pcsPos, IDValues);
	if (!ret)
		*val = double(e);
	return ret;
}


UINT CExpression::IsNum(CString & str, double * val, const CIDValuesMap * IDValues /*= NULL*/)
{
	const char *pcsPos[1];
	pcsPos[0]=(LPCTSTR)str;

	UINT ret = Evaluate(pcsPos, IDValues);
	if ( (!ret) && (val) )
		*val = double(*this);
	return ret;
}
