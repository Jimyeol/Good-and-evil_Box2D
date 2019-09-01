#include "cZone.h"

cZone::cZone( KGAnimate* pAnimate, int nX, int nY, int nW, int nH, int nAtribeState )
{
	m_pSprite				= pAnimate->GetSprite();
	m_pAnimate				= pAnimate;

	m_nX					= nX;
	m_nY					= nY;
	m_nW					= nW;
	m_nH					= nH;
	m_nAtribeState			= nAtribeState;

	m_rObjectRect			= KGRect( m_nX, m_nY, m_nX + m_nW, m_nY + m_nH );

}


cZone::~cZone()
{

}


void cZone::OnLostDevice(void* pUserContext)
{
}


void cZone::OnDestroyDevice(void* pUserContext)
{
}


void cZone::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	cStageMng* pStageMng = (cStageMng*)cMain()->GetCurrent();

	if( m_rObjectRect.isOverlap(pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_rHeroRect) )
	{
		switch( m_nAtribeState )
		{
		case BLACK:
			pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_nAttribeState = BLACK;
			break;
		case WHITE:
			pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_nAttribeState = WHITE;
			break;
		case REAL:
			pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_nAttribeState = REAL;
			break;
		}
	}
}


void cZone::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	switch(m_nAtribeState)
	{
	case BLACK:
		m_pSprite->Render(L"BlackZone", m_rObjectRect, D3DXCOLOR(1, 1, 1, 0.6f) );
		break;
	case WHITE:
		m_pSprite->Render(L"WhiteZone", m_rObjectRect, D3DXCOLOR(1, 1, 1, 0.6f) );
		break;
	case REAL:
		m_pSprite->Render(L"RealZone", m_rObjectRect, D3DXCOLOR(1, 1, 1, 0.6f) );
		break;
	}
}


void cZone::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{

	switch(nChar)
	{
	case VK_UP:

		break;
	}

}


void cZone::OnChangeZone()
{
	switch(m_nAtribeState)
	{
	case BLACK:
		m_nAtribeState = WHITE;
		break;
	case WHITE:
		m_nAtribeState = BLACK;
		break;
	}
}