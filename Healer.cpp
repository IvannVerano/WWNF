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
        
        m_heroHUD.setTexture(m_data->assets.GetTexture("HERO_FACE2"));
        m_heroHUD.setOrigin(m_heroHUD.getLocalBounds().width / 2, m_heroHUD.getLocalBounds().height / 2);
        m_heroHUD.setPosition(1450,980);
        //m_heroHUD.scale(0.92,0.92);
        
        m_heroHUDred.setSize(sf::Vector2f(100,15));
        m_heroHUDred.setPosition(m_heroHUD.getPosition().x - m_heroHUD.getGlobalBounds().width/2, m_heroHUD.getPosition().y+m_heroHUD.getGlobalBounds().height/2);
        m_heroHUDred.setFillColor(sf::Color::Red);
        
        m_heroHUDLife.setSize(sf::Vector2f(100,15));
        m_heroHUDLife.setPosition(m_heroHUD.getPosition().x - m_heroHUD.getGlobalBounds().width/2, m_heroHUD.getPosition().y+m_heroHUD.getGlobalBounds().height/2);
        m_heroHUDLife.setFillColor(sf::Color::Green);
        
        
        m_lateralMovementTexture = m_data->assets.GetTexture("Hero2_Moving");
        m_upMovementTexture = m_data->assets.GetTexture("Hero2_UpDown");
        m_idleTexture = m_data->assets.GetTexture("Hero2_Idle");
        m_attackingAnimationTexture = m_data->assets.GetTexture("Hero2_Attack");
        
        m_lateralAnimation.push_back(sf::IntRect(0,0,18,33));
        m_lateralAnimation.push_back(sf::IntRect(0,67,14,36));
        m_lateralAnimation.push_back(sf::IntRect(0,67,14,36));
        m_lateralAnimation.push_back(sf::IntRect(42,33,16,37));
        m_lateralAnimation.push_back(sf::IntRect(42,33,16,37));
        m_lateralAnimation.push_back(sf::IntRect(0,33,18,34));
        m_lateralAnimation.push_back(sf::IntRect(0,33,18,34));
        m_lateralAnimation.push_back(sf::IntRect(18,0,22,33));
        m_lateralAnimation.push_back(sf::IntRect(18,0,22,33));
        m_lateralAnimation.push_back(sf::IntRect(40,0,25,33));
        
        m_upAnimation.push_back(sf::IntRect(17,0,17,37));
        m_upAnimation.push_back(sf::IntRect(17,0,17,37));
        m_upAnimation.push_back(sf::IntRect(17,71,17,34));
        m_upAnimation.push_back(sf::IntRect(17,71,17,34));
        m_upAnimation.push_back(sf::IntRect(52,0,17,32));
        m_upAnimation.push_back(sf::IntRect(52,0,17,32));
        m_upAnimation.push_back(sf::IntRect(86,0,14,34));
        m_upAnimation.push_back(sf::IntRect(86,0,14,34));
        m_upAnimation.push_back(sf::IntRect(52,65,16,38));
        m_upAnimation.push_back(sf::IntRect(52,65,16,38));
        m_upAnimation.push_back(sf::IntRect(69,0,17,38));
        m_upAnimation.push_back(sf::IntRect(69,0,17,38));
        m_upAnimation.push_back(sf::IntRect(69,38,17,34));
        m_upAnimation.push_back(sf::IntRect(69,38,17,34));
        m_upAnimation.push_back(sf::IntRect(69,72,17,32));
        m_upAnimation.push_back(sf::IntRect(69,72,17,32));
        m_upAnimation.push_back(sf::IntRect(86,65,14,31));
        m_upAnimation.push_back(sf::IntRect(86,65,14,31));
        
        
        m_downAnimation.push_back(sf::IntRect(34,0,18,38));
        m_downAnimation.push_back(sf::IntRect(34,0,18,38));
        m_downAnimation.push_back(sf::IntRect(0,80,16,37));
        m_downAnimation.push_back(sf::IntRect(0,80,16,37));
        m_downAnimation.push_back(sf::IntRect(0,0,17,37));
        m_downAnimation.push_back(sf::IntRect(0,0,17,37));
        m_downAnimation.push_back(sf::IntRect(116,0,17,34));
        m_downAnimation.push_back(sf::IntRect(116,0,17,34));
        m_downAnimation.push_back(sf::IntRect(116,34,17,35));
        m_downAnimation.push_back(sf::IntRect(116,34,17,35));
        m_downAnimation.push_back(sf::IntRect(17,37,17,34));
        m_downAnimation.push_back(sf::IntRect(17,37,17,34));
        m_downAnimation.push_back(sf::IntRect(34,0,18,38));
        m_downAnimation.push_back(sf::IntRect(34,0,18,38));
        m_downAnimation.push_back(sf::IntRect(0,80,16,37));
        m_downAnimation.push_back(sf::IntRect(0,80,16,37));
        m_downAnimation.push_back(sf::IntRect(0,0,17,37));
        m_downAnimation.push_back(sf::IntRect(0,0,17,37));
        m_downAnimation.push_back(sf::IntRect(116,0,17,34));
        m_downAnimation.push_back(sf::IntRect(116,0,17,34));
        m_downAnimation.push_back(sf::IntRect(116,34,17,35));
        m_downAnimation.push_back(sf::IntRect(116,34,17,35));
        m_downAnimation.push_back(sf::IntRect(17,37,17,34));
        
        m_idleAnimation.push_back(sf::IntRect(0,0,18,36));
        m_idleAnimation.push_back(sf::IntRect(18,0,18,36));
        m_idleAnimation.push_back(sf::IntRect(18,0,18,36));
        m_idleAnimation.push_back(sf::IntRect(36,0,18,36));
        m_idleAnimation.push_back(sf::IntRect(36,0,18,36));
        m_idleAnimation.push_back(sf::IntRect(54,0,18,36));
        m_idleAnimation.push_back(sf::IntRect(54,0,18,36));
        m_idleAnimation.push_back(sf::IntRect(72,0,18,36));
        m_idleAnimation.push_back(sf::IntRect(72,0,18,36));
        m_idleAnimation.push_back(sf::IntRect(90,0,18,36));
        m_idleAnimation.push_back(sf::IntRect(90,0,18,36));
        
        m_attackAnimation.push_back(sf::IntRect(82,0,23,35));
        m_attackAnimation.push_back(sf::IntRect(0,44,38,43));
        m_attackAnimation.push_back(sf::IntRect(82,0,23,35));
        m_attackAnimation.push_back(sf::IntRect(82,0,23,35));
        m_attackAnimation.push_back(sf::IntRect(0,44,38,43));
        m_attackAnimation.push_back(sf::IntRect(0,44,38,43));
        m_attackAnimation.push_back(sf::IntRect(0,0,41,44));
        m_attackAnimation.push_back(sf::IntRect(0,0,41,44));
        m_attackAnimation.push_back(sf::IntRect(82,0,23,44));
        m_attackAnimation.push_back(sf::IntRect(82,0,23,44));
        m_attackAnimation.push_back(sf::IntRect(82,0,23,44));
        m_attackAnimation.push_back(sf::IntRect(82,0,23,44));
        m_attackAnimation.push_back(sf::IntRect(82,0,23,44));
        m_attackAnimation.push_back(sf::IntRect(82,0,23,44));
        m_attackAnimation.push_back(sf::IntRect(82,0,23,44));
        
        m_mainAnimation = m_idleAnimation;
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
    
    void Healer::Draw()
    {
        if (m_state == HERO_MOVING_STATE || m_state == HERO_FOLLOWING_ENEMY || m_state == HERO_FOLLOWING_HERO) 
        {
            if(m_switchAnimation.getElapsedTime().asSeconds() > 0.2f)
            {
                this->SelectTexture();
                this->SelectAnimation();
                m_switchAnimation.restart();
            }
            m_data->window.draw(m_destinyPointer);
            this->Animate();
        }
        
        if(m_state == HERO_IDLE_STATE)
        {
            if(m_switchAnimation.getElapsedTime().asSeconds() > 0.2f)
            {
                m_mainSprite.setTexture(m_idleTexture);
                m_mainAnimation = m_idleAnimation;
            }
            this->Animate();
        }
        
        if(m_state == HERO_ATTACKING_ENEMY)
        {
            if(m_switchAnimation.getElapsedTime().asSeconds() > 0.2f)
            {
                m_mainSprite.setTexture(m_attackingAnimationTexture);
                m_mainAnimation = m_attackAnimation;
            }
            this->Animate();
        }
        
        if (m_isSelected) 
        {
            m_data->window.draw(m_heroPlace);
            m_data->window.draw(m_heroArrow);
        }
        
        m_data->window.draw(m_heroHUD);
        m_data->window.draw(m_heroHUDred);
        m_data->window.draw(m_heroHUDLife);
        m_data->window.draw(m_mainSprite);
    }
    
    void Healer::SelectAnimation()
    {
       sf::Vector2f distance = m_destiny - m_mainSprite.getPosition();
        if(std::abs(distance.y) > std::abs(distance.x))
        {
            if(distance.y<0)
            {
                m_mainAnimation = m_upAnimation;
            }
            else
            {
                m_mainAnimation = m_downAnimation;
            }
        }
        else
        {
            m_mainAnimation = m_lateralAnimation;
            if(distance.x < 0) // me muevo a la isquierda
            {
                if(m_way !=1)
                {
                    m_way = 1;
                    m_mainSprite.scale(-1.0,1.0);
                }
            }
            else if(distance.x > 0)
            {
                if(m_way !=0)
                {
                    if(m_way == 1)
                    {
                        m_way = 0;
                        m_mainSprite.scale(-1.0,1.0);
                    }
                }
            }
        }
     }
    
    void Healer::SelectTexture()
    {
       sf::Vector2f distance = m_destiny - m_mainSprite.getPosition();
       if(std::abs(distance.y) > std::abs(distance.x))
        {
            m_mainSprite.setTexture(m_upMovementTexture);
        }
        else
        {
            m_mainSprite.setTexture(m_lateralMovementTexture);
        }
    }
    
    void Healer::Animate()
    {
        if (m_aniClock.getElapsedTime().asSeconds() > SPEED_ANIMATION / m_mainAnimation.size()) {
            
            if (m_animationCounter < m_mainAnimation.size() - 1) 
            {
                m_animationCounter++;
            } 
            else 
            {
                m_animationCounter = 0;
            }

            m_mainSprite.setTextureRect(m_mainAnimation.at(m_animationCounter));

            m_aniClock.restart();
        }
    }
}