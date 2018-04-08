/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Enemy.cpp
 * Author: edward
 *
 * Created on 20 de marzo de 2018, 18:29
 */

#include "Enemy.hpp"

namespace Zenon {

    Enemy::Enemy(GameDataRef l_data, sf::Vector2f l_position, const std::vector<Enemy*>& l_neighbors, const std::vector<Bezier>& l_routes, int l_path) : m_data(l_data), m_neighbors(l_neighbors), m_routes(l_routes), m_enemyId(ID()) {

        m_path = m_routes[l_path];
        m_enemySprite.setTexture(m_data->assets.GetTexture("enemigo"));
        m_enemySprite.setOrigin(m_enemySprite.getGlobalBounds().width / 2, m_enemySprite.getGlobalBounds().height / 2);
        m_enemySprite.scale(0.5, 0.5);
        m_enemySprite.setPosition(l_position);
        m_pathCompleted = false;
        srand(time(NULL));
        m_killer = -1;
        m_life = 50;
        m_state = ENEMY_STATE_ALIVE;


    }

    void Enemy::Update(float dt) {

        if (!m_pathCompleted) {
            //SI HAY MAS DE UN ENEMIGO EN PANTALLA
            if (m_neighbors.size() > 1) {
                std::cout << "tiempo de repulsir\n";
                for (int i = 0; i < m_neighbors.size(); i++) {
                    //NO ME EVALUO A MI
                    if (m_enemyId != m_neighbors[i]->GetId()) {

                        //CALCULO LA DISTANCIA DE LOS VECINOS
                        sf::Vector2f l_neighborVec = m_neighbors[i]->GetPosition() - this->GetPosition();

                        //SACO SU MODULO PARA SABER EL VALOR DE ESA DISTANCIA
                        float l_neighborModule = Module(l_neighborVec);

                        //SI EL VECINO ESTA A LA DISTANCIA A LA QUE CONSIDERO OPORTUNA
                        //LO AÑADO A LOS VECINOS CERCANOS Y ACUMULO LOS VECTORES
                        if (l_neighborModule <= MINIMUM_NEIGHBOR_DISTANCE) {
                            m_resultantAcc.push_back(l_neighborVec);
                        }
                    }
                }

                //ACUMULO LAS RESULTANTES
                for (int i = 0; i < m_resultantAcc.size(); i++) {
                    m_resultant = m_resultant + m_resultantAcc[i];
                }

                m_resultant = InverseDir(m_resultant);
                sf::Vector2f l_waypointVec = m_path.m_bezierBody[m_currentWP] - this->GetPosition();
                sf::Vector2f l_resultantPosition = Resultant(m_resultant, l_waypointVec);
                float l_resultantPositionModule = Module(l_resultantPosition);

                if (m_path.m_bPoints.count(m_currentWP) == 1) {
                    if (l_resultantPositionModule < MINIMUM_WAYPOINT_DISTANCE) {
                        checkRoutes();
                    }
                }

                if (l_resultantPositionModule < MINIMUM_WAYPOINT_DISTANCE) {
                    if (m_currentWP == m_path.m_bezierBody.size() - 1) {
                        m_pathCompleted = true;
                    } else {
                        m_currentWP++;
                    }
                }

                if (l_resultantPositionModule > MINIMUM_WAYPOINT_DISTANCE) {
                    l_resultantPosition = Normalize(l_resultantPosition, l_resultantPositionModule);
                    m_enemySprite.move(ENEMY_SPEED * l_resultantPosition.x * dt, ENEMY_SPEED * l_resultantPosition.y * dt);
                }
                m_resultant = sf::Vector2f(0, 0);
                m_resultantAcc.clear();

            } else {
                if (m_path.m_bPoints.count(m_currentWP) == 1) {

                    sf::Vector2f l_waypointVec = m_path.m_bPoints[m_currentWP] - this->GetPosition();
                    float l_waypointDistance = Module(l_waypointVec);

                    if (l_waypointDistance < MINIMUM_WAYPOINT_DISTANCE) {
                        checkRoutes();
                    }
                }

                sf::Vector2f l_waypointVec = m_path.m_bezierBody[m_currentWP] - this->GetPosition();

                float l_waypointDistance = Module(l_waypointVec);

                //NORMALIZO DICHO VECTOR RESULTANTE
                sf::Vector2f l_normalizedDirection = NormalizeDir(m_path.m_bezierBody[m_currentWP], this->GetPosition());

                if (l_waypointDistance < MINIMUM_WAYPOINT_DISTANCE) {

                    if (m_currentWP == m_path.m_bezierBody.size() - 1) {
                        m_pathCompleted = true;
                    } else {
                        m_currentWP++;
                    }
                }

                if (l_waypointDistance > MINIMUM_WAYPOINT_DISTANCE) {
                    m_enemySprite.move(ENEMY_SPEED * l_normalizedDirection.x * dt, ENEMY_SPEED * l_normalizedDirection.y * dt);
                }
            }
        }
    }

