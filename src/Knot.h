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
#include "Matr.h"
#include "SpectrParam.h"
#include "ParamTime.h"
#include "ShemeExpr.h"

class CSheme;

class CKnot : public CObjectSheme  
{
private:
	//����������
	CCoordD coord;

	void InitBy( const CKnot& );
public:
	void SetVarState( double x, double v, double a, double t );
	void SetCommonProperties( CKnot *pKnot );
	int SetKinematicPos( CMatr &Y1, CMatr &Y2, CMatr *pY3, int  i, double Tt, std::string *pMsg = NULL );
	void DrawPower(CDC * pDC,  POINT & point, CParamView* pParamView);
	void EndIntegr();
	int BeginIntegr(double T);

	//��������� �������
	CShemeExpr m_Ux, m_Uy, m_Ua;
	CShemeExpr m_Uxp, m_Uyp, m_Uap;
	//������� ���������� (���������, �������, ����, ������������ ����������)
	CShemeExpr m_Px, m_Py;
	double Ax, Wx, Fix;
	double Ay, Wy, Fiy;
	CSpectrParam SpPx, SpPy;
	//������������, ������������� ��� ��������� ����������
	int TypePx, TypePy;
	//���� ������� ����������
	BOOL PxEnable, PyEnable;

	//�������������� ���������� (���������, �������, ����, ������������ ����������)
	CShemeExpr m_uUx, m_uUy;
	double uAx, uWx, uFix;
	double uAy, uWy, uFiy;
	CSpectrParam SpUx, SpUy;
	//������������, ������������� ��� ��������� ����������
	int TypeUx, TypeUy;
	//���� ������� ����������
	BOOL UxEnable, UyEnable;

	double GetPx(double x, double x1, double a, double Tt, std::string *pMsg = NULL );
	double GetPy(double x, double x1, double a, double Tt, std::string *pMsg = NULL );
	int SetMatrmP( CMatr &mP, CMatr &RezY1, CMatr &RezY2, CMatr *pRezY3, int i, double Tt, std::string *pMsg = NULL );
	void Init();
	int SetMatrmP( CMatr &mP, CMatr &RezY1, CMatr &RezY2, CMatr *pRezY3, int i, double Tt, CMatr & mUM, CMatr & mUD, CMatr & mUC, std::string *pMsg = NULL );
	int SetFixedKnot();
	virtual void Serialize( CArchive &, int );

	double GetUa( double x, double v, double a, double t, std::string *pMsg = NULL, int p=0);
	double GetUy( double x, double v, double a, double Tt, std::string *pMsg = NULL, int p=0);
	double GetUx( double x, double v, double a, double Tt, std::string *pMsg = NULL, int p=0);

	void DrawFixed(CDC *pDC, POINT &point, CParamView *pParamView);
	void DrawFreeNums( CDC*, POINT&, CParamView* );
	int GoDlg( bool full = true/*CListKnot *pListKnot, CListSpectr *pListSpectr*/);
	CPoint GetScreenCoord(CParamView* pParamView);
	CString GetName(UINT num=0);
	CString GetFullName();

	//����� ������ ���� �� ������� (��� ����������)
	int SelectMode, OldMode;
	//����� ����
	int Num;

	//������ �������� ������� ��� ����������� � ����� ��������
	int nXRez;
	int nYRez;
	int nARez[10];
	int CntAngle;

	//����������� ��� ����������� ���� ���������
	double MoveX;
	double MoveY;
	double MoveA[10];

	//������ �������� ������� ��� ��������������� ����������
	int nXU, nYU;

	//��������� ������ ��������
	CParamTime ParamTime;

	//���������� ������ �� �������� �����
	CCoordD FriendCoord;
	//��� ����������� � ����
	int FixedType;
	//��� ���������� � ���� (�����=0/��������)
	int ConnectType;

	void DrawGL( CShemeDoc*, int );
	void Draw(CDC * pDC, CParamView* pParamView);

	int SetCoord( double, double );
	double GetCoordX( double multmove = 0.0 );
	double GetCoordY( double multmove = 0.0 );
	CCoordD GetCoord(double multmove=0);

	CKnot( CSheme *p = NULL );
	CKnot( double, double, CSheme *p = NULL );
	CKnot( const CKnot& );
	virtual ~CKnot();
	CKnot& operator = ( const CKnot& );

};

#endif // !defined(AFX_KNOT_H__A9AC9422_C7EA_11D2_AF23_BB2B1C460D22__INCLUDED_)