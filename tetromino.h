#pragma once
#include "define.h"
#include "color.h"

namespace gm
{
    // i[5][5]  JLOTSZ[3][3]
    extern Tetromino_1 i, j, l, o, t, s, z;
    Tetromino_1 rotate(Tetromino_1 &t);
    extern std::map<int, Color> tetromino_color;

    //-----------------------------------
    extern Tetromino_2 I_set, J_set, L_set, O_set, T_set, S_set, Z_set;
    extern bool get_bit(int t, int i, int j);

    //-----------------------------------
    extern Tetromino I, J, L, O, T, S, Z;
    extern Offset offset,offset_I,offset_O;
}