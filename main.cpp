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

// Главная функция
int main(int argc, char* args[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return -1;

    SDL_Window* window = SDL_CreateWindow("Bouncing Ball SDL2", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Характеристики мяча
    float posX = SCREEN_WIDTH / 2.0f;
    float posY = 100.0f;
    float velX = 5.0f;
    float velY = 0.0f;
    float gravity = 0.5f;
    float bounce = -0.95f;

    bool quit = false;
    SDL_Event e;

    // Выход
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) quit = true;
        }

        // Физика
        velY += gravity;
        posX += velX;
        posY += velY;

        // Коллизия с полом
        if (posY + BALL_RADIUS > SCREEN_HEIGHT) {
            posY = SCREEN_HEIGHT - BALL_RADIUS;
            velY *= bounce;
            if (std::abs(velY) < 1.0f) velY = 0; // Гасим микро-прыжки
        }

        // Коллизии со стенами
        if (posX + BALL_RADIUS > SCREEN_WIDTH) {
            posX = SCREEN_WIDTH - BALL_RADIUS;
            velX = -velX;
        } else if (posX - BALL_RADIUS < 0) {
            posX = BALL_RADIUS;
            velX = -velX;
        }

        // Цвет экрана
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        // Цвет мяча
        SDL_SetRenderDrawColor(renderer, 255, 105, 180, 255);
        FillCircle(renderer, (int)posX, (int)posY, BALL_RADIUS);

        // Отрисовка
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    // Очистка ресурсов
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}