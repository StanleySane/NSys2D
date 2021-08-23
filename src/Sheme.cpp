// Sheme.cpp: implementation of the CSheme class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "NSys2D.h"
#include "Sheme.h"

#include "StdAfxMy.h"

#include "ShemeDoc.h"
#include "ShemeGroup.h"
#include "GroupEditDlg.h"
#include "EqualDegrees.h"
#include "Elem.h"
#include "Rod.h"
#include "HardRod.h"
#include "Spring.h"
#include "Mass.h"
#include "Demf.h"
#include "ProgressDlg.h"
#include "MovieView.h"

#include<algorithm>
#include<limits>

using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#ifdef max
#undef max
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSheme::CSheme()
{
	m_pDoc = NULL;
	try
	{
		m_pEqDeg = new CEqualDegrees();
	}
	catch( bad_alloc& )
	{
		m_pEqDeg = NULL;
	}
	m_bIntegrTest = false;
	m_EVMethod = EVM_QR_DIR;

	m_bIsHardRod = false;

	m_InvertMethod = 1;
	m_HardMethod = 0;
	m_verShemeVersion = VER_EQ31;// версия 3.1
	m_bAutoCorrect = true;
	m_bValidateExpr = false;

	m_bRichCalc = false;

	pProgressDlg = NULL;
}

CSheme::~CSheme()
{
	Clear();
	/*
	delete m_pEqDeg;
	POSITION pos=listElem.GetHeadPosition();
	while (pos)
	{
		CElem *el = listElem.GetNext(pos);
		if( el )
			delete el;
	}
	*/
}

void CSheme::Clear()
{
//ф-ция полностью очищает схему
	ASSERT( pProgressDlg == NULL );

	delete m_pEqDeg;
	m_pEqDeg = NULL;
	//удаляем все элементы и узлы:
	ClearElem();
	DelFreeKnot();
	//группы:
	m_vecElemGroups.erase( m_vecElemGroups.begin(), m_vecElemGroups.end() );
	m_vecKnotGroups.erase( m_vecKnotGroups.begin(), m_vecKnotGroups.end() );
	//списки:
	listspectrP.Clear();
	listspectrU.Clear();
	//матрицы:
	matr_M.Clear();
	matr_C.Clear();
	matr_D.Clear();
	matr_M_1.Clear();
	matr_RezY1.Clear();
	matr_RezY2.Clear();
	matr_RezY3.Clear();
	matr_UM.Clear();
	matr_UC.Clear();
	matr_UD.Clear();
}
//////////////////////////////////////////////////////////////////////
// Members Functions
//////////////////////////////////////////////////////////////////////

bool CSheme::AddElem( CElem *elem )
{
//ф-ция добавляет в схему элемент elem, если это возможно.
//в отличие от ф-ций типа AddDemf, AddMass и т.п. эта ф-ция
//добавляет в схему полностью сформированный элемент,
//а не создаёт новый по двум узлам.
//ф-ция добавлена для её использования в скриптах.
	ASSERT(elem);
	POSITION pos = listElem.GetHeadPosition();
	while( pos )
	{
		CElem *p = listElem.GetNext(pos);
		if( p == elem )
			return false;
		if( ((p->knot1 == elem->knot1)&&(p->knot2 == elem->knot2))||
			((p->knot2 == elem->knot1)&&(p->knot1 == elem->knot2)) )
		{
			//если с такими узлами уже есть элемент, то проверяем
			//не составят ли они пару "пружина-демпфер"?
			//если нет, то добавлять нельзя.
			if( (elem->TypeElem != IDC_DEMF)&&(elem->TypeElem != IDC_SPRING) )
				return false;
			if( (p->TypeElem != IDC_DEMF)&&(p->TypeElem != IDC_SPRING) )
				return false;
			if( ((elem->TypeElem == IDC_DEMF)&&(p->TypeElem == IDC_DEMF))||
				((elem->TypeElem == IDC_SPRING)&&(p->TypeElem == IDC_SPRING)) )
				return false;
		}
	}
	elem->m_pSheme = this;
	listElem.AddTail( elem );
	//устанавливаем номер элемента
	elem->SetNumber( GetNotExistingElemNum() );
	return true;
}

CElem* CSheme::AddDemf( CKnot *knot1, CKnot *knot2 )
{
	CElem *demf;
	
	POSITION pos = listElem.GetHeadPosition();
	while( pos )
	{
		demf = listElem.GetNext(pos);
		if ( ((demf->knot1==knot1)&&(demf->knot2==knot2))||
			 ((demf->knot1==knot2)&&(demf->knot2==knot1)) )
		{
			if( demf->TypeElem == IDC_SPRING )
				continue;			
			return demf;
		}
	}
	demf = new CDemf( knot1, knot2, this );
	listElem.AddTail( demf );
	//устанавливаем номер элемента
	demf->SetNumber( GetNotExistingElemNum() );

	if( m_pDoc )
		m_pDoc->SetModifiedFlag();
	return demf;
}

CElem* CSheme::AddRod( CKnot *knot1, CKnot *knot2 )
{
	CElem *prod;
	
	POSITION pos=listElem.GetHeadPosition();
	while (pos)
	{
		prod=listElem.GetNext(pos);
		if ( ((prod->knot1==knot1)&&(prod->knot2==knot2))||
			 ((prod->knot1==knot2)&&(prod->knot2==knot1)) )
		{
			return prod;
		}
	}
	prod = new CRod( knot1, knot2, this );

	knot1->FriendCoord=knot2->GetCoord();
	knot2->FriendCoord=knot1->GetCoord();

	listElem.AddTail(prod);
	//устанавливаем номер элемента
	prod->SetNumber( GetNotExistingElemNum() );

	if(m_pDoc)
		m_pDoc->SetModifiedFlag();
	return prod;
}

CElem* CSheme::AddHardRod( CKnot *knot1, CKnot *knot2 )
{
	CElem *pHardRod;
	
	POSITION pos = listElem.GetHeadPosition();
	while (pos)
	{
		pHardRod = listElem.GetNext(pos);
		if( ((pHardRod->knot1==knot1)&&(pHardRod->knot2==knot2))||
			 ((pHardRod->knot1==knot2)&&(pHardRod->knot2==knot1)) )
		{
			return pHardRod;
		}
	}

	pHardRod = new CHardRod( knot1, knot2, this );

//	knot1->FriendCoord=knot2->GetCoord();
//	knot2->FriendCoord=knot1->GetCoord();

	listElem.AddTail(pHardRod);
	//устанавливаем номер элемента
	pHardRod->SetNumber( GetNotExistingElemNum() );

	if(m_pDoc)
		m_pDoc->SetModifiedFlag();
	return pHardRod;
}

CElem* CSheme::AddSpring( CKnot *knot1, CKnot *knot2 )
{
	CElem *sprn;
	
	POSITION pos=listElem.GetHeadPosition();
	while (pos)
	{
		sprn=listElem.GetNext(pos);
		if ( ((sprn->knot1==knot1)&&(sprn->knot2==knot2))||
			 ((sprn->knot1==knot2)&&(sprn->knot2==knot1)) )
		{
			if (sprn->TypeElem==IDC_DEMF) continue;
			return sprn;
		}
	}
	sprn = new CSpring( knot1, knot2, this );
	listElem.AddTail(sprn);
	//устанавливаем номер элемента
	sprn->SetNumber( GetNotExistingElemNum() );

	if(m_pDoc)
		m_pDoc->SetModifiedFlag();
	return sprn;
}

CElem* CSheme::AddMass( CKnot *knot1 )
{
	CElem *mass;
	
	POSITION pos=listElem.GetHeadPosition();
	while (pos)
	{
		mass=listElem.GetNext(pos);
		if ( (mass->knot1==knot1)&&(mass->TypeElem==IDC_MASS) )
		{
			return mass;
		}
	}
	mass = new CMass( knot1, this );
	listElem.AddTail(mass);
	//устанавливаем номер элемента
	mass->SetNumber( GetNotExistingElemNum() );
	
	if(m_pDoc)
		m_pDoc->SetModifiedFlag();
	return mass;
}

void CSheme::ClearElem()
{
	POSITION pos=listElem.GetHeadPosition();
	while (pos)
	{
		delete listElem.GetNext(pos);
	}
	listElem.RemoveAll();
}

int CSheme::GetNotExistingElemNum()
{
	//Определение номера элемента
	int NewNum = 0;
	bool bExistNum = true;
	while( bExistNum )
	{
		bExistNum = false;
		NewNum++;
		POSITION pos = listElem.GetHeadPosition();
		while( pos )
		{
			if( listElem.GetNext(pos)->GetNumber() == NewNum )	
				bExistNum = true;
		}
	}
	return NewNum;
}

void CSheme::ClearAllSelectings()
{
//	Ф-ция снимает со всех элементов и узлов флаг о выделении
	POSITION pos = listElem.GetHeadPosition();
	if( !pos )	return;

	while( pos )
	{
		CElem *elem = listElem.GetNext(pos);
		elem->SelectMode = elem->knot1->SelectMode = elem->knot2->SelectMode = 0;
	}
}

void CSheme::CorrectGroups()
{
//	Ф-ция перенумеровывает узлы и элементы и меняет соответствующие
//	номера в группах
	if( !m_vecElemGroups.empty() )
	{
		if( listElem.GetCount() > 0 )
		{
			ARRAY oldNum, newNum;
			int count = 0;
			POSITION pos = listElem.GetHeadPosition();
			CElem *pElem;

			while( pos )
			{
				pElem = listElem.GetNext(pos);
				oldNum.push_back( pElem->GetNumber() );
				count++;
				pElem->SetNumber( count );
				newNum.push_back( count );
			}
			int s = m_vecElemGroups.size();
			for( int i = 0; i < s; i++ )
			{
				ARRAY set;
				m_vecElemGroups[i].GetNumSet( set );
				int ss = set.size();
				for( int j = 0; j < ss; j++ )
				{
					ARRAY::iterator it;
					it = find( oldNum.begin(), oldNum.end(), set[j] );
					if( it != oldNum.end() )
					{
						//данный номер элемента надо заменить на новый
						set[j] = *( newNum.begin() + (it-oldNum.begin()) );
					}
				}
				m_vecElemGroups[i].SetGroup( CShemeGroup::GetPackedGroup(set) );
			}
		}
	}
	if( !m_vecKnotGroups.empty() )
	{
		if( listKnot.GetCount() > 0 )
		{
			ARRAY oldNum, newNum;
			int count = 0;
			POSITION pos = listKnot.GetHeadPosition();
			CKnot *pKnot;

			while( pos )
			{
				pKnot = listKnot.GetNext(pos);
				oldNum.push_back( pKnot->Num );
				count++;
				pKnot->Num = count;
				newNum.push_back( count );
			}
			int s = m_vecKnotGroups.size();
			for( int i = 0; i < s; i++ )
			{
				ARRAY set;
				m_vecKnotGroups[i].GetNumSet( set );
				int ss = set.size();
				for( int j = 0; j < ss; j++ )
				{
					ARRAY::iterator it;
					it = find( oldNum.begin(), oldNum.end(), set[j] );
					if( it != oldNum.end() )
					{
						//данный номер элемента надо заменить на новый
						set[j] = *( newNum.begin() + (it-oldNum.begin()) );
					}
				}
				m_vecKnotGroups[i].SetGroup( CShemeGroup::GetPackedGroup(set) );
			}
		}
	}
}

