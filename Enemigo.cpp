#include "Enemigo.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>

namespace Zenon{
    Enemigo::Enemigo(GameDataRef l_data, sf::Vector2f l_position, int id):m_data(l_data)
    {
        m_mainSprite.setTexture(m_data->assets.GetTexture("enemigo"));
        m_mainSprite.setOrigin(m_mainSprite.getGlobalBounds().width/2,m_mainSprite.getGlobalBounds().height/2);
        m_mainSprite.scale(0.5,0.5);
        m_mainSprite.setPosition(l_position);
        m_position = l_position;
        m_state = ENEMY_STATE_ALIVE;
        m_life = 50;
        this->id = id;
        m_killer = -1;
    }
    
    void Enemigo::Update(float dt)
    {
        if(m_state == ENEMY_STATE_ALIVE)
        {
            m_mainSprite.move(dt*35,dt*5);
            m_position = m_mainSprite.getPosition();
        }
    }
    void Enemigo::Draw(){
    
        m_data->window.draw(m_mainSprite);
    }
    
    sf::Vector2f Enemigo::GetPosition()
    {
        return m_position;
    }
    
    int Enemigo::GetActualState()
    {
        return m_state;
    }
    
    void Enemigo::TakeDamage(int l_damage)
    {
        this->m_life -= l_damage;
        std::cout<<m_life<<std::endl;
        if(m_life<0)
        {
            std::cout<<"He muerto xd"<<std::endl;
            m_state = ENEMY_STATE_DEAD;
        }
    }
    
    Enemigo::~Enemigo()
    {}
    
    const sf::Sprite &Enemigo::GetSprite() const
    {
        return  m_mainSprite;
    }
    
    int Enemigo::GetID()
    {
        return id;
    }
    
    void Enemigo::SetKiller(int l_killer)
    {
        m_killer = l_killer;
    }
    
    int Enemigo::GetKiller()
    {
        return m_killer;
    }
}