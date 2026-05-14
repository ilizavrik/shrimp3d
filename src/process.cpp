#include"runner.h"
#include"linal.h"
#include"Mesh.h"


void Runner::update(Mesh& mesh, float& ang) {
	mesh.angs[mesh.y].setang(ang);
	ang += 5;
}

void Runner::render(Mesh& mesh) {
	for (auto trg : mesh.triangles) {
		Vec4 projected[3];
		for (int i = 0; i < 3; ++i) {

			projected[i] = (proj * mesh.modelMat())(mesh.points[trg[i]]);
			projected[i] /= projected[i][3];
		}
		buf.drawatriangle(
			buf.fromNDC(projected[0]),
			buf.fromNDC(projected[1]),
			buf.fromNDC(projected[2]), 219);
	}
}