#include <iostream>
#include "neuralNet.hpp"

NeuralNet::NeuralNet()
{
    for (int i = 0; i < num_of_inputs; ++i)
    {
        this->_inputs.push_back(Neuron());
    }

    for (auto it : hidden_layers)
    {
        this->_hidden.push_back(std::vector<Neuron>());
        for (int i = 0; i < it; ++i)
        {
            this->_hidden.back().push_back(Neuron());
        }
    }
    for (int i = 0; i < num_of_outputs; ++i)
        this->_outputs.push_back(Neuron());

    uint num_of_weights = 0;
    std::vector<uint> tmp;
    tmp.push_back(num_of_inputs);
    for (auto it : hidden_layers)
        tmp.push_back(it);
    tmp.push_back(num_of_outputs);

    auto it = tmp.begin();
    uint last = *it;
    it++;
    while(it != (tmp.end()))
    {
        num_of_weights += ((*it) * last);
        last = *it;
        it++;
    }

    for (int i = 0; i < num_of_weights; ++i)
        this->_weights.push_back(0);
}

void NeuralNet::randomize_weights()
{
    for (int i = 0; i < this->_weights.size(); ++i)
        this->_weights[i] = static_cast<double>(
            GetRandomValue(-300, 300)
        ) / 100.;
}

void NeuralNet::set_inputs(const std::vector<double>& ins)
{
    for (int i = 0; i < num_of_inputs; ++i)
    {
        this->_inputs[i].input = ins[i];
        this->_inputs[i].Normalize();
    }
}

std::vector<double> NeuralNet::get_outputs()
{
    std::vector<double> tmp;
    for (auto it : this->_outputs)
        tmp.push_back(it.output);
    return tmp;
}

void NeuralNet::forward()
{
    double sum = 0;

    uint weight_num = 0;

    int shift = -1;
    for (auto it : hidden_layers)
    {
        for (int i = 0; i < it; ++i)
        {
            sum = 0;
            if (shift == -1)
            {  
                for (int j = 0; j < num_of_inputs; ++j)
                {
                    sum += ((this->_inputs[j].output) * 
                        this->_weights[weight_num]);
                    ++weight_num;
                }
            }
            else 
            {
                for (int j = 0; j < hidden_layers[shift]; ++j)
                {
                    sum += ((this->_hidden[shift][j].output) * 
                        this->_weights[weight_num]);
                    ++weight_num;
                }
            }
            this->_hidden[shift + 1][i].input = sum;
            this->_hidden[shift + 1][i].Activate();
        }
        shift += 1;
    }

    for (int i = 0; i < num_of_outputs; ++i)
    {
        sum = 0;
        for (int j = 0; j < hidden_layers.back(); ++j)
        {
            sum += ((this->_hidden.back()[j].output) * 
                this->_weights[weight_num]);
            ++weight_num;
        }
        this->_outputs[i].input = sum;
        this->_outputs[i].Activate();
    }
}

void NeuralNet::draw_net(const Vec2& pos,
    cuint in, const std::vector<uint>& lrs, cuint ou, float scale)
{
    uint m = 0;
    for (auto i : lrs)
        if (i > m) 
            m = i;
    if (in > m)
        m = in;
    if (ou > m)
        m = ou;

    uint line = (m - in) / 2;

    std::vector<int> posy;
    int posx;

    for (int i = 0; i < in; i++)
    {
        DrawRing(
            {(float)pos.x, pos.y + (60 * scale * line)}, 
            19 * scale,
            21 * scale, 
            0,
            360,
            1,
            BLACK
        );
        Color cl1 = {0, 0, 0, 0};

        cl1.r = 192;

        if (this->_inputs[i].output > 0)
            cl1.g = 192;
        else
            cl1.b = 192;

        cl1.a = (int)(192. * abs(this->_inputs[i].output));
        
        DrawCircle(
            (float)pos.x, 
            pos.y + (60 * scale * line), 
            10,
            cl1
        );
        posx = pos.x + 21;
        posy.push_back(pos.y + (60 * scale * line));
        ++line;
    }

    uint shift = 1;

    std::vector<int> t_c;

    uint weight_num = 0;

    for (auto it : lrs)
    {
        line = (m - it) / 2;
        t_c.clear();
        for (int i = 0; i < it; ++i)
        {
            DrawRing(
                {
                    (float)pos.x + shift * scale * 220, 
                    pos.y + (60 * scale * line)
                }, 
                19 * scale,
                21 * scale, 
                0,
                360,
                1,
                BLACK
            );

            Color cl1 = {0, 0, 0, 0};

            cl1.r = 192;

            if (this->_hidden[shift - 1][i].output > 0)
                cl1.g = 192;
            else
                cl1.b = 192;

            cl1.a = (int)(192. * abs(this->_hidden[shift - 1][i].output));
            
            DrawCircle(
                (float)pos.x + shift * scale * 220, 
                pos.y + (60 * scale * line),
                10,
                cl1
            );

            double weight = 0;

            for (auto jt : posy)
            {
                Color c = {0, 0, 0, 128};
                uint diff = (char)static_cast<int>(abs(
                    this->_weights[weight_num]
                ) * 64);
                if (this->_weights[weight_num] < 0)
                    c.b += diff;
                else
                    c.r += diff;

                ++weight_num;

                DrawLine(
                    posx,
                    jt,
                    (float)pos.x + shift * scale * 220 - 21,
                    pos.y + (60 * scale * line),
                    c
                );
            }
            t_c.push_back(pos.y + (60 * scale * line));
            ++line;
        }
        posx = (float)pos.x + shift * scale * 220 + 21;
        posy = t_c;
        ++shift;
    }

    line = 0;

    int tmp = m * 30 - (30 * ou);

    for (int i = 0; i < ou; i++)
    {
        DrawRing(
            {
                (float)pos.x + shift * scale * 220, 
                pos.y + (60 * scale * line) + tmp
            },
            19 * scale,
            21 * scale, 
            0,
            360,
            1,
            BLACK
        );

        Color cl1 = {0, 0, 0, 0};

        cl1.r = 192;

        if (this->_outputs[i].output > 0)
            cl1.g = 192;
        else
            cl1.b = 192;

        cl1.a = (int)(192. * abs(this->_outputs[i].output));
        
        DrawCircle(
            (float)pos.x + shift * scale * 220, 
                pos.y + (60 * scale * line) + tmp,
            10,
            cl1
        );

        for (auto jt : posy)
        {
            Color c = {0, 0, 0, 128};
            uint diff = (char)static_cast<int>(abs(
                this->_weights[weight_num]
            ) * 64);
            if (this->_weights[weight_num] < 0)
                c.b += diff;
            else
                c.r += diff;

            ++weight_num;

            DrawLine(
                posx,
                jt,
                (float)pos.x + shift * scale * 220 - 21,
                pos.y + (60 * scale * line) + tmp,
                c
            );
        }
        ++line;
    }
}

void NeuralNet::Neuron::Normalize()
{
    this->output = this->input;
}

void NeuralNet::Neuron::Activate()
{
    this->output = tanh(this->input);
}