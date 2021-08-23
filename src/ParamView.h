// ParamView.h: interface for the CParamView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARAMVIEW_H__6CF72FA3_C76C_11D2_AF23_BB2B1C460D22__INCLUDED_)
#define AFX_PARAMVIEW_H__6CF72FA3_C76C_11D2_AF23_BB2B1C460D22__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "StdAfxMy.h"
#include <afxwin.h>
#include "coordd.h"

class CParamView  
{
public:
	void Serialize( CArchive&, int );
	void DelZeroInSelNumbers();

	double Scale;
	static double m_DefaultScale;
	CCoordD MoveCenter;
	CPoint pos;
	BOOL Gray;
	double MultMove;
	double MultAngl;

	//m_iClickedObjects - ����������, ��� ������ ������ �����
	//������ (1-���������,2-�����) ������, ����� m_iClickedObjects==0
	int m_iClickedObjects;
	//m_bSelType - ����, ������������, ��� ���� �������� ��� ���������:
	//�������� (m_bSelType=true) ��� ���� (m_bSelType=true),
	//���� ������ m_vecSelNumbers �� ������.
	bool m_bSelType;
	//������, ���������� ������ ��������� ��� �����, �������
	//���������� ��������.
	ARRAY m_vecSelNumbers;
	//����� �������
	CString m_strFreeFontName, m_strNumElemsFontName, m_strNumKnotsFontName;
	//����� ��� ������ ������� �����
	CFont m_fntKnot;
	//����� ��� ������ ������.������ � ��������� ������� �� ������
	CFont m_fntFree;
	//����� ��� ������ ������� ��-��
	CFont m_fntElems;
	COLORREF m_clrFree, m_clrNumElems, m_clrNumKnots;
	bool m_bTextOut;//�������� �� ������ � ���� ������
	bool m_bNumElems, m_bNumKnots;
	//�������� �������� ���������� ������� ������� �����,
	//���� ������� ������� �� ������������:
	double m_ZeroRot;
	//���� � ���, �������� �� ������ �������� ������� � �����:
	bool m_bFreeNums;

//	CParamView(double scale=2, CPoint &point=CPoint(0,0));
	CParamView(double scale=2, 
		   CCoordD &coord=CCoordD(0,0));
	virtual ~CParamView();

};

#endif // !defined(AFX_PARAMVIEW_H__6CF72FA3_C76C_11D2_AF23_BB2B1C460D22__INCLUDED_)
