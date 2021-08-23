// ShemeGroup.cpp: implementation of the CShemeGroup class.
//
//////////////////////////////////////////////////////////////////////

#include<stdlib.h>

#include "StdAfx.h"
#include "NSys2D.h"
#include "ShemeGroup.h"

#include "StdAfxMy.h"

#include "Resource.h"
#include "Elem.h"
#include "Knot.h"

#include<algorithm>

using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

int CShemeGroup::m_iGrCounter = 0;
int CShemeGroup::m_iMaxItems = 200;
CString CShemeGroup::m_strElementsTypeName = CString("elements");
CString CShemeGroup::m_strKnotsTypeName = CString("knots");
//////////////////////////////////////////////////////////////////////
// Base class Construction/Destruction
//////////////////////////////////////////////////////////////////////
void CShemeGroup::Init( const CString& group, const CString& name, int type )
{
	m_strErrorMsg.Empty();
	m_strGroup = group;
	m_strName = name;
	m_iGroupType = type;
}

CShemeGroup::CShemeGroup( const CShemeGroup& gr )
{
	Init( gr.m_strGroup, gr.m_strName, gr.m_iGroupType );
	m_strErrorMsg = gr.m_strErrorMsg;
}

CShemeGroup::CShemeGroup( int type )
{
	CString gr, name;
	name.Format("��� ����� %d", m_iGrCounter );
	m_iGrCounter++;
	Init( gr, name, type );
}

CShemeGroup::CShemeGroup( const CString& group, int type )
{
	CString name;
	name.Format("��� ����� %d", m_iGrCounter );
	m_iGrCounter++;
	Init( group, name, type );
}

CShemeGroup::CShemeGroup( const CString& group, const CString& name, int type )
{
	m_iGrCounter++;
	Init( group, name, type );
}

CShemeGroup::~CShemeGroup()
{
	Clear();
}

int CShemeGroup::StringToInt( const CString& str )
{
	int num = atoi( str );
	if( num == 0 )
	{
		//�����-�� �� ��������� ������ !!!
		m_strErrorMsg.LoadString( IDS_GE_UNKNOWN );
		m_strErrorMsg += _T("\n��������: ������������� ������������� ������.");
	}
	return num;
}

void CShemeGroup::Clear()
{
	m_strGroup.Empty();
	m_strErrorMsg.Empty();
}

void CShemeGroup::SetName( const CString& name )
{
	m_strName = name;
}

void CShemeGroup::SetGroup( const CString& str )
{
	m_strGroup = str;
}

void CShemeGroup::GetName( CString& name ) const
{
	name = m_strName;
}

void CShemeGroup::GetGroup( CString& gr ) const
{
	gr = m_strGroup;
}

void CShemeGroup::GetErrorMessage( CString& em ) const
{
	em = m_strErrorMsg;
}

int CShemeGroup::GetType() const
{
	return m_iGroupType;
}

void CShemeGroup::SetType( int type )
{
	m_iGroupType = type;
}

