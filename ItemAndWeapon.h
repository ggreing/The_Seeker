#pragma once
#include "System.h"
#include <Windows.h>

// �ѽ�� ����
typedef struct GUN {
	int shootingRange;
	COORD arriveBulletPos;		// �Ѿ��� �����ؾ��ϴ� ��ġ
	COORD currentBulletPos;		// ���ư��� �Ѿ��� �� ��ġ
	int shotOrNot;						// �� �߻� ����
	int currentDirect;					// �� ��� ����
}GUN;

extern GUN gun;

// ������ ������ ����
typedef struct ROCK {
	COORD arriveRockPos;		//  �����̰� �����ؾ��ϴ� ��ġ
	COORD currentRockPos;		//  ������ ������ �� ��ġ
	int throwOrNot;					//  ������ ��ô ����
	int currentDirect;					//  ������ ��� ����
	int distance;						//  ������-�� ���� �Ÿ�
	int showRange;					//  �Ÿ��� ���� �ֺ� �������� ����
}ROCK;

extern ROCK rock;

// functions
void initGunInfo(void);
void initRockInfo(void);
COORD moveByDirection(int currentDirect);	// ���ڷ� ���� ���⿡ ���� ������/������ x,y��ǥ ��ȭ�� ��ȯ
void shotGun(void);		// ���� ��� - ź�ǰ� ���ư��� ���ߴ� ��ġ ���� ����
int showBullet(void);	// shotGun���� ����� ��ġ���� ź�ǰ� �����̴� ���� ������
void useItemRock(void);	// ������ ������ ���
int showRock(void);	// ������ �������� ���ư��� ���� ������
void useItemPortion(void);	// ���� ������ ���