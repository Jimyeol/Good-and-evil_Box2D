#ifndef _cBox_H
#define _cBox_H

#include "MyInclude.h"
#include <KGEmotion.h>
#include "cBoxCollision.h"

using namespace KG;

class cBoxCollision;

class cBox
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
	int						m_nCount;
	int						m_nNumber;
	
	KGRect					m_rObjectRect;

public:
	int						m_nUp;
	int						m_nDown;
	int						m_nLeft;
	int						m_nRight;

public:
	//점프관련
	bool					m_bJumpCheck;	//점프체크
	int						m_nGravity;		//중력

public:
	//충돌
	cBoxCollision*			m_pBoxColl;

public:


public:
	cBox( KGAnimate* pAnimate, int nX, int nY, int nW, int nH, int whatkind, int i);
	~cBox();

public:
	void CALLBACK		OnLostDevice(void* pUserContext);
	void CALLBACK		OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK		OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK		OnDestroyDevice(void* pUserContext);
	void CALLBACK		OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext);

};

#endif