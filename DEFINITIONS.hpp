#pragma once

#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 1024

#define NO_TRAP_SPRITE "resources/posicionador.png"
#define SUPPORT_SPRITE "resources/seleccion4.png"
#define GUI_ELEMENTS "resources/elementosGUI.png"
#define WHITE_GUI_ELEMENTS "resources/elementosGUImej.png"
#define CURSOR_BUILD "resources/CursorBuild.png"
#define LASER_SPRITE "resources/laser.png"
#define FONT_DINERO "resources/Autobus-Bold.ttf"
#define TILESET_FILEPATH "resources/Tileset01.png"
#define HERO_GUI_POS "resources/circles.png"
#define WORLD_MAP "resources/WorldMap.jpg"
#define FOLDER "resources/Folder.png"
#define MARKER "resources/marcadormapa.png"
#define MAINMENUTHEME "resources/soundtrack/music/menu.wav"
#define PREPARE "resources/soundtrack/music/preparation.wav"
#define COMBAT "resources/soundtrack/music/combat.wav"
#define INTERFACE "resources/soundtrack/music/interface.wav"
#define GAMEOVER "resources/soundtrack/music/gameover.wav"
#define MAXIMUM_CHAR 50
#define FILTRO_SPRITE "resources/filtro.png"

//Relojes
#define CLOCK_SELECTION 0.5f
#define TIEMPO_ESPERA 4


//Todo lo relacionado con los tiempos de aparición y estados de la trampa
#define TRAP_STATE_APPEARING 0
#define TRAP_STATE_PLACED 1
#define TRAP_DESTROYED 2
#define TRAP_DYING_STATE 3
#define DEAD_POINT 100.0f
#define TRAP_DYING_TIME 2.5f
#define ATRAP_APPEARING_TIME 1.0f
#define ATRAP_MACHINEGUN_APPEARING_TIME 3.0f
#define DTRAP_APPEARING_TIME 2.0f


//Parámetros de ENEMIGO
#define ENEMY_SPRITE "resources/enemy.png"
#define ENEMY_LIFE 50
#define SPEED_ANIMATION 0.5f
#define ENEMY_STATE_ALIVE 1
#define ENEMY_STATE_DEAD 0
#define ENEMY_DYING_STATE 7
#define ENEMY_DYING_TIME 1.0f
#define ENEMY_SPEED 100.0f
#define MINIMUM_WAYPOINT_DISTANCE 50.0f
#define MINIMUM_NEIGHBOR_DISTANCE 50.0f
#define MINIMUM_OBJECTIVE_DETECTION 80.0f
#define ENEMY_REPULSION 10.0f
#define WP_FACTOR 0.9
#define ENEMY_FACTOR 0.7
#define DOXY_HITING_STATE 2
#define DOXY_HITING_TIME 1.0f
#define DOXY_ANIMATION "resources/doxyAnimation.png"
#define BERSEKER_MOVE_ANIMATION "resources/bersekerSpriteSheet.png"
#define TRAPPER_MOVE_ANIMATION "resources/trapperAnimation.png"


//variables del menu
#define BACKGROUND_MONEY "resources/BotonDinero.png"
#define TRAPs_GUI "resources/GuiBatalla.png"


//variables de la TORRETA
#define METRALLETA_SPRITE "resources/seleccion1.png"
#define GUI_METRALLETA "resources/gui_torreta.png"
#define GUI_METRALLETA_SEL "resources/gui_torreta_sel.png"
#define GUI_METRALLETA_BLOCK "resources/gui_torreta_blocked.png"
#define DESCRIPTIVE_TURRET "resources/descriptor_torreta.png"
#define RANGO_TORRETA 200
#define CADENCIA_TORRETA 0.5f
#define POTENCIA_TORRETA 15
#define PRECIO_TORRETA 100
#define PORCENTAJE_TORRETA 25
#define REFRESCO_TORRETA 0


