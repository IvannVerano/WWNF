
#include <sstream>
#include "SplashState.hpp"
#include "FichaTrampa.hpp"
#include "DEFINITIONS.hpp"
#include "Trampa.hpp"
#include "Attack.hpp"
#include "HUD.hpp"
#include "Hero.hpp"
#include "Healer.hpp"
#include "Ice.hpp"
#include "Nuke.hpp"
#include "Adrenalin.hpp"
#include "Fighter.hpp"
#include "GameOverState.hpp"
#include "PlaneReturnScene.hpp"
#include <string>
#include <iostream>

namespace Zenon {

    SplashState::SplashState(GameDataRef data, std::vector<FichaTrampa*> l_fichaTrampa) : m_data(data) {
        m_trampasSel = l_fichaTrampa;
        m_disponible = m_data->data.GetMoney();
        m_themePreparation.openFromFile(PREPARE);
        m_themePreparation.setVolume(50);
        m_themePreparation.setLoop(true);
        m_themePreparation.play();
        m_themeCombat.openFromFile(COMBAT);
        m_themeCombat.setVolume(50);
        m_themeCombat.setLoop(true);
    }

    void SplashState::Init() {
        m_iluminationLayer.setTexture(m_data->assets.GetTexture("Iluminations"));
        m_filterLayer.setTexture(this->m_data->assets.GetTexture("filtro"));
        m_spawnWait = std::max(0.1f, 3.0f - (((float) 1.0f/*NIVEL DE PANICO */) / 99.0f) * 3.0f);
        std::cout << "Tienes " << m_trampasSel.size() << " trampas" << std::endl;

        m_countdownText.setFont(m_data->assets.GetFont("FUENTE_DINERO"));
        m_countdownText.setString("Prepara tus armas  " + std::to_string(m_countdown));
        m_countdownText.setPosition(820, 950);
        m_countdownText.setCharacterSize(40);

        const char * titulo = "MapicaNuevo.tmx";
        map = new Maps(m_data, titulo);

        spawn1 = sf::RectangleShape(sf::Vector2f(144, 70));
        spawn1.setOrigin(spawn1.getGlobalBounds().width / 2, spawn1.getGlobalBounds().height / 2);
        spawn1.setFillColor(sf::Color::Green);
        spawn1.setPosition(210, 860);

        spawn2 = sf::RectangleShape(sf::Vector2f(144, 70));
        spawn2.setOrigin(spawn2.getGlobalBounds().width / 2, spawn2.getGlobalBounds().height / 2);
        spawn2.setFillColor(sf::Color::Blue);
        spawn2.setPosition(210, 80);

        spawn3 = sf::RectangleShape(sf::Vector2f(70, 144));
        spawn3.setOrigin(spawn3.getGlobalBounds().width / 2, spawn3.getGlobalBounds().height / 2);
        spawn3.setFillColor(sf::Color::Red);
        spawn3.setPosition(120, 465);

        m_mouseCoordinates.setFont(this->m_data->assets.GetFont("FUENTE_DINERO"));
        m_mouseCoordinates.setString(std::to_string(sf::Mouse::getPosition(this->m_data->window).x) + ", " + std::to_string(sf::Mouse::getPosition(this->m_data->window).y));
        m_mouseCoordinates.setOrigin(m_mouseCoordinates.getGlobalBounds().width / 2, m_mouseCoordinates.getGlobalBounds().height / 2);
        m_mouseCoordinates.setPosition(sf::Mouse::getPosition(this->m_data->window).x, sf::Mouse::getPosition(this->m_data->window).y - 10);

        LoadPlacers();

        m_trampa = -1;
        m_posicion.x = m_data->window.getSize().x / 2;
        m_posicion.y = m_data->window.getSize().y / 2;

        LoadHeroes();

        m_hud = new HUD(m_data, m_trampasSel);
        m_noCompruebes = false;

        m_mouseConstruct.setTexture(m_data->assets.GetTexture("CURSOR_BUILD"));
        m_mouseConstruct.setOrigin(m_mouseConstruct.getGlobalBounds().width / 2, m_mouseConstruct.getGlobalBounds().height / 2);
        m_mouseConstruct.scale(0.7, 0.7);

        m_trapsGui.setTexture(m_data->assets.GetTexture("TrapsGui"));
        m_trapsGui.setOrigin(m_trapsGui.getGlobalBounds().width / 2, m_trapsGui.getGlobalBounds().height / 2);
        m_trapsGui.setPosition(m_data->window.getSize().x / 2, m_data->window.getSize().y / 2 + 450);
        m_trapsGui.scale(1.7, 1.0);



        LoadPaths();
        LoadAssets();


    }

