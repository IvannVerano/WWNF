/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Core.hpp
 * Author: edward
 *
 * Created on 29 de abril de 2018, 18:41
 */
#include "Objective.hpp"

namespace Zenon {

    class Core : public Objective {
    public:
        Core(GameDataRef l_data, sf::Vector2f l_position, const std::vector<Enemy*>& l_nearestEnemies, Bezier& l_routePath);
        ~Core();

        void Update(float dt);
        void Draw();

    private:

    };
}

