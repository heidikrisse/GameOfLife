// game.cpp
#include "game.h"
#include "constants.h"
#include <iostream>
#include <vector>
#include <random>

// Function counts number of cell neighbors alive
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
            // Check that we're not outside the gameboard, and that we're not counting the current cell
            if ((neighbor_col < 0 || neighbor_col >= static_cast<int>(gameboard.at(0).size())) ||
                (neighbor_row == row && neighbor_col == col))
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

// A function that returns a bool if the cell should be alive or dead next evolution
bool update_cell(const Cell &cell)
{
    // If cell is alive
    if (cell.is_alive)
    {
        // Cell stays alive if 2 or 3 neighbors are alive, otherwise cell dies
        if (cell.alive_neighbors == 2 || cell.alive_neighbors == 3)
        {
            return true;
        }
        return false;
    }
    // If cell initial state is dead
    else
    {
        // Cell becomes alive if 3 neighbor cells alive
        if (cell.alive_neighbors == 3)
        {
            return true;
        }
        return false;
    }
}

// Function makes an evolution on the board
void evolve_board(Gameboard &gameboard)
{
    // Make copy of gameboard
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
    // The "copperhead" pattern hardcoded as default pattern
    // in the middle of gameboard that can be scaled

    clear_gameboard(gameboard);

    int width = static_cast<int>(gameboard[0].size());
    int height = static_cast<int>(gameboard.size());

    int mh{height / 2}; // middle height
    int mw{width / 2};  // middle width

    // Set the cell of the copperheadpattern to alive
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

void randomize_starting_pattern(Gameboard &gameboard)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 1); // 0 = false, 1 = true

    // Randomly set each cell to alive or dead
    for (auto &row : gameboard)
    {
        for (auto &cell : row)
        {
            cell.is_alive = dist(gen);
        }
    }
}

Gameboard create_board(int board_width, int board_height)
{
    // If the provided size is not accepted, use the default size
    if (!accepted_size(board_width, board_height))
    {
        board_width = DEFAULT_BOARD_WIDTH;
        board_height = DEFAULT_BOARD_HEIGHT;
    }

    // Create the gameboard with the specified width and height
    Gameboard gameboard(board_height, std::vector<Cell>(board_width));

    return gameboard;
}

bool accepted_size(int board_width, int board_height)
{
    // Check if the provided width and height are within the accepted range
    return board_width >= MIN_BOARD_WIDTH && board_width <= MAX_BOARD_WIDTH &&
           board_height >= MIN_BOARD_HEIGHT && board_height <= MAX_BOARD_HEIGHT;
}
