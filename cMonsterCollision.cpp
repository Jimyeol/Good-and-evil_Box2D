#include "cMonsterCollision.h"

cMonsterCollision::cMonsterCollision(bool Left, bool Right, bool Up, bool Down, 
					   int nLeft, int nRight, int nDown, int nUp)
{
	//false �� ��������.

	m_bLeft					= Left;
	m_bRight				= Right;
	m_bUp					= Up;
	m_bDown					= Down;
	m_bMoveDown				= Down;
	m_bMoveLeft				= Left;
	m_bMoveRight			= Right;
	m_bMoveUp				= Up;

	m_nMonsterLeft			= nLeft;
	m_nMonsterRight			= nRight;
	m_nMonsterUp			= nUp;
	m_nMonsterDown			= nDown;

	m_bCollCheck			= false;
	m_bTopDown				= false;
}


cMonsterCollision::~cMonsterCollision()
{
	/*	if( m_pMonster != NULL )
	SAFE_DELETE(m_pMonster);
	if( m_pWall != NULL )
	SAFE_DELETE(m_pWall);
	if( m_pLeverWall != NULL )
	SAFE_DELETE(m_pLeverWall);
	;*/
}


bool cMonsterCollision::WallCollision(cMonster* pMonster, cWall* pWall, cLeverWall* pLeverWall, int nAttribe)
{

	SettingCollision(m_bCollCheck);		//�ʱ⶧ ��� �ʱ�ȭ��.

	m_pMonster				= pMonster;
	m_pWall					= pWall;
	m_pLeverWall			= pLeverWall;
	int m_nAttribe			= nAttribe;		//0 = WALL, 1 = LEVERWALL
	//m_pMonster->SettingLieXY();

	m_nMonsterLeft			= m_pMonster->m_nX - m_pMonster->m_nW;
	m_nMonsterRight			= m_pMonster->m_nX + m_pMonster->m_nW;
	m_nMonsterUp			= m_pMonster->m_nY - m_pMonster->m_nH;
	m_nMonsterDown			= m_pMonster->m_nY;

	switch( nAttribe )		//����
	{
	case WALL:
		CollWall(m_pMonster, m_pWall);
		break;
	case LEVERWALL:
		CollLeverWall(m_pMonster, m_pLeverWall);
		break;
	}



	return true;
}


bool cMonsterCollision::WallCollLeft(int MonsterX, int MonsterY, int WallX, int WallY, int WallLeft, int WallRight, int WallUp, int WallDown)
{	
	//���� ������ �¾������ ������� �������� �������̰��ϴ� �Լ�

	if( MonsterX < WallX && m_nMonsterDown > WallUp && m_nMonsterUp < WallDown )
	{
		if( m_nMonsterRight+PLUSALPHA > WallLeft )
		{
			return true;	//�浹��ٸ� true ��ȯ.
		}
	}

	return false;
}


bool cMonsterCollision::WallCollRight(int MonsterX, int MonsterY, int WallX, int WallY, int WallLeft, int WallRight, int WallUp, int WallDown)
{
	//���� �������� �¾������ ������� ������ �������̰��ϴ� �Լ�

	if( MonsterX > WallX && m_nMonsterDown > WallUp && m_nMonsterUp < WallDown )
	{
		if( m_nMonsterLeft-PLUSALPHA < WallRight )
		{
			return true;
		}
	}

	return false;
}


bool cMonsterCollision::WallCollUp(int MonsterX, int MonsterY, int WallX, int WallY, int WallLeft, int WallRight, int WallUp, int WallDown)
{
	//���� ���� ������� �Ʒ��� �¾������ �������̰��ϴ� �Լ�

	if( MonsterY < WallY && m_nMonsterRight > WallLeft && m_nMonsterLeft < WallRight )
	{
		if( m_nMonsterDown+PLUSALPHA > WallUp )
		{
			return true;
		}
	}


	return false;
}


bool cMonsterCollision::WallCollDown(int MonsterX, int MonsterY, int WallX, int WallY, int WallLeft, int WallRight, int WallUp, int WallDown)
{
	//���� �Ʒ��� ������� ���� �¾������ �������ӿ�

	if( MonsterY > WallY && m_nMonsterRight > WallLeft && m_nMonsterLeft < WallRight )
	{
		if( m_nMonsterUp-PLUSALPHA < WallDown )
		{
			return true;
		}
	}	
	return false;
}


