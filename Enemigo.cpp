#include "Enemigo.hpp"

namespace Zenon{
    Enemigo::Enemigo(GameDataRef l_data, sf::Vector2f l_position):m_data(l_data)
    {
        m_mainSprite.setTexture(m_data->assets.GetTexture("enemigo"));
        m_mainSprite.setOrigin(m_mainSprite.getGlobalBounds().width/2,m_mainSprite.getGlobalBounds().width/2);
        m_mainSprite.scale(0.5,0.5);
        m_mainSprite.setPosition(l_position);
        m_position = l_position;
    }
    
    void Enemigo::Update(float dt)
    {
        m_mainSprite.move(dt*100,dt*50);
        m_position = m_mainSprite.getPosition();
    }
    void Enemigo::Draw(){
    
        m_data->window.draw(m_mainSprite);
    }
    
    sf::Vector2f Enemigo::GetPosition()
    {
        return m_position;
    }
}