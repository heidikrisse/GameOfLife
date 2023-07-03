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

    SUBCASE("Print board")
    {
        Gameboard gameboard{create_board(15, 15)};

        for (std::size_t col{0}; col < gameboard.size(); ++col)
        {
            gameboard.at(5).at(col).is_alive = true;
        }

        print_board(gameboard);
    }
}

TEST_CASE("Test cell update functions")
{
    SUBCASE("Count cell alive neighbors")
    {
        Gameboard gameboard{create_board(15, 15)};
        }
}

// TEST_CASE(""){

// }
