#pragma once
#include"linal.h"
#include"math.h"
#include<vector>
#include<array>
#include<map>
#include<fstream>
#include <sstream>
#include<string>
using std::array; 
using std::vector;
using std::string;
using std::ifstream;
struct Mesh {
	Vec4 worldCords;
	vector<Vec4> points;
	vector<array<int, 3>> triangles;
	TrigAng angs[3];
	enum{
		x,
		y,
		z
	};
	//default cube
	Mesh() {
	
		points = {
			//._ .'
			{0.5, 0.5, 0.5, 1},
			{0.5, 0.5, -0.5, 1},
			{0.5, -0.5, 0.5, 1},
			{0.5, -0.5, -0.5, 1},
			{-0.5, 0.5, 0.5, 1},
			{-0.5, 0.5, -0.5, 1},
			{-0.5, -0.5, 0.5, 1},
			{-0.5, -0.5, -0.5, 1},
		};
		triangles = {
			//front
			{0, 2, 3},
			{0, 3, 1},
			//back
			{4, 5, 7},
			{4, 7, 6},
			//top
			{0, 1, 5},
			{0, 5, 4},
			//bottom
			{2, 6, 7},
			{2, 7, 3},
			//right
			{0, 4, 6},
			{0, 6, 2},
			//left	
			{1, 3, 7},
			{1, 7, 5}

		};

		angs[x].setang(0);
		angs[y].setang(0);
		angs[z].setang(0);
	}

	//modelMatrix
	Mat4x4 modelMat() {
		Mat4x4 rx, ry, rz,  T;

		rx = {
			{
			{1, 0, 0, 0},
			{0, angs[x].cs, angs[x].sn, 0},
			{0, -angs[x].sn,angs[x].cs, 0},
			{0, 0, 0, 1}
			}
		};
		ry = {
			{
			{angs[y].cs, 0, -angs[y].sn, 0},
			{0, 1, 0, 0},
			{angs[y].sn, 0, angs[y].cs, 0},
			{0, 0, 0, 1}
			}
		};
		rz = {
			{
			{angs[z].cs, angs[z].sn, 0, 0},
			{-angs[z].sn, angs[z].cs, 0, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 1}
			}
		};

		T(3, 0) = worldCords[0];
		T(3, 1) = worldCords[1];
		T(3, 2) = worldCords[2];

		return T * rz * ry * rx;
	}

	
	bool loadFromObj(string filename) {
		ifstream file(filename);
		if (!file.is_open()) return false;

		
		points.clear();
		triangles.clear();

		string line;
		while (getline(file, line)) {
			std::stringstream ss(line);
			string prefix;
			ss >> prefix;

			if (prefix == "v") {
				Vec4 v;
				v[3] = 1.0f;
				ss >> v[0] >> v[1] >> v[2];
				points.push_back(v);
			}
			else if (prefix == "f") {
				array<int, 3> face;
				for (int i = 0; i < 3; ++i) {
					string vertexData;
					ss >> vertexData;

					size_t firstSlash = vertexData.find('/');
					if (firstSlash != string::npos) {
						face[i] = std::stoi(vertexData.substr(0, firstSlash)) - 1;
					}
					else {
						face[i] = std::stoi(vertexData) - 1;
					}
				}
				triangles.push_back(face);
			}
		}

		file.close();
		return true;
	}
};
