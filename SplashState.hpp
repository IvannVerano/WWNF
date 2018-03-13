#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include <vector>
#include "Enemy.hpp"

namespace Zenon {

    class SplashState : public State {
    public:
        SplashState(GameDataRef data);

        void Init();

        void HandleInput();
        void Update(float dt);
        void Draw(float dt);

        void LoadAssets();
        void LoadDestinies();
        void LoadPaths();
        void SpawnEnemy();

        std::vector<sf::Vector2f> CalculateBQ
        (
                const sf::Vector2f &start,
                const sf::Vector2f &end,
                const sf::Vector2f &startControl,
                const sf::Vector2f &endControl,
                const std::size_t nSegments
                );

        sf::VertexArray ToVertex(std::vector<sf::Vector2f> l_points);

    private:
        GameDataRef _data;

        sf::Clock _clock;

        std::vector<sf::Vector2f> m_pathPoints;
        std::vector<std::vector<sf::Vector2f>> m_caminos;
        std::vector<Enemy*> m_enemyVector;
        Enemy* m_enemy;

        sf::VertexArray m_pathVertex;
        sf::VertexArray m_pathVertex2;
        bool enemyDiving = false;
        bool m_cambio;
        bool m_wantsNew;

        sf::Sprite m_objective;
        sf::Sprite m_objective2;
        sf::Sprite m_spawn;
        sf::Texture _backgroundTexture;
        sf::Sprite _background;

    };
}