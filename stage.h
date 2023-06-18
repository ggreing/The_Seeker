#pragma once
#include "interface.h"
#include "ItemAndWeapon.h"
#include "Player.h"
#include "System.h"
#include <stdio.h>
#include <stdbool.h>

extern int stageNum;
extern char STAGE[STAGE_Y][STAGE_X / 2];
void GetStageInfor(int StageNum); //파일 입출력을 StageNum에 해당하는 스테이지 파일을 읽어 STAGE에 저장.
void printStage(); //스테이지 전체를 출력하는 함수
void showStage(int stageObject, int posX, int posY); //posX, posY에 stageObject를 출력하는 함수.
void PrintUI(); //UI출력함
void StageInforInit(int stageNum); //스테이지, 플레이어, 몬스터 등 정보 초기화
void clearStage(); //스테이지 화면 초기화
void clearScreen(); //화면 전체 초기화
void GameOver();  //게임오버 화면 출력, 6초 뒤에 자동으로 다시 시작함.
void GameStart(); //게임메인 화면 출력
int SelectMenu(); //게임시작, 도움말, 게임종료 메뉴를 선택할 수 있음. 리턴값은 각각 0, 1, 2
void help(); //도움말 출력