
#include "Support.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>

namespace Zenon
{
    Support::Support(GameDataRef l_data, sf::Vector2f l_posicion, sf::Texture &l_textura, const std::vector<Hero*> &l_hero, int l_rango):Trampa(l_data),m_hero(l_hero)
    {
        m_SpriteAnimation.setTexture(m_datos->assets.GetTexture("GUI_ELEMENTS"));
        m_SpriteAnimation.setTextureRect(sf::IntRect(321, 163, 24, 30));
        m_SpriteAnimation.setOrigin(m_SpriteAnimation.getGlobalBounds().width/2, m_SpriteAnimation.getGlobalBounds().height/2);
        m_SpriteAnimation.scale(2.0,2.0);
        m_SpriteAnimation.setPosition(l_posicion.x, l_posicion.y - 50);
        
        m_mainSprite.setTexture(l_textura);
        m_mainSprite.setOrigin(m_mainSprite.getGlobalBounds().width/2, m_mainSprite.getGlobalBounds().height/2);
        m_mainSprite.setPosition(l_posicion);
        m_mainSprite.scale(0.6,0.6);
        
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
        m_time.restart();

        
        m_state = TRAP_STATE_APPEARING;
    }
    void Support::Update(float dt)
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
    void Support::Draw()
    {
        if(m_state == TRAP_STATE_APPEARING)
            m_datos->window.draw(m_SpriteAnimation);
        else
            m_datos->window.draw(m_mainSprite);
    }
    
    void Support::AnimateApparition()
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
    
    int Support::CalculateRec(int l_sum)
    {
        return 1;
    }
    
    void Support::Act()
    {
                
                for(int i = 0; i<m_hero.size(); i++)
        {

                if(m_mainSprite.getPosition().x-m_hero.at(i)->GetCurrentPosition().x < m_rango && m_mainSprite.getPosition().y-m_hero.at(i)->GetCurrentPosition().y < m_rango && 
                    m_hero.at(i)->GetCurrentPosition().x - m_mainSprite.getPosition().x < m_rango && m_hero.at(i)->GetCurrentPosition().y-m_mainSprite.getPosition().y < m_rango ||
                        m_mainSprite.getPosition().x-m_hero.at(i)->GetCurrentPosition().x < m_rango && m_mainSprite.getPosition().y-m_hero.at(i)->GetCurrentPosition().y < -m_rango && 
                            m_hero.at(i)->GetCurrentPosition().x - m_mainSprite.getPosition().x < -m_rango && m_hero.at(i)->GetCurrentPosition().y-m_mainSprite.getPosition().y < -m_rango)
                {
                    
                    if(m_time.getElapsedTime().asSeconds()>TIEMPO_CURA){
                        m_hero[i]->Heal(POTENCIA_SANACION);
                        m_time.restart();
                    }
                }
        
        }     
                
       
    }
        
}

