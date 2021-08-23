// ShemePtr.cpp: implementation of the ShemePtr class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "NSys2D.h"
#include "ShemePtr.h"

#include "AlgolMatr.h"
#include "Elem.h"
#include "Sheme.h"

using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

bool ShemePtr::Construct()
{
	if( m_pSheme == NULL )
	{
		try
		{
			m_pSheme = new CSheme();
		}
		catch( bad_alloc& )
		{
			m_pSheme = NULL;
			return false;
		}
		AddRef( m_pSheme );
	}
	return true;
}

bool ShemePtr::RemoveRef( CSheme *pSh )
{
//ф-ция возвращает ИСТИНУ, если указатель уже можно удалять, 
//т.е. если на него никто не ссылается.
	if( pSh != NULL )
	{
		Refs::iterator it = m_RefMap.find(pSh);
		ASSERT( it != m_RefMap.end() );
		(*it).second--;
		if( (*it).second != 0 )	return false;
		m_RefMap.erase(it);
	}
	return true;
}

bool ShemePtr::AddRef( CSheme *pSh )
{
//ф-ция возвращает ИСТИНУ, только если такого указателя ещё не было
//и ссылка на него успешно установлена в 1.
//если же указатель нулевой (тогда вообще ничего не происходит)
//или такой указатель уже есть в карте (тогда инкрементируется счётчик ссылок на него),
//то вернётся ЛОЖЬ.
	if( pSh != NULL )
	{
		Pair p = m_RefMap.insert( MakeRef(pSh,1) );
		if( p.second )	return true;
		//значит такой указатель уже есть
		++(*p.first).second;
	}
	return false;
}

void ShemePtr::Destruct()
{
	if( m_pSheme )
	{
		if( RemoveRef(m_pSheme) )
		{
			delete m_pSheme;
			m_pSheme = NULL;
		}
	}
}

void ShemePtr::InitBy( const ShemePtr &obj )
{
	if( m_pSheme != obj.m_pSheme )
	{
		if( m_pSheme )
			Destruct();
		m_pSheme = obj.m_pSheme;
		if( m_pSheme )
		{
			bool res = AddRef( m_pSheme );
			ASSERT( res == false );
		}
	}
}

/*
CSheme* ShemePtr::GetSheme() const
{
	ASSERT(m_pSheme);
	return m_pSheme;
}
*/

std::string ShemePtr::GetName() const
{
	ASSERT(m_pSheme);
	return m_strShemeName;
}

bool ShemePtr::Open( const std::string &path )
{
	m_strShemeName = "";
	if( !Construct() )
		return false;

	m_pSheme->Clear();

	CString strPathName( path.c_str() );

	try
	{
		CFile F( strPathName, CFile::modeRead );
		CArchive ar( &F, CArchive::load );
		
		m_pSheme->Serialize( ar );

//		ar.Flush();
//		F.Flush();
//		F.Close();
	}
	catch( CException &ex )
	{
		const int N = 255;
		TCHAR szCause[N];
		CString strMes;
        ex.GetErrorMessage( szCause, N );
		strMes = _T("Ошибка при открытии файла: ");
		strMes += szCause;
		AfxMessageBox( strMes );
		return false;
	}
	m_strShemeName = path;
	return true;
}

bool ShemePtr::Close()
{
	m_strShemeName = "";
	Destruct();
	ASSERT( m_pSheme == NULL );
	return true;
}

bool ShemePtr::Save()
{
	if( (m_pSheme == NULL)||(m_strShemeName.empty()) )
		return false;

	CString strPathName( m_strShemeName.c_str() );
	try
	{
		CFile F( strPathName, CFile::modeCreate|CFile::modeWrite );
		CArchive ar( &F, CArchive::store );
		
		m_pSheme->Serialize( ar );

		ar.Flush();
		F.Flush();
		F.Close();
	}
	catch( CException &ex )
	{
		const int N = 255;
		TCHAR szCause[N];
		CString strMes;
        ex.GetErrorMessage( szCause, N );
		strMes = _T("Ошибка при сохранении файла: ");
		strMes += szCause;
		AfxMessageBox( strMes );
		return false;
	}
	return true;
}

