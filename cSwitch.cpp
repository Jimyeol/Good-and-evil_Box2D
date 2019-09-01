#include "cSwitch.h"

cSwitch::cSwitch( KGAnimate* pAnimate, int nX, int nY, int nW, int nH, int nAtribeState )
{
	m_pSprite				= pAnimate->GetSprite();
	m_pAnimate				= pAnimate;

	m_nX					= nX;
	m_nY					= nY;
	m_nW					= nW;
	m_nH					= nH;
	m_nAtribeState			= nAtribeState;
	m_PushTiming			= 0.f;		//스위치 타이밍을 주는 변수.

	m_rObjectRect			= KGRect( m_nX - m_nW, m_nY - m_nH, m_nX + m_nW, m_nY );
}


cSwitch::~cSwitch()
{

}


void cSwitch::OnLostDevice(void* pUserContext)
{
}


void cSwitch::OnDestroyDevice(void* pUserContext)
{
}


void cSwitch::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	m_PushTiming += fElapsedTime;
}


void cSwitch::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	switch(m_nAtribeState)
	{
	case BLACK:
		m_pSprite->Render(L"SwitchReal", m_rObjectRect, D3DXCOLOR(1, 1, 1, 1) );
		break;
	case WHITE:
		m_pSprite->Render(L"SwitchReal", m_rObjectRect, D3DXCOLOR(1, 1, 1, 1) );
		break;
	case REAL:
		m_pSprite->Render(L"SwitchReal", m_rObjectRect, D3DXCOLOR(1, 1, 1, 1) );
		break;
	}
}


void cSwitch::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{
	//==========================================================
	// 눌렀을때 스위치 가동
	//==========================================================
	cStageMng* pStageMng = (cStageMng*)cMain()->GetCurrent();
	if( m_rObjectRect.isOverlap(pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_rHeroRect) )
	{
		switch(nChar)
		{
		case VK_UP:
			if( m_PushTiming > 0.1f )
			{
				for( int i = 0; i < pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_nZoneNumber; i++ )
				{
					pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_ppZone[i]->OnChangeZone();
				}
				m_PushTiming = 0.f;
			}
			break;
		}
	}

}