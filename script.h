#pragma once
#include "stage.h"

typedef struct SCRIPT {
	char name[21];
	char text[201];
	struct SCRIPT* next;
} SCRIPT;

extern SCRIPT* script;

void getScript(int stageNum); //스테이지 대화 내용을 읽어 전역변수script에 queue형태로 저장함
SCRIPT* getScriptNode(char* name, char* text); //name과 text내용을 담고있는 SCRIPT노드를 반환
void putScriptQueue(char* name, char* text); //script queue에 name과 text를 담고있는 SCRIPT노드를 추가함
void printScriptQueue(); //script queue에 저장된 대화내용을 전부 출력함
void clearScript(); //대화창을 청소함
void printTextAlign(); //대화창에 테두리 출력