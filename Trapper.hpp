/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Trapper.hpp
 * Author: edward
 *
 * Created on 30 de abril de 2018, 2:21
 */

#include "Enemy.hpp"
#include "Trampa.hpp"
#include "Objective.hpp"
#include "Maps.hpp"
#include "MathHelper.hpp"

namespace Zenon {

    class Trapper : public Enemy {
    public:
        Trapper(GameDataRef l_data, Enemy::TYPE l_type, sf::Vector2f l_position, Maps& l_map, const std::vector<Enemy*>& l_neighbors, const std::vector<Trampa*>& l_traps, const std::vector<Objective*>& l_objectives);
        ~Trapper();

        void Update(float dt);
        void Draw();
        void FindTrap();
        void FindCore();
        void CheckState();
        bool TheresTrap();
        int CheckNearTrap();
        void CheckPath();

    private:

        Maps& m_map;
        const std::vector<Trampa*>& m_traps;
        const std::vector<Objective*>& m_objectives;
        std::vector<sf::Vector2f> m_pathObj;
        sf::Clock m_hitingClock;
        std::vector<sf::CircleShape> m_debugCircles;
        int m_currentWP = 1;
        int m_obj = -1;
        bool m_pathCompleted = false;
        bool m_trapDestroyed = false;


    };
}

