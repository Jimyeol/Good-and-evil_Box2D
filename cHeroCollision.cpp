#include "cHeroCollision.h"

cHeroCollision::cHeroCollision(bool Left, bool Right, bool Up, bool Down, 
					   int nLeft, int nRight, int nDown, int nUp)
{
	//false 가 못움직임.

	m_bLeft					= Left;
	m_bRight				= Right;
	m_bUp					= Up;
	m_bDown					= Down;
	m_bMoveDown				= Down;
	m_bMoveLeft				= Left;
	m_bMoveRight			= Right;
	m_bMoveUp				= Up;

	m_nHeroLeft				= nLeft;
	m_nHeroRight			= nRight;
	m_nHeroUp				= nUp;
	m_nHeroDown				= nDown;

	m_bCollCheck			= false;
	m_bTopDown				= false;

	m_bPushLeft				= false;
	m_bPushRight			= false;

}


cHeroCollision::~cHeroCollision()
{
	/*	if( m_pHero != NULL )
	SAFE_DELETE(m_pHero);
	if( m_pWall != NULL )
	SAFE_DELETE(m_pWall);
	if( m_pLeverWall != NULL )
	SAFE_DELETE(m_pLeverWall);
	;*/
}


bool cHeroCollision::WallCollision(cHero* pHero, cWall* pWall, cLeverWall* pLeverWall, cBox* pBox, int nAttribe)
{

	SettingCollision(m_bCollCheck);		//초기때 모두 초기화함.

	m_pHero					= pHero;
	m_pWall					= pWall;
	m_pLeverWall			= pLeverWall;
	m_pBox					= pBox; 

	int m_nAttribe			= nAttribe;		//0 = WALL, 1 = LEVERWALL
	//m_pHero->SettingLieXY();

	m_nHeroLeft				= m_pHero->m_nX - m_pHero->m_nW;
	m_nHeroRight			= m_pHero->m_nX + m_pHero->m_nW;
	m_nHeroUp				= m_pHero->m_nY - m_pHero->m_nH;
	m_nHeroDown				= m_pHero->m_nY;

	switch( nAttribe )		//종류
	{
	case WALL:
		printf("-----------벽충돌------------\n");
		CollWall(m_pHero, m_pWall);
		break;
	case LEVERWALL:
		printf("-----------움직벽충돌------------\n");
		CollLeverWall(m_pHero, m_pLeverWall);
		break;
	case BOX:
		CollBox(m_pHero, m_pBox);
		break;
	}



	return true;
}


bool cHeroCollision::WallCollLeft(int HeroX, int HeroY, int WallX, int WallY, int WallLeft, int WallRight, int WallUp, int WallDown)
{	
	//벽의 왼쪽을 맞았을경우 히어로의 오른쪽을 못움직이게하는 함수

	if( HeroX < WallX && m_nHeroDown > WallUp && m_nHeroUp < WallDown )
	{
		if( m_nHeroRight+PLUSALPHA > WallLeft )
		{
			printf("왼쪽 충돌\n");
			return true;	//충돌됬다면 true 반환.
		}
	}

	return false;
}


bool cHeroCollision::WallCollRight(int HeroX, int HeroY, int WallX, int WallY, int WallLeft, int WallRight, int WallUp, int WallDown)
{
	//벽의 오른쪽을 맞았을경우 히어로의 왼쪽을 못움직이게하는 함수

	if( HeroX > WallX && m_nHeroDown > WallUp && m_nHeroUp < WallDown )
	{
		if( m_nHeroLeft-PLUSALPHA < WallRight )
		{
			printf("오른쪽 충돌\n");
 			return true;
		}
	}

	return false;
}


bool cHeroCollision::WallCollUp(int HeroX, int HeroY, int WallX, int WallY, int WallLeft, int WallRight, int WallUp, int WallDown)
{
	//벽의 위를 히어로의 아래와 맞았을경우 못움직이게하는 함수

	if( HeroY < WallY && m_nHeroRight > WallLeft && m_nHeroLeft < WallRight )
	{
		if( m_nHeroDown+PLUSALPHA > WallUp )
		{
			printf("위쪽 충돌\n");
			return true;
		}
	}


	return false;
}


