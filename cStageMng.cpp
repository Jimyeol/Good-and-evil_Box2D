#include "cStageMng.h"

cStageMng::cStageMng()
{
	m_pSprite				= NULL;
	m_pAnimate				= NULL;
	m_pDialog				= NULL;

	//===============================================
	//    �������� ���� ������
	//===============================================
	m_ppStagePart			= NULL;
	m_pStageMenu			= NULL;
	m_nMapListCount			= 0 ;
	m_nResolutionX 			= 0 ;
	m_nResolutionY			= 0 ;
	m_bSelectStage			= true ;		//�ʱⰪ�� true �������� ����

	//===============================================
}


cStageMng::~cStageMng()
{
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pAnimate);
	SAFE_DELETE(m_pDialog);
	if(m_ppStagePart != NULL)
	{
		for( int i = 0; i < m_nMapListCount; i++ )
		{
			SAFE_DELETE(m_ppStagePart[i]);
		}
		SAFE_DELETE_ARRAY(m_ppStagePart);
	}
	SAFE_DELETE(m_pStageMenu);
}


void cStageMng::OnDestroyDevice(void* pUserContext)
{
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pAnimate);
	SAFE_DELETE(m_pDialog);
	if(m_ppStagePart != NULL)
	{
		for( int i = 0; i < m_nMapListCount; i++ )
		{
			SAFE_DELETE(m_ppStagePart[i]);
		}
		SAFE_DELETE_ARRAY(m_ppStagePart);
	}
	SAFE_DELETE(m_pStageMenu);
}


HRESULT cStageMng::OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	if(m_pSprite == NULL)
	{
		m_pSprite			= new KGSprite(pd3dDevice);
		m_pSprite->Entry(L"res/Image/te/�ΰ�/GameLogo.te");
		m_pSprite->Entry(L"res/Image/te/�ΰ�/TeamLogo.te");
		m_pSprite->Entry(L"Resource/Te/example.te");
		m_pSprite->Entry(L"Resource/Te/Object.te");
	}
	if(m_pAnimate == NULL)
	{
		m_pAnimate			= new KGAnimate(m_pSprite);
	}
	if( m_pDialog == NULL )
	{
		m_pDialog			= new KGDialog(m_pSprite, NULL, this);
	}
	if(m_ppStagePart == NULL)
	{
		LoadStageData(L"Resource/MapInformation/MapList.txt");
	}

	return S_OK;
}


HRESULT cStageMng::OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	SAFE_ONRESETDEVICE(m_pDialog);
	return S_OK;
}


void cStageMng::OnLostDevice(void* pUserContext)
{
	SAFE_ONLOSTDEVICE(m_pDialog);
}


void cStageMng::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	
	if(m_bSelectStage == true)	//���� -1�̶�� �޴������̴ϱ� PasS!
	{
		SAFE_ONFRAMEMOVE(m_pDialog);
	}
	else
	{
		SAFE_ONFRAMEMOVE(m_ppStagePart[cMain()->m_nCurrenttage]);
	}
	

}


void cStageMng::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	HRESULT hr;
	V(pd3dDevice->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255,1,255,255), 1.0f, 0));
	if(SUCCEEDED(pd3dDevice->BeginScene()))
	{
		if(m_bSelectStage == true)	//���� -1�̶�� �޴������̴ϱ� PasS!
		{
			SAFE_ONFRAMERENDER(m_pDialog);
		}
		else
		{
			SAFE_ONFRAMERENDER(m_ppStagePart[cMain()->m_nCurrenttage]);
			//SAFE_ONFRAMERENDER(m_pStageMenu);
			//SAFE_ONFRAMERENDER(m_pStageMenu);
		}
		V(pd3dDevice->EndScene());
	}
}



void cStageMng::OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down,
						   bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext)
{
	SAFE_ONMOUSE(m_pDialog);

}


LRESULT cStageMng::OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)
{
	if( m_bSelectStage )
	{
		SAFE_ONMSGPROC(m_pDialog);
		
	}
	else
	{
	}

	return uMsg;
}


void cStageMng::OnEvent(UINT id, int xPos, int yPos)
{
	switch(id)
	{
	default:
		break;
	}
	OnSwitchSelectStage(id, m_nMapListCount);
}


