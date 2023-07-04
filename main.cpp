// main.cpp
#include "user_ui.h"
#include "game.h"
#include "constants.h"
#include "raylib.h"

#include <vector>
int main(void)
{

    Gameboard gameboard{create_board(20, 20)};

    gameboard.at(4).at(2).is_alive = true;
    gameboard.at(5).at(2).is_alive = true;
    gameboard.at(10).at(10).is_alive = true;

    game_render_loop(gameboard);

    return 0;
}
