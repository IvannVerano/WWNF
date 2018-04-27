#include "Flamethrower.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>
#include <math.h>


namespace Zenon
{
    Flamethrower::Flamethrower(GameDataRef l_data, sf::Vector2f l_posicion, sf::Texture& l_texture, const std::vector<Enemy*>& l_enemies, std::vector<Bala*> &l_bullets):Trampa(l_data), m_enemies(l_enemies), m_bullets(l_bullets)
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
        m_mainSprite.scale(0.35,0.35);
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        
        m_animationAppearCounter = 1;
        m_aniAppearClock.restart();
        m_timeAppear.restart();
        m_state = TRAP_STATE_APPEARING;
        m_target = -1;
        m_ShootCadence.restart();
    }
    
    void Flamethrower::SetAttributes(int l_id, float l_cadence, float l_apptime, int l_power, int l_range, int l_refresh, int l_wait, int l_percentaje, int l_price)
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
    
    void Flamethrower::AnimateApparition()
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
    
    void Flamethrower::Update(float dt)
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
    
    void Flamethrower::FindTarget()
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
                   m_realID = m_enemies.at(i)->GetId();

                }
            }
        }
    }
    
    void Flamethrower::Shoot()
    {
        if(m_target != -1)
        {
            if (m_mainSprite.getPosition().x - m_enemies[m_target]->GetPosition().x < m_rango && m_mainSprite.getPosition().y - m_enemies[m_target]->GetPosition().y < m_rango &&
                    m_enemies[m_target]->GetPosition().x - m_mainSprite.getPosition().x < m_rango && m_enemies[m_target]->GetPosition().y - m_mainSprite.getPosition().y < m_rango) 
            {

                m_mainSprite.rotate(ANGULO_LANZALLAMAS);

                
                if(m_ShootCadence.getElapsedTime().asSeconds() > m_cadencia)
                {

                    

                    this->CreateBullet( m_mainSprite.getRotation());
                    this->CreateBullet( m_mainSprite.getRotation()+90);
                    this->CreateBullet( m_mainSprite.getRotation()+180);
                    this->CreateBullet( m_mainSprite.getRotation()+270);
                    
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
    
    void Flamethrower::CreateBullet( float angle)
    {
        sf::Vector2f m_direccion_sentido;

                    if(0<= m_mainSprite.getRotation()<=90){
                    
                        m_direccion_sentido.x = (std::cos(angle*PI/180))*-45;
                        m_direccion_sentido.y = (std::sin(angle*PI/180))*55;
                    
                    }else if(90< m_mainSprite.getRotation()<=180){
                        
                        m_direccion_sentido.x = (std::cos(angle*PI/180))*-45;
                        m_direccion_sentido.y = (std::sin(angle*PI/180))*55;
                    }else if(180< m_mainSprite.getRotation()<=270){
 
                        m_direccion_sentido.x = (std::cos(angle*PI/180))*-45;
                        m_direccion_sentido.y = (std::sin(angle*PI/180))*55;                       
                    }else if(270< m_mainSprite.getRotation()<360){
                        
                        m_direccion_sentido.x = (std::cos(angle*PI/180))*-45;
                        m_direccion_sentido.y = (std::sin(angle*PI/180))*55;                        
                    }
        
        
       Bala * c_bala = new Bala(m_datos, m_mainSprite.getPosition(), m_direccion_sentido, angle-90, m_potencia, m_id,1);
       m_bullets.push_back(c_bala);
    }
        

    
    void Flamethrower::Draw()
    {
        if (m_state == TRAP_STATE_APPEARING)
        {
            this->AnimateApparition();
            m_datos->window.draw(m_SpriteAnimation);
        }
        else
            m_datos->window.draw(m_mainSprite);
                 
    }
    
    void Flamethrower::DeleteTarget(int l_posicion)
    {
        if(m_realID == l_posicion)
        {
            m_target = -1;
            m_realID = -1;
            m_mainSprite.setRotation(0);
        }
    }
    
    int Flamethrower::CalculateRec(int l_sum)
    {
        int c_res = l_sum + (m_price * (m_percentaje/100.0));
        return c_res;
    }
    
    
}