void CSheme::AfterCalc()
{
	matr_UM.Clear();
	matr_UD.Clear();
	matr_UC.Clear();

	POSITION pos=listKnot.GetHeadPosition();
	while (pos)
	{
		//проходим по всем узлам
		CKnot *kn=listKnot.GetNext(pos);
		kn->EndIntegr();
	}
}

int CSheme::ResetAllFree()
{
	//чистим узлы
	POSITION pos=listKnot.GetHeadPosition();
	while (pos)
	{
		CKnot *knot=listKnot.GetNext(pos);
		knot->nXRez=-1;
		knot->nYRez=-1;
		for (int i=0;i<knot->CntAngle;i++)
			knot->nARez[i]=-1;
	}

	//Проставляем -2 на используемых степенях свободы
	pos=listElem.GetHeadPosition();
	while (pos)
	{
		CElem *elem=listElem.GetNext(pos);
		elem->knot1->nXRez=-2;
		elem->knot1->nYRez=-2;
		elem->knot2->nXRez=-2;
		elem->knot2->nYRez=-2;
		if (elem->TypeElem==IDC_ROD)
		{
			CRod *rod=(CRod*)elem;
			//Если шарнирно, то 
			rod->FreeA1=0;
			rod->FreeA2=0;

			if (rod->knot1->ConnectType!=0) 
			{
				for (int i=0;i<rod->knot1->CntAngle;i++)
					if (rod->knot1->nARez[i]==-1) 
					{
						rod->knot1->nARez[i]=-2;
						rod->FreeA1=i;
						break;
					}
			}
			else 
			{
				rod->knot1->nARez[0]=-2;
			}

			if (rod->knot2->ConnectType!=0) 
			{
				for (int i=0;i<rod->knot2->CntAngle;i++)
					if (rod->knot2->nARez[i]==-1) 
					{
						rod->knot2->nARez[i]=-2;
						rod->FreeA2=i;
						break;
					}
			}
			else 
			{
				rod->knot2->nARez[0]=-2;
			}
		}

		if( elem->TypeElem == IDC_HARDROD)
		{
			CHardRod *Hrod=(CHardRod*)elem;
			//Если шарнирно, то 
			Hrod->FreeA1=0;
			Hrod->FreeA2=0;

			if( Hrod->knot1->ConnectType != 0 ) 
			{
				for( int i = 0; i < Hrod->knot1->CntAngle; i++ )
					if( Hrod->knot1->nARez[i] == -1 ) 
					{
						Hrod->knot1->nARez[i] = -2;
						Hrod->FreeA1 = i;
						break;
					}
			}
			else 
			{
				Hrod->knot1->nARez[0] = -2;
			}

			if( Hrod->knot2->ConnectType != 0 ) 
			{
				for( int i = 0; i < Hrod->knot2->CntAngle; i++ )
					if( Hrod->knot2->nARez[i] == -1 ) 
					{
						Hrod->knot2->nARez[i] = -2;
						Hrod->FreeA2 = i;
						break;
					}
			}
			else 
			{
				Hrod->knot2->nARez[0]=-2;
			}
		}//IDC_HARDROD

		if (elem->TypeElem==IDC_MASS)
		{
			CMass *mas=(CMass*)elem;
			if (mas->GetJp()>0) 
				mas->knot1->nARez[0]=-2;
		}
	}
	
	//устанавливаем связи для закрепленных степеней свободы
	pos=listKnot.GetHeadPosition();
	while (pos)
	{
		//проходим по всем элементам
		CKnot *kn=listKnot.GetNext(pos);
		kn->SetFixedKnot();
	}
	
	//считаем степени свободы и
	//заполняем номера степеней свободы
	int Count=0;
	pos=listKnot.GetHeadPosition();
	while (pos)
	{
		CKnot *knot=listKnot.GetNext(pos);
		if (knot->nXRez==-2) knot->nXRez=Count++;
		if (knot->nYRez==-2) knot->nYRez=Count++;
		for (int i=0;i<knot->CntAngle;i++)
			if (knot->nARez[i]==-2) knot->nARez[i]=Count++;
	}
	return Count;
}

int CSheme::UpdateAllFree()
{
	int Count = ResetAllFree();
/***************************************************************/
	m_bIsHardRod = false;
	if( Count == 0 )	return Count;
	//учёт абс.жёстких стержней
	delete m_pEqDeg;
	m_pEqDeg = new CEqualDegrees(Count);

	POSITION pos = listElem.GetHeadPosition();
	while(pos)
	{
		CElem *elem = listElem.GetNext(pos);
		if( elem->TypeElem == IDC_HARDROD )
		{
			CHardRod *Hrod = (CHardRod*)elem;

			double len = elem->GetLength(), ang = elem->GetAngle();
			CCoordD c1 = elem->knot1->GetCoord();
			CCoordD c2 = elem->knot2->GetCoord();
			double val;
//			if( c1.y == c2.y )	val = 0.0;
//			else	val = len*sin(ang);
			val = len*sin(ang);

			m_pEqDeg->AddTriple( elem->knot2->nXRez, 
								elem->knot1->nXRez, 
								elem->knot1->nARez[Hrod->FreeA1],
								val );

//			if( c1.x == c2.x )	val = 0.0;
//			else	val = len*cos(ang);
			val = len*cos(ang);

			m_pEqDeg->AddTriple( elem->knot2->nYRez, 
								elem->knot1->nYRez, 
								elem->knot1->nARez[Hrod->FreeA1],
								val );
			m_pEqDeg->AddPair( elem->knot1->nARez[Hrod->FreeA1],
								elem->knot2->nARez[Hrod->FreeA2]);
			m_bIsHardRod = true;
		}
	}
	m_pEqDeg->Prepare();
/***************************************************************/
	return Count;
}

int CSheme::SetBeginPosition()
{
	POSITION pos=listKnot.GetHeadPosition();
	string msg;
	while (pos)
	{
		//проходим по всем элементам
		CKnot *kn=listKnot.GetNext(pos);
		if (kn->nXRez>=0) 
		{
			matr_RezY1[kn->nXRez][0] = kn->GetUx( 0.0, 0.0, 0.0, 0.0, &msg );
			if( m_bValidateExpr && !msg.empty() )
			{
				AfxMessageBox( CString("Ошибка при вычислении выражения: ") + msg.c_str() );
				return -1;
			}
			matr_RezY2[kn->nXRez][0] = kn->GetUx( 0.0, 0.0, 0.0, 0.0, &msg, 1 );
			if( m_bValidateExpr && !msg.empty() )
			{
				AfxMessageBox( CString("Ошибка при вычислении выражения: ") + msg.c_str() );
				return -1;
			}
		}
		if (kn->nYRez>=0) 
		{
			matr_RezY1[kn->nYRez][0] = kn->GetUy( 0.0, 0.0, 0.0, 0.0, &msg );
			if( m_bValidateExpr && !msg.empty() )
			{
				AfxMessageBox( CString("Ошибка при вычислении выражения: ") + msg.c_str() );
				return -1;
			}
			matr_RezY2[kn->nYRez][0] = kn->GetUy( 0.0, 0.0, 0.0, 0.0, &msg, 1 );
			if( m_bValidateExpr && !msg.empty() )
			{
				AfxMessageBox( CString("Ошибка при вычислении выражения: ") + msg.c_str() );
				return -1;
			}
		}
		for( int i = 0; i < kn->CntAngle; i++ )
			if( kn->nARez[i] >= 0 )
			{
				matr_RezY1[kn->nARez[i]][0] = kn->GetUa( 0.0, 0.0, 0.0, 0.0, &msg );
				if( m_bValidateExpr && !msg.empty() )
				{
					AfxMessageBox( CString("Ошибка при вычислении выражения: ") + msg.c_str() );
					return -1;
				}
				matr_RezY2[kn->nARez[i]][0] = kn->GetUa( 0.0, 0.0, 0.0, 0.0, &msg, 1 );
				if( m_bValidateExpr && !msg.empty() )
				{
					AfxMessageBox( CString("Ошибка при вычислении выражения: ") + msg.c_str() );
					return -1;
				}
		}
	}
	return 0;
}

ARRAY::iterator CSheme::GetElemIteratorInGroup( const CElem* elem, ARRAY& vec )
{
	ARRAY::iterator it;
	it = find( vec.begin(), vec.end(), elem->GetNumber() );
	return it;
}

ARRAY::iterator CSheme::GetKnotIteratorInGroup( const CKnot* knot, ARRAY& vec )
{
	ARRAY::iterator it;
	it = find( vec.begin(), vec.end(), knot->Num );
	return it;
}

