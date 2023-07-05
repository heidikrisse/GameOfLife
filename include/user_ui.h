#ifndef USER_UI_H
#define USER_UI_H
#include "game.h"

// Handles user's option selection input of the main menu
int input_menu_option_selection(int select_option);

// Draws a checkmark symbol at the selected option
void draw_selected_option(int select_option);

// Handles user's board size selection input
void input_boardsize_selection(int &board_width, int &board_height);

// Game main menu
void main_menu();

//void menu_selection(Gameboard &gameboard, int &board_width, int &board_height, int& current_pattern, int mouse_y);

void change_board_size_menu(Gameboard &gameboard, int &board_width, int &board_height);

// Function to get user input for the board size
void get_user_input_boardsize(int &board_width, int &board_height);

int get_user_input_pattern(Gameboard &gameboard);

#endif
