#include "cStagePart.h"

cStagePart::cStagePart(KGAnimate* pAnimate, int nStageNumber, WCHAR *cStageRoot, WCHAR *cStageName
		,  int nResoultionX, int nResoultionY)
{
	m_pSprite				= pAnimate->GetSprite();
	m_pAnimate				= pAnimate;

	m_nResoultionX			= nResoultionX; //해상도 X
	m_nResoultionY			= nResoultionY; //해상도Y
	wcscpy(m_cStageName, cStageName);		//맵의 이름
	wcscpy(m_cStageRoot, cStageRoot);		//로드할 맵의 경로 복사
	
	m_pHero					= NULL;
	m_ppWall				= NULL;
	m_ppLever				= NULL;
	m_ppLeverWall			= NULL;
	m_ppThorn				= NULL;
	m_ppZone				= NULL;
	m_ppSwitch				= NULL;
	m_ppClue				= NULL;
	m_ppMonster				= NULL;
	m_ppLadder				= NULL;
	m_ppBox					= NULL;
	m_ppDoor				= NULL;

	
	LoadObjectData(m_cStageRoot);
}


cStagePart::~cStagePart()
{
	SAFE_DELETE(m_pHero);

	if(m_ppWall != NULL)
	{
		for( int i = 0; i < m_nWallNumber; i++ )
		{
			SAFE_DELETE(m_ppWall[i]);
		}
		SAFE_DELETE_ARRAY(m_ppWall);
	}

	if(m_ppLever != NULL)
	{
		for( int i = 0; i < m_nLeverNumber; i++ )
		{
			SAFE_DELETE(m_ppLever[i]);
		}
		SAFE_DELETE_ARRAY(m_ppLever);
	}

	if(m_ppLeverWall != NULL)
	{
		for( int i = 0; i < m_nLeverWallNumber; i++ )
		{
			SAFE_DELETE(m_ppLeverWall[i]);
		}
		SAFE_DELETE_ARRAY(m_ppLeverWall);
	}

	if(m_ppThorn != NULL)
	{
		for( int i = 0; i < m_nThornNumber; i++ )
		{
			SAFE_DELETE(m_ppThorn[i]);
		}
		SAFE_DELETE_ARRAY(m_ppThorn);
	}

	if(m_ppZone != NULL)
	{
		for( int i = 0; i < m_nZoneNumber; i++ )
		{
			SAFE_DELETE(m_ppZone[i]);
		}
		SAFE_DELETE_ARRAY(m_ppZone);
	}

	if(m_ppSwitch != NULL)
	{
		for( int i = 0; i < m_nSwitchNumber; i++ )
		{
			SAFE_DELETE(m_ppSwitch[i]);
		}
		SAFE_DELETE_ARRAY(m_ppSwitch);
	}

	if(m_ppClue != NULL)
	{
		for( int i = 0; i < m_nClueNumber; i++ )
		{
			SAFE_DELETE(m_ppClue[i]);
		}
		SAFE_DELETE_ARRAY(m_ppClue);
	}

	if(m_ppMonster != NULL)
	{
		for( int i = 0; i < m_nMonsterNumber; i++ )
		{
			SAFE_DELETE(m_ppMonster[i]);
		}
		SAFE_DELETE_ARRAY(m_ppMonster);
	}

	if(m_ppLadder != NULL)
	{
		for( int i = 0; i < m_nLadderNumber; i++ )
		{
			SAFE_DELETE(m_ppLadder[i]);
		}
		SAFE_DELETE_ARRAY(m_ppLadder);
	}

	if(m_ppBox != NULL)
	{
		for( int i = 0; i < m_nBoxNumber; i++ )
		{
			SAFE_DELETE(m_ppBox[i]);
		}
		SAFE_DELETE_ARRAY(m_ppBox);
	}

	if(m_ppDoor != NULL)
	{
		for( int i = 0; i < m_nDoorNumber; i++ )
		{
			SAFE_DELETE(m_ppDoor[i]);
		}
		SAFE_DELETE_ARRAY(m_ppDoor);
	}
}


