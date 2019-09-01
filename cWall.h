#ifndef _CWALL_H
#define _CWALL_H

#include "MyInclude.h"
#include <KGEmotion.h>

using namespace KG;

class cWall
{
private:
	KGSprite*				m_pSprite;
	KGAnimate*				m_pAnimate;

public:
	int						m_nX;
	int						m_nY;
	int						m_nLieX;
	int						m_nLieY;
	int						m_nH;
	int						m_nW;
	int						m_nAtribeState;
	KGRect					m_rObjectRect;

	int						m_nUp;
	int						m_nDown;
	int						m_nLeft;
	int						m_nRight;

public:
	cWall(KGAnimate* pAnimate, int nX, int nY, int nw, int nH, int nAtribeState);
	~cWall();

	void					SettingLieXY();
	int						GetLieX();
	int						GetLieY();

	void					OnAttribeColl();

public:
	void CALLBACK			OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext);

};

#endif