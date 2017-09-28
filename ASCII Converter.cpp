#include "necessities.h"
#include <Windows.h>
#include <cctype>
#include <chrono>
#include <conio.h>
#include <iostream>
#include <string>
#include <thread>

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO screen;

unsigned int tab = 1;
unsigned int conversion = 12;
unsigned int view = 0;
char base[] = { ' ' };
unsigned int characters[101];
std::string items[] = { "Length: ", "\nNumber of:\n    Spaces ( )                      ", "    Exclamations (!)                ", "    Quotations (\x22)                  ", "    Hashes(#)                       ", "    Dollars($)                      ", "    Percents(%)                     ", "    Ampersands(&)                   ", "    Apostrophes(')                  ", "    Opening Parentheses (()         ", "    Closing Parentheses ())         ", "    Asterisks (*)                   ", "    Plusses (+)                     ", "    Commas (,)                      ", "    Dashes (-)                      ", "    Periods (.)                     ", "    Slashes (/)                     ", "    Colons (:)                      ", "    Semi-Colons (;)                 ", "    Lesser Than Quillemets (<)      ", "    Equals (=)                      ", "    Greater Than Quillemets (>)     ", "    Questions (?)                   ", "    Ats (@)                         ", "    Opening Braces ([)              ", "    Backslashes (\\)                 ", "    Closing Braces (])              ", "    Carets (^)                      ", "    Underscore (_)                  ", "    Graves (`)                      ", "    Opening Curly Brackets ({)      ", "    Vertical Bars (|)               ", "    Closing Curly Brackets (})      ", "    Tildes (~)                      ", "    Pounds (£)                      ", "    Micros (µ)                      ", "    Obeluses (÷)                    ", "    Degrees (°)                     ", "    No-Breaking Spaces ( )          ", "    1                               ", "    2                               ", "    3                               ", "    4                               ", "    5                               ", "    6                               ", "    7                               ", "    8                               ", "    9                               ", "    0                               ", "    A                               ", "    B                               ", "    C                               ", "    D                               ", "    E                               ",  "    F                               ", "    G                               ", "    H                               ", "    I                               ", "    J                               ", "    K                               ", "    L                               ", "    M                               ", "    N                               ", "    O                               ", "    P                               ", "    Q                               ", "    R                               ", "    S                               ", "    T                               ", "    U                               ", "    V                               ", "    W                               ", "    X                               ", "    Y                               ", "    Z                               ", "    a                               ", "    b                               ", "    c                               ", "    d                               ", "    e                               ", "    f                               ", "    g                               ", "    h                               ", "    i                               ", "    j                               ", "    k                               ", "    l                               ", "    m                               ", "    n                               ", "    o                               ", "    p                               ", "    q                               ", "    r                               ", "    s                               ", "    t                               ", "    u                               " , "    v                               ", "    w                               ", "    x                               ", "    y                               ", "    z                               ", "\nUnrecognized characters:            " };

void waitForUpdate() {
	CONSOLE_SCREEN_BUFFER_INFO screenOld = screen;
	while (screenOld.srWindow.Right == screen.srWindow.Right && screenOld.srWindow.Bottom == screen.srWindow.Bottom && !GetAsyncKeyState(VK_RETURN) && !GetAsyncKeyState(VK_DOWN) && !GetAsyncKeyState(VK_UP) && !GetAsyncKeyState(VK_RIGHT) && !GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_ESCAPE)) {
		GetConsoleScreenBufferInfo(console, &screen);
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
}

void draw(int x, int y) {
	std::string space = "";

	screen = necessities::clear();

	necessities::setWindow(screen.srWindow.Right + 1, screen.srWindow.Bottom + 1);

	if (screen.srWindow.Right > 0) {
		for (int i = 0; i < (screen.srWindow.Right - 28) / 5; i++) {
			space.append(" ");
		}
	}

	necessities::goXY(0, 0);
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

	switch (tab) {
	case 1:
		necessities::goXY(0, 2);
		std::cout << "Move selection with arrow keys.\nLeft and right to switch tabs.\nEnter / Return key to interact with tab.\nEscape key to exit programme.\n\nUp and down to change options in this tab.\n\n\nConversion:\n\n Decimals\n Hexadecimals\n Octals";
		break;
	case 2:
		for (int i = 0; i < sizeof(base); i++) {
			std::cout << base[i];
		}
		break;
	case 3:
		necessities::goXY(0, 2);
		for (int i = 0; i <= screen.srWindow.Bottom - 5; i++) {
			if (view + i > 101) {
				break;
			}
			std::cout << items[i + view] << characters[i + view] << std::endl;
		}
		break;
	case 4:
		break;
	}

	necessities::goXY(0, 0);
	std::cout << " ";

	necessities::setCursor(15, false);
}

void helptab() {
	if (GetAsyncKeyState(VK_RETURN)) {
		necessities::goXY(0, conversion);
		std::cout << ">";

		while (GetAsyncKeyState(VK_RETURN)) {
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
		}

		while (!GetAsyncKeyState(VK_RETURN)) {
			if (GetAsyncKeyState(VK_DOWN) && conversion != 14) {
				necessities::goXY(0, conversion);
				std::cout << " ";
				conversion++;
				necessities::goXY(0, conversion);
				std::cout << ">";
			} else if (GetAsyncKeyState(VK_UP) && conversion != 12) {
				necessities::goXY(0, conversion);
				std::cout << " ";
				conversion--;
				necessities::goXY(0, conversion);
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
	if (GetAsyncKeyState(VK_RETURN)) {
		unsigned int i = 0;
		unsigned int x = 0;
		int thing;

		necessities::setCursor(15, true);
		necessities::goXY(x, 2);

		while (GetAsyncKeyState(VK_RETURN)) {
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
		}

		while (!GetAsyncKeyState(VK_RETURN)) {
			draw(0, 2);
			thing = _getch();
			if (thing == 0x7F) {
				if (x == 0 && screen.dwCursorPosition.Y > 2) {
					x = screen.srWindow.Right;
					necessities::goXY(x, --screen.dwCursorPosition.Y);
				} else if (x != 0) {
					x--;
					necessities::goXY(x, screen.dwCursorPosition.Y);
				}
				base[i] = (char)32;
				i--;
			} else if (std::isprint(thing)) {
				base[i] = (char)thing;
				i++;
				if (x == screen.srWindow.Right) {
					x = 0;
					necessities::goXY(x, ++screen.dwCursorPosition.Y);
				} else {
					x++;
					necessities::goXY(x, screen.dwCursorPosition.Y);
				}
			}
		}

		necessities::setCursor(15, false);

		while (GetAsyncKeyState(VK_RETURN)) {
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
		}
	} else if (GetAsyncKeyState(VK_LEFT)) {
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

	necessities::setCursor(15, false);

	necessities::setWindow(45, 17);
	necessities::setWindow(46, 18);

	for (int i = 0; i < 101; i++) {
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

		draw(NULL, NULL);

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
		std::this_thread::sleep_for(std::chrono::nanoseconds(100));
	}
    return 0;
}
