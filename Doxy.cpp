/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Doxy.cpp
 * Author: edward
 *
 * Created on 18 de abril de 2018, 17:58
 */

#include "Doxy.hpp"
#include "Enemy.hpp"

namespace Zenon {

    Doxy::Doxy(GameDataRef l_data, Enemy::TYPE l_type, sf::Vector2f l_position, const std::vector<Enemy*>& l_neighbors, const std::vector<Objective*>& l_objectives, const std::vector<Bezier>& l_routes, int l_path) :
    Enemy(l_data, l_type, l_position, l_neighbors), m_routes(l_routes), m_objectives(l_objectives) {
        m_path = m_routes[l_path];
        m_enemySprite.setTexture(m_data->assets.GetTexture("enemigo"));
        m_enemySprite.setOrigin(m_enemySprite.getGlobalBounds().width / 2, m_enemySprite.getGlobalBounds().height / 2);
        m_enemySprite.scale(0.5, 0.5);
        m_enemySprite.setPosition(l_position);
        m_pathCompleted = false;
        srand(time(NULL));
    }

    void Doxy::Update(float dt) {

        if (m_state == DOXY_HITING_STATE) {

            if (m_hitingClock.getElapsedTime().asSeconds() >= DOXY_HITING_TIME) {
                m_objTarget->TakeDamage(50);
                m_hitingClock.restart();
            }
        } else {
            if (!m_pathCompleted) {
                //SI HAY MAS DE UN ENEMIGO EN PANTALLA
                if (m_neighbors.size() > 1) {
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

                    //INVIERTO EL SENTIDO DE LA RESULTANTE DE TODA LA REPULSION CALCULADA
                    m_resultant = InverseDir(m_resultant);

                    //VECTOR POSICION - WP
                    sf::Vector2f l_waypointVec = m_path.m_bezierBody[m_currentWP] - this->GetPosition();

                    //RESULTANTE WP - VECINOS
                    sf::Vector2f l_resultantPosition = Resultant(m_resultant, l_waypointVec);

                    //MODULO DE ESTA RESULTANTE
                    float l_resultantPositionModule = Module(l_resultantPosition);

                    //COMPRUEBO LAS BIFURCACIONES
                    if (m_path.m_bPoints.count(m_currentWP) == 1) {
                        if (l_resultantPositionModule < MINIMUM_WAYPOINT_DISTANCE) {
                            CheckRoutes();
                        }
                    }

                    //SI ESTAMOS CERCA DE UN WP VEMOS SI TERMINAMOS EL PATH O SI DEBEMOS SEGUIR
                    if (l_resultantPositionModule < MINIMUM_WAYPOINT_DISTANCE) {
                        if (m_currentWP == m_path.m_bezierBody.size() - 2) {
                            m_state = DOXY_HITING_STATE;
                            FindObj();
                        } else {
                            m_currentWP++;
                        }
                    }

                    //SI NO ESTAMOS CERCA, NOS SEGUIMOS MOVIENDO
                    if (l_resultantPositionModule > MINIMUM_WAYPOINT_DISTANCE) {
                        l_resultantPosition = Normalize(l_resultantPosition, l_resultantPositionModule);
                        m_enemySprite.move(ENEMY_SPEED * l_resultantPosition.x * dt, ENEMY_SPEED * l_resultantPosition.y * dt);
                    }

                    //RESETEAMOS LAS VARIABLES USADAS PARA CALCULAR LA RESULTANTE DE LA REPULSION
                    m_resultant = sf::Vector2f(0, 0);
                    m_resultantAcc.clear();

                    //SI NO HAY ENEMIGOS CERCA, NOS MOVEMOS DE FORMA NORMAL
                } else {
                    if (m_path.m_bPoints.count(m_currentWP) == 1) {

                        sf::Vector2f l_waypointVec = m_path.m_bPoints[m_currentWP] - this->GetPosition();
                        float l_waypointDistance = Module(l_waypointVec);

                        if (l_waypointDistance < MINIMUM_WAYPOINT_DISTANCE) {
                            CheckRoutes();
                        }
                    }

                    sf::Vector2f l_waypointVec = m_path.m_bezierBody[m_currentWP] - this->GetPosition();

                    float l_waypointDistance = Module(l_waypointVec);

                    //NORMALIZO DICHO VECTOR RESULTANTE
                    sf::Vector2f l_normalizedDirection = NormalizeDir(m_path.m_bezierBody[m_currentWP], this->GetPosition());

                    if (l_waypointDistance < MINIMUM_WAYPOINT_DISTANCE) {
                        if (m_currentWP == m_path.m_bezierBody.size() - 2) {
                            m_state = DOXY_HITING_STATE;
                            FindObj();
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
    }

    void Doxy::FindObj() {
        float d = 0;
        float minD = 100000;
        int obj = -1;
        for (int i = 0; i < m_objectives.size(); i++) {
            sf::Vector2f vec = m_objectives[i]->GetPosition() - m_enemySprite.getPosition();
            d = Module(vec);
            if (d < minD) {
                minD = d;
                obj = i;
            }
        }
        m_objTarget = m_objectives[obj];
    }

    void Doxy::CheckRoutes() {
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
            if (ran <= m_path.m_bRoutes[0].probability && m_path.m_bRoutes[0].IsTransitable()) {
                //std::cout << "1 bifurcacion: entro porque cumplo prob\n";
                l_rNumber = 0;
                m_path = m_path.m_bRoutes[0];
                m_currentWP = 2;
            }
        }

        if (l_rNumber == 2) {
            int ran = rand() % 100;
            if (m_path.m_bRoutes[0].probability < m_path.m_bRoutes[1].probability) {
                if (ran <= m_path.m_bRoutes[0].probability && m_path.m_bRoutes[0].IsTransitable()) {
                    l_rNumber = 0;
                    m_path = m_path.m_bRoutes[0];
                    m_currentWP = 2;
                    //std::cout << "2 bifurcaciones, PRIMERA menor que la SEGUNDA: entro porque cumplo prob de la MENOR\n";
                } else if (ran > m_path.m_bRoutes[0].probability && ran <= m_path.m_bRoutes[1].probability && m_path.m_bRoutes[1].IsTransitable()) {
                    l_rNumber = 0;
                    m_path = m_path.m_bRoutes[1];
                    m_currentWP = 2;
                    //std::cout << "2 bifurcaciones, PRIMERA menor que la SEGUNDA: entro porque cumplo prob de la MAYOR\n";
                }
            } else {
                if (ran < m_path.m_bRoutes[1].probability && m_path.m_bRoutes[1].IsTransitable()) {
                    l_rNumber = 0;
                    m_path = m_path.m_bRoutes[1];
                    m_currentWP = 2;
                    //std::cout << "2 bifurcaciones, SEGUNDA menor que la PRIMERA: entro porque cumplo prob de la MENOR\n";
                } else if (ran > m_path.m_bRoutes[1].probability && ran <= m_path.m_bRoutes[0].probability && m_path.m_bRoutes[0].IsTransitable()) {

                    l_rNumber = 0;
                    m_path = m_path.m_bRoutes[0];
                    m_currentWP = 2;
                    //std::cout << "2 bifurcaciones, SEGUNDA menor que la PRIMERA: entro porque cumplo prob de la MAYOR\n";

                }
            }
        }
    }

    void Doxy::SetHiting() {
        m_state = DOXY_HITING_STATE;
        m_pathCompleted = true;
    }

    Bezier Doxy::GetPath() {
        return m_path;
    }

    int Doxy::GetCurrentWP() {
        return m_currentWP;
    }


}


