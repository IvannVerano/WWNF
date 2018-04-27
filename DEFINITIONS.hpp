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
#define TILESET_FILEPATH "resources/BG_Laboratory.png"
#define HERO_GUI_POS "resources/circles.png"
#define WORLD_MAP "resources/WorldMap.jpg"
#define MARKER "resources/marcadormapa.png"



//Relojes
#define CLOCK_SELECTION 0.5f
#define TIEMPO_ESPERA 4


//Todo lo relacionado con los tiempos de aparición y estados de la trampa
#define TRAP_STATE_APPEARING 0
#define TRAP_STATE_PLACED 1
#define ATRAP_APPEARING_TIME 1.0f
#define ATRAP_MACHINEGUN_APPEARING_TIME 3.0f
#define DTRAP_APPEARING_TIME 2.0f


//Parámetros de ENEMIGO
#define ENEMY_SPRITE "resources/enemy.png"
#define ENEMY_LIFE 50
#define SPEED_ANIMATION 0.5f
#define ENEMY_STATE_ALIVE 1
#define ENEMY_STATE_DEAD 0
#define ENEMY_SPEED 100.0f
#define MINIMUM_WAYPOINT_DISTANCE 50.0f
#define MINIMUM_NEIGHBOR_DISTANCE 50.0f
#define ENEMY_REPULSION 10.0f
#define WP_FACTOR 0.9
#define ENEMY_FACTOR 0.7


//variables de la TORRETA
#define METRALLETA_SPRITE "resources/seleccion1.png"
#define GUI_METRALLETA "resources/gui_torreta.png"
#define GUI_METRALLETA_SEL "resources/gui_torreta_sel.png"
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
#define DESCRIPTIVE_AMETRALLADORA "resources/descriptor_ametralladora.png"
#define RANGO_AMETRALLADORA 200
#define CADENCIA_AMETRALLADORA 0.1f
#define POTENCIA_AMETRALLADORA 5
#define PRECIO_AMETRALLADORA 200
#define PORCENTAJE_AMETRALLADORA 20
#define REFRESCO_AMETRALLADORA 6


#define POINT1 "resources/generador.png"
#define TIENDA "resources/tienda.png"
#define SPAWN "resources/effect.png"

//variables de Hero
#define SPRITESHEET_HEROE "resources/spritesheetHeroe1.png"
#define SPRITE_HEROE_FACE1 "resources/HeroHud1.png"
#define HERO_IDLE_STATE 0
#define HERO_MOVING_STATE 1
#define HERO_DEAD_STATE 3
#define HERO_DETECT_WAYPOINT 20.0f
#define HERO_SPEED 150.0f


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


//variables del LANZALLAMAS
#define LANZALLAMAS_SPRITE "resources/lanzallamas.png"
#define FIRE_SPRITE "resources/flame.png"
#define GUI_LANZALLAMAS "resources/gui_lanzallamas.png"
#define GUI_LANZALLAMAS_SEL "resources/gui_lanzallamas_sel.png"
#define DESCRIPTIVE_LANZALLAMAS "resources/descriptor_ametralladora.png"
#define RANGO_LANZALLAMAS 150
#define CADENCIA_LANZALLAMAS 0.1f
#define POTENCIA_LANZALLAMAS 10
#define PRECIO_LANZALLAMAS 300
#define PORCENTAJE_LANZALLAMAS 27
#define REFRESCO_LANZALLAMAS 4
#define ANGULO_LANZALLAMAS 3
#define RANGO_FUEGO 150


//Variables TORRE SANACION

#define SANACION_SPRITE "resources/seleccion4.png"
#define GUI_SANACION "resources/gui_support.png"
#define GUI_SANACION_SEL "resources/gui_support_sel.png"
#define DESCRIPTIVE_SANACION "resources/descriptor_ametralladora.png"
#define RANGO_SANACION 150
#define CADENCIA_SANACION 0
#define POTENCIA_SANACION 15
#define PRECIO_SANACION 500
#define PORCENTAJE_SANACION 0
#define REFRESCO_SANACION 0
#define TIEMPO_CURA  2.0f


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