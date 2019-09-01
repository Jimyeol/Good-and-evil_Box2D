#include "cThorn.h"

cThorn::cThorn( KGAnimate* pAnimate, int nX, int nY, int nW, int nH, int nAtribeState )
{
	m_pSprite				= pAnimate->GetSprite();
	m_pAnimate				= pAnimate;

	m_nX					= nX;
	m_nY					= nY;
	m_nW					= nW;
	m_nH					= nH;
	m_nAtribeState			= nAtribeState;

	m_rObjectRect			= KGRect( m_nX - m_nW, m_nY - m_nH, m_nX + m_nW, m_nY );

}


cThorn::~cThorn()
{

}


void cThorn::OnLostDevice(void* pUserContext)
{
}


void cThorn::OnDestroyDevice(void* pUserContext)
{
}


void cThorn::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	cStageMng* pStageMng = (cStageMng*)cMain()->GetCurrent();
	
	m_rObjectRect			= KGRect( m_nX - m_nW, m_nY - m_nH, m_nX + m_nW, m_nY );

	//===================================================================
	//가시 밟았을경우 사망 코드인데 영역대로 분리 또 해줘야 할거 같습니다.
	//===================================================================
	OnDeadCheck(m_rObjectRect, pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_rHeroRect, pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_nAttribeState);
	
}


void cThorn::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	switch(m_nAtribeState)
	{
	case BLACK:
		m_pSprite->Render(L"BlackThorn", m_rObjectRect, COLOR);
		break;
	case WHITE:
		m_pSprite->Render(L"WhiteThorn", m_rObjectRect, COLOR);
		break;
	case REAL:
		break;
	}
}


void cThorn::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{

	switch(nChar)
	{
	case VK_UP:

		break;
	}

}


void cThorn::OnDeadCheck(KGRect	rObjectRect, KGRect rHeroRect, int nHeroAttribe)
{
	int m_nHeroAttribe		= nHeroAttribe;
	KGRect m_rObjectRect	= rObjectRect;
	KGRect m_rHeroRect		= rHeroRect;

	if( m_rObjectRect.isOverlap(rHeroRect) )
	{
		//if( m_nHeroAttribe == REAL)
		//	continue;
		if( m_nAtribeState != m_nHeroAttribe )
			printf("사망");
	}
}