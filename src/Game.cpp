#include "Game.h"

Game::Game() : renderer(score) {}

void Game::Run() {
    isrunning = true;
    while (!WindowShouldClose() && isrunning) {
        BeginDrawing();
        ClearBackground(DARKBLUE);

        // Input
        if (IsKeyPressed(KEY_UP) and not tetromino.checkCollisionBottom() and not tetromino.WouldCollide(fixedBlocks, Vector2{0,0})) {
            tetromino.RotateBlock();
        }

        if (IsKeyPressed(KEY_RIGHT) and not tetromino.checkCollisionBottom() and not tetromino.checkCollisionRight() and not tetromino.WouldCollide(fixedBlocks, Vector2{1,0})) {
            tetromino.MoveRight();
        }

        if (IsKeyPressed(KEY_LEFT) and not tetromino.checkCollisionBottom() and not tetromino.checkCollisionLeft() and not tetromino.WouldCollide(fixedBlocks, Vector2{-1,0})) {
            tetromino.MoveLeft();
        }

        if (IsKeyPressed(KEY_DOWN) and not tetromino.checkCollisionBottom() and not tetromino.WouldCollide(fixedBlocks, Vector2{0,1})) {
            tetromino.MoveDown();
        }

        // Update
        if (ShouldUpdate(GAME_SPEED) and not tetromino.checkCollisionBottom() and not tetromino.WouldCollide(fixedBlocks, Vector2{0,1})) {
            tetromino.MoveDown();
        }

        if (tetromino.checkCollisionBottom() or tetromino.WouldCollide(fixedBlocks, Vector2{0,1})) {
            // Guardamos el bloque que vamos a colocar
            Block lastBlock = tetromino.GetCurrentBlock();
            fixedBlocks.push_back(lastBlock);
            
            // Comprobamos si el bloque que acabamos de colocar está fuera del grid
            bool gameOver = false;
            for (const Vector2& pos : lastBlock.positions) {
                if (pos.y < 1) {
                    gameOver = true;
                    break;
                }
            }
            
            if (gameOver) {
                isrunning = false;
                GameOver();
                return;
            }
            
            tetromino = Tetromino();
            ClearLines();
        }   

        // Draw
        renderer.DrawBoard();
        // Dibujar primero las piezas fijas
        for (const Block& block : fixedBlocks) {
            renderer.DrawBlock(block);
        }
        // Luego dibujar la pieza actual
        renderer.DrawBlock(tetromino.GetCurrentBlock());
        renderer.DrawGrid();
        renderer.DrawUI();

        EndDrawing();
    }
}

bool Game::ShouldUpdate(double interval) {
    double currentTime = GetTime();
    if (currentTime - lastTimeUpdate >= interval) {
        lastTimeUpdate = currentTime;
        return true;
    }
    return false;
}

bool Game::isLineFull(int y, const vector<Block>& fixedBlocks) {
    vector<bool> line(GRID_WIDTH, false);
    
    for (const Block& block : fixedBlocks) {
        for (const Vector2& pos : block.positions) {
            if (pos.y == y && pos.x >= 1 && pos.x <= GRID_WIDTH) {
                line[pos.x - 1] = true;
            }
        }
    }
    
    for (bool occupied : line) {
        if (!occupied) return false;
    }
    return true;
}

void Game::ResetGame() {
    score = 0;
    fixedBlocks.clear();
    tetromino = Tetromino();
    lastTimeUpdate = GetTime();
    isrunning = true;
}

void Game::GameOver() {
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DARKBLUE);

        const char* GameOverText = "GAME OVER";
        float fontSize = 60;
        float textWidth = MeasureText(GameOverText, fontSize);
        float textX = (SCREEN_WIDTH - textWidth) / 2;
        float textY = SCREEN_HEIGHT / 2 - fontSize;
        
        DrawText(GameOverText, textX, textY, fontSize, RED);

        char scoreText[32];
        sprintf(scoreText, "Score: %d", score);
        float scoreFontSize = 40;
        float scoreWidth = MeasureText(scoreText, scoreFontSize);
        float scoreX = (SCREEN_WIDTH - scoreWidth) / 2;
        float scoreY = SCREEN_HEIGHT / 2 + 20;  

        DrawText(scoreText, scoreX, scoreY, scoreFontSize, WHITE);

        const char* exitText = "Press ESC to exit";
        float exitFontSize = 20;
        float exitWidth = MeasureText(exitText, exitFontSize);
        float exitX = (SCREEN_WIDTH - exitWidth) / 2;
        float exitY = SCREEN_HEIGHT / 2 + 100;
        DrawText(exitText, exitX, exitY, exitFontSize, GRAY);

        const char* restartText = "Press Enter to play again";
        float restartFontSize = 20;
        float restartWidth = MeasureText(restartText, restartFontSize);
        float restartX = (SCREEN_WIDTH - restartWidth) / 2;
        float restartY = SCREEN_HEIGHT / 2 + 130;
        DrawText(restartText, restartX, restartY, restartFontSize, GRAY);

        EndDrawing();

        if (IsKeyPressed(KEY_ESCAPE)) {
            break;
        }
        if (IsKeyPressed(KEY_ENTER)) {
            ResetGame();
            Run();
        }
    }
}

void Game::ClearLines() {
    int linesCleared = 0;
    
    for (int y = GRID_HEIGHT - 1; y >= 0; y--) {
        if (isLineFull(y, fixedBlocks)) {
            linesCleared++;
            
            for (auto it = fixedBlocks.begin(); it != fixedBlocks.end();) {
                bool blockModified = false;
                auto positions = it->positions;
                
                for (auto posIt = positions.begin(); posIt != positions.end();) {
                    if (posIt->y == y) {
                        posIt = positions.erase(posIt);
                        blockModified = true;
                    } else {
                        ++posIt;
                    }
                }
                
                for (Vector2& pos : positions) {
                    if (pos.y < y) {
                        pos.y += 1;
                        blockModified = true;
                    }
                }
                
                if (blockModified) {
                    if (positions.empty()) {
                        it = fixedBlocks.erase(it);
                    } else {
                        it->positions = positions;
                        ++it;
                    }
                } else {
                    ++it;
                }
            }
            
            y++;
        }
    }
    
    if (linesCleared > 0) {
        switch (linesCleared) {
            case 1: score += 100; break;
            case 2: score += 300; break;
            case 3: score += 500; break;
            case 4: score += 800; break;
        }
    }
} 