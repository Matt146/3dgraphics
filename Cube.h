#ifndef CUBE_H
#define CUBE_H

#include <eigen3/Eigen/Dense>
#include <vector>
#include <SDL2/SDL.h>
#include <map>
#include "utils.h"

const SDL_Color cube_default_face_color = {52, 235, 5, 255};
//const SDL_Texture* cube_default_texture = NULL;

enum {
    CUBE_FRONT,
    CUBE_BACK,
    CUBE_LEFT,
    CUBE_RIGHT,
    CUBE_DOWN,
    CUBE_UP
};

class Cube {
private:
    Object o;
    void constructorBody(std::map<size_t, SDL_Texture*> cube_face_textures,
        std::map<size_t, SDL_Color> cube_face_colors,
        Eigen::Vector4d center_pos, double size);
public:
    Cube(std::map<size_t, SDL_Texture*> cube_face_textures,
        std::map<size_t, SDL_Color> cube_face_colors,
        Eigen::Vector4d center_pos, double size);
    Cube(SDL_Texture* cube_face_texture,
        SDL_Color cube_face_color,
        Eigen::Vector4d center_pos, double size);
    Object getCubeObject() {return o;}
};

#endif // CUBE_H