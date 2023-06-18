#include"script.h"
#pragma warning(disable:4996)

SCRIPT* script = NULL;
static SCRIPT* scriptLast = NULL;
void getScript(int stageNum) {
	FILE* fscript = NULL;
	char str[301];
	char* name;
	char* text;
	switch (stageNum) {
	case 0:
		fscript = fopen("script/prologText.txt", "r");
		break;
	case 1:
		fscript = fopen("script/stage1Text.txt", "r");
		break;
	case 2:
		fscript = fopen("script/stage2Text.txt", "r");
		break;
	case 3:
		fscript = fopen("script/stage3Text.txt", "r");
		break;
	case 4:
		fscript = fopen("script/stage4Text.txt", "r");
		break;
	case 5:
		fscript = fopen("script/endingLose.txt", "r");
		break;
	case 6:
		fscript = fopen("script/endingWin.txt", "r");
		break;
	default:
		break;
	}
	if (fscript != NULL) {
		while (fgets(str, sizeof(str), fscript) != NULL) {
			name = strtok(str, ":");
			text = strtok(NULL, "");
			if (name != NULL && text != NULL)
				putScriptQueue(name, text);
		}
		fclose(fscript);
	}
}
SCRIPT* getScriptNode(char* name, char* text) {
	SCRIPT* node;

	node = (SCRIPT*)malloc(sizeof(SCRIPT));
	if (node == NULL) exit(-1);

	strcpy(node->name, name);
	strcpy(node->text, text);
	node->next = NULL;

	return node;
}
void putScriptQueue(char* name, char* text) {
	SCRIPT* node = getScriptNode(name, text);

	if (script == NULL) {
		script = node;
		scriptLast = script;
	}
	else {
		scriptLast->next = node;
		scriptLast = node;
	}
}
void printScriptQueue() {
	SCRIPT* tmp;
	char* pch;
	int i, j;
	printTextAlign();
	while (script != NULL) {
		clearScript();
		tmp = script->next;
		SetCurrentCursorPos(SCRIPT_POS_X + 1, SCRIPT_POS_Y);
		printf("%s", script->name);
		if (strlen(script->text) > SCRIPT_X - 1) {
			for (pch = script->text, j = 0; *pch != '\0'; pch++, j++) {
				SetCurrentCursorPos(SCRIPT_POS_X + 1, SCRIPT_POS_Y + 1 + j);
				for (i = 0; i < SCRIPT_X - 2 && *pch != '\0'; i++, pch++) {
					printf("%c", *pch);
				}
				pch--;
			}
		}
		else {
			SetCurrentCursorPos(SCRIPT_POS_X + 1, SCRIPT_POS_Y + 1);
			printf("%s", script->text);
		}
		script = tmp;
		getch();
	}
}
void clearScript() {
	int i, j;
	for (i = 0; i < SCRIPT_Y; i++) {
		for (j = 1; j < SCRIPT_X - 1; j++) {
			SetCurrentCursorPos(SCRIPT_POS_X + j, SCRIPT_POS_Y + i);
			printf(" ");
		}
	}
}
void printTextAlign() {
	int i;
	SetCurrentCursorPos(SCRIPT_POS_X - 1, SCRIPT_POS_Y - 1);
	printf("¦£");
	for (i = 0; i < SCRIPT_X; i++)
		printf("¦¡");
	printf("¦¤");
	for (i = 0; i < SCRIPT_Y; i++) {
		SetCurrentCursorPos(SCRIPT_POS_X - 1, SCRIPT_POS_Y + i);
		printf("¦¢");
		SetCurrentCursorPos(SCRIPT_POS_X + SCRIPT_X, SCRIPT_POS_Y + i);
		printf("¦¢");
	}
	SetCurrentCursorPos(SCRIPT_POS_X - 1, SCRIPT_POS_Y + SCRIPT_Y);
	printf("¦¦");
	for (i = 0; i < SCRIPT_X; i++)
		printf("¦¡");
	printf("¦¥");
}