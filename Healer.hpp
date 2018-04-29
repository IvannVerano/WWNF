#pragma once
#include "Hero.hpp"
#include "Enemy.hpp"

namespace Zenon
{
    class Healer : public Hero
    {
        public:
            Healer(GameDataRef l_data, Maps &l_map, int l_id, const std::vector<Hero*>& l_allies, const std::vector<Enemy*>& l_enemies);
            void HealHero();
            void Update(float dt);
            void OrderMovement(sf::Vector2f l_destiny);
            void RecalculateHeroLocation();
            void RecalculateEnemy();
        private:
            const std::vector<Hero*>& m_allies;
            const std::vector<Enemy*>& m_enemies;
            
            int m_healTarget = -1;
            int m_attackTarget = -1;
            
            sf::Clock m_followingHeroClock;
            sf::Clock m_healingClock;
            sf::Clock m_recalculateElapsed;
            sf::Clock m_attackTimer;
    };
}

