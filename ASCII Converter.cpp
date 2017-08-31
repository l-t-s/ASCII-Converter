#include <iostream>
#include <string>
#include <sstream>
#include <Windows.h>
#include <thread> 
#include <chrono>


HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

DWORD written;
CONSOLE_SCREEN_BUFFER_INFO screen;
CONSOLE_CURSOR_INFO cursor;

unsigned int tab = 1;
unsigned int conversion = 12;
unsigned int characters[102];
unsigned int view = 0;
std::string items[] = { , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , "\n    N                               ", "\n    O                               ", "\n    P                               ", "\n    Q                               ", "\n    R                               ", "\n    S                               ", "\n    T                               ", "\n    U                               ", "\n    V                               ", "\n    W                               ", "\n    X                               ", "\n    Y                               ", "\n    Z                               ", "\n    a                               ", "\n    b                               ", "\n    c                               ", "\n    d                               ", "\n    e                               ", "\n    f                               ", "\n    g                               ", "\n    h                               ", "\n    i                               ", "\n    j                               ", "\n    k                               ", "\n    l                               ", "\n    m                               ", "\n    n                               ", "\n    o                               ", "\n    p                               ", "\n    q                               ", "\n    r                               ", "\n    s                               ", "\n    t                               ", "\n    u                               " , "\n    v                               ", "\n    w                               ", "\n    x                               ", "\n    y                               ", "\n    z                               ", "\n\nUnrecognized characters:            " };

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
	std::stringstream info;

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
		info << "Length: " << characters[101] << "\n\nNumber of:\n    Spaces ( )                      " << characters[0] << "\n    Exclamations (!)                " << characters[1] << "\n    Quotations (\x22)                  " << characters[2] << "\n    Hashes(#)                      " << characters[3] << "\n    Dollars($)                     " << characters[4] << "\n    Percents(%)                    " << characters[5] << "\n    Ampersands(&)                  " << characters[6] << "\n    Apostrophes(')                 " << characters[7] << "\n    Opening Parentheses (()         " << characters[8] << "\n    Closing Parentheses ())         " << characters[9] << "\n    Asterisks (*)                   " << characters[10] << "\n    Plusses (+)                     " << characters[11] << "\n    Commas (,)                      " << characters[12] << "\n    Dashes (-)                      " << characters[13] << "\n    Periods (.)                     " << characters[14] << "\n    Slashes (/)                     " << characters[15] << "\n    Colons (:)                      " << characters[16] << "\n    Semi-Colons (;)                 " << characters[17] << "\n    Lesser Than Quillemets (<)      " << characters[18] << "\n    Equals (=)                      " << characters[19] << "\n    Greater Than Quillemets (>)     " << characters[20] << "\n    Questions (?)                   " << characters[21] << "\n    Ats (@)                         " << characters[22] << "\n    Opening Braces ([)              " << characters[23] << "\n    Backslashes (\\)                " << characters[24] << "\n    Closing Braces (])              " << characters[25] << "\n    Carets (^)                      " << characters[26] << "\n    Underscore (_)                  " << characters[27] << "\n    Graves (`)                      " << characters[28] << "\n    Opening Curly Brackets ({)      " << characters[29] << "\n    Vertical Bars (|)               " << characters[30] << "\n    Closing Curly Brackets (})      " << characters[31] << "\n    Tildes (~)                      " << characters[32] << "\n    Pounds (£)                      " << characters[33] << "\n    Micros (µ)                      " << characters[34] << "\n    Obeluses (÷)                    " << characters[35] << "\n    Degrees (°)                     " << characters[36] << "\n    No-Breaking Spaces ( )          " << characters[37] << "\n    1                               " << characters[38] << "\n    2                               " << characters[39] << "\n    3                               " << characters[40] << "\n    4                               " << characters[41] << "\n    5                               " << characters[42] << "\n    6                               " << characters[43] << "\n    7                               " << characters[44] << "\n    8                               " << characters[45] << "\n    9                               " << characters[46] << "\n    0                               " << characters[47] << "\n    A                               " << characters[48] << "\n    B                               " << characters[49] << "\n    C                               " << characters[50] << "\n    D                               " << characters[51] << "\n    E                               " << characters[52] << "\n    F                               " << characters[53] << "\n    G                               " << characters[54] << "\n    H                               " << characters[55] << "\n    I                               " << characters[56] << "\n    J                               " << characters[57] << "\n    K                               " << characters[58] << "\n    L                               " << characters[59] << "\n    M                               " << characters[60] << 
		std::cout << info.str();
		break;
	case 4:
		break;
	}

	gotoxy(0, 1);
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
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	} else if (GetAsyncKeyState(VK_UP)) {
		if (view <= 0) {
			view = 101;
		} else {
			view--;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
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

	SetWindow(43, 15);
	SetWindow(44, 16);

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
			if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN) && tab == 3) {
				break;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
		}

		waitForUpdate();
	}
    return 0;
}