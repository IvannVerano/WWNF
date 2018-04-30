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
        void Animate();
        void SelectAnimation();
        void Draw();
    private:
        sf::Clock m_recalculateElapsed;
        sf::Clock m_attackTimer;
        sf::Clock m_aniClock;
        int m_target;
        int m_animationCounter = 0;
        int m_way = 0; //0-derecha, 1-izquierda
        const std::vector<Enemy*>& m_enemies;
        
        sf::Texture m_idleTexture;
        sf::Texture m_lateralMovementTexture;
        std::vector<sf::IntRect> m_mainAnimation;
        std::vector<sf::IntRect> m_lateralAnimation;
        
    };
}

