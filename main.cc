#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>

#define COLOR_WHITE 0xffffffff
#define COLOR_BLACK 0x000000
#define COLOR_GRAY 0x808080
#define COLOR_YELLOW 0xFFFF00
#define WIDTH 900
#define HEIGHT 600
#define PIXEL_SIZE 1
constexpr static long size = 100;

struct Circle {
    double x;
    double y;
    double radius;
};

struct Ray {
    double x_s, y_s;
    double angle;
};

static Ray rays[size] = {};

void FillCircle(SDL_Surface* surface, const Circle* circle, const uint32_t color) {
    const double radius = pow(circle->radius,2);
    for (int x = circle->x - circle->radius; x <= circle->x + circle->radius; x++) {
        for(int y = circle->y - circle->radius; y <= circle->y + circle->radius; y++) {
            if(x < 0 || x > WIDTH) continue;
            if(y < 0 || y > HEIGHT) continue;
            const double distance_squared = pow(x-circle->x,2) + pow(y-circle->y,2);

            if(distance_squared < radius) {
                SDL_Rect pixel = {x,y, 1,1};
                SDL_FillRect(surface, &pixel, color);
            }
        }
    }
}

void FillRays(SDL_Surface* surface, uint32_t color, const Circle& circle) {

    double radius = pow(circle.radius,2);

    for(int i = 0; i < size; i++) {
        Ray ray = rays[i];

        bool end_of_screen = false;
        bool object_hit = false;

        double step = 0.1;
        double x_draw = ray.x_s;
        double y_draw = ray.y_s;

        while(!end_of_screen && !object_hit) {
            x_draw += step * cos(ray.angle);
            y_draw += step * (0.1*sin(ray.angle));

            SDL_Rect pixel = {(int)x_draw, (int)y_draw, 1,1};
            SDL_FillRect(surface, &pixel, color);

            if(x_draw < 0 || x_draw > 900)
                end_of_screen = true;
            if(y_draw < 0 || y_draw > 600)
                end_of_screen = true;

            const double distance_squared = pow(x_draw-circle.x,2) + pow(y_draw-circle.y,2);

            if(distance_squared < radius) {
                object_hit = true;
            }
        }
    }

}

constexpr double pi = 1/M_PI;

void generate_rays(const Circle& circle) {

    for(int i = 0; i < size; i++) {
        double angle = ((double) i * size) * 0.5 * pi;
        Ray ray = {circle.x, circle.y, angle};
        rays[i] = ray;
    }

}

void clear_screen(SDL_Surface* surface) {
    SDL_Rect scr = {0,0,WIDTH,HEIGHT};
    SDL_FillRect(surface, &scr, COLOR_BLACK);
}



int SDL_main(int argc, char *argv[]){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Raytracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 600, NULL);

    SDL_Surface* surface = SDL_GetWindowSurface(window);

    Circle circle = {200, 200, 80};
    Circle shadow = {650, 300, 140};

    generate_rays(circle);

    bool running = true;
    SDL_Event event;

    while (running) {

        clear_screen(surface);

        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                running = false;
            }

            if(event.type == SDL_MOUSEMOTION && event.motion.state != 0) {

                circle.x = event.motion.x;
                circle.y = event.motion.y;

                generate_rays(circle);

            }
        }

        FillCircle(surface, &circle, COLOR_WHITE);

        FillCircle(surface, &shadow, COLOR_GRAY);
        FillRays(surface, COLOR_YELLOW, shadow);

        SDL_UpdateWindowSurface(window);
        SDL_Delay(10);
    }

    return 0;
}