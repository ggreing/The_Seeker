#pragma once
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ENTER 13

#define SPACE 32
#define ITEM_INPUT_1 49
#define ITEM_INPUT_2 50
#define ATTACK 97
#define INTERACT 102

#define EMPTY_SPACE 0
#define WALL 1
#define ITEM_1 2 
#define ITEM_2 3
#define WEAPON 4
#define MONSTER 5
#define NPC 6
#define PC 7
#define KEY 8
#define EXIT 9

#define STAGE_X 100
#define STAGE_Y 41
#define GBOARD_X 20
#define GBOARD_Y 41
#define SCRIPT_X 60
#define SCRIPT_Y 10

#define STAGE_POS_X 0
#define STAGE_POS_Y 0
#define GBOARD_POS_X STAGE_POS_X + STAGE_X + 3
#define GBOARD_POS_Y STAGE_POS_Y
#define SCRIPT_POS_X STAGE_POS_X + (STAGE_X - SCRIPT_X) / 2
#define SCRIPT_POS_Y STAGE_POS_Y + (STAGE_Y - SCRIPT_Y) / 2

#define MAX_LIFE 5			// ������ �ִ� ���� ���� ��
#define INIT_WEAPON 0	// ó�� ������ �� ������ ź�� ��
#define MAX_ROCK_SHOWRANGE 5

#define LIGHTNING 10

//��� ���� �Ҹ� ���
#define GAME 0			// ���� ��� ����
#define GET_ITEM1 1		// ������ ȹ��
#define GET_ITEM2 2		// ���� ȹ��
#define GET_GUN 3		// ź�� ȹ��
#define GET_KEY 4		// ���� ȹ��
#define MONSTER 5		// ���� �Ҹ�
#define USE_ITEM1 6		// ������ ���
#define	USE_ITEM2 7		// ���� ���
#define USE_GUN1 8		// ź�� ���(ź�� �̺��� ��)
#define USE_GUN2 9		// ź�� ���(ź�� ���� ��)
#define USE_KEY 10		// ���� ���
#define DAMAGE 11		// �÷��̾ �������� ����
#define GAMEOVER 12		// ���ӿ��� ȿ����
#define SELECT_MANU 13  // ����ȭ�� �޴� ȿ����

extern int isCleared;