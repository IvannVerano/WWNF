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


namespace Zenon {

    Enemy::Enemy(GameDataRef l_data, sf::Vector2f l_position) : m_data(l_data) {

        m_initialPosition = l_position;
        m_enemySprite.setTexture(m_data->assets.GetTexture("Enemy Texture"));
        m_enemySprite.setOrigin(m_enemySprite.getGlobalBounds().width / 2, m_enemySprite.getGlobalBounds().height / 2);
        m_enemySprite.scale(0.5f, 0.5f);
        m_enemySprite.setPosition(l_position);

    }

    void Enemy::Update(float dt) {

        //m_go SIMPLEMENTE ACTIVA PARA QUE EMPIECE A MOVERSE
        //SI NO SE HA COMPLETADO EL PATH, SEGUIMOS ANDANDO
        //CUANDO LA DISTANCA <<len>> AL SIGUIENTE WAYPOINT < QUE LA QUE QUERAMOS
        //HEMOS COMPLETADO EL CAMINO HACIA ESE WAYPOINT Y PASAMOS AL SIGUIENTE

        if (m_go) {
            if (!m_pathCompleted) {
                if (m_currentWP == 14 && m_cambio == true) {
                    std::cout << "[UPDATE] : Cambio de rama bitches" << std::endl;
                    std::cout << "\n";
                    m_currentWP = 0;
                    m_path = m_pathA;
                    m_cambio = false;
                }
                float vx = m_path[m_currentWP].x - m_enemySprite.getPosition().x;
                float vy = m_path[m_currentWP].y - m_enemySprite.getPosition().y;

                float len = std::sqrt(vx * vx + vy * vy);

                if (len < 1.0f) {
                    if (m_currentWP == m_path.size() - 1) {
                        std::cout << "\n";
                        std::cout << "[GAME OVER]: Objetivo alcanzado." << std::endl;
                        m_go = false;
                        m_pathCompleted = true;

                    } else {
                        //std::cout << "[ENEMY]: Waypoint [" << m_currentWP << "] alcanzado --> a por el siguiente" << std::endl;
                        m_currentWP++;
                    }
                }

                if (len > 1.0f) {
                    vx = vx / len;
                    vy = vy / len;

                    m_enemySprite.move(ENEMY_SPEED * vx * dt, ENEMY_SPEED * vy * dt);
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

    int Enemy::GetCurrentWP() {
        return m_currentWP;
    }

    int Enemy::GetPathEnd() {
        return m_path.size() - 1;
    }
}
