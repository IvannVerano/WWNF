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
        m_enemySprite.setTexture(this->m_data->assets.GetTexture("trapper"));
        m_enemySprite.setOrigin(m_enemySprite.getGlobalBounds().width / 2, m_enemySprite.getGlobalBounds().height / 2);
        m_enemySprite.setPosition(l_position);
        m_enemySprite.scale(0.7f, 0.7f);

        if (m_traps.size() > 0) {
            FindTrap();
        } else {
            std::cout << "entro aqui, no habia trampas\n";
            FindCore();
        }

    }

    Trapper::~Trapper() {
    }

    void Trapper::Update(float dt) {


        if (m_state == TRAPPER_HITING_CORE_STATE) {
            if (m_hitingClock.getElapsedTime().asSeconds() >= TRAPPER_HITING_TIME) {
                std::cout << "pego al core\n";
                m_objectives[m_objectives.size() - 1]->TakeDamage(50);
                m_hitingClock.restart();
            }
        } else {
            if (m_state == TRAPPER_FOLLOWING_TRAP_STATE) {
                if (!m_pathCompleted) {
                    if (m_traps[m_obj]->GetActualState() != TRAP_DESTROYED) {
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
                    }
                } else {
                    FindTrap();
                }
            }

            if (m_state == TRAPPER_HITING_TRAP_STATE) {
                if (m_traps.size() > 0) {
                    if (m_traps[m_obj]->GetActualState() != TRAP_DESTROYED) {
                        if (m_hitingClock.getElapsedTime().asSeconds() >= TRAPPER_HITING_TIME) {
                            std::cout << "pego a la trampa\n";
                            m_traps[m_obj]->TakeDamage(50);
                        }
                    } else {
                        FindTrap();
                    }
                } else {
                    FindCore();
                }
            }

            if (m_state == TRAPPER_FOLLOWING_CORE_STATE) {
                std::cout << "a moverse\n";
                if (!m_pathCompleted) {
                    if (m_traps.size() == 0) {
                        sf::Vector2f l_vec = m_pathObj[m_currentWP] - m_enemySprite.getPosition();
                        float l_module = Module(l_vec);
                        if (l_module <= TRAPPER_MINIMUM_WP_D) {
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
                    } else {
                        FindTrap();
                    }
                }
            }
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
        if (m_obj != -1) {
            if (m_map.GetPath(m_enemySprite.getPosition(), m_traps[m_obj]->GetPosition(), m_pathObj)) {
                CheckPath();
                std::reverse(m_pathObj.begin(), m_pathObj.end());
                m_state = TRAPPER_FOLLOWING_TRAP_STATE;
                m_currentWP = 1;
                m_pathCompleted = false;
            }
        } else {
            FindCore();
        }
    }

    void Trapper::FindCore() {
        m_pathObj.clear();
        if (m_map.GetPath(m_enemySprite.getPosition(), m_objectives[m_objectives.size() - 1]->GetPosition(), m_pathObj)) {
            CheckPath();
            std::reverse(m_pathObj.begin(), m_pathObj.end());
            m_state = TRAPPER_FOLLOWING_CORE_STATE;
            m_currentWP = 1;
            m_pathCompleted = false;
        }

    }

    int Trapper::CheckNearTrap() {
        float d = 0;
        float minD = 100000;
        int obj = -1;
        int cuantos = 0;

        if (m_traps.size() != 0) {
            for (int i = 0; i < m_traps.size(); i++) {
                if (m_traps[i]->GetLife() > 10 && m_traps[i]->GetActualState() != TRAP_DESTROYED && m_traps[i]->GetOcupada() == false) {
                    sf::Vector2f vec = m_traps[i]->GetPosition() - m_enemySprite.getPosition();
                    cuantos++;
                    d = Module(vec);
                    if (d < minD) {
                        minD = d;
                        obj = i;
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
        this->m_data->window.draw(m_enemySprite);
    }
}

