#include "Hero.hpp"
#include "DEFINITIONS.hpp"
#include "MathHelper.hpp"
#include <iostream>


namespace Zenon
{
    Hero::Hero(GameDataRef l_data, Maps &l_map):m_data(l_data), m_map(l_map)
    {
        m_state = HERO_IDLE_STATE;
        m_mainSprite.setTexture(m_data->assets.GetTexture("Hero"));
        m_mainSprite.setTextureRect(sf::IntRect(105,284,14,42));
        m_mainSprite.setOrigin(m_mainSprite.getGlobalBounds().width/2, m_mainSprite.getGlobalBounds().height/2);
        m_mainSprite.setPosition(300,300);
        m_mainSprite.scale(2.0,2.0);
        m_direction = sf::Vector2f(-1,-1);
        
        m_destinyPointer.setTexture(m_data->assets.GetTexture("Hero_GUI"));
        m_destinyPointer.setTextureRect(sf::IntRect(0,0,65,64));
        m_destinyPointer.scale(0.5,0.5);
        m_destinyPointer.setOrigin(m_destinyPointer.getGlobalBounds().width/2, m_destinyPointer.getGlobalBounds().height/2);
        
        
        m_heroArrow.setTexture(m_data->assets.GetTexture("Hero_GUI"));
        m_heroArrow.setTextureRect(sf::IntRect(68,44,24,20));
        m_heroArrow.setOrigin(m_heroArrow.getGlobalBounds().width/2, m_heroArrow.getGlobalBounds().height/2);
        m_heroArrow.setPosition(m_mainSprite.getPosition().x, m_mainSprite.getPosition().y-60);
        
        m_heroPlace.setTexture(m_data->assets.GetTexture("Hero_GUI"));
        m_heroPlace.setTextureRect(sf::IntRect(122,0,68,64));
        m_heroPlace.setOrigin(m_heroPlace.getGlobalBounds().width/2, m_heroPlace.getGlobalBounds().height/2);
        m_heroPlace.setPosition(m_mainSprite.getPosition().x, m_mainSprite.getPosition().y+30);
        
        m_isSelected = false;
        m_waypoint = 1;
        m_pathComplete = false;
    }
    
    void Hero::Update(float dt)
    {
        m_heroArrow.setPosition(m_mainSprite.getPosition().x, m_mainSprite.getPosition().y-60);
        m_heroPlace.setPosition(m_mainSprite.getPosition().x, m_mainSprite.getPosition().y+30);
        if(m_mainSprite.getGlobalBounds().contains(m_destinyPointer.getPosition()))
                m_state = HERO_IDLE_STATE;
        if(m_state == HERO_MOVING_STATE)
        {   
            if(!m_pathComplete)
            {
                sf::Vector2f distance = m_path[m_waypoint] - m_mainSprite.getPosition();
                float module_distance = Module(distance);
                if(module_distance <= HERO_DETECT_WAYPOINT)
                {
                    if(m_waypoint < m_path.size()-1)
                    {
                        m_waypoint++;
                        m_direction = m_path[m_waypoint] - m_mainSprite.getPosition();
                        m_direction = Normalize(m_direction, Module(m_direction));
                    }
                    else
                    {
                        m_pathComplete = true;
                        std::cout<<"Entro para ponerle fin a esta mierda"<<std::endl;
                        m_direction = m_destiny - m_mainSprite.getPosition();
                        m_direction = Normalize(m_direction, Module(m_direction));
                    }
                }
                    
            }
            
            this->Move(dt);
        }
    }
    
    void Hero::OrderMovement(sf::Vector2f l_destiny)
    {
        m_waypoint = 1;
        m_pathComplete = false;
        m_path.clear();
        m_map.GetPath(m_mainSprite.getPosition(), l_destiny, m_path);
        std::reverse(std::begin(m_path), std::end(m_path));
        for(int i=0; i<m_path.size(); i++)
        {
            std::cout<<m_path[i].x<<","<<m_path[i].y<<std::endl;
        }
        std::cout<<m_path.front().x<<","<<m_path.front().y<<std::endl;
        std::cout<<m_mainSprite.getPosition().x<<","<<m_mainSprite.getPosition().y<<std::endl;
        m_destiny = l_destiny;
        m_destinyPointer.setPosition(l_destiny);
        m_direction = m_path[m_waypoint] - m_mainSprite.getPosition();
        m_direction = Normalize(m_direction, Module(m_direction));
        m_state = HERO_MOVING_STATE;
        m_isSelected = false;
    }
    
    void Hero::Move(float dt)
    {
        //std::cout<<"Mi direccion es: "<<m_direction.x<<","<<m_direction.y<<std::endl;
        m_mainSprite.move(dt*m_direction.x*HERO_SPEED, dt*m_direction.y*HERO_SPEED);
    }
    
    void Hero::Draw()
    {
        if(m_state == HERO_MOVING_STATE)
        {
            m_data->window.draw(m_destinyPointer);
        }
        if(m_isSelected)
        {
            m_data->window.draw(m_heroPlace);
            m_data->window.draw(m_heroArrow);
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