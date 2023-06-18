#include "System.h"
#include "interface.h"
#include "stage.h"
#include "Player.h"
#include "ItemAndWeapon.h"
#include "script.h"
#include <conio.h>
#include <time.h>
#include "boss.h"
#include "Sound.h"
#include "monster.h"

int stageNum = 1;
int d = 0;
isCleared = 0;

int main(void)
{

	system("mode con cols=130 lines=42");
	RemoveCursor();
	SoundInit();

	// 메인화면 출력
	GameStart();

	playerInfoInit(MAX_LIFE, 0, 0, INIT_WEAPON, RIGHT);
	initGunInfo();
	initRockInfo();

	// 스테이지 출력
	StageInforInit(stageNum);
	getScript(0);
	printScriptQueue();

	getScript(stageNum);
	printScriptQueue();
	clearStage();
	ShowPlayer();
	PrintUI();
	MonsterInit();
	while (1) {
		ShowPlayer();
		if (isPlayerDead() == 1) {
			if (stageNum == 4) {
				clearStage();
				stageNum++;
				getScript(stageNum);
				printScriptQueue();
				stageNum--;
			}
			GameOver();
			StageInforInit(stageNum);
			initGunInfo();
			initRockInfo();

			player.life = 3;
			MonsterInit();
			bossCooldownThread = CreateThread(NULL, 0, Thread_BOSS_COOLDOWN, (LPVOID)1, 0, &threadId);
		}
		if (gun.shotOrNot && !showBullet()) {
			continue;
		}
		if (rock.throwOrNot && !showRock()) {
			continue;
		}
		ProcessKeyInput();
		if (stageNum == 4) {
			bossCooldown();
			clearLightning();
		}

		t_pos = SoundPoint();
		isMonsterInRange(d, t_pos);
		Sleep(30);
		d++;
		PrintUI();
		FindMonster();
	}
	getchar();
	return 0;
}