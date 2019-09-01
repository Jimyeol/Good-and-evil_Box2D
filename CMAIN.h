#ifndef _CMAIN_H
#define _CMAIN_H

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include <KGEmotion.h>
#if defined(DEBUG)  ||  defined(_DEBUG)
#pragma comment(lib, "KGEmotionD.lib")
#else
#pragma comment(lib, "KGEmotion.lib")
#endif


class cmain : public KG::KGEmotion
{
public:
	static cmain*			m_pMain;

	int						m_nCurrenttage;


public:
	cmain();
	~cmain();


public:
	void			Create();
	void			Init();

};

inline cmain*      cMain()
{
	return cmain::m_pMain;
}
#endif