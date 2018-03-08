/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Ataque.hpp
 * Author: antonio
 *
 * Created on 8 de marzo de 2018, 17:40
 */

#pragma once
#include "Trampa.hpp"
#include <SFML/Graphics.hpp>

namespace Zenon
{
    class Ataque : public Trampa
    {
        public:
            Ataque(GameDataRef data, sf::Vector2f posicion);
            void Draw();
            void Update(float dt);
        private:
            
    };
}