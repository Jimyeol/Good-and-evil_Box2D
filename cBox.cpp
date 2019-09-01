#include "cBox.h"

cBox::cBox( KGAnimate* pAnimate, int nX, int nY, int nW, int nH, int whatkind, int i )
{
	m_pSprite				= pAnimate->GetSprite();
	m_pAnimate				= pAnimate;

	m_nX					= nX;
	m_nY					= nY;
	m_nW					= nW;
	m_nH					= nH;
	m_nWhatKind				= whatkind;
	m_nNumber				= i;

	m_rObjectRect			= KGRect(  m_nX - m_nW, m_nY - m_nH, m_nX + m_nW, m_nY ) ;

	m_nUp					= m_nY - m_nH;
	m_nDown					= m_nY;
	m_nLeft					= m_nX - m_nW;
	m_nRight				= m_nX + m_nW;

	m_bJumpCheck			= true;	//초기상태는 점프를 안하고 있음 
	m_nGravity				= 0;
	m_nCount				= 0;

	m_pBoxColl				= new cBoxCollision(false, false, false, false, 
		m_nX - m_nW, m_nX + m_nW, m_nY, m_nY - m_nH); //다움직임.

}


cBox::~cBox()
{
	SAFE_DELETE(m_pBoxColl);
}


void cBox::OnLostDevice(void* pUserContext)
{
}


void cBox::OnDestroyDevice(void* pUserContext)
{
}


void cBox::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	cStageMng* pStageMng = (cStageMng*)cMain()->GetCurrent();

	//-----------------------------------------------------------------
	//충돌 업데이트
	//-----------------------------------------------------------------
	m_pBoxColl->m_bCollCheck	= false;
	//그냥 벽
	for( int i = 0; i < pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_nWallNumber; i++ )
	{
		if( pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_ppWall[i]->m_rObjectRect.isOverlap(m_rObjectRect) )
		{
			m_pBoxColl->WallCollision(this, NULL, pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_ppWall[i], NULL, WALL);	//충돌될경우 호출
			
		}
	}
	//움직이는 오브젝트
	for( int i = 0; i < pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_nLeverWallNumber; i++ )
	{
		if( pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_ppLeverWall[i]->m_rObjectRect.isOverlap(m_rObjectRect) )
		{
			m_pBoxColl->WallCollision(this, NULL, NULL, pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_ppLeverWall[i], LEVERWALL);	//충돌될경우 호출
		}
	}
	//박스
	for( int i = 0; i < pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_nBoxNumber; i++ )
	{
		if( pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_ppBox[i]->m_rObjectRect.isOverlap(m_rObjectRect) )
		{
			if( m_nNumber == i )
				continue;

			m_pBoxColl->WallCollision(this,  pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_ppBox[i], NULL, NULL, BOX);	//충돌될경우 호출
		}
	}
	m_pBoxColl->SettingCollision(m_pBoxColl->m_bCollCheck);	//충돌이 안될경우 셋팅
	//-----------------------------------------------------------------

	//================================================================
	//땅에 박아노는 코드
	//================================================================
	if( m_pBoxColl->m_bDown  )	//아래쪽이 안부딪혀있으면
	{
		if( !m_bJumpCheck ) //점프가 아니라면
		{
			m_bJumpCheck = true;
			m_nGravity = 0;
		}
	}
	if( m_bJumpCheck )	//점프중
	{
		m_nY += (m_nGravity / JUMPDIVIALPHA);
		m_nGravity += JUMPPLUSALPHA;
	}

	//================================================================
	//박스 밀때 움직임
	//================================================================
	if( m_pBoxColl->m_bStopRight || m_pBoxColl->m_bBoxRight )
	{
		pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_bStopRight = true;
	}
	if( m_pBoxColl->m_bStopLeft || m_pBoxColl->m_bBoxLeft )
	{
		pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_bStopLeft = true;
	}

	//================================================================
	//히어로 충돌시 움직임
	//================================================================
	if( pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_pHeroColl->m_bPushRight )
	{
		if( !m_pBoxColl->m_bStopRight )	//박스 밀때 박스가 부딛히면 못움직이게함.
		{
			pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_bStopRight = false;
			if( m_nCount == m_nNumber && !m_pBoxColl->m_bBoxRight) //미는게 똑같을때
				m_nX += 2;
		}

	}
	else if( pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_pHeroColl->m_bPushLeft )
	{
		if( !m_pBoxColl->m_bStopLeft )
		{
			pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_bStopLeft = false;
			if( m_nCount == m_nNumber && !m_pBoxColl->m_bBoxLeft) //미는게 똑같을때
				m_nX -= 2;
		}
	}


	m_nUp					= m_nY - m_nH;
	m_nDown					= m_nY;
	m_nLeft					= m_nX - m_nW;
	m_nRight				= m_nX + m_nW;

	m_rObjectRect			= KGRect(  m_nX - m_nW, m_nY - m_nH, m_nX + m_nW, m_nY );
}


void cBox::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{

	switch(m_nWhatKind)
	{
	case BLACK:
		m_pSprite->Render(L"bt_1vs1_over", m_rObjectRect, COLOR);
		break;
	case WHITE:
		break;
	case REAL:
		break;
	}

}


void cBox::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{
	switch(nChar)
	{
	case VK_UP:
		break;
	}

}