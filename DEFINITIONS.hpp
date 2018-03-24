#pragma once

#define SCREEN_WIDTH 768
#define SCREEN_HEIGHT 1024

#define NO_TRAP_SPRITE "resources/posicionador.png"
#define METRALLETA_SPRITE "resources/seleccion1.png"
#define DEFENSA_SPRITE "resources/seleccion3.png"
#define AMETRALLADORA_SPRITE "resources/ametralladora.png"
#define SUPPORT_SPRITE "resources/seleccion4.png"
#define GUI_METRALLETA "resources/gui_torreta.png"
#define GUI_METRALLETA_SEL "resources/gui_torreta_sel.png"
#define GUI_DEFENSA "resources/gui_defensa.png"
#define GUI_DEFENSA_SEL "resources/gui_defensa_sel.png"
#define GUI_AMETRALLADORA "resources/gui_ametralladora.png"
#define GUI_AMETRALLADORA_SEL "resources/gui_ametralladora_sel.png"
#define GUI_ELEMENTS "resources/elementosGUI.png"
#define WHITE_GUI_ELEMENTS "resources/elementosGUImej.png"
#define CURSOR_BUILD "resources/CursorBuild.png"
#define ENEMY_SPRITE "resources/enemy.png"
#define LASER_SPRITE "resources/laser.png"



//Relojes
#define CLOCK_SELECTION 0.5f


//Todo lo relacionado con los tiempos de aparición y estados de la trampa
#define TRAP_STATE_APPEARING 0
#define TRAP_STATE_PLACED 1
#define ATRAP_APPEARING_TIME 1.0f
#define DTRAP_APPEARING_TIME 2.0f


//Parámetros de animacion
#define SPEED_ANIMATION 0.5f

#define ENEMY_STATE_ALIVE 1
#define ENEMY_STATE_DEAD 0




//variables de la torreta 

#define RANGO_TORRETA 200
#define CADENCIA_TORRETA 0.5f
#define POTENCIA_TORRETA 15
#define PRECIO_TORRETA 100
#define PORCENTAJE_TORRETA 25


//variables de la Ametralladora

#define RANGO_AMETRALLADORA 200
#define CADENCIA_AMETRALLADORA 0.1f
#define POTENCIA_AMETRALLADORA 5
#define PRECIO_AMETRALLADORA 200
#define PORCENTAJE_AMETRALLADORA 20