/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   HydraSegment.hpp
 * Author: edward
 *
 * Created on 23 de abril de 2018, 18:47
 */
#pragma once
#include "MathHelper.hpp"
#include "Game.hpp"
#include "Enemy.hpp"
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"

namespace Zenon {

    class HydraSegment : public Enemy {
    public:

        enum PART {
            cabeza = 0, cuerpo = 1, cola = 2
        };

        HydraSegment(GameDataRef l_data, Enemy::TYPE l_type, sf::Vector2f l_position, const std::vector<Enemy*>& l_neighbors, HydraSegment::PART l_part, Bezier& l_route);
        ~HydraSegment();
        void Update(float dt);
        void Draw();
        void PutDiving();
        void Stop();
        bool GetDiving();
        sf::Sprite GetSprite();
        int GetCurrentWP();

    private:

        Bezier& m_route;
        sf::Clock m_animationClock;
        std::vector<sf::IntRect> m_spriteRects;
        HydraSegment::PART m_part;
        bool m_diving = false;
        bool m_pathCompleted = false;
        int m_currentWP = 1;
        int m_animationIterator = 0;

    };
}