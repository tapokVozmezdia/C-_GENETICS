#include "cell.hpp"
#include "raylib.h"

Cell::Cell(cint _x, cint _y)
{
    this->_coords.x = _x;
    this->_coords.y = _y;
}

void Cell::draw()
{
    this->_draw();
}

void Cell::update()
{
    int x = GetRandomValue(-1, 1);
    int y = GetRandomValue(-1, 1);

    this->_move_delta({x, y});
}

void Cell::_draw()
{
    DrawCircle(
        this->_coords.x,
        this->_coords.y, 
        5, 
        RED);
}

void Cell::_move_delta(const Vec2& delta)
{
    if ((delta.x + static_cast<int>(this->_coords.x) > 5 + this->_field_margin)
        && (delta.x + static_cast<int>(this->_coords.x)
        < this->_field_size.x + this->_field_margin - 5))
        this->_coords.x += delta.x;

    if ((delta.y + static_cast<int>(this->_coords.y) > 5 + this->_field_margin)
        && (delta.y + static_cast<int>(this->_coords.y)
        < this->_field_size.y + this->_field_margin - 5))
        this->_coords.y += delta.y;
}