bool cHeroCollision::WallCollDown(int HeroX, int HeroY, int WallX, int WallY, int WallLeft, int WallRight, int WallUp, int WallDown)
{
	//벽의 아래를 히어로의 위와 맞았을경우 못움직임요

	if( HeroY > WallY && m_nHeroRight > WallLeft && m_nHeroLeft < WallRight )
	{
		if( m_nHeroUp-PLUSALPHA < WallDown )
		{
			printf("아래쪽 충돌\n");
			return true;
		}
	}	
	return false;
}


void cHeroCollision::SettingCollision(bool bCollCheck)
{
	if( !bCollCheck)
	{
		m_bLeft					= false;
		m_bRight				= false;
		m_bUp					= false;
		m_bDown					= false;
		m_bMoveDown				= false;
		m_bMoveLeft				= false;
		m_bMoveRight			= false;
		m_bMoveUp				= false;
		m_bPushRight			= false;
		m_bPushLeft				= false;
	}
}


void cHeroCollision::CollWall(cHero* pHero, cWall* pWall)
{
	m_pHero					= pHero;
	m_pWall					= pWall;

	if( WallCollLeft( (m_pHero->m_nX + m_pHero->m_nW), m_pHero->m_nY, (m_pWall->m_nX + m_pWall->m_nW), m_pWall->m_nY, 
		m_pWall->m_nLeft, m_pWall->m_nRight, m_pWall->m_nUp,  m_pWall->m_nDown) )
	{
		m_bRight = true;
	}
	else if( WallCollRight( (m_pHero->m_nX - m_pHero->m_nW), m_pHero->m_nY, (m_pWall->m_nX - m_pWall->m_nW), m_pWall->m_nY, 
		m_pWall->m_nLeft, m_pWall->m_nRight, m_pWall->m_nUp,  m_pWall->m_nDown) )
	{
		m_bLeft = true;
	}
	if( WallCollUp(m_pHero->m_nX, (m_pHero->m_nY - m_pHero->m_nH/2), m_pWall->m_nX, (m_pWall->m_nY - m_pWall->m_nH),
		m_pWall->m_nLeft, m_pWall->m_nRight, m_pWall->m_nUp,  m_pWall->m_nDown) )
	{
		if( !m_pHero->m_bLadderCheck )
		{
			m_bDown = true;
			m_pHero->m_nY = m_pWall->m_nUp;		//착륙시 안착
			m_pHero->m_bJumpCheck = false;
		}
		//printf(" Up : %d \n", m_pWall->m_nUp);
	}
	else if( WallCollDown(m_pHero->m_nX, (m_pHero->m_nY - m_pHero->m_nH/2), m_pWall->m_nX, (m_pWall->m_nY + m_pWall->m_nH), 
		m_pWall->m_nLeft, m_pWall->m_nRight, m_pWall->m_nUp,  m_pWall->m_nDown) )
	{
		if( !m_pHero->m_bLadderCheck )
		{
			m_bUp = true;
			if( !m_bMoveDown )
				m_pHero->m_nY = m_pWall->m_nDown + m_pHero->m_nH + PLUSALPHA;		//밑에 부딛힐경우 떨어짐.
		}
	}
	
	m_bCollCheck			= true;
	m_bMoveDown				= false;

	if( !m_bRight && !m_bLeft && !m_bDown && !m_bUp )
		return;
}


