#include "cLadder.h"

cLadder::cLadder( KGAnimate* pAnimate, int nX, int nY, int nW, int nH, int whatkind )
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


cLadder::~cLadder()
{

}


void cLadder::OnLostDevice(void* pUserContext)
{
}


void cLadder::OnDestroyDevice(void* pUserContext)
{
}


void cLadder::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{

}


void cLadder::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	cStageMng* pStageMng = (cStageMng*)cMain()->GetCurrent();

	switch(m_nWhatKind)
	{
	case BLACK:
		m_pSprite->Render(L"LadderReal", m_rObjectRect, D3DXCOLOR(1, 1, 1, 0.5f) );
		break;
	case WHITE:
		m_pSprite->Render(L"LadderReal", m_rObjectRect, D3DXCOLOR(1, 1, 1, 0.5f) );
		break;
	case REAL:
		break;
	}
}


void cLadder::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{

}