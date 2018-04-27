/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   HydraSegment.cpp
 * Author: edward
 *
 * Created on 23 de abril de 2018, 18:47
 */

#include "HydraSegment.hpp"

namespace Zenon {

    HydraSegment::HydraSegment(GameDataRef l_data, Enemy::TYPE l_type, sf::Vector2f l_position, const std::vector<Enemy*>& l_neighbors, HydraSegment::PART l_part, Bezier& l_route) :
    Enemy(l_data, l_type, l_position, l_neighbors), m_route(l_route) {


        m_part = l_part;
        m_enemySprite.setTexture(this->m_data->assets.GetTexture("Hydra Sheet"));

        switch (m_part) {
            case HydraSegment::cabeza:
                m_spriteRects.push_back(sf::IntRect(9, 0, 116, 180));
                m_spriteRects.push_back(sf::IntRect(9, 180, 116, 180));
                m_spriteRects.push_back(sf::IntRect(9, 360, 116, 180));
                m_spriteRects.push_back(sf::IntRect(9, 540, 116, 180));
                m_enemySprite.setTextureRect(m_spriteRects[0]);
                m_enemySprite.setOrigin(m_enemySprite.getGlobalBounds().width / 2, m_enemySprite.getGlobalBounds().height / 2);
                m_enemySprite.scale(HYDRA_SCALE_X, HYDRA_SCALE_X);
                m_enemySprite.setPosition(l_position);
                m_enemySprite.setRotation(90);
                m_life = 30;
                break;

            case HydraSegment::cuerpo:
                m_spriteRects.push_back(sf::IntRect(144, 26, 108, 128));
                m_spriteRects.push_back(sf::IntRect(144, 206, 108, 128));
                m_spriteRects.push_back(sf::IntRect(144, 386, 108, 128));
                m_spriteRects.push_back(sf::IntRect(144, 566, 108, 128));
                m_enemySprite.setTextureRect(m_spriteRects[0]);
                m_enemySprite.setOrigin(m_enemySprite.getGlobalBounds().width / 2, m_enemySprite.getGlobalBounds().height / 2);
                m_enemySprite.scale(HYDRA_SCALE_X, HYDRA_SCALE_X);
                m_enemySprite.setPosition(l_position);
                m_enemySprite.setRotation(90);
                m_life = 12;
                break;

            case HydraSegment::cola:
                m_spriteRects.push_back(sf::IntRect(265, 32, 130, 116));
                m_spriteRects.push_back(sf::IntRect(265, 212, 130, 116));
                m_spriteRects.push_back(sf::IntRect(265, 392, 130, 116));
                m_spriteRects.push_back(sf::IntRect(265, 572, 130, 116));
                m_enemySprite.setTextureRect(m_spriteRects[0]);
                m_enemySprite.setOrigin(m_enemySprite.getGlobalBounds().width / 2, m_enemySprite.getGlobalBounds().height / 2);
                m_enemySprite.scale(HYDRA_SCALE_X, HYDRA_SCALE_X);
                m_enemySprite.setPosition(l_position);
                m_enemySprite.setRotation(90);
                m_life = 15;
                break;
        }

    }

    void HydraSegment::Update(float dt) {
        if (m_diving) {
            if (!m_pathCompleted) {
                sf::Vector2f l_vec = m_route.m_bezierBody[m_currentWP] - m_enemySprite.getPosition();
                float l_module = Module(l_vec);

                if (l_module < MINIMUM_WAYPOINT_DISTANCE) {
                    if (m_currentWP == m_route.m_bezierBody.size() - 1) {
                        m_pathCompleted = true;
                    } else {
                        m_currentWP++;
                    }
                }

                if (l_module > MINIMUM_WAYPOINT_DISTANCE) {
                    l_vec = Normalize(l_vec, l_module);
                    m_enemySprite.move(HYDRA_SPEED * dt * l_vec.x, HYDRA_SPEED * dt * l_vec.y);
                    m_enemySprite.setRotation(std::atan2(l_vec.x, l_vec.y * -1) * RAD_TO_DEG);
                }
            }
        }
    }

    void HydraSegment::Draw() {

        if (m_animationClock.getElapsedTime().asSeconds() >= HYDRA_ANIMATION_FPS) {
            m_animationIterator++;

            if (m_animationIterator > m_spriteRects.size() - 1) {
                m_animationIterator = 0;
            }

            m_enemySprite.setTextureRect(m_spriteRects[m_animationIterator]);
            m_animationClock.restart();
        }

        this->m_data->window.draw(m_enemySprite);
    }

    void HydraSegment::PutDiving() {
        m_diving = true;
    }

    sf::Sprite HydraSegment::GetSprite() {
        return m_enemySprite;
    }

    int HydraSegment::GetCurrentWP() {
        return m_currentWP;
    }

    void HydraSegment::Stop() {
        m_pathCompleted = true;
        m_diving = false;
    }

    bool HydraSegment::GetDiving() {
        return m_diving;
    }

    HydraSegment::~HydraSegment() {
    }

}