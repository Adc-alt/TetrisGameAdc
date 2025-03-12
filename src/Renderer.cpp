#include "Renderer.h"
#include "Block.h"

Renderer::Renderer(int& gameScore) : score(gameScore) {}

void Renderer::DrawBlock(const Block& block) {
    for (const Vector2& pos : block.positions) {
        DrawRectangle(
            pos.x * CELL_SIZE, 
            pos.y * CELL_SIZE, 
            CELL_SIZE, 
            CELL_SIZE, 
            block.color
        );
    }
}

void Renderer::DrawNextBlock(const Block& block) {
    // Dibujamos el siguiente bloque en el panel de "Next Piece"
    // Ajustamos la posición para que aparezca en el panel
    for (const Vector2& pos : block.positions) {
        DrawRectangle(
            (pos.x + 8) * CELL_SIZE,  // Desplazamiento para centrar en el panel
            (pos.y + 10) * CELL_SIZE, // Desplazamiento vertical para el panel
            CELL_SIZE,
            CELL_SIZE,
            block.color
        );
    }
}

void Renderer::DrawGrid() {
    // Líneas verticales
    for (int i = CELL_SIZE; i <= CELL_SIZE * (GRID_WIDTH + 1); i += CELL_SIZE) {
        DrawLineEx(
            Vector2{(float)i, (float)CELL_SIZE},
            Vector2{(float)i, (float)CELL_SIZE * (GRID_HEIGHT + 1)},
            2.0f,
            GRID_COLOR
        );
    }
    
    // Líneas horizontales
    for (int i = CELL_SIZE; i < CELL_SIZE * (GRID_HEIGHT + 1); i += CELL_SIZE) {
        DrawLineEx(
            Vector2{(float)CELL_SIZE, (float)i},
            Vector2{(float)CELL_SIZE * (GRID_WIDTH + 1), (float)i},
            2.0f,
            GRID_COLOR
        );
    }
}

void Renderer::DrawUI() {
    // Panel de puntuación
    DrawRectangleRounded(
        Rectangle{(float)CELL_SIZE * 12, (float)CELL_SIZE * 3, (float)CELL_SIZE * 7, (float)CELL_SIZE * 3},
        0.3f,
        8,
        PANEL_COLOR
    );
    
    // Centrar el texto "Score"
    const char* scoreText = "Score";
    float scoreTextWidth = MeasureText(scoreText, CELL_SIZE);
    float scoreX = (CELL_SIZE * 12) + ((CELL_SIZE * 7 - scoreTextWidth) / 2);
    DrawText(scoreText, scoreX, CELL_SIZE * 2.0f, CELL_SIZE, WHITE);
    
    // Centrar el número del score
    char scoreValue[32];
    sprintf(scoreValue, "%d", score);
    float scoreValueWidth = MeasureText(scoreValue, CELL_SIZE);
    float scoreValueX = (CELL_SIZE * 12) + ((CELL_SIZE * 7 - scoreValueWidth) / 2);
    DrawText(scoreValue, scoreValueX, CELL_SIZE * 4.0f, CELL_SIZE, WHITE);

    // Panel de siguiente pieza
    DrawRectangleRounded(
        Rectangle{(float)CELL_SIZE * 12, (float)CELL_SIZE * 10, (float)CELL_SIZE * 7, (float)CELL_SIZE * 6},
        0.3f,
        8,
        PANEL_COLOR
    );
    
    // Centrar el texto "Next Piece"
    const char* nextPieceText = "Next Piece";
    float nextPieceTextWidth = MeasureText(nextPieceText, CELL_SIZE);
    float nextPieceX = (CELL_SIZE * 12) + ((CELL_SIZE * 7 - nextPieceTextWidth) / 2);
    DrawText(nextPieceText, nextPieceX, CELL_SIZE * 9.0f, CELL_SIZE, WHITE);
}

void Renderer::DrawBoard() {
    DrawRectangle(
        CELL_SIZE, 
        CELL_SIZE, 
        CELL_SIZE * GRID_WIDTH, 
        CELL_SIZE * GRID_HEIGHT, 
        BOARD_COLOR
    );
}

    