    void SplashState::HandleInput() {
        sf::Event event;

        while (this->m_data->window.pollEvent(event)) {
            if (sf::Event::Closed == event.type || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                this->m_data->data.SaveChanges();
                m_themePreparation.stop();
                m_themeCombat.stop();
                this->m_data->window.close();
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (m_hud->CheckClick()) {
                    m_trampa = m_hud->GetClick();
                }

                if (m_trampa> -1 && m_trampasSel.at(m_trampa)->GetTipo() == 6) {

                    std::cout << "feo mierda" << std::endl;
                    const std::vector<Enemy*> &enes = m_enemies;
                    Trampa* tramp = new Ice(m_data, m_posicion, m_trampasSel.at(m_trampa)->GetTexturaPosicion(), enes);
                    m_trampas.push_back(tramp);

                }

                if (m_trampa> -1 && m_trampasSel.at(m_trampa)->GetTipo() == 7) {

                    sf::Vector2f m_posicion;
                    const std::vector<Enemy*> &enes = m_enemies;


                    if (m_trampasSel.at(m_trampa)->IsClicked()) {
                        std::cout << "feo mierda2" << std::endl;
                        m_posicion = (sf::Vector2f)m_data->input.GetMousePosition(m_data->window);
                        Trampa* tramp1 = new Nuke(m_data, m_posicion, m_trampasSel.at(m_trampa)->GetTexturaPosicion(), enes);
                        m_trampas.push_back(tramp1);
                    }
                }


                for (int i = 0; i < m_placer.size(); i++) {
                    if (m_placer.at(i)->Clicked(m_trampa)) {
                        if (m_trampa> -1) {
                            if (m_trampasSel.at(m_trampa)->GetTipo() == 1) {
                                if (m_trampasSel.at(m_trampa)->Afordable(m_disponible)) {
                                    const std::vector<Enemy*> &enes = m_enemies;
                                    const std::vector<Bala*> &bull = m_bullets;
                                    Trampa* tramp = new Attack(m_data, m_placer.at(i)->GetPosicion(), m_trampasSel.at(m_trampa)->GetTexturaPosicion(), enes, m_bullets);
                                    tramp->SetAttributes(m_trampas.size(), m_trampasSel[m_trampa]->GetCadencia(), m_trampasSel[m_trampa]->GetAparicion(), m_trampasSel[m_trampa]->GetPotencia(), m_trampasSel[m_trampa]->GetRango(), m_trampasSel[m_trampa]->GetRefresco(), 0, m_trampasSel[m_trampa]->GetPorcentaje(), m_trampasSel[m_trampa]->GetPrecio());
                                    m_trampas.push_back(tramp);
                                    m_disponible -= m_trampasSel.at(m_trampa)->GetPrecio();
                                } else {
                                    m_placer.at(i)->SetOcupadoFalse();
                                }
                            } else if (m_trampasSel.at(m_trampa)->GetTipo() == 3) {
                                if (m_trampasSel.at(m_trampa)->Afordable(m_disponible)) {
                                    const std::vector<Enemy*> &enes = m_enemies;
                                    const std::vector<Bala*> &bull = m_bullets;
                                    Trampa* tramp = new Flamethrower(m_data, m_placer.at(i)->GetPosicion(), m_trampasSel.at(m_trampa)->GetTexturaPosicion(), enes, m_bullets);
                                    tramp->SetAttributes(m_trampas.size(), m_trampasSel[m_trampa]->GetCadencia(), m_trampasSel[m_trampa]->GetAparicion(), m_trampasSel[m_trampa]->GetPotencia(), m_trampasSel[m_trampa]->GetRango(), m_trampasSel[m_trampa]->GetRefresco(), 0, m_trampasSel[m_trampa]->GetPorcentaje(), m_trampasSel[m_trampa]->GetPrecio());
                                    m_trampas.push_back(tramp);
                                    m_disponible -= m_trampasSel.at(m_trampa)->GetPrecio();
                                } else {
                                    m_placer.at(i)->SetOcupadoFalse();
                                }
                            } else if (m_trampasSel.at(m_trampa)->GetTipo() == 4) {
                                if (m_trampasSel.at(m_trampa)->Afordable(m_disponible)) {
                                    const std::vector<Hero*> &heros = m_heroes;
                                    Trampa* tramp = new Support(m_data, m_placer.at(i)->GetPosicion(), m_trampasSel.at(m_trampa)->GetTexturaPosicion(), heros, RANGO_SANACION);
                                    m_trampas.push_back(tramp);
                                    m_disponible -= m_trampasSel.at(m_trampa)->GetPrecio();
                                } else {
                                    m_placer.at(i)->SetOcupadoFalse();
                                }
                            } else if (m_trampasSel.at(m_trampa)->GetTipo() == 5) {
                                if (m_trampasSel.at(m_trampa)->Afordable(m_disponible)) {
                                    const std::vector<Hero*> &heros = m_heroes;
                                    Trampa* tramp = new Adrenalin(m_data, m_placer.at(i)->GetPosicion(), m_trampasSel.at(m_trampa)->GetTexturaPosicion(), heros, RANGO_ADRENALINA);
                                    m_trampas.push_back(tramp);
                                    m_disponible -= m_trampasSel.at(m_trampa)->GetPrecio();
                                } else {
                                    m_placer.at(i)->SetOcupadoFalse();
                                }
                            }
                        }
                    }
                }

                for (int i = 0; i < m_heroes.size(); i++) {
                    if (m_heroes[i]->IsClicked()) {
                        m_heroes[i]->Select();
                    } else if (m_heroes[i]->IsSelected())
                        m_heroes[i]->Deselect();
                }
            }

        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            for (int i = 0; i < m_heroes.size(); i++) {
                if (m_heroes[i]->IsSelected()) {
                    m_heroes[i]->OrderMovement((sf::Vector2f)m_data->input.GetMousePosition(m_data->window));
                }
            }

        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
            m_themePreparation.stop();
            m_themeCombat.stop();
            m_data->machine.AddState(StateRef(new PlaneReturnScene(m_data, false)));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
            m_wantsHydra = true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            m_data->data.Reset();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
            m_trampa = 0;
            m_hud->ProccessSelection(0);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
            if (m_trampasSel.size() >= 2) {
                m_trampa = 1;
                m_hud->ProccessSelection(1);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
            if (m_trampasSel.size() >= 3) {
                m_trampa = 2;
                m_hud->ProccessSelection(2);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
            if (m_trampasSel.size() >= 4) {
                m_trampa = 3;
                m_hud->ProccessSelection(3);
            }
        }



        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
            m_wantsDoxy = true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5)) {
            m_wantsChangeD = true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
            m_wantsBerseker = true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
            m_wantsTrapper = true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
            m_data->data.SetMoney(m_disponible);
            m_themePreparation.stop();
            m_themeCombat.stop();
            m_data->machine.AddState(StateRef(new PlaneReturnScene(m_data, true)));
        }
    }

