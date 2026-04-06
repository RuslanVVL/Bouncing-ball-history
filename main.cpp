// Библиотеки
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <iostream>
#include <cmath>

// Константы
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int BALL_RADIUS = 20;

// Функция для отрисовки заполненного круга
void FillCircle(SDL_Renderer* renderer, int x, int y, int radius) {
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w; // расстояние от центра по X
            int dy = radius - h; // расстояние от центра по Y
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}