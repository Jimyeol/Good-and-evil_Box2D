#include "cLever.h"

cLever::cLever( KGAnimate* pAnimate, int nX, int nY, int nW, int nH, int whatRoot, int whatkind, int nID )
{
	m_pSprite				= pAnimate->GetSprite();
	m_pAnimate				= pAnimate;

	m_nX					= nX;
	m_nY					= nY;
	m_nW					= nW;
	m_nH					= nH;
	m_nWhatRoot				= whatRoot;
	m_nWhatKind				= whatkind;
	m_nID					= nID;

	m_rObjectRect			= KGRect( m_nX - m_nW, m_nY - m_nH, m_nX + m_nW, m_nY + m_nH );
 
}


cLever::~cLever()
{

}


void cLever::OnLostDevice(void* pUserContext)
{
}


void cLever::OnDestroyDevice(void* pUserContext)
{
}


void cLever::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{

}


void cLever::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	switch(m_nWhatKind)
	{
	case BLACK:
		m_pSprite->Render(L"bt_renewal_click", m_rObjectRect, COLOR);
		break;
	case WHITE:
		break;
	case REAL:
		break;
	}
}


void cLever::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{
	//----------------------------------------------------------------
	//ID가 똑같으면 움직이게하는 코드
	//===============================================================
	cStageMng* pStageMng = (cStageMng*)cMain()->GetCurrent();
	if( m_rObjectRect.isOverlap(pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_rHeroRect) )
	{
		switch(nChar)
		{
		case VK_UP:
			for( int i = 0; i < pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_nLeverWallNumber; i++ )
			{
				if( m_nID == pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_ppLeverWall[i]->m_nID )
				{
					if( pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_ppLeverWall[i]->m_nMoveCheck == OFF)
					{
						pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_ppLeverWall[i]->m_nMoveCheck = ON;
					}
					else
					{
						pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_ppLeverWall[i]->m_nMoveCheck = OFF;
					}
				}
			}
			break;
		}
	}
}