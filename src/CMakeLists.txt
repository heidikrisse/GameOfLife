add_library(user_ui STATIC user_ui.cpp)
add_library(game STATIC game.cpp)
target_include_directories(game PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(user_ui PUBLIC ${CMAKE_SOURCE_DIR}/include)

