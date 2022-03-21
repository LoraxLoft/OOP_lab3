cmake_minimum_required(VERSION 3.15)
project(Segundo)

set(CMAKE_CXX_STANDARD 14)
find_package(SFML 2.5 COMPONENTS system window graphics)

add_executable(Segundo main.cpp jarvis.h geometry.h sort.h algo.h frame.h graham.h)
target_link_libraries(Segundo sfml-system sfml-window sfml-graphics)