int CSheme::IsGroupContainsNotexistingObject( bool bElem, CShemeGroup& gr, CString& ErrorMsg, ARRAY& vec )
{
/*
	bElem - показывает что проверять - элементы (true) или узлы (false).
	Если переданная группа содержит номера несуществующих объектов
	(элементов или узлов), тогда возвращается 1.
	Если переданная группа некорректна синтаксически, то возвращается 2.
	В обоих случаях ErrorMsg будет содержать строку сообщения об ошибке.
	Если всё в порядке (группа корректна и содержит номера только существующих
	объектов), то возвращается 0, а vec будет содержать номера объектов группы.
*/
	if( !gr.GetNumSet( vec ) )
	{
		gr.GetErrorMessage( ErrorMsg );
		return 2;
	}

	POSITION pos;
	if( bElem )	pos = listElem.GetHeadPosition();
	else	pos = listKnot.GetHeadPosition();

	ARRAY tmpvec = vec;
	while( pos )
	{
		if( bElem )
		{
			CElem *elem = listElem.GetNext(pos);

			ARRAY::iterator it;
			if( (it = GetElemIteratorInGroup(elem,tmpvec)) != tmpvec.end() )
			{
				tmpvec.erase(it);
			}
		}
		else
		{
			CKnot *knot = listKnot.GetNext(pos);
			
			ARRAY::iterator it;
			if( (it = GetKnotIteratorInGroup(knot,tmpvec)) != tmpvec.end() )
			{
				tmpvec.erase(it);
			}
		}
	}
	if( !tmpvec.empty() )
	{
		ErrorMsg = _T("Группа содержит номер(а) несуществующих ");
		if( bElem )	ErrorMsg += _T("элементов:");
		else	ErrorMsg += _T("узлов:");

		int n = tmpvec.size();
		for( int i = 0; i < n; i++ )
		{
			CString tmp;
			tmp.Format("%d,", tmpvec[i] );
			ErrorMsg += tmp;
			if( ErrorMsg.GetLength() >= 200 )
			{
				tmp = CString(" и т.д.");
				ErrorMsg += tmp;
				break;
			}
		}
		ErrorMsg.SetAt( ErrorMsg.GetLength()-1, _T('!') );
		return 1;
	}
	ErrorMsg.Empty();
	return 0;
}

bool CSheme::CreateGroupForAllObjects( int type )
{
	ASSERT( (type==IDC_ROD)||(type==IDC_HARDROD)||(type==IDC_MASS)||(type==IDC_DEMF)||(type==IDC_SPRING) );
//	Ф-ция создаёт группу для всех объектов одного типа (type)
//	Например масс или стержней.
	ARRAY vec;
	POSITION pos = listElem.GetHeadPosition();
	while( pos )
	{
		CElem *elem = listElem.GetNext(pos);
		if( elem->TypeElem == type )
		{
			vec.push_back( elem->GetNumber() );
		}
	}
	if( vec.empty() )
	{
		CString str;
		str.LoadString(type);
		str = _T("Схема не содержит элементов типа\"") + str + _T("\"!");
		AfxMessageBox( str, MB_OK|MB_ICONEXCLAMATION );
		return false;
	}
	CString strGroup = CShemeGroup::GetPackedGroup( vec );
	CShemeGroup gr( strGroup, 0 );//группа для элементов
	CGroupEditDlg dlg( &gr );
	if( dlg.DoModal() == IDOK )
	{
		gr.SetName( dlg.m_strGroupName );
		gr.SetGroup( dlg.m_strGroup );
		//здесь полагаем, что группа уже была проверена на
		//корректность в самом диалоге.
		m_vecElemGroups.push_back( gr );
		return true;
	}
	return false;
}

int CSheme::DelFreeKnot()
{
	POSITION pos_old, pos=listKnot.GetHeadPosition();
	while (pos)
	{
		pos_old=pos;
		CKnot *kn=listKnot.GetNext(pos);
		BOOL busy=false;
		POSITION pos2=listElem.GetHeadPosition();
		while (pos2)
		{
			CElem *elem=listElem.GetNext(pos2);
			if ((elem->knot1==kn)||(elem->knot2==kn))
				busy=true;
		}
		if (!busy)
		{
			delete kn;
			listKnot.RemoveAt(pos_old);
		}
	}
	return 0;
}

bool CSheme::IsElemGroupOfOneType( const ARRAY& vec )
{
	POSITION pos = listElem.GetHeadPosition();
	if( !pos )	return true;

	int type;
	bool first = true;
	while( pos )
	{
		CElem *elem = listElem.GetNext(pos);

		if( CShemeGroup::IsElemContainsInGroup( elem, vec ) )
		{
			if( first )
			{
				type = elem->TypeElem;
				first = false;
			}
			else
			{
				if( elem->TypeElem != type )
					return false;
			}
		}
	}
	return true;
}

bool CSheme::IsXFree( int x )
{
	POSITION pos = listKnot.GetHeadPosition();
	while( pos )
	{
		if( listKnot.GetNext(pos)->nXRez == x )
			return true;
	}
	return false;	
}

bool CSheme::IsYFree( int y )
{
	POSITION pos = listKnot.GetHeadPosition();
	while( pos )
	{
		if( listKnot.GetNext(pos)->nYRez == y )
			return true;
	}
	return false;	
}

bool CSheme::IsShemeContainsHardRod()
{
	POSITION pos = listElem.GetHeadPosition();
	while( pos )
	{
		if( listElem.GetNext(pos)->TypeElem == IDC_HARDROD )
			return true;
	}
	return false;
}

//Вроде уже не используется
void CSheme::SetConnectElements()
{
	POSITION pos=listElem.GetHeadPosition();
	while (pos)
	{
		CElem *pElem=listElem.GetNext(pos);
		pElem->knot1->FriendCoord=pElem->knot2->GetCoord();
		pElem->knot2->FriendCoord=pElem->knot1->GetCoord();
	}
	pos=listElem.GetHeadPosition();
	while (pos)
	{
		CElem *pElem=listElem.GetNext(pos);
		if (pElem->TypeElem==IDC_ROD)
		{
			pElem->knot1->FriendCoord=pElem->knot2->GetCoord();
			pElem->knot2->FriendCoord=pElem->knot1->GetCoord();
		}
	}
}

void CSheme::ReNumElems()
{
//ф-ция перенумеровывает элементы в схеме по новому
	int count = 0;
	POSITION pos = listElem.GetHeadPosition();
	CElem *pElem;

	while( pos )
	{
		pElem = listElem.GetNext(pos);
		count++;
		pElem->SetNumber( count );
	}
}

int CSheme::SetMatrMDC( int Count, std::string *pMsg, int Freq/*=0*/)
{
	if (Count==0) return -1;

	//выделяем память
	matr_M.ReSize(Count,Count);
	matr_M_1.ReSize(Count,Count);
	matr_C.ReSize(Count,Count);
	matr_D.ReSize(Count,Count);

	//заполняем матрицы
	POSITION pos=listElem.GetHeadPosition();
	while (pos)
	{
		//проходим по всем элементам
		CElem *elem=listElem.GetNext(pos);
		/************************************************/
		if( (m_HardMethod == 1 )&&(elem->TypeElem == IDC_HARDROD) )
		{
			CHardRod *pHR = (CHardRod*)elem;
			pHR->m_HardMethod = m_HardMethod;
			
			int cLeft = 0, cRight = 0;
			POSITION posE = listElem.GetHeadPosition();
			while( posE )
			{
				if( listElem.GetAt(posE)->TypeElem == IDC_HARDROD )
				{
					if( listElem.GetAt(posE)->knot1 == elem->knot1 )
						cLeft++;
					if( listElem.GetAt(posE)->knot2 == elem->knot1 )
						cLeft++;
					if( listElem.GetAt(posE)->knot1 == elem->knot2 )
						cRight++;
					if( listElem.GetAt(posE)->knot2 == elem->knot2 )
						cRight++;
				}
				listElem.GetNext(posE);
			}

			pHR->m_NofHardRodsInOneKnot[0] = cLeft;
			pHR->m_NofHardRodsInOneKnot[1] = cRight;
			pHR->m_NofKnots = m_pEqDeg->CountKnots(elem->knot1->nARez[pHR->FreeA1]);
		}
		/************************************************/
		elem->SetMatrMDC( matr_M, matr_D, matr_C, pMsg );
		if( m_bValidateExpr && pMsg && !pMsg->empty() )
			return -1;
	}
	//проверка диагонали матрицы matr_C (можно убрать)
	for (int i=0;i<Count;i++)
	{
		if( fabs(matr_C[i][i]) < ZERO )
		{
			//ошибка, если эта степень свободы принадлежит гибкому стержню.
			bool IsErr = false;
			POSITION posE = listElem.GetHeadPosition();
			while( posE )
			{
				CElem *el = listElem.GetNext(posE);
				if( el->TypeElem == IDC_ROD )
				{
					if( (el->knot1->nXRez == i)||(el->knot1->nYRez == i)||
						(el->knot2->nXRez == i)||(el->knot2->nYRez == i) )
					{
						IsErr = true;
					}
					else
					{
						for( int k = 0; k < el->knot1->CntAngle; k++ )
						{
							if( el->knot1->nARez[k] == i )
							{
								IsErr = true;
							}
						}
						if( !IsErr )
						{
							for( k = 0; k < el->knot2->CntAngle; k++ )
							{
								if( el->knot2->nARez[k] == i )
								{
									IsErr = true;
								}
							}
						}
					}
				}
			}
			if( IsErr )
			{
				CString str;
				str.Format("Нулевая жесткость в узле № %d\n(степень свободы №%d)\nПродолжать проверку диагонали?",
					listKnot.FindNum(i), i );
				int res = AfxMessageBox( str, MB_YESNOCANCEL|MB_TASKMODAL|MB_ICONINFORMATION);
				if( res == IDNO )
					break;
				if( res == IDCANCEL )
					return -1;
			}
		}
	}
	//среднее диагональных элементов
	double avC=0, avD=0, avM=0;
	for (int t=0;t<matr_C.SizeY;t++)
	{
		avC+=matr_C[t][t];
		avD+=matr_D[t][t];
		avM+=matr_M[t][t];
	}
	avC/=matr_C.SizeY;	avD/=matr_D.SizeY;	avM/=matr_M.SizeY;
	if (avC==0) avC=1;
	if (avM==0) avM=1;
	
	if (!Freq)
	{
		//Поиск и подсчет кинематических возмущений
		int CntU=0;
		pos=listKnot.GetHeadPosition();
		while (pos)
		{
			CKnot *knot=listKnot.GetNext(pos);
			if ((knot->nXRez>=0)&&(knot->UxEnable)) knot->nXU=CntU++;
			else knot->nXU=-1;
			if ((knot->nYRez>=0)&&(knot->UyEnable)) knot->nYU=CntU++;
			else knot->nYU=-1;
		}
		UEnable=false;
		if (CntU>0)
		{
			//Устанавливаем флаг использования кинематического возмущения
			UEnable=true;
			
			//matr_UM.ReSize(Count, CntU);
			matr_UD.ReSize(Count, CntU);
			matr_UC.ReSize(Count, CntU);

			//Делаем копии нужных столбцов матрицы
			pos=listKnot.GetHeadPosition();
			while (pos)
			{
				CKnot *knot=listKnot.GetNext(pos);
				if (knot->nXU>=0) 
				{
					for (int i=0;i<matr_C.SizeY;i++)
					{
						matr_UD[i][knot->nXU]=matr_D[i][knot->nXRez];
						matr_UC[i][knot->nXU]=matr_C[i][knot->nXRez];
					}
				}
				if (knot->nYU>=0) 
				{
					for (int i=0;i<matr_C.SizeY;i++)
					{
						matr_UD[i][knot->nYU]=matr_D[i][knot->nYRez];
						matr_UC[i][knot->nYU]=matr_C[i][knot->nYRez];
					}
				}
			}

			//Чистим основные матицы
			pos=listKnot.GetHeadPosition();
			while (pos)
			{
				CKnot *knot=listKnot.GetNext(pos);
				if (knot->nXU>=0) 
				{
					for (int i=0;i<matr_C.SizeY;i++)
					{
						matr_C[i][knot->nXRez]=0;
						matr_C[knot->nXRez][i]=0;

						matr_D[i][knot->nXRez]=0;
						matr_D[knot->nXRez][i]=0;

						matr_M[i][knot->nXRez]=0;
						matr_M[knot->nXRez][i]=0;
					}
					matr_C[knot->nXRez][knot->nXRez]=avC;
					matr_D[knot->nXRez][knot->nXRez]=avD;
					matr_M[knot->nXRez][knot->nXRez]=avM;
				}
				if (knot->nYU>=0) 
				{
					for (int i=0;i<matr_C.SizeY;i++)
					{
						matr_C[i][knot->nYRez]=0;
						matr_C[knot->nYRez][i]=0;

						matr_D[i][knot->nYRez]=0;
						matr_D[knot->nYRez][i]=0;

						matr_M[i][knot->nYRez]=0;
						matr_M[knot->nYRez][i]=0;
					}
					matr_C[knot->nYRez][knot->nYRez]=avC;
					matr_D[knot->nYRez][knot->nYRez]=avD;
					matr_M[knot->nYRez][knot->nYRez]=avM;
				}
			}
		}
	}
	//Проверяем степени свободы с кинематическим возмущением
	pos=listKnot.GetHeadPosition();
	while (pos)
	{
		CKnot *knot=listKnot.GetNext(pos);
		if ((knot->nXRez>=0)&&(knot->UxEnable>=0)) 
		{
			if (matr_C[knot->nXRez][knot->nXRez]==0) 
				matr_C[knot->nXRez][knot->nXRez]=avC;
			if (matr_D[knot->nXRez][knot->nXRez]==0) 
				matr_D[knot->nXRez][knot->nXRez]=avD;
			if (matr_M[knot->nXRez][knot->nXRez]==0) 
				matr_M[knot->nXRez][knot->nXRez]=avM;
		}
		if ((knot->nYRez>=0)&&(knot->UyEnable>=0)) 
		{
			if (matr_C[knot->nYRez][knot->nYRez]==0) 
				matr_C[knot->nYRez][knot->nYRez]=avC;
			if (matr_D[knot->nYRez][knot->nYRez]==0) 
				matr_D[knot->nYRez][knot->nYRez]=avD;
			if (matr_M[knot->nYRez][knot->nYRez]==0) 
				matr_M[knot->nYRez][knot->nYRez]=avM;
		}
	}
/*****************************************************************/
////////////////////////////////////////////
#ifdef _DEBUG
	TRACE0("\n\nBefore modify M:\n");
	for( int r = 0; r < matr_M.SizeY; r++ )
	{
		TRACE1("\n%d>>> ", r);
		for( int c = 0; c < matr_M.SizeX; c++ )
		{
			TRACE1("%.5lf ", matr_M[r][c] );
		}
	}
#endif
////////////////////////////////////////////

	//модификация матриц если надо
	if( m_bIsHardRod )
	{
		m_pEqDeg->ModifyMatrMDC( matr_M, matr_D, matr_C );
		////////////////////////////////////////////
#ifdef _DEBUG
		TRACE0("\n\nAfter modify M:\n");
		for( int r = 0; r < matr_M.SizeY; r++ )
		{
			TRACE1("\n%d>>> ", r);
			for( int c = 0; c < matr_M.SizeX; c++ )
			{
				TRACE1("%.5lf ", matr_M[r][c] );
			}
		}
#endif
		////////////////////////////////////////////
	}
/*****************************************************************/
	//Ищем обратную матрицу
	int code;
	
	CMatr TempM(matr_M.SizeY,matr_M.SizeX);
	TempM=matr_M;
	matr_M_1 = TempM.GetInvert( code, m_InvertMethod );
	if (!code)
	{
		AfxMessageBox( _T("Ошибка в схеме."),MB_OK|MB_ICONSTOP);
		return -1;
	}
	return 0;
}

