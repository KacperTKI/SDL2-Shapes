#include <cmath>
#include <iostream>
#include <SDL2/SDL.h>

#include "Application.h"
#include "Graphics/Color.h"
#include "Graphics/Screen.h"
#include "Shapes/Triangle.h"
#include "Shapes/AARectangle.h"
#include "Shapes/Circle.h"

// global constants for the window width and height
const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;
const int MAGNIFICATION = 3;

int main(int argc, char* argv[]) { // to use SDL the main function has to have parameters
    Screen screen;
    screen.Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION);
    Triangle tri(Vec2D(60, 10), Vec2D(10, 110), Vec2D(110, 110));
    AARectangle rect(Vec2D(SCREEN_WIDTH / 2 - 25, SCREEN_HEIGHT / 2 - 25), 50, 50);
    Circle circle(Vec2D(SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2 + 50), 50);
    screen.Draw(tri, Color::Red(), true, Color::Red());
    screen.Draw(circle, Color(0, 255, 0, 255), true, Color(0, 255, 0, 255));
    screen.Draw(rect, Color(0, 0, 255, 255), true, Color(0, 0, 255, 50));
    screen.SwapScreens();

    // Create an SDL Event and check it in the "game loop"
    SDL_Event testEvent;

    bool running = true;
    while (running) {
        while (SDL_PollEvent(&testEvent)) {
            switch (testEvent.type) {
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }
    }

    return 0;
}
