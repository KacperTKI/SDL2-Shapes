//
// Created by Kacper Tomaszewski on 27.07.22.
//

#include <algorithm> // for std::sort
#include <cassert>
#include <cmath>
#include <vector>
#include <SDL2/SDL.h>

#include "Screen.h"
#include "../Utils/Vec2D.h"
#include "../Shapes/Line2D.h"
#include "../Shapes/Star2D.h"
#include "../Shapes/Triangle.h"
#include "../Shapes/AARectangle.h"
#include "../Shapes/Circle.h"
#include "../Utils/Utils.h"

Screen::Screen()
    : mWidth(0), mHeight(0), mopWindow(nullptr), mnopSurface(nullptr)
{

}

void Screen::ClearScreen() {
    assert(mopWindow);
    if (mopWindow)
        SDL_FillRect(mnopSurface, nullptr, mClearColor.GetPixelColor());
}

void Screen::FillPoly(const std::vector<Vec2D>& points, const Color& c)
{
    if (points.size() > 0)
    {
        // set the boundries of the shape
        float top = points[0].GetY();
        float bottom = points[0].GetY();
        float right = points[0].GetX();
        float left = points[0].GetX();

        // get the most top, bottom, left and right pixel of the shape
        for (size_t i = 1; i < points.size(); i++)
        {
            if (points[i].GetY() < top)
            {
                top = points[i].GetY();
            }

            if (points[i].GetY() > bottom)
            {
                bottom = points[i].GetY();
            }

            if (points[i].GetX() < left)
            {
                left = points[i].GetX();
            }

            if (points[i].GetX() > right)
            {
                right = points[i].GetX();
            }
        }

        // go through the pixels from top to bottom
        for (int pixelY = top; pixelY < bottom; pixelY++)
        {
            std::vector<float> nodeXVec; // save the x pixels in this vector

            size_t j = points.size() - 1;

            for (size_t i = 0; i < points.size(); i++)
            {
                float pointiY = points[i].GetY();
                float pointjY = points[j].GetY();

                // check if the pixel is inbetween the top and the bottom
                if ((pointiY <= (float)pixelY && pointjY > (float)pixelY) ||
                    (pointjY <= (float)pixelY && pointiY > (float)pixelY))
                {
                    // Check that the denominator is not zero
                    float denom = pointjY - pointiY;
                    if (IsEqual(denom, 0))
                    {
                        continue;
                    }
                    // Solve for x if the denominator is not 0 and push the result onto the vector
                    float x = points[i].GetX() + (pixelY - pointiY)/(denom)
                        * (points[j].GetX() - points[i].GetX());
                    nodeXVec.push_back(x);
                }

                j = i;

            }

            // sort the vector in ascending order, so we draw the lines from the left most, to the right most
            std::sort(nodeXVec.begin(), nodeXVec.end(), std::less<>());

            for (size_t k = 0; k < nodeXVec.size(); k+=2) // +=2 because we do this to each pair of pixels
            {
                // bound the x's so it does not go outside our boundries
                if (nodeXVec[k] > right)
                {
                    break;
                }

                if (nodeXVec[k+1] > left)
                {
                    if (nodeXVec[k] < left)
                    {
                        nodeXVec[k] = left;
                    }

                    if (nodeXVec[k+1] > right)
                    {
                        nodeXVec[k+1] = right;
                    }

                    // after setting the boundries, draw each individual pixel
                    for (int pixelX = nodeXVec[k]; pixelX < std::round(nodeXVec[k+1]); pixelX++)
                    {
                        Draw(pixelX, pixelY, c);
                    }
                }
            }
        }
    }
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
    mopWindow = SDL_CreateWindow("SDL-Shapes", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                            mWidth * mag, mHeight * mag, 0);

    if (mopWindow) {
        // Create window surface
        mnopSurface = SDL_GetWindowSurface(mopWindow);

        // Just in case, if the machine does not have a alpha channel automaticaly, we force it to use one
        SDL_PixelFormat *pixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
        std::cout << SDL_GetPixelFormatName(pixelFormat->format) << '\n';

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
    assert(mopWindow);
    for (size_t i = 0; i < star.GetStarSize(); i++)
    {
        Draw(star[i], c);
    }
}

void Screen::Draw(const Triangle& triangle, const Color& c, bool fill, const Color& fillC)
{
    assert(mopWindow);
    if (mopWindow) {
        // check if the shape should be filled
        if (fill)
        {
            FillPoly(triangle.GetPoints(), fillC);
        }

        Line2D line1(triangle.GetP0(), triangle.GetP1());
        Line2D line2(triangle.GetP1(), triangle.GetP2());
        Line2D line3(triangle.GetP2(), triangle.GetP0());

        Draw(line1, c);
        Draw(line2, c);
        Draw(line3, c);
    }
}

void Screen::Draw(const AARectangle& rect, const Color& c, bool fill, const Color& fillC)
{
    assert(mopWindow);
    if (mopWindow) {
        // check if the shape should be filled
        if (fill)
        {
            FillPoly(rect.GetPoints(), fillC);
        }

        std::vector<Vec2D> points = rect.GetPoints();
        std::vector<Line2D> lines;
        for (int i = 0; i < 3; i++)
        {
            lines.push_back(Line2D(points[i], points[i+1]));
        }
        lines.push_back(Line2D(points[3], points[0]));

        for (auto& line : lines)
        {
            Draw(line, c);
        }
    }
}

void Screen::Draw(const Circle& circle, const Color& c, bool fill, const Color& fillC)
{
    assert(mopWindow);
    if (mopWindow) {
        // The higher the number of segments, then the circle will have less edges
        const unsigned int NUM_CIRCLE_SEGMENTS = 100;

        // vector for holding all the segments of the circle
        std::vector<Line2D> lines;
        std::vector<Vec2D> circlePoints;

        float angle = TWO_PI / float(NUM_CIRCLE_SEGMENTS);

        // we get the right most point on the height of the center point
        Vec2D p0 = Vec2D(circle.GetCenterPoint().GetX() + circle.GetRadius(),
                         circle.GetCenterPoint().GetY());
        Vec2D p1 = p0;
        Line2D nextLine;

        for (unsigned int i = 0; i < NUM_CIRCLE_SEGMENTS; i++)
        {
            // we rotate p1 by the angle
            p1.Rotate(angle, circle.GetCenterPoint());
            // we update the next line with the rotated point
            nextLine.SetP0(p0);
            nextLine.SetP1(p1);
            // push the line onto the vector
            lines.push_back(nextLine);
            // we update p0 to be the next point
            p0 = p1;
            // We add the point to our points vector
            circlePoints.push_back(p0);
        }

        // check if the shape should be filled
        if (fill)
        {
            // circle is not a polygon!
            // but we can fill it like a polygon, because we are working with segments
            FillPoly(circlePoints, fillC);
        }

        // draw the segments of the circle
        for (auto& line : lines)
        {
            Draw(line, c);
        }
    }
}
