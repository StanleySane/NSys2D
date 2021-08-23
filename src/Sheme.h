// Sheme.h: interface for the CSheme class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHEME_H__89D530E4_5477_11D6_B89D_FE2BA355A53D__INCLUDED_)
#define AFX_SHEME_H__89D530E4_5477_11D6_B89D_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "FreqParam.h"
#include "ParamIntegr.h"
#include "ListSpectr.h"
#include "ListKnot.h"
#include "ShemeGroup.h"
#include "Matr.h"

class CEqualDegrees;
class CShemeDoc;
class CElem;

typedef enum ShemeVersion
{
	VER_LE25 = 0,// ������ 2.5 � ����
	VER_EQ30// ������ 3.0
} ShemeVersion;

class CSheme
{
	CSheme& operator = ( const CSheme& );
	CSheme( const CSheme& );

public:
	CList<CElem*,CElem*> listElem;
	Groups m_vecElemGroups;
	Groups m_vecKnotGroups;

	CListKnot listKnot;
	CListSpectr listspectrP, listspectrU;

	EV_METHOD m_EVMethod;//����� ������ ������.���� � ��������
	CEqualDegrees *m_pEqDeg;//��������� �� ������, ������� ���������
	//������������ ������ � ������ ������� ������ ��������
	bool m_bIsHardRod;//���� �� � ����� ���.��������
	int m_HardMethod;//����� ����� ���.��������
	//0 - ��� ������� ����
	//1 - � ��������
	//2 - ������� �.�., �� � ��������� �������� �������
	bool m_bCondenceMass;//������������ �� ����� ����������� ��� �-�� ����?

	CMatr matr_M, matr_C, matr_D, matr_M_1, matr_RezY1, matr_RezY2, matr_RezY3;
	CMatr matr_UM, matr_UC, matr_UD;

	BOOL UEnable;

	ShemeVersion m_verShemeVersion;//������� ������ ���������� ��� ����������
	bool m_bAutoCorrect;//���� �� ����������������� ���� ��� ���������� � ���������� �������

	CFreqParam ParamFreq;
	CFreqParam ParamSpectrOut;
	CParamIntegr ParamIntegr;

	CShemeDoc *m_pDoc;

protected:
	CSheme();

public:
	friend class CShemeDoc;

	~CSheme();
	void Serialize( CArchive& ar );
//	void Serialize1( CArchive& ar, int &count, ShemeVersion &ver );
//	void Serialize2( CArchive& ar, int &count, ShemeVersion &ver );

	CElem* AddDemf( CKnot*, CKnot* );
	CElem* AddRod( CKnot*, CKnot* );
	CElem* AddHardRod( CKnot*, CKnot* );
	CElem* AddSpring( CKnot*, CKnot* );
	CElem* AddMass( CKnot* );

	static ARRAY::iterator CSheme::GetElemIteratorInGroup( const CElem*, ARRAY& );
	static ARRAY::iterator CSheme::GetKnotIteratorInGroup( const CKnot*, ARRAY& );
	int IsGroupContainsNotexistingObject( bool, CShemeGroup&, CString&, ARRAY& );
	bool IsElemGroupOfOneType( const ARRAY& vec );
	bool IsShemeContainsHardRod();

	int GetNotExistingElemNum();
	void ClearElem();
	void ClearAllSelectings();
	void CorrectGroups();
	void AfterCalc();

	int UpdateAllFree();
	int ResetAllFree();

	int SetBeginPosition();
	int DelFreeKnot();
	void SetConnectElements();
	void ReNumElems();
	int SetMatrMDC(int Count, int Freq = 0 );
	void CreateGroupForAllObjects( int type );

};

#endif // !defined(AFX_SHEME_H__89D530E4_5477_11D6_B89D_FE2BA355A53D__INCLUDED_)