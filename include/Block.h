#pragma once
#include <raylib.h>
#include <deque>

struct Block
{
    std::deque<Vector2> positions;
    Color color;
}; 