/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Placer.cpp
 * Author: antonio
 * 
 * Created on 8 de marzo de 2018, 18:40
 */

#include "Placer.hpp"

namespace Zenon
{
    Placer::Placer(GameDataRef data, sf::Vector2f pos):datos(data)
    {
        mainSprite.setTexture(datos->assets.GetTexture("No_trampa"));
        mainSprite.setOrigin(mainSprite.getGlobalBounds().width/2, mainSprite.getGlobalBounds().height/2);
        mainSprite.scale(3.0,3.0);
        mainSprite.setPosition(pos);
        posicion = pos;
        ocupado = false;
    }
    
    Placer::~Placer(){}
    
    bool Placer::Clicked(int trampa)
    {
        if(datos->input.IsSpriteClicked(mainSprite,sf::Mouse::Left,datos->window) && !ocupado && trampa>-1)
        {
            ocupado = true;
            return true;
        }
        return false;
    }
    
    sf::Vector2f Placer::GetPosicion()
    {
        return posicion;
    }
    
    void Placer::Draw()
    {
        this->datos->window.draw(mainSprite);
    }
    
    bool Placer::GetOccuped()
    {
        return ocupado;
    }
    
    bool Placer::Hovered()
    {
        if(datos->input.IsSpriteHovered(mainSprite, sf::Mouse::Left, datos->window))
            return true;
        else
            return false;
    }
}
