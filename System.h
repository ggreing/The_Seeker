#pragma once
#include"Sound.h"
#include"interface.h"
#include"stage.h"
#include"Player.h"
#include<Windows.h>

COORD GetCurrentCursorPos(void); //커서의 현재 좌표 반환
void RemoveCursor(void); //커서가 깜박이지 않게 함
void SetCurrentCursorPos(int x, int y); //현재 커서의 좌표 지정
void ProcessKeyInput(); //플레이어로부터 키 입력을 받음
int DetectCollision(int posX, int posY); //posX와 posY에 있는 오브젝트가 어떤 오브젝트와 부딛치는지 반환
void showSoundRange(COORD curPos, int objNum, int range); //curPos에 range만큼의 범위를 보여줌.
