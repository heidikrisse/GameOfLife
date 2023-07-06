#ifndef USER_UI_H
#define USER_UI_H

#include "game.h"
#include "constants.h"
#include <string>

// Function to prompt user to confirm the user wants to change the board size
void change_board_size_menu(Gameboard &gameboard, int &board_width, int &board_height, Pattern &current_pattern);

// Function to get user input for the board size
void get_user_input_boardsize(int &board_width, int &board_height);

// Function to choose pattern (default, randomized or custom)
Pattern get_user_input_pattern(Gameboard &gameboard);

// The main in-game loop logic
void game_render_loop(Gameboard &gameboard);

// Draws one evolution of the game board
void draw_one_evolution(Gameboard &gameboard);

// Prints out the game board
void print_board(const Gameboard &gameboard);

// Allows user to choose the starting pattern on the game board
void user_defined_starting_pattern(Gameboard &gameboard);

#endif
