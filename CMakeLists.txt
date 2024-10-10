cmake_minimum_required(VERSION 3.29)
project(ConwayGameOfLifeAssignment)

set(CMAKE_CXX_STANDARD 20)

add_executable(ConwayGameOfLifeAssignment main.cpp
        randomBoardGenerator.cpp
        randomBoardGenerator.h)
