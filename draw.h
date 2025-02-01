#pragma once
#include "tetromino.h"
#include "define.h"

namespace dw
{

    void windows(int top, int left, int width, int height, std::string title);
    void tetromino(Tetromino_1 &t, int top, int left);
    void tetromino(Tetromino_2 &t, int top, int left, int index);
    void tetromino(Tetromino &t, int top, int left, int index);
    void frame(Matrix &frame, int top, int left);
    void next(std::queue<Tetromino> next_5, int top, int left);
    void field_piece(Matrix &m, int top, int left, Matrix *buffer = nullptr, std::string blank = "  ");
    void hold(Tetromino &h,int top, int left);
}