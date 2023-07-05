#ifndef GAME_H
#define GAME_H

#include <vector>

struct Cell
{
    bool is_alive{false};
    unsigned int alive_neighbors{0};
};

using Gameboard = std::vector<std::vector<Cell>>;

// The main in-game loop logic
void game_render_loop(Gameboard &gameboard);

// Pauses the simulation
void pause_simulation(Gameboard &gameboard);

// Draws one evolution of the game board
void draw_one_evolution(Gameboard &gameboard);

// Counts the number of alive naighbor cells
int count_cell_alive_neighbors(const Gameboard &gameboard, int row, int col);

// Updates the state of a single cell
bool update_cell(const Cell &cell);

// Evolves the gameboard to the next gameboard generation
void evolve_board(Gameboard &gameboard);

//Prints out the game board
void print_board(const Gameboard &gameboard);

// Sets default starting pattern on the game board
void default_starting_pattern(Gameboard &gameboard);

// Allows user to choose the starting pattern on the game board
void user_defined_starting_pattern(Gameboard &gameboard);

// Sets a random starting pattern on the game board
void randomize_starting_pattern(Gameboard &gameboard);

// Creates a game board with specified width and height
Gameboard create_board(int width, int height);

#endif
