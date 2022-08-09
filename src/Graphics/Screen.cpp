//
// Created by Kacper Tomaszewski on 27.07.22.
//
#include <cassert>
#include <cmath>
#include <SDL2/SDL.h>

#include "Screen.h"
#include "../Utils/Vec2D.h"
#include "../Shapes/Line2D.h"
#include "../Shapes/Star2D.h"
#include "../Shapes/Triangle.h"

void Screen::ClearScreen() {
    assert(mopWindow);
    if (mopWindow)
        SDL_FillRect(mnopSurface, nullptr, mClearColor.GetPixelColor());
}

Screen::Screen() : mWidth(0), mHeight(0), mopWindow(nullptr), mnopSurface(nullptr) {

}

Screen::~Screen() {
    if (mopWindow) {
        SDL_DestroyWindow(mopWindow);
        mopWindow = nullptr;
    }

    SDL_Quit();
}

SDL_Window *Screen::Init(uint32_t w, uint32_t h, uint32_t mag) {
    // Initialize SDL and check if it has not failed
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) { // with OR we can add as many flags as we want
        printf("Error: SDL failed to initialize\n");
        return nullptr;
    }

    mWidth = w;
    mHeight = h;

    // Create window
    // NOTE: to have no flags enter 0
    mopWindow = SDL_CreateWindow("Line-Program", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                            mWidth * mag, mHeight * mag, 0);

    if (mopWindow) {
        // Create window surface
        mnopSurface = SDL_GetWindowSurface(mopWindow);

        // Get the pixel format of the current machine
        SDL_PixelFormat *pixelFormat = mnopSurface->format;

        // Initialize the format
        Color::InitFormat(pixelFormat);

        mClearColor = Color::Black();

        // Initialize the back buffer for double buffering
        mBackBuffer.Init(pixelFormat->format, mWidth, mHeight);
    }

    return mopWindow;
}

void Screen::SwapScreens() {
    assert(mopWindow);
    if (mopWindow) {
        ClearScreen();

        // SDL_BlitScaled scales the window surface to the window size, thus
        // we can increase the window size without increasing the number of pixels.
        SDL_BlitScaled(mBackBuffer.GetSurface(), nullptr, mnopSurface, nullptr);

        SDL_UpdateWindowSurface(mopWindow);

        mBackBuffer.Clear(mClearColor);
    }
}

void Screen::Draw(int x, int y, const Color &c) {
    assert(mopWindow);
    if (mopWindow) {
        mBackBuffer.SetPixel(c, x, y);
    }
}

void Screen::Draw(const Vec2D &point, const Color &c) {
    assert(mopWindow);
    if (mopWindow) {
        mBackBuffer.SetPixel(c, point.GetX(), point.GetY());
    }
}

void Screen::Draw(const Line2D& line, const Color& c) {
    // we draw the line using Bresenham's Line Algorithm
    // the general idea is that we have a grid of pixels and line going through it.
    // we decide that if the line is below the half way point of the pixel, we draw the current pixel.
    // if the line is above the half way mark, then we increase the y and draw the pixel.
    assert(mopWindow);
    if (mopWindow) {
        int dx, dy;
        
        // the algorithm works with integers, so we have to round our float values
        int x0 = roundf(line.GetP0().GetX());
        int y0 = roundf(line.GetP0().GetY());
        int x1 = roundf(line.GetP1().GetX());
        int y1 = roundf(line.GetP1().GetY());

        dx = x1 - x0;
        dy = y1 - y0;

        signed const char ix((dx > 0) - (dx < 0)); 
        signed const char iy((dy > 0) - (dy < 0));
        // both evaluate to either 1 or -1
        // with that, we know if the line goes up or down

        dx = abs(dx) * 2;
        dy = abs(dy) * 2;

        // The first pixel that will be drawn
        Draw(x0, y0, c);

        if (dx >= dy) {
            // go along the x
            int d = dy - dx /2;

            while (x0 != x1) {
                if (d >= 0) {
                    d -= dx;
                    y0 += iy;
                }

                d += dy;
                x0 += ix;

                Draw(x0, y0, c);
            }
        } else {
            // go along the y
            int d = dx - dy/2;
            
            while (y0 != y1) {
                if (d >= 0) {
                    d -= dy;
                    x0 += ix;
                }
                
                d += dx;
                y0 += iy;

                Draw(x0, y0, c);
            }
        }
    }
}

void Screen::Draw(Star2D& star, const Color& c)
{
    for (size_t i = 0; i < star.GetStarSize(); i++)
    {
        Draw(star[i], c);
    }
}

void Screen::Draw(const Triangle& triangle, const Color& c)
{
    Line2D line1(triangle.GetP0(), triangle.GetP1());
    Line2D line2(triangle.GetP1(), triangle.GetP2());
    Line2D line3(triangle.GetP2(), triangle.GetP0());

    Draw(line1, c);
    Draw(line2, c);
    Draw(line3, c);
}