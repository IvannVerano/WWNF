#include "Attack.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>

namespace Zenon
{
    Attack::Attack(GameDataRef l_data, sf::Vector2f l_posicion, sf::Texture& l_texture, const std::vector<Enemy*>& l_enemies, std::vector<Bala*> &l_bullets):Trampa(l_data), m_enemies(l_enemies), m_bullets(l_bullets)
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
        m_target = -1;
        m_ShootCadence.restart();
    }
    
    void Attack::SetAttributes(int l_id, float l_cadence, float l_apptime, int l_power, int l_range, int l_refresh, int l_wait, int l_percentaje, int l_price)
    {
        m_id = l_id;
        m_cadencia = l_cadence;
        m_timeAparicion = l_apptime;
        m_potencia = l_power;
        m_rango = l_range;
        m_refresco = l_refresh;
        m_espera = l_wait;
        m_percentaje = l_percentaje;
        m_price = l_price;
    }
    
    void Attack::AnimateApparition()
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
    
    void Attack::Update(float dt)
    {
        switch(m_state)
        {
            case TRAP_STATE_APPEARING:
                if(m_timeAppear.getElapsedTime().asSeconds() > m_timeAparicion) 
                    m_state = TRAP_STATE_PLACED;
                break;
            
            case TRAP_STATE_PLACED:
                if(m_target == -1)
                {
                    this->FindTarget();
                }
                else
                {
                    this->Shoot();
                }
            break;   
        }    
    }
    
    void Attack::FindTarget()
    {
        for (int i = 0; i < m_enemies.size(); i++) 
        {
            if (m_target == -1) 
            {
                if (m_mainSprite.getPosition().x - m_enemies.at(i)->GetPosition().x < m_rango && m_mainSprite.getPosition().y - m_enemies.at(i)->GetPosition().y < m_rango &&
                        m_enemies.at(i)->GetPosition().x - m_mainSprite.getPosition().x < m_rango && m_enemies.at(i)->GetPosition().y - m_mainSprite.getPosition().y < m_rango ||
                        m_mainSprite.getPosition().x - m_enemies.at(i)->GetPosition().x < m_rango && m_mainSprite.getPosition().y - m_enemies.at(i)->GetPosition().y < -m_rango &&
                        m_enemies.at(i)->GetPosition().x - m_mainSprite.getPosition().x < -m_rango && m_enemies.at(i)->GetPosition().y - m_mainSprite.getPosition().y < -m_rango) 
                {
                   m_target = i; 
                }
            }
        }
    }
    
    void Attack::Shoot()
    {
        if(m_target != -1)
        {
            if (m_mainSprite.getPosition().x - m_enemies[m_target]->GetPosition().x < m_rango && m_mainSprite.getPosition().y - m_enemies[m_target]->GetPosition().y < m_rango &&
                    m_enemies[m_target]->GetPosition().x - m_mainSprite.getPosition().x < m_rango && m_enemies[m_target]->GetPosition().y - m_mainSprite.getPosition().y < m_rango) 
            {
                float angle = 0;
                float hipotenusa;
                float PI = 3.14159265;
                float incremento_x, incremento_y;
                sf::Vector2f m_direccion_sentido;
                hipotenusa = sqrt(pow(m_mainSprite.getPosition().x - m_enemies[m_target]->GetPosition().x, 2) + pow(m_mainSprite.getPosition().y - m_enemies[m_target]->GetPosition().y, 2));
                angle = asin(abs(m_mainSprite.getPosition().y - m_enemies[m_target]->GetPosition().y) / hipotenusa) * 180.0 / PI;
                angle = angle - 90;
                
                if (m_mainSprite.getPosition().x - m_enemies[m_target]->GetPosition().x < 0 && m_mainSprite.getPosition().y - m_enemies[m_target]->GetPosition().y > 0) {//primer cuadrante

                    angle = angle*-1;

                    m_direccion_sentido.x = (m_enemies[m_target]->GetPosition().x - m_mainSprite.getPosition().x)*-1;
                    m_direccion_sentido.y = m_enemies[m_target]->GetPosition().y - m_mainSprite.getPosition().y;

                }
                if (m_mainSprite.getPosition().x - m_enemies[m_target]->GetPosition().x > 0 && m_mainSprite.getPosition().y - m_enemies[m_target]->GetPosition().y < 0) {// tercer cuadrante

                    angle = 180 - angle;
                    m_direccion_sentido.x = (m_enemies[m_target]->GetPosition().x - m_mainSprite.getPosition().x)*-1;
                    m_direccion_sentido.y = m_enemies[m_target]->GetPosition().y - m_mainSprite.getPosition().y;
                }

                if (m_mainSprite.getPosition().x - m_enemies[m_target]->GetPosition().x <= 0 && m_mainSprite.getPosition().y - m_enemies[m_target]->GetPosition().y <= 0) { //cuarto cuadrante

                    angle = angle - 180;
                    m_direccion_sentido.x = (m_enemies[m_target]->GetPosition().x - m_mainSprite.getPosition().x)*-1;
                    m_direccion_sentido.y = m_enemies[m_target]->GetPosition().y - m_mainSprite.getPosition().y;
                }

                if (m_mainSprite.getPosition().x - m_enemies[m_target]->GetPosition().x > 0 && m_mainSprite.getPosition().y - m_enemies[m_target]->GetPosition().y > 0) { //cuarto cuadrante

                    m_direccion_sentido.x = (m_enemies[m_target]->GetPosition().x - m_mainSprite.getPosition().x)*-1;
                    m_direccion_sentido.y = (m_enemies[m_target]->GetPosition().y - m_mainSprite.getPosition().y);
                }
                m_mainSprite.setRotation(angle);
                
                if(m_ShootCadence.getElapsedTime().asSeconds() > m_cadencia)
                {
                    this->CreateBullet(m_direccion_sentido, angle);
                    m_ShootCadence.restart();
                }
            }
            else
            {
                m_target = -1;
                m_mainSprite.setRotation(0);
            }    
        }
    }
    
    void Attack::CreateBullet(sf::Vector2f l_direccionSentido, float angle)
    {
       Bala * c_bala = new Bala(m_datos, m_mainSprite.getPosition(), l_direccionSentido, angle, m_potencia, m_id);
       m_bullets.push_back(c_bala);
    }
    
    void Attack::Draw()
    {
        if (m_state == TRAP_STATE_APPEARING)
        {
            this->AnimateApparition();
            m_datos->window.draw(m_SpriteAnimation);
        }
        else
            m_datos->window.draw(m_mainSprite);
                 
    }
    
    void Attack::DeleteTarget(int l_posicion)
    {
        if(m_target == l_posicion)
        {
            m_target = -1;
            m_mainSprite.setRotation(0);
        }
    }
    
    int Attack::CalculateRec(int l_sum)
    {
        int c_res = l_sum + (m_price * (m_percentaje/100.0));
        return c_res;
    }
    
    
}