/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Defensa.cpp
 * Author: antonio
 * 
 * Created on 8 de marzo de 2018, 21:08
 */

#include "Defensa.hpp"

namespace Zenon
{
    Defensa::Defensa(GameDataRef data, sf::Vector2f posicion):Trampa(data)
    {
        mainSprite.setTexture(_datos->assets.GetTexture("Defensa"));
        mainSprite.setOrigin(mainSprite.getGlobalBounds().width/2, mainSprite.getGlobalBounds().height/2);
        mainSprite.setPosition(posicion);
    }
    void Defensa::Update(float dt)
    {
        
    }
    void Defensa::Draw()
    {
        _datos->window.draw(mainSprite);
    }
}

