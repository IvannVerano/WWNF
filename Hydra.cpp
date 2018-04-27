/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Hydra.cpp
 * Author: edward
 *
 * Created on 23 de abril de 2018, 16:18
 */

#include "Hydra.hpp"

namespace Zenon {

    Hydra::Hydra(GameDataRef l_data, Enemy::TYPE l_type, sf::Vector2f l_position, const std::vector<Enemy*>& l_neighbors, Bezier& l_route) : Enemy(l_data, l_type, l_position, l_neighbors), m_route(l_route) {

        LoadBody();

    }

    Hydra::~Hydra() {

    }

    void Hydra::Update(float dt) {

        CheckBodySize();

        for (int i = 0; i < m_parts.size(); i++) {
            if (m_parts[i]->GetActualState() != ENEMY_STATE_DEAD) {
                m_parts[i]->Update(dt);
            }
        }

        if (!m_allLaunched) {
            CheckAllLaunched();
        }

        if (!m_allLaunched) {
            if (m_divingClock.getElapsedTime().asSeconds() >= LAUNCH_TIME) {
                if (m_parts[m_divingIterator]->GetDiving() == false && m_parts[m_divingIterator]->GetActualState() != ENEMY_STATE_DEAD) {
                    m_parts[m_divingIterator]->PutDiving();
                    m_divingIterator++;
                    m_divingClock.restart();
                }
            }
        }

    }

    void Hydra::Draw() {
        for (int i = m_parts.size() - 1; i >= 0; i--) {
            if (m_parts[i]->GetActualState() != ENEMY_STATE_DEAD) {
                m_parts[i]->Draw();
            }
        }
    }

    void Hydra::LoadBody() {
        for (int i = 0; i < m_nsegments; i++) {
            if (i == 0) {
                m_s = new HydraSegment(m_data, Enemy::segmento, m_route.m_startPoint, m_neighbors, HydraSegment::cabeza, m_route);
                m_parts.push_back(m_s);
            } else if (i == m_nsegments - 1) {
                m_s = new HydraSegment(m_data, Enemy::segmento, m_route.m_startPoint, m_neighbors, HydraSegment::cola, m_route);
                m_parts.push_back(m_s);
            } else {
                m_s = new HydraSegment(m_data, Enemy::segmento, m_route.m_startPoint, m_neighbors, HydraSegment::cuerpo, m_route);
                m_parts.push_back(m_s);
            }
        }
    }

    void Hydra::CheckAllLaunched() {
        bool temp = true;

        for (int i = 0; i < m_parts.size(); i++) {
            if (m_parts[i]->GetDiving() == false) {
                temp = false;
            }
        }

        m_allLaunched = temp;
    }

    void Hydra::CheckBodySize() {

        if (m_parts[0]->GetType() == ENEMY_STATE_DEAD) {
            this->m_state = ENEMY_STATE_DEAD;
        }

    }

    HydraSegment *Hydra::GetPart(int l_member) {
        return m_parts[l_member];
    }

    int Hydra::GetBodySize() {
        return m_parts.size();
    }
}