# Tetris Game

Un juego de Tetris implementado en C++ usando la librería Raylib.

## Características

- Implementación clásica del Tetris
- Sistema de puntuación
- Pantalla de Game Over
- Reinicio del juego
- Controles intuitivos

## Controles

- **Flecha Arriba**: Rotar pieza
- **Flecha Izquierda**: Mover pieza a la izquierda
- **Flecha Derecha**: Mover pieza a la derecha
- **Flecha Abajo**: Acelerar caída
- **ESC**: Salir del juego
- **ENTER**: Reiniciar juego (en pantalla de Game Over)

## Requisitos

- C++17 o superior
- Raylib 5.0
- Compilador compatible con C++17 (g++, clang++, etc.)

## Instalación

1. Clona el repositorio:
```bash
git clone https://github.com/Adc-alt/TetrisGameAdc.git
cd TetrisGameAdc
```

2. Compila el juego:
```bash
make
```

3. Ejecuta el juego:
```bash
./game
```

## Estructura del Proyecto

```
.
├── include/          # Archivos de cabecera
│   ├── Block.h
│   ├── Constants.h
│   ├── Game.h
│   ├── Renderer.h
│   └── Tetromino.h
├── src/             # Archivos fuente
│   ├── Game.cpp
│   ├── main.cpp
│   ├── Renderer.cpp
│   └── Tetromino.cpp
├── Makefile
└── README.md
```

## Licencia

Este proyecto está bajo la Licencia MIT - ver el archivo [LICENSE](LICENSE) para más detalles.
