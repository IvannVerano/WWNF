#include "Hero.hpp"
#include "DEFINITIONS.hpp"


namespace Zenon
{
    Hero::Hero(GameDataRef l_data):m_data(l_data)
    {
        m_state = HERO_IDLE_STATE;
        m_mainSprite.setTexture(m_data->assets.GetTexture("Heroe"));
        m_mainSprite.setTextureRect(sf::IntRect(105,284,14,42));
        m_mainSprite.setOrigin(m_mainSprite.getGlobalBounds().width/2, m_mainSprite.getGlobalBounds().height/2);
        m_mainSprite.setPosition(300,300);
        m_mainSprite.scale(2.0,2.0);
        m_direction = sf::Vector2f(-1,-1);
        m_destiny = sf::Vector2f(-1,-1);
        m_isSelected = false;
    }
    
    void Hero::Update(float dt)
    {
        if(m_state == HERO_MOVING_STATE)
        {
            if(m_mainSprite.getPosition().x > m_destiny.x)
                m_state = HERO_IDLE_STATE;
            else
                this->Move(dt);
        }
    }
    
    void Hero::OrderMovement(sf::Vector2f l_destiny)
    {
        m_destiny = l_destiny;
        m_direction = l_destiny - m_mainSprite.getPosition();
        m_state = HERO_MOVING_STATE;
    }
    
    void Hero::Move(float dt)
    {
        m_mainSprite.move(dt*m_direction.x, dt*m_direction.y);
    }
    
    void Hero::Draw()
    {
        m_data->window.draw(m_mainSprite);
    }
    
    bool Hero::IsSelected()
    {
        return m_isSelected;
    }
    
    bool Hero::IsClicked()
    {
        return m_data->input.IsSpriteClicked(m_mainSprite, sf::Mouse::Left, m_data->window);
    }
    
    void Hero::Select()
    {
        m_isSelected = true;
    }
    
}