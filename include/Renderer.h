#ifndef RENDERER_H
#define RENDERER_H

#include "raylib.h"
#include "Block.h"
#include "Constants.h"
#include <string>

class Renderer {
    private:
        int& score;  // Referencia al score de Game

    public:
        Renderer(int& gameScore);  // Solo declaración del constructor
        void DrawBlock(const Block& block);
        void DrawGrid();
        void DrawUI();
        void DrawBoard();
};

#endif