    void SplashState::Update(float dt) {

        m_mouseCoordinates.setString(std::to_string(sf::Mouse::getPosition(this->m_data->window).x) + ", " + std::to_string(sf::Mouse::getPosition(this->m_data->window).y));
        m_mouseCoordinates.setOrigin(m_mouseCoordinates.getGlobalBounds().width / 2, m_mouseCoordinates.getGlobalBounds().height / 2);
        m_mouseCoordinates.setPosition(sf::Mouse::getPosition(this->m_data->window).x, sf::Mouse::getPosition(this->m_data->window).y - 20);

        if (m_wantsChangeD) {
            if (m_debugMode == true) {
                m_debugMode = false;
                m_wantsChangeD = false;
            } else {
                m_debugMode = true;
                m_wantsChangeD = false;
            }
        }

        if (!isCombatPhase) {
            if (m_preparationCountdown.getElapsedTime().asSeconds() > 1.0f) {
                m_countdown--;
                m_countdownText.setString("Prepara tu estrategia:  " + std::to_string(m_countdown));
                if (m_countdown == 0) {
                    m_themePreparation.stop();
                    m_themeCombat.play();
                    isCombatPhase = true;
                }
                m_preparationCountdown.restart();
            }
        }

        if (isCombatPhase) {
            if (m_spawnerClock.getElapsedTime().asSeconds() >= m_spawnWait) {
                CheckSpawnType(rand() % 3, rand() % 100);
                m_spawnerClock.restart();
            }
        }


        for (int i = 0; i < m_heroes.size(); i++) {
            m_heroes[i]->Update(dt);
            if (m_heroes[i]->GetState() == HERO_DEAD_STATE) {
                std::cout << "elimino al heore\n";
                m_data->data.UpdateData(m_heroes[i]->GetId(), false);
                delete m_heroes[i];
                m_heroes.erase(m_heroes.begin() + i);
            }
        }

        m_textoDinero.setString(std::to_string(m_disponible));
        int counter = 0;

        for (int i = 0; i < m_trampas.size(); i++) {
            if (m_trampas[i] != nullptr) {
                m_trampas.at(i)->Update(dt);
            }
        }

        for (int i = 0; i < m_trampas.size(); i++) {
            if (m_trampas[i] != nullptr) {
                if (m_trampas[i]->GetActualState() == TRAP_DYING_STATE && m_trampas[i]->getDyingClockTime() >= TRAP_DYING_TIME) {
                    FreePlacer(i);
                    delete m_trampas[i];
                    m_trampas[i] = nullptr;
                }
            }
        }

        /*
        for (int i = 0; i < m_objectives.size(); i++) {
            if (m_objectives[i]->GetActualState() == OBJECTIVE_DESTROYED_STATE) {
                delete m_objectives[i];
                m_objectives.erase(m_objectives.begin() + i);
            }
        }
         * */



        for (int i = 0; i < m_enemies.size(); i++) {
            if (m_enemies.at(i)->GetActualState() != ENEMY_STATE_DEAD) {
                m_enemies.at(i)->Update(dt);
            }
        }

        for (int i = 0; i < m_bullets.size(); i++) {
            m_bullets[i]->Update(dt);
        }

        this->CheckColision();

        for (int i = 0; i < m_placer.size(); i++) {
            if (m_placer.at(i)->Hovered() && !m_placer.at(i)->GetOccuped()) {
                counter++;
            }
        }

        if (counter > 0)
            m_hideCursor = true;
        else
            m_hideCursor = false;

        m_mouseConstruct.setPosition((sf::Vector2f)m_data->input.GetMousePosition(m_data->window));

        this->CheckFail();
        this->CheckDeadEnemies();

    }

