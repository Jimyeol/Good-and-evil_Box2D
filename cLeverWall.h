#ifndef _cLeverWall_H
#define _cLeverWall_H

#include "MyInclude.h"
#include <KGEmotion.h>
#include "cHeroCollision.h"

using namespace KG;

class cLeverWall
{
private:
	KGSprite*				m_pSprite;
	KGAnimate*				m_pAnimate;

public:
	int						m_nX;
	int						m_nY;
	int						m_nW;
	int						m_nH;
	int						m_nLeftMove;
	int						m_nRightMove;
	int						m_nWhatRoot;
	int						m_nWhatKind;
	int						m_nID;

	int						m_nMoveCheck;

	bool					m_bMoveCheck;

public:
	KGRect					m_rObjectRect;

	int						m_nUp;
	int						m_nDown;
	int						m_nLeft;
	int						m_nRight;

	cHeroCollision*				m_pHeroColl;


public:
	cLeverWall( KGAnimate* pAnimate, int nX, int nY, int nW, int nH, int nLeft, int nRight, int whatRoot, int whatkind, int nID );
	~cLeverWall();

public:
	void CALLBACK		OnLostDevice(void* pUserContext);
	void CALLBACK		OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK		OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK		OnDestroyDevice(void* pUserContext);

public:
	void				OnWallMove(bool bMoveDown);


};

#endif