void cStageMng::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{


	if(m_bSelectStage == true)
	{
		
	}
	else
	{
		SAFE_ONKEYBOARD(m_ppStagePart[cMain()->m_nCurrenttage]);
	}

	switch(nChar)
	{
	case VK_SPACE:
		break;
	}
}


void cStageMng::LoadStageData(const WCHAR* pFileName)
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
		KGOutputDebugString(L"�� �ε� ����\n");
		printf("�ʷε�����!!\n");
		return;
	}

	while(!feof(fp))
	{
		fgetws(m_cLine, sizeof(m_cLine), fp);
		swscanf(m_cLine, L"%s", m_cString);

		if(wcscmp(m_cString, L"//") == 0)
			continue;

		if(wcscmp(m_cString, L"[MAPLIST]") == 0)
			DecodeStage(fp);
	}
	fclose(fp);
}


void cStageMng::DecodeStage(FILE* fp)
{
	WCHAR cLine[LARGE_SIZE];
	WCHAR ctemp[LARGE_SIZE];
	WCHAR cStageRoot[LARGE_SIZE];
	WCHAR cStageName[LARGE_SIZE];
	int nResolutionX, nResolutionY;
	int nStageNumber		= 0;
	int	nMapListCount		= 0;

	memset(cLine, 0, sizeof(cLine));
	memset(ctemp, 0, sizeof(ctemp));
	fgetws(cLine, sizeof(cLine), fp);
	swscanf(cLine, L"%d", &nMapListCount); //���������� ������ �����ɴϴ�.

	m_nMapListCount = nMapListCount;

	m_ppStagePart = new cStagePart*[nMapListCount];	//���������� �����Ҵ� �մϴ�.

	for( int i = 0 ; i < nMapListCount; i++ )
	{
		memset(cLine, 0, sizeof(cLine));
		fgetws(cLine, sizeof(cLine), fp);
		swscanf(cLine, L"%s %s %d %d", cStageRoot, cStageName, &nResolutionX, &nResolutionY); //Stage Number StageName ����
		m_ppStagePart[i] = new cStagePart(m_pAnimate, i, cStageRoot, cStageName, nResolutionX, nResolutionY);
	}


	//==========================================================
	//�������� �ڵ� ����
	//==========================================================
	memset(ctemp, 0, sizeof(ctemp));
	fgetws(ctemp, sizeof(ctemp), fp);

	int nStageTileX, nStageTileY, nTileInterVal, nTileInterVal2;
	WCHAR TRASH[255];

	memset(ctemp, 0, sizeof(ctemp));
	fgetws(ctemp, sizeof(ctemp), fp);
	swscanf(ctemp, L"%d %d %s %d %d", &nStageTileX, &nStageTileY, TRASH, &nTileInterVal, &nTileInterVal2); //

	//==========================================================
	//�������� ����
	//==========================================================
	int nIDGive = 0;	//ID�� �ֱ� ���Ѱ�.
	for( int j = 0; j < nStageTileX; j++ )
	{
		for( int k = 0; k < nStageTileY; k++ )
		{
			m_pDialog->AddButton(nIDGive, L"RealZone", L"RealZone", L"RealZone", L"RealZone", 
				D3DXVECTOR3((float)k*nTileInterVal2+nTileInterVal,(float)j*nTileInterVal2+nTileInterVal,0));
			m_pDialog->AddNumber(nIDGive, L"num_", D3DXVECTOR3((float)k*nTileInterVal2+nTileInterVal,
				(float)j*nTileInterVal2+nTileInterVal,0));
			m_pDialog->GetNumber(nIDGive)->SetNumber(nIDGive+1);
			nIDGive++;
		}
	}
}


void cStageMng::OnSwitchSelectStage(UINT id, int nMapListCount)
{
	//==========================================================
	//Switch�� ���������� ������ �Լ�
	//==========================================================
	for( int i = 0; i < nMapListCount; i++ )
	{
		if( id == 1*i )
		{
			cMain()->m_nCurrenttage = 1*i;
			m_bSelectStage = false;
			return;
		}
	}
}