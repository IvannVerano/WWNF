#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "Trampa.hpp"
#include "Placer.hpp"
#include "HUD.hpp"
#include "FichaTrampa.hpp"
#include "Enemigo.hpp"
#include "Enemy.hpp"
#include "Doxy.hpp"
#include "Berseker.hpp"
#include "Bala.hpp"
#include "MathHelper.hpp"
#include "Maps.hpp"
#include "Hero.hpp"
#include <vector>

namespace Zenon {

    class SplashState : public State {
    public:
        SplashState(GameDataRef l_data, std::vector<FichaTrampa*> l_fichaTrampa, int l_dinero);

        void Init();

        void HandleInput();
        void Update(float dt);
        void Draw(float dt);

        void LoadPaths();
        void LoadAssets();
        void SpawnEnemy(sf::Vector2f l_position, int l_path);
        void SpawnDoxy(sf::Vector2f l_position, int l_path);
        void SpawnBerseker(sf::Vector2f l_position, int l_obj);

        void CheckColision();

        sf::VertexArray ToVertex(std::vector<sf::Vector2f> l_points);

    private:
        GameDataRef m_data;

        int m_trampa;
        int m_disponible;

        sf::Clock m_enemy_dead;
        sf::Texture _backgroundTexture;
        sf::Sprite _background;
        sf::Text m_textoDinero;
        sf::Sprite m_mouseConstruct;

        HUD * m_hud;
        bool m_noCompruebes;
        bool m_hideCursor;

        Enemy* m_enemy;

        std::vector<Trampa*> m_trampas;
        std::vector<Placer*> m_placer;
        std::vector<sf::Sprite> m_objectives;
        std::vector<FichaTrampa*> m_trampasSel;
        std::vector<Bezier> m_routes;
        std::vector<Enemigo*> m_enemys;
        std::vector<Enemy*> m_enemies;
        std::vector<Bala*>m_bullets;
        std::vector<sf::CircleShape> m_wps;
        std::vector<sf::VertexArray> m_pathsVertex;
        std::vector<sf::Vector2f> m_loc_placers;

        bool m_wantsDoxy = false;
        bool m_wantsBerseker = false;
        Maps* map;

        std::vector<Hero*> m_heroes;



    };
}