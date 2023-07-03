cmake_minimum_required(VERSION 3.20)

project(GameOfLife)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

include_directories(${PROJECT_SOURCE_DIR} include)

add_subdirectory(src)
add_subdirectory(tests)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC user_ui game stdc++fs)