bool ShemePtr::SaveAs( const std::string &path )
{
	m_strShemeName = "";
	if( m_pSheme == NULL ) 
		return false;

	CString strPathName( path.c_str() );
	try
	{
		CFile F( strPathName, CFile::modeCreate|CFile::modeWrite );
		CArchive ar( &F, CArchive::store );
		
		m_pSheme->Serialize( ar );

		ar.Flush();
		F.Flush();
		F.Close();
	}
	catch( CException &ex )
	{
		const int N = 255;
		TCHAR szCause[N];
		CString strMes;
        ex.GetErrorMessage( szCause, N );
		strMes = _T("Ошибка при сохранении файла: ");
		strMes += szCause;
		AfxMessageBox( strMes );
		return false;
	}
	m_strShemeName = path;
	return true;
}

bool ShemePtr::SetEVMethod( int evm )
{
	if( m_pSheme == NULL )
		return false;
	switch( evm )
	{
	case 0:
		m_pSheme->m_EVMethod = EVM_JACOBY;
		break;
	case 1:
		m_pSheme->m_EVMethod = EVM_QR_ELM;
		break;
	case 2:
		m_pSheme->m_EVMethod = EVM_QR_DIR;
		break;
	case 3:
		m_pSheme->m_EVMethod = EVM_QR_ORT;
		break;
	default:
		return false;
	}
	return true;
}

bool ShemePtr::GetEigen( AlgolMatr &Freqs, AlgolMatr &Forms )
{
	if( m_pSheme == NULL )
		return false;
	CMatr matrFreqs, matrForms;
	if( m_pSheme->GetEigen( matrFreqs, matrForms ) == false )
		return false;
	matrForms.ConvertToAlgolMatr( Forms );
	Forms.SetMinCol(0);
	Freqs.Resize( matrFreqs.SizeY, 1 );
	for( int r = 0; r < matrFreqs.SizeY; r++ )
		Freqs( r+1, 0 ) = matrFreqs[0][r];
	return true;
}

bool ShemePtr::SetParamIntegr( int iMethod, double dTime, double dStep )
{
	if( m_pSheme == NULL )
		return false;
	if( (iMethod != 0)&&(iMethod != 1)&&(iMethod != 2) )
		return false;
	m_pSheme->ParamIntegr.TypeMethod = iMethod;
	m_pSheme->ParamIntegr.Time = dTime;
	m_pSheme->ParamIntegr.Step = dStep;
	return true;
}

bool ShemePtr::Integrate()
{
	if( m_pSheme == NULL )
		return false;
	return (m_pSheme->Integrate() == 0);
}

bool ShemePtr::GetResY1( AlgolMatr &m )
{
	if( m_pSheme == NULL )
		return false;
	m_pSheme->matr_RezY1.ConvertToAlgolMatr( m );
	return true;
}

bool ShemePtr::GetResY2( AlgolMatr &m )
{
	if( m_pSheme == NULL )
		return false;
	m_pSheme->matr_RezY2.ConvertToAlgolMatr( m );
	return true;
}

bool ShemePtr::GetResY3( AlgolMatr &m )
{
	if( m_pSheme == NULL )
		return false;
	m_pSheme->matr_RezY3.ConvertToAlgolMatr( m );
	return true;
}

bool ShemePtr::GetMatrMDC( AlgolMatr &M, AlgolMatr &D, AlgolMatr &C )
{
	if( m_pSheme == NULL )
		return false;
	int Count = m_pSheme->UpdateAllFree();
	if( Count == 0 )
		return false;
	if( m_pSheme->SetMatrMDC(Count) != 0 )
		return false;
	m_pSheme->matr_M.ConvertToAlgolMatr( M );
	m_pSheme->matr_D.ConvertToAlgolMatr( D );
	m_pSheme->matr_C.ConvertToAlgolMatr( C );
	return true;
}

CElem* ShemePtr::GetElemByNum( int num )
{
	if( m_pSheme == NULL )
		return NULL;
	if( num < 0 )
		return NULL;
	return m_pSheme->GetElemByNum( num );
}

CKnot* ShemePtr::GetKnotByNum( int num )
{
	if( m_pSheme == NULL )
		return NULL;
	if( num < 0 )
		return NULL;
	return m_pSheme->GetKnotByNum( num );
}

bool ShemePtr::DelElem( CElem *pEl )
{
	if( (m_pSheme == NULL)||(pEl == NULL) )
		return false;
	return m_pSheme->DelElem( pEl );
}

bool ShemePtr::AddElement( CElem *pEl )
{
	if( (m_pSheme == NULL)||(pEl == false) )
		return false;
	return m_pSheme->AddElem( pEl );
}
