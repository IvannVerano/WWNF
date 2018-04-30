/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Healer.cpp
 * Author: user
 * 
 * Created on 29 de abril de 2018, 20:55
 */

#include "Healer.hpp"
#include "DEFINITIONS.hpp"
#include "MathHelper.hpp"

namespace Zenon
{
    Healer::Healer(GameDataRef l_data, Maps &l_map, int l_id, const std::vector<Hero*>& l_allies, const std::vector<Enemy*>& l_enemies):Hero(l_data, l_map, l_id), m_allies(l_allies), m_enemies(l_enemies)
    {
        m_mainSprite.setTexture(m_data->assets.GetTexture("Herosprite2"));
        m_mainSprite.setTextureRect(sf::IntRect(53, 317, 18, 36));
        m_mainSprite.setOrigin(m_mainSprite.getGlobalBounds().width / 2, m_mainSprite.getGlobalBounds().height / 2);
        m_mainSprite.setPosition(400, 400);
        m_mainSprite.scale(2.0, 2.0);
        
        m_heroHUD.setTexture(m_data->assets.GetTexture("Hero_Face1"));
        m_heroHUD.setOrigin(m_heroHUD.getLocalBounds().width / 2, m_heroHUD.getLocalBounds().height / 2);
        m_heroHUD.setPosition(1000,900);
        m_heroHUD.scale(0.92,0.92);
        
        m_heroHUDred.setSize(sf::Vector2f(100,15));
        m_heroHUDred.setPosition(m_heroHUD.getPosition().x - m_heroHUD.getGlobalBounds().width/2, m_heroHUD.getPosition().y+m_heroHUD.getGlobalBounds().height/2);
        m_heroHUDred.setFillColor(sf::Color::Red);
        
        m_heroHUDLife.setSize(sf::Vector2f(100,15));
        m_heroHUDLife.setPosition(m_heroHUD.getPosition().x - m_heroHUD.getGlobalBounds().width/2, m_heroHUD.getPosition().y+m_heroHUD.getGlobalBounds().height/2);
        m_heroHUDLife.setFillColor(sf::Color::Green);
        
    }
    
    void Healer::Update(float dt)
    {
        if (m_live <= 0) {
            m_state = HERO_DEAD_STATE;
        }
        
        if(m_healTarget!= -1 && m_allies[m_healTarget]->GetState() == HERO_DEAD_STATE)
        {
            m_healTarget = -1;
            m_state = HERO_IDLE_STATE;
        }
        
        if(m_attackTarget!= -1 && m_enemies[m_attackTarget]->GetActualState() == ENEMY_STATE_DEAD)
        {
            m_attackTarget = -1;
            m_state = HERO_IDLE_STATE;
        }
        
        if(m_state == HERO_IDLE_STATE)
        {
            for(int i = 0; i<m_enemies.size(); i++)
            {
                sf::Vector2f distance = m_mainSprite.getPosition() - m_enemies[i]->GetSprite().getPosition();
                float l_module = Module(distance);
                if(l_module < HITSCAM_DISTANCE_HEALER)
                {
                    m_state = HERO_ATTACKING_ENEMY;
                    m_attackTarget == i;
                    m_attackTimer.restart();
                    break;
                }
            }
        }
        
        if(m_state == HERO_FOLLOWING_HERO)
        {
            if(m_followingHeroClock.getElapsedTime().asSeconds() > HERO_LOOKTIME)
            {
                this->RecalculateHeroLocation();
            }
            
            sf::Vector2f distance = m_mainSprite.getPosition() - m_allies[m_healTarget]->GetCurrentPosition();
            float l_module = Module(distance);
            if(l_module < HERO_HEALINGDISTANCE)
            {
                m_state = HERO_HEALING;
                m_healingClock.restart();
            }
        }
        
        if(m_state == HERO_FOLLOWING_ENEMY)
        {
            if(m_recalculateElapsed.getElapsedTime().asSeconds() > HERO_LOOKTIME)
            {
                this->RecalculateEnemy();
            }
            
            sf::Vector2f distance = m_mainSprite.getPosition() - m_enemies[m_attackTarget]->GetSprite().getPosition();
            float l_module = Module(distance);
            if(l_module < HITSCAM_DISTANCE_HEALER)
            {
                m_state = HERO_ATTACKING_ENEMY;
                m_attackTimer.restart();
            }
        }
        
        if(m_state == HERO_ATTACKING_ENEMY)
        {
            if(m_attackTimer.getElapsedTime().asSeconds() > HERO_ATTACKINGTIME)
            {
                if(m_attackTarget!=-1)
                {
                    m_enemies[m_attackTarget]->TakeDamage(5);
                    if(m_enemies[m_attackTarget]->GetActualState() == ENEMY_STATE_DEAD)
                    {
                    m_attackTarget = -1;
                    m_state = HERO_IDLE_STATE;
                    }
                }
                
                m_attackTimer.restart();
            }
            
            if(m_attackTarget != -1)
            {
                sf::Vector2f distance = m_mainSprite.getPosition() - m_enemies[m_attackTarget]->GetSprite().getPosition();
                float l_module = Module(distance);
                if(l_module > HITSCAM_DISTANCE_HEALER)
                {
                    m_state = HERO_IDLE_STATE;
                    m_attackTarget = -1;
                }
            }
        }
        
        if(m_state == HERO_HEALING)
        {
            if(m_allies[m_healTarget]->IsRecovered())
            {
                m_healTarget = -1;
                m_state = HERO_IDLE_STATE;
            }
            else
            {
                if(m_healingClock.getElapsedTime().asSeconds() > HERO_ATTACKINGTIME)
                {
                    m_allies[m_healTarget]->Heal(15.0);
                    m_healingClock.restart();
                }
            }
            
        }

        if (m_state != HERO_DEAD_STATE) {
            m_heroArrow.setPosition(m_mainSprite.getPosition().x, m_mainSprite.getPosition().y - 60);
            m_heroPlace.setPosition(m_mainSprite.getPosition().x, m_mainSprite.getPosition().y + 30);
            m_destinyPointer.rotate(2);
            if (m_mainSprite.getGlobalBounds().contains(m_destinyPointer.getPosition()))
                m_state = HERO_IDLE_STATE;
            if (m_state == HERO_MOVING_STATE || m_state == HERO_FOLLOWING_HERO || m_state == HERO_FOLLOWING_ENEMY) {
                if (!m_pathComplete) {
                    sf::Vector2f distance = m_path[m_waypoint] - m_mainSprite.getPosition();
                    float module_distance = Module(distance);
                    if (module_distance <= HERO_DETECT_WAYPOINT) {
                        if (m_waypoint < m_path.size() - 1) {
                            m_waypoint++;
                            m_direction = m_path[m_waypoint] - m_mainSprite.getPosition();
                            m_direction = Normalize(m_direction, Module(m_direction));
                        } else {
                            m_pathComplete = true;
                            m_direction = m_destiny - m_mainSprite.getPosition();
                            m_direction = Normalize(m_direction, Module(m_direction));
                        }
                    }

                }

                this->Move(dt);
            }
        }
    }
    
