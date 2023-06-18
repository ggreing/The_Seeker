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
void FindMonster(void); //�ֺ��� ���Ͱ� �ִ� ���, �Ÿ������� �ٸ� ������ �Ҹ� ���
COORD SoundPoint(void);

FMOD_SYSTEM* g_System;
FMOD_SOUND* g_Sound[15];
FMOD_CHANNEL* channel[15];

FMOD_BOOL IsPlaying;

COORD soundPos;