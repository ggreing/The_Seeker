#include"stage.h"
#pragma warning(disable:4996)

int stageNum = 1;
char STAGE[STAGE_Y][STAGE_X / 2];
void GetStageInfor(int StageNum) {
	FILE* fstage = NULL;
	char tmp;
	int i, j;
	switch (StageNum) {
	case 1:
		fstage = fopen("stage/stage1.txt", "r");
		break;
	case 2:
		fstage = fopen("stage/stage2.txt", "r");
		break;
	case 3:
		fstage = fopen("stage/stage3.txt", "r");
		break;
	case 4:
		fstage = fopen("stage/stage4.txt", "r");
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
					playerPosInit(i * 2, j);
					STAGE[i][i] = EMPTY_SPACE;
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
			showStage(STAGE[i][j], i, j);
		}
		printf("\n");
	}
}
void showStage(int stageObject, int posX, int posY) {
	SetCurrentCursorPos(posX, posY);
	switch (stageObject) {
	case EMPTY_SPACE:
		printf("  ");
		break;
	case WALL:
		printf("■");
		break;
	case ITEM_1:
		printf("○");
		break;
	case ITEM_2:
		printf("♥");
		break;
	case WEAPON:
		printf("ⅹ");
		break;
	case MONSTER:
		printf("§");
		break;
	case NPC:
		printf("ⓝ");		// 삭제 예정
		break;
	case PC:
		//printf("◆");	
		break;
	case KEY:
		printf("＊");
		break;
	case EXIT:
		printf("★");
		break;
	default:
		break;
	}
}
void PrintUI() {

	// 기호 설명, 라이프 개수, 아이템 보유 현황

	int posY = GBOARD_POS_Y;
	int i;

	SetCurrentCursorPos(GBOARD_POS_X, posY++);
	printf("------라이프------");
	SetCurrentCursorPos(GBOARD_POS_X, posY);
	for (i = 0; i < player.life; i++) {
		printf("♥");
	}
	for (; i < MAX_LIFE; i++) {
		printf("  ");
	}

	posY += 3;
	SetCurrentCursorPos(GBOARD_POS_X, posY++);
	printf("--아이템 보유 현황--");
	SetCurrentCursorPos(GBOARD_POS_X, posY++);
	printf("돌멩이:% d", player.item_rock);
	SetCurrentCursorPos(GBOARD_POS_X, posY++);
	printf("포션:% d", player.item_portion);
	SetCurrentCursorPos(GBOARD_POS_X, posY++);
	printf("무기:% d", player.weapon);
	SetCurrentCursorPos(GBOARD_POS_X, posY++);
	printf("보유 열쇠:% d", player.stageKey);

	posY += 2;
	SetCurrentCursorPos(GBOARD_POS_X, posY++);
	printf("----아이콘 설명----");
	SetCurrentCursorPos(GBOARD_POS_X, posY++);
	printf("○: 돌멩이");
	SetCurrentCursorPos(GBOARD_POS_X, posY++);
	printf("♥: 포션");
	SetCurrentCursorPos(GBOARD_POS_X, posY++);
	printf("ⅹ: 탄피");
	SetCurrentCursorPos(GBOARD_POS_X, posY++);
	printf("§: 몬스터");
	SetCurrentCursorPos(GBOARD_POS_X, posY++);
	printf("ⓝ: NPC");
	SetCurrentCursorPos(GBOARD_POS_X, posY++);
	printf("＊: 열쇠");
	SetCurrentCursorPos(GBOARD_POS_X, posY++);
	printf("★: 출구");
}
void StageInforInit(int stageNum) {
	clearStage();
	GetStageInfor(stageNum);
	playerInfoInit(MAX_LIFE, 0, 0, INIT_WEAPON, RIGHT);
	initGunInfo();
}
void clearStage() {
	int i, j;
	SetCurrentCursorPos(STAGE_POS_X, STAGE_POS_Y);
	for (i = 0; i < STAGE_Y; i++) {
		for (j = 0; j < STAGE_X / 2; j++)
			printf("  ");
		printf("\n");
	}
}