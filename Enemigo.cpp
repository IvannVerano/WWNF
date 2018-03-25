#include "Enemigo.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>

namespace Zenon{
    Enemigo::Enemigo(GameDataRef l_data, sf::Vector2f l_position, int id, float l_speed):m_data(l_data)
    {
        m_mainSprite.setTexture(m_data->assets.GetTexture("enemigo"));
        m_mainSprite.setOrigin(m_mainSprite.getGlobalBounds().width/2,m_mainSprite.getGlobalBounds().height/2);
        m_mainSprite.scale(0.5,0.5);
        m_mainSprite.setPosition(l_position);
        m_position = l_position;
        m_state = ENEMY_STATE_ALIVE;
        m_life = ENEMY_LIFE;
        this->id = id;
        m_killer = -1;
        m_speed = l_speed;
        m_slowed = false;
        m_vidaDraw.setSize(sf::Vector2f(m_life, 10));
        m_vidaDraw.setFillColor(sf::Color::Green);
        m_vidaDraw.setOrigin(m_vidaDraw.getGlobalBounds().width/2, m_vidaDraw.getGlobalBounds().height/2);
        m_vidaDraw.setPosition(m_mainSprite.getGlobalBounds().left + 20, m_mainSprite.getGlobalBounds().top);
    }
    
    void Enemigo::Update(float dt)
    {
        if(m_state == ENEMY_STATE_ALIVE)
        {
            m_mainSprite.move(dt*m_speed, dt*m_speed);
            m_position = m_mainSprite.getPosition();
            m_vidaDraw.setPosition(m_mainSprite.getGlobalBounds().left + 20, m_mainSprite.getGlobalBounds().top);
        }
    }
    void Enemigo::Draw(){
    
        m_data->window.draw(m_mainSprite);
        m_data->window.draw(m_vidaDraw);
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
        m_vidaDraw.setSize(sf::Vector2f(m_life, 10));
        
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
    
    void Enemigo::SlowDown(float l_factor)
    {
        m_speed *= l_factor;
        m_slowed = true;
    }
    
    void Enemigo::NoEffect(float l_factor)
    {
        m_speed = m_speed/l_factor;
        m_slowed = false;
    }
    
    bool Enemigo::GetSlowed()
    {
        return m_slowed;
    }
    
}