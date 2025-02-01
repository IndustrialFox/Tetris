#include "game.h"
#include "tetromino.h"
#include "utils.h"

namespace gm
{
    //---------------variables-------------
    bool running;
    bool locking;
    bool holding;
    bool game_over;
    bool resetting;
    bool helping;
    Piece cur_piece;
    Matrix playfield;
    std::chrono::microseconds interval;
    Matrix frame;
    std::queue<Tetromino> next;
    Tetromino hold_piece;
    int score, level, lines;
    //-------------------------------------
    void init()
    {
        running = true;
        holding = false;
        locking = false;
        game_over = false;
        resetting = true;
        helping = false;
        score = lines = 0;
        levelup();
        playfield = Matrix(22, std::vector<int>(10, 0));
        preview();
        // load();
        cur_piece = pick();
        frame = playfield;
    }
    void process()
    {
        if (game_over)
            return;
        render();
        if (ut::timer(interval))
        {
            if (cur_piece.down())
                return;
            if (locking)
            {
                lock();
                clear();
                levelup();
                cur_piece = pick();
                resetting = false;
                locking = false;
                holding = false;
            }
            else
            {
                locking = true;
            }
        }
    }
    void render()
    {
        frame = playfield;
        // 正常塊
        merge(frame, cur_piece);
        // 陰影塊
        Piece shadow = cur_piece;
        shadow.set_shadow();
        while (shadow.down())
            ;
        merge(frame, shadow);
    }
    Piece pick()
    {
        // get the first element in "Next" window
        assert(next.size() > 0);
        Piece p(next.front(), 4, 20, 0);
        next.pop();
        preview();
        if (!p.detect(6, 20))
        {
            game_over = true;
        }
        return std::move(p);
    }
    void quit()
    {
        running = false;
    }
    void rotateL()
    {
        cur_piece.rotate(3);
    }
    void rotateR()
    {
        cur_piece.rotate(1);
    }
    void rotate0()
    {
        cur_piece.rotate(2);
    }
    void left()
    {
        cur_piece.left();
    }
    void right()
    {
        cur_piece.right();
    }
    void down()
    {
        if (cur_piece.down())
            score += 1;
    }
    void drop()
    {
        while (cur_piece.down())
            score += 2;
        interval = 5ms;
    }
    void lock()
    {
        merge(playfield, cur_piece);
    }
    void clear()
    {
        int count = 0;
        for (auto it = playfield.begin(); it != playfield.end(); ++it)
        {
            bool full = true;
            for (auto cell : *it)
            {
                if (cell == 0)
                {
                    full = false;
                    break;
                }
            }
            if (full) // 消行
            {
                it = playfield.erase(it);
                playfield.push_back(std::vector<int>(it->size(), 0));
                --it;
                count++;
            }
        }
        /*
        Single	100 x level	100 x level
        Double	300 x level	300 x level
        Triple	500 x level	500 x level
        Tetris	800 x level	800 x level

        Soft drop	1 point per cell	1 point per cell
        Hard drop	2 points per cell	2 point per cell
        */
        if (count == 1)
            score += 10 * level;
        if (count == 2)
            score += 30 * level;
        if (count == 3)
            score += 50 * level;
        if (count == 4)
            score += 80 * level;
        lines += count;
    }
    void preview()
    {
        static std::vector<Tetromino> bag = {I, J, L, O, T, S, Z};
        std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());

        int index;
        while (next.size() < 5)
        {
            std::uniform_int_distribution<> dist(0, bag.size() - 1);
            index = dist(gen);
            next.push(bag[index]);
            bag.erase(bag.begin() + index);
            if (bag.size() == 0)
                bag = {I, J, L, O, T, S, Z};
        }
    }
    // void load()
    // {
    //     std::fstream fs("Tetris_1.map");
    //     assert(fs.is_open());
    //     std::string line;
    //     auto first_20 = playfield | std::ranges::views::take(20);
    //     auto reversed = std::ranges::views::reverse(first_20);
    //     for (auto &row : reversed)
    //     {
    //         getline(fs, line);
    //         for (auto i : std::ranges::views::iota(0, 10))
    //         {
    //             if (line[i] == '1')
    //                 row[i] = (int)Color::Gray;
    //         }
    //     }
    //     fs.close();
    // }
    // hold区为空，取当前Tetromino存入hold区
    // hold区已存Tetromino，取出替换当前Tetromino
    // 每个循环只能hold一次
    void hold()
    {
        if (holding)
            return;
        if (hold_piece.empty())
        {
            hold_piece = cur_piece.get_tetromino();
            cur_piece = pick();
        }
        else
        {
            auto tmp = hold_piece;
            hold_piece = cur_piece.get_tetromino();
            cur_piece = Piece(tmp, 4, 20, 0);
        }
        holding = true;
    }
    void levelup()
    {
        level = lines / 1 + 1;
        double base_time = 0.8 - ((level - 1) * 0.007);
        if (base_time < 0.1)
            base_time = 0.1;
        interval = std::chrono::milliseconds(static_cast<int>(1000 / (0.5 + 0.1 * level)));
        // Time = (0.8-((Level-1)*0.007))^(Level-1)
        // interval = std::chrono::milliseconds((int(pow((0.8 - ((level - 1) * 0.007)), level - 1)) * 1000));
    }
    void restart()
    {
        init();
        resetting = true;
    }
    void help()
    {
        helping=!helping;
        resetting=!helping;
    }
    void merge(Matrix &m, const Piece &p)
    {
        auto [x, y] = p.get_xy();                    // 使用 [] 解包，替代first和second
        for (int i : std::ranges::views::iota(0, 4)) //([0,4),相當於for(int i=0;i<4;++i)
        {
            auto [dx, dy] = p.get_mino(i);
            if (m[y + dy][x + dx] == 0)
                m[y + dy][x + dx] = p.get_color();
        }
    }
}