//variable de la TORRE DEFENSIVA
#define DEFENSA_SPRITE "resources/seleccion3.png"
#define GUI_DEFENSA "resources/gui_defensa.png"
#define GUI_DEFENSA_SEL "resources/gui_defensa_sel.png"
#define GUI_DEFENSA_BLOCK "resources/gui_defensa_blocked.png"
#define DESCRIPTIVE_DEFENSE "resources/descriptor_defensa.png"
#define RANGO_TORRE_DEFENSA 200
#define PRECIO_TORRE_DEFENSA 200
#define REALENTIZA_TORRE_DEFENSA 0.8f
#define REFRESCO_TORRE_DEFENSA 0
#define POTENCIA_TORRE_DEFENSA 0
#define PORCENTAJE_TORRE_DEFENSA 0
#define CADENCIA_TORRE_DEFENSA 0


//variables de la AMETRALLADORA
#define AMETRALLADORA_SPRITE "resources/ametralladora.png"
#define GUI_AMETRALLADORA "resources/gui_ametralladora.png"
#define GUI_AMETRALLADORA_SEL "resources/gui_ametralladora_sel.png"
#define GUI_AMETRALLADORA_BLOCK "resources/gui_ametralladora_blocked.png"
#define DESCRIPTIVE_AMETRALLADORA "resources/descriptor_ametralladora.png"
#define RANGO_AMETRALLADORA 200
#define CADENCIA_AMETRALLADORA 0.1f
#define POTENCIA_AMETRALLADORA 5
#define PRECIO_AMETRALLADORA 400
#define PORCENTAJE_AMETRALLADORA 20
#define REFRESCO_AMETRALLADORA 6


#define SIGUIENTE_SPRITE "resources/next.png"
//Variables de Objective
#define POINT1 "resources/generador.png"
#define TIENDA "resources/tienda.png"
#define SPAWN "resources/effect.png"
#define OBJECTIVE_ACTIVE_STATE 0
#define OBJECTIVE_DESTROYED_STATE 1


//--- Generator ---//
#define GENERATOR_SCALEX 0.5f
#define GENERATOR_SCALEY 0.5f
#define GENERATOR_DAM_AREA 220.0f

//--- Core ---//
#define CORE_SCALEX 0.5f
#define CORE_SCALEY 0.5f

//variables de Hero
#define SPRITESHEET_HEROE "resources/spritesheetHeroe1.png"
#define HEROE_1_UP "resources/hero1upanimation.png"
#define HEROE_1_DOWN "resources/Hero1_DownAnimation.png"
#define HEROE_1_IDLE "resources/Hero1_IdleAnimation.png"
#define HEROE_2_MOVING "resources/Hero2_moving.png"
#define HEROE_2_UPDOWN "resources/Hero2_UpDown.png"
#define HEROE_2_IDLE "resources/Hero2_Idle.png"
#define HEROE_2_ATTACK "resources/Heroe2_attack.png"
#define HEROE_1_ATTACK "resources/Hero1_attack.png"
#define SPRITESHEET_HEROE2 "resources/spritesheetHeroe2.png"
#define SPRITE_HEROE_FACE1 "resources/HeroHud1.png"
#define SPRITE_HEROE_FACE2 "resources/HeroHud2.png"
#define HERO_IDLE_STATE 0
#define HERO_MOVING_STATE 1
#define HERO_DEAD_STATE 3
#define HERO_FOLLOWING_ENEMY 4
#define HERO_ATTACKING_ENEMY 5
#define HERO_FOLLOWING_HERO 6
#define HERO_HEALING 7
#define HERO_HITTINGRANGE 80.0f
#define HERO_ATTACKINGTIME 1.0f
#define HERO_LOOKTIME 2.0f
#define HERO_HITTINGDISTANCE 120.0f
#define HERO_HEALINGDISTANCE 70.0f
#define HITSCAM_DISTANCE_HEALER 200.0f
#define HERO_DETECT_WAYPOINT 20.0f
#define HERO_SPEED 180.0f
#define HERO_DETECT_ENEMY 200.0f
#define HERO_DISTANCEFOLLOWINGHERO 140.0f

//variables de FIGHTER
#define SPRITESHEET_LATERAL_MOV1 "resources/lateralmovement1.png"

//HELP STATE
#define HELPBG_SPRITE "resources/Ayuda.png"
#define RETURN_SPRITE "resources/returnButton.png"

