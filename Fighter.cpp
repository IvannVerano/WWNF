#include "Fighter.hpp"
#include "DEFINITIONS.hpp"

namespace Zenon
{
    Fighter::Fighter(GameDataRef l_data, Maps& l_map, int l_id, const std::vector<Enemy*>& l_enemies) : Hero(l_data,l_map,l_id), m_enemies(l_enemies)
    {
        m_mainSprite.setTexture(m_data->assets.GetTexture("Hero"));
        m_mainSprite.setTextureRect(sf::IntRect(105, 284, 14, 42));
        m_mainSprite.setOrigin(m_mainSprite.getGlobalBounds().width / 2, m_mainSprite.getGlobalBounds().height / 2);
        m_mainSprite.setPosition(500, 500);
        m_mainSprite.scale(2.0, 2.0);
        
        m_heroHUD.setTexture(m_data->assets.GetTexture("Hero_Face1"));
        m_heroHUD.setOrigin(m_heroHUD.getLocalBounds().width / 2, m_heroHUD.getLocalBounds().height / 2);
        m_heroHUD.setPosition(885,900);
        m_heroHUD.scale(0.92,0.92);
        
        m_heroHUDred.setSize(sf::Vector2f(100,15));
        m_heroHUDred.setPosition(m_heroHUD.getPosition().x - m_heroHUD.getGlobalBounds().width/2, m_heroHUD.getPosition().y+m_heroHUD.getGlobalBounds().height/2);
        m_heroHUDred.setFillColor(sf::Color::Red);
        
        m_heroHUDLife.setSize(sf::Vector2f(100,15));
        m_heroHUDLife.setPosition(m_heroHUD.getPosition().x - m_heroHUD.getGlobalBounds().width/2, m_heroHUD.getPosition().y+m_heroHUD.getGlobalBounds().height/2);
        m_heroHUDLife.setFillColor(sf::Color::Green);
        
        
        //Construimos las animaciones
        m_lateralMovementTexture = m_data->assets.GetTexture("LATERAL_MOV_FIGHTER");
        m_lateralAnimation.push_back(sf::IntRect(100,0,20,28));
        m_lateralAnimation.push_back(sf::IntRect(88,30,18,29));
        m_lateralAnimation.push_back(sf::IntRect(88,30,18,29));
        m_lateralAnimation.push_back(sf::IntRect(106,30,16,32));
        m_lateralAnimation.push_back(sf::IntRect(106,30,16,32));
        m_lateralAnimation.push_back(sf::IntRect(71,30,17,32));
        m_lateralAnimation.push_back(sf::IntRect(71,30,17,32));
        m_lateralAnimation.push_back(sf::IntRect(0,31,17,32));
        m_lateralAnimation.push_back(sf::IntRect(0,31,17,32));
        m_lateralAnimation.push_back(sf::IntRect(0,0,25,31));
        m_lateralAnimation.push_back(sf::IntRect(0,0,25,31));
        m_lateralAnimation.push_back(sf::IntRect(71,0,29,30));
        m_lateralAnimation.push_back(sf::IntRect(71,0,29,30));
        m_lateralAnimation.push_back(sf::IntRect(0,0,25,31));
        m_lateralAnimation.push_back(sf::IntRect(0,0,25,31));
        m_lateralAnimation.push_back(sf::IntRect(0,31,17,32));
        m_lateralAnimation.push_back(sf::IntRect(0,31,17,32));
        m_lateralAnimation.push_back(sf::IntRect(71,30,17,32));
        m_lateralAnimation.push_back(sf::IntRect(71,30,17,32));
        m_lateralAnimation.push_back(sf::IntRect(106,30,16,32));
        m_lateralAnimation.push_back(sf::IntRect(106,30,16,32));
        m_lateralAnimation.push_back(sf::IntRect(88,30,18,29));
        m_lateralAnimation.push_back(sf::IntRect(88,30,18,29));
        m_lateralAnimation.push_back(sf::IntRect(100,0,20,28));
        
        m_mainAnimation = m_lateralAnimation;
        
    }
    
    
    void Fighter::Update(float dt)
    {
        if (m_live <= 0) {
            m_state = HERO_DEAD_STATE;
        }
          
        if(m_state == HERO_IDLE_STATE)
        {
            for(int i = 0; i<m_enemies.size(); i++)
            {
                sf::Vector2f distance = m_mainSprite.getPosition() - m_enemies[i]->GetSprite().getPosition();
                float l_module = Module(distance);
                if(l_module < HERO_DETECT_ENEMY)
                {
                    m_target = i;
                    this->RecalculateEnemyPath();
                }
            }
        }

        if (m_state != HERO_DEAD_STATE) {
            m_heroArrow.setPosition(m_mainSprite.getPosition().x, m_mainSprite.getPosition().y - 60);
            m_heroPlace.setPosition(m_mainSprite.getPosition().x, m_mainSprite.getPosition().y + 30);
            m_destinyPointer.rotate(2);
            
            if(m_state == HERO_FOLLOWING_ENEMY)
            {
                if(m_recalculateElapsed.getElapsedTime().asSeconds() > HERO_LOOKTIME)
                {
                  this->RecalculateEnemyPath();
                    m_recalculateElapsed.restart();  
                }
                
                sf::Vector2f distance = m_mainSprite.getPosition() - m_enemies[m_target]->GetSprite().getPosition();
                float l_module = Module(distance);
                if(l_module<HERO_HITTINGDISTANCE)
                {
                    m_state = HERO_ATTACKING_ENEMY;
                }
                
            }
            
            if (m_mainSprite.getGlobalBounds().contains(m_destinyPointer.getPosition()))
                m_state = HERO_IDLE_STATE;
            if (m_state == HERO_MOVING_STATE || m_state == HERO_FOLLOWING_ENEMY) {
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
            
            if(m_state == HERO_ATTACKING_ENEMY)
            {
                if(m_attackTimer.getElapsedTime().asSeconds() > HERO_ATTACKINGTIME)
                {
                    for(int i = 0; i< m_enemies.size(); i++)
                    {
                         sf::Vector2f distance = m_mainSprite.getPosition() - m_enemies[i]->GetSprite().getPosition();
                         float l_module = Module(distance);
                         if(l_module < HERO_HITTINGRANGE)
                         {
                             std::cout<<"Atacooo"<<std::endl;
                             m_enemies[i]->TakeDamage(25);
                         }
                    }
                    m_attackTimer.restart();
                }
                
                sf::Vector2f distance = m_mainSprite.getPosition() - m_enemies[m_target]->GetSprite().getPosition();
                float l_module = Module(distance);
                
                if(l_module> HERO_HITTINGDISTANCE)
                {
                    this->RecalculateEnemyPath();
                }
                
            }
        }
    }
    
    void Fighter::OrderMovement(sf::Vector2f l_destiny)
    {
        bool flagEnemyDetected = false;
        m_backupPath = m_path;
        m_path.clear();
        if (m_map.GetPath(m_mainSprite.getPosition(), l_destiny, m_path)) 
        { 
            m_waypoint = 1;
            m_pathComplete = false;
            this->CheckPath();
            std::reverse(std::begin(m_path), std::end(m_path));
            m_destiny = l_destiny;
            m_destinyPointer.setPosition(l_destiny);
            m_direction = m_path[m_waypoint] - m_mainSprite.getPosition();
            m_direction = Normalize(m_direction, Module(m_direction));
            for(int i=0; i<m_enemies.size(); i++)
            {
                if(m_data->input.IsSpriteClicked(m_enemies[i]->GetSprite(), sf::Mouse::Button(sf::Mouse::Right), m_data->window))
                {
                    flagEnemyDetected = true;
                    m_target = i;
                }
            }
            
            if(flagEnemyDetected)
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
    
    void Fighter::RecalculateEnemyPath()
    {
        if (m_map.GetPath(m_mainSprite.getPosition(), m_enemies[m_target]->GetPosition(), m_path)) 
        { 
            m_waypoint = 1;
            m_pathComplete = false;
            this->CheckPath();
            std::reverse(std::begin(m_path), std::end(m_path));
            m_destiny = m_enemies[m_target]->GetPosition();
            m_destinyPointer.setPosition(m_enemies[m_target]->GetPosition());
            m_direction = m_path[m_waypoint] - m_mainSprite.getPosition();
            m_direction = Normalize(m_direction, Module(m_direction));
            m_state = HERO_FOLLOWING_ENEMY;
        }
    }
    
    void Fighter::CheckIfTargetIsDead()
    {
        if(m_enemies[m_target]->GetActualState() == ENEMY_STATE_DEAD)
        {
            m_target = -1;
            m_state = HERO_IDLE_STATE;
        }
    }
    
    void Fighter::Animate()
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
    
    void Fighter::Draw()
    {
        if (m_state == HERO_MOVING_STATE) {
            m_mainSprite.setTexture(m_lateralMovementTexture);
            this->SelectAnimation();
            this->Animate();
            m_data->window.draw(m_destinyPointer);
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
    
    void Fighter::SelectAnimation()
    {
        sf::Vector2f distance = m_destiny - m_mainSprite.getPosition();
        
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