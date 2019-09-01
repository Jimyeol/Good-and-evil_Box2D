#include "cGame.h"

cGame::cGame()
{
	m_pSprite				= NULL;
	m_pAnimate				= NULL;
}


cGame::~cGame()
{
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pAnimate);
}


void cGame::OnDestroyDevice(void* pUserContext)
{
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pAnimate);
}


HRESULT cGame::OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{

	if(m_pSprite == NULL)
	{
		m_pSprite			= new KGSprite(pd3dDevice);
		m_pSprite->Entry(L"res/Image/te/로고/GameLogo.te");
		m_pSprite->Entry(L"res/Image/te/로고/TeamLogo.te");

	}
	if(m_pAnimate == NULL)
	{
		m_pAnimate			= new KGAnimate(m_pSprite);
	}

	return S_OK;
}


HRESULT cGame::OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	return S_OK;
}


void cGame::OnLostDevice(void* pUserContext)
{
}


void cGame::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{


}


void cGame::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	HRESULT hr;
	V(pd3dDevice->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255,1,255,255), 1.0f, 0));
	if(SUCCEEDED(pd3dDevice->BeginScene()))
	{

		V(pd3dDevice->EndScene());
	}
}


void cGame::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{
	if(!bKeyDown) return;
	switch(nChar)
	{
	case VK_SPACE:
		break;
	}
}

