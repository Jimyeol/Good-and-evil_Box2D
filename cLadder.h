#ifndef _cLadder_H
#define _cLadder_H

#include "MyInclude.h"
#include <KGEmotion.h>

using namespace KG;

class cLadder
{
private:
	KGSprite*				m_pSprite;
	KGAnimate*				m_pAnimate;

public:
	int						m_nX;
	int						m_nY;
	int						m_nW;
	int						m_nH;
	int						m_nWhatKind;
	
	KGRect					m_rObjectRect;

public:


public:
	cLadder( KGAnimate* pAnimate, int nX, int nY, int nW, int nH, int whatkind );
	~cLadder();

public:
	void CALLBACK		OnLostDevice(void* pUserContext);
	void CALLBACK		OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK		OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK		OnDestroyDevice(void* pUserContext);
	void CALLBACK		OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext);

};

#endif