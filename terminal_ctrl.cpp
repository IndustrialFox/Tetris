#include "define.h"
#include "terminal_ctrl.h"

void tc::Move_to(int row, int col,std::ostream& os)
{
    os << "\033[" << row << ';' << col << 'H';
}

void tc::Set_Fore_Color(int id,std::ostream& os)
{
    os << "\033[38;5;" << id << 'm';
}

void tc::Set_Back_Color(int id,std::ostream& os)
{
    os << "\033[48;5;" << id << 'm';
}

void tc::Clean_Screen(std::ostream& os)
{
    os << "\033[2J";
}

void tc::Reset_Color(std::ostream& os)
{
    os << "\033[0m";
}

void tc::Hide_Cursor(std::ostream& os)
{
    os << "\033[?25l";
}

void tc::Show_Cursor(std::ostream& os)
{
    os << "\033[?25h";
}
