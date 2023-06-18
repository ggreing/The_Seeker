#pragma once
#include "boss.h"
#include "Player.h"

BOSS boss;
HANDLE bossCooldownThread;
DWORD threadId;
COORD attackPos;
void BossInfoInit() {
	boss.bossHP = 3;
	boss.phase1Cooldown = 10;
	boss.phase2Cooldown = 8;
	boss.phase3Cooldown = 5;
	boss.time = 0;
}
DWORD WINAPI Thread_BOSS_COOLDOWN(LPVOID n) {
	while (1) {
		if (boss.time > boss.phase1Cooldown) boss.time = 0;
		boss.time++;
		Sleep(1000);
		if (isPlayerDead() == 1) {
			break;
		}
		if (boss.bossHP == 0) {
			break;
		}
	}
	_endthread();
	return 0;
}
void bossCooldown() {
	if (boss.bossHP == 3) {
		if (boss.phase1Cooldown == boss.time) {
			boss.time = 0;
			attackPos = SetAttackPos(5);
			bossLightning(attackPos, 2);
			attackPos.X *= 2;
			showSoundRange(attackPos, LIGHTNING, 7);
		}
	}
	else if (boss.bossHP == 2) {
		if (boss.phase2Cooldown == boss.time) {
			boss.time = 0;
			attackPos = SetAttackPos(5);
			bossLightning(attackPos, 2);
			attackPos.X *= 2;
			showSoundRange(attackPos, LIGHTNING, 7);
		}
	}
	else if (boss.bossHP == 1) {
		if (boss.phase3Cooldown == boss.time) {
			boss.time = 0;
			attackPos = SetAttackPos(5);
			bossLightning(attackPos, 2);
			attackPos.X *= 2;
			showSoundRange(attackPos, LIGHTNING, 7);
		}
	}
	if (boss.time > boss.phase1Cooldown) {
		boss.time = 0;
	}
}
void bossLightning(COORD curPos, int attackRange) {
	int posX = curPos.X;
	int posY = curPos.Y;

	for (posX = curPos.X; posX >= 0 && posX > curPos.X - attackRange; posX--) {
		for (posY = curPos.Y; posY >= 0 && posY > curPos.Y - attackRange; posY--) {
			if (STAGE[posY][posX] == 0) {
				STAGE[posY][posX] = LIGHTNING;
			}
			if (STAGE[posY][posX] == WALL) break;
		}
		for (posY = curPos.Y; posY < STAGE_Y && posY < curPos.Y + attackRange; posY++) {
			if (STAGE[posY][posX] == 0) {
				STAGE[posY][posX] = LIGHTNING;
			}
			if (STAGE[posY][posX] == WALL) break;
		}
		if (STAGE[curPos.Y][posX] == WALL) break;
	}
	for (posX = curPos.X; posX < STAGE_X / 2 && posX < curPos.X + attackRange; posX++) {
		for (posY = curPos.Y; posY >= 0 && posY > curPos.Y - attackRange; posY--) {
			if (STAGE[posY][posX] == 0) {
				STAGE[posY][posX] = LIGHTNING;
			}
			if (STAGE[posY][posX] == WALL) break;
		}
		for (posY = curPos.Y; posY < STAGE_Y && posY < curPos.Y + attackRange; posY++) {
			if (STAGE[posY][posX] == 0) {
				STAGE[posY][posX] = LIGHTNING;
			}
			if (STAGE[posY][posX] == WALL) break;
		}
		if (STAGE[curPos.Y][posX] == WALL) break;
	}
	for (posY = curPos.Y; posY >= 0 && posY > curPos.Y - attackRange; posY--) {
		for (posX = curPos.X; posX >= 0 && posX > curPos.X - attackRange; posX--) {
			if (STAGE[posY][posX] == 0) {
				STAGE[posY][posX] = LIGHTNING;
			}
			if (STAGE[posY][posX] == WALL) break;
		}
		for (posX = curPos.X; posX < STAGE_X / 2 && posX < curPos.X + attackRange; posX++) {
			if (STAGE[posY][posX] == 0) {
				STAGE[posY][posX] = LIGHTNING;
			}
			if (STAGE[posY][posX] == WALL) break;
		}
		if (STAGE[posY][curPos.X] == WALL) break;
	}
	for (posY = curPos.Y; posY < STAGE_Y && posY < curPos.Y + attackRange; posY++) {
		for (posX = curPos.X; posX >= 0 && posX > curPos.X - attackRange; posX--) {
			if (STAGE[posY][posX] == 0) {
				STAGE[posY][posX] = LIGHTNING;
			}
			if (STAGE[posY][posX] == WALL) break;
		}
		for (posX = curPos.X; posX < STAGE_X / 2 && posX < curPos.X + attackRange; posX++) {
			if (STAGE[posY][posX] == 0) {
				STAGE[posY][posX] = LIGHTNING;
			}
			if (STAGE[posY][posX] == WALL) break;
		}
		if (STAGE[posY][curPos.X] == WALL) break;
	}
}
COORD SetAttackPos(int range) {
	COORD playerPos = player.playerPos;
	playerPos.X /= 2;
	srand(time(NULL));

	while (1) {
		int posX_rand = (unsigned int)rand() % range;
		int posY_rand = (unsigned int)rand() % range;
		int multiMin = (unsigned int)rand() % 2;

		if (multiMin == 1) posX_rand *= -1;
		multiMin = (unsigned int)rand() % 2;
		if (multiMin == 1) posY_rand *= -1;

		playerPos.X += posX_rand;
		playerPos.Y += posY_rand;
		if (playerPos.X > STAGE_X / 2 || playerPos.X < 0 || playerPos.Y > STAGE_Y || playerPos.Y < 0) continue;
		if (STAGE[playerPos.Y][playerPos.X] == 0) break;
	}
	return playerPos;
}
void clearLightning() {
	if (boss.time == 3) {
		removeLightning();
		showSoundRange(attackPos, LIGHTNING, 2);
	}
}
void removeLightning() {
	int i, j;
	for (i = attackPos.Y - 2; i < attackPos.Y + 2 && i < STAGE_Y; i++) {
		for (j = attackPos.X / 2 - 2; j < attackPos.X / 2 + 2 && j < STAGE_X / 2; j++) {
			if (STAGE[i][j] == LIGHTNING) STAGE[i][j] = EMPTY_SPACE;
		}
	}
}