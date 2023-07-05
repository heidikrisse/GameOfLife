// user_ui.cpp
#include "user_ui.h"
#include "raylib.h"
#include "game.h"
#include "constants.h"

#include <string>
#include <iostream>
#include <vector>

int input_menu_option_selection(select_option)
{
    if (IsKeyPressed(KEY_DOWN))
    {
        select_option = (select_option + 1) % 4;
    }
    else if (IsKeyPressed(KEY_UP))
    {
        select_option = (select_option - 1 + 4) % 4;
    }
    else if (IsKeyPressed(KEY_ENTER))
    {
        CloseWindow();
    }

    return select_option;
}

void draw_selected_option(int select_option)
{
    if (select_option == 0)
    {
        DrawText("> ", 10, 180, 30, BLACK);
    }
    else if (select_option == 1)
    {
        DrawText("> ", 10, 230, 30, BLACK);
    }
    else if (select_option == 2)
    {
        DrawText("> ", 10, 280, 30, BLACK);
    }
    else if (select_option == 3)
    {
        DrawText("> ", 10, 330, 30, BLACK);
    }
}

void input_boardsize_selection(int &board_width, int &board_height)
{
    // Adjust board width with down/up arrows:
    if (IsKeyPressed(KEY_DOWN))
    {
        if (board_width > MIN_BOARD_WIDTH)
            --board_width;
    }
    else if (IsKeyPressed(KEY_UP))
    {
        if (board_width < MAX_BOARD_WIDTH)
            ++board_width;
    }

    // Adjust board height with right/left arrows
    else if (IsKeyPressed(KEY_RIGHT))
    {
        if (board_height < MAX_BOARD_HEIGHT)
            ++board_height;
    }
    else if (IsKeyPressed(KEY_LEFT))
    {
        if (board_height > MIN_BOARD_HEIGHT)
            --board_height;
    }
}

// Game main menu
void main_menu()
{
    InitWindow(MENU_WIDTH, MENU_HEIGHT, "Game of Life - Main Menu");
    SetTargetFPS(40);

    int board_width{DEFAULT_BOARD_WIDTH};
    int board_height{DEFAULT_BOARD_HEIGHT};
    bool default_size{true};
    bool default_pattern{true};

    int select_option{0};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // START
        // CHANGE BOARD SIZE
        // CHANGE PATTERN
        // QUIT

        // CURRENT SETTINGS:
        // BOARD SIZE : XX x XX
        // PATTERN : RANDOM

        // Tekstien paikkaa ja fonttia voi muuttaa (ensimmäinen nro on leveys, toinen korkeus ja kolmas on fonttikoko, jos haluaa fonttikoon voisi laittaa myös constants.h-tiedostoon esim FONT_HEADER, FONT_TEXT osv.ja se kolmannen numeron tilalle)
        DrawText("Game of Life - Main Menu", 10, 10, 40, BLACK);
        /*DrawText("Choose an option:", 10, 100, 30, BLACK);
        DrawText("1. Start with default board size", 30, 180, 30, BLACK);
        DrawText("2. Start with custom board size", 30, 230, 30, BLACK);
        DrawText("3. Use default pattern", 30, 280, 30, BLACK);
        DrawText("4. Use random pattern", 30, 330, 30, BLACK); */

        // Draws "> " symbol to the selected option(s)
        draw_selected_option(select_option);

        EndDrawing();

        select_option = input_menu_option_selection(select_option);
    }

    if (select_option == 1)
    {
        default_size = false;
        CloseWindow();
    }
    else if (select_option == 2)
    {
        default_size = false;
        get_user_input_boardsize(board_width, board_height);
        CloseWindow();
    }
    else if (select_option == 3)
    {
        default_pattern = true;
        CloseWindow();
    }
    else if (select_option == 4)
    {
        default_pattern = false;
        CloseWindow();
    }

    // Creates a gameboard of defined board size (either user defined or default)
    Gameboard gameboard{create_board(board_width, board_height)};

    if (!default_pattern)
    {
        // Set randomized starting pattern
        randomize_starting_pattern(gameboard);
    }
    else
    {
        // Set default starting pattern
        default_starting_pattern(gameboard);
    }

    game_render_loop(gameboard);
}

void get_user_input_boardsize_selection(int &board_width, int &board_height)
{
    InitWindow(MENU_WIDTH, MENU_HEIGHT, "Game of Life - User Input");
    SetTargetFPS(40);

    bool default_size{true};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Display title and options
        DrawText("Game of Life - Board Size Selection", 10, 10, 40, BLACK); // first numbers are the coordinates (10, 10) and last number is font size (30)
        DrawText("Choose an option:", 10, 100, 30, BLACK);
        DrawText("1. Use default board size", 30, 180, 30, BLACK);
        DrawText("2. Specify board size", 30, 230, 30, BLACK);

        if (default_size)
        {
            DrawText("> ", 10, 180, 30, BLACK); // arrow to the same height as the options
        }
        else
        {
            DrawText("> ", 10, 230, 30, BLACK);
        }

        EndDrawing();

        // Check if user has pressed either up/down arrow
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN))
        {
            default_size = !default_size;
        }
        // Check if user has hit enter
        else if (IsKeyPressed(KEY_ENTER))
        {
            // If default board size is used
            if (default_size)
            {
                board_width = DEFAULT_BOARD_WIDTH;
                board_height = DEFAULT_BOARD_HEIGHT;
            }
            CloseWindow();
        }
    }
}

void get_user_input_boardsize(int &board_width, int &board_height)
{
    InitWindow(MENU_WIDTH, MENU_HEIGHT, "Game of Life - Board Size Selection");
    SetTargetFPS(40);

    while (!WindowShouldClose)
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Display the title and board size inputs
        DrawText("Game of Life - Set Width and Height", 10, 10, 40, BLACK);
        DrawText("Enter board width (10-100):", 10, 100, 30, BLACK);
        DrawText("Enter board height (10-100):", 10, 150, 30, BLACK);

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
                CloseWindow();
                break;
            }
        }
    }
}

void get_user_input_pattern(bool &random_pattern)
{
    InitWindow(MENU_WIDTH, MENU_HEIGHT, "Game of Life - Pattern Selection");
    SetTargetFPS(40);

    bool default_pattern{true};
    bool is_running{true};

    while (is_running)
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Game of Life - Pattern Selection", 10, 10, 40, BLACK);
        DrawText("Choose an option:", 10, 100, 30, BLACK);
        DrawText("1. Use default pattern", 30, 180, 30, BLACK);
        DrawText("2. Randomize pattern", 30, 230, 30, BLACK);

        if (default_pattern)
        {
            DrawText("> ", 10, 180, 30, BLACK);
        }
        else
        {
            DrawText("> ", 10, 230, 30, BLACK);
        }

        EndDrawing();

        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN))
        {
            default_pattern = !default_pattern;
        }
        else if (IsKeyPressed(KEY_ENTER))
        {
            is_running = false;
        }
    }

    if (!default_pattern)
    {
        random_pattern = true;
    }

    CloseWindow();
}
