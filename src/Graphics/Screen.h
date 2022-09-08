//
// Created by Kacper Tomaszewski on 27.07.22.
//

#ifndef SDL_A_LINE_SCREEN_H
#define SDL_A_LINE_SCREEN_H

#include <cstdint>
#include <vector>

#include "ScreenBuffer.h"
#include "Color.h"

class Line2D;
class Star2D;
class Vec2D;
class Triangle;
class AARectangle;
class Circle;
struct SDL_Window;
struct SDL_Surface;

/**
 * @brief Screen class which handles creating the screen and double buffering.
 */
class Screen {
public:
    /**
     * @brief Default Constructor
     */
    Screen();
    /**
     * @brief Destructor
     */
    ~Screen();

    /**
     * @brief Initializes the window and surfaces.
     * @param w Window Width
     * @param h Window Height
     * @param mag Magnification
     * @return The created window pointer
     */
    SDL_Window* Init(uint32_t w, uint32_t h, uint32_t mag);

    /**
     * @brief Swaps the surface of the back buffer with the window surface.
     */
    void SwapScreens();

    /**
     * @brief Sets a new color for clearing the screen.
     * @param c New color
     */
    inline void SetClearColor(const Color& c) { mClearColor = c.GetPixelColor(); }
    /**
     * @return Window Width
     */
    inline uint32_t Width() const { return mWidth; }
    /**
     * @return Window Height
     */
    inline uint32_t Height() const { return mHeight; }

    // Draw methods go here

    /**
     * @brief Draw a color at the given coordinates.
     * @param x The x position
     * @param y The y position
     * @param c The color which should be applied.
     */
    void Draw(int x, int y, const Color& c);
    /**
     * @brief Draw a color using a 2D Vector.
     * @param point The point to which the vector points.
     * @param c The color which should be applied.
     */
    void Draw(const Vec2D& point, const Color& c);
    /**
     * @brief Draw a line with a specific color.
     * @param line The line we want to draw.
     * @param c The color which should be applied to the line.
     */
    void Draw(const Line2D& line, const Color& c);
    /**
     * @brief Draw a star to the screen with a given color.
     * @param star The star which should be drawn.
     * @param c The color of the star.
     */
    void Draw(Star2D& star, const Color& c);
    /**
     * @brief Draw a triangle with a given color.
     * @param triangle The triangle which should be drawn.
     * @param c The color of the triangle.
     * @param fill Flag to check, if the shape should be filled
     * @param fillC The color of the filling 
     */
    void Draw(const Triangle& triangle, const Color& c, bool fill = false, const Color& fillC = Color::White());

    /**
     * @brief Draw a rectangle with a given color.
     * @param rect The rectangle that should be drawn.
     * @param c The color of the rectangle.
     * @param fill Flag to check, if the shape should be filled
     * @param fillC The color of the filling
     */
    void Draw(const AARectangle& rect, const Color& c, bool fill = false, const Color& fillC = Color::White());

    /**
     * @brief Draw a circle to the screen with a given color.
     * @param circle The circle that should be drawn.
     * @param c The color of the circle.
     * @param fill Flag to check, if the shape should be filled
     * @param fillC The color of the filling
     */
    void Draw(const Circle& circle, const Color& c, bool fill = false, const Color& fillC = Color::White());

private:
    // putting the copy constructor and assignment operator in the private field, so it would not be used.
    Screen(const Screen& screen);
    Screen& operator=(const Screen& screen);

    /**
     * @brief Clears the whole screen to the clear color.
     */
    void ClearScreen();

    /**
     * @brief Fill the polygon with a color.
     * @param points The points of the polygon.
     * @param c The color of the filling.
     */
    void FillPoly(const std::vector<Vec2D>& points, const Color& c);

    uint32_t mWidth;
    uint32_t mHeight;

    Color mClearColor;
    ScreenBuffer mBackBuffer;

    SDL_Window *mopWindow;
    SDL_Surface *mnopSurface;
};


#endif //SDL_A_LINE_SCREEN_H
