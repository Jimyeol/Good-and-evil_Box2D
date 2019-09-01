#ifndef _CHEROCOLLI_H
#define _CHEROCOLLI_H

#include "MyInclude.h"
#include "cHero.h"
#include "cWall.h"

class cHero;
class cWall;
class cLeverWall;
class cBox;

class cHeroCollision
{
public:
	bool					m_bLeft;
	bool					m_bRight;
	bool					m_bUp;
	bool					m_bDown;
	bool					m_bMoveDown;
	bool					m_bMoveLeft;
	bool					m_bMoveRight;
	bool					m_bMoveUp;
	
	bool					m_bTopDown;

	bool					m_bCollCheck;

public:
	//box
	bool					m_bPushLeft;
	bool					m_bPushRight;

public:
	int						m_nHeroLeft;
	int						m_nHeroRight;
	int						m_nHeroUp;
	int						m_nHeroDown;


private:
	cHero*					m_pHero;
	cWall*					m_pWall;
	cLeverWall*				m_pLeverWall;
	cBox*					m_pBox;

public:
	cHeroCollision();
	cHeroCollision(bool Left, bool Right, bool Up, bool Down, 
		int nLeft, int nRight, int nDown, int nUp);
	~cHeroCollision();


public:
	//벽과의 충돌 체크
	bool					WallCollision(cHero* pHero, cWall* pWall = NULL, cLeverWall* pLeverWall = NULL, cBox* pBox = NULL, int nAttribe = 0);
	bool					WallCollLeft(int HeroX, int HeroY, int WallX, int WallY, 
		int WallLeft, int WallRight, int WallUp, int WallDown);
	bool					WallCollRight(int HeroX, int HeroY, int WallX, int WallY, 
		int WallLeft, int WallRight, int WallUp, int WallDown);
	bool					WallCollUp(int HeroX, int HeroY, int WallX, int WallY, 
		int WallLeft, int WallRight, int WallUp, int WallDown);
	bool					WallCollDown(int HeroX, int HeroY, int WallX, int WallY, 
		int WallLeft, int WallRight, int WallUp, int WallDown);
	void					SettingCollision(bool bCollCheck);
	////////////////////////////////////////////////////////////////////////////

	void					CollWall(cHero* pHero, cWall* pWall);
	void					CollLeverWall(cHero* pHero, cLeverWall* pLeverWall);
	void					CollBox(cHero* pHero, cBox* pBox);

	


public:

};

#endif