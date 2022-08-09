//
// Created by Tomaszewski on 03.10.2021.
//

#ifndef UTILS_VECTOR2D_H
#define UTILS_VECTOR2D_H

#include "Utils.h"

#include <cassert>
#include <cmath>
#include <iostream>

class Vec2D {
public:
    Vec2D();
    Vec2D(float x, float y);

    static const Vec2D sZERO;

    inline void SetX(float x) { mX = x; }
    inline void SetY(float y) { mY = y; }
    inline float GetX() const { return mX; }
    inline float GetY() const { return mY; }

    friend std::ostream& operator<<(std::ostream& ConsoleOut, const Vec2D &vec);
    friend Vec2D operator*(float scalar, const Vec2D &vec);

    // Operators for vector comparison
    bool operator ==(const Vec2D &vec2) const;
    bool operator!=(const Vec2D &vec2) const;

    Vec2D operator-() const; // Vector Negation
    Vec2D operator*(float scale) const; // Vector Multiplication
    Vec2D operator/(float scale) const; // Vector Division
    Vec2D operator*=(float scale);
    Vec2D operator/=(float scale);
    Vec2D operator+(const Vec2D &vec2) const; // Vector Addition
    Vec2D operator-(const Vec2D &vec2) const; // Vector Subtraction
    Vec2D operator+=(const Vec2D &vec2);
    Vec2D operator-=(const Vec2D &vec2);

    float Mag2() const; // Vector Magnitude (The Length of a Vector)
    float Mag() const;

    Vec2D GetUnitVec() const; // A Unit Vector basically has a length of 1
    Vec2D& Normalize();

    float Distance(const Vec2D &vec2) const; // Getting the distance between two vectors
    float Dot(const Vec2D &vec2) const; // The dot product of two vectors

    Vec2D ProjectOnto(const Vec2D &vec2) const; // Scalar projection of @this vector onto @vec2

    float AngleBetween(const Vec2D &vec2) const; // Getting the angle between two vectors

    Vec2D Reflect(const Vec2D &normal) const; // Reflection of a vector from a normal

    void Rotate(float angle, const Vec2D &aroundPoint);
    Vec2D RotationResult(float angle, const Vec2D &aroundPoint) const;

private:
    float mX;
    float mY;
};


#endif //UTILS_VECTOR2D_H
