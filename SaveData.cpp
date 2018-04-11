#include "SaveData.hpp"




namespace Zenon
{
    SaveData::SaveData()
    {
        this->LoadData();
    }
    
    void SaveData::LoadData()
    {
        m_doc.LoadFile("SaveData.xml");
        m_data = m_doc.FirstChildElement("data");

        m_heroes= m_data->FirstChildElement("hero");
        
        
        while(m_heroes)
        {
            m_heroes->QueryIntAttribute("alive",&m_alive);
            m_heroesState.push_back(m_alive);
            m_heroes = m_heroes->NextSiblingElement("hero");
        }
        
        
        for(int i= 0; i<m_heroesState.size(); i++)
        {
            std::cout<<this->IsHeroeAlive(i)<<std::endl;
        }
    }
    
    void SaveData::Reset()
    {
        for(int i = 0; i<m_heroesState.size(); i++)
        {
            m_heroesState[i] = true;
        }
        this->SaveChanges();
    }
    
    void SaveData::UpdateData(int l_hero, bool l_state)
    {
        m_heroesState[l_hero] = l_state;
    }
    
    void SaveData::SaveChanges()
    {
        tinyxml2::XMLDocument xmlDoc;
        tinyxml2::XMLNode * pData = xmlDoc.NewElement("data");
        xmlDoc.InsertFirstChild(pData);
        
        for(int i = 0;i<m_heroesState.size();i++)
        {
            tinyxml2::XMLElement * pElement = xmlDoc.NewElement("hero");
            pElement->SetAttribute("alive", (int)m_heroesState[i]);
            pData->InsertEndChild(pElement);
        }
        
        tinyxml2::XMLError eResult = xmlDoc.SaveFile("SaveData.xml");
        
    }
    
    int SaveData::NumberOfHeroes()
    {
        return m_heroesState.size();
    }
    
    bool SaveData::IsHeroeAlive(int l_hero)
    {
        return m_heroesState[l_hero];
    }
}