//
// Created by Kacper Tomaszewski on 13.07.22.
//
#include <cassert>
#include <SDL2/SDL.h>

#include "ScreenBuffer.h"

uint32_t ScreenBuffer::GetIndex(int r, int c) {
    assert(mopSurface);
    if (mopSurface) {
        return r * mopSurface->w + c;
    }

    return 0;
}

ScreenBuffer::ScreenBuffer() : mopSurface(nullptr) {

}

ScreenBuffer::ScreenBuffer(const ScreenBuffer &screenBuffer)
    : mopSurface(nullptr) {
    // Check if there exists a surface to copy
    if (screenBuffer.mopSurface) {
        // If so, then copy the other surface
        mopSurface = SDL_CreateRGBSurfaceWithFormat(0, screenBuffer.mopSurface->w,
                                                    screenBuffer.mopSurface->h, 0,
                                                    screenBuffer.mopSurface->format->format);

        //SDL_BlitSurface copies all the pixel from the source surface to the destination surface
        SDL_BlitSurface(screenBuffer.mopSurface, nullptr, mopSurface, nullptr);
    }
}

ScreenBuffer::ScreenBuffer(ScreenBuffer&& otherBuffer)
    : mopSurface(otherBuffer.mopSurface)
{
    // invalidate the other buffer
    otherBuffer.mopSurface = nullptr;
}

ScreenBuffer& ScreenBuffer::operator=(ScreenBuffer&& otherBuffer)
{
    // check if it is assigning itself
    if (this == &otherBuffer)
    {
        return *this;
    }

    // delete existing data
    delete mopSurface;

    // take ownership of the other data
    mopSurface = otherBuffer.mopSurface;

    // invalidate the other buffer
    otherBuffer.mopSurface = nullptr;

    return *this;
}

ScreenBuffer::~ScreenBuffer() {
    // if there exists a surface, then free it
    if (mopSurface) {
        SDL_FreeSurface(mopSurface);
        mopSurface = nullptr;
    }
}

ScreenBuffer &ScreenBuffer::operator=(const ScreenBuffer &screenBuffer) {
    // Check if it's the same Screen Buffer
    if (this == &screenBuffer) {
        return *this;
    }

    // Check if we already have a surface, if so, then delete it
    if (mopSurface) {
        SDL_FreeSurface(mopSurface);
        mopSurface = nullptr;
    }

    // check whether the other Screen Buffer has a surface, if so, then copy it
    if (screenBuffer.mopSurface) {
        mopSurface = SDL_CreateRGBSurfaceWithFormat(0, screenBuffer.mopSurface->w,
                                                    screenBuffer.mopSurface->h, 0,
                                                    screenBuffer.mopSurface->format->format);

        SDL_BlitSurface(screenBuffer.mopSurface, nullptr, mopSurface, nullptr);
    }

    return *this;
}

void ScreenBuffer::Init(uint32_t format, uint32_t width, uint32_t height) {
    mopSurface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 0, format);
    Clear();
}

void ScreenBuffer::Clear(const Color &c) {
    assert(mopSurface);
    if (mopSurface) {
        // Fills the entire surface with the given color
        SDL_FillRect(mopSurface, nullptr, c.GetPixelColor());
    }
}

void ScreenBuffer::SetPixel(const Color &c, int x, int y) {
    assert(mopSurface);

    if (mopSurface && (y < mopSurface->h && y >= 0 && x >= 0 && x < mopSurface->w)) {
        // Locks the surface from being used somewhere else than here
        SDL_LockSurface(mopSurface);

        // Gets the array of pixels from the surface
        auto *pixels = (uint32_t *) mopSurface->pixels;

        // Gets the index of the pixel which is located at the given coordinates
        auto index = GetIndex(y, x);

        // Changes the pixel color
        auto surfaceColor = Color(pixels[index]); // destination color
        pixels[index] = Color::Evaluate1MinusSourceAlpha(c, surfaceColor).GetPixelColor();

        // Unlocks the surface so it can be used again
        SDL_UnlockSurface(mopSurface);
    }
}

