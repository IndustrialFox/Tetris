#include "define.h"
#include "terminal_ctrl.h"
#include "utils.h"
#include "draw.h"
#include "control.h"
#include "game.h"
#include "windows.h"

/*
性能優化
1.一次性的繪製,放在init中
2.只繪製屏幕變化的部分,不變化的部分不繪製
3.減少調用stdout的次數.  寄存器 ---> cache ---> memory ---> io device
*/
void init()
{
    tc::Hide_Cursor();
    tc::Clean_Screen();
    ui::windows_ui();
    gm::start_listerner();
    gm::init();
    // setbuf(stdout, nullptr);
}
void loop()
{
    while (gm::running)
    {
        gm::process();
        ui::info_ui();
        ui::game_ui();
        ui::show_help();
        std::this_thread::sleep_for(20ms);
    }
}
void exit()
{
    tc::Show_Cursor();
    tc::Reset_Color();
    ui::exit_ui();
}
int main()
{
    init();
    loop();
    exit();
    return 0;
}