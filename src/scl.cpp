#include <math.h>

#include "scl.hpp"

void scl::debug()
{
    std::cout << "======\nDEBUG\n======\n" << std::endl;
}

float scl::get_distance(const Vec2& st, const Vec2& fi)
{
    return sqrt(
        (st.x - fi.x) * (st.x - fi.x) + 
        (st.y - fi.y) * (st.y - fi.y)
    );
}

float scl::get_distance(const uVec2& st, const uVec2& fi)
{
    return sqrt(
        (st.x - fi.x) * (st.x - fi.x) + 
        (st.y - fi.y) * (st.y - fi.y)
    );
}