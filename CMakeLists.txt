cmake_minimum_required(VERSION 3.0.0)
project(snake-console VERSION 0.1.0)

include(CTest)
enable_testing()

add_definitions(-std=c++11)
add_executable(snake-console
    src/main.cpp
    src/snake.cpp
    src/frame.cpp
    src/game.cpp
    src/const.cpp
    src/keyboard.cpp
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
