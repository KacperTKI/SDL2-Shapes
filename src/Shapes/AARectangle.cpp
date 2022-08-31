#include "AARectangle.h"

AARectangle::AARectangle() : AARectangle(Vec2D::sZERO, Vec2D::sZERO) 
{

}

AARectangle::AARectangle(const Vec2D& topLeft, unsigned int width, unsigned int height)
{
    mPoints.push_back(topLeft);
    mPoints.push_back(Vec2D(topLeft.GetX() + width - 1, topLeft.GetY() + height - 1));
}

AARectangle::AARectangle(const Vec2D& topLeft, const Vec2D& bottomRight)
{
    mPoints.push_back(topLeft);
    mPoints.push_back(bottomRight);
}

float AARectangle::GetWidth() const 
{
    return (GetBottomRight().GetX() - GetTopLeft().GetX() + 1);
}

float AARectangle::GetHeight() const
{
    return (GetBottomRight().GetY() - GetTopLeft().GetY() + 1);
}

void AARectangle::MoveTo(const Vec2D& position)
{
    float width = GetWidth();
    float height = GetHeight();

    SetTopLeft(position);
    SetBottomRight(Vec2D(position.GetX() + width - 1, position.GetY() + height - 1));
}

Vec2D AARectangle::GetCenterPoint() const 
{
    return Vec2D(GetTopLeft().GetX() + GetWidth() / 2.0f, GetTopLeft().GetY() + GetHeight() / 2.0f);
}

bool AARectangle::Intersects(const AARectangle& otherRect) const
{
    return !(otherRect.GetBottomRight().GetY() < GetTopLeft().GetY() ||
            otherRect.GetTopLeft().GetX() > GetBottomRight().GetX() ||
            otherRect.GetTopLeft().GetY() > GetBottomRight().GetY() ||
            otherRect.GetBottomRight().GetX() < GetTopLeft().GetX());
}

bool AARectangle::CotaintsPoint(const Vec2D& point) const 
{
    return (point.GetY() <= GetBottomRight().GetY() && point.GetY() >= GetTopLeft().GetY()) && 
           (point.GetX() >= GetTopLeft().GetX() && point.GetX() <= GetBottomRight().GetX());
}

AARectangle AARectangle::Inset(const AARectangle& rect, Vec2D& insets)
{
    return AARectangle(rect.GetTopLeft() + insets, rect.GetWidth() - 2*insets.GetX(), rect.GetHeight() - 2*insets.GetY());
}

std::vector<Vec2D> AARectangle::GetPoints() const
{
    std::vector<Vec2D> points;

    points.push_back(GetTopLeft());
    points.push_back(Vec2D(GetBottomRight().GetX(), GetTopLeft().GetY()));
    points.push_back(GetBottomRight());
    points.push_back(Vec2D(GetTopLeft().GetX(), GetBottomRight().GetY()));

    return points;
}