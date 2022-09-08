#ifndef SHAPES_SHAPE_H
#define SHAPES_SHAPE_H

#include <vector>

#include "../Utils/Vec2D.h"

/**
 * @brief Shape class will be used as the base class for all the shapes, that will be created.
 */
class Shape
{
public:
    /**
     * @brief Destructor
     */
    virtual ~Shape() {}
    /**
     * @brief Get the Center Point object.
     * @return The center point
     */
    virtual Vec2D GetCenterPoint() const =0;
    /**
     * @brief Get the points vector
     * @return mPoints
     */
    inline virtual std::vector<Vec2D> GetPoints() const { return mPoints; }
    /**
     * @brief Move all the points by the offset.
     * @param deltaOffset By how much the points should be moved.
     */
    void MoveBy (const Vec2D& deltaOffset);

    /**
     * @brief Move the shape to the given point
     * @param p New point of the shape
     */
    virtual void MoveTo(const Vec2D& p) = 0;

protected:
    std::vector<Vec2D> mPoints;
};

#endif
