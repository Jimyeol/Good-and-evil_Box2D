#ifndef _CBOXCOLLI_H
#define _CBOXCOLLI_H

#include "MyInclude.h"
#include "cBox.h"
#include "cWall.h"

class cBox;
class cWall;
class cLeverWall;

class cBoxCollision
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

	bool					m_bStopLeft;	//히어로 밀때 못움직이게 함
	bool					m_bStopRight;

public:
	int						m_nBoxLeft;
	int						m_nBoxRight;
	int						m_nBoxUp;
	int						m_nBoxDown;

	bool					m_bBoxLeft;
	bool					m_bBoxRight;
	bool					m_bBoxUp;
	bool					m_bBoxDown;


private:
	cBox*					m_pBox;
	cBox*					m_pBox2;
	cWall*					m_pWall;
	cLeverWall*				m_pLeverWall;

public:
	cBoxCollision();
	cBoxCollision(bool Left, bool Right, bool Up, bool Down, 
		int nLeft, int nRight, int nDown, int nUp);
	~cBoxCollision();


public:
	//벽과의 충돌 체크
	bool					WallCollision(cBox* pBox, cBox* pBox2 = NULL, cWall* pWall = NULL, cLeverWall* pLeverWall = NULL, int nAttribe = 0);
	bool					WallCollLeft(int BoxX, int BoxY, int WallX, int WallY, 
		int WallLeft, int WallRight, int WallUp, int WallDown);
	bool					WallCollRight(int BoxX, int BoxY, int WallX, int WallY, 
		int WallLeft, int WallRight, int WallUp, int WallDown);
	bool					WallCollUp(int BoxX, int BoxY, int WallX, int WallY, 
		int WallLeft, int WallRight, int WallUp, int WallDown);
	bool					WallCollDown(int BoxX, int BoxY, int WallX, int WallY, 
		int WallLeft, int WallRight, int WallUp, int WallDown);
	void					SettingCollision(bool bCollCheck);
	////////////////////////////////////////////////////////////////////////////

	void					CollWall(cBox* pMonster, cWall* pWall);
	void					CollLeverWall(cBox* pMonster, cLeverWall* pLeverWall);
	void					CollBox(cBox* pBox_1, cBox* pBox_2);

	


public:

};

#endif