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

    Enemy::Enemy(GameDataRef l_data, Enemy::TYPE l_type, sf::Vector2f l_position, const std::vector<Enemy*>& l_neighbors) : m_data(l_data), m_neighbors(l_neighbors), m_enemyId(ID()) {

        m_type = l_type;
        m_killer = -1;
        m_life = 50;
        m_startLife = m_life;
        m_state = ENEMY_STATE_ALIVE;

    }

    void Enemy::Update(float dt) {

    }

    sf::FloatRect Enemy::GetGB() {

        return m_enemySprite.getGlobalBounds();
    }

    const int Enemy::GetId() {

        return m_enemyId;
    }

    Enemy::TYPE Enemy::GetType() {
        return m_type;
    }

    sf::Vector2f Enemy::GetPosition() {

        return m_enemySprite.getPosition();
    }

    void Enemy::Draw() {
        m_data->window.draw(m_enemySprite);
    }

    void Enemy::TakeDamage(int l_factor) {
        m_life -= l_factor;
        this->ResizeLifeIndicator();
        if (m_life < 0) {
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
    
    void Enemy::ResizeLifeIndicator()
    {
        float newLife = ((m_life*50)/m_startLife);
        m_lifeIndicator.setSize(sf::Vector2f(newLife, 5));
    }
    


}


