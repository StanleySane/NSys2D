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

	//��������� �������� ���������, �������� � ���� �������
	CString strwBeg, strwEnd, strwStep;
	//����� ���������� � ��������������� �����������
	BOOL LogCoord;
	//����� ����������� (0-��� �����������;1-������;2-������ �����������)
	int Derive;
	//��� �������������� (0-���;1-���;2-���)
	int TypeCharact;
	//����� ������� ������� �����(1) � ������(2)
	int nFree1, nFree2;
	//����������� �������� ������� �����(1) � ������(2)
	int typeFree1, typeFree2;
	//�������(0)/��������������(1) ����������
	int typeForce;
	//��������� �������������� ����
	CKnot *pKnot1, *pKnot2;
};

#endif // !defined(AFX_FREQPARAM_H__12A2D622_9102_11D3_980F_BF05434AD432__INCLUDED_)
