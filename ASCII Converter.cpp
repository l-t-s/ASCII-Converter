#include "necessities.cpp"
#include <Windows.h>
#include <cctype>
#include <chrono>
#include <conio.h>
#include <iostream>
#include <string>
#include <vector>
#include <thread>

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO screen;

unsigned int tab = 1;
unsigned int conversion = 12;
unsigned int view = 0;
std::string decoded;
unsigned int characters[101];
std::string items[] = { "Length: ", "\nNumber of:\n    Spaces ( )                      ", "    Exclamations (!)                ", "    Quotations (\")                  ", "    Hashes(#)                       ", "    Dollars($)                      ", "    Percents(%)                     ", "    Ampersands(&)                   ", "    Apostrophes(')                  ", "    Opening Parentheses (()         ", "    Closing Parentheses ())         ", "    Asterisks (*)                   ", "    Plusses (+)                     ", "    Commas (,)                      ", "    Dashes (-)                      ", "    Periods (.)                     ", "    Slashes (/)                     ", "    Colons (:)                      ", "    Semi-Colons (;)                 ", "    Lesser Than Quillemets (<)      ", "    Equals (=)                      ", "    Greater Than Quillemets (>)     ", "    Questions (?)                   ", "    Ats (@)                         ", "    Opening Braces ([)              ", "    Backslashes (\\)                 ", "    Closing Braces (])              ", "    Carets (^)                      ", "    Underscore (_)                  ", "    Graves (`)                      ", "    Opening Curly Brackets ({)      ", "    Vertical Bars (|)               ", "    Closing Curly Brackets (})      ", "    Tildes (~)                      ", "    Pounds (£)                      ", "    Micros (µ)                      ", "    Obeluses (÷)                    ", "    Degrees (°)                     ", "    No-Breaking Spaces ( )          ", "    1                               ", "    2                               ", "    3                               ", "    4                               ", "    5                               ", "    6                               ", "    7                               ", "    8                               ", "    9                               ", "    0                               ", "    A                               ", "    B                               ", "    C                               ", "    D                               ", "    E                               ",  "    F                               ", "    G                               ", "    H                               ", "    I                               ", "    J                               ", "    K                               ", "    L                               ", "    M                               ", "    N                               ", "    O                               ", "    P                               ", "    Q                               ", "    R                               ", "    S                               ", "    T                               ", "    U                               ", "    V                               ", "    W                               ", "    X                               ", "    Y                               ", "    Z                               ", "    a                               ", "    b                               ", "    c                               ", "    d                               ", "    e                               ", "    f                               ", "    g                               ", "    h                               ", "    i                               ", "    j                               ", "    k                               ", "    l                               ", "    m                               ", "    n                               ", "    o                               ", "    p                               ", "    q                               ", "    r                               ", "    s                               ", "    t                               ", "    u                               " , "    v                               ", "    w                               ", "    x                               ", "    y                               ", "    z                               ", "\nUnrecognized characters:            " };

struct modifier_keys {
	bool caps = false;
	bool shift = false;
	bool ctrl = false;
	bool alt = false;
	bool tab = false;
	bool alt_ctrl = false;
	bool backspace = false;
};

void wait_update() 
{
	const auto screen_old = screen;
	while (screen_old.srWindow.Right == screen.srWindow.Right && screen_old.srWindow.Bottom == screen.srWindow.Bottom && !GetAsyncKeyState(VK_RETURN) && !GetAsyncKeyState(VK_DOWN) && !GetAsyncKeyState(VK_UP) && !GetAsyncKeyState(VK_RIGHT) && !GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_ESCAPE)) {
		GetConsoleScreenBufferInfo(console, &screen);
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
}

void draw() {
	std::string space;

	screen = necessities::clear();

	necessities::set_window(screen.srWindow.Right + 1, screen.srWindow.Bottom + 1);

	if (screen.srWindow.Right > 0) {
		for (auto i = 0; i < (screen.srWindow.Right - 28) / 5; i++) {
			space.append(" ");
		}
	}

	necessities::go_to(0, 0);
	switch (tab) {
	case 2:
		std::cout << space << " Help " << space << ">Decode<" << space << " Info " << space << " Encode " << space;
		break;
	case 3:
		std::cout << space << " Help " << space << " Decode " << space << ">Info<" << space << " Encode " << space;
		break;
	case 4:
		std::cout << space << " Help " << space << " Decode " << space << " Info " << space << ">Encode<" << space;
		break;
	default:
		std::cout << space << ">Help<" << space << " Decode " << space << " Info " << space << " Encode " << space;
	}

	necessities::go_to(0, 2);

	switch (tab) {
	case 2:
		necessities::go_to(0, 2);
		std::cout << decoded;
		break;
	case 3:
		for (auto i = 0; i <= screen.srWindow.Bottom - 5; i++) {
			if (view + i > 101) {
				break;
			}
			std::cout << items[i + view] << characters[i + view] << std::endl;
		}
		necessities::go_to(0, 0);
		std::cout << " ";

		necessities::set_cursor(15, false);
		break;
	case 4:
		break;
	default:
		std::cout << "Move selection with arrow keys.\nLeft and right to switch tabs.\nEnter / Return key to interact with tab.\nEscape key to exit programme.\n\nUp and down to change options in this tab.\n\n\nConversion:\n\n Decimals\n Hexadecimals\n Octals";
		necessities::go_to(0, 0);
		std::cout << " ";

		necessities::set_cursor(15, false);
	}

}

