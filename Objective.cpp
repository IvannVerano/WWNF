/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Objective.cpp
 * Author: edward
 *
 * Created on 28 de abril de 2018, 19:30
 */

#include "Objective.hpp"

namespace Zenon {

    Objective::Objective(GameDataRef l_data, sf::Vector2f l_position, const std::vector<Enemy*>& l_nearestEnemies, std::vector<Bezier>& l_routePaths) : m_data(l_data), m_nearestEnemies(l_nearestEnemies), m_routePaths(l_routePaths) {
    }

    Objective::~Objective() {

    }

    void Objective::Update(float dt) {

    }

    void Objective::Draw() {
        this->m_data->window.draw(m_mainSprite);
    }

    void Objective::TakeDamage(int l_factor) {
        std::cout << "me pegan, soy el objetivo de la posicion: " << m_mainSprite.getPosition().x << ", " << m_mainSprite.getPosition().y << std::endl;
        m_life -= l_factor;
        if (m_life <= 30) {
            for (int i = 0; i < m_routePaths.size(); i++) {
                for (int j = 0; j < m_routePaths[i].m_bRoutes.size(); j++) {
                    sf::Vector2f d = m_routePaths[i].m_bRoutes[j].m_endPoint - m_mainSprite.getPosition();
                    float m = Module(d);
                    if (m <= 30) {
                        m_routePaths[i].m_bRoutes[j].SetIntransitable();
                    }
                }
            }
        }

        if (m_life <= 0) {
            m_state = OBJECTIVE_DESTROYED_STATE;

            for (int i = 0; i < m_routePaths.size(); i++) {
                for (int j = 0; j < m_routePaths[i].m_bRoutes.size(); j++) {
                    sf::Vector2f d = m_routePaths[i].m_bRoutes[j].m_bezierBody[m_routePaths[i].m_bRoutes[j].m_bezierBody.size() - 1] - m_mainSprite.getPosition();
                    float m = Module(d);
                    if (m <= 30) {
                        std::cout << "la pongo intransitable\n";
                        m_routePaths[i].m_bRoutes[j].SetIntransitable();
                    }
                }
            }

            for (int i = 0; i < m_nearestEnemies.size(); i++) {
                sf::Vector2f l_vec = m_nearestEnemies[i]->GetPosition() - m_mainSprite.getPosition();
                float l_module = Module(l_vec);
                if (l_module <= GENERATOR_DAM_AREA) {
                    m_nearestEnemies[i]->TakeDamage(500);
                }
            }
        }
    }

    int Objective::GetActualState() {
        return m_state;
    }

    int Objective::GetLife() {
        return m_life;
    }

    sf::Vector2f Objective::GetPosition() {
        return m_mainSprite.getPosition();
    }

    sf::FloatRect Objective::GetGB() {
        return m_mainSprite.getGlobalBounds();
    }

    bool Objective::Intersects(sf::FloatRect l_rect) {
        sf::FloatRect l_ownRect = sf::FloatRect(m_mainSprite.getGlobalBounds().left, m_mainSprite.getGlobalBounds().top,
                m_mainSprite.getGlobalBounds().width * m_mainSprite.getScale().x, m_mainSprite.getGlobalBounds().width * m_mainSprite.getScale().y);

        if (l_rect.intersects(l_ownRect)) {
            return true;
        } else {
            return false;
        }
    }
}

