#pragma once
#include "interface.h"
#include "ItemAndWeapon.h"
#include "Player.h"
#include "System.h"
#include <stdio.h>
#include <stdbool.h>

extern int stageNum;
extern char STAGE[STAGE_Y][STAGE_X / 2];
void GetStageInfor(int StageNum); //���� ������� StageNum�� �ش��ϴ� �������� ������ �о� STAGE�� ����.
void printStage(); //�������� ��ü�� ����ϴ� �Լ�
void showStage(int stageObject, int posX, int posY); //posX, posY�� stageObject�� ����ϴ� �Լ�.
void PrintUI(); //UI�����
void StageInforInit(int stageNum); //��������, �÷��̾�, ���� �� ���� �ʱ�ȭ
void clearStage(); //�������� ȭ�� �ʱ�ȭ
void clearScreen(); //ȭ�� ��ü �ʱ�ȭ
void GameOver();  //���ӿ��� ȭ�� ���, 6�� �ڿ� �ڵ����� �ٽ� ������.
void GameStart(); //���Ӹ��� ȭ�� ���
int SelectMenu(); //���ӽ���, ����, �������� �޴��� ������ �� ����. ���ϰ��� ���� 0, 1, 2
void help(); //���� ���