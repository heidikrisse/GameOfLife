#include "game.h"
#include "constants.h"
#include "raylib.h"
#include <algorithm> // for std::copy
#include <iostream>
#include <vector>

void game_render_loop(Gameboard &gameboard)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game of Life");

    SetTargetFPS(40); // FPS = frames per second

    bool paused{false};
    bool step{false};

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_P))
        {
            paused = !paused;
        }
        else if (IsKeyPressed(KEY_SPACE))
        {
            step = true;
        }
        else if (IsKeyPressed(KEY_Q))
        {
            break;
        }

        if (!paused || step)
        {
            draw_one_evolution(gameboard);
            step = false;
        }
    }

    CloseWindow();
}

void draw_one_evolution(Gameboard &gameboard)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Q - quit | P - pause | SPACE - step", 10, 10, 10, DARKGRAY);
    print_board(gameboard);
    evolve_board(gameboard);
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

    std::size_t height{gameboard.size()};
    std::size_t width{gameboard.at(0).size()};

    for (std::size_t row{0}; row < height; ++row)
    {
        for (std::size_t col{0}; col < width; ++col)
        {
            // Calculates the number of neighbors alive from the copy, which stays unmodified
            copy_of_board.at(row).at(col).alive_neighbors = count_cell_alive_neighbors(copy_of_board, row, col);

            // Updates the original board according to the number of neighbors alive in the
            gameboard.at(row).at(col).is_alive = update_cell(copy_of_board.at(row).at(col));
        }
    }
}

// void randomize_starting_pattern()
// {
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_distribution<int> dist(0, 1); // 0 = false, 1 = true
// }

void print_board(const Gameboard &gameboard)
{
    std::size_t height{gameboard.size()};
    std::size_t width{gameboard[0].size()};

    int scaled_width{SCREEN_WIDTH / static_cast<int>(width)};
    int scaled_height{SCREEN_HEIGHT / static_cast<int>(height)};

    for (std::size_t row{0}; row < height; ++row)
    {
        for (std::size_t col{0}; col < width; ++col)
        {
            if (gameboard.at(row).at(col).is_alive)
            {
                DrawRectangle(row * scaled_width, col * scaled_height, scaled_width - 1, scaled_height - 1, BLACK);
            }
        }
    }
}

Gameboard create_board(int board_width, int board_height)
{
    if (board_width <= 0 || board_width > 100 || board_height <= 0 || board_height > 100)
    {
        board_width = DEFAULT_BOARD_WIDTH;
        board_height = DEFAULT_BOARD_HEIGHT;

        std::cout << "Creating a default gameboard " << DEFAULT_BOARD_WIDTH << "x" << DEFAULT_BOARD_HEIGHT << "...\n";
    }

    Gameboard gameboard(board_height, std::vector<Cell>(board_width));

    return gameboard;
}