void helptab() {
	if (GetAsyncKeyState(VK_RETURN)) {
		necessities::go_to(0, conversion);
		std::cout << ">";

		while (GetAsyncKeyState(VK_RETURN)) {
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
		}

		while (!GetAsyncKeyState(VK_RETURN)) {
			if (GetAsyncKeyState(VK_DOWN) && conversion != 14) {
				necessities::go_to(0, conversion);
				std::cout << " ";
				conversion++;
				necessities::go_to(0, conversion);
				std::cout << ">";
			} else if (GetAsyncKeyState(VK_UP) && conversion != 12) {
				necessities::go_to(0, conversion);
				std::cout << " ";
				conversion--;
				necessities::go_to(0, conversion);
				std::cout << ">";
			}

			switch (conversion) {
				case 13:
					SetConsoleTitle(L"ASCII - Hexadecimals");
					break;
				case 14:
					SetConsoleTitle(L"ASCII - Octals");
					break;
				default:
					SetConsoleTitle(L"ASCII - Decimals");
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
		decoded.clear();

		std::vector<char> keys;
		std::vector<byte> codes;
		unsigned int timer = 0;

		modifier_keys modifiers;
		necessities::set_cursor(15, true);
		necessities::go_to(0, 2);

		while (GetAsyncKeyState(VK_RETURN)) {
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
		}

		while (!GetAsyncKeyState(VK_RETURN)) {
			keys.clear();
			codes.clear();

			codes = necessities::wait_for_action(false);

			if (GetAsyncKeyState(VK_RETURN)) 
				break;

			if (!codes.empty()) {

				for (auto code : codes) {
					if (std::isprint(code) && !std::iscntrl(code)) {
						keys.push_back(char(code));
					}
				}

				for (auto code : codes) {
					switch (code) 
					{
					case VK_BACK:
						modifiers.backspace = true;
						continue;
					case VK_SHIFT:
						modifiers.shift = true;
						continue;
					case VK_CAPITAL:
						if (modifiers.caps)
							modifiers.caps = false;
						else
							modifiers.caps = true;
						continue;
					case VK_CONTROL:
						modifiers.ctrl = true;
						/*
						for (auto key : codes) {
							switch (key)
							{
							case 0x41:
								decoded.clear();

								std::cout << "All deleted!";
							default:
								break;
							}
						}*/
					}
				}

				if (!modifiers.backspace) {
					if (!keys.empty()) {
						for (auto key : keys) {
							if (modifiers.shift || modifiers.caps)
								decoded.push_back(key);
							else
								decoded.push_back(std::tolower(key));
						}
					}
				}
				else {
					if (!decoded.empty())
						decoded.pop_back();
				}

				draw();

				necessities::go_to(0, 1);
				if (modifiers.caps)
					std::cout << "CAPS ";
				if (modifiers.shift)
					std::cout << "SHIFT ";
				if (modifiers.ctrl)
					std::cout << "CTRL ";
				modifiers.caps = false;
				modifiers.shift = false;
				modifiers.ctrl = false;
			}
			else 
				draw();

			while (!necessities::key_down().empty())
			{
				timer++;

				if (timer >= 500)
					break;

				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
			timer = 0;
		}

		necessities::set_cursor(15, false);

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
	necessities::enable_virtual_console();
	necessities::disable_mouse_interaction();
	necessities::disable_ctrl_functions();

	SetConsoleTitle(L"ASCII - Decimals");

	necessities::set_cursor(15, false);

	necessities::set_window(45, 17);
	necessities::set_window(46, 18);

	for (int i : characters) {
		characters[i] = 0;
	}
	
	std::ios::sync_with_stdio(false);

	while (!GetAsyncKeyState(VK_ESCAPE)) {
		switch (tab) {
			case 2:
				decode();
				break;
			case 3:
				infotab();
				break;
			case 4:
				encode();
				break;
			default:
				helptab();
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

		wait_update();
		std::this_thread::sleep_for(std::chrono::nanoseconds(100));
	}

    return 0;
}
