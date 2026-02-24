cmake_minimum_required(VERSION 3.16)
project(SudokuPlusPlus)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Raylib
include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
)
FetchContent_MakeAvailable(raylib)

set(SOURCE_FILES src/main.cpp src/shuffle_board.cpp src/sudoku_grid.cpp src/sudoku_generator.cpp src/sudoku_solver.cpp src/gui/game.cpp src/random_gen.cpp)

include_directories(include)

add_executable(SudokuPlusPlus ${SOURCE_FILES})

target_link_libraries(SudokuPlusPlus raylib)

add_custom_target(run
    COMMAND ./SudokuPlusPlus
    DEPENDS SudokuPlusPlus
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})