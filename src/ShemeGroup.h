// ShemeGroup.h: interface for the CShemeGroup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHEMEGROUP_H__1FDB6282_7620_11D5_B89C_FE2BA355A53D__INCLUDED_)
#define AFX_SHEMEGROUP_H__1FDB6282_7620_11D5_B89C_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "StdAfxMy.h"

class CElem;
class CKnot;

class CShemeGroup  
{
	static int m_iGrCounter;
	static CString m_strElementsTypeName, m_strKnotsTypeName;
public:
    friend bool operator < ( const CShemeGroup &a1, const CShemeGroup &a2 );
    friend bool operator == ( const CShemeGroup &a1, const CShemeGroup &a2 );
	friend CArchive& operator <<( CArchive& ar, const CShemeGroup& gr );
	friend CArchive& operator >>( CArchive& ar, CShemeGroup& gr );

	static CString GetPackedGroup( ARRAY numset );
	static CString GetTypeName( int type );
	static int WhatType( const CString& );
	static int GetRealPosInGroup( const ARRAY&, int );
	static bool IsElemContainsInGroup( const CElem* elem, const ARRAY& vec );
	static bool IsKnotContainsInGroup( const CKnot* knot, const ARRAY& vec );

	void SetType( int type );
	int GetType() const;
	void Clear();
	void GetErrorMessage( CString& em ) const;
	virtual bool GetNumSet( ARRAY& vec );
	virtual bool Analize();
	void SetName( const CString& name );
	void SetGroup( const CString& str );
	void GetName( CString& name ) const;
	void GetGroup( CString& gr ) const;

	CShemeGroup( const CShemeGroup& gr );
	CShemeGroup( const CString& group, int type );
	CShemeGroup( const CString& group, const CString& name, int type );
	CShemeGroup( int type = 0 );
	virtual ~CShemeGroup();

private:
	void Init( const CString& group, const CString& name, int type );
	int StringToInt( const CString& str );

	int m_iGroupType;//тип группы: 0 - элементы, 1 - узлы
	CString m_strGroup;
	CString m_strErrorMsg;
	CString m_strName;
	static int m_iMaxItems;//максимальное число элементов
	//группы. Например, число конечных элементов.
};

/*
class CShemeElemsGroup : public CShemeGroup  
{
public:
    friend bool operator < ( const CShemeElemsGroup &a1, const CShemeElemsGroup &a2 );
    friend bool operator == ( const CShemeElemsGroup &a1, const CShemeElemsGroup &a2 );

	virtual bool GetNumSet( ARRAY& vec );
	virtual bool Analize();
	CShemeElemsGroup( const CString& str );
	CShemeElemsGroup( const CString& str, const CString& name );
	CShemeElemsGroup();
	CShemeElemsGroup( const CShemeElemsGroup& gr );
	virtual ~CShemeElemsGroup();

};
*/
typedef std::vector<CShemeGroup> Groups;

#endif // !defined(AFX_SHEMEGROUP_H__1FDB6282_7620_11D5_B89C_FE2BA355A53D__INCLUDED_)
