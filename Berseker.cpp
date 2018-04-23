/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Berseker.cpp
 * Author: edward
 *
 * Created on 18 de abril de 2018, 19:14
 */

#include "Berseker.hpp"

namespace Zenon {

    Berseker::Berseker(GameDataRef l_data, Enemy::TYPE l_type, sf::Vector2f l_position, const std::vector<Enemy*>& l_neighbors,
            Maps &l_map, std::vector<sf::Sprite>& l_objectives, const std::vector<Hero*>& l_heroes)
    : Enemy(l_data, l_type, l_position, l_neighbors), m_map(l_map), m_objectives(l_objectives), m_heroes(l_heroes) {

        m_objectives = l_objectives;
        m_enemySprite.setTexture(m_data->assets.GetTexture("berseker"));
        m_enemySprite.setOrigin(m_enemySprite.getGlobalBounds().width / 2, m_enemySprite.getGlobalBounds().height / 2);
        m_enemySprite.scale(0.7, 0.7);
        m_enemySprite.setPosition(l_position);
        FindObj();
        m_state = BERSEKER_MOVING_TO_OBJ_STATE;
    }

    Berseker::~Berseker() {

    }

    void Berseker::Update(float dt) {

        if (m_state == BERSEKER_FOLLOWING_HERO_STATE) {
            if (m_checkHeroClock.getElapsedTime().asSeconds() >= BERSEKER_CHECKING_HERO_TIME) {
                if (CheckNearHero()) {
                    sf::Vector2f l_vec = m_heroes[m_heroTarget]->GetCurrentPosition() - m_enemySprite.getPosition();
                    float l_module = Module(l_vec);
                    if (l_module <= BERSEKER_HITING_D && l_module > 32.0f) {
                        m_state = BERSEKER_HITING_HERO_STATE;
                        m_currentWP = 1;
                        m_pathComplete = false;
                    } else if (l_module > BERSEKER_HITING_D && l_module <= BERSEKER_HERO_DETECTION) {
                        FindHero();
                        m_currentWP = 1;
                        m_pathComplete = false;
                        m_checkHeroClock.restart();
                    }
                } else {
                    m_state = BERSEKER_MOVING_TO_OBJ_STATE;
                    m_pathComplete = false;
                    m_currentWP = 1;
                    FindObj();
                }
            }


            if (m_state == BERSEKER_FOLLOWING_HERO_STATE) {
                if (!m_pathComplete) {
                    sf::Vector2f l_direction = m_pathHero[m_currentWP] - m_enemySprite.getPosition();
                    float l_module = Module(l_direction);

                    if (l_module < BERSEKER_MINIMUM_WP_D) {
                        if (m_enemySprite.getGlobalBounds().intersects(m_heroes[m_heroTarget]->GetGB())) {
                            m_pathComplete = true;
                        } else {
                            m_currentWP++;
                        }
                    }

                    if (l_module >= BERSEKER_MINIMUM_WP_D) {
                        l_direction = Normalize(l_direction, l_module);
                        m_enemySprite.move(BERSEKER_SPEED * dt * l_direction.x, BERSEKER_SPEED * dt * l_direction.y);
                    }
                }
            }
        }


        if (m_state == BERSEKER_HITING_HERO_STATE) {
            if (CheckNearHero()) {
                if (m_hitingClock.getElapsedTime().asSeconds() >= BERSEKER_HIT_HERO_TIME) {
                    std::cout << "Ataque: -" << m_damage << std::endl;
                    m_heroes[m_heroTarget]->TakeDamage(m_damage);
                    std::cout << "vida del heroe: " << m_heroes[m_heroTarget]->GetLive() << std::endl;
                    m_hitingClock.restart();
                }
            }
        }

        if (m_state == BERSEKER_MOVING_TO_OBJ_STATE) {
            if (!CheckNearHero()) {
                if (!m_pathComplete) {
                    sf::Vector2f l_direction = m_pathObj[m_currentWP] - m_enemySprite.getPosition();
                    float l_module = Module(l_direction);

                    if (l_module < BERSEKER_MINIMUM_WP_D) {
                        if (m_enemySprite.getGlobalBounds().intersects(m_objectives[m_obj].getGlobalBounds())) {
                            m_pathComplete = true;
                        } else {
                            m_currentWP++;
                        }
                    }

                    if (l_module >= BERSEKER_MINIMUM_WP_D) {
                        l_direction = Normalize(l_direction, l_module);
                        m_enemySprite.move(BERSEKER_SPEED * dt * l_direction.x, BERSEKER_SPEED * dt * l_direction.y);
                    }
                }
            }
        }

    }

