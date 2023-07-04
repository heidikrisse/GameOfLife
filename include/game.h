#ifndef GAME_H
#define GAME_H

#include <vector>

struct Cell
{
    bool is_alive{false};
    unsigned int alive_neighbors{0};
};

using Gameboard = std::vector<std::vector<Cell>>;

void game_render_loop(Gameboard &gameboard, bool random_pattern);

void draw_one_evolution(Gameboard &gameboard);

int count_cell_alive_neighbors(const Gameboard &gameboard, int row, int col);

bool update_cell(const Cell &cell);

void evolve_board(Gameboard &gameboard);

void print_board(const Gameboard &gameboard);

void default_starting_pattern(Gameboard &gameboard);

void randomize_starting_pattern(Gameboard &gameboard);

Gameboard create_board(int width, int height);

#endif