//Variables de Berseker
#define BERSEKER_SPRITE "resources/berseker.png"
#define BERSEKER_MINIMUM_WP_D 10.0f
#define BERSEKER_SPEED 100.0f
#define BERSEKER_IDLE_STATE 2
#define BERSEKER_MOVING_TO_OBJ_STATE 3
#define BERSEKER_HERO_DETECTION 150.0f
#define BERSEKER_HITING_D 120.0f
#define BERSEKER_HITING_OBJ 4
#define BERSEKER_FOLLOWING_HERO_STATE 5
#define BERSEKER_HITING_HERO_STATE 6
#define BERSEKER_CHECKING_HERO_TIME 0.8f
#define BERSEKER_HIT_HERO_TIME 1.0f

//Variables TRAPPER
#define TRAPPER_SPRITE "resources/trapper.png"
#define TRAPPER_FOLLOWING_TRAP_STATE 2
#define TRAPPER_HITING_TRAP_STATE 3
#define TRAPPER_FOLLOWING_CORE_STATE 4
#define TRAPPER_HITING_CORE_STATE 5
#define TRAPPER_MINIMUM_WP_D 10.0f
#define TRAPPER_SPEED 40.0f
#define TRAPPER_HITING_TIME 2.5f

//variables del LANZALLAMAS
#define LANZALLAMAS_SPRITE "resources/lanzallamas.png"
#define FIRE_SPRITE "resources/flame.png"
#define GUI_LANZALLAMAS "resources/gui_lanzallamas.png"
#define GUI_LANZALLAMAS_SEL "resources/gui_lanzallamas_sel.png"
#define DESCRIPTIVE_LANZALLAMAS "resources/descriptor_lanzallamas.png"
#define RANGO_LANZALLAMAS 150
#define CADENCIA_LANZALLAMAS 0.1f
#define POTENCIA_LANZALLAMAS 10
#define PRECIO_LANZALLAMAS 300
#define PORCENTAJE_LANZALLAMAS 27
#define REFRESCO_LANZALLAMAS 4
#define ANGULO_LANZALLAMAS 3
#define RANGO_FUEGO 150
#define GUI_LANZALLAMAS_BLOCK "resources/gui_lanzallamas_blocked.png"



//Variables TORRE SANACION

#define SANACION_SPRITE "resources/seleccion4.png"
#define GUI_SANACION "resources/gui_support.png"
#define GUI_SANACION_SEL "resources/gui_support_sel.png"
#define DESCRIPTIVE_SANACION "resources/descriptor_ametralladora.png"
#define RANGO_SANACION 150
#define CADENCIA_SANACION 0
#define POTENCIA_SANACION 10
#define PRECIO_SANACION 500
#define PORCENTAJE_SANACION 0
#define REFRESCO_SANACION 0
#define TIEMPO_CURA  5
#define GUI_SANACION_BLOCK "resources/gui_support_blocked.png"


//Variables TORRE ADRENALINA

#define ADRENALINA_SPRITE "resources/seleccion5.png"
#define GUI_ADRENALINA "resources/gui_adrenalina.png"
#define GUI_ADRENALINA_SEL "resources/gui_adrenalina_sel.png"
#define GUI_ADRENALINA_BLOCK "resources/gui_adrenalina_blocked.png"
#define DESCRIPTIVE_ADRENALINA "resources/descriptor_adrenalina.png"
#define RANGO_ADRENALINA 150
#define CADENCIA_ADRENALINA 0
#define POTENCIA_ADRENALINA 10
#define PRECIO_ADRENALINA 250
#define PORCENTAJE_ADRENALINA 0
#define REFRESCO_ADRENALINA 0
#define TIEMPO_ADRENALINA  15.0f
#define EFECTO_ADRENALINA 1.4f



