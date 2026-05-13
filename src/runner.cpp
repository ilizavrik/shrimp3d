#include"runner.h"
#include"stdio.h"
#include"mesh.h"

void Runner::run() {
	
	Mesh fuck;
	fuck.worldCords = {0, 0, 2, 1};
	float ang = 0;

	while (true) {
		
		buf.clear();

		update(fuck, ang);
		render(fuck);

		buf.flip();

		//Sleep(8);
	}
}