// Sheme.cpp: implementation of the CSheme class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "NSys2D.h"
#include "Sheme.h"

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

#include<algorithm>

using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
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
	m_EVMethod = EVM_QR_DIR;
	m_bCondenceMass = false;

	m_bIsHardRod = false;

	m_HardMethod = 0;
	m_verShemeVersion = VER_EQ30;// версия 3.0
	m_bAutoCorrect = false;
}

CSheme::~CSheme()
{
	delete m_pEqDeg;
	POSITION pos=listElem.GetHeadPosition();
	while (pos)
	{
		CElem *el = listElem.GetNext(pos);
		if( el )
			delete el;
	}
}

//////////////////////////////////////////////////////////////////////
// Members Functions
//////////////////////////////////////////////////////////////////////
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
	demf = new CDemf( knot1, knot2 );
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
	prod=new CRod(knot1,knot2);

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

	pHardRod = new CHardRod(knot1,knot2);

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
	sprn=new CSpring(knot1,knot2);
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
	mass=new CMass(knot1);
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
	while (pos)
	{
		//проходим по всем элементам
		CKnot *kn=listKnot.GetNext(pos);
		if (kn->nXRez>=0) 
		{
			matr_RezY1[kn->nXRez][0]=kn->GetUx(0);
			matr_RezY2[kn->nXRez][0]=kn->GetUx(0,1);
		}
		if (kn->nYRez>=0) 
		{
			matr_RezY1[kn->nYRez][0]=kn->GetUy(0);
			matr_RezY2[kn->nYRez][0]=kn->GetUy(0,1);
		}
		for (int i=0;i<kn->CntAngle;i++)
			if (kn->nARez[i]>=0)
			{
				matr_RezY1[kn->nARez[i]][0]=kn->GetUa();
				matr_RezY2[kn->nARez[i]][0]=kn->GetUa(1);
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

void CSheme::CreateGroupForAllObjects( int type )
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
		return;
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
	}
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

int CSheme::SetMatrMDC(int Count, int Freq/*=0*/)
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
		elem->SetMatrMDC(matr_M, matr_D, matr_C);
	}
	//проверка диагонали матрицы matr_C (можно убрать)
	for (int i=0;i<Count;i++)
	{
		if (matr_C[i][i]==0) 
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
	TRACE0("\n\nBefore modify M:\n");
	for( int r = 0; r < matr_M.SizeY; r++ )
	{
		TRACE1("\n%d>>> ", r);
		for( int c = 0; c < matr_M.SizeX; c++ )
		{
			TRACE1("%.5lf ", matr_M[r][c] );
		}
	}
////////////////////////////////////////////

	//модификация матриц если надо
	if( m_bIsHardRod )
	{
		m_pEqDeg->ModifyMatrMDC( matr_M, matr_D, matr_C, m_bCondenceMass );
		////////////////////////////////////////////
		TRACE0("\n\nAfter modify M:\n");
		for( int r = 0; r < matr_M.SizeY; r++ )
		{
			TRACE1("\n%d>>> ", r);
			for( int c = 0; c < matr_M.SizeX; c++ )
			{
				TRACE1("%.5lf ", matr_M[r][c] );
			}
		}
		////////////////////////////////////////////
	}
/*****************************************************************/
	//Ищем обратную матрицу
	int code;
	
	CMatr TempM(matr_M.SizeY,matr_M.SizeX);
	TempM=matr_M;
	matr_M_1 = TempM.GetInvert(code);
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
		if( m_verShemeVersion != VER_LE25 )
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

			ar << -1;
			long int iReserved = 3;// так, на будущее
			CString strThisVersionSignature;
			strThisVersionSignature.LoadString( IDS_SIGNATURE );
			ar << strThisVersionSignature;
			ar << iReserved;
		}

		ar << listElem.GetCount();

		if( m_pDoc )
			m_pDoc->ParamView.Serialize(ar);
		else
		{
			CParamView tmp;
			tmp.Serialize( ar );
		}
		ParamIntegr.Serialize(ar);
		ParamFreq.Serialize(ar);
		ParamSpectrOut.Serialize(ar);
		//CElem
		POSITION pos=listElem.GetHeadPosition();
		while (pos)
		{
			CElem *pElem=listElem.GetNext(pos);

			ar << pElem->TypeElem;
			pElem->Serialize(ar);
		}

		//Совместная спектральная плотность
		ar << listspectrP.GetCount();
		pos=listspectrP.GetHeadPosition();
		while (pos)
		{
			CComplexSpectr *pCS=(CComplexSpectr*)listspectrP.GetNext(pos);
			pCS->Serialize(ar);
		}
		//Совместная спектральная плотность
		ar << listspectrU.GetCount();
		pos=listspectrU.GetHeadPosition();
		while (pos)
		{
			CComplexSpectr *pCS=(CComplexSpectr*)listspectrU.GetNext(pos);
			pCS->Serialize(ar);
		}

		if( m_verShemeVersion != VER_LE25 )
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
		}
	}
	else
	{	// loading code
		//ParamView
		int count;
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
			if( strSignature.Compare( strThisVersionSignature ) != 0)
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
			ver = VER_EQ30;
			ar >> iReserved;
			ar >> count;
		}
		try
		{
			if( m_pDoc )
				m_pDoc->ParamView.Serialize(ar);
			else
			{
				CParamView tmp;
				tmp.Serialize( ar );
			}
			ParamIntegr.Serialize(ar);
			ParamFreq.Serialize(ar);
			ParamSpectrOut.Serialize(ar);
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
						
						CSpring *pSpring=new CSpring(0,0);
						pSpring->Serialize(ar);

						listElem.AddTail(pSpring);
						break;
					}
				case IDC_ROD:
					{
						CRod *pRod=new CRod(0,0);
						pRod->Serialize(ar);
						listElem.AddTail(pRod);
						break;
					}
				case IDC_DEMF:
					{
						CDemf *pDemf=new CDemf(0,0);
						pDemf->Serialize(ar);
						listElem.AddTail(pDemf);
						break;
					}
				case IDC_MASS:
					{
						CMass *pMass=new CMass(0);
						pMass->Serialize(ar);
						listElem.AddTail(pMass);
						break;
					}
				case IDC_HARDROD:
					{
						CHardRod *pHardRod=new CHardRod(0,0);
						pHardRod->Serialize(ar);
						listElem.AddTail(pHardRod);
						break;
					}
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
				pCS->Serialize(ar);

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
				pCS->Serialize(ar);

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

			if( ver != VER_LE25 )
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

