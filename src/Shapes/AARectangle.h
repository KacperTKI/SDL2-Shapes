#ifndef SHAPES_AARECTANGLE_H
#define SHAPES_AARECTANGLE_H

#include "Shape.h"

class AARectangle: public Shape
{
public:
    /**
     * @brief Default Constructor
     */
    AARectangle();
    /**
     * @brief Constructor
     * @param topLeft The top left point of the rectangle.
     * @param width The width of the rectangle.
     * @param height The height of the rectangle.
     */
    AARectangle(const Vec2D& topLeft, unsigned int width, unsigned int height);
    /**
     * @brief Constructor
     * @param topLeft The top left point of the rectangle.
     * @param bottomRight The bottom left point of the rectangle.
     */
    AARectangle(const Vec2D& topLeft, const Vec2D& bottomRight);

    /**
     * @brief Set a new point as the top left point of the rectangle.
     * @param topLeft The new top left point.
     */
    inline void SetTopLeft(const Vec2D& topLeft) { mPoints[0] = topLeft; }
    /**
     * @brief Set a new point as the bottom right point of the rectangle.
     * @param bottomRight The new bottom right point.
     */
    inline void SetBottomRight(const Vec2D& bottomRight) { mPoints[1] = bottomRight; }

    /**
     * @brief Get the top left point.
     * @return Top left Vec2D point
     */
    inline Vec2D GetTopLeft() const { return mPoints[0]; }
    /**
     * @brief Get the bottom right point.
     * @return Bottom right Vec2D point
     */
    inline Vec2D GetBottomRight() const { return mPoints[1]; }

    /**
     * @brief Get the width of the rectangle.
     * @return Width of the rectangle.
     */
    float GetWidth() const;
    /**
     * @brief Get the height of the rectangle.
     * @return Height of the rectangle.
     */
    float GetHeight() const;

    /**
     * @brief Move the rectangle to a new position.
     * @param position The new position of the rectangle.
     */
    void MoveTo(const Vec2D& position);

    /**
     * @brief Get the center point of the rectangle.
     * @return The center point 
     */
    virtual Vec2D GetCenterPoint() const override;

    /**
     * @brief Check if another rectangle intersects this rectangle.
     * @param otherRect The other rectangle
     * @return true if it intersects
     * @return false otherwise.
     */
    bool Intersects(const AARectangle& otherRect) const;
    /**
     * @brief Check if a point is in the rectangle.
     * @param point The point
     * @return true if it is in the rectangle
     * @return false otherwise.
     */
    bool CotaintsPoint(const Vec2D& point) const;

    /**
     * @brief Create an inset rectangle of a rectangle.
     * @param rect The rectangle from which the inset should be created.
     * @param insets The insets
     * @return A new inset rectangle
     */
    static AARectangle Inset(const AARectangle& rect, Vec2D& insets);

    /**
     * @brief Get the points of the rectangle.
     * @return A vector with all the four points.
     */
    virtual std::vector<Vec2D> GetPoints() const override;
};

#endif // SHAPES_AARECTANGLE_H