cmake_minimum_required(VERSION 3.12)
project(GeneticAlg)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(GeneticAlg
        globales.h
        includes.h
        main.cpp)
