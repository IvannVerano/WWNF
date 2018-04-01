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
        
        m_destinyPointer.setTexture(m_data->assets.GetTexture("GUI"));
        m_destinyPointer.setTextureRect(sf::IntRect(61,76,21,21));
        m_destinyPointer.setOrigin(m_destinyPointer.getGlobalBounds().width/2, m_destinyPointer.getGlobalBounds().height/2);
        m_isSelected = false;
    }
    
    void Hero::Update(float dt)
    {
        if(m_state == HERO_MOVING_STATE)
        {
            if(m_mainSprite.getGlobalBounds().contains(m_destinyPointer.getPosition()))
                m_state = HERO_IDLE_STATE;
            else
                this->Move(dt);
        }
    }
    
    void Hero::OrderMovement(sf::Vector2f l_destiny)
    {
        m_destinyPointer.setPosition(l_destiny);
        m_direction = l_destiny - m_mainSprite.getPosition();
        m_state = HERO_MOVING_STATE;
        m_isSelected = false;
    }
    
    void Hero::Move(float dt)
    {
        m_mainSprite.move(dt*m_direction.x, dt*m_direction.y);
    }
    
    void Hero::Draw()
    {
        if(m_state == HERO_MOVING_STATE)
        {
            m_data->window.draw(m_destinyPointer);
        }
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