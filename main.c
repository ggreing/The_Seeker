#pragma warning(disable:4996)
#include "System.h"
#include "interface.h"
#include "stage.h"
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

void ShowCharacter();
void DeleteCharacter();
void ProcessKeyInput();
void ShiftRight(void);
void ShiftLeft(void);
void ShiftUp(void);
void ShiftDown(void);
int curPosX = 0, curPosY = 0;

int main(void)
{
    system("mode con cols=180 lines=50");
    RemoveCursor();

    // 스테이지 출력
    GetStageInfor(1);
    printStage();

    int key;
    curPosX = 4;
    curPosY = 2;
    SetCurrentCursorPos(curPosX, curPosY);
    ShowCharacter();

    while (1)
    {
        ProcessKeyInput();
        PrintUI();
    }
    getchar();
    return 0;
}
void ProcessKeyInput() {
    int key;

    if (_kbhit() != 0) {
        key = _getch();
        switch (key) {
        case LEFT:
            ShiftLeft();
            break;
        case RIGHT:
            ShiftRight();
            break;
        case UP:
            ShiftUp();
            break;
        case DOWN:
            ShiftDown();
            break;
        }
    }
}

void ShiftRight(void)
{
    if (!DetectCollision(curPosX + 2, curPosY)) return;

    DeleteCharacter();
    curPosX += 2;
    SetCurrentCursorPos(curPosX, curPosY);
    ShowCharacter();
}
void ShiftLeft(void)
{
    if (!DetectCollision(curPosX - 2, curPosY)) return;

    DeleteCharacter();
    curPosX -= 2;
    SetCurrentCursorPos(curPosX, curPosY);
    ShowCharacter();
}
void ShiftUp(void)
{
    if (!DetectCollision(curPosX, curPosY - 1)) return;

    DeleteCharacter();
    curPosY -= 1;
    SetCurrentCursorPos(curPosX, curPosY);
    ShowCharacter();
}
void ShiftDown(void)
{
    if (!DetectCollision(curPosX, curPosY + 1)) return;

    DeleteCharacter();
    curPosY += 1;
    SetCurrentCursorPos(curPosX, curPosY);
    ShowCharacter();
}
void ShowCharacter()
{
    COORD curPos = GetCurrentCursorPos();
    SetCurrentCursorPos(curPos.X, curPos.Y);
    printf("◈");    // PC icon
    SetCurrentCursorPos(curPos.X, curPos.Y);

}
void DeleteCharacter()
{
    COORD curPos = GetCurrentCursorPos();
    SetCurrentCursorPos(curPos.X, curPos.Y);
    printf("  ");
}
int DetectCollision(int posX, int posY) {
    int pcX = (posX) / 2;
    int pcY = posY;

    if (STAGE[pcY ][pcX ] != EMPTY_SPACE)
        return 0;
    return 1;
}