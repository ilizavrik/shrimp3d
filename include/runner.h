#pragma once
#include"buffer.h"
class Runner {

	HANDLE hConsole; 
	CONSOLE_CURSOR_INFO cursorInfo; 
	COORD bufferSize; 
	SMALL_RECT windowSize; 
	CONSOLE_FONT_INFOEX cfi;

	Buffer buf;
	short Hei = 60, Wid = 240;

public:

	Runner() {
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		//font
		cfi.cbSize = sizeof(cfi); 
		GetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
		cfi.dwFontSize.X = 8; 
		cfi.dwFontSize.Y = 8;
		wcscpy_s(cfi.FaceName, L"Consolas");
		SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);

		//cursor
		cursorInfo = { 1, FALSE };
		SetConsoleCursorInfo(hConsole, &cursorInfo);

		//resize;
		SMALL_RECT tmp = { 0, 0, 1, 1 };
		SetConsoleWindowInfo(hConsole, TRUE, &tmp);

		bufferSize = { Wid, Hei };
		SetConsoleScreenBufferSize(hConsole, bufferSize);

		windowSize = { 0, 0, (short)(Wid - 1), (short)(Hei - 1) };
		SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

		buf.resize(Hei, Wid);

		//fix console size
		HWND hwnd = GetConsoleWindow();
		
		LONG style = GetWindowLong(hwnd, GWL_STYLE);

		style &= ~WS_SIZEBOX;
		style &= ~WS_MAXIMIZEBOX;

		SetWindowLong(hwnd, GWL_STYLE, style);

		SetWindowPos(
			hwnd,
			NULL,
			0, 0, 0, 0,
			SWP_NOMOVE | SWP_NOSIZE |
			SWP_NOZORDER | SWP_FRAMECHANGED
		);
	}
	
	void run();
};