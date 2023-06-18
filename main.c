#pragma warning(disable:4996)
#include "System.h"
#include "interface.h"
#include "stage.h"
#include "Player.h"
#include "ItemAndWeapon.h"
#include "script.h"
#include <conio.h>
#include <time.h>

int main(void)
{
    system("mode con cols=130 lines=42");
    RemoveCursor();

    // 스테이지 출력
    StageInforInit(1);
    //printStage();

    ShowPlayer();
	StageInforInit(1);
	getScript(0);
	printScriptQueue();
	ShowPlayer();
	getScript(1);
	printScriptQueue();
	clearStage();
    while (1) {
		ShowPlayer();
        if (isPlayerDead() == 1) {
            StageInforInit(stageNum);
        }
		if (gun.shotOrNot && !showBullet()) {
			continue;
		}
		ProcessKeyInput();
		PrintUI();
    }
    getchar();
    return 0;
}