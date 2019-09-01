#ifndef _cMonster_H
#define _cMonster_H

#include "MyInclude.h"
#include <KGEmotion.h>
#include "cMonsterCollision.h"

using namespace KG;

class cMonsterCollision;

class cMonster
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
	int						m_nPattern;
	int						m_nWhatKind;

	bool					m_bMoveCheck;

	int						m_nAttribeState;
	
	KGRect					m_rObjectRect;

	//점프관련
	bool					m_bJumpCheck;	//점프체크
	int						m_nGravity;		//중력

	//충돌관련함수
	cMonsterCollision*		m_pMonsterColl;

public:
	void					OnMonsterMove();


public:
	cMonster( KGAnimate* pAnimate, int nX, int nY, int nW, int nH, int nLeft, int nRight, int nPattern, int whatkind );
	~cMonster();

public:
	void CALLBACK		OnLostDevice(void* pUserContext);
	void CALLBACK		OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK		OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK		OnDestroyDevice(void* pUserContext);
	void CALLBACK		OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext);

};

#endif