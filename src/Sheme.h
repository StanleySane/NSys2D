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
#include "ShemeVarsTable.h"

class CEqualDegrees;
class CShemeDoc;
class ShemePtr;
class CElem;
class CProgressDlg;

typedef enum ShemeVersion
{
	VER_LE25 = 0,// ������ 2.5 � ����
	VER_EQ30,// ������ 3.0
	VER_EQ31//������ 3.1
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

	CShemeVarsTable m_VarsTable;//����� ���������� �����

	bool m_bRichCalc;//���������� - ���� �� �������� ���������� � ����
	//�������������� � ������� "��������������" (CProgressDlg)
	bool m_bValidateExpr;//���� � ���, ��� ���� ��������� ������������
	//���������� ���������.
	bool m_bIntegrTest;//���� � ���, ��� ��� �������������� ���� ��������� ������������.
	int m_InvertMethod;//����� �������������� �����
	//0 - ������� ������� ���������
	//1 - ��������� ������������ ����������� ������
	EV_METHOD m_EVMethod;//����� ������ ������.���� � ��������
	CEqualDegrees *m_pEqDeg;//��������� �� ������, ������� ���������
	//������������ ������ � ������ ������� ������ ��������
	bool m_bIsHardRod;//���� �� � ����� ���.��������
	int m_HardMethod;//����� ����� ���.��������
	//0 - ��� ������� ����
	//1 - � ��������
	//2 - ������� �.�., �� � ��������� �������� �������

	CMatr matr_M, matr_C, matr_D, matr_M_1, matr_RezY1, matr_RezY2, matr_RezY3;
	CMatr matr_UM, matr_UC, matr_UD;

	BOOL UEnable;

	ShemeVersion m_verShemeVersion;//������� ������ ���������� ��� ����������
	bool m_bAutoCorrect;//���� �� ����������������� ���� ��� ���������� � ���������� �������
	CString m_strDescription;//��������� �������� �����

	CFreqParam ParamFreq;
	CFreqParam ParamSpectrOut;
	CParamIntegr ParamIntegr;

	CShemeDoc *m_pDoc;
	CProgressDlg *pProgressDlg;

protected:
	CSheme();

public:
	friend class CShemeDoc;
	friend class ShemePtr;

	~CSheme();
	void Serialize( CArchive& ar );
	void Clear();
//	void Serialize1( CArchive& ar, int &count, ShemeVersion &ver );
//	void Serialize2( CArchive& ar, int &count, ShemeVersion &ver );

	CElem* AddDemf( CKnot*, CKnot* );
	CElem* AddRod( CKnot*, CKnot* );
	CElem* AddHardRod( CKnot*, CKnot* );
	CElem* AddSpring( CKnot*, CKnot* );
	CElem* AddMass( CKnot* );

	bool AddElem( CElem* );
	bool DelElem( CElem* );

	CElem* GetElemByNum( int );
	CKnot* GetKnotByNum( int );

	static ARRAY::iterator CSheme::GetElemIteratorInGroup( const CElem*, ARRAY& );
	static ARRAY::iterator CSheme::GetKnotIteratorInGroup( const CKnot*, ARRAY& );
	int IsGroupContainsNotexistingObject( bool, CShemeGroup&, CString&, ARRAY& );
	bool IsElemGroupOfOneType( const ARRAY& vec );
	bool IsShemeContainsHardRod();
	bool IsXFree( int );
	bool IsYFree( int );

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
	int SetMatrMDC(int Count, std::string *pMsg = NULL, int Freq = 0 );
	bool CreateGroupForAllObjects( int type );

	int Integrate();
	int PreCalculated();

	int Numark( int );
	int Park( int );
	int RungeKutt( int );

	bool GetEigen( CMatr&, CMatr& );

};

#endif // !defined(AFX_SHEME_H__89D530E4_5477_11D6_B89D_FE2BA355A53D__INCLUDED_)