void cStagePart::OnDestroyDevice(void* pUserContext)
{
	SAFE_DELETE(m_pHero);

	if(m_ppWall != NULL)
	{
		for( int i = 0; i < m_nWallNumber; i++ )
		{
			SAFE_DELETE(m_ppWall[i]);
		}
		SAFE_DELETE_ARRAY(m_ppWall);
	}

	if(m_ppLever != NULL)
	{
		for( int i = 0; i < m_nLeverNumber; i++ )
		{
			SAFE_DELETE(m_ppLever[i]);
		}
		SAFE_DELETE_ARRAY(m_ppLever);
	}

	if(m_ppLeverWall != NULL)
	{
		for( int i = 0; i < m_nLeverWallNumber; i++ )
		{
			SAFE_DELETE(m_ppLeverWall[i]);
		}
		SAFE_DELETE_ARRAY(m_ppLeverWall);
	}

	if(m_ppThorn != NULL)
	{
		for( int i = 0; i < m_nThornNumber; i++ )
		{
			SAFE_DELETE(m_ppThorn[i]);
		}
		SAFE_DELETE_ARRAY(m_ppThorn);
	}

	if(m_ppZone != NULL)
	{
		for( int i = 0; i < m_nZoneNumber; i++ )
		{
			SAFE_DELETE(m_ppZone[i]);
		}
		SAFE_DELETE_ARRAY(m_ppZone);
	}

	if(m_ppSwitch != NULL)
	{
		for( int i = 0; i < m_nSwitchNumber; i++ )
		{
			SAFE_DELETE(m_ppSwitch[i]);
		}
		SAFE_DELETE_ARRAY(m_ppSwitch);
	}

	if(m_ppClue != NULL)
	{
		for( int i = 0; i < m_nClueNumber; i++ )
		{
			SAFE_DELETE(m_ppClue[i]);
		}
		SAFE_DELETE_ARRAY(m_ppClue);
	}

	if(m_ppMonster != NULL)
	{
		for( int i = 0; i < m_nMonsterNumber; i++ )
		{
			SAFE_DELETE(m_ppMonster[i]);
		}
		SAFE_DELETE_ARRAY(m_ppMonster);
	}

	if(m_ppLadder != NULL)
	{
		for( int i = 0; i < m_nLadderNumber; i++ )
		{
			SAFE_DELETE(m_ppLadder[i]);
		}
		SAFE_DELETE_ARRAY(m_ppLadder);
	}

	if(m_ppBox != NULL)
	{
		for( int i = 0; i < m_nBoxNumber; i++ )
		{
			SAFE_DELETE(m_ppBox[i]);
		}
		SAFE_DELETE_ARRAY(m_ppBox);
	}

	if(m_ppDoor != NULL)
	{
		for( int i = 0; i < m_nDoorNumber; i++ )
		{
			SAFE_DELETE(m_ppDoor[i]);
		}
		SAFE_DELETE_ARRAY(m_ppDoor);
	}
}


void cStagePart::OnLostDevice(void* pUserContext)
{
}


void cStagePart::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	
	for( int i = 0; i < m_nWallNumber; i++ )
	{
		SAFE_ONFRAMEMOVE(m_ppWall[i]);
	}
	for( int i = 0; i < m_nLeverNumber; i++ )
	{
		SAFE_ONFRAMEMOVE(m_ppLever[i]);
	}
	for( int i = 0; i < m_nLeverWallNumber; i++ )
	{
		SAFE_ONFRAMEMOVE(m_ppLeverWall[i]);
	}
	for( int i = 0; i < m_nThornNumber; i++ )
	{
		SAFE_ONFRAMEMOVE(m_ppThorn[i]);
	}
	for( int i = 0; i < m_nZoneNumber; i++ )
	{
		SAFE_ONFRAMEMOVE(m_ppZone[i]);
	}
	for( int i = 0; i < m_nSwitchNumber; i++ )
	{
		SAFE_ONFRAMEMOVE(m_ppSwitch[i]);
	}
	for( int i = 0; i < m_nClueNumber; i++ )
	{
		SAFE_ONFRAMEMOVE(m_ppClue[i]);
	}
	for( int i = 0; i < m_nMonsterNumber; i++ )
	{
		SAFE_ONFRAMEMOVE(m_ppMonster[i]);
	}
	for( int i = 0; i < m_nLadderNumber; i++ )
	{
		SAFE_ONFRAMEMOVE(m_ppLadder[i]);
	}
	for( int i = 0; i < m_nBoxNumber; i++ )
	{
		SAFE_ONFRAMEMOVE(m_ppBox[i]);
	}
	for( int i = 0; i < m_nDoorNumber; i++ )
	{
		SAFE_ONFRAMEMOVE(m_ppDoor[i]);
	}
	SAFE_ONFRAMEMOVE(m_pHero);
}


