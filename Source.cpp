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

    SDL_DisplayMode dm; SDL_GetCurrentDisplayMode(0, &dm);

    int w_ = dm.w - dm.w / 4;
    int h_ = dm.h - dm.h / 4;

    SDL_Window* window = SDL_CreateWindow("3D",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        w_,
        h_,
        SDL_WINDOW_OPENGL);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    int w; int h; SDL_GetWindowSize(window, &w, &h);
    Eigen::Vector3d initN; initN << 0, 0, 1;
    Eigen::Vector3d initV; initV << 0, 1, 0;
    Camera c(renderer, window, 100, ((double)w)/h, 0.01, 5000, initN, initV, 0, 0, 0);

    Object o;
    o.world_position << 0, 0, 10, 1;
    o.pitch = 0;
    o.yaw = 0;
    o.roll = 0;
    o.scale_x = 1;
    o.scale_y = 1;
    o.scale_z = 1;
    std::vector<Eigen::Vector4d> verts;
    verts.push_back(Eigen::Vector4d(-0.5, -0.5, 0, 1));
    verts.push_back(Eigen::Vector4d(0, 0.5, 0, 1));
    verts.push_back(Eigen::Vector4d(0.5, -0.5, 0, 1));
    o.vertices = verts;

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
                    default:
                    break;
                }
            }
        }
        //c.setAngles(c.getYaw() + 1 / (M_PI * 10000), 0, 0);
        //c.setAngles(0, c.getPitch() + 1 / (M_PI * 10000), 0);
        //c.setXYZ(0, 0, c.getZ() + 0.1);
        SDL_RenderClear(renderer);
        c.render_object(o);
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