//
// Created by Tomaszewski on 03.10.2021.
//

#ifndef UTILS_UTILS_H
#define UTILS_UTILS_H

#include <cmath>

const float PI = 3.14159f;
const float TWO_PI = 2.0f * PI;

static const float EPSILON = 0.0001f;

bool IsEqual(float x, float y);
bool IsGreaterThanOrEqual(float x, float y);
bool isLessThanOrEqual(float x, float y);

#endif //UTILS_UTILS_H
