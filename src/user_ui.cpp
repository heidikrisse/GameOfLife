// user_ui.cpp
#include "user_ui.h"
#include "raylib.h"
#include "game.h"
#include "constants.h"

#include <string>
#include <iostream>
#include <vector>

void input_boardsize_selection(int &board_width, int &board_height)
{
    // Adjust board width with down/up arrows:
    if (IsKeyDown(KEY_DOWN))
    {
        if (board_width > MIN_BOARD_WIDTH)
            --board_width;
    }
    else if (IsKeyDown(KEY_UP))
    {
        if (board_width < MAX_BOARD_WIDTH)
            ++board_width;
    }

    // Adjust board height with right/left arrows
    else if (IsKeyDown(KEY_RIGHT))
    {
        if (board_height < MAX_BOARD_HEIGHT)
            ++board_height;
    }
    else if (IsKeyDown(KEY_LEFT))
    {
        if (board_height > MIN_BOARD_HEIGHT)
            --board_height;
    }
}

// Game main menu
void main_menu()
{
    Gameboard gameboard{create_board(DEFAULT_BOARD_WIDTH, DEFAULT_BOARD_HEIGHT)};

    default_starting_pattern(gameboard);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game of Life - Main Menu");
    SetTargetFPS(30);

    int mouse_x{0};
    int mouse_y{0};

    int board_width{DEFAULT_BOARD_WIDTH};
    int board_height{DEFAULT_BOARD_HEIGHT};

    bool default_size{true};

    // 0 = default, 1 = random, 2 = custom
    int current_pattern{0};

    int select_option{0};

    while (!WindowShouldClose())
    {
        mouse_x = GetMouseX();
        mouse_y = GetMouseY();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Game of Life - Main Menu", 10, 10, 40, BLACK);
        DrawText("Start", 30, 180, 30, BLACK);
        DrawText("Change board size", 30, 230, 30, BLACK);
        DrawText("Change pattern", 30, 280, 30, BLACK);
        DrawText("Quit", 30, 330, 30, BLACK);

        DrawText("Current settings:", 30, 530, 30, GRAY);
        DrawText("Board size:", 30, 580, 30, GRAY);
        DrawText(std::to_string(board_width).c_str(), 400, 580, 30, GRAY);
        DrawText("x", 450, 580, 30, GRAY);
        DrawText(std::to_string(board_height).c_str(), 500, 580, 30, GRAY);
        DrawText("Board pattern:", 30, 630, 30, GRAY);
        if (current_pattern == 0)
        {
            DrawText("default", 400, 630, 30, GRAY);
        }
        if (current_pattern == 1)
        {
            DrawText("random", 400, 630, 30, GRAY);
        }
        if (current_pattern == 2)
        {
            DrawText("custom", 400, 630, 30, GRAY);
        }

        if (mouse_y >= 180 && mouse_y < 230) // start
        {
            DrawText("> ", 10, 180, 30, BLACK);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                EndDrawing();
                game_render_loop(gameboard);
            }
        }
        else if (mouse_y >= 230 && mouse_y < 280) // change board size
        {
            DrawText("> ", 10, 230, 30, BLACK);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                EndDrawing();
                change_board_size_menu(gameboard, board_width, board_height);
            }
        }
        else if (mouse_y >= 280 && mouse_y < 330) // change pattern
        {
            DrawText("> ", 10, 280, 30, BLACK);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                EndDrawing();
                current_pattern = get_user_input_pattern(gameboard);
            }
        }
        else if (mouse_y > 330 && mouse_y < 380)
        {
            DrawText("> ", 10, 330, 30, BLACK);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                break;
            }
        }
        EndDrawing();
    }
    CloseWindow();
}

// void menu_selection(Gameboard& gameboard, int& board_width, int& board_height, int& current_pattern, int mouse_y)
// {
    
// }
    
void change_board_size_menu(Gameboard& gameboard, int& board_width, int& board_height)
{
    int mouse_x{0};
    int mouse_y{0};
    
    while (!WindowShouldClose())
    {
        mouse_x = GetMouseX();
        mouse_y = GetMouseY();
        
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Changing board size will erase current pattern!", 30, 230, 30, BLACK);
        DrawText("Continue?", 30, 280, 30, BLACK);
        DrawText("Yes", 30, 330, 30, BLACK);
        DrawText("No", 30, 380, 30, BLACK);

        if (mouse_y >= 330 && mouse_y < 380) // yes option
        {
            DrawText("> ", 10, 330, 30, BLACK);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                EndDrawing();
                get_user_input_boardsize(board_width, board_height);
                break;
            }
        }
        if (mouse_y >= 380 && mouse_y < 430) // no option
        {
            DrawText("> ", 10, 380, 30, BLACK);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                break;
            }
        }
        EndDrawing();
    }
}

void get_user_input_boardsize(int &board_width, int &board_height)
{
    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Display the title and board size inputs
        DrawText("Game of Life - Set Width and Height", 10, 10, 40, BLACK);
        DrawText("Enter board width (10-333):", 10, 100, 30, BLACK);
        DrawText("Enter board height (10-333):", 10, 150, 30, BLACK);

        DrawText(std::to_string(board_width).c_str(), 480, 100, 30, BLACK); // same height as the enter text but little bit more right
        DrawText(std::to_string(board_height).c_str(), 480, 150, 30, BLACK);

        // Instructions for the user:
        DrawText("Use UP/DOWN arrow keys to adjust width", 10, 250, 20, BLACK);
        DrawText("Use LEFT/RIGHT arrow keys to adjust height", 10, 280, 20, BLACK);
        DrawText("Press ENTER to confirm the board size", 10, 310, 20, BLACK);

        EndDrawing();

        // Choose the board size with arrow keys:
        input_boardsize_selection(board_width, board_height);

        // If user hits enter, close the window
        if (IsKeyPressed(KEY_ENTER))
        {
            if (board_width >= MIN_BOARD_WIDTH && board_width <= MAX_BOARD_WIDTH && board_height >= MIN_BOARD_HEIGHT && board_height <= MAX_BOARD_HEIGHT)
            {
                break;
            }
        }
    }
}

int get_user_input_pattern(Gameboard &gameboard)
{
    int mouse_y {0};
    int mouse_x {0};

    int current_pattern {0};

    while (!WindowShouldClose())
    {
        mouse_y = GetMouseY();
        mouse_x = GetMouseX();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Pattern Selection", 10, 10, 40, BLACK);
        
        DrawText("Use default pattern", 30, 180, 30, BLACK);
        DrawText("Use random pattern", 30, 230, 30, BLACK);
        DrawText("Create custom pattern", 30, 280, 30, BLACK);

        if (mouse_y >= 180 && mouse_y < 230) // use default
        {
            DrawText("> ", 10, 180, 30, BLACK);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    current_pattern = 0;
                    default_starting_pattern(gameboard);
                    EndDrawing();
                    break;
                }
        }
        else if (mouse_y >= 230 && mouse_y < 280) // use random
        {
            DrawText("> ", 10, 230, 30, BLACK);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    current_pattern = 1;
                    randomize_starting_pattern(gameboard);
                    EndDrawing();
                    break;
                }
        }
        else if (mouse_y >= 280 && mouse_y < 330) // create custom
        {
            DrawText("> ", 10, 280, 30, BLACK);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    current_pattern = 2;
                    user_defined_starting_pattern(gameboard);
                    EndDrawing();
                    break;
                }
        }

        EndDrawing();
    }
    
    return current_pattern;
}