//		Realisations:
/************************************************************/
bool CShemeGroup::Analize()
{
/*
	�-��� ���� ������, �� ����������� � ����������� �����.
	��� �� �������� ������, ��������� � ��������������
	������� � ������� ������ (GetNumSet), 
	��������: ������������ �������� ������ ��������.
*/
	//�������� �� ������ ���� ������
	if( m_strName.IsEmpty() )
	{
		m_strErrorMsg.LoadString( IDS_GE_NONAME );
		return false;
	}
	//�������� �� ������������ �������
	CString strCompare("0123456789 ,-");//����������
	int len = m_strGroup.GetLength();
	if( len == 0 )	return true;

	for( int p = 0; p < len; p++ )
	{
		CString ch( m_strGroup[p] );
		if( ch.FindOneOf(strCompare) == -1 )
		{
			//������������ ������
			m_strErrorMsg.LoadString( IDS_GE_WRONG_SYMBOL );
			CString simbol;
			simbol.Format(": %c", ch[0] );
			m_strErrorMsg += simbol;
			return false;
		}
	}

	//��������� ������������ ��������� "����"
	CString strTempGroup(m_strGroup);//��������� �����
	while( (p = strTempGroup.Find( _T("-") )) != -1 )
	{
		//���� ����� ���������� ������ ����� ����� �������
		if( (p == 0)||(p == (len-1)) )
		{
			m_strErrorMsg.LoadString( IDS_GE_WRONG_SYNTAX );
			m_strErrorMsg += _T(": ");
			m_strErrorMsg += m_strGroup.Left(p+1) + _T("?");
			m_strErrorMsg += m_strGroup.Right(len-p-1);
			return false;
		}
		for( int i = p-1; i >= 0; i-- )
		{
			//��� �����, ��������� �������, �� ������ �����
			if( (i == 0)&&((strTempGroup[i] == ',')||(strTempGroup[i] == '-')||(strTempGroup[i] == ' ')) )
			{
				m_strErrorMsg.LoadString( IDS_GE_WRONG_SYNTAX );
				m_strErrorMsg += _T(": ");
				m_strErrorMsg += m_strGroup.Left(p+1) + _T("?");
				m_strErrorMsg += m_strGroup.Right(len-p-1);
				return false;
			}
			if( strTempGroup[i] == ' ' )	continue;
			if( (strTempGroup[i] == ',')||(strTempGroup[i] == '-') )
			{
				m_strErrorMsg.LoadString( IDS_GE_WRONG_SYNTAX );
				m_strErrorMsg += _T(": ");
				m_strErrorMsg += m_strGroup.Left(i+1) + _T("?");
				m_strErrorMsg += m_strGroup.Right(len-i-1);
				return false;
			}
			//���� ��� �� ������ � �� ',' � �� '-',
			//����� ��� ����� ���� ������ �����
			break;
		}
		for( i = p+1; i < len; i++ )
		{
			//��� ������
			if( (i == (len-1))&&((strTempGroup[i] == ',')||(strTempGroup[i] == '-')||(strTempGroup[i] == ' ')) )
			{
				m_strErrorMsg.LoadString( IDS_GE_WRONG_SYNTAX );
				m_strErrorMsg += _T(": ");
				m_strErrorMsg += m_strGroup.Left(p+1) + _T("?");
				m_strErrorMsg += m_strGroup.Right(len-p-1);
				return false;
			}
			if( strTempGroup[i] == ' ' )	continue;
			if( (strTempGroup[i] == ',')||(strTempGroup[i] == '-') )
			{
				m_strErrorMsg.LoadString( IDS_GE_WRONG_SYNTAX );
				m_strErrorMsg += _T(": ");
				m_strErrorMsg += m_strGroup.Left(i+1) + _T("?");
				m_strErrorMsg += m_strGroup.Right(len-i-1);
				return false;
			}
			//���� ��� �� ������ � �� ',' � �� '-',
			//����� ��� ����� ���� ������ �����
			break;
		}
		//���������: ���� �� "��������" ���������: (1-5-3)
		CString tmp = strTempGroup.Right(len-p-1);
		int pos1 = tmp.Find(_T('-')), pos2 = tmp.Find(_T(','));
		//pos1 - ������� ���� ������, � pos2 - ������� �������
		if( pos1 != -1 )
		{
			//���� ����� ����, �� ��������� ��� ��� �� ���������
			//� ��������� �������?
			if( (pos2==-1)||(pos1<pos2) )
			{
				//������: ��� ������ ���� �� ������� �� ����� ����
				m_strErrorMsg.LoadString( IDS_GE_WRONG_SYNTAX );
				m_strErrorMsg += _T(": ");
				m_strErrorMsg += m_strGroup.Left(p+pos1+1) + _T("?");
				m_strErrorMsg += m_strGroup.Right(len-p-pos1-1);
				return false;
			}
		}
		//������ ���� ���������
		strTempGroup.SetAt( p, _T(',') );
	}
	
	//...

	//�� ��������
	return true;
}

