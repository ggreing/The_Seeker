#pragma once
#include <fmod.h>
#include<stdio.h>
#include<Windows.h>

void SoundInit(void);
void StopSound(void);
void VolumeSetSound(int n);
void SoundUpdate(void);
void VolumeCtrl(void);
void Sound_Play(int n);

FMOD_SYSTEM* g_System;
FMOD_SOUND* g_Sound[15];
FMOD_CHANNEL* channel[15];

FMOD_BOOL IsPlaying;