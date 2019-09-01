#include "cMonster.h"

cMonster::cMonster( KGAnimate* pAnimate, int nX, int nY, int nW, int nH, int nLeft, int nRight, int nPattern, int whatkind )
{
	m_pSprite				= pAnimate->GetSprite();
	m_pAnimate				= pAnimate;

	m_nX					= nX;
	m_nY					= nY;
	m_nW					= nW/2;
	m_nH					= nH;
	m_nWhatKind				= whatkind;
	m_nLeftMove				= nLeft;
	m_nRightMove			= nRight;
	m_nPattern				= nPattern;
	m_bMoveCheck			= MOVERIGHTTOP;

	m_bJumpCheck			= true;	//초기상태는 점프를 안하고 있음 
	m_nGravity				= 0;

	m_pMonsterColl			= new cMonsterCollision(false, false, false, false, 
		m_nX - m_nW, m_nX + m_nW, m_nY, m_nY - m_nH); //다움직임.



	m_rObjectRect			= KGRect(  m_nX - m_nW, m_nY - m_nH, m_nX + m_nW, m_nY );

}


cMonster::~cMonster()
{
	SAFE_DELETE(m_pMonsterColl);
}


void cMonster::OnLostDevice(void* pUserContext)
{
}


void cMonster::OnDestroyDevice(void* pUserContext)
{
}


void cMonster::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	cStageMng* pStageMng = (cStageMng*)cMain()->GetCurrent();
	

	//-----------------------------------------------------------------
	//충돌 업데이트
	//-----------------------------------------------------------------
	m_pMonsterColl->m_bCollCheck	= false;
	//그냥 벽
	for( int i = 0; i < pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_nWallNumber; i++ )
	{
		if( pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_ppWall[i]->m_rObjectRect.isOverlap(m_rObjectRect) )
		{
			m_pMonsterColl->WallCollision(this, pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_ppWall[i], NULL, WALL);	//충돌될경우 호출
		}
	}
	//움직이는 오브젝트
	for( int i = 0; i < pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_nLeverWallNumber; i++ )
	{
		if( pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_ppLeverWall[i]->m_rObjectRect.isOverlap(m_rObjectRect) )
		{
			m_pMonsterColl->WallCollision(this, NULL, pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_ppLeverWall[i], LEVERWALL);	//충돌될경우 호출
		}
	}
	m_pMonsterColl->SettingCollision(m_pMonsterColl->m_bCollCheck);	//충돌이 안될경우 셋팅
	//-----------------------------------------------------------------

	//================================================================
	//땅에 박아노는 코드
	//================================================================
	if( m_pMonsterColl->m_bDown  )	//아래쪽이 안부딪혀있으면
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

	OnMonsterMove();		//움직이는 함수


	//==========================================================
	//몬스터 종류와 다른데 닿으면 사망
	//==========================================================
	if( m_rObjectRect.isOverlap( pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_rHeroRect ) )
	{
		if( pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_nAttribeState != m_nWhatKind )
			printf("사망");
	}

	m_rObjectRect			= KGRect(  m_nX - m_nW, m_nY - m_nH, m_nX + m_nW, m_nY );

}


void cMonster::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	switch(m_nWhatKind)
	{
	case BLACK:
		m_pSprite->Render(L"bt_1vs1_over", m_rObjectRect, COLOR);
		break;
	case WHITE:
		m_pSprite->Render(L"bt_1vs1_over", m_rObjectRect, D3DXCOLOR(1, 0.5, 0.5, 0.5) );
		break;
	case REAL:
		m_pSprite->Render(L"bt_1vs1_over", m_rObjectRect, D3DXCOLOR(1, 0.1f, 0.1f, 0.5f));
		break;
	}
}


void cMonster::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{
	switch(nChar)
	{
	case VK_UP:
		break;
	}
}


void cMonster::OnMonsterMove()
{
	if( m_nPattern == PATTERN_MOVE )
	{
		if( m_nX < m_nLeftMove )
		{
			//오른쪽으로감
			m_bMoveCheck = MOVERIGHTTOP;
		}
		else if( m_nX > m_nRightMove)
		{
			//왼쪽
			m_bMoveCheck = MOVELEFTDOWN;
		}

		if(m_bMoveCheck == MOVERIGHTTOP)
		{
			if( !m_pMonsterColl->m_bRight )
				m_nX += 2;
			else
				m_bMoveCheck = MOVELEFTDOWN;
		}
		else
		{
			if( !m_pMonsterColl->m_bLeft )
				m_nX -= 2;
			else
				m_bMoveCheck = MOVERIGHTTOP;
		}
	}
	else if( m_nPattern == PATTERN_STOP )
	{
		
	}

}