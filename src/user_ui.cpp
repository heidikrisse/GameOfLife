// user_ui.cpp
#include "user_ui.h"
#include "raylib.h"
#include "constants.h"

#include <string>
#include <iostream>

// Start with default pattern or random pattern (or user-defined?)

// TODO: Ikkunan leveyttä ja korkeutta voi lisää säätää, samoin tekstien paikkaa ja fonttia (ensimmäinen nro on leveys, toinen korkeus ja kolmas on fontti)

void get_user_input_boardsize(int &board_width, int &board_height)
{
    // width x height = 600 x 300
    InitWindow(700, 300, "Game of Life - User Input");
    SetTargetFPS(40);

    bool default_size{true};
    bool is_running{true};

    while (is_running)
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Display title and options
        DrawText("Game of Life - User Input", 10, 10, 40, BLACK); // first numbers are the coordinates (10, 10) and last number is font size (30)
        DrawText("Choose an option:", 10, 70, 30, BLACK);
        DrawText("1. Use default board size", 30, 120, 20, BLACK);
        DrawText("2. Specify board size", 30, 150, 20, BLACK);

        if (default_size)
        {
            DrawText("> ", 10, 120, 20, BLACK); // arrow to the same height as the options
        }
        else
        {
            DrawText("> ", 10, 150, 20, BLACK);
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
            is_running = false;
        }
    }

    // If default board size is used
    if (default_size)
    {
        board_width = DEFAULT_BOARD_WIDTH;
        board_height = DEFAULT_BOARD_HEIGHT;
    }
    // Else close previous window and create a new window to choose board size
    else
    {
        CloseWindow();
        InitWindow(700, 500, "Game of Life - Board Size");
        SetTargetFPS(40);

        bool is_valid_size{false};

        // Loop until valid board size
        while (!is_valid_size)
        {
            BeginDrawing();

            ClearBackground(RAYWHITE);

            // Display the title and board size inputs
            DrawText("Game of Life - Board Size", 10, 10, 40, BLACK);
            DrawText("Enter board width (1-100):", 10, 90, 20, BLACK);
            DrawText("Enter board height (1-100):", 10, 130, 20, BLACK);

            DrawText(std::to_string(board_width).c_str(), 290, 90, 20, BLACK); // same height as the enter text but little bit more right
            DrawText(std::to_string(board_height).c_str(), 310, 130, 20, BLACK);

            // Instructions for the user:
            DrawText("Use UP/DOWN arrow keys to adjust width", 10, 200, 15, BLACK);
            DrawText("Use LEFT/RIGHT arrow keys to adjust height", 10, 230, 15, BLACK);
            DrawText("Press ENTER to confirm the board size", 10, 260, 15, BLACK);

            EndDrawing();

            // Adjust board size with arrow keys:

            // Adjust board width with down/up arrows:
            if (IsKeyPressed(KEY_DOWN))
            {
                if (board_width > 1)
                    --board_width;
            }
            else if (IsKeyPressed(KEY_UP))
            {
                if (board_width < 100)
                    ++board_width;
            }

            // Adjust board height with right/left arrows
            else if (IsKeyPressed(KEY_RIGHT))
            {
                if (board_height < 100)
                    ++board_height;
            }
            else if (IsKeyPressed(KEY_LEFT))
            {
                if (board_height > 1)
                    --board_height;
            }

            // Enter to confirm selection
            else if (IsKeyPressed(KEY_ENTER))
            {
                // Chech if board width and height > 0 and <= 100
                if (board_width > 0 && board_width <= 100 && board_height > 0 && board_height <= 100)
                {
                    is_valid_size = true; // valid board size
                }
            }
        }
    }

    CloseWindow();
}
