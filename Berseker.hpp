/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Berseker.hpp
 * Author: edward
 *
 * Created on 18 de abril de 2018, 19:14
 */
#pragma once

#include "Enemy.hpp"
#include "MathHelper.hpp"
#include"Maps.hpp"
#include "Hero.hpp"

namespace Zenon {

    class Berseker : public Enemy {
    public:

        Berseker(GameDataRef l_data, Enemy::TYPE l_type, sf::Vector2f l_position, const std::vector<Enemy*>& l_neighbors,
                Maps &l_map, std::vector<sf::Sprite>& l_objectives, const std::vector<Hero*>& l_heroes);

        ~Berseker();

        void Update(float dt);
        void Draw();
        void CheckPathObj();
        void CheckPathHero();
        void FindObj();
        void FindHero();
        bool CheckNearHero();
        void CheckState();
        int CheckNearestObj();


        //AUXILIAR
        void DrawDebugCircles();

    private:

        Maps& m_map;
        std::vector<sf::Sprite>& m_objectives;
        const std::vector<Hero*>& m_heroes;
        std::vector<sf::Vector2f> m_pathHero;
        std::vector<sf::Vector2f> m_pathObj;
        std::vector<sf::CircleShape> m_debugCircles;

        sf::Clock m_checkHeroClock;
        sf::Clock m_hitingClock;

        int m_currentWP = 1;
        int m_obj = 0;
        int m_heroTarget = 0;

        float m_damage = 20.0f;
        bool m_pathComplete = false;

    };
}



