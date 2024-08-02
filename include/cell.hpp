#pragma once

#include <math.h>

#include "scl.hpp"
#include "neuralNet.hpp"

class Cell
{
    public:
        Cell() = default;
        Cell(cint _x, cint _y);

        void set_field(cuint margin, const uVec2& size);

        uVec2 get_pos() const;

        NeuralNet* get_brain_scan();
        // randomizes weights in neural network
        void scatter_brain();

        void draw();
        void update();

    private:
        void __draw();

        void __move_delta(const Vec2& delta);

        NeuralNet __brain;

        uVec2 _coords{500, 500};
        
        uint _field_margin = 10;
        uVec2 _field_size{500, 500};

        uint __time_alive = 0;
        uint __bumped = 0;
};