#pragma once

#include <list>

#include "cell.hpp"
#include "raylib.h"
#include "scl.hpp"

class Simulation
{
    public:
        explicit Simulation(const uint x, const uint y);

        void spawn_cell(cint x, cint y);
        //works inside the field boundaries
        void spawn_populus(uint pop_num);
 
        void update_all();
        void draw_all();

        void set_field_margin(const uint m);
        
        void set_field_size(
            const Vec2& n_size);

        void run();

    private:

        struct Field
        {
            uint margin = 10;
            Vec2 SIZE = {500, 500};
        } field;

        std::list<Cell> _cells;

};