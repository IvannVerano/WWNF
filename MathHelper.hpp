#pragma once
#include <math.h>
#include <valarray>
#include <vector>

namespace Zenon {

#define PI 3.14159265
#define DEG_TO_RAD PI / 180.0f

    struct Vector2 {
        float x;
        float y;

        Vector2(float l_x = 0.0f, float l_y = 0.0f) : x(l_x), y(l_y) {
        }

        float MagnitudeSqr() {

            return x * x + y * y;
        }

        float Magnitude() {

            return std::sqrt(x * x + y * y);

        }

        Vector2 Normalized() {

            float mag = Magnitude();

            return Vector2(x / mag, y / mag);

        }

    };

    inline Vector2 operator+(const Vector2& lhs, const Vector2& rhs) {

        return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
    }

    inline Vector2 operator-(const Vector2& lhs, const Vector2& rhs) {

        return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
    }

    inline Vector2 RotateVector(Vector2& vec, float angle) {

        float radAngle = (float) (angle * DEG_TO_RAD);

        return Vector2((float) (vec.x * std::cos(radAngle) - vec.y * std::sin(radAngle)), (float) (vec.x * std::sin(radAngle) + vec.y * std::cos(radAngle)));

    }
}


