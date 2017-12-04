#include <Windows.h>
#include <chrono>
#include <thread>
#include "necessities.h"

HWND necessities::getConsoleHwnd(void)
{
#define MY_BUFSIZE 1024 // Buffer size for console window titles.
	HWND hwndFound;         // This is what is returned to the caller.
	char pszNewWindowTitle[MY_BUFSIZE]; // Contains fabricated
										// WindowTitle.
	char pszOldWindowTitle[MY_BUFSIZE]; // Contains original
										// WindowTitle.

										// Fetch current window title.

	GetConsoleTitle((LPWSTR)pszOldWindowTitle, MY_BUFSIZE);

	// Format a "unique" NewWindowTitle.

	wsprintf((LPWSTR)pszNewWindowTitle, L"%d/%d",
		(int)GetTickCount64(),
		GetCurrentProcessId());

	// Change current window title.

	SetConsoleTitle((LPWSTR)pszNewWindowTitle);

	// Ensure window title has been updated.

	Sleep(40);

	// Look for NewWindowTitle.

	hwndFound = FindWindow(NULL, (LPWSTR)pszNewWindowTitle);

	// Restore original window title.

	SetConsoleTitle((LPWSTR)pszOldWindowTitle);

	return(hwndFound);
}

void necessities::setWindow(int width, int height) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	_COORD coord;
	coord.X = width;
	coord.Y = height;

	CONSOLE_SCREEN_BUFFER_INFO screen;
	screen.srWindow.Top = 0;
	screen.srWindow.Left = 0;
	screen.srWindow.Bottom = height - 1;
	screen.srWindow.Right = width - 1;

	SetConsoleWindowInfo(handle, TRUE, &screen.srWindow);
	SetConsoleScreenBufferSize(handle, coord);
}

void necessities::setWindow(HANDLE handle, int width, int height) {
	_COORD coord;
	coord.X = width;
	coord.Y = height;

	CONSOLE_SCREEN_BUFFER_INFO screen;
	screen.srWindow.Top = 0;
	screen.srWindow.Left = 0;
	screen.srWindow.Bottom = height - 1;
	screen.srWindow.Right = width - 1;

	SetConsoleWindowInfo(handle, TRUE, &screen.srWindow);
	SetConsoleScreenBufferSize(handle, coord);
}

CONSOLE_SCREEN_BUFFER_INFO necessities::clear() {
	COORD topLeft = { 0, 0 };
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(handle, &screen);
	FillConsoleOutputCharacterA(
		handle, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		handle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);

	SetConsoleCursorPosition(handle, topLeft);
	
	return screen;
}

CONSOLE_SCREEN_BUFFER_INFO necessities::clear(HANDLE handle) {
	COORD topLeft = { 0, 0 };
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(handle, &screen);
	FillConsoleOutputCharacterA(
		handle, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		handle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);

	SetConsoleCursorPosition(handle, topLeft);
	
	return screen;
}

void necessities::goXY(int x, int y) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(handle, coord);
}

void necessities::goXY(HANDLE handle, int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(handle, coord);
}

void necessities::setCursor(int size, bool visibility) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	if (size < 15)
		size = 15;
	if (size > 100)
		size = 100;

	CONSOLE_CURSOR_INFO cursor;
	cursor.dwSize = size;
	cursor.bVisible = visibility;

	SetConsoleCursorInfo(handle, &cursor);
}

void necessities::setCursor(HANDLE handle, int size, bool visibility) {
	if (size < 15)
		size = 15;
	if (size > 100)
		size = 100;

	CONSOLE_CURSOR_INFO cursor;
	cursor.dwSize = size;
	cursor.bVisible = visibility;

	SetConsoleCursorInfo(handle, &cursor);
}

