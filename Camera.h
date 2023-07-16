#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL.h>
#include <eigen3/Eigen/Dense>
#include <vector>
#include <cmath>
#include "SDL2_gfxPrimitives.h"

#define CAMERA_DEFAULT_YAW_RADIANS 0
#define CAMERA_DEFAULT_PITCH_RADIANS 0

class Camera {
public:
	Camera(SDL_Renderer* renderer, SDL_Window* window, double fov, double aspect, double znear, double zfar,
		double initYaw, double initPitch, double initRoll,
		double initX, double initY, double initZ) :
		renderer(renderer), window(window), fov(fov), aspect(aspect), znear(znear), zfar(zfar),
		yaw(initYaw + CAMERA_DEFAULT_YAW_RADIANS), pitch(initPitch + CAMERA_DEFAULT_PITCH_RADIANS), roll(initRoll),
		x(initX), y(initY), z(initZ) {
		make_perspective();
	};
	void make_perspective();
	void render_polygon_full(Eigen::Vector4d center_pos, std::vector<Eigen::Vector4d>& world_coords_of_polygon,
		uint8_t r, uint8_t g, uint8_t b, uint8_t a);

	void setXYZ(double x, double y, double z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void setAngles(double yaw, double pitch, double roll) {
		this->yaw = yaw;
		this->pitch = pitch;
		this->roll = roll;
	}
	double getPitch() { return pitch; };
	double getYaw() { return yaw;  }
	double getRoll() { return roll; }

	double getX() { return x; }
	double getY() { return y; }
	double getZ() { return z; }
	//void render_polygon_wireframe(std::vector<Eigen::Vector4d>& world_coords_of_polygon);
private:
	Eigen::Vector4d world_to_screen(Eigen::Vector4d world_coords);
	Eigen::Vector4d rotate_vector(Eigen::Vector4d world_coords);
	Eigen::Vector4d translate_vector(Eigen::Vector4d world_coords,
		double tx, double ty, double tz);

	SDL_Renderer* renderer;
	SDL_Window* window;

	Eigen::Matrix4d projec_matrix;
	double fov;
	double aspect;
	double znear;
	double zfar;

	double yaw;
	double pitch;
	double roll;

	double x;
	double y;
	double z;
};

#endif // CAMERA_H