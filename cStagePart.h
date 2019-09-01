#ifndef _CSTAGEPART_H
#define _CSTAGEPART_H

#include "MyInclude.h"
#include "cHero.h"

using namespace KG;

class cHero;
class cWall;
class cLever;
class cLeverWall;
class cThorn;
class cZone;
class cSwitch;
class cClue;
class cMonster;
class cLadder;
class cBox;
class cDoor;

class cStagePart
{
public:
	KGSprite*			m_pSprite;
	KGAnimate*			m_pAnimate;

	int					m_nStageNumber;
	int					m_nResoultionX;
	int					m_nResoultionY;
	WCHAR				m_cStageRoot[LARGE_SIZE];
	WCHAR				m_cStageName[LARGE_SIZE];

	//Hero
	cHero*				m_pHero;

	//wall
	int					m_nWallNumber;
	cWall**				m_ppWall;
	//LEVER
	int					m_nLeverNumber;
	cLever**			m_ppLever;
	//LEVERWALL
	int					m_nLeverWallNumber;
	cLeverWall**		m_ppLeverWall;
	//THORN
	int					m_nThornNumber;
	cThorn**			m_ppThorn;
	//ZONE
	int					m_nZoneNumber;
	cZone**				m_ppZone;
	//SWITCH
	int					m_nSwitchNumber;
	cSwitch**			m_ppSwitch;
	//CLUE
	int					m_nClueNumber;
	cClue**				m_ppClue;
	//MONSTER
	int					m_nMonsterNumber;
	cMonster**			m_ppMonster;
	//LADDER
	int					m_nLadderNumber;
	cLadder**			m_ppLadder;
	//BOX
	int					m_nBoxNumber;
	cBox**				m_ppBox;
	//DOOR
	int					m_nDoorNumber;
	cDoor**				m_ppDoor;


public:
	cStagePart(KGAnimate* pAnimate, int nStageNumber, WCHAR *cStageRoot, WCHAR *cStageName
		, int nResoultionX, int nResoultionY);
	~cStagePart();

public:
	void CALLBACK		OnLostDevice(void* pUserContext);
	void CALLBACK		OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK		OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK		OnDestroyDevice(void* pUserContext);
	void CALLBACK		OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext);

private:
	void				LoadObjectData(const WCHAR* pFileName);
	void				DecodeObject(FILE* fp);
};

#endif