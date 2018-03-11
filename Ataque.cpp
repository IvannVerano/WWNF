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
#include "DEFINITIONS.hpp"
#include <iostream>

namespace Zenon
{
    Ataque::Ataque(GameDataRef l_data, sf::Vector2f l_posicion):Trampa(l_data)
    {
        m_mainSprite.setTexture(m_datos->assets.GetTexture("Metralleta"));
        m_mainSprite.setOrigin(m_mainSprite.getGlobalBounds().width/2, m_mainSprite.getGlobalBounds().height/2);
        m_mainSprite.setPosition(l_posicion);
        m_timeAppear.restart();
        m_state = TRAP_STATE_APPEARING;
    }
    void Ataque::Update(float dt)
    {
        if(m_state == TRAP_STATE_APPEARING)
        {
            if(m_timeAppear.getElapsedTime().asSeconds() > ATRAP_APPEARING_TIME)
            {
                m_state = TRAP_STATE_PLACED;
            }
        }
    }
    void Ataque::Draw()
    {
        if(m_state == TRAP_STATE_PLACED)
            m_datos->window.draw(m_mainSprite);
    }
}