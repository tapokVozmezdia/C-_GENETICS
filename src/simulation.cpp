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

            DrawText(
                "PRESS R TO CLEAR SAFE ZONES", 
                this->field.margin + 16, 
                this->field.margin + this->field.SIZE.y + 16, 
                24,
                BLACK
            );
            
            DrawText(
                "PRESS SPACE TO PAUSE SIMULATION", 
                this->field.margin + 16, 
                this->field.margin + this->field.SIZE.y + 48, 
                24,
                BLACK
            );

            DrawText(
                (std::string("CLOCK: ") + 
                    std::to_string(this->_clock)).c_str(), 
                this->field.margin + 16, 
                this->field.margin + this->field.SIZE.y + 80, 
                24,
                BLACK
            );

            DrawText(
                (std::string("EPOCH: ") + 
                    std::to_string(this->_epoch)).c_str(), 
                this->field.margin + 16, 
                this->field.margin + this->field.SIZE.y + 112, 
                24,
                BLACK
            );

            this->__check_sense_relations();

            this->__net_click_check();
            this->__pause_click_check();
            this->__safe_click_check();

            if (this->_selected_net != nullptr)
                this->_selected_net->draw_net(
                    {620, 120},
                    num_of_inputs,
                    hidden_layers,
                    num_of_outputs,
                    0.75
                );

            if (!this->_pause)
            {
                this->update_all();
                this->_clock += 1;
                if (this->_clock == 600)
                {
                    this->_clock = 0;
                    this->_epoch += 1;
                }
            }

            this->__draw_safe_zones();
            this->draw_all();

            this->__forget_sense_relations();

        EndDrawing();
    }
}

void Simulation::__draw_safe_zones()
{
    for (auto it : this->_safe_zones)
        DrawCircle(
            it.first.x,
            it.first.y,
            static_cast<float>(it.second),
            Color{128, 255, 128, 96}
        );
}

// SET DETECTION RADIUS HERE
const float detection_radius = 40;

void Simulation::__check_sense_relations()
{
    for (auto it = this->_cells.begin(); it != this->_cells.end(); ++it)
        for (auto jt = it; jt != this->_cells.end(); ++jt)
            if (
                scl::get_distance(
                    (*it).get_pos(),
                    (*jt).get_pos()
                ) < detection_radius 
                && it != jt
            )
            {    
                (*it).add_sense();
                (*jt).add_sense();
            }
}

void Simulation::__forget_sense_relations()
{
    for (auto it = this->_cells.begin(); it != this->_cells.end(); ++it)
        (*it).forget_sense();
}

void Simulation::__net_click_check()
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
            std::cout << "CELLS NEAR: " << (*it).__sense_others << std::endl;
            return;
        }
    }

    //this->_selected_net = nullptr;
}

void Simulation::__pause_click_check()
{
    if(IsKeyPressed(KEY_SPACE))
        this->_pause = !this->_pause;
}

void Simulation::__safe_click_check()
{
    if(IsKeyPressed(KEY_R))
    {
        this->_safe_zones.clear();
        return;
    }

    Vec2 mouse_pos = {
        static_cast<int>(GetMousePosition().x), 
        static_cast<int>(GetMousePosition().y)
    };

    if (!IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)
        || mouse_pos.x > this->field.margin + this->field.SIZE.x
        || mouse_pos.x < this->field.margin
        || mouse_pos.y > this->field.margin + this->field.SIZE.y
        || mouse_pos.y < this->field.margin)
        return;

    this->_safe_zones.push_back(
        std::pair<Vec2, double>(mouse_pos, 30)
    );
}

void Simulation::__respawn_populus()
{
    
}