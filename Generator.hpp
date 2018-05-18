/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Generator.hpp
 * Author: edward
 *
 * Created on 29 de abril de 2018, 17:45
 */
#pragma once
#include "Objective.hpp"

namespace Zenon {

    class Generator : public Objective {
    public:

        Generator(GameDataRef l_data, sf::Vector2f l_position, const std::vector<Enemy*>& l_nearestEnemies, std::vector<Bezier>& l_routePaths);
        ~Generator();

        void Update(float dt);
        void Draw();

    private:

    };
}

