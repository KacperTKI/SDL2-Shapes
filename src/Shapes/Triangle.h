#ifndef SHAPES_TRIANGLE_H
#define SHAPES_TRIANGLE_H

#include "Shape.h"

/**
 * @brief Triangle class as a representation for the triangle shape.
 */
class Triangle: public Shape
{
public:
    /**
     * @brief Default Construcor
     */
    Triangle();
    /**
     * @brief Constructor
     * @param p0 First point
     * @param p1 Second point
     * @param p2 Third point
     */
    Triangle(const Vec2D& p0, const Vec2D& p1, const Vec2D& p2);

    /**
     * @brief Change the first point.
     * @param p0 New point
     */
    inline void SetP0(const Vec2D& p0) { mPoints[0] = p0; }
    /**
     * @brief Change the second point.
     * @param p1 New point
     */
    inline void SetP1(const Vec2D& p1) { mPoints[1] = p1; }
    /**
     * @brief Change the third point.
     * @param p2 New point
     */
    inline void SetP2(const Vec2D& p2) { mPoints[2] = p2; }

    /**
     * @brief Get the first point.
     * @return First point
     */
    inline Vec2D GetP0() const { return mPoints[0]; }
    /**
     * @brief Get the second point.
     * @return Second point
     */
    inline Vec2D GetP1() const { return mPoints[1]; }
    /**
     * @brief Get the third point.
     * @return Third point
     */
    inline Vec2D GetP2() const { return mPoints[2]; }

    /**
     * @brief Get the center point of the triangle.
     * @return The center point
     */
    virtual Vec2D GetCenterPoint() const override;

    /**
     * @brief Get the area of this triangle.
     * @return Area
     */
    float Area() const;

    /**
     * @brief Check if a given point is in the triangle.
     * @param p point to check
     * @return true if the point is in the triangle
     * @return false otherwise
     */
    bool ContainsPoint(const Vec2D& p) const;

private:
    /**
     * @brief Get the area of a triangle with the given three points.
     * @param p0 First point
     * @param p1 Second point
     * @param p2 Third point
     * @return The area of the given triangle.
     */
    float Area(const Vec2D& p0, const Vec2D& p1, const Vec2D& p2) const;

};

#endif