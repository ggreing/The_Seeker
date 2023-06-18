#include "ItemAndWeapon.h"
#include "Player.h"
#include <Windows.h>
#include <math.h>
#include "monster.h"
GUN gun;
ROCK rock;

void initGunInfo(void) {
	gun.shootingRange = 7;
	gun.shotOrNot = 0;
	gun.currentDirect = RIGHT;
}

void initRockInfo(void) {
	rock.throwOrNot = 0;
	rock.currentDirect = RIGHT;
	rock.distance = 0;
	rock.showRange = 0;
}

COORD moveByDirection(int currentDirect) {
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
	if (player.weapon == 0) {
		Sound_Play(USE_GUN1);
		return 0;		// 탄피가 없음
	}
	player.weapon--;							// 탄피 사용
	Sound_Play(USE_GUN2);

	gun.shotOrNot = 1;
	gun.currentDirect = player.direction;

	COORD curPos;
	curPos.X = player.playerPos.X;
	curPos.Y = player.playerPos.Y;
	COORD movePos = moveByDirection(gun.currentDirect);
	gun.currentBulletPos.X = player.playerPos.X + movePos.X;		// 날아감 보여줄 때 시작 위치
	gun.currentBulletPos.Y = player.playerPos.Y + movePos.Y;

	for (int i = 0; i < gun.shootingRange; i++) {
		if (DetectCollision(curPos.X + movePos.X, curPos.Y + movePos.Y) == WALL) {
			gun.arriveBulletPos.X = curPos.X;
			gun.arriveBulletPos.Y = curPos.Y;
			return;
		}
		if (DetectCollision(curPos.X + movePos.X, curPos.Y + movePos.Y) == MONSTER) {
			gun.arriveBulletPos.X = curPos.X + movePos.X;
			gun.arriveBulletPos.Y = curPos.Y + movePos.Y;
			return;
		}

		curPos.X = curPos.X + movePos.X;
		curPos.Y = curPos.Y + movePos.Y;

	}

	gun.arriveBulletPos.X = curPos.X;
	gun.arriveBulletPos.Y = curPos.Y;
	return;

}

int showBullet(void) {

	COORD movePos = moveByDirection(gun.currentDirect);

	if (gun.currentBulletPos.X == gun.arriveBulletPos.X + movePos.X && gun.currentBulletPos.Y == gun.arriveBulletPos.Y + movePos.Y) {
		// 몬스터를 만남
		if (STAGE[gun.arriveBulletPos.Y][gun.arriveBulletPos.X / 2] == MONSTER) {
			STAGE[gun.arriveBulletPos.Y][gun.arriveBulletPos.X / 2] = 0;

			SetCurrentCursorPos(gun.arriveBulletPos.X, gun.arriveBulletPos.Y);
			printf("※");		// BANG
			StopSound(MONSTER);
			Sleep(50);
			SetCurrentCursorPos(gun.arriveBulletPos.X, gun.arriveBulletPos.Y);
			printf("  ");
		}
		gun.shotOrNot = 0;
		return 0;
	}

	SetCurrentCursorPos(gun.currentBulletPos.X, gun.currentBulletPos.Y);
	printf("ⅹ");
	Sleep(100);
	SetCurrentCursorPos(gun.currentBulletPos.X, gun.currentBulletPos.Y);
	showStage(DetectCollision(gun.currentBulletPos.X, gun.currentBulletPos.Y), gun.currentBulletPos.X, gun.currentBulletPos.Y);

	gun.currentBulletPos.X += movePos.X;
	gun.currentBulletPos.Y += movePos.Y;

	return 1;

}

void useItemRock(void) {
	if (player.item_rock == 0) return;
	player.item_rock--;

	rock.throwOrNot = 1;
	rock.currentDirect = player.direction;
	rock.showRange = 0;

	COORD curPos;
	curPos.X = player.playerPos.X;
	curPos.Y = player.playerPos.Y;
	COORD movePos = moveByDirection(rock.currentDirect);
	rock.currentRockPos.X = player.playerPos.X + movePos.X;		// 날아감 보여줄 때 시작 위치
	rock.currentRockPos.Y = player.playerPos.Y + movePos.Y;

	while (1) {
		if (DetectCollision(curPos.X + movePos.X, curPos.Y + movePos.Y) == WALL) {

			rock.arriveRockPos.X = curPos.X;
			rock.arriveRockPos.Y = curPos.Y;

			// 거리 , 보이는 범위 계산
			if (movePos.Y == 0) {
				rock.distance = (int)sqrt(pow(rock.arriveRockPos.X - rock.currentRockPos.X, 2.0)) / 2;
			}
			else if (movePos.X == 0) {
				rock.distance = (int)sqrt(pow(rock.arriveRockPos.Y - rock.currentRockPos.Y, 2.0));
			}
			rock.showRange = MAX_ROCK_SHOWRANGE - (rock.distance / 3) + 2;
			if (rock.showRange > MAX_ROCK_SHOWRANGE) rock.showRange = MAX_ROCK_SHOWRANGE;

			return;
		}

		curPos.X = curPos.X + movePos.X;
		curPos.Y = curPos.Y + movePos.Y;

	}

	rock.arriveRockPos.X = curPos.X;
	rock.arriveRockPos.Y = curPos.Y;
}

int showRock(void) {
	COORD movePos = moveByDirection(rock.currentDirect);

	if (rock.currentRockPos.X == rock.arriveRockPos.X + movePos.X && rock.currentRockPos.Y == rock.arriveRockPos.Y + movePos.Y) {
		// 벽에 부딪힘
		showSoundRange(rock.arriveRockPos, ITEM_1, rock.showRange);
		rock.throwOrNot = 0;
		Sound_Play(USE_ITEM1);
		return 0;
	}

	SetCurrentCursorPos(rock.currentRockPos.X, rock.currentRockPos.Y);
	printf("ｏ");
	Sleep(70);
	SetCurrentCursorPos(rock.currentRockPos.X, rock.currentRockPos.Y);
	//showStage(DetectCollision(rock.currentRockPos.X, rock.currentRockPos.Y), rock.currentRockPos.X, rock.currentRockPos.Y);
	printf("  ");

	rock.currentRockPos.X += movePos.X;
	rock.currentRockPos.Y += movePos.Y;

	return 1;
}

void useItemPortion(void) {
	if (player.item_portion == 0) return;
	player.item_portion--;
	Sound_Play(USE_ITEM2);
	srand(time(NULL));
	int life = (unsigned int)rand() % 10;
	if (life < 6) player.life++;			// life +1 60%
	else if (life < 7) {
		player.life--;	// life -1 10%
		Sound_Play(DAMAGE);
	}
	else player.life += 2;				// life +2 30%

	if (player.life > MAX_LIFE) player.life = MAX_LIFE;

}