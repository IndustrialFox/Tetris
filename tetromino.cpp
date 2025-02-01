#include "tetromino.h"

namespace gm
{
    //-----------------------------------------------------
    Tetromino_1 i{{{0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0},
                   {0, 1, 1, 1, 1},
                   {0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0}}};
    Tetromino_1 j{{{2, 0, 0}, {2, 2, 2}, {0, 0, 0}}};
    Tetromino_1 l{{{0, 0, 3}, {3, 3, 3}, {0, 0, 0}}};
    Tetromino_1 o{{{0, 4, 4}, {0, 4, 4}, {0, 0, 0}}};
    Tetromino_1 t{{{0, 5, 0}, {5, 5, 5}, {0, 0, 0}}};
    Tetromino_1 s{{{0, 6, 6}, {6, 6, 0}, {0, 0, 0}}};
    Tetromino_1 z{{{7, 7, 0}, {0, 7, 7}, {0, 0, 0}}};

    std::map<int, Color> tetromino_color{
        {1, Color::Cyan},
        {2, Color::Blue},
        {3, Color::Orange},
        {4, Color::Yellow},
        {5, Color::Purple},
        {6, Color::Green},
        {7, Color::Red},
    };
    Tetromino_1 rotate(Tetromino_1 &t)
    {
        Tetromino_1 result(t.size(), std::vector<int>(t.size(), 0));
        // t[i][j]=t'[j][3-i-1]
        for (int i = 0; i < t.size(); ++i)
        {
            for (int j = 0; j < t[0].size(); ++j)
            {
                if (t[i][j] > 0)
                    result[j][t[0].size() - i - 1] = t[i][j];
            }
        }
        return std::move(result);
    }
    //------------------------------------------------------------
    /**
     * I                      S
     * 0000 0010 0000 0100    0000 0100 0000 0110
     * 1111 0010 0000 0100    1110 0100 1000 0100
     * 0000 0010 1111 0100    0010 1100 1110 0100
     * 0000 0010 0000 0100    0000 0000 0000 0000
     *
     * 0x0f00 0x2222 0x00f0 0x4444
     *
     * one integer
     * 1Byte [0000 0000]<<'I'
     * 1Byte [0000 0000]<<color
     * 1Byte [0000 1111]<<data
     * 1Byte [0000 0000]<<data
     */
    Tetromino_2 J_set{
        0x0e20 | (static_cast<int>(Color::Cyan) << 16) | ('I' << 24),
        0x44c0 | (static_cast<int>(Color::Cyan) << 16) | ('I' << 24),
        0x08e0 | (static_cast<int>(Color::Cyan) << 16) | ('I' << 24),
        0x6440 | (static_cast<int>(Color::Cyan) << 16) | ('I' << 24),
    };

    bool get_bit(int t, int i, int j)
    {
        // return (t>>((4-i)*4+(4-j))) &0x1==1;
        return (t >> (i * 4 + j)) & 0x1 == 1;
    }

