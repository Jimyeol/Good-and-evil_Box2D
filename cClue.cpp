#include "cClue.h"

cClue::cClue( KGAnimate* pAnimate, int nX, int nY, int nW, int nH, int whatkind )
{
	m_pSprite				= pAnimate->GetSprite();
	m_pAnimate				= pAnimate;

	m_nX					= nX;
	m_nY					= nY;
	m_nW					= nW;
	m_nH					= nH;
	m_nWhatKind				= whatkind;

	m_rObjectRect			= KGRect( m_nX - m_nW, m_nY - m_nH, m_nX + m_nW, m_nY + m_nH );
 
}


cClue::~cClue()
{

}


void cClue::OnLostDevice(void* pUserContext)
{
}


void cClue::OnDestroyDevice(void* pUserContext)
{
}


void cClue::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{

}


void cClue::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	cStageMng* pStageMng = (cStageMng*)cMain()->GetCurrent();
	if(!pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_bClueCheck)
	{
		switch(m_nWhatKind)
		{
		case BLACK:
			m_pSprite->Render(L"bt_renewal_click", m_rObjectRect, COLOR);
			break;
		case WHITE:
			break;
		case REAL:
			break;
		}
	}
}


void cClue::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{
	//----------------------------------------------------------------
	//Å°¸Ô´ÂÄÚµå
	//===============================================================
	cStageMng* pStageMng = (cStageMng*)cMain()->GetCurrent();
	if( m_rObjectRect.isOverlap(pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_rHeroRect) )
	{
		switch(nChar)
		{
		case VK_UP:
			pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_bClueCheck = true;
			break;
		}
	}
}