    void Enemy::checkRoutes() {
        l_rNumber = 0;
        for (int i = 0; i < m_path.m_bRoutes.size(); i++) {
            if (m_path.m_bRoutes[i].m_startPoint.x == m_path.m_bPoints[m_currentWP].x &&
                    m_path.m_bRoutes[i].m_startPoint.y == m_path.m_bPoints[m_currentWP].y) {
                l_rNumber++;
            }
        }

        if (m_currentWP == m_path.m_bezierBody.size() - 1 && l_rNumber == 1) {
            //std::cout << "He entrao\n";
            m_path = m_path.m_bRoutes[m_path.m_bRoutes.size() - 1];
            l_rNumber = 0;
            m_currentWP = 2;
        }

        if (l_rNumber == 1) {
            int ran = rand() % 100;
            if (ran <= m_path.m_bRoutes[0].probability) {
                //std::cout << "1 bifurcacion: entro porque cumplo prob\n";
                l_rNumber = 0;
                m_path = m_path.m_bRoutes[0];
                m_currentWP = 2;
            }
        }

        if (l_rNumber == 2) {
            int ran = rand() % 100;
            if (m_path.m_bRoutes[0].probability < m_path.m_bRoutes[1].probability) {
                if (ran <= m_path.m_bRoutes[0].probability) {
                    l_rNumber = 0;
                    m_path = m_path.m_bRoutes[0];
                    m_currentWP = 2;
                    //std::cout << "2 bifurcaciones, PRIMERA menor que la SEGUNDA: entro porque cumplo prob de la MENOR\n";
                } else if (ran > m_path.m_bRoutes[0].probability && ran <= m_path.m_bRoutes[1].probability) {
                    l_rNumber = 0;
                    m_path = m_path.m_bRoutes[1];
                    m_currentWP = 2;
                    //std::cout << "2 bifurcaciones, PRIMERA menor que la SEGUNDA: entro porque cumplo prob de la MAYOR\n";
                }
            } else {
                if (ran < m_path.m_bRoutes[1].probability) {
                    l_rNumber = 0;
                    m_path = m_path.m_bRoutes[1];
                    m_currentWP = 2;
                    //std::cout << "2 bifurcaciones, SEGUNDA menor que la PRIMERA: entro porque cumplo prob de la MENOR\n";
                } else if (ran > m_path.m_bRoutes[1].probability && ran <= m_path.m_bRoutes[0].probability) {

                    l_rNumber = 0;
                    m_path = m_path.m_bRoutes[0];
                    m_currentWP = 2;
                    //std::cout << "2 bifurcaciones, SEGUNDA menor que la PRIMERA: entro porque cumplo prob de la MAYOR\n";

                }
            }
        }
    }

    int Enemy::GetNumber() {

        return l_rNumber;
    }

    sf::FloatRect Enemy::GetGB() {

        return m_enemySprite.getGlobalBounds();
    }

    Bezier Enemy::GetPath() {

        return m_path;
    }

    const int Enemy::GetId() {

        return m_enemyId;
    }

    sf::Vector2f Enemy::GetPosition() {

        return m_enemySprite.getPosition();
    }

    int Enemy::GetCurrentWP() {

        return m_currentWP;
    }

    void Enemy::Draw() {
        m_data->window.draw(m_enemySprite);
    }

    void Enemy::TakeDamage(int l_factor) {
        m_life -= l_factor;
        if (m_life < 0) {
            std::cout << "He muerto" << std::endl;
            m_state = ENEMY_STATE_DEAD;
        }
    }

    void Enemy::SetKiller(int l_killer) {
        m_killer = l_killer;
    }

    int Enemy::GetKiller() {
        return m_killer;
    }

    int Enemy::GetActualState() {
        return m_state;
    }

    const sf::Sprite &Enemy::GetSprite() const {
        return m_enemySprite;
    }


}


