#pragma once

#include <math.h>
#include <vector> 

#include "raylib.h"
#include "scl.hpp"

const uint num_of_inputs = 6;
const std::vector<uint> hidden_layers = {12, 10};
const uint num_of_outputs = 3; // always = 3

class NeuralNet
{
    public:
        NeuralNet();

        void randomize_weights();
        void set_inputs(const std::vector<double>& ins);
        std::vector<double> get_outputs();

        void forward();

        void draw_net(const Vec2& pos,
            cuint in, const std::vector<uint>& lrs, cuint ou, float scale);

    private: 

        struct Neuron
        {
            double input = 0;
            double output = 0;

            void Normalize();
            void Activate();
        };

        std::vector<Neuron> _inputs;
        std::vector<std::vector<Neuron>> _hidden;
        std::vector<Neuron> _outputs;

        std::vector<double> _weights;
};