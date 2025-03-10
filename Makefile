# Ruta donde está instalada la librería Raylib
RAYLIB_DIR = C:\raylib

# Compilador
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I$(RAYLIB_DIR)/include -I./include -I./src
LDFLAGS = -L$(RAYLIB_DIR)/lib -lraylib -lopengl32 -lgdi32 -lwinmm

# Archivos fuente y objetivo
SRC = src/main.cpp src/Tetromino.cpp src/Renderer.cpp src/Game.cpp
TARGET = game.exe

# Regla principal
all: $(TARGET)

# Regla para compilar game.exe
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

# Regla para limpiar
clean:
	del /F /Q $(TARGET)

# Regla para ejecutar
run: $(TARGET)
	.\$(TARGET)

#Archivos fuente