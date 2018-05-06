#pragma once
#include "Game.hpp"
#include "SFML/Graphics.hpp"
#include <string>


namespace Zenon
{
    class Level
    {
        public:
            Level(GameDataRef l_data, sf::Vector2f l_location, sf::Vector2f l_locationSmall, std::string l_name);
            void CreateLevelRewards();
            void SetDataRewards(int l_position);
            void SetPanicLevel(int l_position);
            void Update(float dt);
            bool CheckClick();
            void Draw();
            std::string GetLevelName();
            int GetPanicLevel();
            sf::Vector2f Getcoordinates();
        private:
            GameDataRef m_data;
            int m_civilians;
            int m_panicLevel;
            int m_money;
            int m_idTrapReward;
            int m_confidenceReward;
            std::vector<const char*> m_levels;
            sf::Sprite m_mainSprite;
            std::string m_LevelName;
            sf::Vector2f m_location;
            
            
            
    };
}
