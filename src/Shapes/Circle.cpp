#include "Circle.h"
#include "../Utils/Utils.h"

Circle::Circle() : Circle(Vec2D::sZERO, 0.0f) {}

Circle::Circle(const Vec2D& centerPoint, float radius) : mRadius(radius)
{
    mPoints.push_back(centerPoint);
}

bool Circle::Intersects(const Circle& otherCircle) const
{
    // Check if the distance between the points is less than the sum of both radiuses
    // This is often used in game development as checking the intersections of two circles is really fast
    return (GetCenterPoint().Distance(otherCircle.GetCenterPoint()) < (mRadius + otherCircle.mRadius));
}

bool Circle::ContainsPoint(const Vec2D& point) const
{
    // check if the distance between point and center is less than or equal to the radius
    return isLessThanOrEqual(GetCenterPoint().Distance(point), mRadius);
}