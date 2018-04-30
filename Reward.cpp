#include "Reward.hpp"
#include <iostream>

namespace Zenon
{
    Reward::Reward()
    {
        this->ResetpanicLevels();
    }
    
    void Reward::SetReward(int l_money, int l_idTrap, int l_civRescued, int l_confidence, int l_positionSaved)
    {
        m_moneyReward = l_money;
        m_idTrapReward = l_idTrap;
        m_civiliansRescued = l_civRescued;
        m_confidenceRestablished = l_confidence;
        for(int i=0; i<m_panicLevelIncrease.size(); i++)
        {
            if (i==l_positionSaved)
            {
                std::cout<<"La posicion: "<<i<<" sube 10"<<std::endl;
                m_panicLevelIncrease[i] += 10;
            }
            else
            {
                std::cout<<"La posicion: "<<i<<" sube 25"<<std::endl;
                m_panicLevelIncrease[i] += 25; 
            }
        }
        
    }
    
    int Reward::GetMoney()
    {
        return m_moneyReward;
    }
    
    int Reward::GetIdTrapRewarded()
    {
        return m_idTrapReward;
    }
    
    int Reward::GetPanicIncrease(int l_position)
    {
        return m_panicLevelIncrease[l_position];
    }
    
    int Reward::GetCiviliansRescued()
    {
        return m_civiliansRescued;
    }
    
    int Reward::GetConfidenceRestablish()
    {
        return m_confidenceRestablished;
    }
    
    void Reward::ResetpanicLevels()
    {
        m_panicLevelIncrease.clear();
        for(int i=0; i<5; i++)
            m_panicLevelIncrease.push_back(5);
    }
}