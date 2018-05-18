/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Generator.cpp
 * Author: edward
 *
 * Created on 29 de abril de 2018, 17:45
 */

#include "Generator.hpp"

namespace Zenon {

    Generator::Generator(GameDataRef l_data, sf::Vector2f l_position, const std::vector<Enemy*>& l_nearestEnemies, std::vector<Bezier>& l_routePaths) : Objective(l_data, l_position, l_nearestEnemies, l_routePaths) {

        m_life = 100;
        m_mainSprite.setTexture(this->m_data->assets.GetTexture("point1"));
        m_mainSprite.setOrigin(m_mainSprite.getGlobalBounds().width / 2, m_mainSprite.getGlobalBounds().height / 2);
        m_mainSprite.scale(GENERATOR_SCALEX, GENERATOR_SCALEY);
        m_mainSprite.setPosition(l_position);


    }

    Generator::~Generator() {

    }

    void Generator::Update(float dt) {



    }

    void Generator::Draw() {
        this->m_data->window.draw(m_mainSprite);
    }

}
