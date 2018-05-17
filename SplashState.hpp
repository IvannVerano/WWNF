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
#include "Flamethrower.hpp"
#include "Support.hpp"
#include "Hydra.hpp"
#include "Objective.hpp"
#include "Generator.hpp"
#include "Core.hpp"
#include "Trapper.hpp"
#include <vector>

namespace Zenon {

    class SplashState : public State {
    public:
        SplashState(GameDataRef l_data, std::vector<FichaTrampa*> l_fichaTrampa);

        void Init();

        void HandleInput();
        void Update(float dt);
        void Draw(float dt);

        void LoadPaths();
        void LoadAssets();
        void SpawnEnemy(sf::Vector2f l_position, int l_path);
        void SpawnDoxy(sf::Vector2f l_position, int l_path);
        void SpawnTrapper(sf::Vector2f l_position);
        void SpawnBerseker(sf::Vector2f l_position, int l_obj);
        void SpawnHydra(sf::Vector2f l_position, Bezier& l_path);
        void CheckSpawnType(int spawn, int enemyTypeProbability);
        bool TheresTraps();
        void TrapsDestroyed();
        void FreePlacer(int l_trap);
        void CheckColision();

        void CheckFail();
        void CheckDeadEnemies();

        sf::VertexArray ToVertex(std::vector<sf::Vector2f> l_points);

    private:
        GameDataRef m_data;

        int m_trampa;
        int m_disponible;
        int m_countdown = 30;

        sf::Clock m_enemy_dead;
        sf::Clock m_spawnerClock;
        sf::Texture _backgroundTexture;
        sf::Sprite _background;
        sf::Sprite m_trapsGui;
        sf::Sprite m_dineroButton;
        sf::Text m_textoDinero;
        sf::Text m_mouseCoordinates;
        sf::Text m_countdownText;
        sf::Sprite m_mouseConstruct;
        sf::Vector2f m_posicion;
        float m_spawnWait;

        HUD * m_hud;
        bool m_noCompruebes;
        bool m_hideCursor;
        bool isCombatPhase = false;
        bool m_debugMode = false;
        bool m_wantsChangeD = false;

        Enemy* m_enemy;
        Objective* m_obj;

        sf::RectangleShape spawn1;
        sf::RectangleShape spawn2;
        sf::RectangleShape spawn3;

        std::vector<Trampa*> m_trampas;
        std::vector<Placer*> m_placer;
        std::vector<Objective*> m_objectives;
        std::vector<FichaTrampa*> m_trampasSel;
        std::vector<Bezier> m_routes;
        std::vector<Enemy*> m_enemys;
        std::vector<Enemy*> m_enemies;
        std::vector<Bala*>m_bullets;
        std::vector<sf::CircleShape> m_wps;
        std::vector<sf::VertexArray> m_pathsVertex;
        std::vector<sf::Vector2f> m_loc_placers;

        sf::Clock m_preparationCountdown;

        sf::Clock doxy_frequency;
        sf::Clock berseker_frequency;
        sf::Clock trapper_frequency;

        bool m_wantsDoxy = false;
        bool m_wantsBerseker = false;
        bool m_wantsHydra = false;
        bool m_wantsTrapper = false;
        Maps* map;

        std::vector<Hero*> m_heroes;
        sf::Music m_themePreparation;
        sf::Music m_themeCombat;

    };
}