void cStagePart::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	for( int i = 0; i < m_nWallNumber; i++ )
	{
		SAFE_ONFRAMERENDER(m_ppWall[i]);
	}
	for( int i = 0; i < m_nLeverNumber; i++ )
	{
		SAFE_ONFRAMERENDER(m_ppLever[i]);
	}
	for( int i = 0; i < m_nLeverWallNumber; i++ )
	{
		SAFE_ONFRAMERENDER(m_ppLeverWall[i]);
	}
	for( int i = 0; i < m_nThornNumber; i++ )
	{
		SAFE_ONFRAMERENDER(m_ppThorn[i]);
	}
	for( int i = 0; i < m_nZoneNumber; i++ )
	{
		SAFE_ONFRAMERENDER(m_ppZone[i]);
	}
	for( int i = 0; i < m_nSwitchNumber; i++ )
	{
		SAFE_ONFRAMERENDER(m_ppSwitch[i]);
	}
	for( int i = 0; i < m_nClueNumber; i++ )
	{
		SAFE_ONFRAMERENDER(m_ppClue[i]);
	}
	for( int i = 0; i < m_nMonsterNumber; i++ )
	{
		SAFE_ONFRAMERENDER(m_ppMonster[i]);
	}
	for( int i = 0; i < m_nLadderNumber; i++ )
	{
		SAFE_ONFRAMERENDER(m_ppLadder[i]);
	}
	for( int i = 0; i < m_nBoxNumber; i++ )
	{
		SAFE_ONFRAMERENDER(m_ppBox[i]);
	}
	for( int i = 0; i < m_nDoorNumber; i++ )
	{
		SAFE_ONFRAMERENDER(m_ppDoor[i]);
	}
	SAFE_ONFRAMERENDER(m_pHero);
}


void cStagePart::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{

	SAFE_ONKEYBOARD(m_pHero);
	for( int i = 0; i < m_nLeverNumber; i++ )
	{
		SAFE_ONKEYBOARD(m_ppLever[i]);
	}
	for( int i = 0; i < m_nSwitchNumber; i++ )
	{
		SAFE_ONKEYBOARD(m_ppSwitch[i]);
	}
	for( int i = 0; i < m_nClueNumber; i++ )
	{
		SAFE_ONKEYBOARD(m_ppClue[i]);
	}
	for( int i = 0; i < m_nLadderNumber; i++ )
	{
		SAFE_ONKEYBOARD(m_ppLadder[i]);
	}
	for( int i = 0; i < m_nDoorNumber; i++ )
	{
		SAFE_ONKEYBOARD(m_ppDoor[i]);
	}
	switch(nChar)
	{
	case VK_SPACE:
		break;
	}
}

void cStagePart::LoadObjectData(const WCHAR* pFileName)
{
	WCHAR					FileNameBuffer[256];
	WCHAR					m_cLine[100];
	WCHAR					m_cString[100];

	KGFindDXSDKMediaFileCch(FileNameBuffer, 256, pFileName);

	FILE*	fp = NULL;

#pragma warning ( disable : 4996)

	fp	= _wfopen(FileNameBuffer, L"rt");

	if(fp == NULL)
	{
		KGOutputDebugString(L"맵 로딩 실패\n");
		return;
	}

	while(!feof(fp))
	{
		fgetws(m_cLine, sizeof(m_cLine), fp);
		swscanf(m_cLine, L"%s", m_cString);

		if(wcscmp(m_cString, L"//") == 0)
			continue;

		if(wcscmp(m_cString, L"[OBJECTINFO]") == 0)
			DecodeObject(fp);
	}
	fclose(fp);
}