    void Healer::OrderMovement(sf::Vector2f l_destiny)
    {
        m_backupPath = m_path;
        m_path.clear();
        if (m_map.GetPath(m_mainSprite.getPosition(), l_destiny, m_path)) 
        { 
            m_waypoint = 1;
            m_pathComplete = false;
            bool ishealing = false;
            bool isattacking = false;
            std::cout<<"Entro"<<std::endl;
            this->CheckPath();
            std::reverse(std::begin(m_path), std::end(m_path));
            m_destiny = l_destiny;
            m_destinyPointer.setPosition(l_destiny);
            m_direction = m_path[m_waypoint] - m_mainSprite.getPosition();
            m_direction = Normalize(m_direction, Module(m_direction));
            for(int i = 0; i<m_allies.size(); i++)
            {
                if(i!=m_Id && m_allies[i]->ImTargeted())
                {
                    ishealing = true;
                    m_healTarget = i;
                }
            }
            
            for(int i=0; i<m_enemies.size(); i++)
            {
                if(m_data->input.IsSpriteClicked(m_enemies[i]->GetSprite(), sf::Mouse::Right, m_data->window))
                {
                    isattacking = true;
                    m_attackTarget = i;
                }
            }
            
            if(ishealing)
            {
                m_state = HERO_FOLLOWING_HERO;
                m_followingHeroClock.restart();
                
            }
            else if(isattacking)
            {
                m_state = HERO_FOLLOWING_ENEMY;
                m_recalculateElapsed.restart();
            }
            else
                m_state = HERO_MOVING_STATE;         
        } 
        else 
        {
            m_path = m_backupPath;
        }
    }
    
    void Healer::HealHero()
    {
        m_allies[m_healTarget]->Heal(10.0);
    }
    
    void Healer::RecalculateHeroLocation()
    {
        if (m_map.GetPath(m_mainSprite.getPosition(), m_allies[m_healTarget]->GetCurrentPosition(), m_path)) 
        { 
            m_waypoint = 1;
            m_pathComplete = false;
            bool ishealing = false;
            std::cout<<"Entro"<<std::endl;
            this->CheckPath();
            std::reverse(std::begin(m_path), std::end(m_path));
            m_destiny = m_allies[m_healTarget]->GetCurrentPosition();
            m_destinyPointer.setPosition(m_allies[m_healTarget]->GetCurrentPosition());
            m_direction = m_path[m_waypoint] - m_mainSprite.getPosition();
            m_direction = Normalize(m_direction, Module(m_direction));
        }
    }
    
    void Healer::RecalculateEnemy()
    {
        if (m_map.GetPath(m_mainSprite.getPosition(), m_enemies[m_attackTarget]->GetPosition(), m_path)) 
        { 
            m_waypoint = 1;
            m_pathComplete = false;
            this->CheckPath();
            std::reverse(std::begin(m_path), std::end(m_path));
            m_destiny = m_enemies[m_attackTarget]->GetPosition();
            m_destinyPointer.setPosition(m_enemies[m_attackTarget]->GetPosition());
            m_direction = m_path[m_waypoint] - m_mainSprite.getPosition();
            m_direction = Normalize(m_direction, Module(m_direction));
            m_state = HERO_FOLLOWING_ENEMY;
        }
    }
}