    void SplashState::LoadHeroes() {
        Maps &mapref = *map;
        for (int i = 0; i < m_data->data.NumberOfHeroes(); i++) {
            if (m_data->data.IsHeroeAlive(i)) {
                const std::vector<Hero*>& l_allies = m_heroes;
                const std::vector<Enemy*>& l_enemies = m_enemies;
                Hero * c_hero;
                switch (i) {
                    case 0:
                        c_hero = new Fighter(m_data, mapref, i, l_enemies);
                        m_heroes.push_back(c_hero);
                        break;
                    case 1:
                        c_hero = new Healer(m_data, mapref, i, l_allies, l_enemies);
                        m_heroes.push_back(c_hero);
                        break;
                }
            }
        }
    }

    void SplashState::LoadPlacers() {
        m_loc_placers = map->GetPlacerLocation();
        //Creamos los placer en base a nuestro mapa de polla
        for (int x = 0; x < m_loc_placers.size(); x++) {
            Placer* plaser = new Placer(m_data, m_loc_placers.at(x));
            m_placer.push_back(plaser);
        }
    }

    void SplashState::LoadAssets() {
        const std::vector<Enemy* >& l_enemies = m_enemies;

        std::vector<Bezier>& paths = m_routes;

        //Objetivo 1
        m_obj = new Generator(m_data, sf::Vector2f(960, 60), l_enemies, paths);
        m_objectives.push_back(m_obj);

        //Objective 2
        m_obj = new Generator(m_data, sf::Vector2f(1734, 786), l_enemies, paths);
        m_objectives.push_back(m_obj);

        //Objective 3
        m_obj = new Core(m_data, sf::Vector2f(1690, 466), l_enemies, paths);
        m_objectives.push_back(m_obj);

        m_dineroButton.setTexture(this->m_data->assets.GetTexture("MoneyButton"));
        m_dineroButton.setOrigin(m_dineroButton.getGlobalBounds().width / 2, m_dineroButton.getGlobalBounds().height / 2);
        m_dineroButton.scale(0.6, 0.6);
        m_dineroButton.setPosition(1650, 990);

        m_textoDinero.setFont(m_data->assets.GetFont("FUENTE_DINERO"));
        m_textoDinero.setString(std::to_string(m_disponible));
        m_textoDinero.setCharacterSize(20);
        m_textoDinero.setOrigin(m_textoDinero.getGlobalBounds().width / 2, m_textoDinero.getGlobalBounds().height / 2);
        m_textoDinero.scale(1.5, 1.5);
        m_textoDinero.setPosition(sf::Vector2f(m_dineroButton.getPosition().x + 20, m_dineroButton.getPosition().y - 8));
    }

