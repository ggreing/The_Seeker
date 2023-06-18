#pragma once
#include<process.h>
#include<Windows.h>

typedef struct BOSS {
	int bossHP;
	int phase1Cooldown;
	int phase2Cooldown;
	int phase3Cooldown;
	int time;
} BOSS;

extern BOSS boss;
extern HANDLE bossCooldownThread;
extern DWORD threadId;
extern CRITICAL_SECTION cs;
void BossInfoInit(); //boss 정보 초기화
DWORD WINAPI Thread_BOSS_COOLDOWN(LPVOID);
void bossLightning(COORD pos, int attackRange);
COORD SetAttackPos(int range);
void bossCooldown();
void clearLightning();
void removeLightning();