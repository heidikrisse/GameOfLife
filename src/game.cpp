// game.cpp
#include "game.h"
#include "constants.h"
#include "raylib.h"

#include <iostream>
#include <vector>
#include <random>

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

void draw_one_evolution(Gameboard &gameboard)
{
    Font text_font{LoadFont(FONT.c_str())};

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTextEx(text_font, "Q - quit | P - play/pause | SPACE - step", Vector2{10.0f, 10.0f}, 10.0f, 0.0f, DARKBLUE);
    print_board(gameboard);
    EndDrawing();
}

int count_cell_alive_neighbors(const Gameboard &gameboard, int row, int col)
{
    int cell_alive_neighbors{0};

    // Loop through the neighboring gameboard.at(row).at(col)s
    for (int neighbor_row{row - 1}; neighbor_row <= row + 1; ++neighbor_row)
    {
        if (neighbor_row < 0 || neighbor_row >= static_cast<int>(gameboard.size()))
        {
            continue;
        }
        for (int neighbor_col{col - 1}; neighbor_col <= col + 1; ++neighbor_col)
        {
            if ((neighbor_col < 0 || neighbor_col >= static_cast<int>(gameboard.at(0).size())) || (neighbor_row == row && neighbor_col == col))
            {
                continue;
            }
            if (gameboard.at(neighbor_row).at(neighbor_col).is_alive)
            {
                ++cell_alive_neighbors;
            }
        }
    }
    return cell_alive_neighbors;
}

bool update_cell(const Cell &cell)
{
    // If cell is alive
    if (cell.is_alive)
    {
        // Cell becomes dead (is_alive = false) if < 2 or > 3 neighbors are alive, otherwise cell state remains the same
        if (cell.alive_neighbors < 2 || cell.alive_neighbors > 3)
        {
            return false;
        }
        return true;
    }
    // If cell is dead
    else
    {
        // Cell becomes alive (is_alive = true) if 3 neighbor cells alive, otherwise cell state remains the same
        if (cell.alive_neighbors == 3)
        {
            return true;
        }
        return false;
    }
}

void evolve_board(Gameboard &gameboard)
{
    Gameboard copy_of_board{gameboard};

    int height{static_cast<int>(gameboard.size())};
    int width{static_cast<int>(gameboard[0].size())};

    for (int row{0}; row < height; ++row)
    {
        for (int col{0}; col < width; ++col)
        {
            // Calculates the number of neighbors alive from the copy, which stays unmodified
            copy_of_board.at(row).at(col).alive_neighbors = count_cell_alive_neighbors(copy_of_board, row, col);

            // Updates the original board according to the number of neighbors alive in the
            gameboard.at(row).at(col).is_alive = update_cell(copy_of_board.at(row).at(col));
        }
    }
}

void clear_gameboard(Gameboard &gameboard)
{
    for (auto &row : gameboard)
    {
        for (auto &cell : row)
        {
            cell.is_alive = false;
        }
    }
}

void default_starting_pattern(Gameboard &gameboard)
{
    clear_gameboard(gameboard);

    int width = static_cast<int>(gameboard[0].size());
    int height = static_cast<int>(gameboard.size());

    int mh{height / 2}; // middle height
    int mw{width / 2};  // middle width

    gameboard.at(mw - 6).at(mh).is_alive = true;
    gameboard.at(mw - 6).at(mh + 1).is_alive = true;
    gameboard.at(mw - 5).at(mh).is_alive = true;
    gameboard.at(mw - 5).at(mh + 1).is_alive = true;
    gameboard.at(mw - 3).at(mh - 1).is_alive = true;
    gameboard.at(mw - 3).at(mh).is_alive = true;
    gameboard.at(mw - 3).at(mh + 1).is_alive = true;
    gameboard.at(mw - 3).at(mh + 2).is_alive = true;
    gameboard.at(mw - 2).at(mh - 2).is_alive = true;
    gameboard.at(mw - 2).at(mh - 1).is_alive = true;
    gameboard.at(mw - 2).at(mh + 2).is_alive = true;
    gameboard.at(mw - 2).at(mh + 3).is_alive = true;
    gameboard.at(mw - 1).at(mh - 3).is_alive = true;
    gameboard.at(mw - 1).at(mh + 4).is_alive = true;
    gameboard.at(mw + 1).at(mh - 3).is_alive = true;
    gameboard.at(mw + 1).at(mh + 4).is_alive = true;
    gameboard.at(mw + 2).at(mh - 3).is_alive = true;
    gameboard.at(mw + 2).at(mh - 1).is_alive = true;
    gameboard.at(mw + 2).at(mh + 2).is_alive = true;
    gameboard.at(mw + 2).at(mh + 4).is_alive = true;
    gameboard.at(mw + 3).at(mh).is_alive = true;
    gameboard.at(mw + 3).at(mh + 1).is_alive = true;
    gameboard.at(mw + 4).at(mh).is_alive = true;
    gameboard.at(mw + 4).at(mh + 1).is_alive = true;
    gameboard.at(mw + 5).at(mh - 2).is_alive = true;
    gameboard.at(mw + 5).at(mh - 1).is_alive = true;
    gameboard.at(mw + 5).at(mh + 2).is_alive = true;
    gameboard.at(mw + 5).at(mh + 3).is_alive = true;
}

void user_defined_starting_pattern(Gameboard &gameboard)
{
    Font text_font{LoadFont(FONT.c_str())};

    // Check board width and height, or number of cells
    int board_width{static_cast<int>(gameboard[0].size())};
    int board_height{static_cast<int>(gameboard.size())};

    int cell_width{SCREEN_WIDTH / board_width};
    int cell_height{SCREEN_HEIGHT / board_height};

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
            if (mouse_x % cell_width == 0)
            {
                mouse_x -= 1;
            }
            if (mouse_y % cell_height == 0)
            {
                mouse_y -= 1;
            }

            int row = mouse_x / cell_width;
            int col = mouse_y / cell_height;

            gameboard.at(row).at(col).is_alive = !gameboard.at(row).at(col).is_alive;
        }
        if (IsKeyPressed(KEY_Q))
        {
            break;
        }
    }
}

void randomize_starting_pattern(Gameboard &gameboard)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 1); // 0 = false, 1 = true

    for (auto &row : gameboard)
    {
        for (auto &cell : row)
        {
            cell.is_alive = dist(gen);
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

Gameboard create_board(int board_width, int board_height)
{
    if (board_width < MIN_BOARD_WIDTH || board_width > MAX_BOARD_WIDTH || board_height < MIN_BOARD_HEIGHT || board_height > MAX_BOARD_WIDTH)
    {
        board_width = DEFAULT_BOARD_WIDTH;
        board_height = DEFAULT_BOARD_HEIGHT;
    }

    Gameboard gameboard(board_height, std::vector<Cell>(board_width));

    return gameboard;
}
