// user_ui.cpp
#include "user_ui.h"
#include "raylib.h"
#include "game.h"

#include <string>
#include <iostream>
#include <vector>

void game_render_loop(Gameboard &gameboard)
{
    bool game_paused{false};
    while (!WindowShouldClose())
    {
        // Check for keyboard input P - play/pause, SPACE - evolve 1 and pause, Q - quit
        if (IsKeyPressed(KEY_SPACE))
        {
            evolve_board(gameboard);
            game_paused = true;
        }
        if (IsKeyPressed(KEY_P))
        {
            game_paused = !game_paused;
        }
        if (IsKeyPressed(KEY_Q))
        {
            return;
        }
        if (game_paused)
        {
            draw_one_evolution(gameboard);
        }
        if (!game_paused)
        {
            evolve_board(gameboard);
            draw_one_evolution(gameboard);
            WaitTime(0.5);
        }
    }
}

void print_board(const Gameboard &gameboard)
{
    float width{static_cast<float>(gameboard[0].size())}; // number of cells
    float height{static_cast<float>(gameboard.size())};   // number of cells

    float cell_width{static_cast<float>(SCREEN_WIDTH) / width}; // size of displayed cell in pix
    float cell_height{static_cast<float>(SCREEN_HEIGHT) / height};

    for (int row{0}; row < height; ++row)
    {
        for (int col{0}; col < width; ++col)
        {
            if (gameboard.at(row).at(col).is_alive)
            {
                DrawRectangle(row * cell_width, col * cell_height, cell_width - 1, cell_height - 1, BLACK);
            }
        }
    }
}

void user_defined_starting_pattern(Gameboard &gameboard)
{
    Font text_font{LoadFont(FONT.c_str())};

    // Check board width and height, or number of cells
    float board_width{static_cast<float>(gameboard[0].size())};
    float board_height{static_cast<float>(gameboard.size())};

    float cell_width{static_cast<float>(SCREEN_WIDTH) / board_width};
    float cell_height{static_cast<float>(SCREEN_HEIGHT) / board_height};

    int mouse_x{0};
    int mouse_y{0};

    clear_gameboard(gameboard);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextEx(text_font, "Q - save & quit", Vector2{10.0f, 10.0f}, 10.0f, 0.0f, DARKBLUE);
        print_board(gameboard);
        EndDrawing();

        mouse_x = GetMouseX();
        mouse_y = GetMouseY();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            // If mouse position is evenly divisible with cell_scale, subtract one to get correct index
            if (mouse_x % static_cast<int>(cell_width) == 0)
            {
                mouse_x -= 1;
            }
            if (mouse_y % static_cast<int>(cell_height) == 0)
            {
                mouse_y -= 1;
            }

            int row = static_cast<float>(mouse_x) / cell_width;
            int col = static_cast<float>(mouse_y) / cell_height;

            gameboard.at(row).at(col).is_alive = !gameboard.at(row).at(col).is_alive;
        }
        if (IsKeyPressed(KEY_Q))
        {
            break;
        }
    }
}

void draw_one_evolution(Gameboard &gameboard)
{
    Font text_font{LoadFont(FONT.c_str())};

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTextEx(text_font, "Q - quit | P - play/pause | SPACE - step", Vector2{10.0f, 10.0f}, 18.0f, 0.0f, DARKBLUE);
    print_board(gameboard);
    EndDrawing();
}

// Function to prompt user to confirm the user wants to change the board size
void change_board_size_menu(Gameboard &gameboard, int &board_width, int &board_height, Pattern &current_pattern)
{
    Font text_font{LoadFont(FONT.c_str())};

    int mouse_x{0};
    int mouse_y{0};

    while (!WindowShouldClose())
    {
        mouse_x = GetMouseX();
        mouse_y = GetMouseY();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTextEx(text_font, "Changing board size will erase current pattern!", Vector2{30, 230}, 30, 0, BLACK);
        DrawTextEx(text_font, "Continue?", Vector2{30, 280}, 30, 0, BLACK);

        // yes
        if (mouse_y >= 330 && mouse_y < 380) // yes option
        {
            DrawTextEx(text_font, "Yes", Vector2{30, 330}, 30, 0, RED);
            DrawTextEx(text_font, "> ", Vector2{10, 330}, 30, 0, RED);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                EndDrawing();
                get_user_input_boardsize(board_width, board_height);
                gameboard = create_board(board_width, board_height);
                default_starting_pattern(gameboard);
                current_pattern = default_pattern;
                break;
            }
        }
        else
        {
            DrawTextEx(text_font, "Yes", Vector2{30, 330}, 30, 0, BLACK);
        }

        // no
        if (mouse_y >= 380 && mouse_y < 430) // no option
        {
            DrawTextEx(text_font, "No", Vector2{30, 380}, 30, 0, RED);
            DrawTextEx(text_font, "> ", Vector2{10, 380}, 30, 0, RED);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                break;
            }
        }
        else
        {
            DrawTextEx(text_font, "No", Vector2{30, 380}, 30, 0, BLACK);
        }
        EndDrawing();
    }
}

