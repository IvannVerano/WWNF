/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Trapper.cpp
 * Author: edward
 *
 * Created on 30 de abril de 2018, 2:21
 */

#include "Trapper.hpp"

namespace Zenon {

    Trapper::Trapper(GameDataRef l_data, Enemy::TYPE l_type, sf::Vector2f l_position, Maps& l_map, const std::vector<Enemy*>& l_neighbors, const std::vector<Trampa*>& l_traps, const std::vector<Objective*>& l_objectives) :
    Enemy(l_data, l_type, l_position, l_neighbors), m_map(l_map), m_traps(l_traps), m_objectives(l_objectives) {

        m_life = 5000;
        m_movingFrames = m_data->assets.GetTexture("Trapper_animation");
        m_enemySprite.setTexture(m_movingFrames);
        
        
        m_animationMovement.push_back(sf::IntRect(120, 207, 24, 55));
        m_animationMovement.push_back(sf::IntRect(120, 207, 24, 55));
        m_animationMovement.push_back(sf::IntRect(120, 207, 24, 55));
        m_animationMovement.push_back(sf::IntRect(120, 207, 24, 55));
        m_animationMovement.push_back(sf::IntRect(0, 104, 31, 56));
        m_animationMovement.push_back(sf::IntRect(0, 104, 31, 56));
        m_animationMovement.push_back(sf::IntRect(0, 104, 31, 56));
        m_animationMovement.push_back(sf::IntRect(0, 104, 31, 56));
        m_animationMovement.push_back(sf::IntRect(43, 0, 45, 51));
        m_animationMovement.push_back(sf::IntRect(43, 0, 45, 51));
        m_animationMovement.push_back(sf::IntRect(43, 0, 45, 51));
        m_animationMovement.push_back(sf::IntRect(43, 0, 45, 51));
        m_animationMovement.push_back(sf::IntRect(0, 363, 38, 55));
        m_animationMovement.push_back(sf::IntRect(0, 363, 38, 55));
        m_animationMovement.push_back(sf::IntRect(0, 363, 38, 55));
        m_animationMovement.push_back(sf::IntRect(0, 363, 38, 55));
        m_animationMovement.push_back(sf::IntRect(0, 104, 31, 56));
        m_animationMovement.push_back(sf::IntRect(0, 104, 31, 56));
        m_animationMovement.push_back(sf::IntRect(0, 104, 31, 56));
        m_animationMovement.push_back(sf::IntRect(0, 104, 31, 56));
        m_animationMovement.push_back(sf::IntRect(120, 207, 24, 55));
        m_animationMovement.push_back(sf::IntRect(120, 207, 24, 55));
        m_animationMovement.push_back(sf::IntRect(120, 207, 24, 55));
        m_animationMovement.push_back(sf::IntRect(120, 207, 24, 55));
        m_animationMovement.push_back(sf::IntRect(0, 104, 31, 56));
        m_animationMovement.push_back(sf::IntRect(0, 104, 31, 56));
        m_animationMovement.push_back(sf::IntRect(0, 104, 31, 56));
        m_animationMovement.push_back(sf::IntRect(0, 104, 31, 56));
        m_animationMovement.push_back(sf::IntRect(0, 104, 31, 56));
        m_animationMovement.push_back(sf::IntRect(0, 0, 43, 51));
        m_animationMovement.push_back(sf::IntRect(0, 0, 43, 51));
        m_animationMovement.push_back(sf::IntRect(0, 0, 43, 51));
        m_animationMovement.push_back(sf::IntRect(0, 0, 43, 51));
        m_animationMovement.push_back(sf::IntRect(0, 363, 38, 55));
        m_animationMovement.push_back(sf::IntRect(0, 363, 38, 55));
        m_animationMovement.push_back(sf::IntRect(0, 363, 38, 55));
        m_animationMovement.push_back(sf::IntRect(0, 363, 38, 55));
        
        m_attackAnimation.push_back(sf::IntRect(315, 0, 37, 50));
        m_attackAnimation.push_back(sf::IntRect(315, 0, 37, 50));
        m_attackAnimation.push_back(sf::IntRect(0, 160, 37, 48));
        m_attackAnimation.push_back(sf::IntRect(0, 160, 37, 48));
        m_attackAnimation.push_back(sf::IntRect(0, 418, 41, 50));
        m_attackAnimation.push_back(sf::IntRect(0, 418, 41, 50));
        m_attackAnimation.push_back(sf::IntRect(0, 51, 34, 53));
        m_attackAnimation.push_back(sf::IntRect(0, 51, 34, 53));
        m_attackAnimation.push_back(sf::IntRect(0, 208, 33, 51));
        m_attackAnimation.push_back(sf::IntRect(0, 208, 33, 51));
        m_attackAnimation.push_back(sf::IntRect(210, 100, 55, 50));
        m_attackAnimation.push_back(sf::IntRect(210, 100, 55, 50));
        m_attackAnimation.push_back(sf::IntRect(265, 100, 53, 48));
        m_attackAnimation.push_back(sf::IntRect(265, 100, 53, 48));
        m_attackAnimation.push_back(sf::IntRect(367, 100, 52, 48));
        m_attackAnimation.push_back(sf::IntRect(367, 100, 52, 48));
        m_attackAnimation.push_back(sf::IntRect(318, 100, 49, 48));
        m_attackAnimation.push_back(sf::IntRect(318, 100, 49, 48));
        m_attackAnimation.push_back(sf::IntRect(162, 100, 48, 47));
        m_attackAnimation.push_back(sf::IntRect(162, 100, 48, 47));
        
        
        m_enemySprite.setTextureRect(m_animationMovement.at(0));
        m_enemySprite.setOrigin(m_enemySprite.getGlobalBounds().width / 2, m_enemySprite.getGlobalBounds().height / 2);
        m_enemySprite.setPosition(l_position);
        m_enemySprite.scale(2.5f, 2.5f);
        
        m_mainAnimation = m_animationMovement;
        
        FindTrap();
    }

