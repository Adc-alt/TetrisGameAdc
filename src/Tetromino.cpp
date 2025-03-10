#include "Tetromino.h"
#include "Block.h"
#include "Constants.h"

Tetromino::Tetromino() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, blocks.size() - 1);
    currentBlock = &blocks[dis(gen)];   
}

const Block& Tetromino::GetCurrentBlock() const { return *currentBlock; }

void Tetromino::GenerateNextBlock() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, blocks.size() - 1);
    currentBlock = &blocks[dis(gen)];
}

bool Tetromino::WouldCollide(const vector<Block>& fixedBlocks, const Vector2& offset) {
    // Guardamos las posiciones originales
    deque<Vector2> originalPositions = currentBlock->positions;
    
    // Simulamos el movimiento
    for (Vector2& pos : currentBlock->positions) {
        pos.x += offset.x;
        pos.y += offset.y;
    }

    // Comprobamos colisiones
    bool wouldCollide = checkCollisionPiece(fixedBlocks);
    
    // Restauramos las posiciones originales
    currentBlock->positions = originalPositions;
    
    return wouldCollide;
}

void Tetromino::RotateBlock() {
    // Guardamos las posiciones originales
    deque<Vector2> originalPositions = currentBlock->positions;
    
    // Calculamos el centro de rotación
    Vector2 center = currentBlock->positions[1];
    
    // Rotamos la pieza
    for (Vector2& pos : currentBlock->positions) {            
        Vector2 relative = { 
            pos.x - center.x, 
            pos.y - center.y
        };
        
        Vector2 rotated = { 
            center.x - relative.y,
            center.y + relative.x
        };
        
        pos = rotated;
    }

    // Comprobamos si la rotación es válida
    bool isValidRotation = true;
    
    // Comprobamos colisiones con los bordes
    for (const Vector2& pos : currentBlock->positions) {
        if (pos.x < 1 || pos.x > GRID_WIDTH - 1 || pos.y >= GRID_HEIGHT) {
            isValidRotation = false;
            break;
        }
    }

    // Si la rotación no es válida, revertimos a las posiciones originales
    if (!isValidRotation) {
        currentBlock->positions = originalPositions;
    }
}

void Tetromino::MoveDown() {
    for (Vector2& pos : currentBlock->positions) {
        pos.y += 1;
    }
}

void Tetromino::MoveRight() {
    for (Vector2& pos : currentBlock->positions) {
        pos.x += 1;
    }
}

void Tetromino::MoveLeft() {
    for (Vector2& pos : currentBlock->positions) {
        pos.x -= 1;
    }
}

bool Tetromino::checkCollisionBottom() {
    for(Vector2& pos: currentBlock->positions) {
        if (pos.y >= GRID_HEIGHT) {
            return true;
        }
    }
    return false;
}

bool Tetromino::checkCollisionLeftRight() {
    for (Vector2& pos: currentBlock->positions) {
        if (pos.x < 1 || pos.x > GRID_WIDTH - 1) {
            return true;
        }    
    }
    return false;            
}

bool Tetromino::checkCollisionRight() {
    for (Vector2& pos: currentBlock->positions) {
        if (pos.x > GRID_WIDTH - 1) {
            return true;
        }
    }
    return false;
}

bool Tetromino::checkCollisionLeft() {
    for (Vector2& pos: currentBlock->positions) {
        if (pos.x < 2) {
            return true;
        }                
    }   
    return false;                     
}

bool Tetromino::isOutGrid() {
    for (const Vector2& pos : currentBlock->positions) {
        if (pos.y < 1) {
            return true;
        }
    }
    return false;
}

bool Tetromino::checkCollisionPiece(const vector<Block>& fixedBlocks) {
    // Para cada posición de la pieza actual
    for (const Vector2& currentPos : currentBlock->positions) {
        // Comprueba si colisiona con alguna pieza fija
        for (const Block& fixedBlock : fixedBlocks) {
            for (const Vector2& fixedPos : fixedBlock.positions) {
                // Si las posiciones coinciden, hay colisión
                if (currentPos.x == fixedPos.x && currentPos.y == fixedPos.y) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Tetromino::checkLineFull(const vector<Block>& fixedBlocks) {
    // Creamos un array de booleanos para cada columna de la línea
    vector<bool> line(GRID_WIDTH, false);
    
    // Para cada bloque fijo en el tablero
    for (const Block& block : fixedBlocks) {
        // Para cada posición del bloque
        for (const Vector2& pos : block.positions) {
            // Si la posición está en la línea que estamos comprobando
            // y dentro de los límites del tablero
            if (pos.y == GRID_HEIGHT - 1 && pos.x >= 1 && pos.x <= GRID_WIDTH) {
                // Marcamos esa columna como ocupada (ajustamos el índice)
                line[pos.x - 1] = true;
            }
        }
    }
    
    // Comprobamos si todas las columnas están ocupadas
    for (bool occupied : line) {
        if (!occupied) return false;
    }
    return true;
}

