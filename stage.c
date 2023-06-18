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
	printf("------라이프------\n");
	SetCurrentCursorPos(GBOARD_POS_X, posY);
	for (i = 0; i < player.life; i++) {
		printf("♥");
	}
	for (; i < MAX_LIFE; i++) {
		printf("  ");
	}

	posY += 3;
	SetCurrentCursorPos(GBOARD_POS_X, posY++);
	printf("--아이템 보유 현황--\n");
	SetCurrentCursorPos(GBOARD_POS_X, posY++);
	printf(" 돌멩이 : %d       \n", player.item_rock);
	SetCurrentCursorPos(GBOARD_POS_X, posY++);
	printf("    포션 : %d         \n", player.item_portion);
	SetCurrentCursorPos(GBOARD_POS_X, posY++);
	printf("    탄피 : %d         \n", player.weapon);
	SetCurrentCursorPos(GBOARD_POS_X, posY++);
	printf("  보유 열쇠 : %d      \n", player.stageKey);
	
	posY += 2;
	SetCurrentCursorPos(GBOARD_POS_X, posY++);
	printf("----아이콘 설명----\n");
	SetCurrentCursorPos(GBOARD_POS_X, posY++);
	printf("   ○: 돌멩이\n");
	SetCurrentCursorPos(GBOARD_POS_X, posY++);
	printf("   ♥: 포션 \n");
	SetCurrentCursorPos(GBOARD_POS_X, posY++);
	printf("  ⅹ: 탄피 \n");
	SetCurrentCursorPos(GBOARD_POS_X, posY++);
	printf("   § : 몬스터\n");
	SetCurrentCursorPos(GBOARD_POS_X, posY++);
	printf("  ⓝ: NPC\n");
	SetCurrentCursorPos(GBOARD_POS_X, posY++);
	printf("  ＊: 열쇠\n");
	SetCurrentCursorPos(GBOARD_POS_X, posY++);
	printf("  ★: 출구\n");
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

void clearScreen() {
	int i, j;
	SetCurrentCursorPos(STAGE_POS_X, STAGE_POS_Y);
	for (i = 0; i < STAGE_Y; i++) {
		for (j = 0; j < 65; j++)	// 초기 콘솔창 x축 크기 값의 절반만큼 반복
			printf("  ");
		printf("\n");
	}
}
void GameOver() {
	FILE* fstage = NULL;
	char tmp;
	int i, j;
	Sound_Play(GAMEOVER);
	fstage = fopen("gameover.txt", "r");
	if (fstage != NULL) {
		for (i = 0; i < STAGE_Y; i++) {
			SetCurrentCursorPos(0, i);
			for (j = 0; j < STAGE_X / 2; j++) {
				tmp = fgetc(fstage);
				switch (tmp) {
				case '0':
					printf("  ");
					break;
				case '1':
					printf("■");
					break;
				}
			}
			fgetc(fstage);
		}
	}
	SetCurrentCursorPos(36, 33);
	for (i = 6; i > 0; i--) {
		printf("%d초 뒤에 다시 시작합니다.", i);
		Sleep(1000);
		SetCurrentCursorPos(36, 33);
		printf("                          ");
		SetCurrentCursorPos(36, 33);
	}
	clearStage();
}
void GameStart() {
	FILE* fstage = NULL;
	char tmp;
	int i, j;
	int num;
	Sound_Play(12);
	do {
		fstage = fopen("gamestart.txt", "r");
		if (fstage != NULL) {
			for (i = 0; i < 41; i++) {
				SetCurrentCursorPos(0, i);
				for (j = 0; j < 65; j++) {
					tmp = fgetc(fstage);
					switch (tmp) {
					case '0':
						printf("  ");
						break;
					case '1':
						printf("┌");
						break;
					case '2':
						printf("┐");
						break;
					case '3':
						printf("└");
						break;
					case '4':
						printf("┘");
						break;
					case '5':
						printf("──");
						break;
					case '6':
						printf("│");
						break;
					case '7':
						printf("■");
						break;
					}
				}
				fgetc(fstage);
			}
		}
		while (1) {
			num = SelectMenu();
			if (num == 0) {
				StopSound(MAIN);
				break;
			}
			else if (num == 1) {
				help();
				break;
			}
			else {
				exit(0);
			}
		}
	} while (num == 1);
	clearScreen();
}
int SelectMenu() {
	int key;
	int num = 0;
	COORD curPos;
	SetCurrentCursorPos(STAGE_POS_X + 58, STAGE_POS_Y + 25);
	printf("◆ 게임시작");
	SetCurrentCursorPos(STAGE_POS_X + 58, STAGE_POS_Y + 27);
	printf("◇ 도움말");
	SetCurrentCursorPos(STAGE_POS_X + 58, STAGE_POS_Y + 29);
	printf("◇ 게임종료");
	SetCurrentCursorPos(STAGE_POS_X + 70, STAGE_POS_Y + 25);
	printf("<<");
	while (1) {
		Sleep(100);
		if (_kbhit() != 0) {
			key = _getch();
			switch (key) {
			case UP:
				if (num == 0) {
					break;
				}
				else {
					curPos = GetCurrentCursorPos();
					SetCurrentCursorPos(curPos.X - 2, curPos.Y);
					printf("  ");
					SetCurrentCursorPos(curPos.X - 14, curPos.Y);
					printf("◇");
					SetCurrentCursorPos(curPos.X - 14, curPos.Y - 2);
					printf("◆");
					SetCurrentCursorPos(curPos.X - 2, curPos.Y - 2);
					printf("<<");
					Sound_Play(13);
					num--;
					break;
				}
			case DOWN:
				if (num == 2) {
					break;
				}
				else {
					curPos = GetCurrentCursorPos();
					SetCurrentCursorPos(curPos.X - 2, curPos.Y);
					printf("  ");
					SetCurrentCursorPos(curPos.X - 14, curPos.Y);
					printf("◇");
					SetCurrentCursorPos(curPos.X - 14, curPos.Y + 2);
					printf("◆");
					SetCurrentCursorPos(curPos.X - 2, curPos.Y + 2);
					printf("<<");
					Sound_Play(13);
					num++;
					break;
				}
				break;
			case ENTER:
				curPos = GetCurrentCursorPos();
				SetCurrentCursorPos(curPos.X - 2, curPos.Y);
				printf("  ");
				Sound_Play(13);
				return num;
			}
		}
	}
}

void help() {
	int i, j, key;
	FILE* f = NULL;
	char tmp[100];
	clearScreen();
	f = fopen("help.txt", "r");
	if (f != NULL) {
		for (i = 0; i < 40; i++) {
			SetCurrentCursorPos(0, i);
			fgets(tmp, sizeof(tmp), f);
			printf("%s\n", tmp);
		}
	}
	fclose(f);
	while (1) {
		Sleep(100);
		key = _getch();
		if (key == ENTER) {
			clearScreen();
			return;
		}
	}
}