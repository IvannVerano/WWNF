#pragma once
#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Maps.hpp"


namespace Zenon {

    class Hero {
    public:
        Hero(GameDataRef l_data, Maps &l_map, int l_id);
        virtual void Update(float dt);
        void Draw();
        virtual void OrderMovement(sf::Vector2f l_destiny);
        void Move(float dt);
        void Select();
        void CheckPath();
        bool IsSelected();
        bool IsClicked();
        int GetState();
        float GetLive();
        int GetId();
        void TakeDamage(float l_damage);
        void Deselect();
        void ResizeLife();
        void Heal(float l_heal);
        sf::FloatRect GetGB();
        sf::Vector2f GetCurrentPosition();
        bool IsRecovered();
        bool ImTargeted();
    protected:
        GameDataRef m_data;
        int m_state;
        int m_waypoint;
        int m_Id;
        float m_live = 500.0f;
        float m_initlive = m_live;
        sf::Sprite m_mainSprite;
        sf::Vector2f m_direction;
        sf::Vector2f m_destiny;
        sf::Sprite m_destinyPointer;
        sf::Sprite m_heroPlace;
        sf::Sprite m_heroArrow;
        sf::Sprite m_heroHUD;
        sf::RectangleShape m_heroHUDLife;
        sf::RectangleShape m_heroHUDred;
        std::vector<sf::Vector2f> m_path;
        std::vector<sf::Vector2f> m_backupPath;
        Maps &m_map;
        bool m_isSelected;
        bool m_pathComplete;


    };
}