void cMonsterCollision::SettingCollision(bool bCollCheck)
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
	}
}


void cMonsterCollision::CollWall(cMonster* pMonster, cWall* pWall)
{
	m_pMonster					= pMonster;
	m_pWall					= pWall;

	if( WallCollLeft(m_pMonster->m_nX, m_pMonster->m_nY, m_pWall->m_nX, m_pWall->m_nY, 
		m_pWall->m_nLeft, m_pWall->m_nRight, m_pWall->m_nUp,  m_pWall->m_nDown) )
	{
		m_bRight = true;
	}
	else if( WallCollRight(m_pMonster->m_nX, m_pMonster->m_nY, m_pWall->m_nX, m_pWall->m_nY, 
		m_pWall->m_nLeft, m_pWall->m_nRight, m_pWall->m_nUp,  m_pWall->m_nDown) )
	{
		m_bLeft = true;
	}
	if( WallCollUp(m_pMonster->m_nX, m_pMonster->m_nY, m_pWall->m_nX, m_pWall->m_nY,
		m_pWall->m_nLeft, m_pWall->m_nRight, m_pWall->m_nUp,  m_pWall->m_nDown) )
	{
		m_bDown = true;
		m_pMonster->m_nY = m_pWall->m_nUp;		//������ ����
		m_pMonster->m_bJumpCheck = false;
		//printf(" Up : %d \n", m_pWall->m_nUp);
	}
	else if( WallCollDown(m_pMonster->m_nX, m_pMonster->m_nY, m_pWall->m_nX, m_pWall->m_nY, 
		m_pWall->m_nLeft, m_pWall->m_nRight, m_pWall->m_nUp,  m_pWall->m_nDown) )
	{
		m_bUp = true;
		//m_pMonster->m_nY = m_pWall->m_nDown + m_pMonster->m_nH + PLUSALPHA;		//�ؿ� �ε������ ������.
	}
	
	m_bCollCheck			= true;

	if( !m_bRight && !m_bLeft && !m_bDown && !m_bUp )
		return;
}


void cMonsterCollision::CollLeverWall(cMonster* pMonster, cLeverWall* pLeverWall)
{
	m_pMonster				= pMonster;
	m_pLeverWall			= pLeverWall;

	if( WallCollLeft(m_pMonster->m_nX, m_pMonster->m_nY, m_pLeverWall->m_nX, m_pLeverWall->m_nY, 
		m_pLeverWall->m_nLeft, m_pLeverWall->m_nRight, m_pLeverWall->m_nUp,  m_pLeverWall->m_nDown) )
	{
		m_bRight = true;
	}
	else if( WallCollRight(m_pMonster->m_nX, m_pMonster->m_nY, m_pLeverWall->m_nX, m_pLeverWall->m_nY, 
		m_pLeverWall->m_nLeft, m_pLeverWall->m_nRight, m_pLeverWall->m_nUp,  m_pLeverWall->m_nDown) )
	{
		m_bLeft = true;
	}
	if( WallCollUp(m_pMonster->m_nX, m_pMonster->m_nY, m_pLeverWall->m_nX, m_pLeverWall->m_nY,
		m_pLeverWall->m_nLeft, m_pLeverWall->m_nRight, m_pLeverWall->m_nUp,  m_pLeverWall->m_nDown) )
	{
		m_bDown = true;
		m_bMoveDown = true;
		if(!m_bTopDown)
			m_pMonster->m_nY = m_pLeverWall->m_nUp-1;		//������ ����
		else
			m_pMonster->m_nY = m_pLeverWall->m_nUp;		//������ ����
		m_pMonster->m_bJumpCheck = false;
		//printf(" Up : %d \n", m_pWall->m_nUp);
	}
	if( WallCollDown(m_pMonster->m_nX, m_pMonster->m_nY, m_pLeverWall->m_nX, m_pLeverWall->m_nY, 
		m_pLeverWall->m_nLeft, m_pLeverWall->m_nRight, m_pLeverWall->m_nUp,  m_pLeverWall->m_nDown) )
	{
		m_bUp = true;
		//m_pMonster->m_nY = m_pLeverWall->m_nDown + m_pMonster->m_nH + PLUSALPHA;		//�ؿ� �ε������ ������.
	}
	
	m_bCollCheck			= true;


	if( !m_bRight && !m_bLeft && !m_bMoveDown && !m_bMoveUp )
		return;
}