#ifndef SHAPES_CIRCLE_H
#define SHAPES_CIRCLE_H

#include "Shape.h"

class Circle: public Shape
{
public:
    /**
     * @brief Default Constructor
     */
    Circle();
    /**
     * @brief Constructor
     * @param centerPoint The center point of the circle. 
     * @param radius The radius of the circle.
     */
    Circle(const Vec2D& centerPoint, float radius);

    /**
     * @brief Get the center point of the circle.
     * @return Center Vec2D point
     */
    inline virtual Vec2D GetCenterPoint() const override { return mPoints[0]; }
    /**
     * @brief Get the radius of the circle.
     * @return float radius
     */
    inline float GetRadius() const { return mRadius; }
    /**
     * @brief Change the value of the radius.
     * @param radius New radius value
     */
    inline void SetRadius(float radius) { mRadius = radius; }
    /**
     * @brief Move the circle center point to a new position.
     * @param position The new position of the circle.
     */
    inline void MoveTo(const Vec2D& position) { mPoints[0] = position; }

    /**
     * @brief Check if another circle intersects with this one.
     * @param otherCircle The other circle, which is compared.
     * @return true if there is an intersection
     * @return false otherwise
     */
    bool Intersects(const Circle& otherCircle) const;
    /**
     * @brief Check if a point is in the circle.
     * @param point The point that should be checked.
     * @return true if the point is within the circle
     * @return false otherwise
     */
    bool ContainsPoint(const Vec2D& point) const;

private:
    float mRadius;

};

#endif