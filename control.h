#pragma once

namespace gm // game master
{
    extern char command;
    char getch();
    void key_event();
    void start_listerner();
    void command_quit();
    void command_rotateL();
    void command_rotateR();
    void command_rotate0();
    void command_left();
    void command_right();
    void command_down();
    void command_drop();
    void command_hold();
    void command_restart();
    void command_help();
}