#ifndef _cZone_H
#define _cZone_H

#include "MyInclude.h"
#include <KGEmotion.h>

using namespace KG;

class cZone
{
private:
	KGSprite*				m_pSprite;
	KGAnimate*				m_pAnimate;

private:
	int						m_nX;
	int						m_nY;
	int						m_nW;
	int						m_nH;
	int						m_nAtribeState;

	KGRect					m_rObjectRect;

public:


public:
	cZone( KGAnimate* pAnimate, int nX, int nY, int nW, int nH, int nAtribeState );
	~cZone();

public:
	void CALLBACK		OnLostDevice(void* pUserContext);
	void CALLBACK		OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK		OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK		OnDestroyDevice(void* pUserContext);
	void CALLBACK		OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext);

public:
	void				OnChangeZone();

};

#endif