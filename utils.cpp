#include "define.h"
#include "utils.h"

namespace ut
{
    int fps()
    {
        static auto start = std::chrono::steady_clock::now();
        static int frame_count = 0;
        static int fps = 0;

        auto end = std::chrono::steady_clock::now();
        frame_count++;
        if (end - start > 1s)
        {
            fps = frame_count;
            frame_count = 0;
            start = end;
        }
        return fps;
    }

    bool timer(std::chrono::microseconds sec)
    {
        static auto start = std::chrono::steady_clock::now();
        auto end = std::chrono::steady_clock::now();
        if (end - start > sec)
        {
            start = end;
            return true;
        }
        return false;
    }
}