#pragma once
#include "interface.h"
#include "Player.h"
#include "System.h"
#include <stdio.h>

char STAGE[STAGE_Y][STAGE_X / 2];
void GetStageInfor(int StageNum) {
	FILE *fstage = NULL;
	char tmp;
	int i, j;
	switch (StageNum) {
	case 1:
		fstage = fopen("stage1.txt", "r");
		break;
	case 2:
		fstage = fopen("stage2.txt", "r");
		break;
	case 3:
		fstage = fopen("stage3.txt", "r");
		break;
	case 4:
		fstage = fopen("stage4.txt", "r");
		break;
	default:
		break;
	}
	if (fstage != NULL) {
		for (i = 0; i < STAGE_Y; i++) {
			for (j = 0; j < STAGE_X / 2; j++) {
				tmp = fgetc(fstage);
				switch (tmp) {
				case '0':
					STAGE[i][j] = EMPTY_SPACE;
					break;
				case '1':
					STAGE[i][j] = WALL;
					break;
				case '2':
					STAGE[i][j] = ITEM_1;
					break;
				case '3':
					STAGE[i][j] = ITEM_2;
					break;
				case '4':
					STAGE[i][j] = WEAPON;
					break;
				case '5':
					STAGE[i][j] = MONSTER;
					break;
				case '6':
					STAGE[i][j] = NPC;
					break;
				case '7':
					//STAGE[i][j] = PC;
					STAGE[i][i] = 0;
					break;
				case '8':
					STAGE[i][j] = KEY;
					break;
				case '9':
					STAGE[i][j] = EXIT;
					break;
				}
			}
			fgetc(fstage);
		}
	}
}
void printStage() {
	int i, j;
	for (i = 0; i < STAGE_Y; i++) {
		for (j = 0; j < STAGE_X / 2; j++) {
			switch (STAGE[i][j]) {
			case EMPTY_SPACE :
				printf("  ");
				break;
			case WALL:
				printf("��");
				break;
			case ITEM_1 :
				printf("��");
				break;
			case ITEM_2 :
				printf("��");
				break;
			case WEAPON :
				printf("��");
				break;
			case MONSTER :
				printf("��");
				break;
			case NPC :
				printf("��");		// ���� ����
				break;
			case PC :
				//printf("��");	
				break;
			case KEY :
				printf("��");
				break;
			case EXIT :
				printf("��");
				break;
			default :
				break;
			}
		}
		printf("\n");
	}
}
void PrintUI() {

	// ��ȣ ����, ������ ����, ������ ���� ��Ȳ

	int posY = GBOARD_POS_Y;
	
	SetCurrentCursorPos(GBOARD_POS_X, posY++);
	printf("------������------\n");
	SetCurrentCursorPos(GBOARD_POS_X, posY);
	for (int i = 0; i < pcLife; i++) {
		printf("��");
	}

	posY += 3;
	SetCurrentCursorPos(GBOARD_POS_X, posY++);
	printf("--������ ���� ��Ȳ--\n");
	SetCurrentCursorPos(GBOARD_POS_X, posY++);
	printf("������:% d\n", item_rock);
	SetCurrentCursorPos(GBOARD_POS_X, posY++);
	printf("����:% d\n", item_portion);

	posY += 2;
	SetCurrentCursorPos(GBOARD_POS_X, posY++);
	printf("----������ ����----\n");
	SetCurrentCursorPos(GBOARD_POS_X, posY++);
	printf("��: ������\n");
	SetCurrentCursorPos(GBOARD_POS_X, posY++);
	printf("��: ����\n");
	SetCurrentCursorPos(GBOARD_POS_X, posY++);
	printf("��: ź��\n");
	SetCurrentCursorPos(GBOARD_POS_X, posY++);
	printf("��: ����\n");
	SetCurrentCursorPos(GBOARD_POS_X, posY++);
	printf("��: NPC\n");
	SetCurrentCursorPos(GBOARD_POS_X, posY++);
	printf("��: ����\n");
	SetCurrentCursorPos(GBOARD_POS_X, posY++);
	printf("��: �ⱸ\n");
}