    void Berseker::Draw() {
        for (int i = 0; i < m_debugCircles.size(); i++) {
            this->m_data->window.draw(m_debugCircles[i]);
        }

        this->m_data->window.draw(m_enemySprite);
    }

    void Berseker::CheckState() {
        if (CheckNearHero()) {
            sf::Vector2f l_vec = m_heroes[m_heroTarget]->GetCurrentPosition() - m_enemySprite.getPosition();
            float l_module = Module(l_vec);
            if (l_module <= BERSEKER_HITING_D) {
                m_state = BERSEKER_HITING_HERO_STATE;
                m_pathComplete = false;
                m_currentWP = 1;
            } else if (l_module > BERSEKER_HITING_D && l_module <= BERSEKER_HERO_DETECTION) {
                m_state = BERSEKER_FOLLOWING_HERO_STATE;
                m_pathComplete = false;
                m_currentWP = 1;
                FindHero();
            }
        } else {
            m_state = BERSEKER_MOVING_TO_OBJ_STATE;
            m_pathComplete = false;
            m_currentWP = 1;
            FindObj();
        }
    }

    bool Berseker::CheckNearHero() {
        for (int i = 0; i < m_heroes.size(); i++) {
            sf::Vector2f l_vec = m_heroes[i]->GetCurrentPosition() - m_enemySprite.getPosition();
            float l_module = Module(l_vec);
            if (l_module <= BERSEKER_HERO_DETECTION && m_heroes[i]->GetState() != HERO_DEAD_STATE) {
                m_state = BERSEKER_FOLLOWING_HERO_STATE;
                m_heroTarget = i;
                return true;
            }
        }

        return false;
    }

    void Berseker::FindHero() {
        m_pathHero.clear();
        if (m_map.GetPath(m_enemySprite.getPosition(), m_heroes[m_heroTarget]->GetCurrentPosition(), m_pathHero)) {
            CheckPathHero();
            std::reverse(m_pathHero.begin(), m_pathHero.end());
        } else {
            m_state = BERSEKER_HITING_HERO_STATE;
        }
        DrawDebugCircles();
    }

    void Berseker::FindObj() {
        m_obj = CheckNearestObj();
        m_pathObj.clear();
        if (m_map.GetPath(m_enemySprite.getPosition(), m_objectives[m_obj].getPosition(), m_pathObj)) {
            CheckPathObj();
            std::reverse(m_pathObj.begin(), m_pathObj.end());
        }
        DrawDebugCircles();
    }

    void Berseker::CheckPathObj() {
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

    void Berseker::CheckPathHero() {
        int contador = 0;
        while (contador < m_pathHero.size()) {
            if (contador + 1 >= m_pathHero.size() || contador - 1 == 0)
                contador++;
            else {
                if ((m_pathHero[contador - 1].y == m_pathHero[contador].y) && (m_pathHero[contador + 1].x == m_pathHero[contador].x)) {
                    m_pathHero.erase(m_pathHero.begin() + contador);
                } else
                    contador++;
            }
        }
    }

    int Berseker::CheckNearestObj() {
        float d = 0;
        float minD = 100000;
        int obj = -1;
        for (int i = 0; i < m_objectives.size(); i++) {
            sf::Vector2f vec = m_objectives[i].getPosition() - m_enemySprite.getPosition();
            d = Module(vec);
            if (d < minD) {
                minD = d;
                obj = i;
            }
        }

        return obj;
    }

    void Berseker::DrawDebugCircles() {
        for (int i = 0; i < m_pathObj.size(); i++) {
            sf::CircleShape circle(3);
            circle.setOrigin(circle.getGlobalBounds().width / 2, circle.getGlobalBounds().height / 2);
            circle.setPosition(m_pathObj[i].x, m_pathObj[i].y);
            circle.setFillColor(sf::Color::Red);
            m_debugCircles.push_back(circle);
        }
    }

}

