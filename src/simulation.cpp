#include "simulation.hpp"
#include "neuralNet.hpp"

Simulation::Simulation(const uint x, const uint y)
{
    InitWindow(x, y, "GENETICS!");
    SetTargetFPS(60);
}

void Simulation::spawn_cell(cint x, cint y, bool _new)
{
    this->_cells.push_back(
        Cell(x, y)
    );
    this->_cells.back().set_field(
        this->field.margin,
        this->field.SIZE
    );

    if (_new)
        this->_cells.back().scatter_brain();
}

void Simulation::spawn_populus(uint pop_num, bool _new)
{
    for(int i = 0; i < 100; ++i)
        this->spawn_cell(
            GetRandomValue(
                this->field.margin + 5,
                this->field.SIZE.x + this->field.margin - 5
            ),
            GetRandomValue(
                this->field.margin + 5,
                this->field.SIZE.y + this->field.margin - 5
            )
        , _new);
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
    const uVec2& n_size)
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
                this->field.margin,
                this->field.margin,
                this->field.SIZE.x,
                this->field.SIZE.y,
                GRAY
            );
            
            this->net_click_check();

            if (this->_selected_net != nullptr)
                this->_selected_net->draw_net(
                    {620, 120},
                    num_of_inputs,
                    hidden_layers,
                    num_of_outputs,
                    1
                );

            this->update_all();

            this->draw_all();

        EndDrawing();
    }
}

void Simulation::net_click_check()
{
    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        return;

    for(auto it = this->_cells.begin(); it != this->_cells.end(); ++it)
    {
        if (scl::get_distance(
            (*it).get_pos(),
            {
                static_cast<uint>(GetMousePosition().x),
                static_cast<uint>(GetMousePosition().y)
            }
        ) < 7)
        {
            this->_selected_net = (*it).get_brain_scan();
            std::cout << "CELL CLICKED!" << std::endl;
            return;
        }
    }

    //this->_selected_net = nullptr;
}