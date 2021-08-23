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
	VER_LE25 = 0,// версия 2.5 и ниже
	VER_EQ30,// версия 3.0
	VER_EQ31//версия 3.1
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

	CShemeVarsTable m_VarsTable;//карта переменных схемы

	bool m_bRichCalc;//показывает - надо ли выводить информацию о ходе
	//интегрирования в диалоге "Интегрирование" (CProgressDlg)
	bool m_bValidateExpr;//флаг о том, что надо проверять правильность
	//вычисления выражений.
	bool m_bIntegrTest;//флаг о том, что при интегрировании надо проверять расходимость.
	int m_InvertMethod;//метод инвертирования матри
	//0 - решение системы уравнений
	//1 - обращение положительно определённых матриц
	EV_METHOD m_EVMethod;//метод поиска собств.форм и значений
	CEqualDegrees *m_pEqDeg;//указатель на объект, который управляет
	//модификацией матриц с учётом наличия жёстких стержней
	bool m_bIsHardRod;//есть ли в схеме жёст.стержень
	int m_HardMethod;//метод учёта жёст.стержней
	//0 - без разноса масс
	//1 - с разносом
	//2 - обычный К.Э., но с удалением степеней свободы

	CMatr matr_M, matr_C, matr_D, matr_M_1, matr_RezY1, matr_RezY2, matr_RezY3;
	CMatr matr_UM, matr_UC, matr_UD;

	BOOL UEnable;

	ShemeVersion m_verShemeVersion;//текущая версия документов для сохранения
	bool m_bAutoCorrect;//флаг об автокорректировке схем при сохранении в устаревшем формате
	CString m_strDescription;//текстовое описание схемы

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
