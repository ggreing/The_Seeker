#pragma once
#include<Windows.h>
#include"System.h"

typedef struct PLAYER {
	int life;
	int item_rock;
	int item_portion;
	int weapon;
	int direction;
	int stageKey;
	COORD playerPos;
} PLAYER;

extern PLAYER player;

// player
void playerInfoInit(int life, int item_rock, int item_portion, int weapon, int direction); //player 파라미터 초기화
void playerPosInit(int playerPosX, int playerPosY); //player의 위치 정보 초기화
int playerShiftRight(void); //player를 충돌검사 후 오른쪽으로 움직임. playerMove 하위 메소드
int playerShiftLeft(void); //player를 충돌검사 후 왼쪽으로 움직임. playerMove 하위 메소드
int playerShiftUp(void); //player를 충돌검사 후 위로 움직임. playerMove 하위 메소드
int playerShiftDown(void); //player를 충돌검사 후 아래로 움직임. playerMove 하위 메소드
void ShowPlayer(); //player의 캐릭터를 플레이어가 위치한 좌표에 출력함
void DeletePlayer(); //player의 캐릭터를 플레이어가 위치한 좌표에서 삭제함.
void playerMove(int direction); //player 이동 함수. player 이동 시 아이템, 무기 획득, 몬스터에 의한 데미지 입는 기능과 연결.
int isPlayerDead(); //player의 라이프라 0일 경우 1 반환, 이외에 경우 0 반환
int isPlayerHasKey(); //player가 key를 가지고 있으면 1 반환, 이외에 경우 0 반환