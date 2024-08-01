#pragma once

#include "scl.hpp"

class Cell
{
    public:
        Cell() = default;
        Cell(cint _x, cint _y);

        void draw();
        void update();

    private:
        void _draw();

        void _move_delta(const Vec2& delta);

        uVec2 _coords{500, 500};
        
        uint _field_margin = 10;
        uVec2 _field_size{500, 500};
};