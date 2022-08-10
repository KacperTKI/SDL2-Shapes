#include <cmath>
#include <iostream>
#include <SDL2/SDL.h>

#include "Application.h"
#include "Graphics/Color.h"
#include "Graphics/Screen.h"
#include "Shapes/Triangle.h"
#include "Shapes/AARectangle.h"

// global constants for the window width and height
const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;
const int MAGNIFICATION = 3;

int main(int argc, char* argv[]) { // to use SDL the main function has to have parameters
    Screen screen;
    screen.Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION);
    Triangle tri(Vec2D(100, 100), Vec2D(25, 250), Vec2D(175, 250));
    AARectangle rect(Vec2D(50, 50), 50, 100);
    //screen.Draw(tri, Color::Cyan());
    screen.Draw(rect, Color::Green());
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