#include "simulation.hpp"

Simulation::Simulation(const uint x, const uint y)
{
    InitWindow(x, y, "GENETICS!");
    SetTargetFPS(60);
}

void Simulation::spawn_cell(cint x, cint y)
{
    this->_cells.push_back(
        Cell(x, y)
    );
}

void Simulation::spawn_populus(uint pop_num)
{
    for(int i = 0; i < 100; ++i)
        this->spawn_cell(
            GetRandomValue(
                10 + 5,
                this->field.SIZE.x + 10 - 5
            ),
            GetRandomValue(
                10 + 5,
                this->field.SIZE.y + 10 - 5
            )
        );
}

void Simulation::update_all()
{
    for (auto it = this->_cells.begin(); it != this->_cells.end(); ++it)
    {
        (*it).update();
    }
}

void Simulation::draw_all()
{
    for (auto it = this->_cells.begin(); it != this->_cells.end(); ++it)
    {
        (*it).draw();
    }
}

void Simulation::set_field_margin(const uint m)
{
    this->field.margin = m;
}

void Simulation::set_field_size(
    const Vec2& n_size)
{
    this->field.SIZE = n_size;
}

void Simulation::run()
{
    while(!WindowShouldClose())
    {
        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawText("GENETICS!", 4, 900, 48, LIME);

            DrawRectangle(
                10,
                10,
                this->field.SIZE.x,
                this->field.SIZE.y,
                GRAY
            );

            this->update_all();

            this->draw_all();

        EndDrawing();
    }
}