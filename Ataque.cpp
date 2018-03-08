/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Ataque.cpp
 * Author: antonio
 * 
 * Created on 8 de marzo de 2018, 17:40
 */

#include "Ataque.hpp"
#include <iostream>

namespace Zenon
{
    Ataque::Ataque(GameDataRef data, sf::Vector2f posicion):Trampa(data)
    {
        mainSprite.setTexture(_datos->assets.GetTexture("Metralleta"));
        mainSprite.setOrigin(mainSprite.getGlobalBounds().width/2, mainSprite.getGlobalBounds().height/2);
        mainSprite.setPosition(posicion);
    }
    void Ataque::Update(float dt)
    {
        
    }
    void Ataque::Draw()
    {
        _datos->window.draw(mainSprite);
    }
}