void cStagePart::DecodeObject(FILE* fp)
{
	WCHAR cLine[LARGE_SIZE];
	WCHAR cName[LARGE_SIZE];
	WCHAR cAttribe[LARGE_SIZE];
	WCHAR cRootCheck[LARGE_SIZE];
	WCHAR cPattern[LARGE_SIZE];
	int	nX, nY, nW, nH, nPower, nJump, nSpeed, whatkind, nID, whatRoot, nLeft, nRight;
	whatkind = 0;
	int nPattern = NULL;

	int nWallNumber			= 0;
	int nLeverNumber		= 0;
	int	nLeverWallNumber	= 0;
	int	nThornNumber		= 0;
	int nZoneNumber			= 0;
	int nSwitchNumber		= 0;
	int	nClueNumber			= 0;
	int nMonsterNumber		= 0;
	int nLadderNumber		= 0;
	int	nBoxNumber			= 0;
	int nDoorNumber			= 0;

	//----------------------------------------------------------------------------
	//[HERO]
	//----------------------------------------------------------------------------
	memset(cLine, 0, sizeof(cLine));
	fgetws(cLine, sizeof(cLine), fp);
	swscanf(cLine, L"%s", cName);	//Hero읽음

	memset(cLine, 0, sizeof(cLine));
	fgetws(cLine, sizeof(cLine), fp);
	swscanf(cLine, L"%d %d %d %d %d %d %d",  &nX, &nY, &nW, &nH, &nSpeed, &nJump, &nPower);

	m_pHero = new cHero(m_pAnimate, nX, nY, nW, nH, nSpeed, nJump, nPower);
	//생성자에 값을 넣어넣음.




	//----------------------------------------------------------------------------
	//[WALL]
	//----------------------------------------------------------------------------
	memset(cLine, 0, sizeof(cLine));
	fgetws(cLine, sizeof(cLine), fp);
	swscanf(cLine, L"%s", cName);
	//[WALL] 찾음

	memset(cLine, 0, sizeof(cLine));
	fgetws(cLine, sizeof(cLine), fp);
	swscanf(cLine, L"%d", &nWallNumber);
	//갯수를 읽습니다.

	m_nWallNumber = nWallNumber;

	m_ppWall = new cWall*[nWallNumber];

	for(int i=0; i<nWallNumber; i++)
	{
		memset(cLine, 0, sizeof(cLine));
		fgetws(cLine, sizeof(cLine), fp);
		swscanf( cLine, L"%d %d %d %d %s",  &nX, &nY, &nW, &nH, cAttribe );

		if(wcsstr(cAttribe, L"Black"))
			whatkind = BLACK;
		else if(wcsstr(cAttribe, L"White"))
			whatkind = WHITE;
		else
			whatkind = REAL;

		m_ppWall[i] = new cWall( m_pAnimate, nX, nY, nW, nH, whatkind );
		//생성자에 값을 넣어넣음.
	}

	

	//----------------------------------------------------------------------------
	//[Lever]
	//----------------------------------------------------------------------------
	memset(cLine, 0, sizeof(cLine));
	fgetws(cLine, sizeof(cLine), fp);
	swscanf(cLine, L"%s", cName);
	//[Lever] 찾음

	memset(cLine, 0, sizeof(cLine));
	fgetws(cLine, sizeof(cLine), fp);
	swscanf(cLine, L"%d", &nLeverNumber);
	//갯수를 읽습니다.

	m_nLeverNumber = nLeverNumber;

	m_ppLever = new cLever*[nLeverNumber];

	for(int i=0; i<nLeverNumber; i++)
	{
		memset(cLine, 0, sizeof(cLine));
		fgetws(cLine, sizeof(cLine), fp);
		swscanf( cLine, L"%d %d %d %d %s %s %d",  &nX, &nY, &nW, &nH, cRootCheck, cAttribe, &nID);

		if(wcsstr(cAttribe, L"Black"))
			whatkind = BLACK;
		else if(wcsstr(cAttribe, L"White"))
			whatkind = WHITE;
		else
			whatkind = REAL;

		if(wcsstr(cRootCheck, L"Yes"))
			whatRoot = YES;
		else
			whatRoot = NO;

		m_ppLever[i] = new cLever( m_pAnimate, nX, nY, nW, nH, whatRoot, whatkind, nID );
		//생성자에 값을 넣어넣음.
	}



	//----------------------------------------------------------------------------
	//[LEVERWALL]
	//----------------------------------------------------------------------------
	memset(cLine, 0, sizeof(cLine));
	fgetws(cLine, sizeof(cLine), fp);
	swscanf(cLine, L"%s", cName);
	//[LEVERWALL] 찾음

	memset(cLine, 0, sizeof(cLine));
	fgetws(cLine, sizeof(cLine), fp);
	swscanf(cLine, L"%d", &nLeverWallNumber);
	//갯수를 읽습니다.

	m_nLeverWallNumber = nLeverWallNumber;

	m_ppLeverWall = new cLeverWall*[nLeverWallNumber];

	for(int i=0; i<nLeverWallNumber; i++)
	{
		memset(cLine, 0, sizeof(cLine));
		fgetws(cLine, sizeof(cLine), fp);
		swscanf( cLine, L"%d %d %d %d %d %d %s %s %d",  &nX, &nY, &nW, &nH, &nLeft, &nRight, cRootCheck, cAttribe, &nID);

		if(wcsstr(cAttribe, L"Black"))
			whatkind = BLACK;
		else if(wcsstr(cAttribe, L"White"))
			whatkind = WHITE;
		else
			whatkind = REAL;

		if(wcsstr(cRootCheck, L"Side"))
			whatRoot = SIDE;
		else
			whatRoot = TOP;

		m_ppLeverWall[i] = new cLeverWall( m_pAnimate, nX, nY, nW, nH, nLeft, nRight, whatRoot, whatkind, nID );
		//생성자에 값을 넣어넣음.
	}


	//----------------------------------------------------------------------------
	//[THORN]
	//----------------------------------------------------------------------------
	memset(cLine, 0, sizeof(cLine));
	fgetws(cLine, sizeof(cLine), fp);
	swscanf(cLine, L"%s", cName);
	//[THORN] 찾음

	memset(cLine, 0, sizeof(cLine));
	fgetws(cLine, sizeof(cLine), fp);
	swscanf(cLine, L"%d", &nThornNumber);
	//갯수를 읽습니다.

	m_nThornNumber = nThornNumber;

	m_ppThorn = new cThorn*[nThornNumber];

	for(int i=0; i<nThornNumber; i++)
	{
		memset(cLine, 0, sizeof(cLine));
		fgetws(cLine, sizeof(cLine), fp);
		swscanf( cLine, L"%d %d %d %d %s",  &nX, &nY, &nW, &nH, cAttribe );

		if(wcsstr(cAttribe, L"Black"))
			whatkind = BLACK;
		else if(wcsstr(cAttribe, L"White"))
			whatkind = WHITE;
		else
			whatkind = REAL;

		m_ppThorn[i] = new cThorn( m_pAnimate, nX, nY, nW, nH, whatkind );
		//생성자에 값을 넣어넣음.
	}


	//----------------------------------------------------------------------------
	//[ZONE]
	//----------------------------------------------------------------------------
	memset(cLine, 0, sizeof(cLine));
	fgetws(cLine, sizeof(cLine), fp);
	swscanf(cLine, L"%s", cName);
	//[ZONE] 찾음

	memset(cLine, 0, sizeof(cLine));
	fgetws(cLine, sizeof(cLine), fp);
	swscanf(cLine, L"%d", &nZoneNumber);
	//갯수를 읽습니다.

	m_nZoneNumber = nZoneNumber;

	m_ppZone = new cZone*[nZoneNumber];

	for(int i=0; i<nZoneNumber; i++)
	{
		memset(cLine, 0, sizeof(cLine));
		fgetws(cLine, sizeof(cLine), fp);
		swscanf( cLine, L"%d %d %d %d %s",  &nX, &nY, &nW, &nH, cAttribe );

		if(wcsstr(cAttribe, L"Black"))
			whatkind = BLACK;
		else if(wcsstr(cAttribe, L"White"))
			whatkind = WHITE;
		else
			whatkind = REAL;

		m_ppZone[i] = new cZone( m_pAnimate, nX, nY, nW, nH, whatkind );
		//생성자에 값을 넣어넣음.
	}


	//----------------------------------------------------------------------------
	//[SWITCH]
	//----------------------------------------------------------------------------
	memset(cLine, 0, sizeof(cLine));
	fgetws(cLine, sizeof(cLine), fp);
	swscanf(cLine, L"%s", cName);
	//[SWITCH] 찾음

	memset(cLine, 0, sizeof(cLine));
	fgetws(cLine, sizeof(cLine), fp);
	swscanf(cLine, L"%d", &nSwitchNumber);
	//갯수를 읽습니다.

	m_nSwitchNumber = nSwitchNumber;

	m_ppSwitch = new cSwitch*[nSwitchNumber];

	for(int i=0; i<nSwitchNumber; i++)
	{
		memset(cLine, 0, sizeof(cLine));
		fgetws(cLine, sizeof(cLine), fp);
		swscanf( cLine, L"%d %d %d %d %s",  &nX, &nY, &nW, &nH, cAttribe );

		if(wcsstr(cAttribe, L"Black"))
			whatkind = BLACK;
		else if(wcsstr(cAttribe, L"White"))
			whatkind = WHITE;
		else
			whatkind = REAL;

		m_ppSwitch[i] = new cSwitch( m_pAnimate, nX, nY, nW, nH, whatkind );
		//생성자에 값을 넣어넣음.
	}


	//----------------------------------------------------------------------------
	//[CLUE]
	//----------------------------------------------------------------------------
	memset(cLine, 0, sizeof(cLine));
	fgetws(cLine, sizeof(cLine), fp);
	swscanf(cLine, L"%s", cName);
	//[CLUE] 찾음

	memset(cLine, 0, sizeof(cLine));
	fgetws(cLine, sizeof(cLine), fp);
	swscanf(cLine, L"%d", &nClueNumber);
	//갯수를 읽습니다.

	m_nClueNumber = nClueNumber;

	m_ppClue = new cClue*[nClueNumber];

	for(int i=0; i<nClueNumber; i++)
	{
		memset(cLine, 0, sizeof(cLine));
		fgetws(cLine, sizeof(cLine), fp);
		swscanf( cLine, L"%d %d %d %d %s",  &nX, &nY, &nW, &nH, cAttribe );

		if(wcsstr(cAttribe, L"Black"))
			whatkind = BLACK;
		else if(wcsstr(cAttribe, L"White"))
			whatkind = WHITE;
		else
			whatkind = REAL;

		m_ppClue[i] = new cClue( m_pAnimate, nX, nY, nW, nH, whatkind );
		//생성자에 값을 넣어넣음.
	}


	//----------------------------------------------------------------------------
	//[MONSTER]
	//----------------------------------------------------------------------------
	memset(cLine, 0, sizeof(cLine));
	fgetws(cLine, sizeof(cLine), fp);
	swscanf(cLine, L"%s", cName);
	//[MONSTER] 찾음

	memset(cLine, 0, sizeof(cLine));
	fgetws(cLine, sizeof(cLine), fp);
	swscanf(cLine, L"%d", &nMonsterNumber);
	//갯수를 읽습니다.

	m_nMonsterNumber = nMonsterNumber;

	m_ppMonster = new cMonster*[nMonsterNumber];

	for(int i=0; i<nMonsterNumber; i++)
	{
		memset(cLine, 0, sizeof(cLine));
		fgetws(cLine, sizeof(cLine), fp);
		swscanf( cLine, L"%d %d %d %d %d %d %s %s",  &nX, &nY, &nW, &nH, &nLeft, &nRight, cPattern, cAttribe );

		if(wcsstr(cAttribe, L"Black"))
			whatkind = BLACK;
		else if(wcsstr(cAttribe, L"White"))
			whatkind = WHITE;
		else
			whatkind = REAL;

		if(wcsstr(cPattern, L"PatternMove"))
			nPattern = PATTERN_MOVE;
		else
			nPattern = PATTERN_STOP;

		m_ppMonster[i] = new cMonster( m_pAnimate, nX, nY, nW, nH, nLeft, nRight, nPattern, whatkind );
		//생성자에 값을 넣어넣음.
	}


	//----------------------------------------------------------------------------
	//[Ladder]
	//----------------------------------------------------------------------------
	memset(cLine, 0, sizeof(cLine));
	fgetws(cLine, sizeof(cLine), fp);
	swscanf(cLine, L"%s", cName);
	//[Ladder] 찾음

	memset(cLine, 0, sizeof(cLine));
	fgetws(cLine, sizeof(cLine), fp);
	swscanf(cLine, L"%d", &nLadderNumber);
	//갯수를 읽습니다.

	m_nLadderNumber = nLadderNumber;

	m_ppLadder = new cLadder*[nLadderNumber];

	for(int i=0; i<nLadderNumber; i++)
	{
		memset(cLine, 0, sizeof(cLine));
		fgetws(cLine, sizeof(cLine), fp);
		swscanf( cLine, L"%d %d %d %d %s",  &nX, &nY, &nW, &nH, cAttribe );

		if(wcsstr(cAttribe, L"Black"))
			whatkind = BLACK;
		else if(wcsstr(cAttribe, L"White"))
			whatkind = WHITE;
		else
			whatkind = REAL;

		m_ppLadder[i] = new cLadder( m_pAnimate, nX, nY, nW, nH, whatkind );
		//생성자에 값을 넣어넣음.
	}


	//----------------------------------------------------------------------------
	//[BOX]
	//----------------------------------------------------------------------------
	memset(cLine, 0, sizeof(cLine));
	fgetws(cLine, sizeof(cLine), fp);
	swscanf(cLine, L"%s", cName);
	//[BOX] 찾음

	memset(cLine, 0, sizeof(cLine));
	fgetws(cLine, sizeof(cLine), fp);
	swscanf(cLine, L"%d", &nBoxNumber);
	//갯수를 읽습니다.

	m_nBoxNumber = nBoxNumber;

	m_ppBox = new cBox*[nBoxNumber];

	for(int i=0; i<nBoxNumber; i++)
	{
		memset(cLine, 0, sizeof(cLine));
		fgetws(cLine, sizeof(cLine), fp);
		swscanf( cLine, L"%d %d %d %d %s",  &nX, &nY, &nW, &nH, cAttribe );

		if(wcsstr(cAttribe, L"Black"))
			whatkind = BLACK;
		else if(wcsstr(cAttribe, L"White"))
			whatkind = WHITE;
		else
			whatkind = REAL;

		m_ppBox[i] = new cBox( m_pAnimate, nX, nY, nW, nH, whatkind, i);
		//생성자에 값을 넣어넣음.
	}


	//----------------------------------------------------------------------------
	//[DOOR]
	//----------------------------------------------------------------------------
	memset(cLine, 0, sizeof(cLine));
	fgetws(cLine, sizeof(cLine), fp);
	swscanf(cLine, L"%s", cName);
	//[DOOR] 찾음

	memset(cLine, 0, sizeof(cLine));
	fgetws(cLine, sizeof(cLine), fp);
	swscanf(cLine, L"%d", &nDoorNumber);
	//갯수를 읽습니다.

	m_nDoorNumber = nDoorNumber;

	m_ppDoor = new cDoor*[nDoorNumber];

	for(int i=0; i<nDoorNumber; i++)
	{
		memset(cLine, 0, sizeof(cLine));
		fgetws(cLine, sizeof(cLine), fp);
		swscanf( cLine, L"%d %d %d %d %s",  &nX, &nY, &nW, &nH, cAttribe );

		if(wcsstr(cAttribe, L"Black"))
			whatkind = BLACK;
		else if(wcsstr(cAttribe, L"White"))
			whatkind = WHITE;
		else
			whatkind = REAL;

		m_ppDoor[i] = new cDoor( m_pAnimate, nX, nY, nW, nH, whatkind );
		//생성자에 값을 넣어넣음.
	}
}