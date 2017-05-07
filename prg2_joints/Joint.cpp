#include "Joint.h"

float Joint::getAngle(const Joint& j1, const Joint& j2, const Joint& j3) {
	std::array<float, 3> vect1 = {j1.x - j2.x, j1.y - j2.y, j1.z - j2.z};
	std::array<float, 3> vect2 = {j3.x - j2.x, j3.y - j2.y, j3.z - j2.z};

	float v1delta = sqrt(vect1[0] * vect1[0] + vect1[1] * vect1[1] + vect1[2] * vect1[2]);
	float v2delta = sqrt(vect2[0] * vect2[0] + vect2[1] * vect2[1] + vect2[2] * vect2[2]);

	std::array<float, 3> v1norm = {vect1[0] / v1delta, vect1[1] / v1delta, vect1[2] / v1delta};
	std::array<float, 3> v2norm = {vect2[0] / v2delta, vect2[1] / v2delta, vect2[2] / v2delta};

	return acos(v1norm[0] * v2norm[0] + v1norm[1] * v2norm[1] + v1norm[2] * v2norm[2]);
}