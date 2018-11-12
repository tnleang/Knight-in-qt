cmake_minimum_required(VERSION 3.9)
project(knight_tour)

set(CMAKE_CXX_STANDARD 11)

add_executable(knight_tour
        main.cpp
        tour.h
        whereiam.h tour.cpp)
