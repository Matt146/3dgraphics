#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL.h>
#include <eigen3/Eigen/Dense>
#include <vector>
#include <cmath>
#include "SDL2_gfxPrimitives.h"
#include "World.h"

#define CAMERA_DEFAULT_YAW_RADIANS 0
#define CAMERA_DEFAULT_PITCH_RADIANS 0

class Camera {
public:
	Camera(SDL_Renderer* renderer, SDL_Window* window, double fov, double aspect, double znear, double zfar,
		Eigen::Vector3d initN, Eigen::Vector3d initV,
		double initX, double initY, double initZ) :
		renderer(renderer), window(window), fov(fov), aspect(aspect), znear(znear), zfar(zfar), n(initN), v(initV), u(n.cross(v)),
		x(initX), y(initY), z(initZ) {
		make_perspective_matrix();
		setAngles(0, 0, 0);
		make_view_matrix();
	};

	Eigen::Matrix4d make_model_matrix(const Object& object);
	void make_perspective_matrix();
	void make_view_matrix();

	void render_object(const Object& object);

	void setXYZ(double x, double y, double z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void setAngles(double yaw, double pitch, double roll);

	double getYaw() { return yaw; }
	double getPitch() { return pitch; }
	double getRoll() { return roll; }

	double getX() { return x; }
	double getY() { return y; }
	double getZ() { return z; }\

	Eigen::Vector3d get_u() { return u; }
	Eigen::Vector3d get_v() { return v; }
	Eigen::Vector3d get_n() { return n; }
	//void render_polygon_wireframe(std::vector<Eigen::Vector4d>& world_coords_of_polygon);
private:
	Eigen::Vector4d world_to_screen(Eigen::Vector4d world_coords);
	//Eigen::Vector4d rotate_vector(Eigen::Vector4d world_coords);
	Eigen::Vector4d translate_vector(Eigen::Vector4d world_coords,
		double tx, double ty, double tz);

	SDL_Renderer* renderer;
	SDL_Window* window;

	Eigen::Matrix4d projec_matrix;
	Eigen::Matrix4d view_matrix;

	double fov;
	double aspect;
	double znear;
	double zfar;

	double x;
	double y;
	double z;

	Eigen::Vector3d u;
	Eigen::Vector3d v;
	Eigen::Vector3d n;

	double yaw = 0.0;
	double pitch = 0.0;
	double roll = 0.0;
};

#endif // CAMERA_H