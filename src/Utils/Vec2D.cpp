//
// Created by Tomaszewski on 03.10.2021.
//

#include "Vec2D.h"

Vec2D::Vec2D() : Vec2D(0, 0) {

}

Vec2D::Vec2D(float x, float y)
        : mX(x), mY(y) {

}

const Vec2D Vec2D::sZERO { 0, 0 };

std::ostream &operator<<(std::ostream &ConsoleOut, const Vec2D& vec) {
    ConsoleOut << "X: " << vec.mX << " Y: " << vec.mY;
    return ConsoleOut;
}

Vec2D operator*(float scalar, const Vec2D& vec) {
    return vec * scalar;
}

bool Vec2D::operator==(const Vec2D &vec2) const {
    return IsEqual(this->mX, vec2.mX) && IsEqual(this->mY, vec2.mY);
}

bool Vec2D::operator!=(const Vec2D &vec2) const {
    return !(*this == vec2);
}

Vec2D Vec2D::operator-() const {
    return Vec2D{-this->mX, -this->mY};
}

Vec2D Vec2D::operator*(float scale) const {
    return Vec2D{(this->mX * scale), (this->mY * scale)};
}

Vec2D Vec2D::operator/(float scale) const {
    assert(fabsf(scale) > EPSILON);

    return Vec2D{(this->mX / scale), (this->mY / scale)};
}

Vec2D Vec2D::operator*=(float scale) {
    *this = *this * scale;
    return *this;
}

Vec2D Vec2D::operator/=(float scale) {
    assert(fabsf(scale) > EPSILON);

    *this = *this / scale;
    return *this;
}

Vec2D Vec2D::operator+(const Vec2D &vec2) const {
    return Vec2D{(this->mX + vec2.mX), (this->mY + vec2.mY)};
}

Vec2D Vec2D::operator-(const Vec2D &vec2) const {
    return *this + -vec2;
}

Vec2D Vec2D::operator+=(const Vec2D &vec2) {
    *this = *this + vec2;
    return *this;
}

Vec2D Vec2D::operator-=(const Vec2D &vec2) {
    *this = *this - vec2;
    return *this;
}

float Vec2D::Mag2() const {
    return (this->mX * this->mX) + (this->mY * this->mY);
}

float Vec2D::Mag() const {
    return std::sqrt(Mag2());
}

Vec2D Vec2D::GetUnitVec() const {
    float mag = this->Mag();
    if (mag > EPSILON) {
        return Vec2D::sZERO;
    }

    return *this / mag;
}

Vec2D& Vec2D::Normalize() {
    float mag = this->Mag();
    if (mag > EPSILON) {
        *this /= mag;
    }

    return *this;
}

float Vec2D::Distance(const Vec2D &vec2) const {
    return (vec2 - *this).Mag();
}

float Vec2D::Dot(const Vec2D &vec2) const {
    return (this->mX * vec2.mX) + (this->mY * vec2.mY);
}

Vec2D Vec2D::ProjectOnto(const Vec2D &vec2) const {
    Vec2D uVec2 = vec2.GetUnitVec();
    float dot = this->Dot(uVec2);

    return uVec2 * dot;
}

float Vec2D::AngleBetween(const Vec2D &vec2) const {
    return acosf((this->GetUnitVec().Dot(vec2.GetUnitVec())));
}

Vec2D Vec2D::Reflect(const Vec2D &normal) const {
    /*
     *  The formula to get the reflection vector is:
     *      reflection = aVec - 2 * (aVec * nVec) * nVec
     *
     *  NOTE: nVec is the normalized vector perpendicular to the surface which aVec is in contact with
     * */

    return *this - 2 * ProjectOnto(normal);
}

void Vec2D::Rotate(float angle, const Vec2D &aroundPoint) {
    float cosine = cosf(angle); //cosf and sinf take radiants not degrees!
    float sine = sinf(angle);

    Vec2D oldVec { mX, mY };
    oldVec -= aroundPoint; // bring the vector to the middle

    float newX = (oldVec.mX * cosine) - (oldVec.mY * sine);
    float newY = (oldVec.mX * sine) + (oldVec.mY * cosine);

    Vec2D newVec = Vec2D{newX, newY};

	*this = newVec + aroundPoint; // we have to bring the rotated vector into the right place
}

Vec2D Vec2D::RotationResult(float angle, const Vec2D &aroundPoint) const {
    float cosine = cosf(angle);
    float sine = sinf(angle);

    Vec2D oldVec { mX, mY };
    oldVec -= aroundPoint;

    float newX = (oldVec.mX * cosine) - (oldVec.mY * sine);
    float newY = (oldVec.mX * sine) + (oldVec.mY * cosine);

    Vec2D newVec = Vec2D{newX, newY};

    return newVec + aroundPoint;
}
