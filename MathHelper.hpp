#pragma once
#include <math.h>
#include <valarray>
#include <vector>

namespace Galaga {

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

struct Point2D {
    float x;
    float y;
};

struct Spline2D {
    std::vector<Point2D> m_points;

    Point2D GetSplinePoint(float t, bool bLooped = false) {
        int p0, p1, p2, p3;
        if (!bLooped) {
            p1 = (int) t + 1;
            p2 = p1 + 1;
            p3 = p2 + 1;
            p0 = p1 - 1;
        } else {
            p1 = (int) t;
            p2 = (p1 + 1) % m_points.size();
            p3 = (p2 + 1) % m_points.size();
            p0 = p1 >= 1 ? p1 - 1 : m_points.size() - 1;
        }

        t = t - (int) t;

        float tt = t * t;
        float ttt = tt * t;

        float q1 = -ttt + 2.0f * tt - t;
        float q2 = 3.0f * ttt - 5.0f * tt + 2.0f;
        float q3 = -3.0f * ttt + 4.0f * tt + t;
        float q4 = ttt - tt;

        float tx = 0.5f * (m_points[p0].x * q1 + m_points[p1].x * q2 + m_points[p2].x * q3 + m_points[p3].x * q4);
        float ty = 0.5f * (m_points[p0].y * q1 + m_points[p1].y * q2 + m_points[p2].y * q3 + m_points[p3].y * q4);

        return{ tx, ty};
    }

};


