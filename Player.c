#include "Player.h"
#include "interface.h"
#include "System.h"
#include <stdio.h>
#include <Windows.h>

PLAYER player;
shootingRange = 7;
void playerInfoInit(int life, int item_rock, int item_portion, int weapon, int direction) {
	player.life = life;
	player.item_rock = item_rock;
	player.item_portion = item_portion;
	player.weapon = weapon;
	player.direction = direction;
	player.stageKey = 0;
}
void playerPosInit(int playerPosX, int playerPosY) {
	player.playerPos.X = playerPosX;
	player.playerPos.Y = playerPosY;
}
int playerShiftRight(void)
{
	int detectCollision = DetectCollision(player.playerPos.X + 2, player.playerPos.Y);
	if (detectCollision == WALL) return WALL;
	//else if (detectCollision == MONSTER) return MONSTER;

	DeletePlayer();
	player.playerPos.X += 2;
	SetCurrentCursorPos(player.playerPos.X, player.playerPos.Y);
	player.direction = RIGHT;
	ShowPlayer();
	return detectCollision;
}
int playerShiftLeft(void)
{
	int detectCollision = DetectCollision(player.playerPos.X - 2, player.playerPos.Y);
	if (detectCollision == WALL) return WALL;
	//else if (detectCollision == MONSTER) return MONSTER;

	DeletePlayer();
	player.playerPos.X -= 2;
	SetCurrentCursorPos(player.playerPos.X, player.playerPos.Y);
	player.direction = LEFT;
	ShowPlayer();

	return detectCollision;
}
int playerShiftUp(void)
{
	int detectCollision = DetectCollision(player.playerPos.X, player.playerPos.Y - 1);
	if (detectCollision == WALL) return WALL;
	//else if (detectCollision == MONSTER) return MONSTER;

	DeletePlayer();
	player.playerPos.Y -= 1;
	SetCurrentCursorPos(player.playerPos.X, player.playerPos.Y);
	player.direction = UP;
	ShowPlayer();
	return detectCollision;
}
int playerShiftDown(void)
{
	int detectCollision = DetectCollision(player.playerPos.X, player.playerPos.Y + 1);
	if (detectCollision == WALL) return WALL;
	//else if (detectCollision == MONSTER) return MONSTER;

	DeletePlayer();
	player.playerPos.Y += 1;
	SetCurrentCursorPos(player.playerPos.X, player.playerPos.Y);
	player.direction = DOWN;
	ShowPlayer();
	return detectCollision;
}
void ShowPlayer()
{
	COORD curPos = GetCurrentCursorPos();
	SetCurrentCursorPos(player.playerPos.X, player.playerPos.Y);
	//printf("﹥");    // PC icon
	switch (player.direction) {
	case LEFT:
		printf("←");
		break;
	case RIGHT:
		printf("→");
		break;
	case UP:
		printf("↑");
		break;
	case DOWN:
		printf("↓");
		break;
	default:
		break;
	}
	SetCurrentCursorPos(curPos.X, curPos.Y);
}
void DeletePlayer()
{
	COORD curPos = GetCurrentCursorPos();
	SetCurrentCursorPos(player.playerPos.X, player.playerPos.Y);
	printf("  ");
}
void playerMove(int direction) {
	int detectCollision = WALL;
	switch (direction) {
	case LEFT:
		detectCollision = playerShiftLeft();
		break;
	case RIGHT:
		detectCollision = playerShiftRight();
		break;
	case UP:
		detectCollision = playerShiftUp();
		break;
	case DOWN:
		detectCollision = playerShiftDown();
		break;
	default:
		break;
	}
	switch (detectCollision) {
	case ITEM_1:
		player.item_rock++;
		break;
	case ITEM_2:
		player.item_portion++;
		break;
	case WEAPON:
		player.weapon++;
		break;
	case MONSTER:
		player.life--;
		break;
	case KEY:
		player.stageKey++;
		break;
	case EXIT:
		break;
	default:
		break;
	}
	showSoundRange(player.playerPos, PC, 5);
}

void shotGun() {

	if (player.weapon == 0) return;		// 탄피가 없음
	player.weapon--;						// 탄피 사용

	COORD curPos, nextPos;
	curPos.X = player.playerPos.X;
	curPos.Y = player.playerPos.Y;
	nextPos.X = player.playerPos.X;
	nextPos.Y = player.playerPos.Y;

	for (int i = 0; i < shootingRange; i++) {
		if (player.direction == LEFT) { 
			nextPos.X -= 2;
		}
		if (player.direction == RIGHT) {
			nextPos.X += 2;
		}
		if (player.direction == UP) {
			nextPos.Y--;
		}
		if (player.direction == DOWN) {
			nextPos.Y++;
		}

		if (DetectCollision(nextPos.X, nextPos.Y) == WALL) { 	// 벽
			return;
		}
		if (DetectCollision(nextPos.X, nextPos.Y) == MONSTER) { 	// 몬스터
			SetCurrentCursorPos(nextPos.X, nextPos.Y);
			printf("※");		// 우선 몬스터와 부딪혔다는 것 표현 //
			
			// 그 후 몬스터 관련 정보 update - 몬스터 die, stage배열 초기화


			return;
		}
		else {
			curPos.X = nextPos.X;
			curPos.Y = nextPos.Y;

			SetCurrentCursorPos(curPos.X, curPos.Y);
			printf("ⅹ");
			Sleep(150);
			SetCurrentCursorPos(curPos.X, curPos.Y);
			showStage(DetectCollision(curPos.X, curPos.Y), curPos.X, curPos.Y);
			//printf("  ");				// 아이템/키 등이 빈칸되는부분 설정
		}
	}
}

int DetectCollision_Bullet(int posX, int posY) {
	int bulletX = (posX) / 2;
	int bulletY = posY;

	// 벽
	if (STAGE[bulletY][bulletX] == WALL)
		return 1;
	// 몬스터
	if (STAGE[bulletY][bulletX] == MONSTER)
		return 2;
	// nothing
	return 0;
}