#pragma once

#define LARGE_SIZE 255
#define COLOR D3DXCOLOR(1, 1, 1, 1)

#define REAL 1
#define BLACK 2
#define WHITE 3

#define YES 1
#define NO 2

#define SIDE 1
#define TOP 2

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600

#define WALL 0
#define LEVERWALL 1
#define BOX 2

#define OFF 0
#define ON 1

#define MOVERIGHTTOP 0
#define MOVELEFTDOWN 1

#define PLUSALPHA 3	//충돌시 값 좀 더해주는거

#define PATTERN_MOVE 1 //계속 움직이는거
#define PATTERN_STOP 2 //다가가면 움직임


//------------------------------------------
//점프관련 매크로 변수
//------------------------------------------
#define JUMPDIVIALPHA 100
#define JUMPPLUSALPHA 50