//variable de la TORRE HIELO
#define HIELO_SPRITE "resources/seleccion3.png"
#define GUI_HIELO "resources/gui_ice.png"
#define GUI_HIELO_SEL "resources/gui_ice_sel.png"
#define DESCRIPTIVE_HIELO "resources/descriptor_defensa.png"
#define RANGO_TORRE_HIELO 2000
#define PRECIO_TORRE_HIELO 200
#define REALENTIZA_TORRE_HIELO 0.8f
#define REFRESCO_TORRE_HIELO 0
#define POTENCIA_TORRE_HIELO 0
#define PORCENTAJE_TORRE_HIELO 0
#define CADENCIA_TORRE_HIELO 0

#define GUI_NUKE "resources/gui_nuke.png"
#define GUI_NUKE_SEL "resources/gui_nuke_sel.png"
#define RANGO_NUKE 400
#define POTENCIA_NUKE 2000

//Variables HYDRA
#define HYDRA_SPRITE_SHEET "resources/HydraSheet2.png"
#define HYDRA_SPEED 150.0f
#define HYDRA_SCALE_X 0.5f
#define HYDRA_SCALE_Y 0.5f
#define LAUNCH_TIME 0.12f
#define HYDRA_ANIMATION_FPS 0.1f

//Variables conexion a server
#define SA      struct sockaddr
#define MAXLINE 4096
#define MAXSUB  200

//Variables OPTIONS
#define EMPTY_MAP_SPRITE "resources/emptyMap.png"
#define OPTION1_SPRITE "resources/option1.png"
#define OPTION2_SPRITE "resources/option2.png"
#define OPTION3_SPRITE "resources/option3.png"
#define BOTTOM1_SPRITE "resources/bottom1.png"
#define BOTTOM2_SPRITE "resources/bottom2.png"
#define BOTTOM3_SPRITE "resources/bottom3.png"
#define BOTTOM1OFF_SPRITE "resources/bottom1OFF.png"
#define BOTTOM2OFF_SPRITE "resources/bottom2OFF.png"
#define BOTTOM3OFF_SPRITE "resources/bottom3OFF.png"


//fichero cinematica
#define PLANE "resources/Plane.png"
#define PLANE_SPEED 500.0f
#define PLANE_SPEED_RETURN 100.0f
#define BOTON_DESPLEGAR "resources/Desplegar.png"
#define CLEAN_MAP "resources/CleanMap.jpg"

//bgs
#define SELECT_BG "resources/selectBackground.png"
#define INFOBOX "resources/Infobox.png"
#define GAME_OVERBG "resources/GameOver.jpg"

//botones gameOver
#define SAVEBUTTON "resources/Guarda.png"
#define REPEATBUTTON "resources/Repite.png"

//cosas MainMenu
#define MAINMENUBACKGROUND "resources/fondo_menu.png"
#define EXITBUTTON "resources/exitButton.png"
#define HELPBUTTON "resources/helpButton.png"
#define NEWGAMEBUTTON "resources/startButton.png"
#define CHARGEGAME "resources/loadButton.png"


//Soundtrack
#define LOADOUT_THEME "resources/soundtrack/music/loadout.wav"
#define VICTORY_THEME "resources/soundtrack/music/success.wav"
#define FAILURE_THEME "resources/soundtrack/music/failure.wav"

#define DEPLOY_1 "resources/soundtrack/soundeffects/deploy1.ogg"
#define DEPLOY_2 "resources/soundtrack/soundeffects/deploy2.ogg"
#define DEPLOY_3 "resources/soundtrack/soundeffects/deploy3.ogg"
#define DEPLOY_4 "resources/soundtrack/soundeffects/deploy4.ogg"

#define VICTORY_1 "resources/soundtrack/soundeffects/victory1.ogg"
#define VICTORY_2 "resources/soundtrack/soundeffects/victory2.ogg"
#define VICTORY_3 "resources/soundtrack/soundeffects/victory3.ogg"
#define DEFEAT_1 "resources/soundtrack/soundeffects/defeat1.ogg"
#define DEFEAT_2 "resources/soundtrack/soundeffects/defeat2.ogg"
#define DEFEAT_3 "resources/soundtrack/soundeffects/defeat3.ogg"

#define SOUND_TURRET "resources/soundtrack/soundeffects/torreta.ogg"
#define SWORD_SOUND "resources/soundtrack/soundeffects/espada.ogg"

#define ILUMINATIONS "resources/iluminations.png"




