// user_ui.cpp
#include "user_ui.h"
#include "raylib.h"
#include "constants.h"

#include <string>
#include <iostream>

// TODO: Ikkunan leveyttä ja korkeutta voi lisää säätää, samoin tekstien paikkaa ja fonttia (ensimmäinen nro on leveys, toinen korkeus ja kolmas on fontti)

void get_user_input_boardsize(int &board_width, int &board_height)
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

    // Else close previous window and create a new window to choose board size
    else
    {
        CloseWindow();
        InitWindow(1000, 500, "Game of Life - Board Size Selection");
        SetTargetFPS(40);

        bool is_valid_size{false};

        // Loop until valid board size
        while (!is_valid_size)
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

            // Adjust board size with arrow keys:

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

            // Enter to confirm selection
            else if (IsKeyPressed(KEY_ENTER))
            {
                // Check if board width and height > 10 and <= 100
                if (board_width >= MIN_BOARD_WIDTH && board_width <= MAX_BOARD_WIDTH && board_height >= MIN_BOARD_HEIGHT && board_height <= MAX_BOARD_HEIGHT)
                {
                    is_valid_size = true; // valid board size
                }
            }
        }
    }

    CloseWindow();
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
