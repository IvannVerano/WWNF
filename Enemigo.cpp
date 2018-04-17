#include "Enemigo.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>

namespace Zenon {

    Enemigo::Enemigo(GameDataRef l_data, sf::Vector2f l_position,
            const std::vector<Enemigo*>& l_neighbors, const std::vector<Bezier>& l_routes, int l_path) : m_data(l_data),
    m_neighbors(l_neighbors), m_routes(l_routes), m_id(ID()) {

        m_mainSprite.setTexture(m_data->assets.GetTexture("enemigo"));
        m_mainSprite.setOrigin(m_mainSprite.getGlobalBounds().width / 2, m_mainSprite.getGlobalBounds().height / 2);
        m_mainSprite.scale(0.5, 0.5);
        m_mainSprite.setPosition(l_position);
        m_position = l_position;

        m_path = m_routes[l_path];
        m_state = ENEMY_STATE_ALIVE;
        m_life = ENEMY_LIFE;
        m_killer = -1;
        m_speed = 90;
        m_slowed = false;
        srand(time(NULL));

        LoadLives();


    }

    void Enemigo::Update(float dt) {

        if (!m_pathCompleted) {
            std::cout << m_currentWP << std::endl;
            if (m_neighbors.size() > 1) {
                for (int i = 0; i < m_neighbors.size(); i++) {
                    if (m_id != m_neighbors[i]->GetID()) {

                        //CALCULO LA DISTANCIA ENTRE LOS VECINOS
                        sf::Vector2f l_neighborVec = m_neighbors[i]->GetPosition() - this->GetPosition();

                        //SACO EL MODULO
                        float l_neighborDistance = Module(l_neighborVec);

                        if (l_neighborDistance <= MINIMUM_NEIGHBOR_DISTANCE) {

                            //INVIERTO EL VECTOR RESULTANTE NEIGHBOR -> ENEMY
                            sf::Vector2f l_inverseEnemyDir = InverseDir(l_neighborVec);

                            //CALCULO EL VECTOR WP -> ENEMY
                            sf::Vector2f l_waypointVec = m_path.m_bezierBody[m_currentWP] - this->GetPosition();

                            //CALCULO EL VECTOR RESULTANTE
                            sf::Vector2f l_resultant = l_inverseEnemyDir + l_waypointVec;

                            //CALCULO EL MODULO DE LA RESULTANTE
                            float l_resultantDistance = Module(l_resultant);

                            sf::Vector2f l_resultantNormalized = Normalize(l_resultant, l_resultantDistance);

                            //COMPRUEBO LAS BIFURCACIONES
                            if (m_path.m_bPoints.count(m_currentWP) == 1) {
                                if (l_resultantDistance < MINIMUM_WAYPOINT_DISTANCE) {
                                    CheckRoutes();
                                }
                            }

                            if (l_resultantDistance < MINIMUM_WAYPOINT_DISTANCE) {
                                if (m_currentWP == m_path.m_bezierBody.size() - 1) {
                                    m_pathCompleted = true;
                                } else {
                                    m_currentWP++;
                                }
                            }

                            if (l_resultantDistance > MINIMUM_WAYPOINT_DISTANCE) {
                                //float x = LimitV(m_speed * l_resultantNormalized.x * dt);
                                //float y = LimitV(m_speed * l_resultantNormalized.y * dt);
                                m_mainSprite.move(m_speed * l_resultantNormalized.x * dt, m_speed * l_resultantNormalized.y * dt);
                            }

                        }
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

                            if (m_currentWP == m_path.m_bezierBody.size() - 1) {
                                m_pathCompleted = true;
                            } else {
                                std::cout << "Aumento WP: \n";
                                m_currentWP++;
                            }
                        }

                        if (l_waypointDistance > MINIMUM_WAYPOINT_DISTANCE) {

                            m_mainSprite.move(m_speed * l_normalizedDirection.x * dt, m_speed * l_normalizedDirection.y * dt);
                        }
                    }
                }
            } else {
                std::cout << "Solo hay uno\n";
                if (m_path.m_bPoints.count(m_currentWP) == 1) {
                    std::cout << "He llegado a un waypoint\n";
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
                    if (m_currentWP == m_path.m_bezierBody.size() - 1) {
                        m_pathCompleted = true;
                    } else {
                        m_currentWP++;
                    }
                }

                if (l_waypointDistance > MINIMUM_WAYPOINT_DISTANCE) {
                    m_mainSprite.move(m_speed * l_normalizedDirection.x * dt, m_speed * l_normalizedDirection.y * dt);
                }
            }
        }
    }

    void Enemigo::CheckRoutes() {
        m_randNumber = 0;
        for (int i = 0; i < m_path.m_bRoutes.size(); i++) {
            if (m_path.m_bRoutes[i].m_startPoint.x == m_path.m_bPoints[m_currentWP].x &&
                    m_path.m_bRoutes[i].m_startPoint.y == m_path.m_bPoints[m_currentWP].y) {
                m_randNumber++;
            }
        }

        if (m_currentWP == m_path.m_bezierBody.size() - 1 && m_randNumber == 1) {
            //std::cout << "He entrao\n";
            m_path = m_path.m_bRoutes[m_path.m_bRoutes.size() - 1];
            m_randNumber = 0;
            m_currentWP = 2;
        }

        if (m_randNumber == 1) {
            int ran = rand() % 100;
            if (ran <= m_path.m_bRoutes[0].probability) {
                //std::cout << "1 bifurcacion: entro porque cumplo prob\n";
                m_randNumber = 0;
                m_path = m_path.m_bRoutes[0];
                m_currentWP = 2;
            }
        }

        if (m_randNumber == 2) {
            int ran = rand() % 100;
            if (m_path.m_bRoutes[0].probability < m_path.m_bRoutes[1].probability) {
                if (ran <= m_path.m_bRoutes[0].probability) {
                    m_randNumber = 0;
                    m_path = m_path.m_bRoutes[0];
                    m_currentWP = 2;
                    //std::cout << "2 bifurcaciones, PRIMERA menor que la SEGUNDA: entro porque cumplo prob de la MENOR\n";
                } else if (ran > m_path.m_bRoutes[0].probability && ran <= m_path.m_bRoutes[1].probability) {
                    m_randNumber = 0;
                    m_path = m_path.m_bRoutes[1];
                    m_currentWP = 2;
                    //std::cout << "2 bifurcaciones, PRIMERA menor que la SEGUNDA: entro porque cumplo prob de la MAYOR\n";
                }
            } else {
                if (ran < m_path.m_bRoutes[1].probability) {
                    m_randNumber = 0;
                    m_path = m_path.m_bRoutes[1];
                    m_currentWP = 2;
                    //std::cout << "2 bifurcaciones, SEGUNDA menor que la PRIMERA: entro porque cumplo prob de la MENOR\n";
                } else if (ran > m_path.m_bRoutes[1].probability && ran <= m_path.m_bRoutes[0].probability) {
                    m_randNumber = 0;
                    m_path = m_path.m_bRoutes[0];
                    m_currentWP = 2;
                    //std::cout << "2 bifurcaciones, SEGUNDA menor que la PRIMERA: entro porque cumplo prob de la MAYOR\n";

                }
            }
        }
    }

    void Enemigo::Draw() {

        m_data->window.draw(m_mainSprite);
        m_data->window.draw(m_vidaDraw);
    }

    void Enemigo::LoadLives() {
        m_vidaDraw.setSize(sf::Vector2f(m_life, 10));
        m_vidaDraw.setFillColor(sf::Color::Green);
        m_vidaDraw.setOrigin(m_vidaDraw.getGlobalBounds().width / 2, m_vidaDraw.getGlobalBounds().height / 2);
        m_vidaDraw.setPosition(m_mainSprite.getGlobalBounds().left + 20, m_mainSprite.getGlobalBounds().top);
    }

    sf::Vector2f Enemigo::GetPosition() {
        return m_position;
    }

    int Enemigo::GetActualState() {
        return m_state;
    }

    void Enemigo::TakeDamage(int l_damage) {
        this->m_life -= l_damage;
        m_vidaDraw.setSize(sf::Vector2f(m_life, 10));

        if (m_life < 0) {
            m_state = ENEMY_STATE_DEAD;
        }
    }

    Enemigo::~Enemigo() {
    }

    const sf::Sprite &Enemigo::GetSprite() const {
        return m_mainSprite;
    }

    int Enemigo::GetID() {
        return m_id;
    }

    void Enemigo::SetKiller(int l_killer) {
        m_killer = l_killer;
    }

    int Enemigo::GetKiller() {
        return m_killer;
    }

    void Enemigo::SlowDown(float l_factor) {
        m_speed *= l_factor;
        m_slowed = true;
    }

    void Enemigo::NoEffect(float l_factor) {
        m_speed = m_speed / l_factor;
        m_slowed = false;
    }

    bool Enemigo::GetSlowed() {
        return m_slowed;
    }

}