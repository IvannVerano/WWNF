#include "Fighter.hpp"
#include "DEFINITIONS.hpp"

namespace Zenon
{
    Fighter::Fighter(GameDataRef l_data, Maps& l_map, int l_id, const std::vector<Enemy*>& l_enemies) : Hero(l_data,l_map,l_id), m_enemies(l_enemies)
    {
        m_buffer.loadFromFile(SWORD_SOUND);
        m_sound.setBuffer(m_buffer);
        
        m_mainSprite.setTexture(m_data->assets.GetTexture("Hero"));
        m_mainSprite.setTextureRect(sf::IntRect(105, 284, 14, 42));
        m_mainSprite.setOrigin(m_mainSprite.getGlobalBounds().width / 2, m_mainSprite.getGlobalBounds().height / 2);
        m_mainSprite.setPosition(500, 500);
        m_mainSprite.scale(2.0, 2.0);
        
        m_heroHUD.setTexture(m_data->assets.GetTexture("Hero_Face1"));
        m_heroHUD.setOrigin(m_heroHUD.getLocalBounds().width / 2, m_heroHUD.getLocalBounds().height / 2);
        m_heroHUD.setPosition(1300,980);
        m_heroHUD.scale(0.92,0.92);
        
        m_heroHUDred.setSize(sf::Vector2f(100,15));
        m_heroHUDred.setPosition(m_heroHUD.getPosition().x - m_heroHUD.getGlobalBounds().width/2, m_heroHUD.getPosition().y+m_heroHUD.getGlobalBounds().height/2);
        m_heroHUDred.setFillColor(sf::Color::Red);
        
        m_heroHUDLife.setSize(sf::Vector2f(100,15));
        m_heroHUDLife.setPosition(m_heroHUD.getPosition().x - m_heroHUD.getGlobalBounds().width/2, m_heroHUD.getPosition().y+m_heroHUD.getGlobalBounds().height/2);
        m_heroHUDLife.setFillColor(sf::Color::Green);
        
        
        //Construimos las animaciones
        m_idleTexture = m_data->assets.GetTexture("Hero1_Idle");
        m_lateralMovementTexture = m_data->assets.GetTexture("LATERAL_MOV_FIGHTER");
        m_upMovementTexture = m_data->assets.GetTexture("Hero1_Up_animation");
        m_downMovementTexture = m_data->assets.GetTexture("Hero1_Down_animation");
        m_attackingAnimationTexture = m_data->assets.GetTexture("Hero1_Attack");
        
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
        
        
        //Animacion para arriba
        m_upAnimation.push_back(sf::IntRect(0,0,14,34));
        m_upAnimation.push_back(sf::IntRect(0,0,14,34));
        m_upAnimation.push_back(sf::IntRect(14,0,14,33));
        m_upAnimation.push_back(sf::IntRect(14,0,14,33));
        m_upAnimation.push_back(sf::IntRect(28,33,14,25));
        m_upAnimation.push_back(sf::IntRect(28,33,14,25));
        m_upAnimation.push_back(sf::IntRect(42,33,12,26));
        m_upAnimation.push_back(sf::IntRect(42,33,12,26));
        m_upAnimation.push_back(sf::IntRect(14,0,13,27));
        m_upAnimation.push_back(sf::IntRect(14,0,13,27));
        m_upAnimation.push_back(sf::IntRect(28,0,15,33));
        m_upAnimation.push_back(sf::IntRect(28,0,15,33));
        m_upAnimation.push_back(sf::IntRect(0,34,13,29));
        m_upAnimation.push_back(sf::IntRect(0,34,13,29));
        
        //Animacion para abajo
        m_downAnimation.push_back(sf::IntRect(81,0,15,32));
        m_downAnimation.push_back(sf::IntRect(81,0,15,32));
        m_downAnimation.push_back(sf::IntRect(49,0,16,33));
        m_downAnimation.push_back(sf::IntRect(49,0,16,33));
        m_downAnimation.push_back(sf::IntRect(0,0,17,36));
        m_downAnimation.push_back(sf::IntRect(0,0,17,36));
        m_downAnimation.push_back(sf::IntRect(65,0,16,36));
        m_downAnimation.push_back(sf::IntRect(65,0,16,36));
        m_downAnimation.push_back(sf::IntRect(81,0,15,32));
        m_downAnimation.push_back(sf::IntRect(81,0,15,32));
        m_downAnimation.push_back(sf::IntRect(34,0,15,32));
        m_downAnimation.push_back(sf::IntRect(34,0,15,32));
        m_downAnimation.push_back(sf::IntRect(17,0,17,32));
        m_downAnimation.push_back(sf::IntRect(17,0,17,32));
        m_downAnimation.push_back(sf::IntRect(17,32,15,32));
        m_downAnimation.push_back(sf::IntRect(17,32,15,32));
        
        //Animacion de ataque
        m_attackAnimation.push_back(sf::IntRect(85,47,26,44));
        m_attackAnimation.push_back(sf::IntRect(0,0,42,42));
        m_attackAnimation.push_back(sf::IntRect(0,87,42,40));
        m_attackAnimation.push_back(sf::IntRect(0,87,42,40));
        m_attackAnimation.push_back(sf::IntRect(0,42,42,45));
        m_attackAnimation.push_back(sf::IntRect(42,0,43,45));
        m_attackAnimation.push_back(sf::IntRect(42,0,43,45));
        m_attackAnimation.push_back(sf::IntRect(85,0,45,47));
        m_attackAnimation.push_back(sf::IntRect(85,0,45,47));
        m_attackAnimation.push_back(sf::IntRect(85,47,26,44));
        m_attackAnimation.push_back(sf::IntRect(85,47,26,44));
        m_attackAnimation.push_back(sf::IntRect(85,47,26,44));
        m_attackAnimation.push_back(sf::IntRect(85,47,26,44));
        m_attackAnimation.push_back(sf::IntRect(85,47,26,44));
        m_attackAnimation.push_back(sf::IntRect(85,47,26,44));
        m_attackAnimation.push_back(sf::IntRect(85,47,26,44));
        m_attackAnimation.push_back(sf::IntRect(85,47,26,44));
        m_attackAnimation.push_back(sf::IntRect(85,47,26,44));
        m_attackAnimation.push_back(sf::IntRect(85,47,26,44));
        
        //Animacion de idle
        m_idleAnimation.push_back(sf::IntRect(0,0,13,36));
        m_idleAnimation.push_back(sf::IntRect(65,0,13,36));
        m_idleAnimation.push_back(sf::IntRect(65,0,13,36));
        m_idleAnimation.push_back(sf::IntRect(0,36,13,36));
        m_idleAnimation.push_back(sf::IntRect(0,36,13,36));
        m_idleAnimation.push_back(sf::IntRect(52,0,13,36));
        m_idleAnimation.push_back(sf::IntRect(52,0,13,36));
        m_idleAnimation.push_back(sf::IntRect(52,0,13,36));
        m_idleAnimation.push_back(sf::IntRect(0,36,13,36));
        m_idleAnimation.push_back(sf::IntRect(0,36,13,36));
        m_idleAnimation.push_back(sf::IntRect(65,0,13,36));
        m_idleAnimation.push_back(sf::IntRect(65,0,13,36));
        m_idleAnimation.push_back(sf::IntRect(0,0,13,36));
        m_idleAnimation.push_back(sf::IntRect(26,0,13,36));
        m_idleAnimation.push_back(sf::IntRect(26,0,13,36));
        m_idleAnimation.push_back(sf::IntRect(39,0,13,36));
        
        
        m_mainAnimation = m_idleAnimation;
        
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
                    m_sound.play();
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
    
    void Fighter::SelectTexture()
    {
        sf::Vector2f distance = m_destiny - m_mainSprite.getPosition();
        if(std::abs(distance.y) > std::abs(distance.x))
        {
            if(distance.y<0)
                m_mainSprite.setTexture(m_upMovementTexture);
            else
                m_mainSprite.setTexture(m_downMovementTexture);
        }
        else
        {
            m_mainSprite.setTexture(m_lateralMovementTexture);
        }
    }
    
    void Fighter::Draw()
    {
        if (m_state == HERO_MOVING_STATE || m_state == HERO_FOLLOWING_ENEMY) {
            if(m_switchAnimation.getElapsedTime().asSeconds() > 0.2f)
            {
                this->SelectTexture();
                this->SelectAnimation();
                m_switchAnimation.restart();
            }
            m_data->window.draw(m_destinyPointer);
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
        
        if(m_state == HERO_IDLE_STATE)
        {
            if(m_switchAnimation.getElapsedTime().asSeconds() > 0.2f)
            {
                m_mainSprite.setTexture(m_idleTexture);
                m_mainAnimation = m_idleAnimation;
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
    
    void Fighter::SelectAnimation()
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
    
    
}