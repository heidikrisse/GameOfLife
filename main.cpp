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

    // Gameboard gameboard{create_board(20, 20)};

    // gameboard.at(8).at(10).is_alive = true;
    // gameboard.at(9).at(10).is_alive = true;
    // gameboard.at(10).at(10).is_alive = true;

    game_render_loop(gameboard);

    return 0;
}
