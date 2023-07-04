#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "game.h"

#include <stdexcept>
#include <vector>

TEST_CASE("Testing gameboard")
{

    SUBCASE("Testing creation of gameboard")
    {
        Gameboard gameboard{create_board(15, 15)};
        gameboard.at(7).at(5).is_alive = true;

        CHECK(gameboard.at(0).at(0).is_alive == false);
        CHECK(gameboard.at(14).at(14).is_alive == false);
        CHECK(gameboard.at(7).at(5).is_alive == true);
    }
    SUBCASE("Testing creation of incorrectly sized gameboard")
    {
        Gameboard incorrectly_sized_gameboard{create_board(-1, 2)};
        CHECK(incorrectly_sized_gameboard.at(0).size() == 10);
        CHECK(incorrectly_sized_gameboard.size() == 10);
        CHECK_THROWS_AS(incorrectly_sized_gameboard.at(11).at(2), const std::exception &);
    }
}

TEST_CASE("Test cell update functions")
{
    SUBCASE("Count cell alive neighbors")
    {
        Gameboard gameboard{create_board(15, 15)};
        gameboard.at(5).at(5).is_alive = true;
        gameboard.at(5).at(6).is_alive = true;
        gameboard.at(5).at(7).is_alive = true;
        
        CHECK(count_cell_alive_neighbors(gameboard, 5, 6) == 2);
        CHECK(count_cell_alive_neighbors(gameboard, 5, 5) == 1);
        CHECK(count_cell_alive_neighbors(gameboard, 0, 0) == 0);
        CHECK(count_cell_alive_neighbors(gameboard, 5, 7) == 1);
        CHECK(count_cell_alive_neighbors(gameboard, 6, 6) == 3);
        CHECK(count_cell_alive_neighbors(gameboard, 4, 6) == 3);
    }

    SUBCASE("Update cell")
    {
        Gameboard gameboard{create_board(15, 15)};
        gameboard.at(5).at(5).is_alive = true;
        gameboard.at(5).at(6).is_alive = true;
        gameboard.at(5).at(7).is_alive = true;
        gameboard.at(5).at(5).alive_neighbors = 1;
        gameboard.at(5).at(6).alive_neighbors = 2;
        gameboard.at(5).at(7).alive_neighbors = 1;
        gameboard.at(4).at(6).alive_neighbors = 3;
        gameboard.at(6).at(6).alive_neighbors = 3;

        CHECK(update_cell(gameboard.at(0).at(0)) == false);
        CHECK(update_cell(gameboard.at(5).at(5)) == false);
        CHECK(update_cell(gameboard.at(5).at(6)) == true);
        CHECK(update_cell(gameboard.at(5).at(7)) == false);
        CHECK(update_cell(gameboard.at(4).at(6)) == true);
        CHECK(update_cell(gameboard.at(6).at(6)) == true);
    }

    SUBCASE("Evolve board")
    {
        Gameboard gameboard{create_board(15, 15)};
        gameboard.at(5).at(5).is_alive = true;
        gameboard.at(5).at(6).is_alive = true;
        gameboard.at(5).at(7).is_alive = true;

        evolve_board(gameboard);

        CHECK(gameboard.at(0).at(0).is_alive == false); // doesn't change
        CHECK(gameboard.at(5).at(5).is_alive == false);
        CHECK(gameboard.at(5).at(6).is_alive == true);
        CHECK(gameboard.at(5).at(7).is_alive == false);

        evolve_board(gameboard);

        CHECK(gameboard.at(0).at(0).is_alive == false); // doesn't change
        CHECK(gameboard.at(5).at(5).is_alive == true);
        CHECK(gameboard.at(5).at(6).is_alive == true);
        CHECK(gameboard.at(5).at(7).is_alive == true);
    }
}

// TEST_CASE(""){

// }
