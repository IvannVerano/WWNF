

#include "MainMenuState.hpp"
#include "DEFINITIONS.hpp"


namespace Zenon {

    MainMenuState::MainMenuState(GameDataRef l_data) : m_data(l_data) {
        m_data->assets.LoadTexture("TILESET", TILESET_FILEPATH);
        m_data->assets.LoadTexture("No_trampa", NO_TRAP_SPRITE);
        m_data->assets.LoadTexture("Metralleta", METRALLETA_SPRITE);
        m_data->assets.LoadTexture("Defensa", DEFENSA_SPRITE);
        m_data->assets.LoadTexture("GUI_METRALLETA", GUI_METRALLETA);
        m_data->assets.LoadTexture("GUI_METRALLETA_SEL", GUI_METRALLETA_SEL);
        m_data->assets.LoadTexture("GUI_DEFENSA", GUI_DEFENSA);
        m_data->assets.LoadTexture("GUI_DEFENSA_SEL", GUI_DEFENSA_SEL);
        m_data->assets.LoadTexture("GUI_ELEMENTS", GUI_ELEMENTS);
        m_data->assets.LoadTexture("WHITE_GUI_ELEMENTS", WHITE_GUI_ELEMENTS);
        m_data->assets.LoadTexture("CURSOR_BUILD", CURSOR_BUILD);
        m_data->assets.LoadTexture("enemigo", ENEMY_SPRITE);
        m_data->assets.LoadTexture("berseker", BERSEKER_SPRITE);
        m_data->assets.LoadTexture("bullet", LASER_SPRITE);
        m_data->assets.LoadTexture("ametralladora", AMETRALLADORA_SPRITE);
        m_data->assets.LoadTexture("GUI_AMETRALLADORA", GUI_AMETRALLADORA);
        m_data->assets.LoadTexture("GUI_AMETRALLADORA_SEL", GUI_AMETRALLADORA_SEL);
        m_data->assets.LoadFont("FUENTE_DINERO", FONT_DINERO);
        m_data->assets.LoadTexture("DESCRIPTIVE_TURRET", DESCRIPTIVE_TURRET);
        m_data->assets.LoadTexture("DESCRIPTIVE_DEFENSE", DESCRIPTIVE_DEFENSE);
        m_data->assets.LoadTexture("DESCRIPTIVE_AMETRALLADORA", DESCRIPTIVE_AMETRALLADORA);
        m_data->assets.LoadTexture("point1", POINT1);
        m_data->assets.LoadTexture("tienda", TIENDA);
        m_data->assets.LoadTexture("spawn", SPAWN);
        m_data->assets.LoadTexture("Hero", SPRITESHEET_HEROE);
        m_data->assets.LoadTexture("Hero_GUI", HERO_GUI_POS);
        m_data->assets.LoadTexture("Hero_Face1", SPRITE_HEROE_FACE1);
        m_data->assets.LoadTexture("lanzallamas", LANZALLAMAS_SPRITE);
        m_data->assets.LoadTexture("fire", FIRE_SPRITE);
        m_data->assets.LoadTexture("GUI_LANZALLAMAS", GUI_LANZALLAMAS);
        m_data->assets.LoadTexture("GUI_LANZALLAMAS_SEL", GUI_LANZALLAMAS_SEL);
        m_data->assets.LoadTexture("DESCRIPTIVE_LANZALLAMAS", DESCRIPTIVE_AMETRALLADORA);
        m_data->assets.LoadTexture("sanacion", SANACION_SPRITE);
        m_data->assets.LoadTexture("GUI_SANACION", GUI_SANACION);
        m_data->assets.LoadTexture("GUI_SANACION_SEL", GUI_SANACION_SEL);
        m_data->assets.LoadTexture("DESCRIPTIVE_SANACION", DESCRIPTIVE_SANACION);
        m_data->assets.LoadTexture("Hydra Sheet", HYDRA_SPRITE_SHEET);
        m_data->assets.LoadTexture("trapper", TRAPPER_SPRITE);
        m_data->assets.LoadTexture("WorldMap", WORLD_MAP);
        m_data->assets.LoadTexture("MapMarker", MARKER);
        m_data->assets.LoadTexture("Herosprite2", SPRITESHEET_HEROE2);
        m_data->assets.LoadTexture("GUI_AMETRALLADORA_BLOCK", GUI_AMETRALLADORA_BLOCK);
        m_data->assets.LoadTexture("GUI_METRALLETA_BLOCK", GUI_METRALLETA_BLOCK);
        m_data->assets.LoadTexture("GUI_DEFENSA_BLOCK", GUI_DEFENSA_BLOCK);
        m_data->assets.LoadTexture("GUI_SANACION_BLOCK", GUI_SANACION_BLOCK);
        m_data->assets.LoadTexture("GUI_LANZALLAMAS_BLOCK", GUI_LANZALLAMAS_BLOCK);
        m_data->assets.LoadTexture("LATERAL_MOV_FIGHTER", SPRITESHEET_LATERAL_MOV1);
        m_data->assets.LoadTexture("Adrenalina", ADRENALINA_SPRITE);
        m_data->assets.LoadTexture("GUI_ADRENALINA", GUI_ADRENALINA);
        m_data->assets.LoadTexture("GUI_ADRENALINA_SEL", GUI_ADRENALINA_SEL);
        m_data->assets.LoadTexture("DESCRIPTIVE_ADRENALINA", DESCRIPTIVE_ADRENALINA);
        m_data->assets.LoadTexture("GUI_ADRENALINA_BLOCK", GUI_ADRENALINA_BLOCK);

        m_data->assets.LoadTexture("Hielo", HIELO_SPRITE);
        m_data->assets.LoadTexture("GUI_HIELO", GUI_HIELO);
        m_data->assets.LoadTexture("GUI_HIELO_SEL", GUI_HIELO_SEL);
        m_data->assets.LoadTexture("GUI_NUKE", GUI_NUKE);
        m_data->assets.LoadTexture("GUI_NUKE_SEL", GUI_NUKE_SEL);
        m_data->assets.LoadTexture("DESCRIPTIVE_HIELO", DESCRIPTIVE_HIELO);
        m_data->assets.LoadTexture("Next", SIGUIENTE_SPRITE);

        //Compra en fase de seleccion
        m_data->assets.LoadTexture("Empty_Map", EMPTY_MAP_SPRITE);
        m_data->assets.LoadTexture("Option1", OPTION1_SPRITE);
        m_data->assets.LoadTexture("Option2", OPTION2_SPRITE);
        m_data->assets.LoadTexture("Option3", OPTION3_SPRITE);
        m_data->assets.LoadTexture("Bottom1", BOTTOM1_SPRITE);
        m_data->assets.LoadTexture("Bottom2", BOTTOM2_SPRITE);
        m_data->assets.LoadTexture("Bottom3", BOTTOM3_SPRITE);
        m_data->assets.LoadTexture("Bottom1OFF", BOTTOM1OFF_SPRITE);
        m_data->assets.LoadTexture("Bottom2OFF", BOTTOM2OFF_SPRITE);
        m_data->assets.LoadTexture("Bottom3OFF", BOTTOM3OFF_SPRITE);
    }

    void MainMenuState::Init() {
        m_PlayButton.setTexture(m_data->assets.GetTexture("GUI_DEFENSA_BLOCK"));
        m_PlayButton.setOrigin(m_PlayButton.getGlobalBounds().width / 2, m_PlayButton.getGlobalBounds().height / 2);
        m_PlayButton.setPosition(200, 200);
        m_PlayButton.scale(0.8, 0.8);
    }

    void MainMenuState::HandleInput() {
        sf::Event event;
        while (this->m_data->window.pollEvent(event)) {
            if (m_data->input.IsSpriteClicked(m_PlayButton, sf::Mouse::Left, m_data->window)) {
                this->NewGame();
            }
        }
    }

    void MainMenuState::Update(float dt) {
    }

    void MainMenuState::Draw(float dt) {
        this->m_data->window.clear(sf::Color::Black);
        m_data->window.draw(m_PlayButton);
        this->m_data->window.display();
    }

    void MainMenuState::NewGame() {
        m_data->machine.AddState(StateRef(new LevelSelectorState(this->m_data, false)));
    }
}
