// shortcut library

#pragma once

#include <iostream>

using uint = unsigned int;
using cint = const int;
using cuint = const unsigned int;

struct Vec2
{
    int x;
    int y;
};

struct uVec2
{
    uint x;
    uint y;
};

namespace scl 
{
    void debug();

    float get_distance(const Vec2& st, const Vec2& fi);
    float get_distance(const uVec2& st, const uVec2& fi);
}