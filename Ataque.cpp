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
    Ataque::Ataque(GameDataRef l_data, sf::Vector2f l_posicion, sf::Texture &l_textura):Trampa(l_data)
    {
        m_SpriteAnimation.setTexture(m_datos->assets.GetTexture("GUI_ELEMENTS"));
        m_SpriteAnimation.setTextureRect(sf::IntRect(321, 163, 24, 30));
        m_SpriteAnimation.setOrigin(m_SpriteAnimation.getGlobalBounds().width/2, m_SpriteAnimation.getGlobalBounds().height/2);
        m_SpriteAnimation.scale(2.0,2.0);
        m_SpriteAnimation.setPosition(l_posicion.x, l_posicion.y - 50);
        
        m_mainSprite.setTexture(l_textura);
        m_mainSprite.setOrigin(m_mainSprite.getGlobalBounds().width/2, m_mainSprite.getGlobalBounds().height/2);
        m_mainSprite.setPosition(l_posicion);
        
        //Llenamos el vector para animarr
        m_AnimationFramesAppear.push_back(sf::IntRect(321, 163, 24, 30));
        m_AnimationFramesAppear.push_back(sf::IntRect(357, 210, 24, 30));
        m_AnimationFramesAppear.push_back(sf::IntRect(296, 197, 24, 30));
        m_AnimationFramesAppear.push_back(sf::IntRect(3,6, 24, 30));
        
        //inicializamos variables
        m_aniAppearClock.restart();
        m_timeAppear.restart();
        m_animationAppearCounter = 1;
        
        m_state = TRAP_STATE_APPEARING;
    }
    void Ataque::Update(float dt)
    {
        if(m_state == TRAP_STATE_APPEARING)
        {
            this->AnimateApparition();
            if(m_timeAppear.getElapsedTime().asSeconds() > ATRAP_APPEARING_TIME)
            {
                m_state = TRAP_STATE_PLACED;
            }
        }
        
        
    }
    void Ataque::Draw()
    {
        if(m_state == TRAP_STATE_APPEARING)
            m_datos->window.draw(m_SpriteAnimation);
        else
            m_datos->window.draw(m_mainSprite);
    }
    
    void Ataque::AnimateApparition()
    {
        if (m_aniAppearClock.getElapsedTime().asSeconds() > SPEED_ANIMATION / m_AnimationFramesAppear.size())
		{
			if (m_animationAppearCounter < m_AnimationFramesAppear.size() - 1)
			{
				m_animationAppearCounter++;
			}
			else
			{
				m_animationAppearCounter = 0;
			}

			m_SpriteAnimation.setTextureRect(m_AnimationFramesAppear.at(m_animationAppearCounter));

			m_aniAppearClock.restart();
		}
    }
}