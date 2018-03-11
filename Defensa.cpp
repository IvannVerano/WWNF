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
#include "DEFINITIONS.hpp"

namespace Zenon
{
    Defensa::Defensa(GameDataRef l_data, sf::Vector2f l_posicion):Trampa(l_data)
    {
        m_mainSprite.setTexture(m_datos->assets.GetTexture("Defensa"));
        m_mainSprite.setOrigin(m_mainSprite.getGlobalBounds().width/2, m_mainSprite.getGlobalBounds().height/2);
        m_mainSprite.scale(0.8,0.8);
        m_mainSprite.setPosition(l_posicion);
        m_timeAppear.restart();
        m_state = TRAP_STATE_APPEARING;
    }
    void Defensa::Update(float dt)
    {
         if(m_state == TRAP_STATE_APPEARING)
        {
            if(m_timeAppear.getElapsedTime().asSeconds() > DTRAP_APPEARING_TIME)
            {
                m_state = TRAP_STATE_PLACED;
            }
        }
    }
    void Defensa::Draw()
    {
        if(m_state == TRAP_STATE_PLACED)
            m_datos->window.draw(m_mainSprite);
    }
}

