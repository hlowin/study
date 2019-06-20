cmake_minimum_required(VERSION 2.8)

# add_definitions(-std=c++11)

project( project )

add_executable( project CalcTest.cpp CalcTest.h main.cpp )

# SET(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "limited configs" FORCE)

# add_definitions(-DWITH_SOMELIB)