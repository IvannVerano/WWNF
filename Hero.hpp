#pragma once
#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Maps.hpp"


namespace Zenon {

    class Hero {
    public:
        Hero(GameDataRef l_data, Maps &l_map, int l_id);
        void Update(float dt);
        void Draw();
        void OrderMovement(sf::Vector2f l_destiny);
        void Move(float dt);
        void Select();
        void CheckPath();
        bool IsSelected();
        bool IsClicked();
        int GetState();
        float GetLive();
        int GetId();
        void TakeDamage(float l_damage);
        sf::FloatRect GetGB();
        sf::Vector2f GetCurrentPosition();

    private:
        GameDataRef m_data;
        int m_state;
        int m_waypoint;
        int m_Id;
        float m_live = 100.0f;
        sf::Sprite m_mainSprite;
        sf::Vector2f m_direction;
        sf::Vector2f m_destiny;
        sf::Sprite m_destinyPointer;
        sf::Sprite m_heroPlace;
        sf::Sprite m_heroArrow;
        std::vector<sf::Vector2f> m_path;
        Maps &m_map;
        bool m_isSelected;
        bool m_pathComplete;


    };
}