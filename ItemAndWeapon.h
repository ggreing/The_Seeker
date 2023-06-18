#pragma once
#include "System.h"
#include <Windows.h>

// 총쏘기 관련
typedef struct GUN {
	int shootingRange;
	COORD arriveBulletPos;		// 총알이 도착해야하는 위치
	COORD currentBulletPos;		// 날아가는 총알의 현 위치
	int shotOrNot;						// 총 발사 여부
	int currentDirect;					// 총 사용 방향
}GUN;

extern GUN gun;

// 돌멩이 아이템 관련
typedef struct ROCK {
	COORD arriveRockPos;		//  돌멩이가 도착해야하는 위치
	COORD currentRockPos;		//  던져진 돌멩이 현 위치
	int throwOrNot;					//  돌멩이 투척 여부
	int currentDirect;					//  돌멩이 사용 방향
	int distance;						//  돌멩이-벽 간의 거리
	int showRange;					//  거리에 따른 주변 밝혀지는 간격
}ROCK;

extern ROCK rock;

// functions
void initGunInfo(void);
void initRockInfo(void);
COORD moveByDirection(int currentDirect);	// 인자로 받은 방향에 따라 아이템/무기의 x,y좌표 변화량 반환
void shotGun(void);		// 무기 사용 - 탄피가 날아가서 멈추는 위치 정보 저장
int showBullet(void);	// shotGun에서 저장된 위치까지 탄피가 움직이는 것을 보여줌
void useItemRock(void);	// 돌멩이 아이템 사용
int showRock(void);	// 돌멩이 아이템이 날아가는 것을 보여줌
void useItemPortion(void);	// 포션 아이템 사용