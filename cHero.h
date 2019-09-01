#ifndef _CHERO_H
#define _CHERO_H

#include "MyInclude.h"
#include <KGEmotion.h>
#include "cKey.h"
#include "cHeroCollision.h"

using namespace KG;

class cKey;
class cHeroCollision;

class cHero
{

private:
	KGSprite*				m_pSprite;
	KGAnimate*				m_pAnimate;

public:
	int						m_nX;
	int						m_nY;
	int						m_nH;
	int						m_nW;
	int						m_nSpeed;
	int						m_nJump;
	int						m_nPower;
	KGRect					m_rHeroRect;

	bool					m_bStopLeft;
	bool					m_bStopRight;


	int						m_nAttribeState;

	int						m_nLieX;
	int						m_nLieY;

	//��ٸ�����
	bool					m_bLadderColl;
	bool					m_bLadderCheck;


	//��������
	bool					m_bJumpCheck;	//����üũ
	int						m_nGravity;		//�߷�

	bool					m_bClueCheck;

	//Ű
	cKey					m_Key;
	cHeroCollision*			m_pHeroColl;

public:
	cHero(KGAnimate* pAnimate, int nX, int nY, int nW, int nH, int nSpeed, int nJump, int nPower);
	~cHero();
private:
	void					OnHeroCollision();
	void					OnHeroMove();
	void					OnHeroJump();
	bool					OnLadderCheck();

	void					SettingLieXY();

public:
	void CALLBACK			OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext);

};

#endif