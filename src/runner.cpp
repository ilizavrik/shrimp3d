#include"runner.h"
#include"stdio.h"
#include"mesh.h"

void Runner::run() {

	
	Mesh fuck;
	fuck.worldCords = {0, 0, 1.5, 1};

	Mat4x4 proj = {
			{
			{a * f, 0, 0, 0},
			{0, f, 0, 0},
			{0, 0, z_far / (z_far - z_near), 1},
			{0, 0, -z_far * z_near / (z_far - z_near), 0}
			}
	};

	char h = 1;
	int ang = 0;
	while (true) {
		
		buf.clear();

		for (auto trg : fuck.triangles) {
			Vec4 shit[3];
			for (int i = 0; i < 3; ++i) {
				
				shit[i] = (proj*fuck.modelMat())(fuck.points[trg[i]]);
				shit[i] /= shit[i][3];
			}
			buf.drawatriangle(buf.fromNDC(shit[0]), buf.fromNDC(shit[1]), buf.fromNDC(shit[2]), 219);
		}

		buf.flip();
		
		//fuck.angs[0].setang(ang);
		fuck.angs[1].setang(ang);
		//fuck.angs[2].setang(ang);
		ang += 2.5;

		Sleep(8);
	}
}