void CSheme::Serialize( CArchive& ar )
{
	if( ar.IsStoring() )
	{	// storing code
		if( m_verShemeVersion > VER_LE25 )
		{
			// если сохраняем в формате 3.0 и выше
			if( (!m_vecElemGroups.empty())||(!m_vecKnotGroups.empty()) )
			{
				if( (!m_bAutoCorrect)&&(AfxMessageBox("Схема содержит одну или несколько групп.\nКорректировать данные?",
					MB_YESNO|MB_TASKMODAL|MB_ICONQUESTION ) == IDYES) )
				{
					CorrectGroups();// корректировать номера в элементов/узлов в группах
				}
			}

			ar << long(-1);
			long int iReserved = 31;// так, на будущее
			CString strThisVersionSignature;
			switch(m_verShemeVersion)
			{
			case VER_EQ30:
				strThisVersionSignature.LoadString( IDS_SIGNATURE_30 );
				break;
			case VER_EQ31:
				strThisVersionSignature.LoadString( IDS_SIGNATURE );
				break;
			default:
				ASSERT(FALSE);
			}
			ar << strThisVersionSignature;
			ar << iReserved;
			if( m_verShemeVersion >= VER_EQ31 )
			{
				ar << m_strDescription;
				m_VarsTable.Serialize( ar );
			}
		}

		ar << listElem.GetCount();

		if( m_pDoc )
			m_pDoc->ParamView.Serialize( ar, m_verShemeVersion );
		else
		{
			CParamView tmp;
			tmp.Serialize( ar, m_verShemeVersion );
		}
		ParamIntegr.Serialize( ar, m_verShemeVersion );
		ParamFreq.Serialize( ar, m_verShemeVersion );
		ParamSpectrOut.Serialize( ar , m_verShemeVersion );
		//CElem
		POSITION pos=listElem.GetHeadPosition();
		while (pos)
		{
			CElem *pElem=listElem.GetNext(pos);

			ar << pElem->TypeElem;
			pElem->Serialize( ar, m_verShemeVersion );
		}

		//Совместная спектральная плотность
		ar << listspectrP.GetCount();
		pos=listspectrP.GetHeadPosition();
		while (pos)
		{
			CComplexSpectr *pCS=(CComplexSpectr*)listspectrP.GetNext(pos);
			pCS->Serialize( ar, m_verShemeVersion );
		}
		//Совместная спектральная плотность
		ar << listspectrU.GetCount();
		pos=listspectrU.GetHeadPosition();
		while (pos)
		{
			CComplexSpectr *pCS=(CComplexSpectr*)listspectrU.GetNext(pos);
			pCS->Serialize( ar, m_verShemeVersion );
		}

		if( m_verShemeVersion >= VER_EQ30 )
		{
			// если сохраняем в формате 3.0 и выше
			// группы:
			int s = m_vecElemGroups.size();
			ar << s;
			for( int i = 0; i < s; ++i )
			{
				ar << m_vecElemGroups[i];
			}
			s = m_vecKnotGroups.size();
			ar << s;
			for( i = 0; i < s; ++i )
			{
				ar << m_vecKnotGroups[i];
			}
			if( m_verShemeVersion >= VER_EQ31 )
			{
				ar << m_bAutoCorrect << m_bIntegrTest << m_HardMethod;
				ar << m_InvertMethod << m_bValidateExpr << m_bRichCalc;
			}
		}
	}
	else
	{	// loading code
		//ParamView
		long int count;
		ar >> count;

		CString strSignature;// сигнатура версии файла
		long int iReserved;// так, на будущее
		ShemeVersion ver = VER_LE25;// по умолчанию старая версия
		if( count < 0 )
		{
			//значит это версия с 3.0 и выше
			ar >> strSignature;
			CString strThisVersionSignature;
			strThisVersionSignature.LoadString( IDS_SIGNATURE );
			CString strVersion30Signature;
			strVersion30Signature.LoadString( IDS_SIGNATURE_30 );
			if( strSignature.Compare( strThisVersionSignature ) != 0 )
			{
				if( strSignature.Compare( strVersion30Signature ) != 0 )
				{
					// ошибка. файл неверной структуры или более
					// поздней версии
					CString mes("Файл некорректного формата или более поздней версии.\nПопытаться прочитать?");
					if( AfxMessageBox(mes, MB_YESNO|MB_TASKMODAL|MB_ICONEXCLAMATION) == IDNO )
					{
						AfxThrowArchiveException( CArchiveException::badIndex, ar.GetFile()->GetFilePath() );
						return;
					}
				}
				else	
					ver = VER_EQ30;
			}
			else	ver = VER_EQ31;
			ar >> iReserved;
			if( ver >= VER_EQ31 )
			{
				ar >> m_strDescription;
				m_VarsTable.Serialize( ar );
			}
			ar >> count;
		}
		try
		{
			if( m_pDoc )
				m_pDoc->ParamView.Serialize( ar, ver );
			else
			{
				CParamView tmp;
				tmp.Serialize( ar, ver );
			}
			ParamIntegr.Serialize( ar, ver );
			ParamFreq.Serialize( ar, ver );
			ParamSpectrOut.Serialize( ar, ver );
			//CElem
			listKnot.Clear();
			ClearElem();

			for (int i=0;i<count;i++)
			{
				int TypeElem;
				ar >> TypeElem;

				switch (TypeElem)
				{
				case IDC_SPRING: 
					{
						
						CSpring *pSpring = new CSpring( NULL, NULL, this );
						pSpring->Serialize( ar, ver );
						listElem.AddTail(pSpring);
						break;
					}
				case IDC_ROD:
					{
						CRod *pRod = new CRod( NULL, NULL, this );
						pRod->Serialize( ar, ver );
						listElem.AddTail(pRod);
						break;
					}
				case IDC_DEMF:
					{
						CDemf *pDemf = new CDemf( NULL, NULL, this );
						pDemf->Serialize( ar, ver );
						listElem.AddTail(pDemf);
						break;
					}
				case IDC_MASS:
					{
						CMass *pMass = new CMass( NULL, this );
						pMass->Serialize( ar, ver );
						listElem.AddTail(pMass);
						break;
					}
				case IDC_HARDROD:
					{
						CHardRod *pHardRod = new CHardRod( NULL, NULL, this );
						pHardRod->Serialize( ar, ver );
						listElem.AddTail(pHardRod);
						break;
					}
				default:
					ASSERT(FALSE);
					break;
				}
			}
			//Составление списка узлов с отсеиванием повторяющихся
			POSITION pos=listElem.GetHeadPosition();
			while (pos)
			{
				CElem *pElem=listElem.GetNext(pos);
			
				CKnot *pKn=listKnot.AddKnot(*(pElem->knot1));
				if (pKn!=pElem->knot1) 
					delete pElem->knot1;
				pElem->knot1=pKn;

				pKn=listKnot.AddKnot(*(pElem->knot2));
				if (pKn!=pElem->knot2) 
					delete pElem->knot2;
				pElem->knot2=pKn;
			}
			listKnot.ReNum();
		
			//Заполнение списка связей для стержней
			//Сначала проходим по всем элементам, а потом только через стержни
			SetConnectElements();

			//Совместная спектральная плотность
			ar >> count;
			listspectrP.Clear();
			for (i=0;i<count;i++)
			{
				CComplexSpectr *pCS=new CComplexSpectr;
				pCS->Serialize( ar, ver );

				CKnot *pKn=listKnot.AddKnot(*(pCS->pKn1));
				if (pKn!=pCS->pKn1) 
					delete pCS->pKn1;
				pCS->pKn1=pKn;

				pKn=listKnot.AddKnot(*(pCS->pKn2));
				if (pKn!=pCS->pKn2) 
					delete pCS->pKn2;
				pCS->pKn2=pKn;
			
				listspectrP.AddTail(pCS);
			}
			//Совместная спектральная плотность
			ar >> count;
			listspectrU.Clear();
			for (i=0;i<count;i++)
			{
				CComplexSpectr *pCS=new CComplexSpectr;
				pCS->Serialize( ar, ver );

				CKnot *pKn=listKnot.AddKnot(*(pCS->pKn1));
				if (pKn!=pCS->pKn1) 
					delete pCS->pKn1;
				pCS->pKn1=pKn;

				pKn=listKnot.AddKnot(*(pCS->pKn2));
				if (pKn!=pCS->pKn2) 
					delete pCS->pKn2;
				pCS->pKn2=pKn;
				
				listspectrU.AddTail(pCS);
			}
			listKnot.ReNum();

			if( ver >= VER_EQ30 )
			{
				// группы
				m_vecElemGroups.clear();
				m_vecKnotGroups.clear();
				ar >> count;
				for( i = 0; i < count; ++i )
				{
					CShemeGroup gr;
					ar >> gr;
					m_vecElemGroups.push_back(gr);
				}
				ar >> count;
				for( i = 0; i < count; ++i )
				{
					CShemeGroup gr(1);
					ar >> gr;
					m_vecKnotGroups.push_back(gr);
				}
				if( ver >= VER_EQ31 )
				{
					int ac, it, ve, rc;
					ar >> ac >> it >> m_HardMethod;
					m_bAutoCorrect = (ac != 0);
					m_bIntegrTest = (it != 0);
					ar >> m_InvertMethod >> ve >> rc;
					m_bValidateExpr = (ve != 0);
					m_bRichCalc = (rc != 0);
				}
			}//if( ver != VER_LE25 )
		}
		catch( CArchiveException &aex )
		{
			char strMes[ _MAX_PATH];
			if( aex.GetErrorMessage( strMes,  _MAX_PATH ) )
				AfxMessageBox( strMes, MB_OK|MB_TASKMODAL|MB_ICONEXCLAMATION );
			throw;
		}
	}// loading code
}

