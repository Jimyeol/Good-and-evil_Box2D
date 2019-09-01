#include "cBoxCollision.h"

cBoxCollision::cBoxCollision(bool Left, bool Right, bool Up, bool Down, 
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

	m_bStopLeft				= false;
	m_bStopRight			= false;

	m_bBoxLeft				= false;
	m_bBoxRight				= false;
	m_bBoxUp				= false;
	m_bBoxDown				= false;



	m_nBoxLeft				= nLeft;
	m_nBoxRight				= nRight;
	m_nBoxUp				= nUp;
	m_nBoxDown				= nDown;

	m_bCollCheck			= false;
	m_bTopDown				= false;
}


cBoxCollision::~cBoxCollision()
{
	/*	if( m_pBox != NULL )
	SAFE_DELETE(m_pBox);
	if( m_pWall != NULL )
	SAFE_DELETE(m_pWall);
	if( m_pLeverWall != NULL )
	SAFE_DELETE(m_pLeverWall);
	;*/
}


bool cBoxCollision::WallCollision(cBox* pBox, cBox* pBox2, cWall* pWall, cLeverWall* pLeverWall, int nAttribe)
{

	SettingCollision(m_bCollCheck);		//초기때 모두 초기화함.

	m_pBox					= pBox;
	m_pBox2					= pBox2;
	m_pWall					= pWall;
	m_pLeverWall			= pLeverWall;
	int m_nAttribe			= nAttribe;		//0 = WALL, 1 = LEVERWALL
	//m_pBox->SettingLieXY();

	m_nBoxLeft			= m_pBox->m_nX - m_pBox->m_nW;
	m_nBoxRight			= m_pBox->m_nX + m_pBox->m_nW;
	m_nBoxUp			= m_pBox->m_nY - m_pBox->m_nH;
	m_nBoxDown			= m_pBox->m_nY;

	switch( nAttribe )		//종류
	{
	case WALL:
		CollWall(m_pBox, m_pWall);
		break;
	case LEVERWALL:
		CollLeverWall(m_pBox, m_pLeverWall);
		break;
	case BOX:
		CollBox(m_pBox, m_pBox2);
		break;
	}



	return true;
}


bool cBoxCollision::WallCollLeft(int BoxX, int BoxY, int WallX, int WallY, int WallLeft, int WallRight, int WallUp, int WallDown)
{	
	//벽의 왼쪽을 맞았을경우 히어로의 오른쪽을 못움직이게하는 함수

	if( BoxX < WallX && m_nBoxDown > WallUp && m_nBoxUp < WallDown )
	{
		if( m_nBoxRight+PLUSALPHA > WallLeft )
		{
			return true;	//충돌됬다면 true 반환.
		}
	}

	return false;
}


bool cBoxCollision::WallCollRight(int BoxX, int BoxY, int WallX, int WallY, int WallLeft, int WallRight, int WallUp, int WallDown)
{
	//벽의 오른쪽을 맞았을경우 히어로의 왼쪽을 못움직이게하는 함수

	if( BoxX > WallX && m_nBoxDown > WallUp && m_nBoxUp < WallDown )
	{
		if( m_nBoxLeft-PLUSALPHA < WallRight )
		{
			return true;
		}
	}

	return false;
}


bool cBoxCollision::WallCollUp(int BoxX, int BoxY, int WallX, int WallY, int WallLeft, int WallRight, int WallUp, int WallDown)
{
	//벽의 위를 히어로의 아래와 맞았을경우 못움직이게하는 함수

	if( BoxY < WallY && m_nBoxRight > WallLeft && m_nBoxLeft < WallRight )
	{
		if( m_nBoxDown+PLUSALPHA > WallUp )
		{
			return true;
		}
	}


	return false;
}


bool cBoxCollision::WallCollDown(int BoxX, int BoxY, int WallX, int WallY, int WallLeft, int WallRight, int WallUp, int WallDown)
{
	//벽의 아래를 히어로의 위와 맞았을경우 못움직임요

	if( BoxY > WallY && m_nBoxRight > WallLeft && m_nBoxLeft < WallRight )
	{
		if( m_nBoxUp-PLUSALPHA < WallDown )
		{
			return true;
		}
	}	
	return false;
}


void cBoxCollision::SettingCollision(bool bCollCheck)
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
		m_bStopRight			= false;
		m_bStopLeft				= false;
		m_bBoxLeft				= false;
		m_bBoxRight				= false;
		m_bBoxUp				= false;
		m_bBoxDown				= false;

	}
}


void cBoxCollision::CollWall(cBox* pBox, cWall* pWall)
{
	m_pBox					= pBox;
	m_pWall					= pWall;

	if( WallCollLeft(m_pBox->m_nX, m_pBox->m_nY, m_pWall->m_nX, m_pWall->m_nY, 
		m_pWall->m_nLeft, m_pWall->m_nRight, m_pWall->m_nUp,  m_pWall->m_nDown) )
	{
		m_bRight = true;
		//박스밀때
		m_bStopRight = true;
		m_bStopLeft = false;
	}
	else if( WallCollRight(m_pBox->m_nX, m_pBox->m_nY, m_pWall->m_nX, m_pWall->m_nY, 
		m_pWall->m_nLeft, m_pWall->m_nRight, m_pWall->m_nUp,  m_pWall->m_nDown) )
	{
		m_bLeft = true;
		//박스 밀때 
		m_bStopLeft = true;
		m_bStopRight = false;
	}
	if( WallCollUp(m_pBox->m_nX, m_pBox->m_nY, m_pWall->m_nX, m_pWall->m_nY,
		m_pWall->m_nLeft, m_pWall->m_nRight, m_pWall->m_nUp,  m_pWall->m_nDown) )
	{
		m_bDown = true;
		m_pBox->m_nY = m_pWall->m_nUp;		//착륙시 안착
		m_pBox->m_bJumpCheck = false;
		//printf(" Up : %d \n", m_pWall->m_nUp);
	}
	else if( WallCollDown(m_pBox->m_nX, m_pBox->m_nY, m_pWall->m_nX, m_pWall->m_nY, 
		m_pWall->m_nLeft, m_pWall->m_nRight, m_pWall->m_nUp,  m_pWall->m_nDown) )
	{
		m_bUp = true;
		//m_pBox->m_nY = m_pWall->m_nDown + m_pBox->m_nH + PLUSALPHA;		//밑에 부딛힐경우 떨어짐.
	}
	
	m_bCollCheck			= true;

	if( !m_bRight && !m_bLeft && !m_bDown && !m_bUp )
		return;
}


