#include "cWall.h"

cWall::cWall(KGAnimate* pAnimate, int nX, int nY, int nW, int nH, int nAtribeState)
{
	m_pSprite				= pAnimate->GetSprite();
	m_pAnimate				= pAnimate;

	m_nX					= nX;
	m_nY					= nY;
	m_nH					= nH/2;		//wÀÇ ¹Ý
	m_nW					= nW/2;
	m_nAtribeState			= nAtribeState;

	
}


cWall::~cWall()
{
}


void cWall::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	//SettingLieXY();		//°ÅÁþ ÁÂÇ¥ ÇÔ¼ö

	m_nUp					= m_nY - m_nH;
	m_nDown					= m_nY + m_nH;
	m_nLeft					= m_nX - m_nW;
	m_nRight				= m_nX + m_nW;

	m_rObjectRect			= KGRect( m_nX - m_nW, m_nY  - m_nH, m_nX + m_nW, m_nY  + m_nH );

	OnAttribeColl();	//¾îÆ®¸®ºê»óÅÂ

	//pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_nX;

	/*printf("m_bLeft : \t%d\nm_bRight : \t%d\nm_bUp : \t%d\nm_bDown : \t%d\n",
		m_nLeft, m_nRight, m_nUp, m_nDown);*/

}


void cWall::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	switch(m_nAtribeState)
	{
	case REAL:
		m_pSprite->Render(L"RealZone", m_rObjectRect, COLOR);
		break;
	case BLACK:
		m_pSprite->Render(L"BlackZone", m_rObjectRect, COLOR);
		break;
	case WHITE:
		m_pSprite->Render(L"WhiteZone", m_rObjectRect, COLOR);
		break;
	default:
		break;
	}
}


void cWall::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{

	switch(nChar)
	{
	case VK_UP:

		break;
	}
}


void cWall::SettingLieXY()
{
	cStageMng* pStageMng = (cStageMng*)cMain()->GetCurrent();

	if( pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_nX < SCREEN_WIDTH / 2)
		m_nLieX = 0;
	else if( pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_nX > 1000 - (SCREEN_WIDTH/2))
		m_nLieX = 1000 - SCREEN_WIDTH;
	else
		m_nLieX = pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_nX - (SCREEN_WIDTH/2);


	if( pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_nY < SCREEN_HEIGHT / 2)
		m_nLieY = 0;
	else if( pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_nY > 1000 - (SCREEN_HEIGHT/2))
		m_nLieY = 1000 - SCREEN_HEIGHT;
	else
		m_nLieY = pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_nY - (SCREEN_HEIGHT/2);
}


int cWall::GetLieX()
{
	return (m_nX - m_nLieX);
}


int cWall::GetLieY()
{
	return (m_nY - m_nLieY);
}


void  cWall::OnAttribeColl()
{
	cStageMng* pStageMng = (cStageMng*)cMain()->GetCurrent();


	if( m_rObjectRect.isOverlap( pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_rHeroRect ) )
	{
		if( m_nAtribeState != pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_nAttribeState )
		{
			if( pStageMng->m_ppStagePart[cMain()->m_nCurrenttage]->m_pHero->m_nAttribeState == REAL || m_nAtribeState == REAL )
				return;

			printf("»ç¸Á\n");
		}
	}
}