bool CShemeGroup::GetNumSet( ARRAY& vec )
{
/*
	�-��� ������ ������, ���������� ������������������
	������� ���������, ��������� �� ������ ������ ������.
	��������!!! �� ������������� ������ �-��� ���������� 
	������� �-��� Analize, �.�. � GetNumSet ����������,
	��� ��������� ������ ���� �� �����.
	� ������ ������ �-��� ���������� false.
	����� ���� ����� ������ ����� �������� �-���� GetErrorMessage.
*/
	vec.clear();
	int len = m_strGroup.GetLength();
	if( len == 0 )	return true;

	CString strNoSp;//����� ������, �� ������� ������� �������
					//� ������������� �������

	for( int i = 0; i < len; i++ )
	{
		if( m_strGroup[i] == ',' )
		{
			if( i == 0 )	m_strGroup.SetAt(  i, _T(' ') );
			if( i == (len - 1) )	m_strGroup.SetAt(  i, _T(' ') );
			int j = i + 1;
			while( (j < len)&&( (m_strGroup[j] == ',')||(m_strGroup[j] == ' ') ) )
			{
				if( m_strGroup[j] == ' ' )	
				{
					j++;
					continue;
				}
				m_strGroup.SetAt(  j, _T(' ') );
				j++;
			}
		}
		if( m_strGroup[i] == ' ' )	continue;

		strNoSp += m_strGroup[i];
	}

	int p = -1;
	while( (p = strNoSp.Find(_T(','))) != -1 )
	{
		len = strNoSp.GetLength();
		if( p == 0 )
		{
			//�����-�� �� ��������� ������ !!!
			vec.clear();
			m_strErrorMsg.LoadString( IDS_GE_UNKNOWN );
			return false;
		}
		CString strNum( strNoSp.Left(p) );
		strNoSp = strNoSp.Right(len-p-1);

		//strNum �������� ��� ����� ��� �������� ( 1-6 )
		int range;
		if( (range = strNum.Find(_T('-'))) != -1 )
		{
			//��������
			if( range == 0 )
			{
				//�����-�� �� ��������� ������ !!!
				vec.clear();
				m_strErrorMsg.LoadString( IDS_GE_UNKNOWN );
				return false;
			}
			int len = strNum.GetLength();
			CString strLeft( strNum.Left(range) );
			CString strRight( strNum.Right(len-range-1) );

			int left = StringToInt( strLeft );
			if( left == 0 )
			{
				vec.clear();
				return false;
			}
			int right = StringToInt( strRight );
			if( right == 0 )
			{
				vec.clear();
				return false;
			}

			if( left == right )	vec.push_back(left);
			else
			{
				if( left > right )
				{
					int tmp = left;
					left = right;
					right = tmp;
				}
				//left<right
				if( (right-left+1) > m_iMaxItems )
				{
					m_strErrorMsg.LoadString( IDS_GE_TOMANYITEMS );
					CString tmp;
					tmp.Format(": %d.", right-left+1);
					m_strErrorMsg += tmp;
					vec.clear();
					return false;
				}

				for( int i = left; i <= right; i++ )
					vec.push_back( i );
			}
		}
		else
		{
			//�����
			int res = StringToInt( strNum );
			if( res == 0 )
			{
				vec.clear();
				return false;
			}
			vec.push_back(res);
		}
		if( vec.size() > m_iMaxItems )
		{
			m_strErrorMsg.LoadString( IDS_GE_TOMANYITEMS );
			CString tmp;
			tmp.Format(": %d.", vec.size() );
			m_strErrorMsg += tmp;
			vec.clear();
			return false;
		}
	}
	if( !strNoSp.IsEmpty() )
	{
		int range;
		if( (range = strNoSp.Find(_T('-'))) != -1 )
		{
			//��������
			if( range == 0 )
			{
				//�����-�� �� ��������� ������ !!!
				m_strErrorMsg.LoadString( IDS_GE_UNKNOWN );
				vec.clear();
				return false;
			}
			int len = strNoSp.GetLength();
			CString strLeft( strNoSp.Left(range) );
			CString strRight( strNoSp.Right(len-range-1) );

			int left = StringToInt( strLeft );
			if( left == 0 )
			{
				vec.clear();
				return false;
			}
			int right = StringToInt( strRight );
			if( right == 0 )
			{
				vec.clear();
				return false;
			}

			if( left == right )	vec.push_back(left);
			else
			{
				if( left > right )
				{
					int tmp = left;
					left = right;
					right = tmp;
				}
				//left<right
				if( (right-left+1) > m_iMaxItems )
				{
					m_strErrorMsg.LoadString( IDS_GE_TOMANYITEMS );
					CString tmp;
					tmp.Format(": %d.", right-left+1);
					m_strErrorMsg += tmp;
					vec.clear();
					return false;
				}

				for( int i = left; i <= right; i++ )
					vec.push_back( i );
			}
		}
		else
		{
			int res = StringToInt( strNoSp );
			if( res == 0 )
			{
				vec.clear();
				return false;
			}
			vec.push_back(res);
		}
	}
	if( vec.size() > m_iMaxItems )
	{
		m_strErrorMsg.LoadString( IDS_GE_TOMANYITEMS );
		CString tmp;
		tmp.Format(": %d.", vec.size() );
		m_strErrorMsg += tmp;
		vec.clear();
		return false;
	}
	//��������� ������ �������.
	//������ ���� �� ������������� � ������� ��������� ����������
	std::sort( vec.begin(), vec.end() );
	vec.assign( vec.begin(), std::unique_copy( vec.begin(), vec.end(), vec.begin() ) );
	return true;
}

