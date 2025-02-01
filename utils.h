#pragma once
#include "define.h"

namespace ut
{
    int fps();
    inline int block2col(int b)
    {
        return 2 * b - 1;
    }
    bool timer(std::chrono::microseconds sec);
}