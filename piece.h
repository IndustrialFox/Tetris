#pragma once
#include "tetromino.h"

namespace gm
{
    class Piece
    {
    public:
        Piece(Tetromino &t, int x0, int y0, int i);
        Piece() = default;
        bool down();
        bool rotate(int i);
        bool left();
        bool right();
        std::pair<int, int> get_mino(int i) const;
        std::pair<int, int> get_xy() const ;
        int get_color() const;
        bool detect(int ox, int oy) const;
        void set_shadow();
        void set_hold_disable();
        Tetromino get_tetromino() const;

    private:
        bool move(int dx,int dy);
        char get_type() const;
        Tetromino tetro_set;
        int index; //[0 R 2 L]
        int x, y;  // tetromino的坐标系
        std::shared_ptr<Matrix> sp_playfield;//std::shared_ptr多个地方共享同一个Matrix实例
        int status;//0:陰影塊,1:正常塊,2:暂存块
        Offset offset;//wall kicks
    };
}