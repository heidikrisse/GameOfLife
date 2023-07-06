#ifndef GAME_H
#define GAME_H

#include <vector>

struct Cell
{
    bool is_alive{false};
    unsigned int alive_neighbors{0};
};

using Gameboard = std::vector<std::vector<Cell>>;

// Counts the number of alive naighbor cells
int count_cell_alive_neighbors(const Gameboard &gameboard, int row, int col);

// Updates the state of a single cell
bool update_cell(const Cell &cell);

// Evolves the gameboard to the next gameboard generation
void evolve_board(Gameboard &gameboard);

// Clears the gameboard
void clear_gameboard(Gameboard &gameboard);

// Sets default starting pattern on the game board
void default_starting_pattern(Gameboard &gameboard);

// Sets a random starting pattern on the game board
void randomize_starting_pattern(Gameboard &gameboard);

// Creates a game board with specified width and height
Gameboard create_board(int width, int height);

// Checks if the board is of accepted size
bool accepted_size(int board_width, int board_height);

#endif
