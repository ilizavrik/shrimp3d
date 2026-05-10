#pragma once
#include<string.h> 
#include<windows.h>
#include<cmath>
//struct for buffer
struct BufferPoint {
	int x;
	int y;
	bool operator==(BufferPoint p) {
		return (x == p.x && y == p.y);

	}
};
//buffer lol, ur screen is here
class Buffer {
	char defaultChar = ' ';
	char* self = nullptr;
	int width = 0;
	int height = 0;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

public:
	Buffer() = default;
	~Buffer() {
		delete[] self;
	}
	//NO COPY!!!!111!1!
	Buffer(const Buffer&) = delete; 
	Buffer& operator=(const Buffer&) = delete;

	// -_- hmm idk what is this shit doing
	void setDefChar(char c) {
		defaultChar = c;
	}

	//resize lol
	void resize(int h, int w) {
		if (h <= 0 || w <= 0) return;

		height = h;
		width = w;

		size_t size = (size_t)h * (size_t)w;
		delete[] self;
		self = new char[size];

	}

	//fills buffer with default character 
	void clear() { 
		if (!self) return;
		memset(self, defaultChar, (size_t)height * width); }

	//redraw screen with actual information 
	void flip() { 
		if (!self) return; 
		COORD pos = { 0, 0 }; 
		DWORD written = 0; 
		WriteConsoleOutputCharacterA( 
			hConsole, 
			self, 
			(size_t)height * width, 
			pos, &
			written );
	}

	//do i even have to explain this?
	bool belongs(BufferPoint p) {
		if (0 <= p.y && p.y < height && 0 <= p.x && p.x < width)
			return true; 
		else return false;
	}

	//draws a point
	void drawaPoint(BufferPoint p, char c) {
		if(!self) return;
		if(!belongs(p)) return;

		self[width*p.y + p.x] = c;
	}

	//Bresenham's line algorithm
	void drawaLine(BufferPoint p1, BufferPoint p2, char c) {

		int dx = std::abs(p2.x - p1.x);
		int dy = std::abs(p2.y - p1.y);
		int sx = p1.x < p2.x ? 1 : -1;
		int sy = p1.y < p2.y ? 1 : -1;
		int err = dx - dy;

		while (true) {
			drawaPoint({p1.x, p1.y}, c);
			
			if(p1 == p2) break;

			int e2 = 2*err;

			if (e2 >= dy) {
				err -= dy;
				p1.x += sx;
			}
			if (e2 <= dx) {
				err += dx;
				p1.y += sy;
			}

		}
	}
};