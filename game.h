#pragma once
#include "tetromino.h"
#include "piece.h"

namespace gm
{
    //========================================
    // game variables
    //========================================
    // game status
    extern bool running;
    // locking mark
    extern bool locking;
    //holding mark
    extern bool holding;
    //game over
    extern bool game_over;
    //Restart
    extern bool resetting;
    //Help
    extern bool helping;
    // current Piece
    extern Piece cur_piece;
    // the game playfield
    extern Matrix playfield;
    // time interval per frame
    extern std::chrono::microseconds interval;
    // current rendering frame
    extern Matrix frame;
    // five previews
    extern std::queue<Tetromino> next;
    // hold piece
    extern Tetromino hold_piece;
    //scoring,level,clear lines
    extern int score,level,lines;
    //========================================
    //  game logic(functions)
    //========================================
    //  game初始化
    void init();
    // game main logic
    void process();
    // 渲染當前幀frame
    void render();
    // 獲取tetromino
    Piece pick();
    void quit();
    void rotateL();
    void rotateR();
    void rotate0();
    void left();
    void right();
    void down();
    // 直落
    void drop();
    // 鎖定
    void lock();
    // 消行
    void clear();
    // generate previews queue
    void preview();
    // load preset map
    void load();
    //hold piece
    void hold();
    //level up
    void levelup();
    //Restart
    void restart();
    //Help
    void help();
    // 映射工具
    void merge(Matrix &m, const Piece &p);
}
