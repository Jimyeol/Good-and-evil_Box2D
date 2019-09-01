#include "MyInclude.h"

using namespace KG;

IMPLEMENT_MAIN(cmain);

cmain::cmain() : KG::KGEmotion(L"GoodAndEvil", 1000, 600)
{
 m_pMain		 =			this;
 m_nCurrenttage				= 0;

#if defined(NDEBUG)
 SetFullScreenBackBufferWidthAtModeChange(800);
 SetFullScreenBackBufferHeightAtModeChange(600);
 SetOverrideWidth(1000);
 SetOverrideHeight(600);
 SetOverrideFullScreen(false);
 SetHandleAltEnter(false);
 SetHandleDefaultHotkeys(false);
 SetShowMsgBoxOnError(true);
 SetShowCursorWhenFullScreen(false);
#endif
}
cmain::~cmain()
{
}
void cmain::Create()
{
	Entry(L"menu", new cMenu);
	Entry(L"logo", new cLogo);
	Entry(L"stage_ch", new cStageMng);
}
void cmain::Init()
{
	Trans(L"logo");
}
