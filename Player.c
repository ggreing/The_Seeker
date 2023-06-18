#include "Player.h"
#include "interface.h"
#include "System.h"
#include "Sound.h"
#include "boss.h"
#include "stage.h"
#include <stdio.h>
#include <Windows.h>
#include <process.h>

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
	Sound_Play(WALKING);
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
	Sound_Play(WALKING);
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
	Sound_Play(WALKING);
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
	Sound_Play(WALKING);
	return detectCollision;
}
void ShowPlayer()
{
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
}
void DeletePlayer()
{
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
		Sound_Play(GET_ITEM1);
		player.item_rock++;
		STAGE[player.playerPos.Y][player.playerPos.X / 2] = 0;
		PrintUI();
		break;
	case ITEM_2:
		player.item_portion++;
		STAGE[player.playerPos.Y][player.playerPos.X / 2] = 0;
		PrintUI();
		break;
	case WEAPON:
		Sound_Play(GET_GUN);
		player.weapon++;
		STAGE[player.playerPos.Y][player.playerPos.X / 2] = 0;
		PrintUI();
		break;
	case MONSTER:
		Sound_Play(DAMAGE);
		player.life--;
		PrintUI();
		break;
	case KEY:
		Sound_Play(GET_KEY);
		player.stageKey++;
		STAGE[player.playerPos.Y][player.playerPos.X / 2] = 0;
		PrintUI();

		if (stageNum == 4) {
			if (player.stageKey == 1) {
				boss.bossHP = 2;
				STAGE[20][18] = 0;
				STAGE[21][18] = 0;
				STAGE[22][18] = 0;
			}
			else if (player.stageKey == 2) {
				boss.bossHP = 1;
				STAGE[15][23] = 0;
				STAGE[15][24] = 0;
				STAGE[15][25] = 0;
			}
			else if (player.stageKey == 3) {
				boss.bossHP = 1;
				STAGE[5][22] = 0;
				STAGE[6][22] = 0;
				STAGE[7][22] = 0;
			}
		}
		break;
	case EXIT:
		if (isPlayerHasKey() >= 1) {
			Sound_Play(USE_KEY);
			player.stageKey = 0;
			stageNum++;
			StageInforInit(stageNum);
			clearStage();
			getScript(stageNum);
			printScriptQueue();
			clearStage();
			ShowPlayer();

			PrintUI();
			if (stageNum == 4) {
				BossInfoInit();
				bossCooldownThread = CreateThread(NULL, 0, Thread_BOSS_COOLDOWN, (LPVOID)1, 0, &threadId);
			}
		}
		break;
	case LIGHTNING:
		Sound_Play(DAMAGE);
		player.life--;
		PrintUI();
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
