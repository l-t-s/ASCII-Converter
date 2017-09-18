#include <Windows.h>
#include "necessities.h"

void necessities::SetWindow(int width, int height) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	_COORD coord;
	coord.X = width;
	coord.Y = height;

	CONSOLE_SCREEN_BUFFER_INFO screen;
	screen.srWindow.Top = 0;
	screen.srWindow.Left = 0;
	screen.srWindow.Bottom = height - 1;
	screen.srWindow.Right = width - 1;

	SetConsoleWindowInfo(console, TRUE, &screen.srWindow);
	SetConsoleScreenBufferSize(console, coord);
}

CONSOLE_SCREEN_BUFFER_INFO necessities::clear() {
	COORD topLeft = { 0, 0 };
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);

	SetConsoleCursorPosition(console, topLeft);
	
	return screen;
}

void necessities::gotoxy(int x, int y) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(console, coord);
}