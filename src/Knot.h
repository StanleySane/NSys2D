// Knot.h: interface for the CKnot class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KNOT_H__A9AC9422_C7EA_11D2_AF23_BB2B1C460D22__INCLUDED_)
#define AFX_KNOT_H__A9AC9422_C7EA_11D2_AF23_BB2B1C460D22__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <afxtempl.h>
#include "ObjectSheme.h"
#include "Expression.h"
#include "Matr.h"
#include "SpectrParam.h"
#include "ParamTime.h"

/*#include "ListKnot.h"
#include "ListSpectr.h"*/

class CKnot : public CObjectSheme  
{
private:
	//Координаты
	CString str_X, str_Y;
	CCoordD coord;

	//Начальные условия
	CString str_Ux, str_Uy, str_Ua;
	CString str_Uxp, str_Uyp, str_Uap;
	double Ux,Uy,Ua;
	double Uxp,Uyp,Uap;

public:
	int SetKinematicPos(CMatr &matr_RezY1, CMatr &matr_RezY2, int  i, double Tt);
	void DrawPower(CDC * pDC,  POINT & point, CParamView* pParamView);
	void EndIntegr();
	int BeginIntegr(double T);

	//СИЛОВОЕ ВОЗМУЩЕНИЕ (амплитуда, частота, фаза, произвольное возмущение)
	CString str_Ax, str_Wx, str_Fix, str_Px;
	CString str_Ay, str_Wy, str_Fiy, str_Py;
	double Ax, Wx, Fix;
	double Ay, Wy, Fiy;
	CSpectrParam SpPx, SpPy;
	//Произвольное, гармоническое или случайное возмущение
	int TypePx, TypePy;
	//Флаг наличия возмущения
	BOOL PxEnable, PyEnable;

	//КИНЕМАТИЧЕСКОЕ ВОЗМУЩЕНИЕ (амплитуда, частота, фаза, произвольное возмущение)
	CString str_uAx, str_uWx, str_uFix, str_uUx;
	CString str_uAy, str_uWy, str_uFiy, str_uUy;
	double uAx, uWx, uFix;
	double uAy, uWy, uFiy;
	CSpectrParam SpUx, SpUy;
	//Произвольное, гармоническое или случайное возмущение
	int TypeUx, TypeUy;
	//Флаг наличия возмущения
	BOOL UxEnable, UyEnable;

	double GetPx(double x, double x1, double Tt);
	double GetPy(double x, double x1, double Tt);
	int SetMatrmP(CMatr & mP, double Tt);
	void Init();
	int SetMatrmP(CMatr & mP, CMatr & RezY1, CMatr & RezY2, int i, double Tt, CMatr & mUM, CMatr & mUD, CMatr & mUC);
	int SetFixedKnot();
	virtual void Serialize(CArchive & ar);
	double SetStrUa(CString str, int p=0);
	double SetStrUy(CString str, int p=0);
	double SetStrUx(CString str, int p=0);
	CString GetStrUa(int p=0);
	CString GetStrUy(int p=0);
	CString GetStrUx(int p=0);
	double GetUa(int p=0);
	double GetUy(double Tt, int p=0);
	double GetUx(double Tt, int p=0);
	void SetFixedKnotMDC(CMatr & mM, CMatr & mD, CMatr & mC);
	void operator = (CKnot &knot);
	void DrawFixed(CDC *pDC, POINT &point, CParamView *pParamView);
	int GoDlg(/*CListKnot *pListKnot, CListSpectr *pListSpectr*/);
	CPoint GetScreenCoord(CParamView* pParamView);
	CString GetStrY();
	CString GetStrX();
	CString GetName(UINT num=0);

	//режим выбора узла на дисплее (для прорисовки)
	int SelectMode, OldMode;
	//Номер узла
	int Num;

	//номера степеней свободы для перемещений и углов поворота
	int nXRez;
	int nYRez;
	int nARez[10];
	int CntAngle;

	//Перемещения для собственных форм колебаний
	double MoveX;
	double MoveY;
	double MoveA[10];

	//номера степеней свободы для кинематического возмущения
	int nXU, nYU;

	//Параметры вывода графиков
	CParamTime ParamTime;

	//Координаты одного из соседних узлов
	CCoordD FriendCoord;
	//Тип закрепления в узле
	int FixedType;
	//Тип соединения в узле (жёстко=0/шарнирно)
	int ConnectType;

	void Draw(CDC * pDC, CParamView* pParamView);
	int SetCoord(CString strx, CString stry);
	CCoordD GetCoord(double MultMove=0);
	CKnot();
	CKnot(CString strx, CString stry);
	virtual ~CKnot();
};

#endif // !defined(AFX_KNOT_H__A9AC9422_C7EA_11D2_AF23_BB2B1C460D22__INCLUDED_)