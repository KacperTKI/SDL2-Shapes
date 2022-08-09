//
// Created by Kacper Tomaszewski on 01.08.22.
//

#ifndef SHAPES_LINE2D_H
#define SHAPES_LINE2D_H

#include "../Utils/Vec2D.h"

/**
 * @brief This class is not meant for drawing the line, it's meant as representation to use throughout the app.
 */
class Line2D {
private:
    Vec2D mP0;
    Vec2D mP1;

public:
    /**
     * @brief Default Constructor
     */
    Line2D();
    /**
     * @brief Constructor
     * @param x0 First points x value.
     * @param y0 First points y value.
     * @param x1 Second points x value.
     * @param y1 Second points y value.
     */
    Line2D(float x0, float y0, float x1, float y1);
    /**
     * @brief Constructor
     * @param p0 The first point.
     * @param p1 The second point.
     */
    Line2D(const Vec2D& p0, const Vec2D& p1);

    /**
     * @brief Get the first point vector.
     * @return mP0 Vector
     */
    inline const Vec2D& GetP0() const { return mP0; }
    /**
     * @brief Get the second point vector.
     * @return mP1 Vector
     */
    inline const Vec2D& GetP1() const { return mP1; }

    /**
     * @brief Change the first point vector.
     * @param p Point that should be applied.
     */
    inline void SetP0(const Vec2D& p) { mP0 = p; }
    /**
     * @brief Change the second point vector.
     * @param p Point that should be applied.
     */
    inline void SetP1(const Vec2D& p) { mP1 = p; }

    /**
     * @brief Compare to a different line.
     * @param line The line which should be compared to this.
     * @return true if they're the same.
     * @return false if they're not the same.
     */
    bool operator==(const Line2D& line) const;

    /**
     * @brief Get the distance from the closest point that p would be on.
     * @param p The point from which we want the distance.
     * @param limitToSegment A flag to check if it's infinite or not.
     * @return The distance from the closest point.
     */
    float MinDistanceFrom(const Vec2D& p, bool limitToSegment = false) const;

    /**
     * @brief Get the closest point to the line.
     * @param p The point we want to get the closest point of.
     * @param limitToSegment A flag to check if it's infinite or not.
     * @return The closest point to the line.
     */
    Vec2D ClosestPoint(const Vec2D& p, bool limitToSegment = false) const;

    /**
     * @brief Get the midpoint of the line
     * @return The midpoint as a vector.
     */
    Vec2D Midpoint() const;
    /**
     * @brief Get the sloap of the line.
     * @return The sloap of the line.
     */
    float Slope() const;
    /**
     * @brief Get the length of the line.
     * @return The length of the line.
     */
    float Length() const;
};

#endif
