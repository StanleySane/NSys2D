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

	//m_iClickedObjects - показывает, что сейчас ведётся набор
	//группы (1-элементов,2-узлов) мышкой, иначе m_iClickedObjects==0
	int m_iClickedObjects;
	//m_bSelType - флаг, показывающий, что надо выделять при рисовании:
	//элементы (m_bSelType=true) или узлы (m_bSelType=true),
	//если массив m_vecSelNumbers не пустой.
	bool m_bSelType;
	//вектор, содержащий номера элементов или узлов, которые
	//необходимо выделить.
	ARRAY m_vecSelNumbers;
	//имена шрифтов
	CString m_strFreeFontName, m_strNumElemsFontName, m_strNumKnotsFontName;
	//шрифт для вывода номеров узлов
	CFont m_fntKnot;
	//шрифт для вывода собств.частот и заголовка графика на экране
	CFont m_fntFree;
	//шрифт для вывода номеров эл-ов
	CFont m_fntElems;
	COLORREF m_clrFree, m_clrNumElems, m_clrNumKnots;
	bool m_bTextOut;//выводить ли данные в виде текста
	bool m_bNumElems, m_bNumKnots;
	//величина смещения поворотной степени свободы массы,
	//ниже которой поворот не показывается:
	double m_ZeroRot;
	//флаг о том, выводить ли номера степеней свободы в узлах:
	bool m_bFreeNums;

//	CParamView(double scale=2, CPoint &point=CPoint(0,0));
	CParamView(double scale=2, 
		   CCoordD &coord=CCoordD(0,0));
	virtual ~CParamView();

};

#endif // !defined(AFX_PARAMVIEW_H__6CF72FA3_C76C_11D2_AF23_BB2B1C460D22__INCLUDED_)
