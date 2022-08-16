//
// Created by Kacper Tomaszewski on 08.07.22.
//
#include <SDL2/SDL.h>

#include "Color.h"

const SDL_PixelFormat *Color::mnopFormat = nullptr;

void Color::InitFormat(const SDL_PixelFormat *format) {
    Color::mnopFormat = format;
}

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    SetRGBA(r, g, b, a);
}

void Color::SetRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    mColor = SDL_MapRGBA(mnopFormat, r, g, b, a);
}

void Color::SetRed(uint8_t red) {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    SDL_GetRGBA(mColor, mnopFormat, &r, &g, &b, &a);
    SetRGBA(red, g, b, a);
}

void Color::SetGreen(uint8_t green) {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    SDL_GetRGBA(mColor, mnopFormat, &r, &g, &b, &a);
    SetRGBA(r, green, b, a);
}

void Color::SetBlue(uint8_t blue) {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    SDL_GetRGBA(mColor, mnopFormat, &r, &g, &b, &a);
    SetRGBA(r, g, blue, a);
}

void Color::SetAlpha(uint8_t alpha) {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    SDL_GetRGBA(mColor, mnopFormat, &r, &g, &b, &a);
    SetRGBA(r,g,b,alpha);
}

uint8_t Color::GetRed() const {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    SDL_GetRGBA(mColor, mnopFormat, &r, &g, &b, &a);
    return r;
}

uint8_t Color::GetGreen() const {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    SDL_GetRGBA(mColor, mnopFormat, &r, &g, &b, &a);
    return g;
}

uint8_t Color::GetBlue() const {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    SDL_GetRGBA(mColor, mnopFormat, &r, &g, &b, &a);
    return b;
}

uint8_t Color::GetAlpha() const {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    SDL_GetRGBA(mColor, mnopFormat, &r, &g, &b, &a);
    return a;
}


Color Color::Evaluate1MinusSourceAlpha(const Color& source, const Color& dest)
{
    // blending equation
    // SourceRGB * sourceAlpha + DestinationRGB * (1 - sourceAlpha)
    auto alpha = source.GetAlpha();
    
    auto sourceAlpha = (float)alpha / 255.0f;
    auto destAlpha = 1.0f - sourceAlpha;

    Color outColor;

    // The out color always has full alpha
    outColor.SetAlpha(255);
    outColor.SetRed(float(source.GetRed()) * sourceAlpha + dest.GetRed() * destAlpha);
	outColor.SetGreen(float(source.GetGreen()) * sourceAlpha + dest.GetGreen() * destAlpha);
	outColor.SetBlue(float(source.GetBlue()) * sourceAlpha + dest.GetBlue() * destAlpha);

    return outColor;
}
