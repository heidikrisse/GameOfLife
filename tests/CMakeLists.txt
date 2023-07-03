set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(unit_tests_results unit_tests.cpp)
target_link_libraries(unit_tests_results PUBLIC game)
target_include_directories(unit_tests_results PUBLIC ${CMAKE_SOURCE_DIR}/include)
