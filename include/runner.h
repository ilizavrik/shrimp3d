#pragma once
#include"buffer.h"
#include"linal.h"
#include"mesh.h"
class Runner {

	HANDLE hConsole; 
	CONSOLE_CURSOR_INFO cursorInfo; 
	COORD bufferSize; 
	SMALL_RECT windowSize; 
	CONSOLE_FONT_INFOEX cfi;

	Buffer buf;
	short Hei = 240, Wid = 480;
	float a = ((float)Hei / Wid)*2;

	const float FOV = 90;
	float f = 1 / (tan(toRad(FOV / 2)));
	float z_near = f;
	float z_far = 10;

	Mat4x4 proj = {
			{
			{a * f, 0, 0, 0},
			{0, f, 0, 0},
			{0, 0, z_far / (z_far - z_near), 1},
			{0, 0, -z_far * z_near / (z_far - z_near), 0}
			}
	};


public:

	Runner() {
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		//font
		cfi.cbSize = sizeof(cfi); 
		GetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
		cfi.dwFontSize.X = 1; 
		cfi.dwFontSize.Y = 2;
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
	
	void update(Mesh& mesh, float&ang);
	void render(Mesh& mesh);
	void run();
};