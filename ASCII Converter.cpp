#include <iostream>
#include <string>
#include <sstream>
#include <Windows.h>
#include <thread> 
#include <chrono>


HANDLE help = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE decoding = CreateConsoleScreenBuffer(GENERIC_WRITE | GENERIC_READ, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
HANDLE info = CreateConsoleScreenBuffer(GENERIC_WRITE | GENERIC_READ, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
HANDLE encoding = CreateConsoleScreenBuffer(GENERIC_WRITE | GENERIC_READ, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
HANDLE currentHandle = help;

DWORD written;
CONSOLE_SCREEN_BUFFER_INFO screen;
CONSOLE_CURSOR_INFO cursor;

int conversion = 12;
bool windowChange = false;

void SetWindow(int width, int height)
{
	_COORD coord;
	coord.X = width;
	coord.Y = height;

	screen.srWindow.Top = 0;
	screen.srWindow.Left = 0;
	screen.srWindow.Bottom = height - 1;
	screen.srWindow.Right = width - 1;

	SetConsoleScreenBufferSize(currentHandle, coord);
	SetConsoleWindowInfo(currentHandle, TRUE, &screen.srWindow);
}

void clear() 
{
	COORD topLeft = { 0, 0 };

	GetConsoleScreenBufferInfo(currentHandle, &screen);
	FillConsoleOutputCharacterA(
		currentHandle, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		currentHandle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(currentHandle, topLeft);
}

void gotoxy(int x, int y) 
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(currentHandle, coord);
}

void draw()
{
	std::string space = "";
	std::stringstream tab;

	for (int i = 0; i < (screen.srWindow.Right - 28) / 5; i++)
	{
		space.append(" ");
	}

	gotoxy(0, 0);

	for (int i = 0; i < screen.srWindow.Right; i++) std::cout << " ";

	gotoxy(0, 0);

	if (currentHandle == help)
	{
		tab << space << ">Help<" << space << " Decode " << space << " Info " << space << " Encode\n";
	}
	else if (currentHandle == decoding)
	{
		tab << space << "Help" << space << ">Decode<" << space << " Info " << space << " Encode\n";
	}
	else if (currentHandle == info)
	{
		tab << space << "Help" << space << " Decode " << space << ">Info<" << space << " Encode\n";
	}
	else if (currentHandle == encoding)
	{
		tab << space << "Help" << space << " Decode " << space << " Info " << space << ">Encode<\n";
	}

	std::cout << tab.str();
}

void windowWatch()
{
	SMALL_RECT windowOld = screen.srWindow;
	draw();
	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		GetConsoleScreenBufferInfo(currentHandle, &screen);
		if (windowOld.Bottom == screen.srWindow.Bottom && windowOld.Right == screen.srWindow.Right)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(25));
			windowChange = false;
		}
		else
		{
			clear();

			if (screen.srWindow.Right < 43)
			{
				SetWindow(44, screen.srWindow.Bottom + 1);
			}
			if (screen.srWindow.Bottom < 17)
			{
				SetWindow(screen.srWindow.Right + 1, 18);
			}

			draw();

			windowChange = true;

			windowOld = screen.srWindow;
		}
	}
}

void helptab()
{
	gotoxy(0, 3);
	std::cout << "Move selection with arrow keys.\nLeft and right to switch tabs.\nEnter / Return key to interact with tab.\nEscape key to exit programme.\n\nUp and down to change options in this tab.\n\n\nConversion:\n\n Decimals\n Hexadecimals\n Octals";
	
	while (!windowChange || !GetAsyncKeyState(VK_RETURN) || !GetAsyncKeyState(VK_RIGHT) || !GetAsyncKeyState(VK_ESCAPE))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(25));
	}

	if (GetAsyncKeyState(VK_RETURN))
	{
		gotoxy(0, conversion);
		cursor.bVisible = true;
		SetConsoleCursorInfo(currentHandle, &cursor);

		while (GetAsyncKeyState(VK_RETURN))
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(25));
		}

		while (!GetAsyncKeyState(VK_RETURN))
		{
			if (GetAsyncKeyState(VK_DOWN) && conversion != 14)
			{
				conversion++;
				gotoxy(0, conversion);
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
			}
			else if (GetAsyncKeyState(VK_UP) && conversion != 12)
			{
				conversion--;
				gotoxy(0, conversion);
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(25));
		}

		while (GetAsyncKeyState(VK_RETURN))
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(25));
		}

		cursor.bVisible = false;
		SetConsoleCursorInfo(currentHandle, &cursor);
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		currentHandle = decoding;
		SetConsoleActiveScreenBuffer(currentHandle);
	}
}

void decode()
{
}

void infotab()
{
}

void encode()
{
}

int main()
{
	SetConsoleTitle(L"ASCII - Help");
	cursor.dwSize = 100;
	cursor.bVisible = false;
	SetConsoleCursorInfo(currentHandle, &cursor);
	SetWindow(43, 16);
	SetWindow(44, 17);
	std::thread window(windowWatch);
	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		if (currentHandle == decoding)
		{
			decode();
		}
		else if (currentHandle == info)
		{
			infotab();
		}
		else if (currentHandle == encoding)
		{
			encode();
		}
		else
		{
			helptab();
		}
	}
	window.join();
    return 0;
}