    void SplashState::CheckSpawnType(int spawn, int enemyTypeProbability) {
        sf::Vector2f l_spawnPosition;
        int limiteInferiorX;
        int limiteInferiorY;
        int limiteSuperiorX;
        int limiteSuperiorY;
        float x;
        float y;

        switch (spawn) {
            case 0:
                limiteInferiorX = spawn1.getPosition().x - spawn1.getGlobalBounds().width / 2;
                limiteInferiorY = spawn1.getPosition().y - spawn1.getGlobalBounds().height / 2;
                limiteSuperiorX = spawn1.getPosition().x + spawn1.getGlobalBounds().width / 2;
                limiteSuperiorY = spawn1.getPosition().y + spawn1.getGlobalBounds().height / 2;
                x = std::abs((rand() % (limiteInferiorX - limiteSuperiorX + 1)) - limiteSuperiorX);
                y = std::abs((rand() % (limiteSuperiorY - limiteInferiorY + 1)) - limiteInferiorY);
                l_spawnPosition = sf::Vector2f(x, y);

                if (enemyTypeProbability <= 65) {
                    //spawneamos Doxy
                    int formation = rand() % 3;
                    switch (formation) {
                        case 0:
                            SpawnDoxy(l_spawnPosition, 1);
                            break;
                        case 1:
                            SpawnDoxy(l_spawnPosition, 1);
                            SpawnDoxy(sf::Vector2f(l_spawnPosition.x + 60, l_spawnPosition.y), 1);
                            break;
                        case 2:
                            SpawnDoxy(sf::Vector2f(l_spawnPosition.x + 30, l_spawnPosition.y + 60), 1);
                            SpawnDoxy(l_spawnPosition, 1);
                            SpawnDoxy(sf::Vector2f(l_spawnPosition.x + 60, l_spawnPosition.y), 1);

                    }

                } else if (enemyTypeProbability > 65 && enemyTypeProbability <= 90) {
                    SpawnBerseker(l_spawnPosition, 0);

                } else if (enemyTypeProbability > 90) {
                    SpawnTrapper(l_spawnPosition);
                }

                break;

            case 1:
                limiteInferiorX = spawn2.getPosition().x - spawn2.getGlobalBounds().width / 2;
                limiteInferiorY = spawn2.getPosition().y - spawn2.getGlobalBounds().height / 2;
                limiteSuperiorX = spawn2.getPosition().x + spawn2.getGlobalBounds().width / 2;
                limiteSuperiorY = spawn2.getPosition().y + spawn2.getGlobalBounds().height / 2;
                x = std::abs((rand() % (limiteInferiorX - limiteSuperiorX + 1)) - limiteSuperiorX);
                y = std::abs((rand() % (limiteInferiorY - limiteSuperiorY + 1)) - limiteSuperiorY);
                l_spawnPosition = sf::Vector2f(x, y);

                if (enemyTypeProbability <= 65) {
                    //spawneamos Doxy
                    int formation = rand() % 3;
                    switch (formation) {
                        case 0:
                            SpawnDoxy(l_spawnPosition, 0);
                            break;
                        case 1:
                            SpawnDoxy(l_spawnPosition, 0);
                            SpawnDoxy(sf::Vector2f(l_spawnPosition.x + 60, l_spawnPosition.y), 0);
                            break;
                        case 2:
                            SpawnDoxy(sf::Vector2f(l_spawnPosition.x + 30, l_spawnPosition.y + 60), 0);
                            SpawnDoxy(l_spawnPosition, 0);
                            SpawnDoxy(sf::Vector2f(l_spawnPosition.x + 60, l_spawnPosition.y), 0);
                    }
                } else if (enemyTypeProbability > 65 && enemyTypeProbability <= 90) {
                    SpawnBerseker(l_spawnPosition, 0);
                } else if (enemyTypeProbability > 90) {
                    if (TheresTraps()) {
                        SpawnTrapper(l_spawnPosition);
                    }
                }


                break;

            case 2:
                limiteInferiorX = spawn3.getPosition().x - spawn3.getGlobalBounds().width / 2;
                limiteInferiorY = spawn3.getPosition().y - spawn3.getGlobalBounds().height / 2;
                limiteSuperiorX = spawn3.getPosition().x + spawn3.getGlobalBounds().width / 2;
                limiteSuperiorY = spawn3.getPosition().y + spawn3.getGlobalBounds().height / 2;
                x = std::abs((rand() % (limiteInferiorX - limiteSuperiorX + 1)) - limiteSuperiorX);
                y = std::abs((rand() % (limiteInferiorY - limiteSuperiorY + 1)) - limiteSuperiorY);
                l_spawnPosition = sf::Vector2f(x, y);

                if (enemyTypeProbability > 65 && enemyTypeProbability <= 90) {
                    SpawnBerseker(l_spawnPosition, 0);
                } else if (enemyTypeProbability > 90) {
                    if (TheresTraps()) {
                        SpawnTrapper(l_spawnPosition);
                    }
                }

                break;
        }
    }

    bool SplashState::TheresTraps() {
        bool there = false;
        for (int i = 0; i < m_trampas.size() && !there; i++) {
            if (m_trampas[i] != nullptr) {
                there = true;
            }
        }
        return there;
    }