CString CShemeGroup::GetPackedGroup( ARRAY numset )
{
/*
	�-��� ���������� ������, ���������� ���������, �����������
	������, ��������� �� ������ ����������� ������� �������
*/
	int n = numset.size();
	std::sort( numset.begin(), numset.end() );
	CString group;
	if( n == 0 )	return group;

	CString tmp;
	int prev = numset[0];
	bool first = true;
	for( int i = 1; i < n; ++i )
	{
		if( numset[i] == (prev+1) )
		{
			if( first )
			{
				if( i != 1 )	group += _T(',');
				tmp.Format("%d-", prev );
				group += tmp;
				first = false;
			}
			prev++;
			continue;
		}
		if( (first)&&(i!=1) )	group += _T(',');
		tmp.Format("%d", prev );
		group += tmp;
		first = true;
		prev = numset[i];
	}
	if( (n > 1)&&(numset[n-2] != (numset[n-1]-1)) )
		group += _T(',');
	tmp.Format("%d", prev );
	group += tmp;
	return group;
}

CString CShemeGroup::GetTypeName( int type )
{
	return (type==0)?(m_strElementsTypeName):(m_strKnotsTypeName);
}

int CShemeGroup::WhatType( const CString& str )
{
	m_strElementsTypeName.MakeUpper();
	CString type = str;
	type.MakeUpper();
	if( type.Compare(m_strElementsTypeName) == 0 )
		return 0;
	m_strKnotsTypeName.MakeUpper();
	if( type.Compare(m_strKnotsTypeName) == 0 )
		return 1;
	return -1;
}

bool operator < ( const CShemeGroup &a1, const CShemeGroup &a2 )
{
	return ( a1.m_strName.Compare( a2.m_strName ) < 0 );
}

bool operator == ( const CShemeGroup &a1, const CShemeGroup &a2 )
{
	return ( a1.m_strName.Compare( a2.m_strName ) == 0 );
}

CArchive& operator <<( CArchive& ar, const CShemeGroup& gr )
{
	ar << gr.m_iGroupType << gr.m_strName << gr.m_strGroup;
	return ar;
}

CArchive& operator >>( CArchive& ar, CShemeGroup& gr )
{
	ar >> gr.m_iGroupType >> gr.m_strName >> gr.m_strGroup;
	return ar;
}

int CShemeGroup::GetRealPosInGroup( const ARRAY& arDel, int sel )
{
//	�-��� ���������� �������� ������� ������ (������� ������ sel
//	� ���� �������) �� ������ ������� �������� (arDel),
//	��� 1 �������� ��� �����.
	int n = arDel.size(), p = 0;
	for( int i = 0; i < n; i++ )
	{
		if( arDel[i] == 1 )	continue;
		if( sel == p )	
		{
			p = i;
			break;
		}
		p++;
	}
	return p;
}

bool CShemeGroup::IsElemContainsInGroup( const CElem* elem, const ARRAY& vec )
{
//	�-��� ���������� ������, ���� ������ ������� ����������
//	� ������ ���������, �������� �������� ������� ��������� vec.
	ARRAY tmpvec = vec;
	ARRAY::iterator it;
	it = find( tmpvec.begin(), tmpvec.end(), elem->GetNumber() );
	if( it != tmpvec.end() )
		return true;
	return false;
}

bool CShemeGroup::IsKnotContainsInGroup( const CKnot* knot, const ARRAY& vec )
{
//	�-��� ���������� ������, ���� ������ ���� ����������
//	� ������ �����, �������� �������� ������� ����� vec.
	ARRAY tmpvec = vec;
	ARRAY::iterator it;
	it = find( tmpvec.begin(), tmpvec.end(), knot->Num );
	if( it != tmpvec.end() )
		return true;
	return false;
}
