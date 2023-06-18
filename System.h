#pragma once
#include <windows.h>

COORD GetCurrentCursorPos(void);
void RemoveCursor(void);
void SetCurrentCursorPos(int x, int y);