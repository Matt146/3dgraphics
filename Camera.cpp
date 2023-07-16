#include "Camera.h"
#include <cmath>
#include <iostream>

void Camera::make_perspective() {
	projec_matrix << aspect * (1 / tan(fov / 2)), 0, 0, 0,
					0, 1 / tan(fov / 2), 0, 0,
					0, 0, zfar / (zfar - znear), ( - 1 * (zfar * znear)) / (zfar - znear),
					0, 0, 1, 0;
}

/*Returns a vector <x, y, z, w> in screenspace from a vector given in world coords*/
Eigen::Vector4d Camera::world_to_screen(Eigen::Vector4d world_coords) {\
	Eigen::Vector4d result = world_coords;

	result = projec_matrix * result;
	printf("Post-projection: (%lf, %lf, %lf, %lf)\n", result(0), result(1), result(2), result(3));

	if (result(3) != 0) {
		result(0) /= result(3);
		result(1) /= result(3);
		result(2) /= result(3);
	}

	printf("Post-prespective-divide coords: (%lf, %lf, %lf, %lf)\n", result(0), result(1), result(2), result(3));


	int w;
	int h;
	SDL_GetWindowSize(window, &w, &h);

	result(0) += ((double)w / 2);
	result(1) = ((double)h / 2) - result(1);

	printf("Final screen coords: (%lf, %lf, %lf, %lf)\n", result(0), result(1), result(2), result(3));

	return result;
}

Eigen::Vector4d Camera::rotate_vector(Eigen::Vector4d world_coords) {
	Eigen::Vector4d result;

	double oldZ = world_coords(2);

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

	result = (rollMatrix * (pitchMatrix * (yawMatrix * world_coords)));

	result(2) = oldZ;
	result(1) -= znear * cos(yaw);
	result(0) -= znear * sin(pitch);

	return result;
}

Eigen::Vector4d Camera::translate_vector(Eigen::Vector4d world_coords,
									double tx, double ty, double tz) {
	Eigen::Vector4d result;

	Eigen::Matrix4d translationMatrix;
	translationMatrix << 1, 0, 0, tx,
		0, 1, 0, ty,
		0, 0, 1, tz,
		0, 0, 0, 1;

	result = translationMatrix * world_coords;
	return result;
}

double distance(double x1, double y1, double z1, double x2, double y2, double z2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1-y2) + (z1 - z2) * (z1 - z2));
}

void Camera::render_polygon_full(Eigen::Vector4d center_pos,
	std::vector<Eigen::Vector4d>& world_coords_of_polygon,
	uint8_t r, uint8_t g, uint8_t b, uint8_t a) {

	int w;
	int h;
	SDL_GetWindowSize(window, &w, &h);

	std::vector<SDL_Vertex> verts;
	for (size_t i = 0; i < world_coords_of_polygon.size(); i++) {
		std::cout << std::endl << std::endl;
		Eigen::Vector4d vec_to_render = world_coords_of_polygon[i];
		printf("Yaw, Pitch, Roll: (%lf, %lf, %lf)\n", yaw, pitch, roll);
		printf("XYZ: (%lf, %lf, %lf)\n", x, y, z);
		printf("Word coords: (%lf, %lf, %lf, %lf)\n", vec_to_render(0), vec_to_render(1), vec_to_render(2), vec_to_render(3));

		/*vec_to_render = rotate_vector(vec_to_render);
		vec_to_render = translate_vector(vec_to_render, x, y, z);*/
		/*vec_to_render = translate_vector(vec_to_render, -center_pos(0),
			-center_pos(1),
			-center_pos(2));
		vec_to_render = rotate_vector(vec_to_render);
		vec_to_render = translate_vector(vec_to_render, center_pos(0),
			center_pos(1),
			center_pos(2));*/
		/*double x1 = vec_to_render(0) - center_pos(0);
		double y1 = vec_to_render(1) - center_pos(1);
		double z1 = vec_to_render(2) - center_pos(2);
		center_pos = rotate_vector(center_pos);*/
		/*vec_to_render = translate_vector(vec_to_render, center_pos(0),
			center_pos(1),
			center_pos(2));*/
		/*vec_to_render(0) = 0;
		vec_to_render(1) = 0;
		vec_to_render(2) = 0;
		vec_to_render(0) = center_pos(0) + x1;
		vec_to_render(1) = center_pos(1) + y1;
		vec_to_render(2) = center_pos(2) + z1;*/
		vec_to_render = rotate_vector(vec_to_render);
		printf("Post-rotation: (%lf, %lf, %lf, %lf)\n", vec_to_render(0), vec_to_render(1), vec_to_render(2), vec_to_render(3));

		vec_to_render = translate_vector(vec_to_render, x, y, z);
		printf("Post-translation: (%lf, %lf, %lf, %lf)\n", vec_to_render(0), vec_to_render(1), vec_to_render(2), vec_to_render(3));

		vec_to_render = world_to_screen(vec_to_render);
		verts.push_back(
			{ SDL_FPoint{(float)vec_to_render(0) , (float)vec_to_render(1)},
			  SDL_Color{r, g, b, a},
			  SDL_FPoint{0}, }
		);

		/*Eigen::Vector4d vec_to_render = world_coords_of_polygon[i];
		vec_to_render = world_to_screen(vec_to_render);
		// Translate centroid to to origin
		vec_to_render = translate_vector(vec_to_render, -center_pos(0),
			-center_pos(1),
			-center_pos(2));
		// Rotate translated vector
		vec_to_render = rotate_vector(vec_to_render);
		// Translate centroid back from center to where it should be
		vec_to_render = translate_vector(vec_to_render, center_pos(0),
			center_pos(1),
			center_pos(2));
		// Now translate the rotated triangle to where it should be in world to
		// be correctly displayed on the screen
		vec_to_render = translate_vector(vec_to_render, x, y, z);
		vec_to_render = world_to_screen(vec_to_render);
		verts.push_back(
			{ SDL_FPoint{(float)vec_to_render(0), (float)vec_to_render(1)},
			  SDL_Color{r, g, b, a},
			  SDL_FPoint{0}, }
		);*/
	}

	/*std::cout << "===========" << std::endl;
	for (size_t i = 0; i < world_coords_of_polygon.size(); i++) {
		std::cout << "[" << i + 1 << "/" << world_coords_of_polygon.size() << "]" << std::endl;
		std::cout << "Position: ";
		std::cout << verts[i].position.x << ", ";
		std::cout << verts[i].position.y << std::endl;
		std::cout << "Color: ";
		std::cout << (int)verts[i].color.r << ", ";
		std::cout << (int)verts[i].color.g << ", ";
		std::cout << (int)verts[i].color.b << ", ";
		std::cout << (int)verts[i].color.a << std::endl;
		std::cout << "Tex Coord: ";
		std::cout << verts[i].tex_coord.x << ",";
		std::cout << verts[i].tex_coord.y << std::endl;
	}*/

	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderGeometry(renderer, nullptr, verts.data(), verts.size(), nullptr, 0);
	SDL_Rect cross = SDL_Rect{x: w/2 - (10/2), y: w/2 - (10/2), w: 10, h: 10};
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &cross);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	//std::cout << "SDL_RenderGeometry Status: " << SDL_RenderGeometry(renderer, nullptr, verts.data(), verts.size(), nullptr, 0) << std::endl;
}