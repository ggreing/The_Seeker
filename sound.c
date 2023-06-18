#include "Sound.h"
float volume = 0.5;
float monVol;
IsPlaying = FALSE;

void SoundInit(void) {
	soundPos.X = 0;
	soundPos.Y = 0;

	FMOD_System_Create(&g_System);
	FMOD_System_Init(g_System, 15, FMOD_INIT_NORMAL, NULL);

	FMOD_System_CreateSound(g_System, "sound/game.mp3", FMOD_LOOP_NORMAL, 0, &g_Sound[0]);

	FMOD_System_CreateSound(g_System, "sound/getItem1.wav", FMOD_DEFAULT, 0, &g_Sound[1]);
	FMOD_System_CreateSound(g_System, "sound/getItem2.wav", FMOD_DEFAULT, 0, &g_Sound[2]);
	FMOD_System_CreateSound(g_System, "sound/getGun.wav", FMOD_DEFAULT, 0, &g_Sound[3]);
	FMOD_System_CreateSound(g_System, "sound/getKey.mp3", FMOD_DEFAULT, 0, &g_Sound[4]);

	FMOD_System_CreateSound(g_System, "sound/monster.mp3", FMOD_LOOP_NORMAL, 0, &g_Sound[5]);
	FMOD_System_CreateSound(g_System, "sound/useItem1.wav", FMOD_DEFAULT, 0, &g_Sound[6]);
	FMOD_System_CreateSound(g_System, "sound/useItem2.wav", FMOD_DEFAULT, 0, &g_Sound[7]);
	FMOD_System_CreateSound(g_System, "sound/useGun1.wav", FMOD_DEFAULT, 0, &g_Sound[8]);
	FMOD_System_CreateSound(g_System, "sound/useGun2.wav", FMOD_DEFAULT, 0, &g_Sound[9]);
	FMOD_System_CreateSound(g_System, "sound/useKey.mp3", FMOD_DEFAULT, 0, &g_Sound[10]);

	FMOD_System_CreateSound(g_System, "sound/damage.mp3", FMOD_DEFAULT, 0, &g_Sound[11]);
	FMOD_System_CreateSound(g_System, "sound/gameover.mp3", FMOD_DEFAULT, 0, &g_Sound[12]);
	FMOD_System_CreateSound(g_System, "sound/selectUI.wav", FMOD_DEFAULT, 0, &g_Sound[13]);
}

void StopSound(int n) {
	if (n == MONSTER) {
		IsPlaying = FALSE;
	}
	FMOD_Channel_Stop(channel[n]);
}

void VolumeSetSound(int n) {
	FMOD_Channel_SetVolume(channel[n], volume);
}

void SoundUpdate(void) {
	if (IsPlaying == 1) {
		FMOD_System_Update(g_System);
	}
}

void VolumeCtrl(void) {

}

