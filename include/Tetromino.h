#ifndef TETROMINO_H
#define TETROMINO_H

#include "raylib.h"
#include "Block.h"
#include <deque>
#include <random>
#include <vector>

using namespace std;

class Tetromino
{
    private:
        vector<Block> blocks = {
            {{Vector2{4,1}, Vector2{5,1}, Vector2{6,1}}, ORANGE},        // straightBlock
            {{Vector2{5,5}, Vector2{6,5}, Vector2{5,4}, Vector2{6,4}}, YELLOW},  // boxBlock
            {{Vector2{4,1}, Vector2{5,1}, Vector2{6,1}, Vector2{6,0}}, BLUE},    // lBlock
            {{Vector2{4,1}, Vector2{5,1}, Vector2{6,1}, Vector2{5,0}}, SKYBLUE}, // tBlock
            {{Vector2{4,1}, Vector2{5,1}, Vector2{6,1}, Vector2{4,0}}, RED},     // lBlockLeft
            {{Vector2{4,1}, Vector2{5,1}, Vector2{6,1}, Vector2{6,0}}, GREEN},   // lBlockRight
            {{Vector2{4,1}, Vector2{5,1}, Vector2{5,0}, Vector2{6,0}}, PURPLE},  // sBlock
            {{Vector2{4,0}, Vector2{5,0}, Vector2{5,1}, Vector2{6,1}}, DARKBLUE} // zBlock
        };

        Block* currentBlock;

    public:
        Tetromino();
        const Block& GetCurrentBlock() const;
        void GenerateNextBlock();
        bool WouldCollide(const vector<Block>& fixedBlocks, const Vector2& offset);
        void RotateBlock();
        void MoveDown();
        void MoveRight();
        void MoveLeft();
        bool checkCollisionBottom();
        bool checkCollisionLeftRight();
        bool checkCollisionRight();
        bool checkCollisionLeft();
        bool checkCollisionPiece(const vector<Block>& fixedBlocks);
        bool checkLineFull(const vector<Block>& fixedBlocks);
        bool isOutGrid();
};

#endif