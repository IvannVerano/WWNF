#include "SaveData.hpp"




namespace Zenon {

    SaveData::SaveData() {
        this->LoadData();
    }

    void SaveData::LoadData() {
        m_doc.LoadFile("SaveData.xml");
        m_data = m_doc.FirstChildElement("data");

        m_heroes = m_data->FirstChildElement("hero");


        while (m_heroes) {
            m_heroes->QueryIntAttribute("alive", &m_alive);
            m_heroesState.push_back(m_alive);
            m_heroes = m_heroes->NextSiblingElement("hero");
        }

        m_traps = m_data->FirstChildElement("trap");

        while (m_traps) {
            m_traps->QueryIntAttribute("unlocked", &m_unlocked);
            m_trapsUnlocked.push_back(m_unlocked);
            m_traps = m_traps->NextSiblingElement("trap");
        }


        for (int i = 0; i < m_heroesState.size(); i++) {
            std::cout << this->IsHeroeAlive(i) << std::endl;
        }

        for (int i = 0; i < m_trapsUnlocked.size(); i++) {
            std::cout << this->IsTrapUnlocked(i) << std::endl;
        }
    }

    void SaveData::Reset() {
        for (int i = 0; i < m_heroesState.size(); i++) {
            m_heroesState[i] = true;
        }
        for (int i = 0; i < m_trapsUnlocked.size(); i++) {
            if (i < 2)
                m_trapsUnlocked[i] = false;
            else
                m_trapsUnlocked[i] = true;
        }
        m_money = 1000;
        m_generalPunctuation = 0;
        m_confidenceLevel = 3;
        this->SaveChanges();
    }

    void SaveData::UpdateData(int l_hero, bool l_state) {
        m_heroesState[l_hero] = l_state;
    }

    void SaveData::SaveChanges() {
        tinyxml2::XMLDocument xmlDoc;
        tinyxml2::XMLNode * pData = xmlDoc.NewElement("data");
        xmlDoc.InsertFirstChild(pData);

        for (int i = 0; i < m_heroesState.size(); i++) {
            tinyxml2::XMLElement * pElement = xmlDoc.NewElement("hero");
            pElement->SetAttribute("alive", (int) m_heroesState[i]);
            pData->InsertEndChild(pElement);
        }

        for (int i = 0; i < m_trapsUnlocked.size(); i++) {
            tinyxml2::XMLElement * pElement = xmlDoc.NewElement("trap");
            pElement->SetAttribute("unlocked", (int) m_trapsUnlocked[i]);
            pData->InsertEndChild(pElement);
        }

        tinyxml2::XMLError eResult = xmlDoc.SaveFile("SaveData.xml");

    }

    int SaveData::NumberOfHeroes() {
        return m_heroesState.size();
    }

    bool SaveData::IsHeroeAlive(int l_hero) {
        return m_heroesState[l_hero];
    }

    void SaveData::SetUnlockTrap(bool l_value, int l_position) {
        std::cout << "Pongo la trampa con ID: " << l_position << " a " << l_value << std::endl;
        m_trapsUnlocked[l_position] = l_value;
        for (int i = 0; i < m_trapsUnlocked.size(); i++) {
            std::cout << "La trampa con ID: " << i << " esta unlocked a " << m_trapsUnlocked[i] << std::endl;
        }
    }

    bool SaveData::IsTrapUnlocked(int l_trap) {
        return m_trapsUnlocked[l_trap];
    }

    void SaveData::AddMoney(int l_quantity) {
        m_money += l_quantity;
    }

    int SaveData::GetMoney() {
        return m_money;
    }

    void SaveData::SetMoney(int l_quanity) {
        m_money = l_quanity;
    }

    void SaveData::SetGeneralPunctuation(int l_increment) {
        m_generalPunctuation += l_increment;
    }

    void SaveData::SetConfidenceLevel(int increment) {
        if (m_confidenceLevel < 6)
            m_confidenceLevel += increment;
    }

    int SaveData::GetConfidenceLevel() {
        return m_confidenceLevel;
    }

    int SaveData::GetGeneralPunctuation() {
        return m_generalPunctuation;
    }

}