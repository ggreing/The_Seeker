#pragma once
#include "System.h"
#include <Windows.h>


// weapon&item
extern int currentDirect;				// ������/�� ��� ������ �÷��̾� ����
// �ѽ�� ����
typedef struct GUN {
	int shootingRange;
	COORD currentShotPos;	// �Ѿ��� �����ؾ��ϴ� ��ġ
	COORD bulletPos;			// ���ư��� �Ѿ��� �� ��ġ
	int shotOrNot;					// ���� ����� �Ƚ����
}GUN;

extern GUN gun;

// ������ ������ ����

// functions
COORD moveByDirection(void);	// �÷��̾� ���⿡ ���� ������/������ x,y��ǥ ��ȭ�� ��ȯ
void initGunInfo();
void shotGun(void);		// ���� ��� - ź�ǰ� ���ư��� ���ߴ� ��ġ ���� ����
int showBullet(void);	// shotGun���� ����� ��ġ���� ź�ǰ� �����̴� ���� ������
void useItemRock(void);	// ������ ������ ���
void useItemPortion(void);	// ���� ������ ���