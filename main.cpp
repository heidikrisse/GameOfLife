// main.cpp
#include "user_ui.h"
#include "game.h"
#include "constants.h"
#include "raylib.h"

#include <vector>
int main(void)
{
    int board_width{DEFAULT_BOARD_WIDTH};
    int board_height{DEFAULT_BOARD_HEIGHT};

    get_user_input_boardsize(board_width, board_height);

    Gameboard gameboard{create_board(board_width, board_height)};

    bool random_pattern{false};

    // Get user input for pattern choice
    get_user_input_pattern(random_pattern);

    game_render_loop(gameboard, random_pattern);

    // game_render_loop(gameboard);

    return 0;
}
