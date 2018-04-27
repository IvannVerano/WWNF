/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Hydra.hpp
 * Author: edward
 *
 * Created on 23 de abril de 2018, 16:18
 */
#pragma once
#include "Enemy.hpp"
#include "HydraSegment.hpp"
#include "MathHelper.hpp"

namespace Zenon {

    class Hydra : public Enemy {
    public:
        Hydra(GameDataRef l_data, Enemy::TYPE l_type, sf::Vector2f l_position, const std::vector<Enemy*>& l_neighbors, Bezier& l_route);
        ~Hydra();
        void Update(float dt);
        void Draw();
        void LoadBody();
        void LaunchParts();
        void CheckAllLaunched();
        void CheckBodySize();
        HydraSegment* GetPart(int l_member);
        int GetBodySize();
    private:

        Bezier& m_route;
        std::vector<HydraSegment*> m_parts;
        HydraSegment * m_s;
        int m_currentWP = 1;
        int m_nsegments = 10;
        sf::Clock m_divingClock;
        int m_divingIterator = 0;
        bool m_pathCompleted = false;
        bool m_allLaunched = false;
        bool m_bodyEmpty = false;

    };
}