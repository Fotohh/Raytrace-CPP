#include <iostream>
#include <SDL2/SDL.h>

#define COLOR_WHITE 0xffffffff

struct Circle {
    double x;
    double y;
    double radius;
};

void FillCircle(SDL_Surface* surface, const Circle* circle, uint32_t color) {
    const double radius = pow(circle->radius,2);
    for (int x = circle->x - circle->radius; x <= circle->x + circle->radius; x++) {
        for(int y = circle->y - circle->radius; y <= circle->y + circle->radius; y++) {
            const double distance_squared = pow(x-circle->x,2) + pow(y-circle->y,2);

            if(distance_squared < radius) {
                SDL_Rect pixel = {x,y, 1,1};
                SDL_FillRect(surface, &pixel, color);
            }
        }
    }
}

int SDL_main(int argc, char *argv[]){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Raytracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 600, NULL);

    SDL_Surface* surface = SDL_GetWindowSurface(window);

    constexpr Circle circle = {200, 200, 80};
    FillCircle(surface, &circle, COLOR_WHITE);

    SDL_UpdateWindowSurface(window);



    SDL_Delay(5000);

    return 0;
}