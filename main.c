#pragma warning(disable:4996)
#include "System.h"
#include "interface.h"
#include "stage.h"
#include "Player.h"
#include "ItemAndWeapon.h"
#include "script.h"
#include "Sound.h"
#include <conio.h>
#include <time.h>

int main(void)
{
    system("mode con cols=130 lines=42");
    RemoveCursor();
    SoundInit();

    // 메인화면 출력
    GameStart();

    // 스테이지 출력
    StageInforInit(1);

    getScript(0);
    printScriptQueue();
    getScript(1);
    printScriptQueue();
    clearStage();
    ShowPlayer();

    while (1) {
        ShowPlayer();
        if (isPlayerDead() == 1) {
            GameOver();
            StageInforInit(stageNum);
        }
        if (gun.shotOrNot && !showBullet()) {
            continue;
        }
        Sleep(30);
        ProcessKeyInput();
        PrintUI();
    }

    getchar();
    return 0;
}