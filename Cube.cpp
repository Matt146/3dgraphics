#include "Cube.h"

// From: https://www.mbsoftworks.sk/tutorials/opengl4/004-entering-third-dimension/model_space.png
Cube::Cube(std::map<size_t, SDL_Texture*> cube_face_textures,
        std::map<size_t, SDL_Color> cube_face_colors,
        Eigen::Vector4d center_pos, double size) {

        constructorBody(cube_face_textures, cube_face_colors,
    center_pos, size);
}

Cube::Cube(SDL_Texture* cube_face_texture,
        SDL_Color cube_face_color,
        Eigen::Vector4d center_pos, double size) {

    std::map<size_t, SDL_Texture*> cube_face_textures;
    std::map<size_t, SDL_Color> cube_face_colors;

    for (size_t i = 0; i < 6; i++) {
        cube_face_textures.insert({i, cube_face_texture});
    }

    for (size_t i = 0; i < 6; i++) {
        cube_face_colors.insert({i, cube_face_color});
    }

    constructorBody(cube_face_textures, cube_face_colors,
    center_pos, size);
}

void Cube::constructorBody(std::map<size_t, SDL_Texture*> cube_face_textures,
        std::map<size_t, SDL_Color> cube_face_colors,
        Eigen::Vector4d center_pos, double size) {
    Eigen::Vector4d v1;
    Eigen::Vector4d v2;
    Eigen::Vector4d v3;
    Eigen::Vector4d v4;
    Eigen::Vector4d v5;
    Eigen::Vector4d v6;

    // Front face
    Face front;
    if (cube_face_colors.find(0) != cube_face_colors.end()) {
        front.color = cube_face_colors[0];
    }
    if (cube_face_textures.find(0) != cube_face_textures.end()) {
        front.texture = cube_face_textures[0];
    }
    std::vector<Eigen::Vector4d> front_verts;
    v1 << -0.5, 0.5, 0.5, 1;
    v2 << 0.5, 0.5, 0.5, 1;
    v3 << 0.5, -0.5, 0.5, 1;
    v4 << -0.5, -0.5, 0.5, 1;
    v5 << -0.5, 0.5, 0.5, 1;
    v6 << 0.5, -0.5, 0.5, 1;
    front_verts.push_back(v1);
    front_verts.push_back(v2);
    front_verts.push_back(v3);
    front_verts.push_back(v4);
    front_verts.push_back(v5);
    front_verts.push_back(v6);
    front.vertices = front_verts;

    // Back face
    Face back;
    if (cube_face_colors.find(1) != cube_face_colors.end()) {
        back.color = cube_face_colors[1];
    }
    if (cube_face_textures.find(1) != cube_face_textures.end()) {
        back.texture = cube_face_textures[1];
    }
    std::vector<Eigen::Vector4d> back_verts;
    v1 << -0.5, 0.5, -0.5, 1;
    v2 << 0.5, 0.5, -0.5, 1;
    v3 << 0.5, -0.5, -0.5, 1;
    v4 << -0.5, -0.5, -0.5, 1;
    v5 << -0.5, 0.5, -0.5, 1;
    v6 << 0.5, -0.5, -0.5, 1;
    back_verts.push_back(v1);
    back_verts.push_back(v2);
    back_verts.push_back(v3);
    back_verts.push_back(v4);
    back_verts.push_back(v5);
    back_verts.push_back(v6);
    back.vertices = back_verts;

    // Left face
    Face left;
    if (cube_face_colors.find(2) != cube_face_colors.end()) {
        left.color = cube_face_colors[2];
    }
    if (cube_face_textures.find(2) != cube_face_textures.end()) {
        left.texture = cube_face_textures[2];
    }
    std::vector<Eigen::Vector4d> left_verts;
    v1 << -0.5, 0.5, 0.5, 1;
    v2 << -0.5, 0.5, -0.5, 1;
    v3 << -0.5, -0.5, -0.5, 1;
    v4 << -0.5, -0.5, 0.5, 1;
    v5 << -0.5, 0.5, 0.5, 1;
    v6 << -0.5, -0.5, -0.5, 1;
    left_verts.push_back(v1);
    left_verts.push_back(v2);
    left_verts.push_back(v3);
    left_verts.push_back(v4);
    left_verts.push_back(v5);
    left_verts.push_back(v6);
    left.vertices = left_verts;

    // right face
    Face right;
    if (cube_face_colors.find(4) != cube_face_colors.end()) {
        right.color = cube_face_colors[4];
    }
    if (cube_face_textures.find(4) != cube_face_textures.end()) {
        right.texture = cube_face_textures[4];
    }
    std::vector<Eigen::Vector4d> right_verts;
    v1 << 0.5, 0.5, 0.5, 1;
    v2 << 0.5, 0.5, -0.5, 1;
    v3 << 0.5, -0.5, -0.5, 1;
    v4 << 0.5, -0.5, 0.5, 1;
    v5 << 0.5, 0.5, 0.5, 1;
    v6 << 0.5, -0.5, -0.5, 1;
    right_verts.push_back(v1);
    right_verts.push_back(v2);
    right_verts.push_back(v3);
    right_verts.push_back(v4);
    right_verts.push_back(v5);
    right_verts.push_back(v6);
    right.vertices = right_verts;

    // down face
    Face down;
    if (cube_face_colors.find(3) != cube_face_colors.end()) {
        down.color = cube_face_colors[3];
    }
    if (cube_face_textures.find(3) != cube_face_textures.end()) {
        down.texture = cube_face_textures[3];
    }
    std::vector<Eigen::Vector4d> down_verts;
    v1 << -0.5, -0.5, 0.5, 1;
    v2 << -0.5, -0.5, -0.5, 1;
    v3 << 0.5, -0.5, -0.5, 1;
    v4 << 0.5, -0.5, 0.5, 1;
    v5 << -0.5, -0.5, 0.5, 1;
    v6 << 0.5, -0.5, -0.5, 1;
    down_verts.push_back(v1);
    down_verts.push_back(v2);
    down_verts.push_back(v3);
    down_verts.push_back(v4);
    down_verts.push_back(v5);
    down_verts.push_back(v6);
    down.vertices = down_verts;

    // up face
    Face up;
    if (cube_face_colors.find(5) != cube_face_colors.end()) {
        up.color = cube_face_colors[5];
    }
    if (cube_face_textures.find(5) != cube_face_textures.end()) {
        up.texture = cube_face_textures[5];
    }
    std::vector<Eigen::Vector4d> up_verts;
    v1 << -0.5, 0.5, 0.5, 1;
    v2 << -0.5, 0.5, -0.5, 1;
    v3 << 0.5, 0.5, -0.5, 1;
    v4 << 0.5, 0.5, 0.5, 1;
    v5 << -0.5, 0.5, 0.5, 1;
    v6 << 0.5, 0.5, -0.5, 1;
    up_verts.push_back(v1);
    up_verts.push_back(v2);
    up_verts.push_back(v3);
    up_verts.push_back(v4);
    up_verts.push_back(v5);
    up_verts.push_back(v6);
    up.vertices = up_verts;

    std::vector<Face> faces;
    faces.push_back(front);
    faces.push_back(back);
    faces.push_back(left);
    faces.push_back(right);
    faces.push_back(down);
    faces.push_back(up);

    o.faces = faces;
    o.scale_x = size;
    o.scale_y = size;
    o.scale_z = size;

    o.world_position = center_pos;
}