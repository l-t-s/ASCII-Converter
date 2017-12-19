#include <Windows.h>
#include <chrono>
#include <thread>
#include <vector>

class necessities {
public:
	static void set_window(const int width, const int height) {
		const auto handle = GetStdHandle(STD_OUTPUT_HANDLE);

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

	static void enable_virtual_console()
	{
		const auto h_out = GetStdHandle(STD_OUTPUT_HANDLE);
		const auto h_in = GetStdHandle(STD_INPUT_HANDLE);
		DWORD dw_mode = 0;
		GetConsoleMode(h_out, &dw_mode);
		dw_mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		SetConsoleMode(h_out, dw_mode);
		GetConsoleMode(h_in, &dw_mode);
		dw_mode |= ENABLE_VIRTUAL_TERMINAL_INPUT;
		SetConsoleMode(h_in, dw_mode);
	}

	static void disable_mouse_interaction()
	{
		const auto h_in = GetStdHandle(STD_INPUT_HANDLE);
		DWORD dw_mode = 0;
		GetConsoleMode(h_in, &dw_mode);
		dw_mode = dw_mode & ~ENABLE_MOUSE_INPUT;
		dw_mode = dw_mode & ~ENABLE_QUICK_EDIT_MODE;
		SetConsoleMode(h_in, dw_mode);
	}

	static void disable_ctrl_functions()
	{
		const auto h_in = GetStdHandle(STD_INPUT_HANDLE);
		DWORD dw_mode = 0;
		GetConsoleMode(h_in, &dw_mode);
		dw_mode = dw_mode & ~ENABLE_PROCESSED_INPUT;
		SetConsoleMode(h_in, dw_mode);
	}

	static CONSOLE_SCREEN_BUFFER_INFO clear() {
		const COORD top_left = { 0, 0 };
		CONSOLE_SCREEN_BUFFER_INFO screen;
		DWORD written;
		const auto handle = GetStdHandle(STD_OUTPUT_HANDLE);

		GetConsoleScreenBufferInfo(handle, &screen);
		FillConsoleOutputCharacterA(
			handle, ' ', screen.dwSize.X * screen.dwSize.Y, top_left, &written
		);
		FillConsoleOutputAttribute(
			handle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
			screen.dwSize.X * screen.dwSize.Y, top_left, &written
		);

		SetConsoleCursorPosition(handle, top_left);

		return screen;
	}

	static void go_to(const int x, const int y) {
		const auto handle = GetStdHandle(STD_OUTPUT_HANDLE);

		COORD coord;
		coord.X = x;
		coord.Y = y;
		SetConsoleCursorPosition(handle, coord);
	}

	static void set_cursor(int size, const bool visibility) {
		const auto handle = GetStdHandle(STD_OUTPUT_HANDLE);

		if (size < 15)
			size = 15;
		if (size > 100)
			size = 100;

		CONSOLE_CURSOR_INFO cursor;
		cursor.dwSize = size;
		cursor.bVisible = visibility;

		SetConsoleCursorInfo(handle, &cursor);
	}

	static bool is_mouse_move() {
		POINT p;
		GetCursorPos(&p);
		const auto op = p;

		std::this_thread::sleep_for(std::chrono::milliseconds(10));

		GetCursorPos(&p);

		if (op.x != p.x || op.y != p.y) return true; return false;
	}

	static std::vector<byte> mouse_down() {
		std::vector<byte> codes;

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

		return codes;
	}

	static std::vector<byte> key_down() {
		std::vector<byte> codes;
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

		return codes;
	}

	static bool is_active() {
		std::vector<byte> codes;
		codes.clear();

		auto keys = key_down();
		auto buttons = mouse_down();

		if (is_mouse_move || !keys.empty() || !buttons.empty())
			return true;

		return false;
	}

	static void wait_mouse_move(const bool invert) {
		POINT p;
		GetCursorPos(&p);
		const auto op = p;

		if (invert)
		{
			while (true)
			{
				if (op.x == p.x || op.y == p.y)
					break;
				else
					GetCursorPos(&p);

				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
		}
		else
		{
			while (true) 
			{
				if (op.x != p.x || op.y != p.y)
					break;
				else
					GetCursorPos(&p);

				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
		}
		
	}

	static std::vector<byte> wait_mouse_click(const bool invert) {
		std::vector<byte> codes;
		codes.clear();

		if (invert)
		{
			while (!codes.empty())
			{
				codes = mouse_down();

				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
		}
		else
		{
			while (codes.empty()) 
			{
				codes = mouse_down();

				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
		}

		return codes;
	}

	static std::vector<byte> wait_key_down(const bool invert) {
		auto codes = key_down();

		if (invert)
		{
			while (!codes.empty()) {
				codes = key_down();

				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
		}
		else
		{
			while (codes.empty()) {
				codes = key_down();

				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
		}
		
		return codes;
	}

	static std::vector<byte> wait_for_action(const bool watch_mouse_movement) {
		std::vector<byte> codes;
		codes.clear();

		POINT p;
		GetCursorPos(&p);
		const auto op = p;

		while (codes.empty()) 
		{
			auto keys = key_down();
			codes.insert(codes.begin(), keys.begin(), keys.end());

			auto buttons = mouse_down();
			codes.insert(codes.end(), buttons.begin(), buttons.end());

			if (watch_mouse_movement) {
				if (op.x != p.x || op.y != p.y)
					break;
				else
					GetCursorPos(&p);
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}

		return codes;
	}
};
