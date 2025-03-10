#ifndef CONSTANTS_H
#define CONSTANTS_H

// Tamaño de la celda y dimensiones del juego
const int CELL_SIZE = 30;
const int GRID_WIDTH = 10;
const int GRID_HEIGHT = 20;
const int SCREEN_WIDTH = CELL_SIZE * 20;
const int SCREEN_HEIGHT = CELL_SIZE * 22;

// Colores del juego
const Color GRID_COLOR = {100, 100, 100, 100};
const Color PANEL_COLOR = {100, 200, 255, 75};
const Color BOARD_COLOR = {20, 20, 35, 255};

// Velocidad del juego (en segundos)
const double GAME_SPEED = 0.3;  // Reducido de 1.0 a 0.2 para que caigan más rápido

const bool isrunning = true;

#endif


