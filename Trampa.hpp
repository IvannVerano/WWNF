/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Trampa.hpp
 * Author: antonio
 *
 * Created on 8 de marzo de 2018, 17:29
 */

#pragma once
#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
namespace Zenon {

    class Trampa {
    public:

        Trampa(GameDataRef l_data) : m_datos(l_data) {

        }

        virtual void Update(float dt) {
        };

        virtual void Draw() {
        };

        virtual void AnimateApparition() {
        };

        virtual int CalculateRec(int l_sum) {
        };

        virtual void DeleteTarget(int l_position) {
        };
    protected:
        GameDataRef m_datos;
        sf::Sprite m_mainSprite;
        sf::Sprite m_SpriteAnimation;
        int m_state;
        sf::Clock m_timeAppear;
        int m_animationAppearCounter;
        std::vector<sf::IntRect> m_AnimationFramesAppear;
        sf::Clock m_aniAppearClock;
        int m_precio;
        int m_porcentaje;
    };
}