// Function to get user input for the board size (width x height)
void get_user_input_boardsize(int &board_width, int &board_height)
{
    Font text_font{LoadFont(FONT.c_str())};

    int text_box_x{350};
    int text_box_y{350};
    int text_box_width{120};
    int text_box_height{30};

    Rectangle text_box{static_cast<float>(text_box_x), static_cast<float>(text_box_y), static_cast<float>(text_box_width), static_cast<float>(text_box_height)};
    bool mouse_on_text{false};
    bool text_box_clicked{false};

    const int max_input_numbers{3};
    char board_size_input[max_input_numbers + 1]{"\0"}; // One extra space required for null terminator
    int letter_count{0};

    while (!WindowShouldClose())
    {

        if (CheckCollisionPointRec(GetMousePosition(), text_box))
        {
            mouse_on_text = true;
        }
        else
        {
            mouse_on_text = false;
        }

        if (mouse_on_text && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            text_box_clicked = true;
        }
        if (!mouse_on_text && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            text_box_clicked = false;
        }

        if (mouse_on_text)
        {
            // Set the mouse cursor to an I-beam
            SetMouseCursor(MOUSE_CURSOR_IBEAM);
        }
        else
        {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }

        if (text_box_clicked)
        {
            // Get char pressed on the queue
            int key{GetCharPressed()};

            while (key > 0)
            {
                if ((key >= 48) && (key <= 57) && (letter_count < max_input_numbers))
                {
                    board_size_input[letter_count] = static_cast<char>(key);
                    board_size_input[letter_count + 1] = '\0';
                    ++letter_count;
                }

                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE) && letter_count > 0)
            {
                --letter_count;
                board_size_input[letter_count] = '\0';
            }
        }

        board_width = atoi(board_size_input);
        board_height = board_width;

        BeginDrawing();

        ClearBackground(RAYWHITE);
        // Display the title and board size inputs
        DrawTextEx(text_font, "Game of Life - Set Board Size", Vector2{10.0, 10.0}, 40, 0, BLACK);
        DrawTextEx(text_font, "Enter board size (20-250):", Vector2{10.0, 350.0}, 30, 0, BLACK);

        if (accepted_size(board_width, board_height) && text_box_clicked)
        {
            DrawRectangleRec(text_box, GREEN);
        }
        else if (!accepted_size(board_width, board_height) && text_box_clicked)
        {
            DrawRectangleRec(text_box, RED);
        }
        else
        {
            DrawRectangleRec(text_box, WHITE);
        }

        if (mouse_on_text)
        {
            DrawRectangleLines(text_box_x, text_box_y, text_box_width, text_box_height, BLACK);
        }
        else
        {
            DrawRectangleLines(text_box_x, text_box_y, text_box_width, text_box_height, GRAY);
        }
        DrawTextEx(text_font, board_size_input, Vector2{static_cast<float>(text_box_x), static_cast<float>(text_box_y)}, 30, 0, BLACK);

        DrawTextEx(text_font, "Press ENTER to confirm the board size", Vector2{10, 410}, 20, 0, BLACK);

        EndDrawing();

        // If user hits enter, go back to main menu
        if (IsKeyPressed(KEY_ENTER))
        {
            if (accepted_size(board_width, board_height))
            {
                break;
            }
        }
    }
    SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}

// Function to choose pattern (default, randomized or custom)
Pattern get_user_input_pattern(Gameboard &gameboard)
{
    Font text_font{LoadFont(FONT.c_str())};

    int mouse_y{0};
    int mouse_x{0};

    Pattern current_pattern{default_pattern};

    while (!WindowShouldClose())
    {
        mouse_y = GetMouseY();
        mouse_x = GetMouseX();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTextEx(text_font, "Pattern Selection", Vector2{10.0f, 10.0f}, 40.0f, 0.0f, BLACK);

        // Use default pattern
        if (mouse_y >= 180 && mouse_y < 230) // use default
        {
            DrawTextEx(text_font, "Use default pattern", Vector2{30.0f, 180.0f}, 30.0f, 0.0f, RED);
            DrawTextEx(text_font, "> ", Vector2{10.0f, 180.0f}, 30.0f, 0.0f, RED);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                current_pattern = default_pattern;
                default_starting_pattern(gameboard);
                EndDrawing();
                break;
            }
        }
        else
        {
            DrawTextEx(text_font, "Use default pattern", Vector2{30.0f, 180.0f}, 30.0f, 0.0f, BLACK);
        }

        // Use random pattern
        if (mouse_y >= 230 && mouse_y < 280) // use random
        {
            DrawTextEx(text_font, "Use random pattern", Vector2{30.0f, 230.0f}, 30.0f, 0.0f, RED);
            DrawTextEx(text_font, "> ", Vector2{10.0f, 230.0f}, 30.0f, 0.0f, RED);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                current_pattern = random_pattern;
                randomize_starting_pattern(gameboard);
                EndDrawing();
                break;
            }
        }
        else
        {
            DrawTextEx(text_font, "Use random pattern", Vector2{30.0f, 230.0f}, 30.0f, 0.0f, BLACK);
        }

        // Create custom pattern
        if (mouse_y >= 280 && mouse_y < 330)
        {
            DrawTextEx(text_font, "Create custom pattern", Vector2{30.0f, 280.0f}, 30.0f, 0.0f, RED);
            DrawTextEx(text_font, "> ", Vector2{10.0f, 280.0f}, 30.0f, 0.0f, RED);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                current_pattern = custom_pattern;
                user_defined_starting_pattern(gameboard);
                EndDrawing();
                break;
            }
        }
        else
        {
            DrawTextEx(text_font, "Create custom pattern", Vector2{30.0f, 280.0f}, 30.0f, 0.0f, BLACK);
        }

        EndDrawing();
    }

    return current_pattern;
}
