#define RAYMATH_IMPLEMENTATION
#include <raylib.h>
#include "Game.h"

int main() 
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tetris");
    SetTargetFPS(60);

    Game game;
    game.Run();
    CloseWindow();
    return 0;
} //