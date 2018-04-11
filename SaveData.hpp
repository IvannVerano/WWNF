#pragma once
#include <vector>
#include "tinyxml2.hpp"
#include <iostream>

namespace Zenon
{
    class SaveData
    {
        public:
            SaveData();
            void LoadData();
            void SaveChanges();
            void Reset();
            void UpdateData(int l_hero, bool l_state);
            int NumberOfHeroes();
            bool IsHeroeAlive(int l_hero);
            
        private:
            std::vector<bool> m_heroesState;
            tinyxml2::XMLDocument m_doc;
            tinyxml2::XMLElement *m_data;
            tinyxml2::XMLElement *m_heroes;
            int m_alive;
            
        
    };
}