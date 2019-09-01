#include "cHero.h"
#include "CMAIN.h"

cHero::cHero(KGAnimate* pAnimate, int nX, int nY, int nW, int nH, int nSpeed, int nJump, int nPower)
{

	m_pSprite				= pAnimate->GetSprite();
	m_pAnimate				= pAnimate;

	m_nX					= nX;
	m_nY					= nY;
	m_nH					= nH;
	m_nW					= nW/2;
	m_nSpeed				= nSpeed;
	m_nJump					= nJump;
	m_nPower				= nPower;
	m_nAttribeState			= REAL;	///////////////////////////

	m_bJumpCheck			= false;	//초기상태는 점프를 안하고 있음 
	m_nGravity				= 0;
	m_bClueCheck			= false;	//처음에는 키 안가지고 있죠

	m_bStopLeft				= false;	//박스밀떄 박스가 벽에 부딪히면 못움직이게함
	m_bStopRight			= false;


	m_rHeroRect				= KGRect( m_nX - m_nW, m_nY - m_nH, m_nX + m_nW, m_nY );

	m_pHeroColl					= new cHeroCollision(false, false, false, false, 
		m_nX - m_nW, m_nX + m_nW, m_nY, m_nY - m_nH); //다움직임.

}


cHero::~cHero()
{
	SAFE_DELETE(m_pHeroColl);
}


void cHero::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{

	m_bLadderColl = OnLadderCheck();	//히어로 충돌을 제어하는 함수.
	OnHeroCollision();
	if( m_bLadderColl )
	{
		m_pHeroColl->m_bLeft = false;
		m_pHeroColl->m_bRight = false;
	}

	OnHeroMove();		//히어로 움직임을 제어하는 함수
	OnHeroJump();		//히어로의 점프를 제어하는 함수

	m_rHeroRect				= KGRect( m_nX - m_nW, m_nY - m_nH, m_nX + m_nW, m_nY );

}


void cHero::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	m_pSprite->Render(L"bt_renewal_over", m_rHeroRect , COLOR );

	//m_pSprite->Render(L"time_point_end", KGRect(m_pHeroColl->m_nHeroLeft, 
	//	m_pHeroColl->m_nHeroUp, m_pHeroColl->m_nHeroRight, m_pHeroColl->m_nHeroDown), COLOR );

	m_pSprite->Render(L"time_point_end", D3DXVECTOR3( (float)m_nX, (float)m_nY - m_nH/2, (float)0) , COLOR );

}


void cHero::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{

	switch(nChar)
	{
	case VK_UP:

		break;
	}
}


void cHero::SettingLieXY()
{
	cStageMng* pStageMng = (cStageMng*)cMain()->GetCurrent();


	//==============================================
	//스크롤
	//==============================================
	if( m_nX < SCREEN_WIDTH / 2)
		m_nLieX = m_nX;
	else if( m_nX > 1000 - (SCREEN_WIDTH/2))
		m_nLieX = (SCREEN_WIDTH / 2) + (m_nX - (1000 - (SCREEN_WIDTH/2)));
	else
		m_nLieX = SCREEN_WIDTH/2;

	if( m_nY < SCREEN_HEIGHT / 2)
		m_nLieY = m_nY;
	else if( m_nY > 1000 - (SCREEN_HEIGHT/2))
		m_nLieY = (SCREEN_HEIGHT / 2) + (m_nY - (1000 - (SCREEN_HEIGHT/2)));
	else
		m_nLieY = SCREEN_HEIGHT/2;
	//스크롤값수정
	//충돌했을때 함수 호출햄

	printf("(%d / 2) + (%d - (1000 - (%d/2))) = ", SCREEN_HEIGHT, m_nY, SCREEN_HEIGHT);
	printf("%d\n", m_nLieY);
}

