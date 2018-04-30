#include "Nuke.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>

namespace Zenon
{
    Nuke::Nuke(GameDataRef l_data, sf::Vector2f l_posicion, sf::Texture& l_texture, const std::vector<Enemy*>& l_enemies):Trampa(l_data), m_enemies(l_enemies)
    {
        //Seteamos todo el tema de la animacion
        m_SpriteAnimation.setTexture(m_datos->assets.GetTexture("GUI_ELEMENTS"));
        m_SpriteAnimation.setTextureRect(sf::IntRect(321, 163, 24, 30));
        m_SpriteAnimation.setOrigin(m_SpriteAnimation.getGlobalBounds().width / 2, m_SpriteAnimation.getGlobalBounds().height / 2);
        m_SpriteAnimation.scale(2.0, 2.0);
        m_SpriteAnimation.setPosition(l_posicion.x, l_posicion.y - 50);
        m_AnimationFramesAppear.push_back(sf::IntRect(321, 163, 24, 30));
        m_AnimationFramesAppear.push_back(sf::IntRect(357, 210, 24, 30));
        m_AnimationFramesAppear.push_back(sf::IntRect(296, 197, 24, 30));
        m_AnimationFramesAppear.push_back(sf::IntRect(3, 6, 24, 30));
        /////////////////////////////////////////////////////////////////////////////////////
        
        //Seteamos el sprite principal
        m_mainSprite.setTexture(l_texture);
        m_mainSprite.setOrigin(m_mainSprite.getGlobalBounds().width / 2, m_mainSprite.getGlobalBounds().height / 2);
        m_mainSprite.setPosition(l_posicion);
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        
        m_animationAppearCounter = 1;
        m_aniAppearClock.restart();
        m_timeAppear.restart();
        m_state = TRAP_STATE_APPEARING;
        m_rango=RANGO_NUKE;
    }
    

    
    void Nuke::AnimateApparition()
    {
        if (m_aniAppearClock.getElapsedTime().asSeconds() > SPEED_ANIMATION / m_AnimationFramesAppear.size()) {
            
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
    
    void Nuke::Update(float dt)
    {
        switch(m_state)
        {
            case TRAP_STATE_APPEARING:
                if(m_timeAppear.getElapsedTime().asSeconds() > m_timeAparicion) 
                    m_state = TRAP_STATE_PLACED;
                break;
            
            case TRAP_STATE_PLACED:

                    this->FindTarget();
                
            break;   
        }    
    }
    
    void Nuke::FindTarget()
    {
        
        for (int i = m_enemies.size()-1; i>=0 ; i--) 
        {            
            if (m_mainSprite.getPosition().x - m_enemies.at(i)->GetPosition().x < m_rango && m_mainSprite.getPosition().y - m_enemies.at(i)->GetPosition().y < m_rango &&
                m_enemies.at(i)->GetPosition().x - m_mainSprite.getPosition().x < m_rango && m_enemies.at(i)->GetPosition().y - m_mainSprite.getPosition().y < m_rango ||
                m_mainSprite.getPosition().x - m_enemies.at(i)->GetPosition().x < m_rango && m_mainSprite.getPosition().y - m_enemies.at(i)->GetPosition().y < -m_rango &&
                m_enemies.at(i)->GetPosition().x - m_mainSprite.getPosition().x < -m_rango && m_enemies.at(i)->GetPosition().y - m_mainSprite.getPosition().y < -m_rango) 
            {
                m_enemies.at(i)->TakeDamage(POTENCIA_NUKE);
            }
            
        }
    }
    


    
    void Nuke::Draw()
    {
        if (m_state == TRAP_STATE_APPEARING)
        {
            this->AnimateApparition();
            m_datos->window.draw(m_SpriteAnimation);
        }
       
                 
    }

    
}