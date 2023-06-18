#pragma once
#include <fmod.h>
#include<stdio.h>
#include<Windows.h>
#include "stage.h"

void SoundInit(void);
void StopSound(int n);
void VolumeSetSound(int n);
void SoundUpdate(void);
void Sound_Play(int n);
void FindMonster(void); //주변에 몬스터가 있는 경우, 거리에따라 다른 볼륨의 소리 출력
COORD SoundPoint(void);

FMOD_SYSTEM* g_System;
FMOD_SOUND* g_Sound[15];
FMOD_CHANNEL* channel[15];

FMOD_BOOL IsPlaying;

COORD soundPos;