void cHero::OnHeroMove()
{
	if( !m_bLadderCheck )
	{
		if( m_Key.KeyDown( VK_SPACE ) )
		{
			if(!m_bJumpCheck )
			{
				m_nGravity = -1200;
				m_bJumpCheck = true;
			}
		}
		if( m_Key.KeyDown( VK_LEFT ) )
		{
			if( m_pHeroColl->m_bPushLeft )	//박스랑 충돌했을때 속도 낮추고 미는거
			{
				if( !m_bStopLeft )
					m_nX -= 2;
			}
			else if( !m_pHeroColl->m_bLeft  )
				m_nX -= m_nSpeed;
		}
		else if( m_Key.KeyUpSpeed( VK_LEFT ) )
		{
			//키때면 안움직임/
			m_pHeroColl->m_bPushLeft = false;
		}
		if( m_Key.KeyDown( VK_RIGHT ) )
		{
			if( m_pHeroColl->m_bPushRight )
			{
				if( !m_bStopRight  )
					m_nX += 2;
			}
			else if( !m_pHeroColl->m_bRight  )
				m_nX += m_nSpeed;
		}
		else if( m_Key.KeyUpSpeed( VK_RIGHT ) )
		{
			m_pHeroColl->m_bPushRight = false;
		}
	}


	if( m_bLadderColl )		//사다리에 부딛혀있으면
	{
		if( m_Key.KeyDown( VK_UP ) )
		{
			if( !m_pHeroColl->m_bUp )
				m_nY -= m_nSpeed;
			m_bLadderCheck = true;
			m_bJumpCheck = false; //점프 안함으로 바꿈
		}
		if( m_Key.KeyDown( VK_DOWN ) )
		{
			if ( !m_pHeroColl->m_bDown )
				m_nY += m_nSpeed;
			m_bLadderCheck = true;
			m_bJumpCheck = false;
		}
	}
}


void cHero::OnHeroJump()
{
	//-------------------------------------------
	//점프관련
	//-------------------------------------------
	if( !m_bLadderCheck ) //사다리에 안부딛혓을겨웅 중력 영향 안받음
	{
		if( !m_pHeroColl->m_bDown  )	//아래쪽이 안부딪혀있으면
		{
			if( !m_bJumpCheck ) //점프가 아니라면
			{
				m_bJumpCheck = true;
				m_nGravity = 0;
			}
		}

		if( m_pHeroColl->m_bUp )		//위쪽 부딪혔을경우 떨어지기
		{
			m_bJumpCheck = true;
			m_nGravity = 0;
		}
	}
	if( m_bJumpCheck )	//점프중
	{
		m_nY += (m_nGravity / m_nJump);
		m_nGravity += JUMPPLUSALPHA;
	}
}


void cHero::OnHeroCollision()
{
	cStageMng* pStageMng = (cStageMng*)cMain()->GetCurrent();

	//-----------------------------------------------------------------
	//충돌 업데이트
	//-----------------------------------------------------------------
	m_pHeroColl->m_bCollCheck	= false;
	//그냥 벽
	for( int i = 0; i < pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_nWallNumber; i++ )
	{
		if( pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_ppWall[i]->m_rObjectRect.isOverlap(m_rHeroRect) )
		{
			m_pHeroColl->WallCollision(this, pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_ppWall[i], NULL, NULL, WALL);	//충돌될경우 호출
		}
	}
	//움직이는 오브젝트
	for( int i = 0; i < pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_nLeverWallNumber; i++ )
	{
		if( pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_ppLeverWall[i]->m_rObjectRect.isOverlap(m_rHeroRect) )
		{
			m_pHeroColl->WallCollision(this, NULL, pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_ppLeverWall[i], NULL, LEVERWALL);	//충돌될경우 호출
		}
	}
	//박스
	for( int i = 0; i < pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_nBoxNumber; i++ )
	{
		if( pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_ppBox[i]->m_rObjectRect.isOverlap(m_rHeroRect) )
		{
			m_pHeroColl->WallCollision(this, NULL, NULL, pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_ppBox[i], BOX);	//충돌될경우 호출
			pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_ppBox[i]->m_nCount = i;
			break;////////////////////
		}
		else
		{
			pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_ppBox[i]->m_nCount = -1;
		}
	}
	m_pHeroColl->SettingCollision(m_pHeroColl->m_bCollCheck);	//충돌이 안될경우 셋팅
	//-----------------------------------------------------------------
}


bool cHero::OnLadderCheck()
{
	cStageMng* pStageMng = (cStageMng*)cMain()->GetCurrent();

	for( int i = 0; i < pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_nLadderNumber; i++ )
	{
		if( pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_ppLadder[i]->m_rObjectRect.isOverlap(m_rHeroRect) )
		{
			return true;	//사다리를 탈 수 있는 상태.
		}
	}
	m_bLadderCheck = false;
	return false;
}