    void SplashState::LoadPaths() {

        Bezier bezier1;
        bezier1.m_startPoint = sf::Vector2f(208, 129);
        bezier1.m_endPoint = sf::Vector2f(455, 466);
        bezier1.m_controlPoint1 = sf::Vector2f(bezier1.m_startPoint.x, bezier1.m_startPoint.y + 200);
        bezier1.m_controlPoint2 = sf::Vector2f(bezier1.m_endPoint.x - 200, bezier1.m_endPoint.y);
        bezier1.m_segments = 20;
        bezier1.create();
        bezier1.AddCurve(bezier1.m_endPoint, sf::Vector2f(766, 657), sf::Vector2f(bezier1.m_endPoint.x + 200, bezier1.m_endPoint.y), sf::Vector2f(776, 500), 20);
        bezier1.AddCurve(bezier1.m_bezierBody[bezier1.m_bezierBody.size() - 1], sf::Vector2f(1218, 653),
                sf::Vector2f(bezier1.m_bezierBody[bezier1.m_bezierBody.size() - 1].x + 50, bezier1.m_bezierBody[bezier1.m_bezierBody.size() - 1].y + 150),
                sf::Vector2f(bezier1.m_bezierBody[bezier1.m_bezierBody.size() - 1].x + 300, bezier1.m_bezierBody[bezier1.m_bezierBody.size() - 1].y + 150), 20);
        bezier1.AddCurve(bezier1.m_bezierBody[bezier1.m_bezierBody.size() - 1], sf::Vector2f(1690, 459),
                sf::Vector2f(bezier1.m_bezierBody[bezier1.m_bezierBody.size() - 1].x + 100, bezier1.m_bezierBody[bezier1.m_bezierBody.size() - 1].y - 100),
                sf::Vector2f(1033, 459), 22);
        bezier1.m_bezierBody[bezier1.m_bezierBody.size() - 2].x = bezier1.m_bezierBody[bezier1.m_bezierBody.size() - 1].x;
        bezier1.m_bezierBody[bezier1.m_bezierBody.size() - 2].y = bezier1.m_bezierBody[bezier1.m_bezierBody.size() - 1].y;
        bezier1.m_bPoints[29] = bezier1.m_bezierBody[29];
        bezier1.m_bPoints[59] = bezier1.m_bezierBody[59];

        Bezier bezier1br1;
        bezier1br1.probability = 30;
        bezier1br1.m_startPoint = bezier1.m_bPoints[29];
        bezier1br1.m_endPoint = sf::Vector2f(960, 70);
        bezier1br1.m_controlPoint1 = sf::Vector2f(bezier1br1.m_startPoint.x + 150, bezier1br1.m_startPoint.y - 200);
        bezier1br1.m_controlPoint2 = sf::Vector2f(bezier1br1.m_endPoint.x - 60, bezier1br1.m_endPoint.y + 400);
        bezier1br1.m_segments = 20;
        bezier1br1.create();
        bezier1br1.m_bezierBody[bezier1br1.m_bezierBody.size() - 2].x = bezier1br1.m_bezierBody[bezier1br1.m_bezierBody.size() - 1].x;
        bezier1br1.m_bezierBody[bezier1br1.m_bezierBody.size() - 2].y = bezier1br1.m_bezierBody[bezier1br1.m_bezierBody.size() - 1].y;

        bezier1.m_bRoutes.push_back(bezier1br1);

        Bezier bezier1br2;
        bezier1br2.probability = 40;
        bezier1br2.m_startPoint = bezier1.m_bPoints[59];
        bezier1br2.m_endPoint = sf::Vector2f(1731, 790);
        bezier1br2.m_controlPoint1 = sf::Vector2f(bezier1br2.m_startPoint.x + 150, bezier1br2.m_startPoint.y + 200);
        bezier1br2.m_controlPoint2 = sf::Vector2f(bezier1br2.m_endPoint.x - 250, bezier1br2.m_endPoint.y - 50);
        bezier1br2.m_segments = 20;
        bezier1br2.create();

        bezier1.m_bRoutes.push_back(bezier1br2);

        m_routes.push_back(bezier1);

        Bezier bezier2;
        bezier2.m_startPoint = sf::Vector2f(235, 806);
        bezier2.m_endPoint = sf::Vector2f(752, 477);
        bezier2.m_controlPoint1 = sf::Vector2f(bezier2.m_startPoint.x, bezier2.m_startPoint.y - 190);
        bezier2.m_controlPoint2 = sf::Vector2f(bezier2.m_endPoint.x - 100, bezier2.m_endPoint.y + 120);
        bezier2.m_segments = 15;
        bezier2.create();
        bezier2.AddCurve(bezier2.m_endPoint, sf::Vector2f(1185, 380),
                sf::Vector2f(bezier2.m_endPoint.x + 40, bezier2.m_endPoint.y - 150),
                sf::Vector2f(1185 - 50, 380 - 50), 20);
        bezier2.AddCurve(bezier2.m_bezierBody[bezier2.m_bezierBody.size() - 1], sf::Vector2f(1690, 459),
                sf::Vector2f(bezier2.m_bezierBody[bezier2.m_bezierBody.size() - 1].x + 50, bezier2.m_bezierBody[bezier2.m_bezierBody.size() - 1].y + 100),
                sf::Vector2f(1670, 440), 20);
        bezier2.m_bPoints[25] = bezier2.m_bezierBody[25];

        Bezier bezier2br1;
        bezier2br1.m_startPoint = bezier2.m_bPoints[25];
        bezier2br1.m_endPoint = sf::Vector2f(956, 87);
        bezier2br1.m_controlPoint1 = sf::Vector2f(bezier2br1.m_startPoint.x + 180, bezier2br1.m_startPoint.y - 50);
        bezier2br1.m_controlPoint2 = sf::Vector2f(bezier2br1.m_endPoint.x + 50, bezier2br1.m_endPoint.y - 50);
        bezier2br1.m_segments = 20;
        bezier2br1.probability = 40;
        bezier2br1.create();
        bezier2br1.m_bezierBody[bezier2br1.m_bezierBody.size() - 2] = bezier2br1.m_bezierBody[bezier2br1.m_bezierBody.size() - 1];

        bezier2.m_bRoutes.push_back(bezier2br1);

        m_routes.push_back(bezier2);

        for (int i = 0; i < m_routes.size(); i++) {
            for (int j = 0; j < m_routes[i].m_bezierBody.size(); j++) {
                sf::CircleShape circle;
                circle.setRadius(5.0f);
                circle.setFillColor(sf::Color::Magenta);
                circle.setOrigin(circle.getGlobalBounds().width / 2, circle.getGlobalBounds().height / 2);
                circle.setPosition(m_routes[i].m_bezierBody[j].x, m_routes[i].m_bezierBody[j].y);
                m_wps.push_back(circle);
            }

            for (int k = 0; k < m_routes[i].m_bRoutes.size(); k++) {
                for (int n = 0; n < m_routes[i].m_bRoutes[k].m_bezierBody.size(); n++) {
                    sf::CircleShape circle;
                    circle.setRadius(5.0f);
                    circle.setFillColor(sf::Color::Yellow);
                    circle.setOrigin(circle.getGlobalBounds().width / 2, circle.getGlobalBounds().height / 2);
                    circle.setPosition(m_routes[i].m_bRoutes[k].m_bezierBody[n]);
                    m_wps.push_back(circle);
                }
            }

            m_pathsVertex.push_back(ToVertex(m_routes[i].m_bezierBody));

            for (int m = 0; m < m_routes[i].m_bRoutes.size(); m++) {
                m_pathsVertex.push_back(ToVertex(m_routes[i].m_bRoutes[m].m_bezierBody));
            }

        }

    }

