/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Trampa.hpp
 * Author: antonio
 *
 * Created on 8 de marzo de 2018, 17:29
 */

#pragma once
#include "Game.hpp"
#include <SFML/Graphics.hpp>
namespace Zenon
{
    class Trampa
    {
        public:
            Trampa(GameDataRef data):_datos(data) 
            {
                 
            }
            virtual void Update(float dt){};
            virtual void Draw(){};
        protected:
            GameDataRef _datos;
            sf::Sprite mainSprite;
            
    };
}