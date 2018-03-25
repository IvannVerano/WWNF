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
#include <iostream>

namespace Zenon
{
    Defensa::Defensa(GameDataRef l_data, sf::Vector2f l_posicion, sf::Texture &l_textura, const std::vector<Enemigo*> &l_enemigos, int l_rango):Trampa(l_data),m_enemy(l_enemigos)
    {
        m_SpriteAnimation.setTexture(m_datos->assets.GetTexture("GUI_ELEMENTS"));
        m_SpriteAnimation.setTextureRect(sf::IntRect(321, 163, 24, 30));
        m_SpriteAnimation.setOrigin(m_SpriteAnimation.getGlobalBounds().width/2, m_SpriteAnimation.getGlobalBounds().height/2);
        m_SpriteAnimation.scale(2.0,2.0);
        m_SpriteAnimation.setPosition(l_posicion.x, l_posicion.y - 50);
        
        m_mainSprite.setTexture(l_textura);
        m_mainSprite.setOrigin(m_mainSprite.getGlobalBounds().width/2, m_mainSprite.getGlobalBounds().height/2);
        m_mainSprite.setPosition(l_posicion);
        m_mainSprite.scale(0.8,0.8);
        
        //Llenamos el vector para animarr
        m_AnimationFramesAppear.push_back(sf::IntRect(321, 163, 24, 30));
        m_AnimationFramesAppear.push_back(sf::IntRect(357, 210, 24, 30));
        m_AnimationFramesAppear.push_back(sf::IntRect(296, 197, 24, 30));
        m_AnimationFramesAppear.push_back(sf::IntRect(3,6, 24, 30));
        
        //inicializamos variables
        m_aniAppearClock.restart();
        m_timeAppear.restart();
        m_animationAppearCounter = 1;
        
        m_rango= l_rango;

        
        m_state = TRAP_STATE_APPEARING;
    }
    void Defensa::Update(float dt)
    {
         if(m_state == TRAP_STATE_APPEARING)
        {
            this->AnimateApparition();
            if(m_timeAppear.getElapsedTime().asSeconds() > DTRAP_APPEARING_TIME)
            {
                m_state = TRAP_STATE_PLACED;
            }
        }
         else
             this->Act();
    }
    void Defensa::Draw()
    {
        if(m_state == TRAP_STATE_APPEARING)
            m_datos->window.draw(m_SpriteAnimation);
        else
            m_datos->window.draw(m_mainSprite);
    }
    
    void Defensa::AnimateApparition()
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
    
    int Defensa::CalculateRec(int l_sum)
    {
        return 1;
    }
    
    void Defensa::Act()
    {
                
                for(int i = 0; i<m_enemy.size(); i++)
        {

                if(m_mainSprite.getPosition().x-m_enemy.at(i)->GetPosition().x < m_rango && m_mainSprite.getPosition().y-m_enemy.at(i)->GetPosition().y < m_rango && 
                    m_enemy.at(i)->GetPosition().x - m_mainSprite.getPosition().x < m_rango && m_enemy.at(i)->GetPosition().y-m_mainSprite.getPosition().y < m_rango ||
                        m_mainSprite.getPosition().x-m_enemy.at(i)->GetPosition().x < m_rango && m_mainSprite.getPosition().y-m_enemy.at(i)->GetPosition().y < -m_rango && 
                            m_enemy.at(i)->GetPosition().x - m_mainSprite.getPosition().x < -m_rango && m_enemy.at(i)->GetPosition().y-m_mainSprite.getPosition().y < -m_rango    )
                {
                    if(!m_enemy[i]->GetSlowed())
                    {
                        m_enemy[i]->SlowDown(1-REALENTIZA_TORRE_DEFENSA);
                        std::cout<<"Realentizo a: "<<m_enemy[i]->GetID()<<std::endl;
                    
                    }
                }else
                {
                     if(m_enemy[i]->GetSlowed())
                    {
                        m_enemy[i]->NoEffect(1-REALENTIZA_TORRE_DEFENSA);
                        std::cout<<"Vuelve a su velocidad: "<<m_enemy[i]->GetID()<<std::endl;
                    
                    }
                }
            
        
        }     
                
       
    }
        
}


