//
// Created by Kacper Tomaszewski on 08.07.22.
//
#ifndef SDL_A_LINE_COLOR_H
#define SDL_A_LINE_COLOR_H

#include <cstdint> // for uint32_t

struct SDL_PixelFormat; // forward declaration of the SDL_PixelFormat to not include SDL.h again

/**
 * Since the pixel format can be different on each machine, we need this class to handle the color so,
 * that they dont differ.
 * @brief This class allows to handle colors the same way on every format.
 */
class Color {
private:
    uint32_t mColor;
public:
    /**
     * @brief holds the current pixel format on the machine.
     */
    static const SDL_PixelFormat *mnopFormat;
    /**
     * @brief Initializes mnopFormat to the machines current pixel format.
     * @param format Machines current format.
     */
    static void InitFormat(const SDL_PixelFormat *format);

    static Color Black() { return Color(0, 0, 0, 255); }
    static Color White() { return Color(255, 255, 255, 255); }
    static Color Blue() { return Color(0, 0, 255, 255); }
    static Color Red() { return Color(255, 0, 0, 255); }
    static Color Green() { return Color(0, 255, 0, 255); }
    static Color Yellow() { return Color(255, 255, 0, 255); }
    static Color Magenta() { return Color(255, 0, 255, 255); }
    static Color Cyan() { return Color(37, 240, 217, 255); }
    static Color Pink() { return Color(252, 197, 224, 255); }
    static Color Orange() { return Color(245, 190, 100, 255); }

    /**
     * @brief Default Constructor
     */
    Color() : Color(0){}
    /**
     * @brief Copy Constructor
     * @param c The copied color
     */
    Color(const Color& c) : Color(c.mColor){}
    /**
     * Create a color using an already existing color.
     * @brief Constructor
     * @param color The color which should be applied
     */
    Color(uint32_t color) : mColor(color){}
    /**
     * Create a color using RGBA values.
     * @brief Constructor
     * @param r Red
     * @param g Green
     * @param b Blue
     * @param a Alpha
     */
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    inline bool operator==(const Color& c) const { return mColor == c.mColor; }
    inline bool operator!=(const Color& c) const { return !(*this == c); }
    /**
     * @brief Get the current pixel color.
     * @return mColor value
     */
    inline uint32_t GetPixelColor() const { return mColor; }

    /**
     * @brief Set the uint32_t color value using RGBA values.
     * @param r Red
     * @param g Green
     * @param b Blue
     * @param a Alpha
     */
    void SetRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    /**
     * @brief Change the r value.
     * @param red The amount of the red color.
     */
    void SetRed(uint8_t red);
    /**
     * @brief Change the g value.
     * @param green The amount of green color.
     */
    void SetGreen(uint8_t green);
    /**
     * @brief Change the b value.
     * @param blue The amount of blue color.
     */
    void SetBlue(uint8_t blue);
    /**
     * @brief Change the a value.
     * @param alpha The amount of alpha.
     */
    void SetAlpha(uint8_t alpha);

    /**
     * @brief Get the r value.
     * @return the amount of red in the color.
     */
    uint8_t GetRed() const;
    /**
     * @brief Get the g value.
     * @return The amount of green in the color.
     */
    uint8_t GetGreen() const;
    /**
     * @brief Get the b value.
     * @return The amount of blue in the color.
     */
    uint8_t GetBlue() const;
    /**
     * @brief Get the a value.
     * @return The amount of alpha in the color.
     */
    uint8_t GetAlpha() const;
};

#endif //SDL_A_LINE_COLOR_H
