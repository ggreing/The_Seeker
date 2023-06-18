#pragma warning(disable:4996)
#include "System.h"
#include "interface.h"
#include "stage.h"
#include "Player.h"
#include <conio.h>
#include <time.h>

int main(void)
{
    system("mode con cols=180 lines=50");
    RemoveCursor();

    // 스테이지 출력
	StageInforInit(1);
	//printStage();

    SetCurrentCursorPos(player.playerPos.X, player.playerPos.Y);
	ShowPlayer();

    while (1)
    {
        ProcessKeyInput();
        PrintUI();
    }
    getchar();
    return 0;
}