#include <SDL2/SDL.h>

#include "Application.h"
#include "Shapes/Line2D.h"
#include "Shapes/Star2D.h"
#include "Utils/Vec2D.h"
#include "Graphics/Screen.h"

void Application::CounterClockwiseLine(Line2D& line, Screen& screen, int dt) {
  // SDL_Delay(50);
  // Instead of a delay, we should use dt

  float rotationammount = -0.00075 * dt;
  if (rotationammount > 0) {
    rotationammount *= -1;
  }

  line = { line.GetP0().RotationResult(rotationammount, line.GetP1()), line.GetP1() };
  screen.Draw(line, Color::Yellow());
  screen.SwapScreens();

}

void Application::CounterClockwiseStar(Star2D& star, Screen& screen, int dt)
{
  // SDL_Delay(50);
  // Instead of a delay, we should use dt
  // this will make the rotation consistent

  float rotationammount = -0.00075 * dt;
  if (rotationammount > 0) {
    rotationammount *= -1;
  }
  star.RotateStar(rotationammount, star.GetCenter());
  screen.Draw(star, Color::Yellow());
  screen.SwapScreens();
}
