/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Doxy.hpp
 * Author: edward
 *
 * Created on 18 de abril de 2018, 17:58
 */

#include "Enemy.hpp"
#include "MathHelper.hpp"
#include "Objective.hpp"

namespace Zenon {

    class Doxy : public Enemy {
    public:
        Doxy(GameDataRef l_data, Enemy::TYPE l_type, sf::Vector2f l_position, const std::vector<Enemy*>& l_neighbors, const std::vector<Objective*>& l_objectives, const std::vector<Bezier>& l_routes, int l_path);
        ~Doxy();

        void Update(float dt);
        void CheckRoutes();
        void FindObj();
        void SetHiting();
        void Hit();
        int GetCurrentWP();
        Bezier GetPath();

    private:

        Bezier m_path;
        std::vector<Bezier> m_routes;
        int m_currentWP = 1;
        int l_rNumber = 0;
        bool m_pathCompleted = false;
        bool m_toFinalWP = false;

        sf::Vector2f m_resultant;
        sf::Vector2f m_finalWP;
        sf::Clock m_hitingClock;
        Objective* m_objTarget;
        const std::vector<Objective*>& m_objectives;
        std::vector<sf::Vector2f> m_resultantAcc;


    };
}



