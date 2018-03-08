/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Placer.hpp
 * Author: antonio
 *
 * Created on 8 de marzo de 2018, 18:40
 */

#pragma once
#include "Game.hpp"

namespace Zenon
{
    class Placer
    {
        public:
            Placer(GameDataRef data, sf::Vector2f pos);
            ~Placer();
            bool Clicked();
            sf::Vector2f GetPosicion();
            void Draw();
        private:
            GameDataRef datos;
            sf::Sprite mainSprite;
            sf::Vector2f posicion;
            bool ocupado;
    };
}
