#pragma once
#include"Sound.h"
#include"interface.h"
#include"stage.h"
#include"Player.h"
#include<Windows.h>

COORD GetCurrentCursorPos(void); //Ŀ���� ���� ��ǥ ��ȯ
void RemoveCursor(void); //Ŀ���� �������� �ʰ� ��
void SetCurrentCursorPos(int x, int y); //���� Ŀ���� ��ǥ ����
void ProcessKeyInput(); //�÷��̾�κ��� Ű �Է��� ����
int DetectCollision(int posX, int posY); //posX�� posY�� �ִ� ������Ʈ�� � ������Ʈ�� �ε�ġ���� ��ȯ
void showSoundRange(COORD curPos, int objNum, int range); //curPos�� range��ŭ�� ������ ������.
