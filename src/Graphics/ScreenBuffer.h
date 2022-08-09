//
// Created by Kacper Tomaszewski on 13.07.22.
//
#ifndef SDL_A_LINE_SCREENBUFFER_H
#define SDL_A_LINE_SCREENBUFFER_H

#include "Color.h"

struct SDL_Surface;

/**
 * @brief The Screen Buffer represents a buffer that can be applied to the window. We use this to have multiple buffers,
 * which will handle the surfaces. (Double Buffering)
 */
class ScreenBuffer {
private:
    SDL_Surface *mopSurface;
    uint32_t GetIndex(int r, int c);
public:
    /**
     * @brief Defualt Constructor
     */
    ScreenBuffer();
    /**
     * @brief Copy Constructor
     * @param screenBuffer buffer which will be copied.
     */
    ScreenBuffer(const ScreenBuffer& screenBuffer);
    /**
     * @brief Destructor
     */
    ~ScreenBuffer();

    /**
     * @brief Assignment operator
     * @param screenBuffer buffer, to be assigned to this.
     * @return *this
     */
    ScreenBuffer& operator=(const ScreenBuffer& screenBuffer);

    /**
     * @brief Initializing a new surface.
     * @param format The format of the current machine.
     * @param width The width of the window.
     * @param height The height of the window.
     */
    void Init(uint32_t format, uint32_t width, uint32_t height);

    /**
     * @brief Get the current surface.
     * @return mopSurface
     */
    inline SDL_Surface *GetSurface() { return mopSurface; }

    /**
     * @brief Set the surface to a color (By default it's black).
     * @param c The color with which the surface should be cleared.
     */
    void Clear(const Color& c = Color::Black());

    /**
     * @brief Change the color a specific pixel
     * @param c The color, which should be applied to the window.
     * @param x The x coordinate in the window.
     * @param y The y coordinate in the window.
     */
    void SetPixel(const Color& c, int x, int y);
};

#endif //SDL_A_LINE_SCREENBUFFER_H