void Sound_Play(int n) {
	FMOD_System_PlaySound(g_System, g_Sound[n], 0, 0, &channel[n]);
	if (n == GAME) {
		FMOD_Channel_SetVolume(channel[GAME], 0.2);
	}
	//플레이어가 걷거나 총을 사용하는 경우엔 플레이어의 위치를 소리가 난 지점으로 저장
	if (n == USE_GUN2) {
		soundPos = player.playerPos;
	}
	// 돌멩이 아이템을 사용하는 경우 돌멩이가 벽에 부딪히는 지점을 소리가 난 지점으로 저장
	else if (n == USE_ITEM1) {
		soundPos = rock.arriveRockPos;
	}
}
void FindMonster(void) {
	int x = player.playerPos.X / 2;
	int y = player.playerPos.Y;
	int i, j;
	int flag = 0;
	for (i = y - 7; i < y + 8; i++) {
		if (i < 0 || i > 40) {
			continue;
		}
		if (i == y - 7 || i == y + 7) {
			for (j = x - 7; j < x + 8; j++) {
				if (j < 0 || j > 50) {
					continue;
				}
				if (STAGE[i][j] == MONSTER) {
					FMOD_Channel_SetVolume(channel[MONSTER], 0.05);
					monVol = 0.05;
					flag = 1;
				}
			}
		}
		else {
			for (j = x - 7; j < x + 8; j += 14) {
				if (j < 0 || j > 50) {
					continue;
				}
				if (STAGE[i][j] == MONSTER) {
					FMOD_Channel_SetVolume(channel[MONSTER], 0.05);
					monVol = 0.05;
					flag = 1;
				}
			}
		}
	}
	for (i = y - 6; i < y + 7; i++) {
		if (i < 0 || i > 40) {
			continue;
		}
		if (i == y - 6 || i == y + 6) {
			for (j = x - 6; j < x + 7; j++) {
				if (j < 0 || j > 50) {
					continue;
				}
				if (STAGE[i][j] == MONSTER) {
					FMOD_Channel_SetVolume(channel[MONSTER], 0.1);
					monVol = 0.1;
					flag = 1;
				}
			}
		}
		else {
			for (j = x - 6; j < x + 7; j += 12) {
				if (j < 0 || j > 50) {
					continue;
				}
				if (STAGE[i][j] == MONSTER) {
					FMOD_Channel_SetVolume(channel[MONSTER], 0.1);
					monVol = 0.1;
					flag = 1;
				}
			}
		}
	}
	for (i = y - 5; i < y + 6; i++) {
		if (i < 0 || i > 40) {
			continue;
		}
		if (i == y - 5 || i == y + 5) {
			for (j = x - 5; j < x + 6; j++) {
				if (j < 0 || j > 50) {
					continue;
				}
				if (STAGE[i][j] == MONSTER) {
					FMOD_Channel_SetVolume(channel[MONSTER], 0.15);
					monVol = 0.15;
					flag = 1;
				}
			}
		}
		else {
			for (j = x - 5; j < x + 6; j += 10) {
				if (j < 0 || j > 50) {
					continue;
				}
				if (STAGE[i][j] == MONSTER) {
					FMOD_Channel_SetVolume(channel[MONSTER], 0.15);
					monVol = 0.15;
					flag = 1;
				}
			}
		}
	}
	for (i = y - 4; i < y + 5; i++) {
		if (i < 0 || i > 40) {
			continue;
		}
		if (i == y - 4 || i == y + 4) {
			for (j = x - 4; j < x + 5; j++) {
				if (j < 0 || j > 50) {
					continue;
				}
				if (STAGE[i][j] == MONSTER) {
					FMOD_Channel_SetVolume(channel[MONSTER], 0.2);
					monVol = 0.2;
					flag = 1;
				}
			}
		}
		else {
			for (j = x - 4; j < x + 5; j += 8) {
				if (j < 0 || j > 50) {
					continue;
				}
				if (STAGE[i][j] == MONSTER) {
					FMOD_Channel_SetVolume(channel[MONSTER], 0.2);
					monVol = 0.2;
					flag = 1;
				}
			}
		}
	}
	for (i = y - 3; i < y + 4; i++) {
		if (i < 0 || i > 40) {
			continue;
		}
		if (i == y - 3 || i == y + 3) {
			for (j = x - 3; j < x + 4; j++) {
				if (j < 0 || j > 50) {
					continue;
				}
				if (STAGE[i][j] == MONSTER) {
					FMOD_Channel_SetVolume(channel[MONSTER], 0.25);
					monVol = 0.25;
					flag = 1;
				}
			}
		}
		else {
			for (j = x - 3; j < x + 4; j += 6) {
				if (j < 0 || j > 50) {
					continue;
				}
				if (STAGE[i][j] == MONSTER) {
					FMOD_Channel_SetVolume(channel[MONSTER], 0.25);
					monVol = 0.25;
					flag = 1;
				}
			}
		}
	}
	for (i = y - 2; i < y + 3; i++) {
		if (i < 0 || i > 40) {
			continue;
		}
		if (i == y - 2 || i == y + 2) {
			for (j = x - 2; j < x + 3; j++) {
				if (j < 0 || j > 50) {
					continue;
				}
				if (STAGE[i][j] == MONSTER) {
					FMOD_Channel_SetVolume(channel[MONSTER], 0.3);
					monVol = 0.3;
					flag = 1;
				}
			}
		}
		else {
			for (j = x - 2; j < x + 3; j += 4) {
				if (j < 0 || j > 50) {
					continue;
				}
				if (STAGE[i][j] == MONSTER) {
					FMOD_Channel_SetVolume(channel[MONSTER], 0.3);
					monVol = 0.3;
					flag = 1;
				}
			}
		}
	}

	for (i = y - 1; i < y + 2; i++) {
		if (i < 0 || i > 40) {
			continue;
		}
		if (i == y - 1 || i == y + 1) {
			for (j = x - 1; j < x + 2; j++) {
				if (j < 0 || j > 50) {
					continue;
				}
				if (STAGE[i][j] == MONSTER) {
					FMOD_Channel_SetVolume(channel[MONSTER], 0.35);
					monVol = 0.35;
					flag = 1;
				}
			}
		}
		else {
			for (j = x - 1; j < x + 2; j += 2) {
				if (j < 0 || j > 50) {
					continue;
				}
				if (STAGE[i][j] == MONSTER) {
					FMOD_Channel_SetVolume(channel[MONSTER], 0.35);
					monVol = 0.35;
					flag = 1;
				}
			}
		}
	}
	if (flag) {
		if (IsPlaying == FALSE) {
			Sound_Play(MONSTER);
			FMOD_Channel_SetVolume(channel[MONSTER], monVol);
			IsPlaying = TRUE;
		}
	}
	else {
		StopSound(MONSTER);
	}
}
COORD SoundPoint() {
	return soundPos;
}