int CSheme::Integrate()
{
	int code = 0;
	bool bIsIntegr = false;
	try
	{
		if( m_pDoc )
		{
			m_pDoc->BeginWaitCursor();
			bIsIntegr = true;
		}

		if( PreCalculated() != 0 )
			return -1;

		if( m_pDoc )
		{
			m_pDoc->EndWaitCursor();
			bIsIntegr = false;
		}

		CString title( _T("Интегрирование схемы ") );
		if( m_pDoc )
			title += m_pDoc->GetTitle();
		ASSERT( pProgressDlg == NULL );
 		pProgressDlg = new CProgressDlg( 100, title );

		switch( ParamIntegr.TypeMethod )
		{
			case 0:
				code = RungeKutt(matr_RezY1.SizeX);
				break;
			case 1:
				code = Park(matr_RezY1.SizeX); 
				break;
			case 2: 
				code = Numark(matr_RezY1.SizeX); 
				break;
		};

		//if (code) //Интегрирование было прервано
		pProgressDlg->DestroyWindow();
		delete pProgressDlg;
		pProgressDlg = NULL;

		AfterCalc();

		if( m_pDoc )
		{
			if( (m_pDoc->m_pMovieView)&&(code == 0) )
				m_pDoc->m_pMovieView->InitMatr(m_pDoc);
			m_pDoc->UpdateAllViews(0);
		}
	}
	catch(...)
	{
		AfxMessageBox("При интегрировании произошло исключение!!!\nЗакройте приложение");
		if( m_pDoc && bIsIntegr )
		{
			m_pDoc->EndWaitCursor();
		}
	}
	return code;
}

int CSheme::PreCalculated()
{	
	//запрашиваем время, шаг и метод интегрирования
	if( m_pDoc )
	{
		if( m_pDoc->PreCalculated() )
			return -1;
	}
	/****************************************************/
	if( m_bIsHardRod )
	{
		if( (ParamIntegr.TypeMethod != 0)&&
			(ParamIntegr.TypeMethod != 2)&&
			(ParamIntegr.TypeMethod != 1) )
		{
			//если выбран не метод Рунге-Кутта или Ньюмарка или Парка,
			//то решать нельзя
			AfxMessageBox("Использование данного метода для жёст.стержней невозможно !!!",
				MB_OK|MB_ICONINFORMATION);
			return -1;
		}
	}
	/****************************************************/
	int Count = UpdateAllFree();
	string msg;
	int code = SetMatrMDC( Count, &msg );
	if( code )	
	{
		if( !msg.empty() )
			AfxMessageBox( CString("Ошибка вычисления выражения: ") + msg.c_str() );
		return -1;
	}

	//Выделение памяти под массивы интегрирования
	//перемещение
	int cntstep = static_cast<int>(ceil(ParamIntegr.Time/ParamIntegr.Step)+1);
	matr_RezY1.ReSize( Count, cntstep );
	//скорость
	matr_RezY2.ReSize( Count, cntstep );
	if( ParamIntegr.TypeMethod == 2 )
		matr_RezY3.ReSize( Count, cntstep );
	else
		matr_RezY3.ReSize( 1, 1 );
	
	//Подготовка для интегрирования со случайным возмущением
	POSITION pos = listKnot.GetHeadPosition();
	while(pos)
	{
		//проходим по всем элементам
		CKnot *kn = listKnot.GetNext(pos);
		kn->BeginIntegr(ParamIntegr.Time);
	}
	//установка начальных условий
	SetBeginPosition();

	return 0;
}

