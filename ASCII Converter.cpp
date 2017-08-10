// ASCII Converter.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <sstream>
#include <Windows.h>
#include <thread> 
#include <chrono> 

using namespace std::this_thread;
using namespace std::chrono_literals;

HANDLE help = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE decoding = CreateConsoleScreenBuffer(GENERIC_WRITE | GENERIC_READ, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
HANDLE info = CreateConsoleScreenBuffer(GENERIC_WRITE | GENERIC_READ, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
HANDLE encoding = CreateConsoleScreenBuffer(GENERIC_WRITE | GENERIC_READ, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
HANDLE currentHandle = help;

DWORD written;
CONSOLE_SCREEN_BUFFER_INFO screen;
CONSOLE_CURSOR_INFO cursor;

int conversion = 13;

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

void draw(char t)
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

	switch (t)
	{
	case 'h':
		tab << space << ">Help<" << space << " Decode " << space << " Info " << space << " Encode\n";
		break;
	case 'd':
		tab << space << "Help" << space << ">Decode<" << space << " Info " << space << " Encode\n";
		break;
	case 'i':
		tab << space << "Help" << space << " Decode " << space << ">Info<" << space << " Encode\n";
		break;
	case 'e':
		tab << space << "Help" << space << " Decode " << space << " Info " << space << ">Encode<\n";
	}

	std::cout << tab.str();
}

void helptab()
{
	draw('h');
	std::cout << "\nMove selection with arrow keys.\nLeft and right to switch tabs.\nEnter / Return key to interact with tab.\nEscape key to exit programme.\n\nUp and down to change options in this tab.\n\n\nConversion:\n\n Decimals\n Hexadecimals\n Octals";
	if (GetAsyncKeyState(VK_RETURN))
	{
		gotoxy(0, conversion);
		cursor.bVisible = true;
		SetConsoleCursorInfo(currentHandle, &cursor);
		while (GetAsyncKeyState(VK_RETURN))
		{
			sleep_for(100ms);
		}
		while (!GetAsyncKeyState(VK_RETURN))
		{
			if (VK_DOWN && conversion != 15)
			{
				conversion++;
			}
			else if (VK_UP && conversion != 13)
			{
				conversion--;
			}
			gotoxy(0, conversion);
			sleep_for(100ms);
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		currentHandle = decoding;
		SetConsoleActiveScreenBuffer(currentHandle);
	}
}

int main()
{
	SetConsoleTitle(L"ASCII - Help");
	cursor.dwSize = 100;
	cursor.bVisible = false;
	SetConsoleCursorInfo(currentHandle, &cursor);
	SetWindow(43, 16);
	SetWindow(44, 17);
	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		GetConsoleScreenBufferInfo(currentHandle, &screen);
		if (screen.srWindow.Right < 43)
		{
			SetWindow(44, screen.srWindow.Bottom + 1);
		}
		if (screen.srWindow.Bottom < 17)
		{
			SetWindow(screen.srWindow.Right + 1, 18);
		}

		if (currentHandle == decoding)
		{
			if (GetAsyncKeyState(VK_RETURN))
			{

			}
			else if (GetAsyncKeyState(VK_RIGHT))
			{

			}
			else if (GetAsyncKeyState(VK_LEFT))
			{

			}
		}
		else if (currentHandle == info)
		{
			if (GetAsyncKeyState(VK_RIGHT))
			{

			}
			else if (GetAsyncKeyState(VK_LEFT))
			{

			}
		}
		else if (currentHandle == encoding)
		{
			if (GetAsyncKeyState(VK_RETURN))
			{

			}
			else if (GetAsyncKeyState(VK_LEFT))
			{

			}
		}
		else
		{
			helptab();
		}

		sleep_for(100ms);
		clear();
	}
    return 0;
}

