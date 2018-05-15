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
            void Draw();
            
            void Animate();
            void SelectAnimation();
            void SelectTexture();
            
        private:
            const std::vector<Hero*>& m_allies;
            const std::vector<Enemy*>& m_enemies;
            
            int m_healTarget = -1;
            int m_attackTarget = -1;
            int m_way = 0;
            int m_animationCounter = 0;
            
            sf::Clock m_switchAnimation;
            
            sf::Clock m_followingHeroClock;
            sf::Clock m_healingClock;
            sf::Clock m_recalculateElapsed;
            sf::Clock m_attackTimer;
            sf::Clock m_aniClock;
            
            
            sf::Texture m_lateralMovementTexture;
            sf::Texture m_upMovementTexture;
            sf::Texture m_idleTexture;
            sf::Texture m_attackingAnimationTexture;
            std::vector<sf::IntRect> m_mainAnimation;
            std::vector<sf::IntRect> m_lateralAnimation;
            std::vector<sf::IntRect> m_upAnimation;
            std::vector<sf::IntRect> m_downAnimation;
            std::vector<sf::IntRect> m_idleAnimation;
            std::vector<sf::IntRect> m_attackAnimation;
    };
}

