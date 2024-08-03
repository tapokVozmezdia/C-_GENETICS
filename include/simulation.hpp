#pragma once

#include <list>

#include "cell.hpp"
#include "neuralNet.hpp"
#include "raylib.h"
#include "scl.hpp"

class Simulation
{
    public:
        explicit Simulation(const uint x, const uint y);

        void spawn_cell(cint x, cint y, bool _new);
        //works inside the field boundaries
        void spawn_populus(uint pop_num, bool _new);
 
        void update_all();
        void draw_all();

        void set_field_margin(const uint m);
        
        void set_field_size(
            const uVec2& n_size);

        void run();

    private:

        struct Field
        {
            uint margin = 10;
            uVec2 SIZE = {500, 500};
        } field;

        void __draw_safe_zones();

        // n^2 complexity, use may slow the simulation down
        void __check_sense_relations();

        void __forget_sense_relations();

        void __net_click_check();
        void __pause_click_check();
        void __safe_click_check();

        void __respawn_populus();

        NeuralNet* _selected_net = nullptr;
        std::list<std::pair<Vec2, double>> _safe_zones;
        std::list<Cell> _cells;

        bool _pause = false;
        uint _clock = 0;
        uint _epoch = 0;
};