    Trapper::~Trapper() {
    }

    void Trapper::Update(float dt) {

        if (m_state != TRAPPER_HITING_CORE_STATE) {
            if (m_state == TRAPPER_FOLLOWING_TRAP_STATE) {
                std::cout << "me muevo hacia una trampa\n";
                if (!m_pathCompleted) {
                    if (m_traps[m_obj] != nullptr) {
                        std::cout << "Soy el enemigo: " << this->GetId() << " y me voy a mover. MI objetivo es: " << m_obj << std::endl;
                        if (m_traps[m_obj]->GetActualState() != TRAP_DYING_STATE && m_traps[m_obj]->GetLife() > 25 && m_traps[m_obj]->getDyingClockTime() >= 1) {
                            sf::Vector2f l_vec = m_pathObj[m_currentWP] - m_enemySprite.getPosition();
                            float l_module = Module(l_vec);
                            if (l_module <= TRAPPER_MINIMUM_WP_D) {
                                if (m_currentWP == m_pathObj.size() - 2) {
                                    m_pathCompleted = true;
                                    m_state = TRAPPER_HITING_TRAP_STATE;
                                } else {
                                    m_currentWP++;
                                }
                            }

                            if (l_module > TRAPPER_MINIMUM_WP_D) {
                                l_vec = Normalize(l_vec, l_module);
                                m_enemySprite.move(TRAPPER_SPEED * dt * l_vec.x, TRAPPER_SPEED * dt * l_vec.y);
                            }
                        } else {
                            FindTrap();
                        }
                    } else {
                        FindTrap();
                    }
                }
            }

            if (m_state == TRAPPER_HITING_TRAP_STATE) {
                std::cout << "pego a una trampa una trampa\n";
                if (m_traps[m_obj] != nullptr) {
                    if (m_traps[m_obj]->GetActualState() != TRAP_DYING_STATE) {
                        if (m_hitingClock.getElapsedTime().asSeconds() >= TRAPPER_HITING_TIME) {
                            m_mainAnimation = m_attackAnimation;
                            m_traps[m_obj]->TakeDamage(25);
                            m_hitingClock.restart();
                        }
                    } else {
                        FindTrap();
                    }
                } else {
                    FindTrap();
                }
            }

            if (m_state == TRAPPER_FOLLOWING_CORE_STATE) {

                std::cout << "me muevo hacia el core\n";
                if (!m_pathCompleted) {
                    sf::Vector2f l_vec = m_pathObj[m_currentWP] - m_enemySprite.getPosition();
                    float l_module = Module(l_vec);

                    if (l_module < TRAPPER_MINIMUM_WP_D) {
                        if (m_currentWP == m_pathObj.size() - 2) {
                            m_pathCompleted = true;
                            m_state = TRAPPER_HITING_CORE_STATE;
                        } else {
                            m_currentWP++;
                        }
                    }

                    if (l_module > TRAPPER_MINIMUM_WP_D) {
                        l_vec = Normalize(l_vec, l_module);
                        m_enemySprite.move(TRAPPER_SPEED * dt * l_vec.x, TRAPPER_SPEED * dt * l_vec.y);
                    }
                }

            }

        } else {
            m_mainAnimation = m_attackAnimation;
            std::cout << "pego al core\n";
        }

    }