    //------------------------------------------------------------
    /**
     * (0,0)----->(dx,dy)
     */
    Tetromino I{{
        {{{'I', (int)Color::Cyan}, {-1, 0}, {1, 0}, {2, 0}}},  // 0
        {{{'I', (int)Color::Cyan}, {0, 1}, {0, -1}, {0, -2}}}, // R
        {{{'I', (int)Color::Cyan}, {-2, 0}, {-1, 0}, {1, 0}}}, // 2
        {{{'I', (int)Color::Cyan}, {0, 2}, {0, 1}, {0, -1}}},  // L
    }};
    Tetromino J{{
        {{{'J', (int)Color::Blue}, {-1, 1}, {-1, 0}, {1, 0}}},  // 0
        {{{'J', (int)Color::Blue}, {0, 1}, {1, 1}, {0, -1}}},   // R
        {{{'J', (int)Color::Blue}, {-1, 0}, {1, 0}, {1, -1}}},  // 2
        {{{'J', (int)Color::Blue}, {-1, -1}, {0, -1}, {0, 1}}}, // L
    }};
    Tetromino L{{
        {{{'L', (int)Color::Orange}, {-1, 0}, {1, 0}, {1, 1}}},   // 0
        {{{'L', (int)Color::Orange}, {0, 1}, {0, -1}, {1, -1}}},  // R
        {{{'L', (int)Color::Orange}, {-1, -1}, {-1, 0}, {1, 0}}}, // 2
        {{{'L', (int)Color::Orange}, {-1, 1}, {0, 1}, {0, -1}}},  // L
    }};
    Tetromino O{{
        {{{'O', (int)Color::Yellow}, {0, 1}, {1, 1}, {1, 0}}},     // 0
        {{{'O', (int)Color::Yellow}, {0, -1}, {1, 0}, {1, -1}}},   // R
        {{{'O', (int)Color::Yellow}, {-1, -1}, {-1, 0}, {0, -1}}}, // 2
        {{{'O', (int)Color::Yellow}, {-1, 1}, {-1, 0}, {0, 1}}},   // L
    }};
    Tetromino T{{
        {{{'S', (int)Color::Purple}, {-1, 0}, {0, 1}, {1, 0}}},  // 0
        {{{'S', (int)Color::Purple}, {0, 1}, {1, 0}, {0, -1}}},  // R
        {{{'S', (int)Color::Purple}, {-1, 0}, {1, 0}, {0, -1}}}, // 2
        {{{'S', (int)Color::Purple}, {-1, 0}, {0, 1}, {0, -1}}}, // L
    }};
    Tetromino S{{
        {{{'T', (int)Color::Green}, {-1, 0}, {0, 1}, {1, 1}}},   // 0
        {{{'T', (int)Color::Green}, {0, 1}, {1, 0}, {1, -1}}},   // R
        {{{'T', (int)Color::Green}, {-1, -1}, {0, -1}, {1, 0}}}, // 2
        {{{'T', (int)Color::Green}, {-1, 1}, {-1, 0}, {0, -1}}}, // L
    }};
    Tetromino Z{{
        {{{'Z', (int)Color::Red}, {-1, 1}, {0, 1}, {1, 0}}},   // 0
        {{{'Z', (int)Color::Red}, {0, -1}, {1, 0}, {1, 1}}},   // R
        {{{'Z', (int)Color::Red}, {-1, 0}, {0, -1}, {1, -1}}}, // 2
        {{{'Z', (int)Color::Red}, {-1, -1}, {-1, 0}, {0, 1}}}, // L
    }};

    /*
    J, L, S, T, Z Tetromino Offset Data
    Offset 1	Offset 2	Offset 3	Offset 4	Offset 5
    ( 0, 0)	    ( 0, 0)	    ( 0, 0)	    ( 0, 0)	    ( 0, 0)    0
    ( 0, 0)	    (+1, 0)	    (+1,-1)	    ( 0,+2)	    (+1,+2)    R
    ( 0, 0)	    ( 0, 0)	    ( 0, 0)	    ( 0, 0)	    ( 0, 0)    2
    ( 0, 0)	    (-1, 0)	    (-1,-1)	    ( 0,+2)	    (-1,+2)    L

    I Tetromino Offset Data
    Offset 1	Offset 2	Offset 3	Offset 4	Offset 5
    ( 0, 0)	    (-1, 0)	    (+2, 0)     (-1, 0)	    (+2, 0)    0
    (-1, 0)	    ( 0, 0)	    ( 0, 0)	    ( 0,+1)	    ( 0,-2)    R
    (-1,+1)	    (+1,+1)	    (-2,+1)	    (+1, 0)	    (-2, 0)    2
    ( 0,+1)	    ( 0,+1)	    ( 0,+1)	    ( 0,-1)	    ( 0,+2)    L

    O Tetromino Offset Data
    Offset 1	Offset 2	Offset 3	Offset 4	Offset 5
    ( 0, 0)	          No further offset data required          0
    ( 0,-1)           No further offset data required          R
    (-1,-1)           No further offset data required          2
    (-1, 0)           No further offset data required          L
    */
    Offset offset{{
        {{{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}},     // 0
        {{{0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2}}},    // R
        {{{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}},     // 2
        {{{0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}}}, // L
    }};
    Offset offset_I{{
        {{{0, 0}, {-1, 0}, {2, 0}, {-1, 0}, {2, 0}}},  // 0
        {{{-1, 0}, {0, 0}, {0, 0}, {0, 1}, {0, -2}}},  // R
        {{{-1, 1}, {1, 1}, {-2, 1}, {1, 0}, {-2, 0}}}, // 2
        {{{0, 1}, {0, 1}, {0, 1}, {0, -1}, {0, 2}}},   // L
    }};
    Offset offset_O{{
        {{{0, 0}}},   // 0
        {{{0, -1}}},  // R
        {{{-1, -1}}}, // 2
        {{{-1, 0}}},  // L
    }};
}