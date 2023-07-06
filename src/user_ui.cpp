// user_ui.cpp
#include "user_ui.h"
#include "raylib.h"
#include "game.h"

#include <string>
#include <iostream>
#include <vector>

// Game main menu
void main_menu()
{
    Gameboard gameboard{create_board(DEFAULT_BOARD_WIDTH, DEFAULT_BOARD_HEIGHT)};

    default_starting_pattern(gameboard);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game of Life - Main Menu");
    SetTargetFPS(30);

    Font text_font{LoadFont(FONT.c_str())};

    int mouse_x{0};
    int mouse_y{0};

    int board_width{DEFAULT_BOARD_WIDTH};
    int board_height{DEFAULT_BOARD_HEIGHT};

    bool default_size{true};

    // 0 = default, 1 = random, 2 = custom
    Pattern current_pattern{default_pattern};

    // int select_option{0};

    while (!WindowShouldClose())
    {
        mouse_x = GetMouseX();
        mouse_y = GetMouseY();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Header
        // DrawTextEx(fontti, "nimi", Vector2{x-koordinaatti, y-koordinaatti}, fontin koko, kirjaintyyli [0 = oletuskirjaintyyli], väri)
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

        bool accepted_size{board_width >= MIN_BOARD_WIDTH && board_width <= MAX_BOARD_WIDTH && board_height >= MIN_BOARD_HEIGHT && board_height <= MAX_BOARD_HEIGHT};
        if (!accepted_size && text_box_clicked)
        {
            DrawRectangleRec(text_box, YELLOW);
        }
        if (board_width >= MIN_BOARD_WIDTH && board_width <= MAX_BOARD_WIDTH && board_height >= MIN_BOARD_HEIGHT && board_height <= MAX_BOARD_HEIGHT && text_box_clicked)
        {
            DrawRectangleRec(text_box, GREEN);
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
        // DrawTextEx("Enter board height (10-333):", 10, 150, 30, BLACK);

        // if (mouse_on_text)
        // {
        //     if (letter_count < max_input_numbers)
        //     {

        //     }
        // }

        // DrawTextEx(text_font, std::to_string(board_width).c_str(), Vector2{480, 200}, 30, 0, BLACK); // same height as the enter text but little bit more right
        // DrawTextEx(text_font, "x", Vector2{540, 200}, 30, 0, BLACK);
        // DrawTextEx(text_font, std::to_string(board_height).c_str(), Vector2{575, 200}, 30, 0, BLACK);

        // Instructions for the user:
        // DrawTextEx(text_font, "Use UP/DOWN arrow keys to adjust side size", Vector2{10, 350}, 20, 0, BLACK);
        DrawTextEx(text_font, "Press ENTER to confirm the board size", Vector2{10, 410}, 20, 0, BLACK);

        EndDrawing(); // Choose the board size with arrow keys:
        // input_boardsize_selection(board_width, board_height);

        // If user hits enter, go back to main menu
        if (IsKeyPressed(KEY_ENTER))
        {
            if (board_width >= MIN_BOARD_WIDTH && board_width <= MAX_BOARD_WIDTH && board_height >= MIN_BOARD_HEIGHT && board_height <= MAX_BOARD_HEIGHT)
            {
                break;
            }
        }
    }
}

void input_boardsize_selection(int &board_width, int &board_height)
{
    // Adjust board width and height with down/up arrows:
    if (IsKeyDown(KEY_DOWN))
    {
        if (board_width > MIN_BOARD_WIDTH && board_height > MIN_BOARD_HEIGHT)
        {
            --board_height;
            --board_width;
        }
    }
    else if (IsKeyDown(KEY_UP))
    {
        if (board_width < MAX_BOARD_WIDTH && board_height < MAX_BOARD_HEIGHT)
        {
            ++board_width;
            ++board_height;
        }
    }
}

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
