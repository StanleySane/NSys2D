// FreqParam.h: interface for the CFreqParam class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FREQPARAM_H__12A2D622_9102_11D3_980F_BF05434AD432__INCLUDED_)
#define AFX_FREQPARAM_H__12A2D622_9102_11D3_980F_BF05434AD432__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include "knot.h"

class CFreqParam  
{
public:
	void Serialize(CArchive & ar);
	CFreqParam();
	virtual ~CFreqParam();

	//Строковые значения начальной, конечной и шага частоты
	CString strwBeg, strwEnd, strwStep;
	//Вывод результате в логарифмических координатах
	BOOL LogCoord;
	//Номер производной (0-нет производной;1-первая;2-вторая производная)
	int Derive;
	//Тип характеристики (0-АЧХ;1-АФХ;2-ФЧХ)
	int TypeCharact;
	//Номер степени свободы входа(1) и выхода(2)
	int nFree1, nFree2;
	//Направление степеней свободы входа(1) и выхода(2)
	int typeFree1, typeFree2;
	//Силовое(0)/Кинематическое(1) возмущение
	int typeForce;
	//Последние использованные узлы
	CKnot *pKnot1, *pKnot2;
};

#endif // !defined(AFX_FREQPARAM_H__12A2D622_9102_11D3_980F_BF05434AD432__INCLUDED_)