void cBoxCollision::CollLeverWall(cBox* pBox, cLeverWall* pLeverWall)
{
	m_pBox					= pBox;
	m_pLeverWall			= pLeverWall;

	if( WallCollLeft(m_pBox->m_nX, m_pBox->m_nY, m_pLeverWall->m_nX, m_pLeverWall->m_nY, 
		m_pLeverWall->m_nLeft, m_pLeverWall->m_nRight, m_pLeverWall->m_nUp,  m_pLeverWall->m_nDown) )
	{
		m_bRight = true;
	}
	else if( WallCollRight(m_pBox->m_nX, m_pBox->m_nY, m_pLeverWall->m_nX, m_pLeverWall->m_nY, 
		m_pLeverWall->m_nLeft, m_pLeverWall->m_nRight, m_pLeverWall->m_nUp,  m_pLeverWall->m_nDown) )
	{
		m_bLeft = true;
	}
	if( WallCollUp(m_pBox->m_nX, m_pBox->m_nY, m_pLeverWall->m_nX, m_pLeverWall->m_nY,
		m_pLeverWall->m_nLeft, m_pLeverWall->m_nRight, m_pLeverWall->m_nUp,  m_pLeverWall->m_nDown) )
	{
		m_bDown = true;
		m_bMoveDown = true;
		if(!m_bTopDown)
			m_pBox->m_nY = m_pLeverWall->m_nUp-1;		//착륙시 안착
		else
			m_pBox->m_nY = m_pLeverWall->m_nUp;		//착륙시 안착
		m_pBox->m_bJumpCheck = false;
		//printf(" Up : %d \n", m_pWall->m_nUp);
	}
	if( WallCollDown(m_pBox->m_nX, m_pBox->m_nY, m_pLeverWall->m_nX, m_pLeverWall->m_nY, 
		m_pLeverWall->m_nLeft, m_pLeverWall->m_nRight, m_pLeverWall->m_nUp,  m_pLeverWall->m_nDown) )
	{
		m_bUp = true;
		//m_pBox->m_nY = m_pLeverWall->m_nDown + m_pBox->m_nH + PLUSALPHA;		//밑에 부딛힐경우 떨어짐.
	}
	
	m_bCollCheck			= true;


	if( !m_bRight && !m_bLeft && !m_bMoveDown && !m_bMoveUp )
		return;
}


void cBoxCollision::CollBox(cBox* pBox_1, cBox* pBox_2)
{
	m_pBox2					= pBox_2;
	m_pBox					= pBox_1;

	if( WallCollLeft(m_pBox->m_nX, m_pBox->m_nY, m_pBox2->m_nX, m_pBox2->m_nY, 
		m_pBox2->m_nLeft, m_pBox2->m_nRight, m_pBox2->m_nUp,  m_pBox2->m_nDown) )
	{
		m_bBoxRight = true;
	}
	if( m_bBoxRight == false)
	{
		int cscsc;
		cscsc = 0;
		cscsc++;
	}
	if( WallCollRight(m_pBox->m_nX, m_pBox->m_nY, m_pBox2->m_nX, m_pBox2->m_nY, 
		m_pBox2->m_nLeft, m_pBox2->m_nRight, m_pBox2->m_nUp,  m_pBox2->m_nDown) )
	{
		m_bBoxLeft = true;
	}
	if( WallCollUp(m_pBox->m_nX, m_pBox->m_nY, m_pBox2->m_nX, m_pBox2->m_nY,
		m_pBox2->m_nLeft, m_pBox2->m_nRight, m_pBox2->m_nUp,  m_pBox2->m_nDown) )
	{
		m_bBoxDown = true;
		//m_bDown = true;
		//m_bMoveDown = true;
		//if(!m_bTopDown)
		//	m_pHero->m_nY = m_pBox->m_nUp;		//착륙시 안착
		//else
		//	m_pHero->m_nY = m_pBox->m_nUp;		//착륙시 안착
		//m_pHero->m_bJumpCheck = false;
		//printf(" Up : %d \n", m_pWall->m_nUp);
	}
	if( WallCollDown(m_pBox->m_nX, m_pBox->m_nY, m_pBox2->m_nX, m_pBox2->m_nY, 
		m_pBox2->m_nLeft, m_pBox2->m_nRight, m_pBox2->m_nUp,  m_pBox2->m_nDown) )
	{
		m_bBoxUp = true;
		//m_bUp = true;
		//m_pHero->m_nY = m_pBox->m_nDown + m_pHero->m_nH + PLUSALPHA;		//밑에 부딛힐경우 떨어짐.
	}
	
	m_bCollCheck			= true;


	if( !m_bBoxRight && !m_bBoxUp && !m_bBoxDown && !m_bBoxLeft )
		return;
}