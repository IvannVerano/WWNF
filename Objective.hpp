/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Objective.hpp
 * Author: edward
 *
 * Created on 28 de abril de 2018, 19:30
 */
#pragma once
#include "Game.hpp"
#include "DEFINITIONS.hpp"
#include "MathHelper.hpp"
#include "Enemy.hpp"

namespace Zenon {

    class Objective {
    public:

        Objective(GameDataRef l_data, sf::Vector2f l_position, const std::vector<Enemy*>& l_nearestEnemies, Bezier& l_routePath);
        ~Objective();

        virtual void Update(float dt);
        virtual void Draw();
        void TakeDamage(int l_factor);
        bool Intersects(sf::FloatRect l_rect);
        int GetActualState();
        int GetLife();
        sf::Vector2f GetPosition();
        sf::FloatRect GetGB();

    protected:

        GameDataRef m_data;
        sf::Sprite m_mainSprite;
        Bezier& m_routePath;
        int m_life = 50;
        int m_state = OBJECTIVE_ACTIVE_STATE;

        const std::vector<Enemy*>& m_nearestEnemies;

    };

}


