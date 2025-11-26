#include "Structs.h"

#pragma region Vector2
float Vec2::Dot(Vec2 vecA, Vec2 vecB)
{
    return vecA.x * vecB.x + vecA.y * vecB.y;
}
float Vec2::Angle(Vec2 vecA, Vec2 vecB)
{
    return acos(Vec2::Dot(vecA, vecB) / (vecA.Magnitude() * vecB.Magnitude()));
}
void Vec2::LimitMagnitude(Vec2 &vec, float max, float min)
{
    if (vec.Magnitude() > max)
        vec.SetMagnitude(max);
    else if (vec.Magnitude() < min)
        vec.SetMagnitude(min);
}

float Vec2::Magnitude() { return sqrt(Dot(*this, *this)); }

Vec2 Vec2::GetUnitVector() { return *this / Magnitude(); }

void Vec2::Normalize() { *this /= Magnitude(); }

void Vec2::SetMagnitude(float scalar)
{
    Normalize();
    *this *= scalar;
}

Vec2::Vec2(float _x, float _y) : x(_x), y(_y) {}
Vec2::Vec2(float arr[2]) : x(arr[0]), y(arr[1]) {}
#pragma endregion