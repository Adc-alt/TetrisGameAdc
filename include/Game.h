#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "Tetromino.h"
#include "Block.h"
#include "Constants.h"
#include "Renderer.h"
#include <vector>

class Game {
    private:
        int score = 0;
        Tetromino tetromino;
        Renderer renderer;
        double lastTimeUpdate = 0;
        vector<Block> fixedBlocks;
        bool isrunning = true;

    public:
        Game();
        void Run();
        bool ShouldUpdate(double interval);
        bool isLineFull(int y, const vector<Block>& fixedBlocks);
        void ClearLines();
        void GameOver();
        void ResetGame();
};

#endif 