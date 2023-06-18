#include "Player.h"
#include "interface.h"
#include "System.h"
#include <stdio.h>
#include <Windows.h>
#include <time.h>

PLAYER player;

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
		STAGE[player.playerPos.Y][player.playerPos.X / 2] = 0;
		break;
	case ITEM_2:
		player.item_portion++;
		STAGE[player.playerPos.Y][player.playerPos.X / 2] = 0;
		break;
	case WEAPON:
		player.weapon++;
		STAGE[player.playerPos.Y][player.playerPos.X / 2] = 0;
		break;
	case MONSTER:
		player.life--;
		break;
	case KEY:
		player.stageKey++;
		STAGE[player.playerPos.Y][player.playerPos.X / 2] = 0;
		break;
	case EXIT:
		if (isPlayerHasKey() == 1) {
			stageNum++;
			StageInforInit(stageNum);
			getScript(stageNum);
			printScriptQueue();
			clearStage();
			ShowPlayer();
		}
		break;
	default:
		break;
	}
	showSoundRange(player.playerPos, PC, 5);
}
int isPlayerDead() {
	if (player.life == 0) return 1;
	return 0;
}
int isPlayerHasKey() {
	if (player.stageKey > 0) return 1;
	return 0;
}