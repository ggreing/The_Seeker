#pragma once
#include "interface.h"
#include "Player.h"
#include "System.h"
#include <stdio.h>

extern char STAGE[STAGE_Y][STAGE_X / 2];
void GetStageInfor(int StageNum); //파일 입출력을 StageNum에 해당하는 스테이지 파일을 읽어 STAGE에 저장.
void printStage(); //스테이지 전체를 출력하는 함수
void showStage(int stageObject, int posX, int posY); //posX, posY에 stageObject를 출력하는 함수.
void PrintUI(); //UI출력함
void StageInforInit(int stageNum); //스테이지, 플레이어, 몬스터 등 정보 초기화
