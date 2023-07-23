#include <iostream>
#include <ctime>
#include <SDL2/SDL.h>
#include "Camera.h"
#include <cmath>
#undef main

#define MIN_TURN_ANGLE (1 / (M_PI * 5))
#define MIN_MOVE_AMT 0.4

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

    SDL_SetWindowInputFocus(window);
    SDL_SetRelativeMouseMode(SDL_TRUE);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    int w; int h; SDL_GetWindowSize(window, &w, &h);
    Eigen::Vector3d initN; initN << 0, 0, 1;
    Eigen::Vector3d initV; initV << 0, 1, 0;
    Camera c(renderer, window, 100, ((double)w)/h, 0.001, 5000, initN, initV, 0, 0, 0);

    Object o;
    o.world_position << 0, 0, 10, 1;
    o.pitch = 0;
    o.yaw = 0;
    o.roll = 0;
    o.scale_x = 1;
    o.scale_y = 1;
    o.scale_z = 1;
    std::vector<Eigen::Vector4d> verts;
    /*verts.push_back(Eigen::Vector4d(-0.5, -0.5, 0, 1));
    verts.push_back(Eigen::Vector4d(0, 0.5, 0, 1));
    verts.push_back(Eigen::Vector4d(0.5, -0.5, 0, 1));*/
    verts.push_back(Eigen::Vector4d(-0.5, -0.5, 0, 1));
    verts.push_back(Eigen::Vector4d(0, 0.5, 0, 1));
    verts.push_back(Eigen::Vector4d(0.5, -0.5, 0, 1));
    //verts.push_back(Eigen::Vector4d(0.5, 0.5, 0, 1));
    /* verts.push_back(Eigen::Vector4d(-0.5, -0.5, 0.5, 1));
    verts.push_back(Eigen::Vector4d(-0.5, 0.5, 0.5, 1));
    verts.push_back(Eigen::Vector4d(0.5, -0.5, 0.5, 1));
    verts.push_back(Eigen::Vector4d(0.5, 0.5, 0.5, 1)); */
    o.vertices = verts;

    int prev_mouse_x;
    int prev_mouse_y;

    SDL_Event ev;
    bool running = true;
    bool first_time = true;

    double new_x = 0;
    double new_y = 0;
    double new_z = 0;
    while (running) {
        Eigen::Vector3d u_vec = c.get_u();
        Eigen::Vector3d v_vec = c.get_v();
        Eigen::Vector3d n_vec = c.get_n();

        while (SDL_PollEvent(&ev)) {
            switch (ev.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                switch (ev.key.keysym.sym) {
                    case SDLK_w:
                        new_x = c.getX() + MIN_MOVE_AMT * n_vec(0);
                        new_y = c.getY() + MIN_MOVE_AMT * n_vec(1);
                        new_z = c.getZ() + MIN_MOVE_AMT * n_vec(2);
                        c.setXYZ(new_x, new_y, new_z);
                        break;
                    case SDLK_s:
                        new_x = c.getX() - MIN_MOVE_AMT * n_vec(0);
                        new_y = c.getY() - MIN_MOVE_AMT * n_vec(1);
                        new_z = c.getZ() - MIN_MOVE_AMT * n_vec(2);
                        c.setXYZ(new_x, new_y, new_z);
                        break;
                    case SDLK_a:
                        new_x = c.getX() + MIN_MOVE_AMT * u_vec(0);
                        new_y = c.getY() + MIN_MOVE_AMT * u_vec(1);
                        new_z = c.getZ() + MIN_MOVE_AMT * u_vec(2);
                        c.setXYZ(new_x, new_y, new_z);
                        break;
                    case SDLK_d:
                        new_x = c.getX() - MIN_MOVE_AMT * u_vec(0);
                        new_y = c.getY() - MIN_MOVE_AMT * u_vec(1);
                        new_z = c.getZ() - MIN_MOVE_AMT * u_vec(2);
                        c.setXYZ(new_x, new_y, new_z);
                        break;
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                    default:
                        break;
                }
            }
        }

        // Get relative mouse position for camera movement
        int mouse_x; int mouse_y;
        SDL_GetRelativeMouseState(&mouse_x, &mouse_y);

        // Normalize mouse position
        double n_mouse_x = ((double)mouse_x / w) * 5;
        double n_mouse_y = ((double)mouse_y / h) * 5;

        c.setAngles(n_mouse_x, -1 * n_mouse_y, 0);

        printf("Player position: (%lf, %lf, %lf)\n", c.getX(), c.getY(), c.getZ());

        // Render the object
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