//Интегрирование методом Рунге-Кутта (nStep - число шагов плюс один)
int CSheme::RungeKutt( int nStep )
{
	CString strMethName(_T("Метод Рунге-Кутта"));
	if( m_bRichCalc )
		pProgressDlg->SetDetails( strMethName + _T("\r\nЗаполнение матриц") );
	else
		pProgressDlg->SetDetails( strMethName );
	CMatr mMD( matr_M.SizeY, matr_M.SizeX );
	CMatr mMC( matr_M.SizeY, matr_M.SizeX );
	int Psize = matr_M.SizeY;
	if( m_bIsHardRod )	Psize = m_pEqDeg->GetRealSize();
	CMatr mP( Psize, 1 );

	mMD = matr_M_1*matr_D;
	mMC = matr_M_1*matr_C;

	double h = ParamIntegr.Step;
	double mult = (h + h*h/2.0 + h*h*h/6.0 + h*h*h*h/24.0)*(-1.0);

	double MaxD;
	if( m_bIntegrTest )
	{
		MaxD = numeric_limits<double>::max();
	}

	bool FlagExit;
	string strMsg;
	CString tmpstr;
	for( int i = 1; i < nStep; i++ )
	{
		int im1 = i - 1;
		if( m_bRichCalc )
		{
			tmpstr.Format("\r\nВычисление момента времени %.16g", ParamIntegr.Step*i );
			tmpstr = strMethName + tmpstr;
			pProgressDlg->SetDetails( tmpstr );
		}
		//Обработка сообщений
		MSG msg;
		FlagExit = false;
		while( PeekMessage( &msg, pProgressDlg->m_Button.m_hWnd, WM_KEYDOWN, WM_LBUTTONUP, PM_REMOVE))   // Until WM_QUIT message
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
   			if((msg.message==WM_KEYDOWN)||(msg.message==WM_LBUTTONUP))
			{
				switch(msg.wParam)
				{
				case 0:
				case 13:
				case 27:
				case 32:	FlagExit=true; break;
				}
			}
		}
		while(PeekMessage(&msg, 0, 0, 0x0ffff, PM_REMOVE))   // Until WM_QUIT message
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (FlagExit)
		{
			break;
		}
		pProgressDlg->SetPos( static_cast<int>(100.0*i/nStep));

		//Очистка вектора правых частей
		if( m_bRichCalc )
			pProgressDlg->SetDetails( tmpstr + _T("\r\nЗаполнение вектора правых частей") );
		mP.ClearData();

		POSITION pos = listElem.GetHeadPosition();
		while (pos)
		{
			//проходим по всем элементам
			CElem *elem = listElem.GetNext(pos);
	//		if ( (elem->TypeElem==IDC_DEMF)||(elem->TypeElem==IDC_SPRING) )
				if (elem->SetMatrmP(mP, matr_RezY1, matr_RezY2, NULL, im1, ParamIntegr.Step*i, &strMsg )) 
				{
					AfxMessageBox( CString("Ошибка в вычислении выражения: ") + strMsg.c_str() );
					return -1;
				}
		}
		pos = listKnot.GetHeadPosition();
		while (pos)
		{
			//проходим по всем элементам
			CKnot *knot = listKnot.GetNext(pos);
			if( knot->SetMatrmP( mP, matr_RezY1, 
				matr_RezY2, NULL, im1, 
				ParamIntegr.Step*i, 
				matr_UM, matr_UD, matr_UC, &strMsg ) )
			{
				AfxMessageBox( CString("Ошибка в вычислении выражения: ") + strMsg.c_str() );
				return -1;
			}
		}
		pos = listKnot.GetHeadPosition();
		while (pos)
		{
			//проходим по всем элементам
			CKnot *knot = listKnot.GetNext(pos);
			if( knot->SetMatrmP( mP, matr_RezY1, 
				matr_RezY2, NULL, im1, ParamIntegr.Step*i, &strMsg ) ) 
			{
				AfxMessageBox( CString("Ошибка в вычислении выражения: ") + strMsg.c_str() );
				return -1;
			}
		}

		if( m_bRichCalc )
			pProgressDlg->SetDetails( tmpstr + _T("\r\nНепосредственное вычисление точки") );
		Psize = matr_RezY1.SizeY;
		int short_size = m_pEqDeg->GetModifiedSize();
		if( m_bIsHardRod )	Psize = short_size;
		CMatr tmpVect( Psize, 1);
		
		/////////////////////////////////////////////////////////
		//учёт жёст.стержней если надо
		if( m_bIsHardRod )
		{
			CMatr tmpRezY1( short_size,matr_RezY1.SizeX ),
					tmpRezY2( short_size, matr_RezY2.SizeX );

			for( int c = 0; c < matr_RezY1.SizeX; c++ )
			{
				CMatr tmp(matr_RezY1.SizeY, 1);
				for( int r = 0; r < matr_RezY1.SizeY; r++ )
				{
					//вырезаем из matr_RezY? столбец
					tmp[r][0] = matr_RezY1[r][c];
				}
				m_pEqDeg->ModifyVect(tmp);
				tmpRezY1.CopyVectTo( tmp, c );
				
			}
			for( c = 0; c < matr_RezY2.SizeX; c++ )
			{
				CMatr tmp(matr_RezY2.SizeY, 1);
				for( int r = 0; r < matr_RezY2.SizeY; r++ )
				{
					//вырезаем из matr_RezY? столбец
					tmp[r][0] = matr_RezY2[r][c];
				}
				m_pEqDeg->ModifyVect(tmp);
				tmpRezY2.CopyVectTo( tmp, c );
				
			}
			CMatr tmpP( mP.SizeY, mP.SizeX );
			tmpP = mP;
			m_pEqDeg->ModifyVect(tmpP);

			tmpVect = (mMD.MultOnCol(tmpRezY2,im1)-matr_M_1*tmpP+
					   mMC.MultOnCol(tmpRezY1,im1))*mult;
			m_pEqDeg->DeModifyVector(tmpVect);

		}
		else	tmpVect = (mMD.MultOnCol(matr_RezY2,im1)-matr_M_1*mP+
						   mMC.MultOnCol(matr_RezY1,im1))*mult;

		matr_RezY2.CopyVectTo( tmpVect, i );
		
		for (int j=0; j<matr_RezY1.SizeY;j++)
		{
			double ytmp = matr_RezY2[j][im1];
			matr_RezY1[j][i] = matr_RezY1[j][im1] + ytmp*(-mult);
			matr_RezY2[j][i] += ytmp;
			if( m_bIntegrTest )
			{
				double y1 = matr_RezY1[j][i];
				if( (y1 > MaxD)||(y1 < -MaxD) )
				{
					matr_RezY1[j][i] = 0.0;
					AfxMessageBox("Метод расходится");
					return -1;
				}
				double y2 = matr_RezY2[j][i];
				if( (y2 > MaxD)||(y2 < -MaxD) )
				{
					matr_RezY2[j][i] = 0.0;
					AfxMessageBox("Метод расходится");
					return -1;
				}
			}
		}

		if (UEnable)
		{
			//Установка кинематических перемещений и скоростей
			pos = listKnot.GetHeadPosition();
			while (pos)
			{
				//проходим по всем узлам
				CKnot *knot = listKnot.GetNext(pos);
				if( knot->SetKinematicPos( matr_RezY1, matr_RezY2, NULL, i, ParamIntegr.Step*i, &strMsg )) 
				{
					AfxMessageBox( CString("Ошибка при вычислении выражения: ") + strMsg.c_str() );
					return -1;
				}
			}
		}
	}
	return (FlagExit?-1:0);
}

int CSheme::Park( int nStep )
{
	//Стартуем методом Рунге-Кутта
	//Измельчение шага для увеличения точности
	int ReduceStep = nStep/3;
	if( ReduceStep > 5 )	ReduceStep = 5;
	double h = ParamIntegr.Step, tmp = 3*ReduceStep;
	ParamIntegr.Step = h/ReduceStep;
//	RungeKutt(3*ReduceStep);
	matr_RezY3.ReSize( matr_RezY1.SizeY, tmp+1 );
	int exitcode = Numark( tmp );

	CString strMethName(_T("Метод Парка"));
	if( m_bRichCalc )
		pProgressDlg->SetDetails( strMethName + _T("\r\nЗаполнение матриц") );
	else
		pProgressDlg->SetDetails( strMethName );

	matr_RezY3.ReSize(1,1);

	for( int k = 0; k < 3; k++ )
	{
		int kRS = k*ReduceStep;
		for( int i = 0; i < matr_RezY1.SizeY; i++ )
		{
			matr_RezY1[i][k] = matr_RezY1[i][kRS];
			matr_RezY2[i][k] = matr_RezY2[i][kRS];
		}
	}
	ParamIntegr.Step=h;
	if (exitcode) return -1;
	//RungeKutt(5);
	//Numark(5);

	//находим обратную матрицу левой части системы уравнений
	CMatr mM_1(matr_M.SizeY,matr_M.SizeX);
	int code;
	mM_1=(matr_M*(100.0/36.0/ParamIntegr.Step/ParamIntegr.Step)+matr_D*(10.0/6.0/ParamIntegr.Step)+matr_C).GetInvert(code,m_InvertMethod);
	if (!code)
	{
		AfxMessageBox( _T("Ошибка в схеме."),
						MB_OK|MB_ICONSTOP);
		return -1;
	}

	int Psize = matr_M.SizeY;
	if( m_bIsHardRod )
		Psize = m_pEqDeg->GetRealSize();
	CMatr mP(Psize,1);
//	CMatr mP(matr_M.SizeY,1);
	CMatr mF(matr_M.SizeY,1);

	double MaxD;
	if( m_bIntegrTest )
	{
		MaxD = numeric_limits<double>::max();
	}
	
	BOOL FlagExit;
	int nStepm1 = nStep - 1;
	double PIS6 = 6.0*ParamIntegr.Step;
	double tmp1 = 15.0/PIS6, tmp2 = 1.0/ParamIntegr.Step, tmp3 = 1.0/PIS6;
	tmp = PIS6*PIS6;
	double tmp4 = 10.0/tmp, tmp5 = 150.0/tmp, tmp6 = 10.0/PIS6/ParamIntegr.Step;
	CMatr M5D1 = matr_M*tmp5 + matr_D*tmp1, M6D2 = matr_M*tmp6 + matr_D*tmp2;
	CMatr M4D3 = matr_M*tmp4 + matr_D*tmp3;
	string strMsg;
	CString tmpstr;
	for( int i = 2; i < nStepm1; i++ )
	{
		int im1 = i - 1, im2 = i - 2, ip1 = i + 1;
		if( m_bRichCalc )
		{
			tmpstr.Format("\r\nВычисление момента времени %.16g", ParamIntegr.Step*i );
			tmpstr = strMethName + tmpstr;
			pProgressDlg->SetDetails( tmpstr );
		}
		//Обработка сообщений
		MSG msg;
		FlagExit=false;
		while (PeekMessage(&msg, pProgressDlg->m_Button.m_hWnd, WM_KEYDOWN, WM_LBUTTONUP, PM_REMOVE))   // Until WM_QUIT message
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if ((msg.message==WM_KEYDOWN)||(msg.message==WM_LBUTTONUP))
			{
				switch (msg.wParam)
				{
				case 0:
				case 13:
				case 27:
				case 32:	FlagExit=true; break;
				}
			}
		}
		while (PeekMessage(&msg, 0, 0, 0x0ffff, PM_REMOVE))   // Until WM_QUIT message
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (FlagExit)
		{
			break;
		}
		pProgressDlg->SetPos(int(100.0*i/nStep));

		//Заполняем вектор нелинейной части
		if( m_bRichCalc )
			pProgressDlg->SetDetails( tmpstr + _T("\r\nЗаполнение вектора правых частей") );
		mP.ClearData();

		//проходим по всем элементам
		POSITION pos = listElem.GetHeadPosition();
		while (pos)
		{
			CElem *elem = listElem.GetNext(pos);
			//if ( (elem->TypeElem==IDC_DEMF)||(elem->TypeElem==IDC_SPRING) )
				if (elem->SetMatrmP(mP, matr_RezY1, matr_RezY2, NULL, i, ParamIntegr.Step*(ip1), &strMsg )) 
				{
					AfxMessageBox( CString("Ошибка при вычислении выражения: ") + strMsg.c_str() );
					return -1;
				}
		}
		pos = listKnot.GetHeadPosition();
		while (pos)
		{
			//проходим по всем элементам
			CKnot *knot = listKnot.GetNext(pos);
			if( knot->SetMatrmP( mP, matr_RezY1,
				matr_RezY2, NULL, im1, ParamIntegr.Step*i,
				matr_UM, matr_UD, matr_UC, &strMsg )) 
			{
				AfxMessageBox( CString("Ошибка при вычислении выражения: ") + strMsg.c_str() );
				return -1;
			}
		}
		pos = listKnot.GetHeadPosition();
		while (pos)
		{
			//проходим по всем элементам
			CKnot *knot = listKnot.GetNext(pos);
			if( knot->SetMatrmP( mP, matr_RezY1,
				matr_RezY2, NULL, im1, ParamIntegr.Step*i, &strMsg ) ) 
			{
				AfxMessageBox( CString("Ошибка при вычислении выражения: ") + strMsg.c_str() );
				return -1;
			}
		}

		if( m_bRichCalc )
			pProgressDlg->SetDetails( tmpstr + _T("\r\nНепосредственное вычисление точки") );
		Psize = matr_RezY1.SizeY;
		int short_size = m_pEqDeg->GetModifiedSize();
		if( m_bIsHardRod )	Psize = short_size;
		CMatr tmpVect( Psize, 1);
		/////////////////////////////////////////////////////////
		//учёт жёст.стержней если надо
		if( m_bIsHardRod )
		{
			CMatr tmpRezY1( short_size, matr_RezY1.SizeX ),
				tmpRezY2( short_size, matr_RezY2.SizeX );

			for( int c = 0; c < matr_RezY1.SizeX; c++ )
			{
				CMatr tmp(matr_RezY1.SizeY, 1);
				for( int r = 0; r < matr_RezY1.SizeY; r++ )
				{
					//вырезаем из matr_RezY? столбец
					tmp[r][0] = matr_RezY1[r][c];
				}
				m_pEqDeg->ModifyVect(tmp);
				tmpRezY1.CopyVectTo( tmp, c );
				
			}
			for( c = 0; c < matr_RezY2.SizeX; c++ )
			{
				CMatr tmp(matr_RezY2.SizeY, 1);
				for( int r = 0; r < matr_RezY2.SizeY; r++ )
				{
					//вырезаем из matr_RezY? столбец
					tmp[r][0] = matr_RezY2[r][c];
				}
				m_pEqDeg->ModifyVect(tmp);
				tmpRezY2.CopyVectTo( tmp, c );
				
			}
			CMatr tmpP( mP.SizeY, mP.SizeX );
			tmpP = mP;
			m_pEqDeg->ModifyVect(tmpP);

			mF = matr_M.MultOnCol(tmpRezY2,i)*(tmp1)-
				matr_M.MultOnCol(tmpRezY2,im1)*(tmp2)+
				matr_M.MultOnCol(tmpRezY2,im2)*(tmp3)+
			
				(M5D1).MultOnCol(tmpRezY1,i)-

				(M6D2).MultOnCol(tmpRezY1,im1)+

				(M4D3).MultOnCol(tmpRezY1,im2)+
				tmpP;
			tmpVect = mM_1*mF;
			m_pEqDeg->DeModifyVector(tmpVect);
		}
		else	
		{
			mF = matr_M.MultOnCol(matr_RezY2,i)*(tmp1)-
				matr_M.MultOnCol(matr_RezY2,im1)*(tmp2)+
				matr_M.MultOnCol(matr_RezY2,im2)*(tmp3)+
			
				(M5D1).MultOnCol(matr_RezY1,i)-

				(M6D2).MultOnCol(matr_RezY1,im1)+

				(M4D3).MultOnCol(matr_RezY1,im2)+
				mP;
			tmpVect = mM_1*mF;
		}
		matr_RezY1.CopyVectTo( tmpVect, ip1 );

		for( int j = 0; j < matr_RezY2.SizeY; j++ )
		{
			double y1 = matr_RezY1[j][ip1];
			matr_RezY2[j][ip1] = (10*y1-15*matr_RezY1[j][i]+6*matr_RezY1[j][im1]-matr_RezY1[j][im2])/PIS6;
			if( m_bIntegrTest )
			{
				if( (y1 > MaxD)||(y1 < -MaxD) )
				{
					matr_RezY1[j][ip1] = 0.0;
					AfxMessageBox("Метод расходится");
					return -1;
				}
				double y2 = matr_RezY2[j][ip1];
				if( (y2 > MaxD)||(y2 < -MaxD) )
				{
					matr_RezY2[j][ip1] = 0.0;
					AfxMessageBox("Метод расходится");
					return -1;
				}
			}
		}

		if (UEnable)
		{
			//Установка кинематических перемещений и скоростей
			pos = listKnot.GetHeadPosition();
			while (pos)
			{
				//проходим по всем узлам
				CKnot *knot = listKnot.GetNext(pos);
				if (knot->SetKinematicPos( matr_RezY1, matr_RezY2, NULL, ip1, ParamIntegr.Step*(ip1), &strMsg )) 
				{
					AfxMessageBox( CString("Ошибка при вычислении выражения: ") + strMsg.c_str() );
					return -1;
				}
			}
		}
	}
	return (FlagExit?-1:0);
}

