#ifndef UTILS_H
#define UTILS_H

#include <eigen3/Eigen/Dense>
#include <vector>

struct Face {
    std::vector<Eigen::Vector4d> vertices;
    SDL_Texture* texture = NULL;
    SDL_Color color = {255, 0, 0, 255};
};

struct Object {
    std::vector<Face> faces; // vertices in local coordinates
    Eigen::Vector4d world_position; // position of the object in world space
    double yaw;
    double pitch;
    double roll;

    double scale_x;
    double scale_y;
    double scale_z;
};

inline Eigen::Vector4d rotate_vector(Eigen::Vector4d vec, double yaw, double pitch, double roll) {
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

inline Eigen::Matrix4d make_rotation_matrix(double yaw, double pitch, double roll) {
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

inline Eigen::Vector4d translate_vector(Eigen::Vector4d vec,
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

inline Eigen::Matrix4d make_translation_matrix(double tx, double ty, double tz) {
    Eigen::Matrix4d translationMatrix;
	translationMatrix << 1, 0, 0, tx,
		0, 1, 0, ty,
		0, 0, 1, tz,
		0, 0, 0, 1;

    return translationMatrix;
}

inline Eigen::Vector4d scale_vector(Eigen::Vector4d vec, double scale_x, double scale_y, double scale_z) {
    Eigen::Vector4d result;
    Eigen::Matrix4d scaleMatrix;
    scaleMatrix << scale_x, 0, 0, 0,
                    0, scale_y, 0, 0,
                    0, 0, scale_z, 0,
                    0, 0, 0, 1;
    result = scaleMatrix * vec;
    return result;
}

inline Eigen::Matrix4d make_scale_matrix(double scale_x, double scale_y, double scale_z) {
    Eigen::Matrix4d scaleMatrix;
    scaleMatrix << scale_x, 0, 0, 0,
                    0, scale_y, 0, 0,
                    0, 0, scale_z, 0,
                    0, 0, 0, 1;

    return scaleMatrix;
}

inline Eigen::Vector4d t_3d_to_4d(const Eigen::Vector3d& t3) {
    Eigen::Vector4d result;
    result << t3(0), t3(1), t3(2), 1;
    return result;
}

inline Eigen::Vector3d t_4d_to_3d(const Eigen::Vector4d& t4) {
    Eigen::Vector3d result;
    result << t4(0), t4(1), t4(2);
    return result;
}

// https://en.wikipedia.org/wiki/Rodrigues'_rotation_formula#Matrix_notation
// vector = v, k = axis, theta = angle
inline Eigen::Vector3d rotate_vector_around_axis(Eigen::Vector3d v, Eigen::Vector3d k, double theta) {
    Eigen::Vector3d result;
	k /= k.norm();
    result = (v*cos(theta)) + (k.cross(v)*sin(theta)) + (k*(k.dot(v))*(1-cos(theta)));

    return result;
}

inline SDL_Texture* load_texture(SDL_Renderer* renderer, std::string path )
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s!", path.c_str());
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

#endif //UTILS_H