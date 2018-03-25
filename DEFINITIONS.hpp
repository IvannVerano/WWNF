#pragma once

#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 1024

#define NO_TRAP_SPRITE "resources/posicionador.png"
#define SUPPORT_SPRITE "resources/seleccion4.png"
#define GUI_ELEMENTS "resources/elementosGUI.png"
#define WHITE_GUI_ELEMENTS "resources/elementosGUImej.png"
#define CURSOR_BUILD "resources/CursorBuild.png"
#define LASER_SPRITE "resources/laser.png"
#define FONT_DINERO "resources/emulogic.ttf"



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