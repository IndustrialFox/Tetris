#include "define.h"
#include "control.h"
#include "game.h"
#include "control.h"

namespace gm
{
    std::map<char, std::function<void()>> Key_actions{
        {KEY_Q, command_quit},
        {KEY_J, command_rotateL},
        {KEY_K, command_rotateR},
        {KEY_L, command_rotate0},
        {KEY_A, command_left},
        {KEY_D, command_right},
        {KEY_S, command_down},
        {KEY_W, command_drop},
        {KEY_Y, command_restart},
        {KEY_H, command_help},
        {KEY_SPACE, command_hold},
    };

    char command;

    char getch()
    {
        char c;
        struct termios old, cur;
        tcgetattr(STDIN_FILENO, &old);
        cur = old;
        cur.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &cur);
        c = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &old);
        return c;
    }

    void key_event()
    {
        while (running)
        {
            command = getch();
            if (Key_actions.find(command) != Key_actions.end())
                Key_actions[command]();
        }
    }

    void start_listerner()
    {
        std::thread q(key_event);
        q.detach();
    }

    void command_quit()
    {
        quit();
    }

    void command_rotateL()
    {
        rotateL();
    }

    void command_rotateR()
    {
        rotateR();
    }

    void command_rotate0()
    {
        rotate0();
    }

    void command_left()
    {
        left();
    }

    void command_right()
    {
        right();
    }

    void command_down()
    {
        down();
    }

    void command_drop()
    {
        drop();
    }
    void command_hold()
    {
        hold();
    }
    void command_help()
    {
        help();
    }
    void command_restart()
    {
        restart();
    }
}
