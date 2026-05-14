#include"runner.h"
#include"stdio.h"
#include"mesh.h"
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
void Runner::run() {
	
	Mesh fuck;
	fuck.worldCords = {0, 0, 2, 1};
	bool  a = fuck.loadFromObj("mlem.obj");
	float ang = 0;

	//PlaySound(TEXT("music.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	while (true) {
		buf.clear();

		update(fuck, ang);
		render(fuck);

		buf.flip();

		printf("\r%d", a);
		//Sleep(8);
	}
}