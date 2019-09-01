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

	m_bJumpCheck			= true;	//�ʱ���´� ������ ���ϰ� ���� 
	m_nGravity				= 0;
	m_nCount				= 0;

	m_pBoxColl				= new cBoxCollision(false, false, false, false, 
		m_nX - m_nW, m_nX + m_nW, m_nY, m_nY - m_nH); //�ٿ�����.

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
	//�浹 ������Ʈ
	//-----------------------------------------------------------------
	m_pBoxColl->m_bCollCheck	= false;
	//�׳� ��
	for( int i = 0; i < pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_nWallNumber; i++ )
	{
		if( pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_ppWall[i]->m_rObjectRect.isOverlap(m_rObjectRect) )
		{
			m_pBoxColl->WallCollision(this, NULL, pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_ppWall[i], NULL, WALL);	//�浹�ɰ�� ȣ��
			
		}
	}
	//�����̴� ������Ʈ
	for( int i = 0; i < pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_nLeverWallNumber; i++ )
	{
		if( pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_ppLeverWall[i]->m_rObjectRect.isOverlap(m_rObjectRect) )
		{
			m_pBoxColl->WallCollision(this, NULL, NULL, pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_ppLeverWall[i], LEVERWALL);	//�浹�ɰ�� ȣ��
		}
	}
	//�ڽ�
	for( int i = 0; i < pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_nBoxNumber; i++ )
	{
		if( pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_ppBox[i]->m_rObjectRect.isOverlap(m_rObjectRect) )
		{
			if( m_nNumber == i )
				continue;

			m_pBoxColl->WallCollision(this,  pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_ppBox[i], NULL, NULL, BOX);	//�浹�ɰ�� ȣ��
		}
	}
	m_pBoxColl->SettingCollision(m_pBoxColl->m_bCollCheck);	//�浹�� �ȵɰ�� ����
	//-----------------------------------------------------------------

	//================================================================
	//���� �ھƳ�� �ڵ�
	//================================================================
	if( m_pBoxColl->m_bDown  )	//�Ʒ����� �Ⱥε���������
	{
		if( !m_bJumpCheck ) //������ �ƴ϶��
		{
			m_bJumpCheck = true;
			m_nGravity = 0;
		}
	}
	if( m_bJumpCheck )	//������
	{
		m_nY += (m_nGravity / JUMPDIVIALPHA);
		m_nGravity += JUMPPLUSALPHA;
	}

	//================================================================
	//�ڽ� �ж� ������
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
	//����� �浹�� ������
	//================================================================
	if( pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_pHeroColl->m_bPushRight )
	{
		if( !m_pBoxColl->m_bStopRight )	//�ڽ� �ж� �ڽ��� �ε����� �������̰���.
		{
			pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_bStopRight = false;
			if( m_nCount == m_nNumber && !m_pBoxColl->m_bBoxRight) //�̴°� �Ȱ�����
				m_nX += 2;
		}

	}
	else if( pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_pHeroColl->m_bPushLeft )
	{
		if( !m_pBoxColl->m_bStopLeft )
		{
			pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_bStopLeft = false;
			if( m_nCount == m_nNumber && !m_pBoxColl->m_bBoxLeft) //�̴°� �Ȱ�����
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