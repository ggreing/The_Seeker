#include "System.h"

CRITICAL_SECTION cs;

COORD GetCurrentCursorPos(void)
{
	COORD curPoint;
	CONSOLE_SCREEN_BUFFER_INFO curInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curPoint.X = curInfo.dwCursorPosition.X;
	curPoint.Y = curInfo.dwCursorPosition.Y;

	return curPoint;
}
void RemoveCursor(void)
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}
void SetCurrentCursorPos(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void ProcessKeyInput() {
	int key;

	if (_kbhit() != 0) {
		key = _getch();
		switch (key) {
		case LEFT:
			playerMove(LEFT);
			break;
		case RIGHT:
			playerMove(RIGHT);
			break;
		case UP:
			playerMove(UP);
			break;
		case DOWN:
			playerMove(DOWN);
			break;
		case ATTACK:
			shotGun();
			break;
		case ITEM_INPUT_2:
			useItemPortion();
			break;
		case ITEM_INPUT_1:
			useItemRock();
			break;
		}
	}
}

int DetectCollision(int posX, int posY) {
	return STAGE[posY][posX / 2];
}

void showSoundRange(COORD curPos, int objNum, int range) {
	int posX = curPos.X / 2;
	int posY = curPos.Y;

	InitializeCriticalSection(&cs);

	for (posX = curPos.X / 2; posX >= 0 && posX > curPos.X / 2 - range; posX--) {
		for (posY = curPos.Y; posY >= 0 && posY > curPos.Y - range; posY--) {
			if (posX == curPos.X / 2 && posY == curPos.Y) continue;
			showStage(STAGE[posY][posX], posX * 2, posY);
			if (STAGE[posY][posX] == WALL) break;
		}
		for (posY = curPos.Y; posY < STAGE_Y && posY < curPos.Y + range; posY++) {
			if (posX == curPos.X / 2 && posY == curPos.Y) continue;
			showStage(STAGE[posY][posX], posX * 2, posY);
			if (STAGE[posY][posX] == WALL) break;
		}
		if (STAGE[curPos.Y][posX] == WALL) break;
	}
	for (posX = curPos.X / 2; posX < STAGE_X / 2 && posX < curPos.X / 2 + range; posX++) {
		for (posY = curPos.Y; posY >= 0 && posY > curPos.Y - range; posY--) {
			if (posX == curPos.X / 2 && posY == curPos.Y) continue;
			showStage(STAGE[posY][posX], posX * 2, posY);
			if (STAGE[posY][posX] == WALL) break;
		}
		for (posY = curPos.Y; posY < STAGE_Y && posY < curPos.Y + range; posY++) {
			if (posX == curPos.X / 2 && posY == curPos.Y) continue;
			showStage(STAGE[posY][posX], posX * 2, posY);
			if (STAGE[posY][posX] == WALL) break;
		}
		if (STAGE[curPos.Y][posX] == WALL) break;
	}
	for (posY = curPos.Y; posY >= 0 && posY > curPos.Y - range; posY--) {
		for (posX = curPos.X / 2; posX >= 0 && posX > curPos.X / 2 - range; posX--) {
			if (posX == curPos.X / 2 && posY == curPos.Y) continue;
			showStage(STAGE[posY][posX], posX * 2, posY);
			if (STAGE[posY][posX] == WALL) break;
		}
		for (posX = curPos.X / 2; posX < STAGE_X / 2 && posX < curPos.X / 2 + range; posX++) {
			if (posX == curPos.X / 2 && posY == curPos.Y) continue;
			showStage(STAGE[posY][posX], posX * 2, posY);
			if (STAGE[posY][posX] == WALL) break;
		}
		if (STAGE[posY][curPos.X / 2] == WALL) break;
	}
	for (posY = curPos.Y; posY < STAGE_Y && posY < curPos.Y + range; posY++) {
		for (posX = curPos.X / 2; posX >= 0 && posX > curPos.X / 2 - range; posX--) {
			if (posX == curPos.X / 2 && posY == curPos.Y) continue;
			showStage(STAGE[posY][posX], posX * 2, posY);
			if (STAGE[posY][posX] == WALL) break;
		}
		for (posX = curPos.X / 2; posX < STAGE_X / 2 && posX < curPos.X / 2 + range; posX++) {
			if (posX == curPos.X / 2 && posY == curPos.Y) continue;
			showStage(STAGE[posY][posX], posX * 2, posY);
			if (STAGE[posY][posX] == WALL) break;
		}
		if (STAGE[posY][curPos.X / 2] == WALL) break;
	}
	LeaveCriticalSection(&cs);
}