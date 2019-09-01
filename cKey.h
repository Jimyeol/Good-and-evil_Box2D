#ifndef _cKey_H
#define _cKey_H

#include <windows.h>

inline int KeyDownChk	( int vk ) 
{ 
	return ( (GetAsyncKeyState(vk) & 0x8000) ? 1:0 ); 
}

inline int KeyUpChk		( int vk ) 
{ 
	return ( (GetAsyncKeyState(vk) & 0x8000) ? 0:1 ); 
}

class cKey
{
	bool					m_KeyDownChk[255] ;					// 키 다운 입력 체크 배열

	bool					m_KeyDoubleTimeChk[2] ;
	bool					m_KeyTimeChk ;
	DWORD					m_KeyTime ;
	DWORD					m_KeyDoubleTime ;

public :

	cKey() ;
	~cKey() ;

	bool KeyDown			( int vk ) ;
	bool KeyUp				( int vk ) ;
	bool LongTimeKeyDown	( int vk, float time ) ;
	bool DoubleKeyDown		( int vk, float time ) ;

	int KeyDownSpeed	( int vk ) 
	{ 
		return ( (GetAsyncKeyState(vk) & 0x8000) ? 1:0 ); 
	}

	int KeyUpSpeed	( int vk ) 
	{ 
		return ( (GetAsyncKeyState(vk) & 0x8000) ? 0:1 ); 
	}
} ;

#endif