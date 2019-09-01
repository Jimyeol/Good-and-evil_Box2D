#ifndef _cLever_H
#define _cLever_H

#include "MyInclude.h"
#include <KGEmotion.h>

using namespace KG;

class cLever
{
private:
	KGSprite*				m_pSprite;
	KGAnimate*				m_pAnimate;

private:
	int						m_nX;
	int						m_nY;
	int						m_nW;
	int						m_nH;
	int						m_nWhatRoot;
	int						m_nWhatKind;
	int						m_nID;
	
	KGRect					m_rObjectRect;

public:


public:
	cLever( KGAnimate* pAnimate, int nX, int nY, int nW, int nH, int whatRoot, int whatkind, int nID );
	~cLever();

public:
	void CALLBACK		OnLostDevice(void* pUserContext);
	void CALLBACK		OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK		OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK		OnDestroyDevice(void* pUserContext);
	void CALLBACK		OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext);

};

#endif