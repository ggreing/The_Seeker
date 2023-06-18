#include "Sound.h"

float volume = 0.5;


void SoundInit(void) {
	FMOD_System_Create(&g_System);
	FMOD_System_Init(g_System, 15, FMOD_INIT_NORMAL, NULL); //최대 10개의 소리재생가능

	//사운드 생성 -주석 처리된 항목들은 추가할 예정
	FMOD_System_CreateSound(g_System, "sound/walking.wav", FMOD_DEFAULT, 0, &g_Sound[0]);

	FMOD_System_CreateSound(g_System, "sound/getItem1.wav", FMOD_DEFAULT, 0, &g_Sound[1]);
	//FMOD_System_CreateSound(g_System, "sound/getItem2.wav", FMOD_DEFAULT, 0, &g_Sound[2]);
	FMOD_System_CreateSound(g_System, "sound/getGun.wav", FMOD_DEFAULT, 0, &g_Sound[3]);
	FMOD_System_CreateSound(g_System, "sound/getKey.mp3", FMOD_DEFAULT, 0, &g_Sound[4]);

	//FMOD_System_CreateSound(g_System, "sound/useItem1.mp3", FMOD_DEFAULT, 0, &g_Sound[5]);
	//FMOD_System_CreateSound(g_System, "sound/useItem2.mp3", FMOD_DEFAULT, 0, &g_Sound[6]);
	//FMOD_System_CreateSound(g_System, "sound/useGun1.wav", FMOD_DEFAULT, 0, &g_Sound[7]);
	FMOD_System_CreateSound(g_System, "sound/useGun2.wav", FMOD_DEFAULT, 0, &g_Sound[8]);
	FMOD_System_CreateSound(g_System, "sound/useKey.mp3", FMOD_DEFAULT, 0, &g_Sound[9]);

	FMOD_System_CreateSound(g_System, "sound/damage.mp3", FMOD_DEFAULT, 0, &g_Sound[10]);
	FMOD_System_CreateSound(g_System, "sound/gameover.mp3", FMOD_DEFAULT, 0, &g_Sound[11]);
	FMOD_System_CreateSound(g_System, "sound/main.mp3", FMOD_LOOP_NORMAL, 0, &g_Sound[12]);
	FMOD_System_CreateSound(g_System, "sound/selectUI.wav", FMOD_DEFAULT, 0, &g_Sound[13]);
}

void StopSound(int n) {
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
}