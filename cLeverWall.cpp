#include "cLeverWall.h"

cLeverWall::cLeverWall( KGAnimate* pAnimate, int nX, int nY, int nW, int nH, 
					   int nLeft, int nRight, int whatRoot, int whatkind, int nID )
{
	m_pSprite				= pAnimate->GetSprite();
	m_pAnimate				= pAnimate;

	m_nX					= nX;
	m_nY					= nY;
	m_nW					= nW;
	m_nH					= nH;
	m_nLeftMove				= nLeft;
	m_nRightMove			= nRight;
	m_nWhatRoot				= whatRoot;
	m_nWhatKind				= whatkind;
	m_nID					= nID;
	m_nMoveCheck			= ON;
	m_bMoveCheck			= MOVERIGHTTOP;


	m_rObjectRect			= KGRect( m_nX - m_nW, m_nY - m_nH, m_nX + m_nW, m_nY + m_nH );

	m_pHeroColl					= NULL;
	m_pHeroColl					= new cHeroCollision(false, false, false, false, 
		m_nX - m_nW, m_nX + m_nW, m_nY + m_nH, m_nY - m_nH); //다움직임.

}


cLeverWall::~cLeverWall()
{
	SAFE_DELETE(m_pHeroColl);
}


void cLeverWall::OnLostDevice(void* pUserContext)
{
}


void cLeverWall::OnDestroyDevice(void* pUserContext)
{
}


void cLeverWall::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	cStageMng* pStageMng = (cStageMng*)cMain()->GetCurrent();

	m_nUp					= m_nY - m_nH;
	m_nDown					= m_nY + m_nH;
	m_nLeft					= m_nX - m_nW;
	m_nRight				= m_nX + m_nW;

	m_rObjectRect			= KGRect( m_nX - m_nW, m_nY - m_nH-5, m_nX + m_nW, m_nY + m_nH);

	//-----------------------------------------------------------------
	//충돌 업데이트
	//-----------------------------------------------------------------
	m_pHeroColl->m_bCollCheck	= false;
	if( m_rObjectRect.isOverlap(pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_rHeroRect) )
	{
		m_pHeroColl->WallCollision(pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero, NULL, this, NULL, LEVERWALL);	//충돌될경우 호출
	}
	m_pHeroColl->SettingCollision(m_pHeroColl->m_bCollCheck);	//충돌이 안될경우 셋팅
	//-----------------------------------------------------------------

	if(m_nMoveCheck == ON)
	{
		OnWallMove(pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_pHeroColl->m_bMoveDown);		//움직이는 함수
	}

}


void cLeverWall::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	switch(m_nWhatKind)
	{
	case BLACK:
		m_pSprite->Render(L"RealZone", m_rObjectRect, COLOR);
		break;
	case WHITE:
		m_pSprite->Render(L"RealZone", m_rObjectRect, COLOR);
		break;
	case REAL:
		m_pSprite->Render(L"RealZone", m_rObjectRect, COLOR);
		break;
	}
}


void cLeverWall::OnWallMove(bool bMoveDown)
{
	cStageMng* pStageMng = (cStageMng*)cMain()->GetCurrent();

	bool m_bMoveDown = bMoveDown;

	if(m_nWhatRoot == SIDE)
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
			//if( !m_pHeroColl->m_bMoveLeft )
			if( m_bMoveDown && !pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_pHeroColl->m_bRight )
			{
				pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_nX += 2;
			}
			if( !m_pHeroColl->m_bLeft )
			{
				m_nX += 2;
			}
		}
		else
		{
			//if( !m_pHeroColl->m_bMoveRight )
			if( m_bMoveDown && !pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_pHeroColl->m_bLeft )
			{
				pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_nX -= 2;
			}
			if( !m_pHeroColl->m_bRight )
			{
				m_nX -= 2;
			}
		}
	}
	else
	{
		if( m_nY <= m_nLeftMove )
		{
			//위
			m_bMoveCheck = MOVERIGHTTOP;
		}
		else if( m_nY >= m_nRightMove )
		{
			//아래
			m_bMoveCheck = MOVELEFTDOWN;
		}

		if(m_bMoveCheck == MOVERIGHTTOP)
		{
			if( pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_pHeroColl->m_bDown  && m_pHeroColl->m_bUp && !m_pHeroColl->m_bTopDown && !m_bMoveDown)
			{
				//벽이 내려가고있는데 히어로랑 부딛혔을때 다시 올라가게함
				m_bMoveCheck = MOVELEFTDOWN;
			}
			if(m_bMoveCheck == MOVERIGHTTOP)
			{
				if( m_bMoveDown )
				{
					m_pHeroColl->m_bTopDown	= false;
					pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_nY += 2;
				}
				if( !m_pHeroColl->m_bUp )
					m_nY += 2;
				//아래
			}
		}
		else
		{
			if( pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_pHeroColl->m_bUp && m_bMoveDown && m_pHeroColl->m_bTopDown)
			{
				//히어로가 올라가고있을때 벽을 맞았을경우 다시 내려가게 함.
				m_bMoveCheck = MOVERIGHTTOP;
			}
			if(m_bMoveCheck == MOVELEFTDOWN)
			{
				if( m_bMoveDown )
				{
					//히어로가 위에 탔을때 제어 
					m_pHeroColl->m_bTopDown	= true;
					pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_nY -= 2;

				}
				m_nY -= 2;

			}
		}
	}
}

