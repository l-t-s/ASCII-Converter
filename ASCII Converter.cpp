#include <iostream>
#include <string>
#include <sstream>
#include <Windows.h>
#include <thread> 
#include <chrono>


HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
int tab = 1;

DWORD written;
CONSOLE_SCREEN_BUFFER_INFO screen;
CONSOLE_CURSOR_INFO cursor;

int conversion = 12;

void SetWindow(int width, int height) {
	_COORD coord;
	coord.X = width;
	coord.Y = height;

	screen.srWindow.Top = 0;
	screen.srWindow.Left = 0;
	screen.srWindow.Bottom = height - 1;
	screen.srWindow.Right = width - 1;

	SetConsoleScreenBufferSize(console, coord);
	SetConsoleWindowInfo(console, TRUE, &screen.srWindow);
}

void clear() {
	COORD topLeft = { 0, 0 };

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);

	SetConsoleCursorPosition(console, topLeft);
}

void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(console, coord);
}

void waitForUpdate() {
	CONSOLE_SCREEN_BUFFER_INFO screenOld = screen;
	while (screenOld.srWindow.Right == screen.srWindow.Right && !GetAsyncKeyState(VK_RETURN) && !GetAsyncKeyState(VK_DOWN) && !GetAsyncKeyState(VK_UP) && !GetAsyncKeyState(VK_RIGHT) && !GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_ESCAPE)) {
		GetConsoleScreenBufferInfo(console, &screen);
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
}

void draw() {
	std::string space = "";
	std::stringstream menu;

	if (screen.srWindow.Right > 0) {
		for (int i = 0; i < (screen.srWindow.Right - 28) / 5; i++) {
			space.append(" ");
		}
	}

	switch (tab) {
	case 1:
		menu << space << ">Help<" << space << " Decode " << space << " Info " << space << " Encode\n";
		break;
	case 2:
		menu << space << "Help" << space << ">Decode<" << space << " Info " << space << " Encode\n";
		break;
	case 3:
		menu << space << "Help" << space << " Decode " << space << ">Info<" << space << " Encode\n";
		break;
	case 4:
		menu << space << "Help" << space << " Decode " << space << " Info " << space << ">Encode<\n";
		break;
	}

	clear();

	gotoxy(0, 0);
	std::cout << menu.str();

	gotoxy(0, 2);
	switch (tab) {
	case 1:
		std::cout << "Move selection with arrow keys.\nLeft and right to switch tabs.\nEnter / Return key to interact with tab.\nEscape key to exit programme.\n\nUp and down to change options in this tab.\n\n\nConversion:\n\n Decimals\n Hexadecimals\n Octals";
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	}

	cursor.bVisible = false;
	SetConsoleCursorInfo(console, &cursor);
}

void helptab() {
	if (GetAsyncKeyState(VK_RETURN)) {
		gotoxy(0, conversion);
		cursor.bVisible = true;
		SetConsoleCursorInfo(console, &cursor);

		while (GetAsyncKeyState(VK_RETURN)) {
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
		}

		while (!GetAsyncKeyState(VK_RETURN)) {
			if (GetAsyncKeyState(VK_DOWN) && conversion != 14) {
				conversion++;
				gotoxy(0, conversion);
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
			} else if (GetAsyncKeyState(VK_UP) && conversion != 12) {
				conversion--;
				gotoxy(0, conversion);
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(5));
		}

		cursor.bVisible = false;
		SetConsoleCursorInfo(console, &cursor);
	} else if (GetAsyncKeyState(VK_RIGHT)) {
		while (GetAsyncKeyState(VK_RETURN)) {
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
		}
		tab = 2;
		SetConsoleTitle(L"ASCII - Decode");
	}
}

void decode() {
	if (GetAsyncKeyState(VK_LEFT)) {
		while (GetAsyncKeyState(VK_RETURN)) {
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
		}
		tab = 1;
		SetConsoleTitle(L"ASCII - Help");
	} else if (GetAsyncKeyState(VK_RIGHT)) {
		tab = 3;
		SetConsoleTitle(L"ASCII - Info");
	}
}

void infotab() {
	if (GetAsyncKeyState(VK_LEFT)) {
		tab = 2;
		SetConsoleTitle(L"ASCII - Decode");
	} else if (GetAsyncKeyState(VK_RIGHT)) {
		tab = 4;
		SetConsoleTitle(L"ASCII - Encode");
	}
}

void encode() {
	if (GetAsyncKeyState(VK_LEFT)) {
		tab = 3;
		SetConsoleTitle(L"ASCII - Info");
	}
}

int main() {
	SetConsoleTitle(L"ASCII - Help");

	cursor.dwSize = 100;

	SetWindow(43, 15);
	SetWindow(44, 16);

	while (!GetAsyncKeyState(VK_ESCAPE)) {
		switch (tab) {
			case 1:
				helptab();
				break;
			case 2:
				decode();
				break;
			case 3:
				infotab();
				break;
			case 4:
				encode();
				break;
		}

		draw();

		while (GetAsyncKeyState(VK_RETURN) || GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN)) {
			if (GetAsyncKeyState(VK_ESCAPE)) {
				break;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(25));
		waitForUpdate();
	}
    return 0;
}