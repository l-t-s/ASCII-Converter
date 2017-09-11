#include <iostream>
#include <string>
#include <Windows.h>
#include <thread> 
#include <chrono>


HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

DWORD written;
CONSOLE_SCREEN_BUFFER_INFO screen;
CONSOLE_CURSOR_INFO cursor;

unsigned int tab = 1;
unsigned int conversion = 12;
unsigned int view = 0;
unsigned int characters[105];
LPCTSTR items[] = { L"Length: ", L"",  L"Number of:", L"    Spaces ( )                      ", L"    Exclamations (!)                ", L"    Quotations (\x22)                  ", L"    Hashes(#)                       ", L"    Dollars($)                      ", L"    Percents(%)                     ", L"    Ampersands(&)                   ", L"    Apostrophes(')                  ", L"    Opening Parentheses (()         ", L"    Closing Parentheses ())         ", L"    Asterisks (*)                   ", L"    Plusses (+)                     ", L"    Commas (,)                      ", L"    Dashes (-)                      ", L"    Periods (.)                     ", L"    Slashes (/)                     ", L"    Colons (:)                      ", L"    Semi-Colons (;)                 ", L"    Lesser Than Quillemets (<)      ", L"    Equals (=)                      ", L"    Greater Than Quillemets (>)     ", L"    Questions (?)                   ", L"    Ats (@)                         ", L"    Opening Braces ([)              ", L"    Backslashes (\\)                 ", L"    Closing Braces (])              ", L"    Carets (^)                      ", L"    Underscore (_)                  ", L"    Graves (`)                      ", L"    Opening Curly Brackets ({)      ", L"    Vertical Bars (|)               ", L"    Closing Curly Brackets (})      ", L"    Tildes (~)                      ", L"    Pounds (£)                      ", L"    Micros (µ)                      ", L"    Obeluses (÷)                    ", L"    Degrees (°)                     ", L"    No-Breaking Spaces ( )          ", L"    1                               ", L"    2                               ", L"    3                               ", L"    4                               ", L"    5                               ", L"    6                               ", L"    7                               ", L"    8                               ", L"    9                               ", L"    0                               ", L"    A                               ", L"    B                               ", L"    C                               ", L"    D                               ", L"    E                               ",  L"    F                               ", L"    G                               ", L"    H                               ", L"    I                               ", L"    J                               ", L"    K                               ", L"    L                               ", L"    M                               ", L"    N                               ", L"    O                               ", L"    P                               ", L"    Q                               ", L"    R                               ", L"    S                               ", L"    T                               ", L"    U                               ", L"    V                               ", L"    W                               ", L"    X                               ", L"    Y                               ", L"    Z                               ", L"    a                               ", L"    b                               ", L"    c                               ", L"    d                               ", L"    e                               ", L"    f                               ", L"    g                               ", L"    h                               ", L"    i                               ", L"    j                               ", L"    k                               ", L"    l                               ", L"    m                               ", L"    n                               ", L"    o                               ", L"    p                               ", L"    q                               ", L"    r                               ", L"    s                               ", L"    t                               ", L"    u                               " , L"    v                               ", L"    w                               ", L"    x                               ", L"    y                               ", L"    z                               ", L"", L"Unrecognized characters:            " };

void SetWindow(int width, int height) {
	_COORD coord;
	coord.X = width;
	coord.Y = height;

	screen.srWindow.Top = 0;
	screen.srWindow.Left = 0;
	screen.srWindow.Bottom = height - 1;
	screen.srWindow.Right = width - 1;

	SetConsoleWindowInfo(console, TRUE, &screen.srWindow);
	SetConsoleScreenBufferSize(console, coord);
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
	while (screenOld.srWindow.Right == screen.srWindow.Right && screenOld.srWindow.Bottom == screen.srWindow.Bottom && !GetAsyncKeyState(VK_RETURN) && !GetAsyncKeyState(VK_DOWN) && !GetAsyncKeyState(VK_UP) && !GetAsyncKeyState(VK_RIGHT) && !GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_ESCAPE)) {
		GetConsoleScreenBufferInfo(console, &screen);
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
}

