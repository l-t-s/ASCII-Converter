#pragma once
#include <Windows.h>

class necessities {
public:
	static HWND getConsoleHwnd(void);
	static void setWindow(int width, int height);
	static void setWindow(HANDLE handle, int width, int height);
	static CONSOLE_SCREEN_BUFFER_INFO clear(void);
	static CONSOLE_SCREEN_BUFFER_INFO clear(HANDLE handle);
	static void goXY(int x, int y);
	static void goXY(HANDLE handle, int x, int y);
	static void setCursor(int size, bool visibility);
	static void setCursor(HANDLE handle, int size, bool visibility);
	static void waitForMouseMove(void);
	static void waitForMouseClick(void);
	static void waitForKBHit(void);
};