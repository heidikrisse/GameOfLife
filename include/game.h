#ifndef GAME_H
#define GAME_H

#include <vector>

struct Cell
{
    int x{};
    int y{};
    bool is_alive;
};

void initialize_board(std::vector<std::vector<Cell>> &game_board);

#endif
