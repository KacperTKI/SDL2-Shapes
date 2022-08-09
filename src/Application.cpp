#include <SDL2/SDL.h>

#include "Application.h"
#include "Shapes/Line2D.h"
#include "Shapes/Star2D.h"
#include "Utils/Vec2D.h"
#include "Graphics/Screen.h"

void Application::CounterClockwiseLine(Line2D& line, Screen& screen) {
    SDL_Delay(50);

    line = { line.GetP0().RotationResult(-0.01, line.GetP1()), line.GetP1() };
    screen.Draw(line, Color::Yellow());
    screen.SwapScreens();

}

void Application::CounterClockwiseStar(Star2D& star, Screen& screen)
{
    SDL_Delay(50);

    star.RotateStar(-0.01, star.GetCenter());
    screen.Draw(star, Color::Yellow());
    screen.SwapScreens();
}