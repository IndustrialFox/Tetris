#include "piece.h"
#include "game.h"

namespace gm
{
    Piece::Piece(Tetromino &t, int x0, int y0, int i)
        : tetro_set(t),
          x(x0),
          y(y0),
          index(i),
          sp_playfield(std::make_shared<Matrix>(playfield)),
          status(1)
    {
        if (get_type() == 'I')
        {
            offset = gm::offset_I;
        }
        else if (get_type() == 'O')
        {
            offset = gm::offset_O;
        }
        else
        {
            offset = gm::offset;
        }
    }

    std::pair<int, int> Piece::get_mino(int i) const
    {
        assert(i >= 0 && i <= 3);
        if (i == 0)
            return {0, 0};
        return tetro_set[index][i];
    }

    std::pair<int, int> Piece::get_xy() const
    {
        return {x, y};
    }

    int Piece::get_color() const
    {
        if(status==2)return (int)Color::Gray;
        return status ? tetro_set[index][0].second : 0 - tetro_set[index][0].second;
    }

    bool Piece::detect(int ox, int oy) const
    {
        assert(sp_playfield != nullptr);
        for (int i = 0; i < 4; ++i)
        {
            auto [dx, dy] = get_mino(i);
            // 邊界
            if (ox + dx < 0 || ox + dx > (*sp_playfield)[0].size() - 1 || oy + dy < 0 || oy + dy > (*sp_playfield).size() - 1)
                return false;
            // 有块
            if ((*sp_playfield)[oy + dy][ox + dx] > 0)
                return false;
        }
        return true;
    }

    void Piece::set_shadow()
    {
        status = 0;
    }

    void Piece::set_hold_disable()
    {
        status=2;
    }

    Tetromino Piece::get_tetromino() const
    {
        return tetro_set;
    }

    bool Piece::move(int dx, int dy)
    {
        if (detect(x + dx, y + dy))
        {
            x += dx;
            y += dy;
            return true;
        }
        return false;
    }

    char Piece::get_type() const
    {
        return tetro_set[index][0].first;
    }

    bool Piece::down()
    {
        return move(0, -1);
    }

    bool Piece::rotate(int i)
    {
        int future_index = (index + i) % 4;
        for (auto j : std::ranges::views::iota(0, (int)offset[0].size()))
        {
            auto [dx_0, dy_0] = offset[index][j];
            auto [dx_future, dy_future] = offset[future_index][j];
            auto dx = dx_0 - dx_future;
            auto dy = dy_0 - dy_future;
            Piece future_piece(tetro_set, x, y, future_index);
            if (future_piece.detect(x+dx, y+dy))
            {
                index = future_index;
                x += dx;
                y += dy;
                return true;
            }
        }
        return false;
    }

    bool Piece::left()
    {
        return move(-1, 0);
    }

    bool Piece::right()
    {
        return move(1, 0);
    }
}