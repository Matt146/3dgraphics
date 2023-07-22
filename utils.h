#ifndef UTILS_H
#define UTILS_H

#include <eigen3/Eigen/Dense>

Eigen::Vector4d rotate_vector(Eigen::Vector4d vec, double yaw, double pitch, double roll) {
	Eigen::Vector4d result;

	double oldZ = vec(2);

	Eigen::Matrix4d yawMatrix;
	yawMatrix << cos(roll), -sin(roll), 0, 0,
		sin(roll), cos(roll), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1;

	Eigen::Matrix4d pitchMatrix;
	pitchMatrix << cos(pitch), 0, sin(pitch), 0,
		0, 1, 0, 0,
		-sin(pitch), 0, cos(pitch), 0,
		0, 0, 0, 1;

	Eigen::Matrix4d rollMatrix;
	rollMatrix << 1, 0, 0, 0,
		0, cos(yaw), -sin(yaw), 0,
		0, sin(yaw), cos(yaw), 0,
		0, 0, 0, 1;

	result = (rollMatrix * (pitchMatrix * (yawMatrix * vec)));

	/*result(2) = oldZ;
	result(1) -= znear * cos(yaw);
	result(0) -= znear * sin(pitch);*/

	return result;
}

Eigen::Matrix4d make_rotation_matrix(double yaw, double pitch, double roll) {
    Eigen::Matrix4d yawMatrix;
	yawMatrix << cos(roll), -sin(roll), 0, 0,
		sin(roll), cos(roll), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1;

	Eigen::Matrix4d pitchMatrix;
	pitchMatrix << cos(pitch), 0, sin(pitch), 0,
		0, 1, 0, 0,
		-sin(pitch), 0, cos(pitch), 0,
		0, 0, 0, 1;

	Eigen::Matrix4d rollMatrix;
	rollMatrix << 1, 0, 0, 0,
		0, cos(yaw), -sin(yaw), 0,
		0, sin(yaw), cos(yaw), 0,
		0, 0, 0, 1;

	Eigen::Matrix4d rotMatrix = (rollMatrix * (pitchMatrix * (yawMatrix)));
    return rotMatrix;
}

Eigen::Vector4d translate_vector(Eigen::Vector4d vec,
									double tx, double ty, double tz) {
	Eigen::Vector4d result;

	Eigen::Matrix4d translationMatrix;
	translationMatrix << 1, 0, 0, tx,
		0, 1, 0, ty,
		0, 0, 1, tz,
		0, 0, 0, 1;

	result = translationMatrix * vec;
	return result;
}

Eigen::Matrix4d make_translation_matrix(double tx, double ty, double tz) {
    Eigen::Matrix4d translationMatrix;
	translationMatrix << 1, 0, 0, tx,
		0, 1, 0, ty,
		0, 0, 1, tz,
		0, 0, 0, 1;

    return translationMatrix;
}

Eigen::Vector4d scale_vector(Eigen::Vector4d vec, double scale_x, double scale_y, double scale_z) {
    Eigen::Vector4d result;
    Eigen::Matrix4d scaleMatrix;
    scaleMatrix << scale_x, 0, 0, 0,
                    0, scale_y, 0, 0,
                    0, 0, scale_z, 0,
                    0, 0, 0, 1;
    result = scaleMatrix * vec;
    return result;
}

Eigen::Matrix4d make_scale_matrix(double scale_x, double scale_y, double scale_z) {
    Eigen::Matrix4d scaleMatrix;
    scaleMatrix << scale_x, 0, 0, 0,
                    0, scale_y, 0, 0,
                    0, 0, scale_z, 0,
                    0, 0, 0, 1;

    return scaleMatrix;
}

Eigen::Vector4d t_3d_to_4d(const Eigen::Vector3d& t3) {
    Eigen::Vector4d result;
    result << t3(0), t3(1), t3(2), 1;
    return result;
}

Eigen::Vector3d t_4d_to_3d(const Eigen::Vector4d& t4) {
    Eigen::Vector3d result;
    result << t4(0), t4(1), t4(2);
    return result;
}

// https://en.wikipedia.org/wiki/Rodrigues'_rotation_formula#Matrix_notation
// vector = v, k = axis, theta = angle
Eigen::Vector3d rotate_vector_around_axis(Eigen::Vector3d v, Eigen::Vector3d k, double theta) {
    Eigen::Vector3d result;
	k /= k.norm();
    result = (v*cos(theta)) + (k.cross(v)*sin(theta)) + (k*(k.dot(v))*(1-cos(theta)));

    return result;
}

#endif //UTILS_H