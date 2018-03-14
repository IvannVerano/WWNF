#include "Ataque.hpp"
#include <iostream>
#include <math.h>

namespace Zenon{
    
    Ataque::Ataque(GameDataRef l_data, sf::Vector2f l_position):m_data(l_data)
    {
        m_mainSprite.setTexture(m_data->assets.GetTexture("torreta"));
        m_mainSprite.setOrigin(m_mainSprite.getGlobalBounds().width/2,m_mainSprite.getGlobalBounds().width/2);
        m_mainSprite.setPosition(l_position);
        m_is_attacking = false;
    }
    
    void Ataque::Update(float dt)
    {
    }
    void Ataque::Draw()
    {
    
        m_data->window.draw(m_mainSprite);
    }
    
    bool Ataque::IsAttacking()
    {
        return m_is_attacking;
    }
    
    void Ataque::FindTarget(std::vector<Enemigo*> &l_enemys)
    {
        for(int i = 0; i<l_enemys.size(); i++)
        {
            if(!m_is_attacking)
            {
                if(m_mainSprite.getPosition().x-l_enemys.at(i)->GetPosition().x < 200 && m_mainSprite.getPosition().y-l_enemys.at(i)->GetPosition().y < 200 && 
                    l_enemys.at(i)->GetPosition().x - m_mainSprite.getPosition().x < 200 && l_enemys.at(i)->GetPosition().y-m_mainSprite.getPosition().y < 200 ||
                        m_mainSprite.getPosition().x-l_enemys.at(i)->GetPosition().x < 200 && m_mainSprite.getPosition().y-l_enemys.at(i)->GetPosition().y < -200 && 
                            l_enemys.at(i)->GetPosition().x - m_mainSprite.getPosition().x < -200 && l_enemys.at(i)->GetPosition().y-m_mainSprite.getPosition().y < -200    )
                {
                    m_target = l_enemys.at(i);
                    std::cout<<"Ya lo tengo"<<std::endl;
                    m_is_attacking = true;
                }
            }
        
        }   
    }
    
    void Ataque::Attack()
    {
        if(m_is_attacking)
        {
            if(m_mainSprite.getPosition().x-m_target->GetPosition().x < 200 && m_mainSprite.getPosition().y-m_target->GetPosition().y < 200 && 
                   m_target->GetPosition().x - m_mainSprite.getPosition().x < 200 && m_target->GetPosition().y-m_mainSprite.getPosition().y < 200)
            {
                float angulo=0;
                float hipotenusa;
                float angulonuevo=0;
                float PI= 3.14159265;

                hipotenusa=sqrt(pow(m_mainSprite.getPosition().x-m_target->GetPosition().x,2)+pow(m_mainSprite.getPosition().y-m_target->GetPosition().y,2));
                angulo = asin (abs(m_mainSprite.getPosition().y-m_target->GetPosition().y)/hipotenusa) * 180.0 / PI;
                angulo=angulo-90;
                
               if(m_mainSprite.getPosition().x-m_target->GetPosition().x<0 &&  m_mainSprite.getPosition().y-m_target->GetPosition().y>0){
                  
               angulo=angulo*-1;

               }
               if(m_mainSprite.getPosition().x-m_target->GetPosition().x>0 &&  m_mainSprite.getPosition().y-m_target->GetPosition().y<0){

               angulo=180-angulo;

               }

               if(m_mainSprite.getPosition().x-m_target->GetPosition().x<=0 &&  m_mainSprite.getPosition().y-m_target->GetPosition().y<=0){

               angulo=angulo-180;

               }
                m_mainSprite.setRotation(angulo);
            }
            else
            {
                std::cout<<"Dejo de atacar"<<std::endl;
                m_mainSprite.setRotation(0);
                m_is_attacking = false;
            }
        }
        
    }
    
}