int CSheme::Numark( int nStep )
{
	CString strMethName(_T("Метод Ньюмарка"));
	if( m_bRichCalc )
		pProgressDlg->SetDetails( strMethName + _T("\r\nЗаполнение матриц") );
	else
		pProgressDlg->SetDetails( strMethName );

	double alpha = 0.5;
	double betta = 0.25, b2 = betta*2.0;
	double abm1 = alpha/betta - 1, a2bm1 = alpha/b2 - 1;
	double m_Step = ParamIntegr.Step;
	double bS = betta*m_Step, abS = alpha/bS;
		
	CMatr mMpr(matr_M.SizeY, matr_M.SizeX);
	int Psize = matr_M.SizeY;
	if( m_bIsHardRod )
		Psize = m_pEqDeg->GetRealSize();
	CMatr mP(Psize,1);
//	CMatr mP(matr_M.SizeY,1);

	mMpr = matr_M*(1.0/(bS*ParamIntegr.Step)) + 
		matr_D*abS + matr_C;
	int code;
	mMpr = mMpr.GetInvert(code,m_InvertMethod);
	if (!code)
	{
		AfxMessageBox("Ошибка при решении системы уравнений");
		return -1;
	}
	//CMatr matr_RezY3(matr_RezY1.SizeY, 1);
	matr_RezY3.ClearData();

	double MaxD;
	if( m_bIntegrTest )
	{
		MaxD = numeric_limits<double>::max();
	}

	double tmp1 = 1.0/b2-1, tmp2 = 1.0/bS, tmp3 = tmp2/m_Step, tmp4 = m_Step*a2bm1;
	CMatr MD1 = matr_M*tmp1 + matr_D*tmp4, MD2 = matr_M*tmp2 + matr_D*abm1;
	CMatr MD3 = matr_M*tmp3 + matr_D*abS;
	BOOL FlagExit;
	string strMsg;
	CString tmpstr;
	for( int i = 1; i < nStep; i++ )
	{
		int im1 = i - 1, iS = m_Step*i;
		FlagExit = false;
		if( m_bRichCalc )
		{
			tmpstr.Format("\r\nВычисление момента времени %.16g", ParamIntegr.Step*i );
			tmpstr = strMethName + tmpstr;
			pProgressDlg->SetDetails( tmpstr );
		}
		///////////////////////////////////////////////////////////////////////
		//Обработка сообщений
		MSG msg;
		while (PeekMessage(&msg, pProgressDlg->m_Button.m_hWnd, WM_KEYDOWN, WM_LBUTTONUP, PM_REMOVE))   // Until WM_QUIT message
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if ((msg.message==WM_KEYDOWN)||(msg.message==WM_LBUTTONUP))
			{
				switch (msg.wParam)
				{
				case 0:
				case 13:
				case 27:
				case 32:	FlagExit=true; break;
				}
			}
		}
		while (PeekMessage(&msg, 0, 0, 0x0ffff, PM_REMOVE))   // Until WM_QUIT message
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (FlagExit)
		{
			break;
		}
		pProgressDlg->SetPos(int(100.0*i/nStep));
		///////////////////////////////////////////////////////////////////////
		if( m_bRichCalc )
			pProgressDlg->SetDetails( tmpstr + _T("\r\nЗаполнение вектора правых частей") );
		//Очистка вектора правых частей
		mP.ClearData();

		POSITION pos = listElem.GetHeadPosition();
		while (pos)
		{
			//проходим по всем элементам
			CElem *elem = listElem.GetNext(pos);
			//if ( (elem->TypeElem==IDC_DEMF)||(elem->TypeElem==IDC_SPRING) )
				if (elem->SetMatrmP(mP, matr_RezY1, matr_RezY2, &matr_RezY3, im1, iS, &strMsg )) 
				{
					AfxMessageBox( CString("Ошибка в вычислении выражения: ") + strMsg.c_str() );
					return -1;
				}
		}
		pos = listKnot.GetHeadPosition();
		while (pos)
		{
			//проходим по всем узлам
			CKnot *knot = listKnot.GetNext(pos);
			if( knot->SetMatrmP( mP, matr_RezY1, matr_RezY2,
				&matr_RezY3, im1, iS,
				matr_UM, matr_UD, matr_UC, &strMsg ) ) 
			{
				AfxMessageBox( CString("Ошибка при вычислении выражения: ") + strMsg.c_str() );
				return -1;
			}
		}
		pos = listKnot.GetHeadPosition();
		while (pos)
		{
			//проходим по всем узлам
			CKnot *knot = listKnot.GetNext(pos);
			if( knot->SetMatrmP( mP, matr_RezY1, matr_RezY2,
				&matr_RezY3, im1, iS, &strMsg ) )
			{
				AfxMessageBox( CString("Ошибка при вычислении выражения: ") + strMsg.c_str() );
				return -1;
			}
		}

		if( m_bRichCalc )
			pProgressDlg->SetDetails( tmpstr + _T("\r\nНепосредственное вычисление точки") );
		Psize = matr_RezY1.SizeY;
		int short_size = m_pEqDeg->GetModifiedSize();
		if( m_bIsHardRod )	Psize = short_size;
		CMatr tmpVect( Psize, 1);
		//////////////////////////////////////////////////////////
		//учёт жёст.стержней если надо
		if( m_bIsHardRod )
		{
			CMatr tmpRezY1( short_size, matr_RezY1.SizeX ),
				tmpRezY2( short_size, matr_RezY2.SizeX ),
				tmpRezY3( short_size, matr_RezY3.SizeX );

			for( int c = 0; c < matr_RezY1.SizeX; c++ )
			{
				CMatr tmp(matr_RezY1.SizeY, 1);
				for( int r = 0; r < matr_RezY1.SizeY; r++ )
				{
					//вырезаем из matr_RezY? столбец
					tmp[r][0] = matr_RezY1[r][c];
				}
				m_pEqDeg->ModifyVect(tmp);
				tmpRezY1.CopyVectTo( tmp, c );
				
			}
			for( c = 0; c < matr_RezY2.SizeX; c++ )
			{
				CMatr tmp(matr_RezY2.SizeY, 1);
				for( int r = 0; r < matr_RezY2.SizeY; r++ )
				{
					//вырезаем из matr_RezY? столбец
					tmp[r][0] = matr_RezY2[r][c];
				}
				m_pEqDeg->ModifyVect(tmp);
				tmpRezY2.CopyVectTo( tmp, c );
				
			}
			for( c = 0; c < matr_RezY3.SizeX; c++ )
			{
				CMatr tmp(matr_RezY3.SizeY, 1);
				for( int r = 0; r < matr_RezY3.SizeY; r++ )
				{
					//вырезаем из matr_RezY? столбец
					tmp[r][0] = matr_RezY3[r][c];
				}
				m_pEqDeg->ModifyVect(tmp);
				tmpRezY3.CopyVectTo( tmp, c );
				
			}
			CMatr tmpP( mP.SizeY, mP.SizeX );
			tmpP = mP;
			m_pEqDeg->ModifyVect(tmpP);

			tmpVect = mMpr*((MD1).MultOnCol(tmpRezY3,im1)+
					(MD2).MultOnCol(tmpRezY2,im1)+
					(MD3).MultOnCol(tmpRezY1,im1)
					+tmpP);
			m_pEqDeg->DeModifyVector(tmpVect);
		}
		else	
		{
			tmpVect = mMpr*((MD1).MultOnCol(matr_RezY3,im1)+
					(MD2).MultOnCol(matr_RezY2,im1)+
					(MD3).MultOnCol(matr_RezY1,im1)
					+mP);
		}

		matr_RezY1.CopyVectTo( tmpVect, i );

		for( int j = 0; j < matr_RezY2.SizeY; j++ )
		{
			double y1 = matr_RezY1[j][i];
			matr_RezY2[j][i] = (y1-matr_RezY1[j][im1])*(abS)-
							  matr_RezY2[j][im1]*(abm1)-
							  matr_RezY3[j][im1]*tmp4;

			matr_RezY3[j][i] = (y1-matr_RezY1[j][im1])*(tmp3)-
							  matr_RezY2[j][im1]*(tmp2)-
							  matr_RezY3[j][im1]*(tmp1);
			if( m_bIntegrTest )
			{
				if( (y1 > MaxD)||(y1 < -MaxD) )
				{
					matr_RezY1[j][i] = 0.0;
					AfxMessageBox("Метод расходится");
					return -1;
				}
				double y2 = matr_RezY2[j][i];
				if( (y2 > MaxD)||(y2 < -MaxD) )
				{
					matr_RezY2[j][i] = 0.0;
					AfxMessageBox("Метод расходится");
					return -1;
				}
				double y3 = matr_RezY3[j][i];
				if( (y3 > MaxD)||(y3 < -MaxD) )
				{
					matr_RezY3[j][i] = 0.0;
					AfxMessageBox("Метод расходится");
					return -1;
				}
			}
		}
		if (UEnable)
		{
			//Установка кинематических перемещений и скоростей
			POSITION pos = listKnot.GetHeadPosition();
			while (pos)
			{
				//проходим по всем узлам
				CKnot *knot = listKnot.GetNext(pos);
				if (knot->SetKinematicPos( matr_RezY1,
					matr_RezY2, &matr_RezY3, i, iS, &strMsg )) 
				{
					AfxMessageBox( CString("Ошибка при вычислении выражения: ") + strMsg.c_str() );
					return -1;
				}
			}
		}
	}
	return (FlagExit?-1:0);
}

