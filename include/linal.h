#pragma once
#pragma once
#include<math.h>
const float PI = 3.141592653589793;
inline float toRad(float deg) {
	return deg * PI / 180.0f;
}

struct TrigAng {
	float sn, cs;

	void setang(float a) {
		sn = sin(toRad(a));
		cs = cos(toRad(a));
	}
};

struct Vec4 {
	float cords[4] = { 0, 0, 0, 0 };

	Vec4() = default;

	float& operator[](int i) {
		return cords[i];
	}

	friend Vec4 operator+(Vec4 v1, Vec4 v2) {
		Vec4 res;
		for (int i = 0; i < 4; ++i) {
			res[i] = v1[i] + v2[i];
		}
		return res;
	}
	friend Vec4 operator-(Vec4 v1, Vec4 v2) {
		Vec4 res;
		for (int i = 0; i < 4; ++i) {
			res[i] = v1[i] - v2[i];
		}
		return res;
	}
	friend Vec4 operator*(float f, Vec4 v) {
		Vec4 res;
		for (int i = 0; i < 4; ++i) {
			res[i] = v[i] * f;
		}
		return res;
	}
	friend Vec4 operator/(Vec4 v, float f) {
		Vec4 res;
		for (int i = 0; i < 4; ++i) {
			res[i] = v[i] / f;
		}
		return res;
	}
	void operator+=(Vec4 v) {
		for (int i = 0; i < 4; ++i) {
			cords[i] += v[i];
		}
	}
	void operator-=(Vec4 v) {
		for (int i = 0; i < 4; ++i) {
			cords[i] -= v[i];
		}
	}
	void operator*=(float f) {
		for (int i = 0; i < 4; ++i) {
			cords[i] *= f;
		}
	}
	void operator/=(float f) {
		for (int i = 0; i < 4; ++i) {
			cords[i] /= f;
		}
	}
	friend Vec4 operator-(Vec4 v) {
		return -1 * v;
	}
	friend float dotProdV3(Vec4 v1, Vec4 v2) {
		float res = 0;
		for (int i = 0; i < 3; ++i) {
			res += v1[i] * v2[i];
		}
		return res;
	}
	friend Vec4 crossProdV3(Vec4 v1, Vec4 v2) {
		Vec4 res;
		res[0] = v1[1] * v2[2] - v1[2] * v2[1];
		res[1] = v1[2] * v2[0] - v1[0] * v2[2];
		res[2] = v1[0] * v2[1] - v1[1] * v2[0];
		res[3] = 0;
		return res;
	}
	float len3D() {
		float res = 0;
		for (int i = 0; i < 3; ++i) {
			res += cords[i] * cords[i];
		}
		return sqrt(res);
	}
	void norm() {
		*this /= len3D();
	}
};

struct Mat4x4 {
	Vec4 collums[4] = {
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}
	};

	Mat4x4() = default;

	float& operator()(int j, int i) {
		return collums[j][i];
	}
	Vec4 operator()(Vec4 v) {
		Vec4 res;
		for (int i = 0; i < 4; ++i) {
			res += v[i] * collums[i];
		}
		return res;
	}
	friend Mat4x4 operator*(Mat4x4 m1, Mat4x4 m2) {
		Mat4x4 res;
		for (int i = 0; i < 4; ++i) {
			res.collums[i] = m1(m2.collums[i]);
		}
		return res;
	}
};