/*
void CSheme::Serialize1( CArchive& ar, int &count, ShemeVersion &ver ) 
{
	if( ar.IsStoring() )
	{	// storing code
		if( m_verShemeVersion != VER_LE25 )
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

			ar << -1;
			long int iReserved = 3;// так, на будущее
			CString strThisVersionSignature;
			strThisVersionSignature.LoadString( IDS_SIGNATURE );
			ar << strThisVersionSignature;
			ar << iReserved;
		}

		ar << listElem.GetCount();
	}
	else
	{	// loading code
		//ParamView
		ar >> count;

		CString strSignature;// сигнатура версии файла
		long int iReserved;// так, на будущее
		ver = VER_LE25;// по умолчанию старая версия
		if( count < 0 )
		{
			//значит это версия с 3.0 и выше
			ar >> strSignature;
			CString strThisVersionSignature;
			strThisVersionSignature.LoadString( IDS_SIGNATURE );
			if( strSignature.Compare( strThisVersionSignature ) != 0)
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
			ver = VER_EQ30;
			ar >> iReserved;
			ar >> count;
		}
	}// loading code
}

void CSheme::Serialize2( CArchive& ar, int &count, ShemeVersion &ver ) 
{
	if( ar.IsStoring() )
	{	// storing code
		ParamIntegr.Serialize(ar);
		ParamFreq.Serialize(ar);
		ParamSpectrOut.Serialize(ar);
		//CElem
		POSITION pos=listElem.GetHeadPosition();
		while (pos)
		{
			CElem *pElem=listElem.GetNext(pos);

			ar << pElem->TypeElem;
			pElem->Serialize(ar);
		}

		//Совместная спектральная плотность
		ar << listspectrP.GetCount();
		pos=listspectrP.GetHeadPosition();
		while (pos)
		{
			CComplexSpectr *pCS=(CComplexSpectr*)listspectrP.GetNext(pos);
			pCS->Serialize(ar);
		}
		//Совместная спектральная плотность
		ar << listspectrU.GetCount();
		pos=listspectrU.GetHeadPosition();
		while (pos)
		{
			CComplexSpectr *pCS=(CComplexSpectr*)listspectrU.GetNext(pos);
			pCS->Serialize(ar);
		}

		if( m_verShemeVersion != VER_LE25 )
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
		}
	}
	else
	{	// loading code
		try
		{
			ParamIntegr.Serialize(ar);
			ParamFreq.Serialize(ar);
			ParamSpectrOut.Serialize(ar);
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
						
						CSpring *pSpring=new CSpring(0,0);
						pSpring->Serialize(ar);

						listElem.AddTail(pSpring);
						break;
					}
				case IDC_ROD:
					{
						CRod *pRod=new CRod(0,0);
						pRod->Serialize(ar);
						listElem.AddTail(pRod);
						break;
					}
				case IDC_DEMF:
					{
						CDemf *pDemf=new CDemf(0,0);
						pDemf->Serialize(ar);
						listElem.AddTail(pDemf);
						break;
					}
				case IDC_MASS:
					{
						CMass *pMass=new CMass(0);
						pMass->Serialize(ar);
						listElem.AddTail(pMass);
						break;
					}
				case IDC_HARDROD:
					{
						CHardRod *pHardRod=new CHardRod(0,0);
						pHardRod->Serialize(ar);
						listElem.AddTail(pHardRod);
						break;
					}
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
				pCS->Serialize(ar);

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
				pCS->Serialize(ar);

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

			if( ver != VER_LE25 )
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
*/
