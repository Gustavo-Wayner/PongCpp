#pragma once

#include <raylib.h>
#include <iostream>
#include <cmath>

struct Vec2
{
    static float Dot(Vec2 vecA, Vec2 vecB);
    static float Angle(Vec2 vecA, Vec2 vecB);
    static void LimitMagnitude(Vec2 &vec, float max, float min = 0);

    float Magnitude();
    Vec2 GetUnitVector();
    void Normalize();
    void SetMagnitude(float scalar);

    float x;
    float y;
    Vec2() = default;
    Vec2(float _x, float _y);
    Vec2(float arr[2]);

#pragma region operator=
    Vec2 &operator=(Vec2 other)
    {
        this->x = other.x;
        this->y = other.y;

        return *this;
    }

    Vec2 &operator=(float (&other)[2])
    {
        this->x = other[0];
        this->y = other[1];

        return *this;
    }
#pragma endregion

#pragma region operator*
    Vec2 operator*(float scalar)
    {
        return {this->x * scalar, this->y * scalar};
    }

    friend Vec2 operator*(float &scalar, Vec2 &vec)
    {
        return {vec.x * scalar, vec.y * scalar};
    }

    Vec2 &operator*=(float scalar)
    {
        this->x *= scalar;
        this->y *= scalar;

        return *this;
    }
#pragma endregion

#pragma region operator/
    Vec2 operator/(float scalar)
    {
        return {this->x / scalar, this->y / scalar};
    }

    friend Vec2 operator/(float scalar, Vec2 vec)
    {
        return {vec.x / scalar, vec.y / scalar};
    }

    Vec2 &operator/=(float scalar)
    {
        this->x /= scalar;
        this->y /= scalar;

        return *this;
    }
#pragma endregion

#pragma region operator+
    Vec2 operator+(float other[2])
    {
        return {this->x + other[0], this->y + other[1]};
    }

    Vec2 operator+(Vec2 other)
    {
        return {this->x + other.x, this->y + other.y};
    }

    Vec2 &operator+=(Vec2 other)
    {
        this->x += other.x;
        this->y += other.y;

        return *this;
    }

    Vec2 &operator+=(float other[2])
    {
        this->x += other[0];
        this->y += other[1];

        return *this;
    }
#pragma endregion

#pragma region operator -
    Vec2 operator-(float other[2])
    {
        return {this->x - other[0], this->y - other[1]};
    }

    Vec2 operator-(Vec2 other)
    {
        return {this->x - other.x, this->y - other.y};
    }

    Vec2 &operator-=(Vec2 other)
    {
        this->x -= other.x;
        this->y -= other.y;

        return *this;
    }

    Vec2 &operator-=(float other[2])
    {
        this->x -= other[0];
        this->y -= other[1];

        return *this;
    }
#pragma endregion
};

inline int sign(float num) { return ((num > 1) - (num < 1)); }
inline float absolute(float num) { return num * sign(num); }

enum Space
{
    ScreenSpace,
    WorldSpace
};
