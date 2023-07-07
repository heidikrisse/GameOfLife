// main.cpp
#include "user_ui.h"
#include "game.h"
#include "constants.h"
#include "raylib.h"

int main()
{
    // Create gameboard and set default starting pattern as default
    Gameboard gameboard{create_board(DEFAULT_BOARD_WIDTH, DEFAULT_BOARD_HEIGHT)};

    default_starting_pattern(gameboard);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game of Life - Main Menu");
    SetTargetFPS(30);

    Font text_font{LoadFontEx(FONT.c_str(), 50, NULL, 0)};

    int mouse_x{0};
    int mouse_y{0};

    int board_width{DEFAULT_BOARD_WIDTH};
    int board_height{DEFAULT_BOARD_HEIGHT};

    bool default_size{true};

    // 0 = default, 1 = random, 2 = custom
    Pattern current_pattern{default_pattern}; // Starting pattern on the board

    while (!WindowShouldClose())
    {
        // Get mouse position
        mouse_x = GetMouseX();
        mouse_y = GetMouseY();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // DrawTextEx(font, "Text to display", Vector2{x-pos, y-pos}, font size, spacing, color)
        DrawTextEx(text_font, "Game of Life - Main Menu", Vector2{10, 10}, 40, 0, BLACK);

        // Start
        if (mouse_y >= 180 && mouse_y < 230)
        {
            DrawTextEx(text_font, "Start", Vector2{30, 180}, 30, 0, RED);
            DrawTextEx(text_font, "> ", Vector2{10, 180}, 30, 0, RED); // color changes to red when mouse on top of the option
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                EndDrawing();
                game_render_loop(gameboard);
            }
        }
        else
        {
            DrawTextEx(text_font, "Start", Vector2{30, 180}, 30, 0, BLACK);
        }

        // Change board size
        if (mouse_y >= 230 && mouse_y < 280)
        {
            DrawTextEx(text_font, "Change board size", Vector2{30, 230}, 30, 0, RED);
            DrawTextEx(text_font, "> ", Vector2{10, 230}, 30, 0, RED);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                EndDrawing();
                change_board_size_menu(gameboard, board_width, board_height, current_pattern);
            }
        }
        else
        {
            DrawTextEx(text_font, "Change board size", Vector2{30, 230}, 30, 0, BLACK);
        }

        // Change pattern
        if (mouse_y >= 280 && mouse_y < 330)
        {
            DrawTextEx(text_font, "Change pattern", Vector2{30, 280}, 30, 0, RED);
            DrawTextEx(text_font, "> ", Vector2{10, 280}, 30, 0, RED);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                EndDrawing();
                current_pattern = get_user_input_pattern(gameboard);
            }
        }
        else
        {
            DrawTextEx(text_font, "Change pattern", Vector2{30, 280}, 30, 0, BLACK);
        }

        // Quit
        if (mouse_y > 330 && mouse_y < 380)
        {
            DrawTextEx(text_font, "Quit", Vector2{30, 330}, 30, 0, RED);
            DrawTextEx(text_font, "> ", Vector2{10, 330}, 30, 0, RED);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                break;
            }
        }
        else
        {
            DrawTextEx(text_font, "Quit", Vector2{30, 330}, 30, 0, BLACK);
        }

        // Draw current settings
        DrawTextEx(text_font, "Current settings:", Vector2{30, 530}, 30, 0, GRAY);
        DrawTextEx(text_font, "Board size:", Vector2{30, 580}, 30, 0, GRAY);
        DrawTextEx(text_font, std::to_string(board_width).c_str(), Vector2{400, 580}, 30, 0, GRAY);
        DrawTextEx(text_font, "x", Vector2{462, 580}, 30, 0, GRAY);
        DrawTextEx(text_font, std::to_string(board_height).c_str(), Vector2{500, 580}, 30, 0, GRAY);
        DrawTextEx(text_font, "Board pattern:", Vector2{30, 630}, 30, 0, GRAY);

        if (current_pattern == default_pattern)
        {
            DrawTextEx(text_font, "default", Vector2{400, 630}, 30, 0, GRAY);
        }
        if (current_pattern == random_pattern)
        {
            DrawTextEx(text_font, "random", Vector2{400, 630}, 30, 0, GRAY);
        }
        if (current_pattern == custom_pattern)
        {
            DrawTextEx(text_font, "custom", Vector2{400, 630}, 30, 0, GRAY);
        }

        EndDrawing();
    }

    UnloadFont(text_font);
    CloseWindow();

    return 0;
}
