// main.cpp
#include "user_ui.h"
#include "game.h"
#include "constants.h"
#include "raylib.h"

#include <vector>

int main(void)
{
    main_menu();
    /*
    int board_width{DEFAULT_BOARD_WIDTH};
    int board_height{DEFAULT_BOARD_HEIGHT};

    // Main menu jota kutsutaan tästä (sis start with default board size/start with custom board size)


    // Prompts user to either input board size or use default board size
    get_user_input_boardsize(board_width, board_height);

    // Creates a gameboard of defined board size (either user defined or default)
    Gameboard gameboard{create_board(board_width, board_height)};

    bool random_pattern{false};

    // Get user input for pattern choice (either randomized pattern or default/demo pattern)
    get_user_input_pattern(random_pattern);

    if (random_pattern)
    {
        // Set randomized starting pattern
        randomize_starting_pattern(gameboard);
    }
    else
    {
        // Set default starting pattern
        default_starting_pattern(gameboard);
    }

    game_render_loop(gameboard); */

    return 0;
}
