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
#include "DEFINITIONS.hpp"
#include "MathHelper.hpp"
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

        virtual void SetAttributes(int l_id, float l_cadence, float l_apptime, int l_power, int l_range, int l_refresh, int l_wait, int l_percentaje, int l_price) {
        };

        void TakeDamage(int l_factor) {
            m_life -= l_factor;
            m_ocupada = true;
            if (m_life < 0) {
                m_state = TRAP_DESTROYED;
            }
        };

        virtual int GetLife() {
            return m_life;
        }

        sf::Vector2f GetPosition() {
            std::cout << "me pides posicion\n";
            return m_mainSprite.getPosition();
        }

        virtual int GetActualState() {
            return m_state;
        }

        bool GetOcupada() {
            return m_ocupada;
        }

    protected:

        GameDataRef m_datos;
        int m_state = TRAP_STATE_PLACED;
        int m_life = 50;
        int m_charge;
        int m_animationAppearCounter;
        bool m_ocupada = false;
        sf::Sprite m_mainSprite;
        sf::Sprite m_SpriteAnimation;
        sf::Clock m_timeAppear;
        sf::Clock m_aniAppearClock;
        sf::Clock m_timeRefresh;
        std::vector<sf::IntRect> m_AnimationFramesAppear;

    };
}