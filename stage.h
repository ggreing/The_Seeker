#pragma once
#include "interface.h"
#include "Player.h"
#include "System.h"
#include <stdio.h>

extern char STAGE[STAGE_Y][STAGE_X / 2];
void GetStageInfor(int StageNum); //���� ������� StageNum�� �ش��ϴ� �������� ������ �о� STAGE�� ����.
void printStage(); //�������� ��ü�� ����ϴ� �Լ�
void showStage(int stageObject, int posX, int posY); //posX, posY�� stageObject�� ����ϴ� �Լ�.
void PrintUI(); //UI�����
void StageInforInit(int stageNum); //��������, �÷��̾�, ���� �� ���� �ʱ�ȭ
