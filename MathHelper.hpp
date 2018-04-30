#pragma once
#include <math.h>
#include <valarray>
#include <vector>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>
#include <complex>
#include "DEFINITIONS.hpp"

namespace Zenon {

#define PI 3.14159265
#define DEG_TO_RAD PI / 180.0f
#define RAD_TO_DEG 180.0f / PI

    inline float Module(sf::Vector2f& vec) {
        return std::sqrt(vec.x * vec.x + vec.y * vec.y);
    }

    inline sf::Vector2f NormalizeDir(sf::Vector2f vec1, sf::Vector2f vec2) {
        sf::Vector2f temp = vec1 - vec2;
        float d = Module(temp);
        return sf::Vector2f(temp.x / d, temp.y / d);
    }

    inline sf::Vector2f Normalize(sf::Vector2f vec, float d) {
        return sf::Vector2f(vec.x / d, vec.y / d);
    }

    inline sf::Vector2f InverseDir(sf::Vector2f& vec) {
        return sf::Vector2f(vec.x * -1, vec.y * -1);
    }

    inline sf::Vector2f operator+(sf::Vector2f& vec1, sf::Vector2f& vec2) {
        return sf::Vector2f(vec1.x + vec2.x, vec1.y + vec2.y);
    }

    inline sf::Vector2f Resultant(sf::Vector2f& vec1, sf::Vector2f& vec2) {

        return sf::Vector2f(vec1.x * ENEMY_FACTOR + vec2.x * WP_FACTOR, vec1.y * ENEMY_FACTOR + vec2.y * WP_FACTOR);
    }

    inline sf::Vector2f operator-(sf::Vector2f& vec1, sf::Vector2f& vec2) {

        return sf::Vector2f(vec1.x - vec2.x, vec1.y - vec2.y);
    }

    inline sf::Vector2f Scale(sf::Vector2f& vec, float n) {
        return sf::Vector2f(vec.x * n, vec.y * n);
    }

    inline float LimitV(float number) {
        if (number > 0) {
            if (number > 0.3) {
                number = 0.3;
            }
        } else if (number < 0) {
            if (number < -0.3) {

                number = -0.3;
            }
        }
        return number;
    }

    struct Bezier {
        int probability;
        bool m_transitable = true;
        sf::Vector2f m_startPoint;
        sf::Vector2f m_endPoint;
        sf::Vector2f m_controlPoint1;
        sf::Vector2f m_controlPoint2;
        std::size_t m_segments;
        std::map<int, sf::Vector2f> m_bPoints;
        std::vector<Bezier> m_bRoutes;
        std::vector<sf::Vector2f> m_bezierBody;

        void create() {

            std::vector<sf::Vector2f> ret;

            if (!m_segments) {
                printf("No has pasado segmentos");
            }

            ret.push_back(m_startPoint);
            float p = 1.f / m_segments;
            float q = p;

            for (size_t i = 1; i < m_segments; i++, p += q) {
                ret.push_back(p * p * p * (m_endPoint + 3.f * (m_controlPoint1 - m_controlPoint2) - m_startPoint) +
                        3.f * p * p * (m_startPoint - 2.f * m_controlPoint1 + m_controlPoint2) +
                        3.f * p * (m_controlPoint1 - m_startPoint) + m_startPoint);
            }

            ret.push_back(m_endPoint);
            m_bezierBody = ret;

        }

        void AddCurve(sf::Vector2f l_startPoint, sf::Vector2f l_endPoint, sf::Vector2f l_controlPoint1, sf::Vector2f l_controlPoint2, int l_segments) {
            std::vector<sf::Vector2f> ret;

            if (!l_segments) {
                printf("No has pasado segmentos");
            }

            ret.push_back(l_startPoint);
            float p = 1.f / l_segments;
            float q = p;

            for (size_t i = 1; i < l_segments; i++, p += q) {
                ret.push_back(p * p * p * (l_endPoint + 3.f * (l_controlPoint1 - l_controlPoint2) - l_startPoint) +
                        3.f * p * p * (l_startPoint - 2.f * l_controlPoint1 + l_controlPoint2) +
                        3.f * p * (l_controlPoint1 - l_startPoint) + l_startPoint);
            }

            ret.push_back(l_endPoint);
            for (int i = 0; i < ret.size(); i++) {
                m_bezierBody.push_back(ret[i]);
            }
        }

        void MirrorX(int d) {
            for (int i = 0; i < m_bezierBody.size(); i++) {
                m_bezierBody[i].x = (m_bezierBody[i].x * -1) + d;
            }
        }

        void MirrorY(int d) {
            for (int i = 0; i < m_bezierBody.size(); i++) {
                m_bezierBody[i].y = (m_bezierBody[i].y * -1) + d;
            }
        }

        void SetIntransitable() {
            m_transitable = false;
        }

        bool IsTransitable() {
            return m_transitable;
        }
    };

}