/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Enemy.cpp
 * Author: edward
 *
 * Created on 12 de marzo de 2018, 19:14
 */

#include "Enemy.hpp"
#include <iostream>
#include <complex>


namespace Zenon {

    Enemy::Enemy(GameDataRef l_data, sf::Vector2f l_position,
            const std::vector<Enemy*>& l_neighbors) : m_data(l_data), m_neighbors(l_neighbors), m_enemyId(ID()) {

        m_initialPosition = l_position;
        m_enemySprite.setTexture(m_data->assets.GetTexture("Enemy Texture"));
        m_enemySprite.setOrigin(m_enemySprite.getGlobalBounds().width / 2, m_enemySprite.getGlobalBounds().height / 2);
        m_enemySprite.scale(0.5f, 0.5f);
        m_enemySprite.setPosition(l_position);

    }

    void Enemy::Update(float dt) {

        if (m_go) {
            if (!m_pathCompleted) {
                if (m_currentWP == 14 && m_cambio == true) {
                    m_currentWP = 0;
                    m_path = m_pathA;
                    m_cambio = false;
                }

                if (m_neighbors.size() > 1) {
                    for (int i = 0; i < m_neighbors.size(); i++) {
                        if (m_enemyId != m_neighbors[i]->GetId()) {

                            float l_nvx = m_neighbors[i]->GetSprite().getPosition().x - m_enemySprite.getPosition().x;
                            float l_nvy = m_neighbors[i]->GetSprite().getPosition().y - m_enemySprite.getPosition().y;
                            float distance = std::sqrt(l_nvx * l_nvx + l_nvy * l_nvy);

                            if (distance <= MINIMUM_NEIGHBOR_DISTANCE) {
                                std::cout << "Uno cerca" << std::endl;
                                l_nvx *= -1;
                                l_nvy *= -1;
                                float l_vx = m_path[m_currentWP].x - m_enemySprite.getPosition().x;
                                float l_vy = m_path[m_currentWP].y - m_enemySprite.getPosition().y;
                                float l_resultanteX = l_nvx + l_vx;
                                float l_resultanteY = l_nvy + l_vy;
                                float l_waypointDistance = std::sqrt(l_resultanteX * l_resultanteX + l_resultanteY * l_resultanteY);

                                if (l_waypointDistance <= MINIMUM_WAYPOINT_DISTANCE) {
                                    if (m_currentWP == m_path.size() - 1) {
                                        std::cout << "\n";
                                        std::cout << "[GAME OVER]" << std::endl;
                                        m_go = false;
                                        m_pathCompleted = true;
                                    } else {
                                        m_currentWP++;
                                    }
                                }

                                if (l_waypointDistance > MINIMUM_WAYPOINT_DISTANCE) {
                                    l_resultanteX = l_resultanteX / l_waypointDistance;
                                    l_resultanteY = l_resultanteY / l_waypointDistance;
                                    m_enemySprite.move(ENEMY_SPEED * l_resultanteX * dt, ENEMY_SPEED * l_resultanteY * dt);
                                }

                            } else {

                                float vx = m_path[m_currentWP].x - m_enemySprite.getPosition().x;
                                float vy = m_path[m_currentWP].y - m_enemySprite.getPosition().y;
                                float len = std::sqrt(vx * vx + vy * vy);

                                if (len < MINIMUM_WAYPOINT_DISTANCE) {
                                    if (m_currentWP == m_path.size() - 1) {
                                        std::cout << "\n";
                                        std::cout << "[GAME OVER]" << std::endl;
                                        m_go = false;
                                        m_pathCompleted = true;
                                    } else {
                                        m_currentWP++;
                                    }
                                }

                                if (len > MINIMUM_WAYPOINT_DISTANCE) {
                                    vx = vx / len;
                                    vy = vy / len;
                                    m_enemySprite.move(ENEMY_SPEED * vx * dt, ENEMY_SPEED * vy * dt);
                                }
                            }
                        }
                    }
                } else {

                    float vx = m_path[m_currentWP].x - m_enemySprite.getPosition().x;
                    float vy = m_path[m_currentWP].y - m_enemySprite.getPosition().y;
                    float len = std::sqrt(vx * vx + vy * vy);

                    if (len <= MINIMUM_WAYPOINT_DISTANCE) {
                        if (m_currentWP == m_path.size() - 1) {
                            std::cout << "\n";
                            std::cout << "[GAME OVER]: Objetivo alcanzado." << std::endl;
                            m_go = false;
                            m_pathCompleted = true;
                        } else {
                            m_currentWP++;
                        }
                    }

                    if (len >= MINIMUM_WAYPOINT_DISTANCE) {
                        vx = vx / len;
                        vy = vy / len;
                        m_enemySprite.move(ENEMY_SPEED * vx * dt, ENEMY_SPEED * vy * dt);
                    }
                }
            }
        }
    }

    void Enemy::PutDiving() {

        m_go = true;
    }

    void Enemy::SetCambio() {

        m_cambio = true;
    }

    void Enemy::SetAlternative(std::vector<sf::Vector2f> l_path) {

        m_pathA = l_path;
    }

    void Enemy::Draw() {

        m_data->window.draw(m_enemySprite);
    }

    void Enemy::SetPath(std::vector<sf::Vector2f> l_path) {

        m_path = l_path;
    }

    const int Enemy::GetId() {

        return m_enemyId;
    }

    int Enemy::GetCurrentWP() {

        return m_currentWP;
    }

    int Enemy::GetPathEnd() {

        return m_path.size() - 1;
    }

    sf::Sprite & Enemy::GetSprite() {
        return m_enemySprite;

    }
}