    bool Trapper::TheresTrap() {
        for (int i = 0; i < m_traps.size(); i++) {
            if (m_traps[i]->GetActualState() != TRAP_DESTROYED) {
                return true;
            }
        }

        return false;
    }

    void Trapper::CheckState() {
        if (m_traps.size() > 0) {
            if (!m_trapDestroyed) {
                FindTrap();
            }
        } else {
            FindCore();
        }
    }

    void Trapper::FindTrap() {
        m_obj = CheckNearTrap();
        m_pathObj.clear();
        m_debugCircles.clear();
        if (m_obj != -1) {
            if (m_map.GetPath(m_enemySprite.getPosition(), m_traps[m_obj]->GetPosition(), m_pathObj)) {
                CheckPath();
                std::reverse(m_pathObj.begin(), m_pathObj.end());
                m_state = TRAPPER_FOLLOWING_TRAP_STATE;
                m_currentWP = 1;
                m_pathCompleted = false;
                for (int i = 0; i < m_pathObj.size(); i++) {
                    sf::CircleShape circle;
                    circle.setRadius(3);
                    circle.setFillColor(sf::Color::Green);
                    circle.setOrigin(circle.getGlobalBounds().width / 2, circle.getGlobalBounds().height / 2);
                    m_debugCircles.push_back(circle);
                }
            }
        } else {
            FindCore();
        }
    }

    int Trapper::CheckNearTrap() {
        float d = 0;
        float minD = 100000;
        int obj = -1;
        int cuantos = 0;

        if (m_traps.size() > 0) {
            for (int i = 0; i < m_traps.size(); i++) {
                if (m_traps[i] != nullptr) {
                    if (m_traps[i]->GetLife() > 25 && m_traps[i]->GetActualState() != TRAP_DYING_STATE && m_traps[i] ->getDyingClockTime() >= 1) {
                        sf::Vector2f vec = m_traps[i]->GetPosition() - m_enemySprite.getPosition();
                        cuantos++;
                        d = Module(vec);
                        if (d < minD) {
                            minD = d;
                            obj = i;
                        }
                    }
                }
            }
            if (cuantos == 0) {
                obj = -1;
            }
        } else {
            obj = -1;
        }
        return obj;
    }

    void Trapper::FindCore() {
        m_pathObj.clear();
        if (m_map.GetPath(m_enemySprite.getPosition(), m_objectives[2]->GetPosition(), m_pathObj)) {
            m_obj = 2;
            CheckPath();
            std::reverse(m_pathObj.begin(), m_pathObj.end());
            m_state = TRAPPER_FOLLOWING_CORE_STATE;
            m_currentWP = 1;
            m_pathCompleted = false;
        }

    }
    void Trapper::CheckPath() {
        int contador = 0;
        while (contador < m_pathObj.size()) {
            if (contador + 1 >= m_pathObj.size() || contador - 1 == 0)
                contador++;
            else {
                if ((m_pathObj[contador - 1].y == m_pathObj[contador].y) && (m_pathObj[contador + 1].x == m_pathObj[contador].x)) {
                    m_pathObj.erase(m_pathObj.begin() + contador);
                } else
                    contador++;
            }
        }
    }

    void Trapper::Draw() {

        for (int i = 0; i < m_debugCircles.size(); i++) {
            this->m_data->window.draw(m_debugCircles[i]);
        }
        if(m_state == TRAPPER_FOLLOWING_CORE_STATE || m_state == TRAPPER_FOLLOWING_TRAP_STATE)
        {
            m_mainAnimation = m_animationMovement;
        }
        this->Animate();
        this->m_data->window.draw(m_enemySprite);
    }
    
    void Trapper::Animate()
    {
        if (m_aniClock.getElapsedTime().asSeconds() > 1.5f / m_mainAnimation.size()) {
            
            if (m_animationCounter < m_mainAnimation.size() - 1) 
            {
                m_animationCounter++;
            } 
            else 
            {
                m_animationCounter = 0;
            }

            m_enemySprite.setTextureRect(m_mainAnimation.at(m_animationCounter));

            m_aniClock.restart();
        }
    }
}

