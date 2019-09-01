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

	m_bJumpCheck			= false;	//�ʱ���´� ������ ���ϰ� ���� 
	m_nGravity				= 0;
	m_bClueCheck			= false;	//ó������ Ű �Ȱ����� ����

	m_bStopLeft				= false;	//�ڽ��Ћ� �ڽ��� ���� �ε����� �������̰���
	m_bStopRight			= false;


	m_rHeroRect				= KGRect( m_nX - m_nW, m_nY - m_nH, m_nX + m_nW, m_nY );

	m_pHeroColl					= new cHeroCollision(false, false, false, false, 
		m_nX - m_nW, m_nX + m_nW, m_nY, m_nY - m_nH); //�ٿ�����.

}


cHero::~cHero()
{
	SAFE_DELETE(m_pHeroColl);
}


void cHero::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{

	m_bLadderColl = OnLadderCheck();	//����� �浹�� �����ϴ� �Լ�.
	OnHeroCollision();
	if( m_bLadderColl )
	{
		m_pHeroColl->m_bLeft = false;
		m_pHeroColl->m_bRight = false;
	}

	OnHeroMove();		//����� �������� �����ϴ� �Լ�
	OnHeroJump();		//������� ������ �����ϴ� �Լ�

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
	//��ũ��
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
	//��ũ�Ѱ�����
	//�浹������ �Լ� ȣ����

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
			if( m_pHeroColl->m_bPushLeft )	//�ڽ��� �浹������ �ӵ� ���߰� �̴°�
			{
				if( !m_bStopLeft )
					m_nX -= 2;
			}
			else if( !m_pHeroColl->m_bLeft  )
				m_nX -= m_nSpeed;
		}
		else if( m_Key.KeyUpSpeed( VK_LEFT ) )
		{
			//Ű���� �ȿ�����/
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


	if( m_bLadderColl )		//��ٸ��� �ε���������
	{
		if( m_Key.KeyDown( VK_UP ) )
		{
			if( !m_pHeroColl->m_bUp )
				m_nY -= m_nSpeed;
			m_bLadderCheck = true;
			m_bJumpCheck = false; //���� �������� �ٲ�
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
	//��������
	//-------------------------------------------
	if( !m_bLadderCheck ) //��ٸ��� �Ⱥε������ܿ� �߷� ���� �ȹ���
	{
		if( !m_pHeroColl->m_bDown  )	//�Ʒ����� �Ⱥε���������
		{
			if( !m_bJumpCheck ) //������ �ƴ϶��
			{
				m_bJumpCheck = true;
				m_nGravity = 0;
			}
		}

		if( m_pHeroColl->m_bUp )		//���� �ε�������� ��������
		{
			m_bJumpCheck = true;
			m_nGravity = 0;
		}
	}
	if( m_bJumpCheck )	//������
	{
		m_nY += (m_nGravity / m_nJump);
		m_nGravity += JUMPPLUSALPHA;
	}
}


void cHero::OnHeroCollision()
{
	cStageMng* pStageMng = (cStageMng*)cMain()->GetCurrent();

	//-----------------------------------------------------------------
	//�浹 ������Ʈ
	//-----------------------------------------------------------------
	m_pHeroColl->m_bCollCheck	= false;
	//�׳� ��
	for( int i = 0; i < pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_nWallNumber; i++ )
	{
		if( pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_ppWall[i]->m_rObjectRect.isOverlap(m_rHeroRect) )
		{
			m_pHeroColl->WallCollision(this, pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_ppWall[i], NULL, NULL, WALL);	//�浹�ɰ�� ȣ��
		}
	}
	//�����̴� ������Ʈ
	for( int i = 0; i < pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_nLeverWallNumber; i++ )
	{
		if( pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_ppLeverWall[i]->m_rObjectRect.isOverlap(m_rHeroRect) )
		{
			m_pHeroColl->WallCollision(this, NULL, pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_ppLeverWall[i], NULL, LEVERWALL);	//�浹�ɰ�� ȣ��
		}
	}
	//�ڽ�
	for( int i = 0; i < pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_nBoxNumber; i++ )
	{
		if( pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_ppBox[i]->m_rObjectRect.isOverlap(m_rHeroRect) )
		{
			m_pHeroColl->WallCollision(this, NULL, NULL, pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_ppBox[i], BOX);	//�浹�ɰ�� ȣ��
			pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_ppBox[i]->m_nCount = i;
			break;////////////////////
		}
		else
		{
			pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_ppBox[i]->m_nCount = -1;
		}
	}
	m_pHeroColl->SettingCollision(m_pHeroColl->m_bCollCheck);	//�浹�� �ȵɰ�� ����
	//-----------------------------------------------------------------
}


bool cHero::OnLadderCheck()
{
	cStageMng* pStageMng = (cStageMng*)cMain()->GetCurrent();

	for( int i = 0; i < pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_nLadderNumber; i++ )
	{
		if( pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_ppLadder[i]->m_rObjectRect.isOverlap(m_rHeroRect) )
		{
			return true;	//��ٸ��� Ż �� �ִ� ����.
		}
	}
	m_bLadderCheck = false;
	return false;
}