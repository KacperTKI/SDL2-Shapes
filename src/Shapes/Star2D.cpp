#include "Star2D.h"

Star2D::Star2D() : Star2D(Vec2D(0, 0), 0, 0, 0) {}

Star2D::Star2D(Vec2D center, int radius1, int radius2, int numSpikes)
    : mCenter(center), mRadius1(radius1), mRadius2(radius2), mNumSpikes(numSpikes)
{
    Vec2D length1 = Vec2D(mCenter.GetX(), mCenter.GetY() - mRadius1);
    Vec2D length2 = Vec2D(mCenter.GetX(), mCenter.GetY() - mRadius2);

    length2.Rotate(pi / (mNumSpikes * 2), mCenter);

    mStarLines.clear();
    Line2D currLine;
    for (size_t i = 0; i < mNumSpikes * 2; i++)
    {
        currLine.SetP0(length1);
        currLine.SetP1(length2);
        mStarLines.push_back(currLine);

        if (i % 2 == 0)
        {
            length1.Rotate(pi / mNumSpikes, mCenter);
        }
        else
        {
            length2.Rotate(pi / mNumSpikes, mCenter);
        }
    }
}

Star2D::Star2D(const Star2D& star)
    : Star2D(star.mCenter, star.mRadius1, star.mRadius2, star.mNumSpikes)
{

}

void Star2D::UpdateCenter(const Vec2D& newPos)
{
    mCenter = newPos;
    Vec2D length1 = Vec2D(mCenter.GetX(), mCenter.GetY() - mRadius1);
    Vec2D length2 = Vec2D(mCenter.GetX(), mCenter.GetY() - mRadius2);

    length2.Rotate(pi / (mNumSpikes * 2), mCenter);

    mStarLines.clear();
    Line2D currLine;
    for (size_t i = 0; i < mNumSpikes * 2; i++)
    {
        currLine.SetP0(length1);
        currLine.SetP1(length2);
        mStarLines.push_back(currLine);

        if (i % 2 == 0)
        {
            length1.Rotate(pi / mNumSpikes, mCenter);
        }
        else
        {
            length2.Rotate(pi / mNumSpikes, mCenter);
        }
    }
}

void Star2D::RotateStar(const float angle, const Vec2D& aroundPoint)
{
    for (size_t i = 0; i < mStarLines.size(); i++)
    {
        mStarLines[i].SetP0(mStarLines[i].GetP0().RotationResult(angle, aroundPoint));
        mStarLines[i].SetP1(mStarLines[i].GetP1().RotationResult(angle, aroundPoint));
    }
}

float Star2D::Area() const
{
    // NOTE: Only works for 5-pointed stars!
    float num = 10 * (tan((pi / 2) / 10));
    float den = 3 - pow(tan((pi / 2) / 10), 2);

    return (num / den) * pow(mRadius1, 2);
}