void cHeroCollision::CollLeverWall(cHero* pHero, cLeverWall* pLeverWall)
{
	m_pHero					= pHero;
	m_pLeverWall			= pLeverWall;

	if( WallCollLeft( (m_pHero->m_nX + m_pHero->m_nW), m_pHero->m_nY, (m_pLeverWall->m_nX + m_pLeverWall->m_nW), m_pLeverWall->m_nY, 
		m_pLeverWall->m_nLeft, m_pLeverWall->m_nRight, m_pLeverWall->m_nUp,  m_pLeverWall->m_nDown) )
	{
		m_bRight = true;
	}
	else if( WallCollRight( (m_pHero->m_nX + m_pHero->m_nW), m_pHero->m_nY, (m_pLeverWall->m_nX - m_pLeverWall->m_nW), m_pLeverWall->m_nY, 
		m_pLeverWall->m_nLeft, m_pLeverWall->m_nRight, m_pLeverWall->m_nUp,  m_pLeverWall->m_nDown) )
	{
		m_bLeft = true;
	}
	if( WallCollUp(m_pHero->m_nX, (m_pHero->m_nY - m_pHero->m_nH/2), m_pLeverWall->m_nX, (m_pLeverWall->m_nY + m_pLeverWall->m_nH),
		m_pLeverWall->m_nLeft, m_pLeverWall->m_nRight, m_pLeverWall->m_nUp,  m_pLeverWall->m_nDown) )
	{
		m_bDown = true;
		m_bMoveDown = true;
		if(!m_bTopDown)
			m_pHero->m_nY = m_pLeverWall->m_nUp-2;		//착륙시 안착
		else
			m_pHero->m_nY = m_pLeverWall->m_nUp-2;		//착륙시 안착
		m_pHero->m_bJumpCheck = false;
		//printf(" Up : %d \n", m_pWall->m_nUp);
	}
	if( WallCollDown(m_pHero->m_nX, (m_pHero->m_nY - m_pHero->m_nH/2), m_pLeverWall->m_nX, (m_pLeverWall->m_nY - m_pLeverWall->m_nH), 
		m_pLeverWall->m_nLeft, m_pLeverWall->m_nRight, m_pLeverWall->m_nUp,  m_pLeverWall->m_nDown) )
	{
		m_bUp = true;
		m_pHero->m_nY = m_pLeverWall->m_nDown + m_pHero->m_nH + PLUSALPHA;		//밑에 부딛힐경우 떨어짐.
	}
	
	m_bCollCheck			= true;


	if( !m_bRight && !m_bLeft && !m_bMoveDown && !m_bMoveUp )
		return;
}


void cHeroCollision::CollBox(cHero* pHero, cBox* pBox)
{
	m_pHero					= pHero;
	m_pBox					= pBox;

	if( WallCollLeft(m_pHero->m_nX, m_pHero->m_nY, m_pBox->m_nX, m_pBox->m_nY, 
		m_pBox->m_nLeft, m_pBox->m_nRight, m_pBox->m_nUp,  m_pBox->m_nDown) )
	{
		m_bPushRight = true;
		//m_bRight = true;
	}
	else if( WallCollRight(m_pHero->m_nX, m_pHero->m_nY, m_pBox->m_nX, m_pBox->m_nY, 
		m_pBox->m_nLeft, m_pBox->m_nRight, m_pBox->m_nUp,  m_pBox->m_nDown) )
	{
		m_bPushLeft = true;
		//m_bLeft = true;
	}
	if( WallCollUp(m_pHero->m_nX, m_pHero->m_nY, m_pBox->m_nX, m_pBox->m_nY,
		m_pBox->m_nLeft, m_pBox->m_nRight, m_pBox->m_nUp,  m_pBox->m_nDown) )
	{
		m_bDown = true;
		//m_bMoveDown = true;
		//if(!m_bTopDown)
			m_pHero->m_nY = m_pBox->m_nUp;		//착륙시 안착
		//else
		//	m_pHero->m_nY = m_pBox->m_nUp;		//착륙시 안착
		m_pHero->m_bJumpCheck = false;
		//printf(" Up : %d \n", m_pWall->m_nUp);
	}
	if( WallCollDown(m_pHero->m_nX, m_pHero->m_nY, m_pBox->m_nX, m_pBox->m_nY, 
		m_pBox->m_nLeft, m_pBox->m_nRight, m_pBox->m_nUp,  m_pBox->m_nDown) )
	{
		m_bUp = true;
		m_pHero->m_nY = m_pBox->m_nDown + m_pHero->m_nH + PLUSALPHA;		//밑에 부딛힐경우 떨어짐.
	}
	
	m_bCollCheck			= true;


	if( !m_bRight && !m_bLeft && !m_bMoveDown && !m_bMoveUp )
		return;
}