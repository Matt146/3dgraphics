#include "Camera.h"
#include <cmath>
#include <iostream>

void Camera::make_perspective_matrix() {
	Eigen::Matrix4d pm;
	pm << (1/aspect) * (1 / tan(fov / 2)), 0, 0, 0,
					0, 1 / tan(fov / 2), 0, 0,
					0, 0, zfar / (zfar - znear), ( - 1 * (zfar * znear)) / (zfar - znear),
					0, 0, 1, 0;
	projec_matrix = pm;
}

void Camera::make_view_matrix() {
	Eigen::Matrix4d view_matrix_1;
	view_matrix_1 << u(0), u(1), u(2), 0,
					v(0), v(1), v(2), 0,
					n(0), n(1), n(2), 0,
					0, 0, 0, 1;

	Eigen::Matrix4d view_matrix_2;
	view_matrix_2 << 1, 0, 0, -x,
					 0, 1, 0, -y,
					 0, 0, 1, -z,
					 0, 0, 0, 1;

	view_matrix = view_matrix_1 * view_matrix_2;
}

Eigen::Matrix4d Camera::make_model_matrix(const Object& object) {
	Eigen::Matrix4d model_matrix = make_translation_matrix(object.world_position(0), object.world_position(1),
		object.world_position(2)) * make_rotation_matrix(object.yaw, object.pitch, object.roll) * make_scale_matrix(object.scale_x, object.scale_y, object.scale_z);

	return model_matrix;
}

void Camera::setAngles(double yaw, double pitch, double roll) {
	this->yaw = yaw;
	this->pitch = pitch;
	this->roll = roll;
	Eigen::Quaterniond quat;
	quat = Eigen::AngleAxisd(roll, Eigen::Vector3d::UnitZ()) * Eigen::AngleAxisd(pitch, Eigen::Vector3d::UnitX()) * Eigen::AngleAxisd(yaw, Eigen::Vector3d::UnitY());
	n = quat * Eigen::Vector3d(0, 0, 1);
	v = quat * Eigen::Vector3d(0, 1, 0);
	u = quat * Eigen::Vector3d(1, 0, 0);
}

double distance(double x1, double y1, double z1, double x2, double y2, double z2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1-y2) + (z1 - z2) * (z1 - z2));
}

void Camera::render_object(const Object& obj) {
	for (size_t a = 0; a < obj.faces.size(); a++) {
		std::vector<Eigen::Vector4d> verts = obj.faces[a].vertices;

		// Create model/view/projection matrices
		Eigen::Matrix4d model_matrix = make_model_matrix(obj);
		make_view_matrix();
		make_perspective_matrix();

		int w; int h;
		SDL_GetWindowSize(window, &w, &h);

		std::cout << std::endl;
		for (size_t i = 0; i < verts.size(); i++) {
			// NEAR CLIPPING
			Eigen::Vector4d cur_coords; cur_coords << x, y, z, 1;
			Eigen::Vector4d plane_point = t_3d_to_4d(n) * znear + cur_coords;
			if (n.dot(t_4d_to_3d(((model_matrix * verts[i]) - plane_point))) < 0) {
				return;
			}

			verts[i] = projec_matrix * view_matrix * model_matrix * verts[i];
			// perspective divide
			if (verts[i][3] != 0) {
				verts[i](0) /= verts[i](3);
				verts[i](1) /= verts[i](3);
				verts[i](2) /= verts[i](3);
			}

			verts[i](0) = ((double)w/2) * (1 + verts[i](0));
			verts[i](1) = ((double)h/2) * (1 + verts[i](1));
		}

		// Render the object now
		//printf("\n\n");
		SDL_Vertex* verts_in_sdl_form = new SDL_Vertex[verts.size()];
		size_t cur_vert_idx = 0;
		for (size_t i = 0; i < verts.size(); i++) {
			verts_in_sdl_form[cur_vert_idx].position.x = verts[i](0);
			verts_in_sdl_form[cur_vert_idx].position.y = verts[i](1);
			verts_in_sdl_form[cur_vert_idx].color = obj.faces[a].color;
			verts_in_sdl_form[cur_vert_idx].tex_coord = {1, 1};
			//printf("(X,Y): (%f, %f)\n", verts_in_sdl_form[cur_vert_idx].position.x, verts_in_sdl_form[cur_vert_idx].position.y);
			cur_vert_idx += 1;
		}
		if (cur_vert_idx < 2) { return; }
		std::cout << SDL_RenderGeometry(renderer, obj.faces[a].texture, verts_in_sdl_form, cur_vert_idx, NULL, 0);
		delete [] verts_in_sdl_form;
	}
}