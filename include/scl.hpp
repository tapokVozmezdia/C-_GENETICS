// shortcut library

#pragma once

#include <iostream>

using uint = unsigned int;
using cint = const int;

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
}