void necessities::waitForMouseMove(void) {
	POINT p;
	GetCursorPos(&p);
	POINT op = p;

	while (1) {
		if (op.x != p.x || op.y != p.y)
			break;
		else
			GetCursorPos(&p);

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void necessities::waitForMouseClick(void) {
	while (1) {
		if (GetAsyncKeyState(VK_LBUTTON))
			break;
		if (GetAsyncKeyState(VK_RBUTTON))
			break;
		if (GetAsyncKeyState(VK_MBUTTON))
			break;
		if (GetAsyncKeyState(VK_XBUTTON1))
			break;
		if (GetAsyncKeyState(VK_XBUTTON2))
			break;

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void necessities::waitForKBHit(void) {
	while (1) {
		if (GetAsyncKeyState(VK_BACK))
			break;
		if (GetAsyncKeyState(VK_TAB))
			break;
		if (GetAsyncKeyState(VK_CLEAR))
			break;
		if (GetAsyncKeyState(VK_RETURN))
			break;
		if (GetAsyncKeyState(VK_SHIFT))
			break;
		if (GetAsyncKeyState(VK_CONTROL))
			break;
		if (GetAsyncKeyState(VK_MENU))
			break;
		if (GetAsyncKeyState(VK_PAUSE))
			break;
		if (GetAsyncKeyState(VK_ESCAPE))
			break;
		if (GetAsyncKeyState(VK_SPACE))
			break;
		if (GetAsyncKeyState(VK_PRIOR))
			break;
		if (GetAsyncKeyState(VK_NEXT))
			break;
		if (GetAsyncKeyState(VK_END))
			break;
		if (GetAsyncKeyState(VK_HOME))
			break;
		if (GetAsyncKeyState(VK_LEFT))
			break;
		if (GetAsyncKeyState(VK_UP))
			break;
		if (GetAsyncKeyState(VK_RIGHT))
			break;
		if (GetAsyncKeyState(VK_DOWN))
			break;
		if (GetAsyncKeyState(VK_SELECT))
			break;
		if (GetAsyncKeyState(VK_PRINT))
			break;
		if (GetAsyncKeyState(VK_EXECUTE))
			break;
		if (GetAsyncKeyState(VK_SNAPSHOT))
			break;
		if (GetAsyncKeyState(VK_INSERT))
			break;
		if (GetAsyncKeyState(VK_DELETE))
			break;
		if (GetAsyncKeyState(VK_HELP))
			break;
		if (GetAsyncKeyState(0x31))
			break;
		if (GetAsyncKeyState(0x32))
			break;
		if (GetAsyncKeyState(0x33))
			break;
		if (GetAsyncKeyState(0x34))
			break;
		if (GetAsyncKeyState(0x35))
			break;
		if (GetAsyncKeyState(0x36))
			break;
		if (GetAsyncKeyState(0x37))
			break;
		if (GetAsyncKeyState(0x38))
			break;
		if (GetAsyncKeyState(0x39))
			break;
		if (GetAsyncKeyState(0x41))
			break;
		if (GetAsyncKeyState(0x42))
			break;
		if (GetAsyncKeyState(0x43))
			break;
		if (GetAsyncKeyState(0x44))
			break;
		if (GetAsyncKeyState(0x45))
			break;
		if (GetAsyncKeyState(0x46))
			break;
		if (GetAsyncKeyState(0x47))
			break;
		if (GetAsyncKeyState(0x48))
			break;
		if (GetAsyncKeyState(0x49))
			break;
		if (GetAsyncKeyState(0x4A))
			break;
		if (GetAsyncKeyState(0x4B))
			break;
		if (GetAsyncKeyState(0x4C))
			break;
		if (GetAsyncKeyState(0x4D))
			break;
		if (GetAsyncKeyState(0x4E))
			break;
		if (GetAsyncKeyState(0x4F))
			break;
		if (GetAsyncKeyState(0x50))
			break;
		if (GetAsyncKeyState(0x51))
			break;
		if (GetAsyncKeyState(0x52))
			break;
		if (GetAsyncKeyState(0x53))
			break;
		if (GetAsyncKeyState(0x54))
			break;
		if (GetAsyncKeyState(0x55))
			break;
		if (GetAsyncKeyState(0x56))
			break;
		if (GetAsyncKeyState(0x57))
			break;
		if (GetAsyncKeyState(0x58))
			break;
		if (GetAsyncKeyState(0x59))
			break;
		if (GetAsyncKeyState(0x5A))
			break;
		if (GetAsyncKeyState(VK_LWIN))
			break;
		if (GetAsyncKeyState(VK_RWIN))
			break;
		if (GetAsyncKeyState(VK_NUMPAD0))
			break;
		if (GetAsyncKeyState(VK_NUMPAD1))
			break;
		if (GetAsyncKeyState(VK_NUMPAD2))
			break;
		if (GetAsyncKeyState(VK_NUMPAD3))
			break;
		if (GetAsyncKeyState(VK_NUMPAD4))
			break;
		if (GetAsyncKeyState(VK_NUMPAD5))
			break;
		if (GetAsyncKeyState(VK_NUMPAD6))
			break;
		if (GetAsyncKeyState(VK_NUMPAD7))
			break;
		if (GetAsyncKeyState(VK_NUMPAD8))
			break;
		if (GetAsyncKeyState(VK_NUMPAD9))
			break;
		if (GetAsyncKeyState(VK_MULTIPLY))
			break;
		if (GetAsyncKeyState(VK_ADD))
			break;
		if (GetAsyncKeyState(VK_SEPARATOR))
			break;
		if (GetAsyncKeyState(VK_SUBTRACT))
			break;
		if (GetAsyncKeyState(VK_DECIMAL))
			break;
		if (GetAsyncKeyState(VK_DIVIDE))
			break;
		if (GetAsyncKeyState(VK_F1))
			break;
		if (GetAsyncKeyState(VK_F2))
			break;
		if (GetAsyncKeyState(VK_F3))
			break;
		if (GetAsyncKeyState(VK_F4))
			break;
		if (GetAsyncKeyState(VK_F5))
			break;
		if (GetAsyncKeyState(VK_F6))
			break;
		if (GetAsyncKeyState(VK_F7))
			break;
		if (GetAsyncKeyState(VK_F8))
			break;
		if (GetAsyncKeyState(VK_F9))
			break;
		if (GetAsyncKeyState(VK_F10))
			break;
		if (GetAsyncKeyState(VK_F11))
			break;
		if (GetAsyncKeyState(VK_F12))
			break;
		if (GetAsyncKeyState(VK_F13))
			break;
		if (GetAsyncKeyState(VK_F14))
			break;
		if (GetAsyncKeyState(VK_F15))
			break;
		if (GetAsyncKeyState(VK_F16))
			break;
		if (GetAsyncKeyState(VK_F17))
			break;
		if (GetAsyncKeyState(VK_F18))
			break;
		if (GetAsyncKeyState(VK_F19))
			break;
		if (GetAsyncKeyState(VK_F20))
			break;
		if (GetAsyncKeyState(VK_F21))
			break;
		if (GetAsyncKeyState(VK_F22))
			break;
		if (GetAsyncKeyState(VK_F23))
			break;
		if (GetAsyncKeyState(VK_F24))
			break;
		if (GetAsyncKeyState(VK_NUMLOCK))
			break;
		if (GetAsyncKeyState(VK_SCROLL))
			break;
		if (GetAsyncKeyState(VK_LSHIFT))
			break;
		if (GetAsyncKeyState(VK_RSHIFT))
			break;
		if (GetAsyncKeyState(VK_LCONTROL))
			break;
		if (GetAsyncKeyState(VK_RCONTROL))
			break;
		if (GetAsyncKeyState(VK_LMENU))
			break;
		if (GetAsyncKeyState(VK_RMENU))
			break;
		
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

std::vector<byte> necessities::waitForAction(bool includeMouseMovement) {
	std::vector<byte> codes;
	
	POINT p;
	GetCursorPos(&p);
	POINT op = p;

	while (1) {
		codes.clear();

		if (GetAsyncKeyState(VK_BACK))
			codes.push_back(VK_BACK);
		if (GetAsyncKeyState(VK_TAB))
			codes.push_back(VK_TAB);
		if (GetAsyncKeyState(VK_CLEAR))
			codes.push_back(VK_CLEAR);
		if (GetAsyncKeyState(VK_RETURN))
			codes.push_back(VK_RETURN);
		if (GetAsyncKeyState(VK_SHIFT))
			codes.push_back(VK_SHIFT);
		if (GetAsyncKeyState(VK_CONTROL))
			codes.push_back(VK_CONTROL);
		if (GetAsyncKeyState(VK_MENU))
			codes.push_back(VK_MENU);
		if (GetAsyncKeyState(VK_PAUSE))
			codes.push_back(VK_PAUSE);
		if (GetAsyncKeyState(VK_ESCAPE))
			codes.push_back(VK_ESCAPE);
		if (GetAsyncKeyState(VK_SPACE))
			codes.push_back(VK_SPACE);
		if (GetAsyncKeyState(VK_PRIOR))
			codes.push_back(VK_PRIOR);
		if (GetAsyncKeyState(VK_NEXT))
			codes.push_back(VK_NEXT);
		if (GetAsyncKeyState(VK_END))
			codes.push_back(VK_END);
		if (GetAsyncKeyState(VK_HOME))
			codes.push_back(VK_HOME);
		if (GetAsyncKeyState(VK_LEFT))
			codes.push_back(VK_LEFT);
		if (GetAsyncKeyState(VK_UP))
			codes.push_back(VK_UP);
		if (GetAsyncKeyState(VK_RIGHT))
			codes.push_back(VK_RIGHT);
		if (GetAsyncKeyState(VK_DOWN))
			codes.push_back(VK_DOWN);
		if (GetAsyncKeyState(VK_SELECT))
			codes.push_back(VK_SELECT);
		if (GetAsyncKeyState(VK_PRINT))
			codes.push_back(VK_PRINT);
		if (GetAsyncKeyState(VK_EXECUTE))
			codes.push_back(VK_EXECUTE);
		if (GetAsyncKeyState(VK_SNAPSHOT))
			codes.push_back(VK_SNAPSHOT);
		if (GetAsyncKeyState(VK_INSERT))
			codes.push_back(VK_INSERT);
		if (GetAsyncKeyState(VK_DELETE))
			codes.push_back(VK_DELETE);
		if (GetAsyncKeyState(VK_HELP))
			codes.push_back(VK_HELP);
		if (GetAsyncKeyState(0x31))
			codes.push_back(0x31);
		if (GetAsyncKeyState(0x32))
			codes.push_back(0x32);
		if (GetAsyncKeyState(0x33))
			codes.push_back(0x33);
		if (GetAsyncKeyState(0x34))
			codes.push_back(0x34);
		if (GetAsyncKeyState(0x35))
			codes.push_back(0x35);
		if (GetAsyncKeyState(0x36))
			codes.push_back(0x36);
		if (GetAsyncKeyState(0x37))
			codes.push_back(0x37);
		if (GetAsyncKeyState(0x38))
			codes.push_back(0x38);
		if (GetAsyncKeyState(0x39))
			codes.push_back(0x39);
		if (GetAsyncKeyState(0x41))
			codes.push_back(0x41);
		if (GetAsyncKeyState(0x42))
			codes.push_back(0x42);
		if (GetAsyncKeyState(0x43))
			codes.push_back(0x43);
		if (GetAsyncKeyState(0x44))
			codes.push_back(0x44);
		if (GetAsyncKeyState(0x45))
			codes.push_back(0x45);
		if (GetAsyncKeyState(0x46))
			codes.push_back(0x46);
		if (GetAsyncKeyState(0x47))
			codes.push_back(0x47);
		if (GetAsyncKeyState(0x48))
			codes.push_back(0x48);
		if (GetAsyncKeyState(0x49))
			codes.push_back(0x49);
		if (GetAsyncKeyState(0x4A))
			codes.push_back(0x4A);
		if (GetAsyncKeyState(0x4B))
			codes.push_back(0x4B);
		if (GetAsyncKeyState(0x4C))
			codes.push_back(0x4C);
		if (GetAsyncKeyState(0x4D))
			codes.push_back(0x4D);
		if (GetAsyncKeyState(0x4E))
			codes.push_back(0x4E);
		if (GetAsyncKeyState(0x4F))
			codes.push_back(0x4F);
		if (GetAsyncKeyState(0x50))
			codes.push_back(0x50);
		if (GetAsyncKeyState(0x51))
			codes.push_back(0x51);
		if (GetAsyncKeyState(0x52))
			codes.push_back(0x52);
		if (GetAsyncKeyState(0x53))
			codes.push_back(0x53);
		if (GetAsyncKeyState(0x54))
			codes.push_back(0x54);
		if (GetAsyncKeyState(0x55))
			codes.push_back(0x55);
		if (GetAsyncKeyState(0x56))
			codes.push_back(0x56);
		if (GetAsyncKeyState(0x57))
			codes.push_back(0x57);
		if (GetAsyncKeyState(0x58))
			codes.push_back(0x58);
		if (GetAsyncKeyState(0x59))
			codes.push_back(0x59);
		if (GetAsyncKeyState(0x5A))
			codes.push_back(0x5A);
		if (GetAsyncKeyState(VK_LWIN))
			codes.push_back(VK_LWIN);
		if (GetAsyncKeyState(VK_RWIN))
			codes.push_back(VK_RWIN);
		if (GetAsyncKeyState(VK_NUMPAD0))
			codes.push_back(VK_NUMPAD0);
		if (GetAsyncKeyState(VK_NUMPAD1))
			codes.push_back(VK_NUMPAD1);
		if (GetAsyncKeyState(VK_NUMPAD2))
			codes.push_back(VK_NUMPAD2);
		if (GetAsyncKeyState(VK_NUMPAD3))
			codes.push_back(VK_NUMPAD3);
		if (GetAsyncKeyState(VK_NUMPAD4))
			codes.push_back(VK_NUMPAD4);
		if (GetAsyncKeyState(VK_NUMPAD5))
			codes.push_back(VK_NUMPAD5);
		if (GetAsyncKeyState(VK_NUMPAD6))
			codes.push_back(VK_NUMPAD6);
		if (GetAsyncKeyState(VK_NUMPAD7))
			codes.push_back(VK_NUMPAD7);
		if (GetAsyncKeyState(VK_NUMPAD8))
			codes.push_back(VK_NUMPAD8);
		if (GetAsyncKeyState(VK_NUMPAD9))
			codes.push_back(VK_NUMPAD9);
		if (GetAsyncKeyState(VK_MULTIPLY))
			codes.push_back(VK_MULTIPLY);
		if (GetAsyncKeyState(VK_ADD))
			codes.push_back(VK_ADD);
		if (GetAsyncKeyState(VK_SEPARATOR))
			codes.push_back(VK_SEPARATOR);
		if (GetAsyncKeyState(VK_SUBTRACT))
			codes.push_back(VK_SUBTRACT);
		if (GetAsyncKeyState(VK_DECIMAL))
			codes.push_back(VK_DECIMAL);
		if (GetAsyncKeyState(VK_DIVIDE))
			codes.push_back(VK_DIVIDE);
		if (GetAsyncKeyState(VK_F1))
			codes.push_back(VK_F1);
		if (GetAsyncKeyState(VK_F2))
			codes.push_back(VK_F2);
		if (GetAsyncKeyState(VK_F3))
			codes.push_back(VK_F3);
		if (GetAsyncKeyState(VK_F4))
			codes.push_back(VK_F4);
		if (GetAsyncKeyState(VK_F5))
			codes.push_back(VK_F5);
		if (GetAsyncKeyState(VK_F6))
			codes.push_back(VK_F6);
		if (GetAsyncKeyState(VK_F7))
			codes.push_back(VK_F7);
		if (GetAsyncKeyState(VK_F8))
			codes.push_back(VK_F8);
		if (GetAsyncKeyState(VK_F9))
			codes.push_back(VK_F9);
		if (GetAsyncKeyState(VK_F10))
			codes.push_back(VK_F10);
		if (GetAsyncKeyState(VK_F11))
			codes.push_back(VK_F11);
		if (GetAsyncKeyState(VK_F12))
			codes.push_back(VK_F12);
		if (GetAsyncKeyState(VK_F13))
			codes.push_back(VK_F13);
		if (GetAsyncKeyState(VK_F14))
			codes.push_back(VK_F14);
		if (GetAsyncKeyState(VK_F15))
			codes.push_back(VK_F15);
		if (GetAsyncKeyState(VK_F16))
			codes.push_back(VK_F16);
		if (GetAsyncKeyState(VK_F17))
			codes.push_back(VK_F17);
		if (GetAsyncKeyState(VK_F18))
			codes.push_back(VK_F18);
		if (GetAsyncKeyState(VK_F19))
			codes.push_back(VK_F19);
		if (GetAsyncKeyState(VK_F20))
			codes.push_back(VK_F20);
		if (GetAsyncKeyState(VK_F21))
			codes.push_back(VK_F21);
		if (GetAsyncKeyState(VK_F22))
			codes.push_back(VK_F22);
		if (GetAsyncKeyState(VK_F23))
			codes.push_back(VK_F23);
		if (GetAsyncKeyState(VK_F24))
			codes.push_back(VK_F24);
		if (GetAsyncKeyState(VK_NUMLOCK))
			codes.push_back(VK_NUMLOCK);
		if (GetAsyncKeyState(VK_SCROLL))
			codes.push_back(VK_SCROLL);
		if (GetAsyncKeyState(VK_LSHIFT))
			codes.push_back(VK_LSHIFT);
		if (GetAsyncKeyState(VK_RSHIFT))
			codes.push_back(VK_RSHIFT);
		if (GetAsyncKeyState(VK_LCONTROL))
			codes.push_back(VK_LCONTROL);
		if (GetAsyncKeyState(VK_RCONTROL))
			codes.push_back(VK_RCONTROL);
		if (GetAsyncKeyState(VK_LMENU))
			codes.push_back(VK_LMENU);
		if (GetAsyncKeyState(VK_RMENU))
			codes.push_back(VK_RMENU);
		if (GetAsyncKeyState(VK_LBUTTON))
			codes.push_back(VK_LBUTTON);
		if (GetAsyncKeyState(VK_RBUTTON))
			codes.push_back(VK_RBUTTON);
		if (GetAsyncKeyState(VK_MBUTTON))
			codes.push_back(VK_MBUTTON);
		if (GetAsyncKeyState(VK_XBUTTON1))
			codes.push_back(VK_XBUTTON1);
		if (GetAsyncKeyState(VK_XBUTTON2))
			codes.push_back(VK_XBUTTON2);

		if (codes.size() > 0)
			break;

		if (includeMouseMovement) {
			if (op.x != p.x || op.y != p.y)
				break;
			else
				GetCursorPos(&p);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	return codes;
}