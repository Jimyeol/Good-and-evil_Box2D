#ifndef _CSTAGEMNG_H
#define _CSTAGEMNG_H

#include "MyInclude.h"

using namespace KG;

class cStagePart;
class cStageMenu;

class cStageMng : public KGScene , public KGResponseDialog
{
private:
	KGSprite*			m_pSprite;
	KGAnimate*			m_pAnimate;
	KGDialog*			m_pDialog;

public:
	//===============================================
	//    스테이지 관리 변수들
	//===============================================
	cStagePart**		m_ppStagePart;
	cStageMenu*			m_pStageMenu;

	int					m_nResolutionX;		//해상도 X
	int					m_nResolutionY;		//해상도 Y

	int					m_nMapListCount;	//스테이지 갯수

	bool				m_bSelectStage;



public:
	cStageMng();
	~cStageMng();

public:
	HRESULT CALLBACK	OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);
	HRESULT CALLBACK	OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);
	void CALLBACK		OnLostDevice(void* pUserContext);
	void CALLBACK		OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK		OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK		OnDestroyDevice(void* pUserContext);
	void CALLBACK		OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext);
	void CALLBACK		OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down,
						   bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext);
	void CALLBACK		OnEvent(UINT id, int xPos, int yPos);
	LRESULT	CALLBACK	OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext);



private:
	void				LoadStageData(const WCHAR* pFileName);
	void				DecodeStage(FILE* fp);

	void				OnSwitchSelectStage(UINT id, int nMapListCount);
};

#endif