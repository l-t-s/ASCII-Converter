#pragma once

class necessities {
public:
	static void SetWindow(int width, int height);
	static CONSOLE_SCREEN_BUFFER_INFO clear();
	static void gotoxy(int x, int y);
};