    void SplashState::FreePlacer(int l_trap) {
        bool stop = false;

        for (int i = 0; i < m_placer.size() && !stop; i++) {
            if (m_placer[i]->GetPosicion().x == m_trampas[l_trap]->GetPosition().x && m_placer[i]->GetPosicion().y == m_trampas[l_trap]->GetPosition().y) {
                m_placer[i]->SetOcupadoFalse();
                stop = true;
            }
        }
    }

    void SplashState::SpawnTrapper(sf::Vector2f l_position) {
        const std::vector<Trampa*>& l_traps = m_trampas;
        const std::vector<Objective*>& l_objectives = m_objectives;
        const std::vector<Enemy*>& l_enemies = m_enemies;
        Maps& l_map = *map;
        m_enemy = new Trapper(m_data, Enemy::trapper, l_position, l_map, l_enemies, l_traps, l_objectives);
        m_enemies.push_back(m_enemy);
    }

    void SplashState::SpawnDoxy(sf::Vector2f l_position, int l_path) {
        const std::vector<Enemy*>& l_neighbor = m_enemies;
        const std::vector<Bezier>& l_routes = m_routes;
        const std::vector<Objective*>& l_objectives = m_objectives;
        m_enemy = new Doxy(m_data, Enemy::doxy, l_position, l_neighbor, l_objectives, l_routes, l_path);
        m_enemies.push_back(m_enemy);
    }

    void SplashState::SpawnBerseker(sf::Vector2f l_position, int l_obj) {
        const std::vector<Enemy*>& l_neighbor = m_enemies;
        const std::vector<Hero*>& l_heroes = m_heroes;
        Maps &l_map = *map;
        m_enemy = new Berseker(m_data, Enemy::berseker, l_position, l_neighbor, l_map, m_objectives, l_heroes);
        m_enemies.push_back(m_enemy);
    }

    sf::VertexArray SplashState::ToVertex(std::vector<sf::Vector2f> l_points) {
        sf::VertexArray vertices(sf::LinesStrip, 0);

        for (std::vector<sf::Vector2f>::const_iterator a = l_points.begin(); a != l_points.end(); ++a)
            vertices.append(sf::Vertex(*a, sf::Color::White));

        return vertices;
    }