void draw() {
	std::string space = "";

	clear();

	SetWindow(screen.srWindow.Right + 1, screen.srWindow.Bottom + 1);

	if (screen.srWindow.Right > 0) {
		for (int i = 0; i < (screen.srWindow.Right - 28) / 5; i++) {
			space.append(" ");
		}
	}

	gotoxy(0, 0);
	switch (tab) {
	case 1:
		std::cout << space << ">Help<" << space << " Decode " << space << " Info " << space << " Encode" << space;
		break;
	case 2:
		std::cout << space << "Help" << space << ">Decode<" << space << " Info " << space << " Encode" << space;
		break;
	case 3:
		std::cout << space << "Help" << space << " Decode " << space << ">Info<" << space << " Encode" << space;
		break;
	case 4:
		std::cout << space << "Help" << space << " Decode " << space << " Info " << space << ">Encode<" << space;
		break;
	}

	gotoxy(0, 2);
	switch (tab) {
	case 1:
		WriteConsoleOutputCharacter(console, L"Move selection with arrow keys.", 31, { 0, 2 }, &written);
		WriteConsoleOutputCharacter(console, L"Left and right to switch tabs.", 30, { 0, 3 }, &written);
		WriteConsoleOutputCharacter(console, L"Enter / Return key to interact with tab.", 40, { 0, 4 }, &written);
		WriteConsoleOutputCharacter(console, L"Escape key to exit programme.", 29, { 0, 5 }, &written);
		WriteConsoleOutputCharacter(console, L"Up and down to change options in this tab.", 42, { 0, 7 }, &written);
		WriteConsoleOutputCharacter(console, L"Conversion:", 11, { 0, 10 }, &written);
		WriteConsoleOutputCharacter(console, L"Decimals", 8, { 1, 12 }, &written);
		WriteConsoleOutputCharacter(console, L"Hexadecimals", 12, { 1, 13 }, &written);
		WriteConsoleOutputCharacter(console, L"Octals", 6, { 1, 14 }, &written);
		//std::cout << "Move selection with arrow keys.\nLeft and right to switch tabs.\nEnter / Return key to interact with tab.\nEscape key to exit programme.\n\nUp and down to change options in this tab.\n\n\nConversion:\n\n Decimals\n Hexadecimals\n Octals";
		break;
	case 2:
		break;
	case 3:
		COORD y;
		y.X = 0;
		for (int i = 0; i <= screen.srWindow.Bottom - 5; i++) {
			if (view + i > 105) {
				break;
			}
			y.Y = i + 2;
			if (i + view != 1 || i + view != 2 || i + view != 103) {
				WriteConsoleOutputCharacter(console, items[i + view], lstrlen(items[i + view]), y, &written);
				//std::cout << items[i + view] << characters[i + view];
			}
		}
		break;
	case 4:
		break;
	}

	gotoxy(screen.srWindow.Right, screen.srWindow.Bottom - 1);
	std::cout << " ";

	cursor.bVisible = false;
	SetConsoleCursorInfo(console, &cursor);
}

void helptab() {
	if (GetAsyncKeyState(VK_RETURN)) {
		gotoxy(0, conversion);
		std::cout << ">";

		while (GetAsyncKeyState(VK_RETURN)) {
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
		}

		while (!GetAsyncKeyState(VK_RETURN)) {
			if (GetAsyncKeyState(VK_DOWN) && conversion != 14) {
				gotoxy(0, conversion);
				std::cout << " ";
				conversion++;
				gotoxy(0, conversion);
				std::cout << ">";
			} else if (GetAsyncKeyState(VK_UP) && conversion != 12) {
				gotoxy(0, conversion);
				std::cout << " ";
				conversion--;
				gotoxy(0, conversion);
				std::cout << ">";
			}

			switch (conversion) {
				case 12:
					SetConsoleTitle(L"ASCII - Decimals");
					break;
				case 13:
					SetConsoleTitle(L"ASCII - Hexadecimals");
					break;
				case 14:
					SetConsoleTitle(L"ASCII - Octals");
					break;
			}

			while (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(VK_UP)) {
				std::this_thread::sleep_for(std::chrono::milliseconds(5));
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(5));
		}
	} else if (GetAsyncKeyState(VK_RIGHT)) {
		tab = 2;
	}
}

void decode() {
	if (GetAsyncKeyState(VK_LEFT)) {
		tab = 1;
	} else if (GetAsyncKeyState(VK_RIGHT)) {
		tab = 3;
	}
}

void infotab() {
	if (GetAsyncKeyState(VK_DOWN)) {
		if (view >= 101) {
			view = 0;
		} else {
			view++;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	} else if (GetAsyncKeyState(VK_UP)) {
		if (view <= 0) {
			view = 101;
		} else {
			view--;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	} else if (GetAsyncKeyState(VK_LEFT)) {
		tab = 2;
	} else if (GetAsyncKeyState(VK_RIGHT)) {
		tab = 4;
	}
}

void encode() {
	if (GetAsyncKeyState(VK_LEFT)) {
		tab = 3;
	}
}

int main() {
	SetConsoleTitle(L"ASCII - Decimals");

	cursor.dwSize = 100;

	SetWindow(45, 17);
	SetWindow(46, 18);

	for (int i = 0; i < 105; i++) {
		characters[i] = 0;
	}

	std::ios::sync_with_stdio(false);

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
			if ((GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN)) && tab == 3) {
				break;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
		}

		waitForUpdate();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
    return 0;
}
