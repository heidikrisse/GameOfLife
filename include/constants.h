/* constants.h
 *
 * Constant values used in Game of Life program
 * */
#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "raylib.h"

#include <string>

// Game screen width and height
inline constexpr int SCREEN_WIDTH{800};
inline constexpr int SCREEN_HEIGHT{800};

// Default / demo board width and height
constexpr int DEFAULT_BOARD_WIDTH{100};
constexpr int DEFAULT_BOARD_HEIGHT{100};

// Max board width and height
constexpr int MAX_BOARD_WIDTH{250};
constexpr int MAX_BOARD_HEIGHT{250};

// Min board width and height
constexpr int MIN_BOARD_WIDTH{20};
constexpr int MIN_BOARD_HEIGHT{20};

enum Pattern
{
    default_pattern,
    random_pattern,
    custom_pattern
};

// Font
const std::string FONT{"../fonts/VT323-Regular.ttf"};

#endif
