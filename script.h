#pragma once
#include "stage.h"

typedef struct SCRIPT {
	char name[21];
	char text[201];
	struct SCRIPT* next;
} SCRIPT;

extern SCRIPT* script;

void getScript(int stageNum); //�������� ��ȭ ������ �о� ��������script�� queue���·� ������
SCRIPT* getScriptNode(char* name, char* text); //name�� text������ ����ִ� SCRIPT��带 ��ȯ
void putScriptQueue(char* name, char* text); //script queue�� name�� text�� ����ִ� SCRIPT��带 �߰���
void printScriptQueue(); //script queue�� ����� ��ȭ������ ���� �����
void clearScript(); //��ȭâ�� û����
void printTextAlign(); //��ȭâ�� �׵θ� ���