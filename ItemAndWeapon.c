#include "ItemAndWeapon.h"
#include "Player.h"
#include <Windows.h>

currentDirect = RIGHT;
GUN gun;

void initGunInfo(void) {
	gun.shootingRange = 7;
	gun.shotOrNot = 0;
	gun.currentShotPos.X = 0;
	gun.currentShotPos.Y = 0;
	gun.bulletPos.X = 0;
	gun.bulletPos.Y = 0;

}

COORD moveByDirection(void) {
	COORD moveDirection;

	if (currentDirect == LEFT) {
		moveDirection.X = -2;
		moveDirection.Y = 0;
	}
	if (currentDirect == RIGHT) {
		moveDirection.X = 2;
		moveDirection.Y = 0;
	}
	if (currentDirect == UP) {
		moveDirection.X = 0;
		moveDirection.Y = -1;
	}
	if (currentDirect == DOWN) {
		moveDirection.X = 0;
		moveDirection.Y = 1;
	}

	return moveDirection;
}

void shotGun(void) {
	if (player.weapon == 0) return 0;		// 탄피가 없음
	player.weapon--;							// 탄피 사용

	gun.shotOrNot = 1;
	currentDirect = player.direction;

	COORD curPos;
	curPos.X = player.playerPos.X;
	curPos.Y = player.playerPos.Y;
	COORD movePos = moveByDirection();
	gun.bulletPos.X = player.playerPos.X + movePos.X;
	gun.bulletPos.Y = player.playerPos.Y + movePos.Y;

	for (int i = 0; i < gun.shootingRange; i++) {
		if (DetectCollision(curPos.X + movePos.X, curPos.Y + movePos.Y) == WALL) {
			gun.currentShotPos.X = curPos.X;
			gun.currentShotPos.Y = curPos.Y;
			return;
		}
		if (DetectCollision(curPos.X + movePos.X, curPos.Y + movePos.Y) == MONSTER) {
			gun.currentShotPos.X = curPos.X + movePos.X;
			gun.currentShotPos.Y = curPos.Y + movePos.Y;
			return;
		}

		curPos.X = curPos.X + movePos.X;
		curPos.Y = curPos.Y + movePos.Y;

	}

	gun.currentShotPos.X = curPos.X;
	gun.currentShotPos.Y = curPos.Y;
	return;

}

int showBullet(void) {

	COORD movePos = moveByDirection();

	if (gun.bulletPos.X == gun.currentShotPos.X + movePos.X && gun.bulletPos.Y == gun.currentShotPos.Y + movePos.Y) {
		// 몬스터를 만남
		if (STAGE[gun.currentShotPos.Y][gun.currentShotPos.X / 2] == MONSTER) {
			STAGE[gun.currentShotPos.Y][gun.currentShotPos.X / 2] = 0;
			SetCurrentCursorPos(gun.currentShotPos.X, gun.currentShotPos.Y);
			printf("※");		// BANG
		}
		gun.shotOrNot = 0;
		return 0;
	}

	SetCurrentCursorPos(gun.bulletPos.X, gun.bulletPos.Y);
	printf("ⅹ");
	Sleep(150);
	SetCurrentCursorPos(gun.bulletPos.X, gun.bulletPos.Y);
	showStage(DetectCollision(gun.bulletPos.X, gun.bulletPos.Y), gun.bulletPos.X, gun.bulletPos.Y);

	gun.bulletPos.X += movePos.X;
	gun.bulletPos.Y += movePos.Y;

	return 1;

}

/*
void useItemRock(void) {
	if (player.item_rock == 0) return;
	player.item_rock--;



}
*/

void useItemPortion(void) {
	if (player.item_portion == 0) return;

	srand(time(NULL));
	player.item_portion--;
	int life = (unsigned int)rand() % 10;
	if (life < 5) player.life++;		// life +1 50%
	if (life < 8) player.life--;		// life -1 30%
	else player.life += 2;			// life +2 20%

	if (player.life > MAX_LIFE) player.life = MAX_LIFE;

}