#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include <vector>
#include "Enemy.hpp"
#include "MathHelper.hpp"

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
        void SpawnEnemy(sf::Vector2f l_position, int l_path);


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

        std::vector<Bezier> m_caminos;
        std::vector<Enemy*> m_enemyVector;
        std::vector<sf::VertexArray> m_pathsVertex;

        Enemy* m_enemy;

        bool enemyDiving = false;
        bool m_cambio;
        bool m_wantsNew;

        sf::Sprite m_point1;
        sf::Sprite m_point2;
        sf::Sprite m_point3;
        sf::Sprite m_spawn;
        sf::CircleShape m_tempCircle;
        std::vector<sf::CircleShape> m_wps;
        sf::Texture _backgroundTexture;
        sf::Sprite _background;



    };
}