bool CSheme::GetEigen( CMatr &matr_Freq, CMatr &matr_Forms )
{
//ф-ция находит собств. частоты и формы схемы 
//и заносит их в матрицы matr_Freq и matr_Forms соответственно.
//в случае успеха возвращается true, иначе - false.
	int Count = UpdateAllFree();
	if( Count == 0 )
		return false;
	string msg;
	int code = SetMatrMDC( Count, &msg );
	if( code )
	{
		if( !msg.empty() )
			AfxMessageBox( CString("Ошибка вычисления выражения: ") + msg.c_str() );
		return false;
	}

	//Копируем данные
	matr_Forms.ReSize( matr_C.SizeY, matr_C.SizeY );
	matr_Freq.ReSize( matr_C.SizeY, matr_C.SizeY );
	matr_Freq = matr_M_1*matr_C;

	if( Count > 1 )
	{
		if( m_EVMethod == EVM_JACOBY )
		{
			//Вычисление собственных частот и форм колебаний методом Якоби
			code = matr_Freq.Eigen( &matr_Forms );
			if( code < 0 ) 
			{
				//AfxMessageBox( _T("Процесс нахождения собственных частот не сходится."),MB_OK|MB_ICONSTOP);
				//////////////////////////////////////////////////////////
				//демодификация форм если надо
				if( m_bIsHardRod )
				{
					m_pEqDeg->DeModifyMatrix( matr_Forms );
				}
				//////////////////////////////////////////////////////////
				return false;
			}
		}
		else
		{
			//вычисление собств.значений и форм QR-методом
			code = matr_Freq.GetEigenVecs( matr_Forms, m_EVMethod );
			if( code < 0 ) 
			{
				//////////////////////////////////////////////////////////
				//демодификация форм если надо
				if( m_bIsHardRod )
				{
					m_pEqDeg->DeModifyMatrix( matr_Forms );
				}
				//////////////////////////////////////////////////////////
				return false;
			}
		}//if(EVm==EVM_JACOBY)

////////////////////////////////////////////
#ifdef _DEBUG
			TRACE0("Before demodify:\n");
			for( int r = 0; r < matr_Forms.SizeY; r++ )
			{
				for( int c = 0; c < matr_Forms.SizeX; c++ )
				{
					TRACE1("%.5lf ", matr_Forms[r][c] );
				}
				TRACE0("\n");
			}
#endif
////////////////////////////////////////////
		//////////////////////////////////////////////////////////
		//демодификация форм если надо
		if( m_bIsHardRod )
		{
			m_pEqDeg->DeModifyMatrix( matr_Forms );
		}
		//////////////////////////////////////////////////////////
////////////////////////////////////////////
#ifdef _DEBUG
			TRACE0("After demodify:\n");
			for( r = 0; r < matr_Forms.SizeY; r++ )
			{
				for( int c = 0; c < matr_Forms.SizeX; c++ )
				{
					TRACE1("%.5lf ", matr_Forms[r][c] );
				}
				TRACE0("\n");
			}
#endif
////////////////////////////////////////////

		//Нормирование форм
		for( int i = 0; i < matr_Forms.SizeX; i++ )
		{
			double maxU = 0;
			POSITION pos = listKnot.GetHeadPosition();
			while( pos )
			{
				CKnot *kn = listKnot.GetNext(pos);
				if( kn->nXRez >= 0 ) 
				{
					double uu = matr_Forms[kn->nXRez][i];
					if( fabs(uu) > fabs(maxU) )	
						maxU = uu;
				}
				if( kn->nYRez >= 0 )
				{
					double uu = matr_Forms[kn->nYRez][i];
					if( fabs(uu) > fabs(maxU) )
						maxU = uu;
				}
			}
			if( fabs(maxU) > 0.4 )
			{
				double scl = (m_pDoc == NULL)?(1.0):(m_pDoc->ParamView.Scale);
				for( int j = 0; j < matr_Forms.SizeY; j++ )
					matr_Forms[j][i] *= 30.0/scl/maxU;
			}
		}
		//Извлекаем корень из квадратов частот и записываем в первую строку
		for( i = 0; i < matr_Freq.SizeY; i++ )
			matr_Freq[0][i] = sqrt(fabs(matr_Freq[i][i]));

		//Сортируем формы по возрастанию частот
		for( i = 0; i < matr_Freq.SizeX-1; i++ )
			for( int j = i+1; j < matr_Freq.SizeX; j++ )
				if( matr_Freq[0][i] > matr_Freq[0][j] )
				{
					double tmp = matr_Freq[0][i];
					matr_Freq[0][i] = matr_Freq[0][j];
					matr_Freq[0][j] = tmp;
					for( int k = 0; k < matr_Forms.SizeY; k++ )
					{
						tmp = matr_Forms[k][i];
						matr_Forms[k][i] = matr_Forms[k][j];
						matr_Forms[k][j] = tmp;
					}
				}
////////////////////////////////////////////
#ifdef _DEBUG
			TRACE0("After sort:\n");
			for( r = 0; r < matr_Forms.SizeY; r++ )
			{
				for( int c = 0; c < matr_Forms.SizeX; c++ )
				{
					TRACE1("%.5lf ", matr_Forms[r][c] );
				}
				TRACE0("\n");
			}
#endif
////////////////////////////////////////////
	}
	else
	{
		ASSERT( matr_Forms.SizeX == 1 );
		matr_Freq[0][0] = sqrt(matr_C[0][0]/matr_M[0][0]);
		matr_Forms[0][0] = 30.0/((m_pDoc == NULL)?(1.0):(m_pDoc->ParamView.Scale));
	}
	return true;
}

CElem* CSheme::GetElemByNum( int num )
{
//ф-ция ищет среди элементов схемы элемент с номером num и
//возвращает указатель на него, если такого элемента нет,
//то возвращается NULL.
	POSITION pos = listElem.GetHeadPosition();
	while( pos )
	{
		CElem *p = listElem.GetNext(pos);
		if( p->GetNumber() == num )
			return p;
	}
	return NULL;
}

CKnot* CSheme::GetKnotByNum( int num )
{
//ф-ция ищет среди узлов схемы узел с номером num и
//возвращает указатель на него, если такого узла нет,
//то возвращается NULL.
	POSITION pos = listKnot.GetHeadPosition();
	while( pos )
	{
		CKnot *p = listKnot.GetNext(pos);
		if( p->Num == num )
			return p;
	}
	return NULL;
}

bool CSheme::DelElem( CElem *elem )
{
//ф-ция удаляет из схемы элемент elem.
	ASSERT(elem);
	bool busy1 = false, busy2 = false;

	//Ищем элементы, присоединенные к выбранному
	POSITION pos = listElem.GetHeadPosition(), pos2 = pos;
	while( pos2 )
	{
		CElem *pEl = listElem.GetAt(pos2);
		if( pEl == elem )
			break;
		listElem.GetNext(pos2);
	}
	if( pos2 == false )
		return false;
	while( pos )
	{
		//получаем указатель на очередной элемент для поиска
		CElem *findelem = listElem.GetNext(pos);
		if( findelem != elem )
		{
			if( (findelem->knot1 == elem->knot1)||
				(findelem->knot2 == elem->knot1) )
				busy1 = true;
			if( (findelem->knot1 == elem->knot2)||
				(findelem->knot2 == elem->knot2) )
				busy2 = true;
		}
		if( busy1 && busy2 )
			break;
	}

	if( m_pDoc )
	{
		if( !busy1 )
			m_pDoc->CloseView( elem->knot1 );
		if( !busy2 )
			m_pDoc->CloseView( elem->knot2 );
	}
	//Удаление пустых узлов
	if( !busy1 )
	{
		listKnot.FindPos( elem->knot1, &pos );
		delete elem->knot1;
		listKnot.RemoveAt( pos );
	}
	if( (!busy2)&&(elem->knot1 != elem->knot2) )
	{
		listKnot.FindPos( elem->knot2, &pos );
		delete elem->knot2;
		listKnot.RemoveAt( pos );
	}
	//Удаление из списка
	delete elem;
	listElem.RemoveAt(pos2);
	SetConnectElements();
	return true;
}