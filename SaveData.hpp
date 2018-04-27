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
            bool IsTrapUnlocked(int l_trap);
            void SetUnlockTrap(bool l_value, int l_position);
            void AddMoney(int l_quantity);
            int GetMoney();
            void SetMoney(int l_quanity);
            void SetGeneralPunctuation(int l_increment);
            int GetGeneralPunctuation();
            void SetConfidenceLevel(int increment);
            int GetConfidenceLevel();
            
        private:
            std::vector<bool> m_heroesState;
            std::vector<bool> m_trapsUnlocked;
            tinyxml2::XMLDocument m_doc;
            tinyxml2::XMLElement *m_data;
            tinyxml2::XMLElement *m_heroes;
            tinyxml2::XMLElement *m_traps;
            
            
            int m_alive;
            int m_unlocked;
            int m_money = 1000;
            int m_generalPunctuation = 0;
            int m_confidenceLevel = 3;
            
            
        
    };
}