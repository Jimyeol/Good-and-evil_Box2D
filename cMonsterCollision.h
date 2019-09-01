#ifndef _CMONSTERCOLLI_H
#define _CMONSTERCOLLI_H

#include "MyInclude.h"
#include "cMonster.h"
#include "cWall.h"

class cMonster;
class cWall;
class cLeverWall;

class cMonsterCollision
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
	int						m_nMonsterLeft;
	int						m_nMonsterRight;
	int						m_nMonsterUp;
	int						m_nMonsterDown;


private:
	cMonster*				m_pMonster;
	cWall*					m_pWall;
	cLeverWall*				m_pLeverWall;

public:
	cMonsterCollision();
	cMonsterCollision(bool Left, bool Right, bool Up, bool Down, 
		int nLeft, int nRight, int nDown, int nUp);
	~cMonsterCollision();


public:
	//벽과의 충돌 체크
	bool					WallCollision(cMonster* pMonster, cWall* pWall = NULL, cLeverWall* pLeverWall = NULL, int nAttribe = 0);
	bool					WallCollLeft(int MonsterX, int MonsterY, int WallX, int WallY, 
		int WallLeft, int WallRight, int WallUp, int WallDown);
	bool					WallCollRight(int MonsterX, int MonsterY, int WallX, int WallY, 
		int WallLeft, int WallRight, int WallUp, int WallDown);
	bool					WallCollUp(int MonsterX, int MonsterY, int WallX, int WallY, 
		int WallLeft, int WallRight, int WallUp, int WallDown);
	bool					WallCollDown(int MonsterX, int MonsterY, int WallX, int WallY, 
		int WallLeft, int WallRight, int WallUp, int WallDown);
	void					SettingCollision(bool bCollCheck);
	////////////////////////////////////////////////////////////////////////////

	void					CollWall(cMonster* pMonster, cWall* pWall);
	void					CollLeverWall(cMonster* pMonster, cLeverWall* pLeverWall);

	


public:

};

#endif