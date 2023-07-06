#ifndef USER_UI_H
#define USER_UI_H
#include "game.h"
#include "constants.h"
#include <string>

// Game main menu
void main_menu();

// Function to prompt user to confirm the user wants to change the board size
void change_board_size_menu(Gameboard &gameboard, int &board_width, int &board_height, Pattern& current_pattern);

bool accepted_size(int board_size);

// Function to get user input for the board size
void get_user_input_boardsize(int &board_width, int &board_height);

// Handles user's board size selection input
void input_boardsize_selection(int &board_width, int &board_height);

// Function to choose pattern (default, randomized or custom)
Pattern get_user_input_pattern(Gameboard &gameboard);

#endif
