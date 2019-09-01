#ifndef _CSTAGEMENU_H
#define _CSTAGEMENU_H

#include "MyInclude.h"

using namespace KG;

class cStageMenu
{
private:
	KGSprite*			m_pSprite;
	KGAnimate*			m_pAnimate;


public:
	cStageMenu();
	~cStageMenu();

public:
	void CALLBACK		OnLostDevice(void* pUserContext);
	void CALLBACK		OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK		OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK		OnDestroyDevice(void* pUserContext);
	void CALLBACK		OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext);
};

#endif