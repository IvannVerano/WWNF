#pragma once

#include <vector>


namespace Zenon
{
    class Reward
    {
        public:
            Reward();
            void SetReward(int l_money, int l_idTrap, int l_civRescued, int l_confidence, int l_positionSaved);
            int GetMoney();
            int GetIdTrapRewarded();
            int GetCiviliansRescued();
            int GetPanicIncrease(int l_position);
            int GetConfidenceRestablish();
            void ResetpanicLevels();
        private:
            int m_moneyReward=0;
            int m_idTrapReward = -1;
            int m_civiliansRescued;
            int m_confidenceRestablished = 0;
            std::vector<int> m_panicLevelIncrease;
            
    };
}