#pragma once
namespace tc
{
    //=std::cout是給參數提供的預設值,當不提供 os 時，函式會默認使用 std::cout
    void Move_to(int row, int col, std::ostream &os = std::cout);
    void Set_Fore_Color(int id, std::ostream &os = std::cout);
    void Set_Back_Color(int id, std::ostream &os = std::cout);
    void Clean_Screen(std::ostream &os = std::cout);
    void Reset_Color(std::ostream &os = std::cout);
    void Hide_Cursor(std::ostream &os = std::cout);
    void Show_Cursor(std::ostream &os = std::cout);
}