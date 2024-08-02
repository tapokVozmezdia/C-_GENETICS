#include "cell.hpp"
#include "raylib.h"

Cell::Cell(cint _x, cint _y)
{
    this->_coords.x = _x;
    this->_coords.y = _y;
}

void Cell::set_field(cuint margin, const uVec2& size)
{
    this->_field_margin = margin;
    this->_field_size = size;
}

uVec2 Cell::get_pos() const
{
    return this->_coords;
}

NeuralNet* Cell::get_brain_scan()
{
    return &(this->__brain);
}

void Cell::scatter_brain()
{
    this->__brain.randomize_weights();
}

void Cell::draw()
{
    this->__draw();
}

void Cell::update()
{
    std::vector<double> ins;
    ins.push_back((double)((int)(this->_coords.x - this->_field_margin) - 
        (int)(this->_field_size.x / 2)) / (double)(this->_field_size.x / 2));
    ins.push_back((double)((int)(this->_coords.y - this->_field_margin) - 
        (int)(this->_field_size.y / 2)) / (double)(this->_field_size.y / 2));
    ins.push_back(
        (double)(this->__time_alive) / 600.
    );
    ins.push_back(
        sin(((double)(this->__time_alive) / 600.) * PI)
    );
    ins.push_back(0);
    ins.push_back(
        (double)(this->__bumped) / 600.
    );

    // std::cout << ins[5] << std::endl;

    // std::cout << ins[0] << " " << ins[1] << std::endl;


    this->__brain.set_inputs(ins);

    this->__brain.forward();

    // random movement
    // int x = GetRandomValue(-1, 1);
    // int y = GetRandomValue(-1, 1);

    // this->__move_delta({x, y});

    std::vector<double> outs = this->__brain.get_outputs();
    if (abs(outs[0]) > abs(outs[2]))
    {
        if (outs[0] > 0)
            this->__move_delta({1, 0});
        else
            this->__move_delta({-1, 0});
    }
    if (abs(outs[1]) > abs(outs[2]))
    {
        if (outs[1] > 0)
            this->__move_delta({0, 1});
        else
            this->__move_delta({0, -1});
    }

    this->__time_alive += 1;
    if(this->__time_alive >= 600)
        this->__time_alive = 0;

    if (this->__bumped > 0)
        this->__bumped -= 1;
}

void Cell::__draw()
{
    DrawCircle(
        this->_coords.x,
        this->_coords.y, 
        5, 
        RED);
}

void Cell::__move_delta(const Vec2& delta)
{
    if ((delta.x + static_cast<int>(this->_coords.x) > 5 + this->_field_margin)
        && (delta.x + static_cast<int>(this->_coords.x)
        < this->_field_size.x + this->_field_margin - 5))
        this->_coords.x += delta.x;
    else
        this->__bumped = 600;

    if ((delta.y + static_cast<int>(this->_coords.y) > 5 + this->_field_margin)
        && (delta.y + static_cast<int>(this->_coords.y)
        < this->_field_size.y + this->_field_margin - 5))
        this->_coords.y += delta.y;
    else
        this->__bumped = 600;
}