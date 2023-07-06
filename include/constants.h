/* constants.h
 *
 * Constant values used in Game of Life program
 * */
#ifndef CONSTANTS_H
#define CONSTANTS_H

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
constexpr int MIN_BOARD_WIDTH{10};
constexpr int MIN_BOARD_HEIGHT{10};

// Margin for displaying instruction text (quit, step, play/pause)
constexpr int CONTROL_MARGIN{10};

#endif
