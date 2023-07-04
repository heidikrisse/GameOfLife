#ifndef GAME_H
#define GAME_H

#include <vector>

struct Cell
{
    bool is_alive{false};
    unsigned int alive_neighbors{0};
};

using Gameboard = std::vector<std::vector<Cell>>;

void game_render_loop(const Gameboard &gameboard);

int count_cell_alive_neighbors(const Gameboard &gameboard, int row, int col);

void update_cell(Cell &cell);

void evolve_board(const Gameboard &gameboard);

void print_board(const Gameboard &gameboard);

Gameboard create_board(int width, int height);




#endif
