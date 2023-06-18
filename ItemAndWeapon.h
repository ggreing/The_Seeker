#pragma once
#include "System.h"
#include <Windows.h>


// weapon&item
extern int currentDirect;				// 아이템/총 사용 시점의 플레이어 방향
// 총쏘기 관련
typedef struct GUN {
	int shootingRange;
	COORD currentShotPos;	// 총알이 도착해야하는 위치
	COORD bulletPos;			// 날아가는 총알의 현 위치
	int shotOrNot;					// 총을 쏘는지 안쏘는지
}GUN;

extern GUN gun;

// 돌멩이 아이템 관련

// functions
COORD moveByDirection(void);	// 플레이어 방향에 따라 아이템/무기의 x,y좌표 변화량 반환
void initGunInfo();
void shotGun(void);		// 무기 사용 - 탄피가 날아가서 멈추는 위치 정보 저장
int showBullet(void);	// shotGun에서 저장된 위치까지 탄피가 움직이는 것을 보여줌
void useItemRock(void);	// 돌멩이 아이템 사용
void useItemPortion(void);	// 포션 아이템 사용