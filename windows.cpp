#include "windows.h"
#include "draw.h"
#include "terminal_ctrl.h"
#include "utils.h"
#include "game.h"

namespace ui
{
    void windows_ui()
    {
        dw::windows(1, 1, 9, 6, "Hold");
        dw::windows(7, 1, 9, 16, "Status");
        dw::windows(1, 10, 12, 22, "CRRC Tetris");
        dw::windows(1, 22, 9, 18, "Next");
        dw::windows(19, 22, 9, 4, "Info");
    }
    void info_ui()
    {
        tc::Reset_Color();
        tc::Move_to(10, 7);
        std::cout << "FPS:" << ut::fps();
        tc::Move_to(12, 5);
        std::cout << "Level:" << gm::level;
        tc::Move_to(14, 5);
        std::cout << "Score:" << gm::score;
        tc::Move_to(16, 5);
        std::cout << "lines:" << gm::lines;
        if (gm::game_over)
        {
            tc::Set_Fore_Color(9);
            dw::windows(10, 12, 8, 4, "");
            tc::Move_to(11, ut::block2col(13));
            std::cout << " Game Over!\n";
            tc::Move_to(12, ut::block2col(13));
            tc::Set_Fore_Color((int)Color::Yellow);
            std::cout << "重新开始![Y]";
        }
        if (gm::helping)
        {
            tc::Set_Fore_Color((int)Color::Yellow);
            tc::Move_to(8, ut::block2col(13));
            std::cout << "幫助信息";
            tc::Move_to(9, ut::block2col(13));
            std::cout << "左旋     [J]";
            tc::Move_to(10, ut::block2col(13));
            std::cout << "右旋     [K]";
            tc::Move_to(11, ut::block2col(13));
            std::cout << "180旋    [l]";
            tc::Move_to(12, ut::block2col(13));
            std::cout << "下降     [S]";
            tc::Move_to(13, ut::block2col(13));
            std::cout << "直落     [W]";
            tc::Move_to(14, ut::block2col(13));
            std::cout << "存儲     [SPACE]";
            tc::Move_to(15, ut::block2col(13));
            std::cout << "重新開始 [Y]";
            tc::Move_to(16, ut::block2col(13));
            std::cout << "退出     [Q]";
        }
    }
    void game_ui()
    {
        dw::frame(gm::frame, 2, 11);
        dw::next(gm::next, 2, 24);
        dw::hold(gm::hold_piece, 2, 2);
        std::cout << std::flush;
    }
    void exit_ui()
    {
        tc::Clean_Screen();
        tc::Move_to(10, 20);
        tc::Set_Fore_Color(9);
        std::cout << "Bye Bye!\n\n\n\n\n";
    }
    void show_help()
    {
        tc::Reset_Color();
        tc::Move_to(21, ut::block2col(25));
        std::cout << "Help[H]";
    }
}
