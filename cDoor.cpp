#include "cDoor.h"

cDoor::cDoor( KGAnimate* pAnimate, int nX, int nY, int nW, int nH, int whatkind )
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


cDoor::~cDoor()
{

}


void cDoor::OnLostDevice(void* pUserContext)
{
}


void cDoor::OnDestroyDevice(void* pUserContext)
{
}


void cDoor::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{

}


void cDoor::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
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


void cDoor::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
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
			pStageMng->m_bSelectStage = true;
			break;
		}
	}
}