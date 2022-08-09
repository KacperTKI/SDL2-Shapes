//
// Created by Tomaszewski on 03.10.2021.
//

#include "Utils.h"

bool IsEqual(float x, float y) {
    return fabsf(x - y) < EPSILON;
}

bool IsGreaterThanOrEqual(float x, float y) {
    return x > y || IsEqual(x, y);
}

bool isLessThanOrEqual(float x, float y) {
    return x < y || IsEqual(x, y);
}
