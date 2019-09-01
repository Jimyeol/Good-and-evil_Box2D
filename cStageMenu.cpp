#include "cStageMenu.h"

cStageMenu::cStageMenu()
{
	m_pSprite				= NULL;
	m_pAnimate				= NULL;
}


cStageMenu::~cStageMenu()
{
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pAnimate);
}


void cStageMenu::OnDestroyDevice(void* pUserContext)
{
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pAnimate);
}


void cStageMenu::OnLostDevice(void* pUserContext)
{

}


void cStageMenu::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{

}


void cStageMenu::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{

}


void cStageMenu::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{
	if(!bKeyDown) return;
	switch(nChar)
	{
	case VK_SPACE:
		break;
	}
}