    void SplashState::Draw(float dt) {
        this->m_data->window.clear(sf::Color::Black);
        this->m_data->window.setView(this->m_data->window.getDefaultView());

        map->Draw();
        this->m_data->window.draw(this->_background);

        if (m_debugMode) {
            for (int i = 0; i < m_pathsVertex.size(); i++) {
                this->m_data->window.draw(m_pathsVertex[i]);
            }

            for (int i = 0; i < m_wps.size(); i++) {
                this->m_data->window.draw(m_wps[i]);
            }
        }

        this->m_data->window.draw(m_trapsGui);


        for (int i = 0; i < m_placer.size(); i++) {
            m_placer.at(i)->Draw();
        }

        for (int i = 0; i < m_objectives.size(); i++) {
            m_objectives[i]->Draw();
        }
        
        this->m_data->window.draw(m_iluminationLayer);

        for (int i = 0; i < m_trampas.size(); i++) {
            if (m_trampas[i] != nullptr) {
                m_trampas.at(i)->Draw();
            }
        }

        for (int i = 0; i < m_enemys.size(); i++) {
            m_enemys.at(i)->Draw();
        }



        for (int i = 0; i < m_bullets.size(); i++) {
            m_bullets[i]->Draw();
        }

        m_hud->Draw();
        for (int i = 0; i < m_heroes.size(); i++) {
            m_heroes[i]->Draw();
        }

        if (m_debugMode) {
            this->m_data->window.draw(spawn1);
            this->m_data->window.draw(spawn2);
            this->m_data->window.draw(spawn3);
        }

        for (int i = 0; i < m_enemies.size(); i++) {
            m_enemies.at(i)->Draw();
        }

        if (m_hideCursor) {
            this->m_data->window.setMouseCursorVisible(false);
            this->m_data->window.draw(m_mouseConstruct);
        } else
            this->m_data->window.setMouseCursorVisible(true);



        if (m_debugMode) {
            this->m_data->window.draw(m_mouseCoordinates);
        }

        if (!isCombatPhase)
            this->m_data->window.draw(m_countdownText);

        this->m_data->window.draw(m_dineroButton);
        this->m_data->window.draw(m_textoDinero);
        
        this->m_data->window.display();
    }

    void SplashState::CheckColision() {
        for (int i = 0; i < m_enemies.size(); i++) {
            for (int j = 0; j < m_bullets.size(); j++) {
                if (m_bullets[j]->GetType() == 1) {
                    if (abs(m_bullets[j]->GetOrigin().x - m_bullets[j]->GetSprite().getPosition().x) > RANGO_FUEGO
                            || abs(m_bullets[j]->GetOrigin().y - m_bullets[j]->GetSprite().getPosition().y) > RANGO_FUEGO) {

                        delete m_bullets[j];
                        m_bullets.erase(m_bullets.begin() + j);
                    }
                }

                if (m_enemies[i]->GetSprite().getGlobalBounds().intersects(m_bullets[j]->GetSprite().getGlobalBounds())) {
                    int killerCandidate = m_bullets[j]->WhoShooted();
                    delete m_bullets[j];
                    m_bullets.erase(m_bullets.begin() + j);
                    m_enemies[i]->TakeDamage(m_bullets[j]->GetPower());
                    if (m_enemies[i]->GetActualState() == ENEMY_STATE_DEAD) {
                        for (int w = 0; w < m_trampas.size(); w++) {
                            if (m_trampas[w] != nullptr) {
                                m_trampas[w]->DeleteTarget(m_enemies[i]->GetId());
                            }
                        }
                        m_disponible = m_trampas[killerCandidate]->CalculateRec(m_disponible);
                        delete m_enemies[i];
                        m_enemies.erase(m_enemies.begin() + i);
                    }
                }

            }
        }
        for (int j = 0; j < m_bullets.size(); j++) {
            if (m_bullets[j]->GetType() == 1) {
                if (abs(m_bullets[j]->GetOrigin().x - m_bullets[j]->GetSprite().getPosition().x) > RANGO_FUEGO
                        || abs(m_bullets[j]->GetOrigin().y - m_bullets[j]->GetSprite().getPosition().y) > RANGO_FUEGO) {

                    delete m_bullets[j];
                    m_bullets.erase(m_bullets.begin() + j);
                }
            }
        }
    }

    void SplashState::CheckFail() {
        if (m_objectives[m_objectives.size() - 1]->GetActualState() == OBJECTIVE_DESTROYED_STATE) 
        {
            m_themeCombat.stop();
            m_themePreparation.stop();
            this->m_data->machine.AddState(StateRef(new PlaneReturnScene(this->m_data, false)));
        }
    }

    void SplashState::SpawnHydra(sf::Vector2f l_position, Bezier& l_path) {

        const std::vector<Enemy*>& l_neighbor = m_enemies;
        Hydra * l_enemy = new Hydra(m_data, Enemy::hydra, l_position, l_neighbor, m_routes[1]);
        m_enemies.push_back(l_enemy);

        for (int i = 0; i < l_enemy->GetBodySize(); i++) {
            m_enemies.push_back(l_enemy->GetPart(i));
        }

    }

    void SplashState::CheckDeadEnemies() {
        for (int i = 0; i < m_enemies.size(); i++) {
            if (m_enemies[i]->GetActualState() == ENEMY_STATE_DEAD) {
                for (int w = 0; w < m_trampas.size(); w++) {
                    if (m_trampas[w] != nullptr) {
                        m_trampas[w]->DeleteTarget(m_enemies[i]->GetId());
                    }
                }
                delete m_enemies[i];
                m_enemies.erase(m_enemies.begin() + i);
            }
        }
    }
}

