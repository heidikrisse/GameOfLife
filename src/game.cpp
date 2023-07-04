#include "game.h"
#include "constants.h"
#include "raylib.h"

#include <iostream>
#include <vector>

void game_render_loop(const Gameboard &gameboard)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] example - basic window");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        print_board(gameboard);

        EndDrawing();
    }

    CloseWindow();
}

int count_cell_alive_neighbors(const Gameboard &gameboard, int row, int col)
{
    int cell_alive_neighbors{0};

    // Loop through the neighboring cells
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

void update_cell(Cell &cell)
{
    // If cell is alive
    if (cell.is_alive)
    {
        // Cell becomes dead (is_alive = false) if < 2 or > 3 neighbors are alive, otherwise cell state remains the same
        if (cell.alive_neighbors < 2 || cell.alive_neighbors > 3)
        {
            cell.is_alive = false;
        }
    }
    // If cell is dead
    else
    {
        // Cell becomes alive (is_alive = true) if 3 neighbor cells alive, otherwise cell state remains the same
        if (cell.alive_neighbors == 3)
        {
            cell.is_alive = true;
        }
    }
}

void evolve_board(Gameboard &gameboard)
{
    std::size_t height{gameboard.size()};
    std::size_t width{gameboard.at(0).size()};

    for (std::size_t row{0}; row < height; ++row)
    {
        for (std::size_t col{0}; col < width; ++col)
        {
            gameboard.at(row).at(col).alive_neighbors = count_cell_alive_neighbors(gameboard, row, col);

            update_cell(gameboard.at(row).at(col));
        }
    }
}

// void randomize_starting_pattern()
// {
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_distribution<int> dist(0, 1); // 0 = false, 1 = true
// }

// void print_board(const Gameboard &gameboard)
// {
//     std::size_t height{gameboard.size()};
//     std::size_t width{gameboard[0].size()};

//     // Top border line of the board:
//     for (std::size_t row{0}; row < width + 2; ++row)
//     {
//         std::cout << '_';
//     }
//     std::cout << '\n';

//     // Middle of the board boarders
//     for (std::size_t row{0}; row < height; ++row)
//     {
//         std::cout << '|'; // left border

//         for (std::size_t col{0}; col < width; ++col)
//         {
//             if (gameboard.at(row).at(col).is_alive)
//             {
//                 std::cout << 'O'; // O = cell alive/full
//             }
//             else
//             {
//                 std::cout << ' ';
//             }
//         }

//         std::cout << "|\n"; // right border
//     }

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

Gameboard create_board(int width, int height)
{
    if (width > 0 && height > 0)
    {
        Gameboard gameboard(height, std::vector<Cell>(width));

        return gameboard;
    }
    else
    {
        Gameboard gameboard(10, std::vector<Cell>(10));
        std::cout << "Created a default gameboard 10x10.\n";

        return gameboard;
    }
}
