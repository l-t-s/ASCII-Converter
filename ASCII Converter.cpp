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
unsigned int characters[102];
std::string items[] = { "Length: ", "\n\nNumber of:\n    Spaces ( )                      ", "\n    Exclamations (!)                ", "\n    Quotations (\x22)                  ", "\n    Hashes(#)                       ", "\n    Dollars($)                      ", "\n    Percents(%)                     ", "\n    Ampersands(&)                   ", "\n    Apostrophes(')                  ", "\n    Opening Parentheses (()         ", "\n    Closing Parentheses ())         ", "\n    Asterisks (*)                   ", "\n    Plusses (+)                     ", "\n    Commas (,)                      ", "\n    Dashes (-)                      ", "\n    Periods (.)                     ", "\n    Slashes (/)                     ", "\n    Colons (:)                      ", "\n    Semi-Colons (;)                 ", "\n    Lesser Than Quillemets (<)      ", "\n    Equals (=)                      ", "\n    Greater Than Quillemets (>)     ", "\n    Questions (?)                   ", "\n    Ats (@)                         ", "\n    Opening Braces ([)              ", "\n    Backslashes (\\)                 ", "\n    Closing Braces (])              ", "\n    Carets (^)                      ", "\n    Underscore (_)                  ", "\n    Graves (`)                      ", "\n    Opening Curly Brackets ({)      ", "\n    Vertical Bars (|)               ", "\n    Closing Curly Brackets (})      ", "\n    Tildes (~)                      ", "\n    Pounds (£)                      ", "\n    Micros (µ)                      ", "\n    Obeluses (÷)                    ", "\n    Degrees (°)                     ", "\n    No-Breaking Spaces ( )          ", "\n    1                               ", "\n    2                               ", "\n    3                               ", "\n    4                               ", "\n    5                               ", "\n    6                               ", "\n    7                               ", "\n    8                               ", "\n    9                               ", "\n    0                               ", "\n    A                               ", "\n    B                               ", "\n    C                               ", "\n    D                               ", "\n    E                               ",  "\n    F                               ", "\n    G                               ", "\n    H                               ", "\n    I                               ", "\n    J                               ", "\n    K                               ", "\n    L                               ", "\n    M                               ", "\n    N                               ", "\n    O                               ", "\n    P                               ", "\n    Q                               ", "\n    R                               ", "\n    S                               ", "\n    T                               ", "\n    U                               ", "\n    V                               ", "\n    W                               ", "\n    X                               ", "\n    Y                               ", "\n    Z                               ", "\n    a                               ", "\n    b                               ", "\n    c                               ", "\n    d                               ", "\n    e                               ", "\n    f                               ", "\n    g                               ", "\n    h                               ", "\n    i                               ", "\n    j                               ", "\n    k                               ", "\n    l                               ", "\n    m                               ", "\n    n                               ", "\n    o                               ", "\n    p                               ", "\n    q                               ", "\n    r                               ", "\n    s                               ", "\n    t                               ", "\n    u                               " , "\n    v                               ", "\n    w                               ", "\n    x                               ", "\n    y                               ", "\n    z                               ", "\n\nUnrecognized characters:            " };

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
		std::cout << "Move selection with arrow keys.\nLeft and right to switch tabs.\nEnter / Return key to interact with tab.\nEscape key to exit programme.\n\nUp and down to change options in this tab.\n\n\nConversion:\n\n Decimals\n Hexadecimals\n Octals";
		break;
	case 2:
		break;
	case 3:
		for (int i = 0; i <= screen.srWindow.Bottom - 5; i++) {
			if (view + i > 101) {
				break;
			}
			std::cout << items[i + view] << characters[i + view];
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

	for (int i = 0; i < 102; i++) {
		characters[i] = 0;
	}

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
	}
    return 0;
}