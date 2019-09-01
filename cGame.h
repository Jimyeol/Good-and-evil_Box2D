#ifndef _CGAME_H
#define _CGAME_H

#include "MyInclude.h"

using namespace KG;

class cGame : public KGScene
{
private:
	KGSprite*			m_pSprite;
	KGAnimate*			m_pAnimate;


public:
	cGame();
	~cGame();

public:
	HRESULT CALLBACK	OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);
	HRESULT CALLBACK	OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);
	void CALLBACK		OnLostDevice(void* pUserContext);
	void CALLBACK		OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK		OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK		OnDestroyDevice(void* pUserContext);
	void CALLBACK		OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext);
};

#endif