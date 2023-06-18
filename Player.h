#pragma once
#include<Windows.h>
#include"System.h"

typedef struct PLAYER {
	int life;
	int item_rock;
	int item_portion;
	int weapon;
	int direction;
	int stageKey;
	COORD playerPos;
} PLAYER;

extern PLAYER player;

// player
void playerInfoInit(int life, int item_rock, int item_portion, int weapon, int direction); //player �Ķ���� �ʱ�ȭ
void playerPosInit(int playerPosX, int playerPosY); //player�� ��ġ ���� �ʱ�ȭ
int playerShiftRight(void); //player�� �浹�˻� �� ���������� ������. playerMove ���� �޼ҵ�
int playerShiftLeft(void); //player�� �浹�˻� �� �������� ������. playerMove ���� �޼ҵ�
int playerShiftUp(void); //player�� �浹�˻� �� ���� ������. playerMove ���� �޼ҵ�
int playerShiftDown(void); //player�� �浹�˻� �� �Ʒ��� ������. playerMove ���� �޼ҵ�
void ShowPlayer(); //player�� ĳ���͸� �÷��̾ ��ġ�� ��ǥ�� �����
void DeletePlayer(); //player�� ĳ���͸� �÷��̾ ��ġ�� ��ǥ���� ������.
void playerMove(int direction); //player �̵� �Լ�. player �̵� �� ������, ���� ȹ��, ���Ϳ� ���� ������ �Դ� ��ɰ� ����.
int isPlayerDead(); //player�� �������� 0�� ��� 1 ��ȯ, �̿ܿ� ��� 0 ��ȯ
int isPlayerHasKey(); //player�� key�� ������ ������ 1 ��ȯ, �̿ܿ� ��� 0 ��ȯ