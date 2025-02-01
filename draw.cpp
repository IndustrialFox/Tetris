#include "define.h"
#include "draw.h"
#include "terminal_ctrl.h"
#include "utils.h"
#include "game.h"

/*
    0	1	2	3	4	5	6	7	8	9	A	B	C	D	E	F
U+250x	─	━	│	┃	┄	┅	┆	┇	┈	┉	┊	┋	┌	┍	┎	┏
U+251x	┐	┑	┒	┓	└	┕	┖	┗	┘	┙	┚	┛	├	┝	┞	┟
U+252x	┠	┡	┢	┣	┤	┥	┦	┧	┨	┩	┪	┫	┬	┭	┮	┯
U+253x	┰	┱	┲	┳	┴	┵	┶	┷	┸	┹	┺	┻	┼	┽	┾	┿
U+254x	╀	╁	╂	╃	╄	╅	╆	╇	╈	╉	╊	╋	╌	╍	╎	╏
U+255x	═	║	╒	╓	╔	╕	╖	╗	╘	╙	╚	╛	╜	╝	╞	╟
U+256x	╠	╡	╢	╣	╤	╥	╦	╧	╨	╩	╪	╫	╬	╭	╮	╯
U+257x	╰	╱	╲	╳	╴	╵	╶	╷	╸	╹	╺	╻	╼	╽	╾	╿
*/

namespace dw
{

    void windows(int top, int left, int width, int height, std::string title)
    {
        for (int r = 0; r < height; ++r)
        {
            tc::Move_to(top + r, ut::block2col(left)); // move cursor every loop
            for (int c = 0; c < width; ++c)
            {
                if (r == 0)
                {
                    if (c == 0)
                        std::cout << " ╭";
                    else if (c == width - 1)
                        std::cout << "╮";
                    else
                        std::cout << "──";
                }
                else if (r == height - 1)
                {
                    if (c == 0)
                        std::cout << " ╰";
                    else if (c == width - 1)
                        std::cout << "╯";
                    else
                        std::cout << "──";
                }
                else
                {
                    if (c == 0)
                        std::cout << " │";
                    else if (c == width - 1)
                        std::cout << "│";
                    else
                        std::cout << "  ";
                }
            }
        }
        tc::Move_to(top, ut::block2col(left) + (width * 2 - title.length()) / 2);
        std::cout << title;
    }
    void tetromino(Tetromino_1 &t, int top, int left)
    {
        tc::Move_to(top, ut::block2col(left));
        for (int i = 0; i < t.size(); ++i)
        {
            tc::Move_to(top + i, ut::block2col(left));
            for (int j = 0; j < t[0].size(); ++j)
            {
                if (t[i][j] > 0)
                {
                    tc::Reset_Color();
                    tc::Set_Back_Color(static_cast<int>(gm::tetromino_color[t[i][j]]));
                    std::cout << "  ";
                }
                else
                {
                    tc::Reset_Color();
                    std::cout << "  ";
                }
            }
        }
    }
    //---------------------------------------------------------
    void tetromino(Tetromino_2 &t, int top, int left, int index)
    {
        // tc::Move_to(top, block2col(left));
        for (int i = 3; i >= 0; --i)
        {
            tc::Move_to(top + (3 - i), ut::block2col(left));
            for (int j = 3; j >= 0; --j)
            {
                if (gm::get_bit(t[index], i, j))
                {
                    tc::Reset_Color();
                    tc::Set_Back_Color(t[index] >> 16 & 0xff);
                    std::cout << "  ";
                }
                else
                {
                    tc::Reset_Color();
                    std::cout << "  ";
                }
            }
        }
    }
    //--------------------------------------------------------
    /*
    row=row+dy
    col=top-dx
    */
    void tetromino(Tetromino &t, int top, int left, int index)
    {
        tc::Move_to(top, ut::block2col(left));
        tc::Set_Back_Color(t[index][0].second);
        std::cout << "  ";
        for (auto pair : t[index])
        {
            if (pair.first > 'A')
                continue;
            tc::Move_to(top - pair.second, ut::block2col(left + pair.first));
            std::cout << "  ";
        }
    }
    //--------------------------------------------------------
    void frame(Matrix &frame, int top, int left)
    {
        // frame:xy--->col/row
        static Matrix buffer(frame.size(), std::vector<int>(frame[0].size(), -1));
        if(gm::resetting)
        {
            buffer=Matrix(frame.size(), std::vector<int>(frame[0].size(), -1));
        }
        Matrix f(frame.begin(), frame.begin() + 20); // 只绘制前20行，顶上2行不绘制
        field_piece(f, top, left, &buffer, "\u30FB");
    }
    void next(std::queue<Tetromino> next_5, int top, int left)
    {
        static Matrix buffer(15, std::vector<int>(6, -1));
        Matrix next_field(15, std::vector<int>(6, 0));
        for (int y = 12; next_5.size() > 0; y -= 3)
        {
            gm::Piece p(next_5.front(), 2, y, 0);
            gm::merge(next_field, p);
            next_5.pop();
        }

        field_piece(next_field, top, left, &buffer);
    }
    void field_piece(Matrix &m, int top, int left, Matrix *buffer, std::string blank)
    {
        std::ostringstream oss;
        int col, row;
        for (int y = 0; y < m.size(); ++y)
        {
            for (int x = 0; x < m[0].size(); ++x)
            {
                if (buffer != nullptr)
                {
                    if ((*buffer)[y][x] == m[y][x])
                        continue;
                    (*buffer)[y][x] = m[y][x];
                }
                row = top + m.size() - y - 1;
                col = left + x;
                tc::Move_to(row, ut::block2col(col), oss);
                if (m[y][x] > 0) // 正常塊
                {
                    tc::Reset_Color(oss);
                    tc::Set_Back_Color(m[y][x], oss);
                    oss << "  ";
                }
                else if (m[y][x] < 0) // 陰影塊
                {
                    tc::Reset_Color(oss);
                    tc::Set_Fore_Color(0 - m[y][x], oss);
                    oss << "\u25e3\u25e5";
                }
                else // 空白區域
                {
                    tc::Reset_Color(oss);
                    oss << blank;
                }
            }
        }
        std::cout << oss.str();
    }
    void hold(Tetromino &h, int top, int left)
    {
        static Matrix buffer(4, std::vector<int>(7, -1));
        Matrix hold_field(4, std::vector<int>(7, 0));

        if (!h.empty())
        {
            gm::Piece p(h, 3, 1, 0);
            if (gm::holding)
                p.set_hold_disable();
            gm::merge(hold_field, p);
            field_piece(hold_field, top, left, &buffer);
        }
    }
}
