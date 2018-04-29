#pragma once
#include "Hero.hpp"
#include "Enemy.hpp"
#include "MathHelper.hpp"

namespace Zenon
{
    class Fighter: public Hero
    {
    public:
        Fighter(GameDataRef l_data, Maps &l_map, int l_id, const std::vector<Enemy*>& l_enemies);
        void Update(float dt);
        void OrderMovement(sf::Vector2f l_destiny);
        void RecalculateEnemyPath();
        void CheckIfTargetIsDead();
        void SearchTarget();
    private:
        sf::Clock m_recalculateElapsed;
        sf::Clock m_attackTimer;
        int m_target;
        const std::vector<Enemy*>& m_enemies;
        
    };
}

