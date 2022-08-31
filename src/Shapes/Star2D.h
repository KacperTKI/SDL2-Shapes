//
// Created by Kacper Tomaszewski on 06.08.22.
//

#ifndef SHAPES_STAR2D_H
#define SHAPES_STAR2D_H

#include <vector>

#include "../Utils/Vec2D.h"
#include "Line2D.h"

/**
 * @brief The Star2D class is used as representation as well (just like Line2D), so that the screen can use it to draw a star.
 */
class Star2D {
private:
    Vec2D mCenter;
    std::vector<Line2D> mStarLines;
    int mRadius1;
    int mRadius2;
    int mNumSpikes;

    const float pi = 3.141592f * 2.0f;

public:
    /**
     * @brief Defualt Constructor
     */
    Star2D();
    /**
     * @brief Constructor
     * 
     * @param center The center point of the star.
     * @param radius1 The length of the first radius.
     * @param radius2 The length of the second radius.
     * @param numSpikes The amount of spikes the star should have.
     */
    Star2D(Vec2D center, int radius1, int radius2, int numSpikes);

    inline int GetStarSize() const { return mStarLines.size(); }
    inline const Vec2D& GetCenter() { return mCenter; }
    inline Line2D& operator[](size_t index) { return mStarLines[index]; }

    /**
     * @brief Rotate the whole Star by an given angle around a given point.
     * 
     * @param angle The rotation angle
     * @param aroundPoint The center point around which the star is being rotated.
     */
    void RotateStar(const float angle, const Vec2D& aroundPoint);
};

#endif
