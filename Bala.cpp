
#include "Bala.hpp"
#include <iostream>
#include <math.h>

namespace Zenon{
    
    Bala::Bala(GameDataRef l_data, sf::Vector2f l_position,sf::Vector2f l_enemigo,float l_angulo):m_data(l_data)
    {
        m_mainSprite.setTexture(m_data->assets.GetTexture("bullet"));
        m_mainSprite.setOrigin(m_mainSprite.getGlobalBounds().width/2,m_mainSprite.getGlobalBounds().height/2);
        m_mainSprite.setPosition(l_position);
        m_mainSprite.scale(0.2,0.2);
        m_positionBullet = l_position;
        m_direccion=l_enemigo;
        m_angulo=l_angulo;
        m_shoot=false;
        std::cout<<m_direccion.x<<" , "<<m_direccion.y<<std::endl;

    }
    
    void Bala::Update(float dt)
    {
        if(m_shoot==false){
                m_mainSprite.setRotation(m_angulo);
                m_shoot=true;
        }
        
        m_mainSprite.move(5*dt*-m_direccion.x,dt*m_direccion.y*5);
        
        

    }
    void Bala::Draw()
    {
       m_data->window.draw(m_mainSprite);
    }

    
    
    
}