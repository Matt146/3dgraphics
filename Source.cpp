#include <iostream>
#include <ctime>
#include <SDL2/SDL.h>
#include "Camera.h"
#include <cmath>
#undef main

#define MIN_TURN_ANGLE (1 / (M_PI * 5))
#define MIN_MOVE_AMT 10

int main() {
    srand(time(NULL));

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("3D",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640*2,
        640*2,
        SDL_WINDOW_OPENGL);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    int w; int h; SDL_GetWindowSize(window, &w, &h);
    Camera c(renderer, window, 95, (double)h / w, 1, 500, 0, 0, 0, 0, 0, 0);
    Eigen::Vector4d p1(623, 67, -20, 1);
    Eigen::Vector4d p2(351, 558, -20, 1);
    Eigen::Vector4d p3(861, 581, -20, 1);
    std::vector<Eigen::Vector4d> triangle;
    Eigen::Vector4d triangle_centroid;
    triangle_centroid << 612, 402, -20, 1;
    triangle.push_back(p1);
    triangle.push_back(p2);
    triangle.push_back(p3);

    std::vector<Eigen::Vector4d> triangle_REF;
    Eigen::Vector4d triangle_REF_centroid;
    triangle_REF_centroid << 512, 402, -40, 1;
    Eigen::Vector4d p1_REF(523, 67, -40, 1);
    Eigen::Vector4d p2_REF(251, 558, -40, 1);
    Eigen::Vector4d p3_REF(761, 581, -40, 1);
    triangle_REF.push_back(p1_REF);
    triangle_REF.push_back(p2_REF);
    triangle_REF.push_back(p3_REF);

    // Stars
    int star_distance = 200;
    int star_cnt = 500;
    int star_max_dx = 10;
    std::vector<std::vector<Eigen::Vector4d>> stars;
    for (int i = 0; i < star_cnt; i++) {
        int star_dx = rand() % star_max_dx;
        int star_dy = rand() % star_max_dx;
        int star_x;
        if (rand() % 10 > 5) {
            star_x = rand() % star_distance;
        }
        else {
            star_x = (-1) * (rand() % star_distance);
        }
        int star_y;
        if (rand() % 10 > 5) {
            star_y = rand() % star_distance;
        }
        else {
            star_y = (-1) * (rand() % star_distance);
        }
        int star_z;
        if (rand() % 10 > 5) {
            star_z = rand() % star_distance;
        }
        else {
            star_z = (-1) * (rand() % star_distance);
        }

        std::vector<Eigen::Vector4d> star;
        Eigen::Vector4d star_p1; star_p1 << star_x, star_y, star_z, 1;
        Eigen::Vector4d star_p2; star_p2 << star_x + star_dx, star_y, star_z, 1;
        Eigen::Vector4d star_p3; star_p3 << star_x, star_y + star_dy, star_z, 1;
        star.push_back(star_p1); star.push_back(star_p2); star.push_back(star_p3);
        stars.push_back(star);
    }

    SDL_Event ev;
    bool running = true;
    bool first_time = true;
    while (running) {
        while (SDL_PollEvent(&ev)) {
            switch (ev.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                switch (ev.key.keysym.sym) {
                case SDLK_LEFT:
                    c.setAngles(c.getYaw() - MIN_TURN_ANGLE, c.getPitch(), c.getRoll());
                    break;
                case SDLK_RIGHT:
                    c.setAngles(c.getYaw() + MIN_TURN_ANGLE, c.getPitch(), c.getRoll());
                    break;
                case SDLK_UP:
                    c.setAngles(c.getYaw(), c.getPitch() + MIN_TURN_ANGLE, c.getRoll());
                    break;
                case SDLK_DOWN:
                    c.setAngles(c.getYaw(), c.getPitch() - MIN_TURN_ANGLE, c.getRoll());
                    break;
                case SDLK_SPACE:
                    c.setAngles(c.getYaw(), c.getPitch(), c.getRoll() + MIN_TURN_ANGLE);
                    break;
                case SDLK_w:
                    c.setXYZ(c.getX(), c.getY(), c.getZ() + MIN_MOVE_AMT);
                    break;
                case SDLK_s:
                    c.setXYZ(c.getX(), c.getY(), c.getZ() - MIN_MOVE_AMT);
                    break;
                case SDLK_a:
                    c.setXYZ(c.getX(), c.getY() - MIN_MOVE_AMT, c.getZ());
                    break;
                case SDLK_d:
                    c.setXYZ(c.getX(), c.getY() + MIN_MOVE_AMT, c.getZ());
                    break;
                }
            }
        }
        SDL_RenderClear(renderer);
        /*std::cout << "YAW: " <<  c.getYaw() << std::endl;
        std::cout << "PITCH: " << c.getPitch() << std::endl;
        std::cout << "PITCH: " << c.getRoll() << std::endl;*/
        //c.setXYZ(c.getX(), c.getY(), c.getZ() - 0.5);
        //c.setAngles(c.getYaw() + 1 / (2 * M_PI * 10), 0, 0);
        //c.setAngles(c.getYaw() + 3/(2*M_PI), c.getPitch() + 2 / (2 * M_PI), c.getRoll() + 1 / (2 * M_PI));
        /*if (c.getYaw() <= 1.5) {
            c.setAngles(c.getYaw() + 1 / (2 * M_PI * 10), 0, 0);
            c.setAngles(0, 0, c.getRoll() + 1 / (10* 2 * M_PI));
            c.setAngles(0, c.getPitch() + 1 / (2 * M_PI), 0);
        }
        else {
            c.setAngles(0, 0, 0);
        }*/
        //c.setAngles(c.getYaw() + 1 / (1 * M_PI * 10), CAMERA_DEFAULT_PITCH_RADIANS, 0);
        //c.setAngles(c.getYaw() + 1 / (12 * M_PI), c.getPitch() + 1 / (8 * M_PI), c.getRoll() + 1 / (4 * M_PI));
        //c.setAngles(0, c.getPitch() + 1 / (0.00001 * M_PI), 0);
        //c.setAngles(0, 0, c.getRoll() + 1 / (30* 2 * M_PI));
        c.render_polygon_full(triangle_REF_centroid, triangle_REF, 0, 132, 255, 255);
        c.render_polygon_full(triangle_centroid, triangle, 255, 0, 132, 255);
        /*for (size_t i = 0; i < star_cnt; i++) {
            Eigen::Vector4d dummy_centroid;
            c.render_polygon_full(dummy_centroid, stars[i], 255, 0, 0, 255);
        }*/
        SDL_RenderPresent(renderer);

        if (first_time) {
            first_time = false;
            SDL_Delay(1000);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}