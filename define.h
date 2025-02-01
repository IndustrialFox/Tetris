#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <termios.h>
#include <unistd.h>
#include <vector>
#include <map>
#include <cassert>
#include <ranges>
#include <random>
#include <queue>
#include <fstream>
#include <cmath>
#include <functional>
// #include <algorithm>
using namespace std::chrono_literals;

#define KEY_Q 'q'
#define KEY_W 'w'
#define KEY_A 'a'
#define KEY_D 'd'
#define KEY_S 's'
#define KEY_J 'j'
#define KEY_K 'k'
#define KEY_L 'l'
#define KEY_Y 'y'
#define KEY_H 'h'
#define KEY_SPACE ' '

using Tetromino_1 = std::vector<std::vector<int>>;
using Tetromino_2 = std::array<int, 4>;
using Tetromino = std::vector<std::vector<std::pair<int, int>>>;
using Matrix = std::vector<std::vector<int>>;
using Offset=std::vector<std::vector<std::pair<int,int>>>;