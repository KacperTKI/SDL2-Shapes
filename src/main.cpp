#include <cmath>
#include <iostream>
#include <SDL2/SDL.h>

#include "Application.h"
#include "Graphics/Color.h"
#include "Graphics/Screen.h"
#include "Shapes/Line2D.h"
#include "Shapes/Star2D.h"

// global constants for the window width and height
const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;
const int MAGNIFICATION = 3;

int main(int argc, char* argv[]) { // to use SDL the main function has to have parameters
    Screen screen;
    screen.Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION);
    int startX = SCREEN_WIDTH / 2;
    int startY = 50;
    Vec2D middle = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    Line2D line = { Vec2D(startX, startY), middle };
    Star2D star = { Vec2D(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 100, 33, 5 };
    screen.Draw(line, Color::Yellow());
    screen.SwapScreens();
    bool drawStar = false;
    bool drawLine = false;

    // Create an SDL Event and check it in the "game loop"
    SDL_Event testEvent;

    bool running = true;
    while (running) {
        // SDL uses a while loop to process an event in turn
        // Events are stored in a queue and if the queue is empty, then it returns 0
        // while (SDL_PollEvent(&testEvent)) {
        //     switch (testEvent.type) { // we handle the event by using a switch statement
        //         case SDL_QUIT:
        //             running = false;
        //             break;
        //     }
        //     switch (testEvent.key.keysym.sym) {
        //         case SDLK_UP:
        //             screen.Draw(line, Color::Red());
        //             screen.SwapScreens();
        //             break;
        //         case SDLK_DOWN:
        //             screen.Draw(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, Color::Red());
        //             screen.SwapScreens();
        //             break;
        //         case SDLK_LEFT:
        //             screen.Draw(line, Color::Cyan());
        //             screen.SwapScreens();
        //             break;
        //         case SDLK_RIGHT:
        //             screen.Draw(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, Color::Cyan());
        //             screen.SwapScreens();
        //             break;
        //     }
        // }

        while (SDL_PollEvent(&testEvent)) {
            switch (testEvent.type) {
                case SDL_QUIT:
                    running = false;
                    break;
            }

            switch (testEvent.key.keysym.sym) 
            {
                case SDLK_UP:
                    drawLine = true;
                    drawStar = false;
                    break;
                case SDLK_DOWN:
                    drawStar = true;
                    drawLine = false;
                    break;
                case SDLK_LEFT:
                    screen.Draw(line, Color::Yellow());
                    screen.SwapScreens();
                    drawStar = false;
                    drawLine = false;
                    break;
                case SDLK_RIGHT:
                    screen.Draw(star, Color::Yellow());
                    screen.SwapScreens();
                    drawStar = false;
                    drawLine = false;
                    break;
            }    
        }
            
        if (drawLine)
            Application::CounterClockwiseLine(line, screen);
        
        if (drawStar)
            Application::CounterClockwiseStar(star,screen);
    }

    return 0;
}