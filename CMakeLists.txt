cmake_minimum_required(VERSION 3.5)
project(arcade)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -W -Wextra")

file(GLOB SRCFILES *.cpp)
file(GLOB HSRCFILES *.hpp)

add_executable(arcade ${SRCFILES} ${HSRCFILES} core/main.cpp include/IGraphAPI.hpp lib/SFML/SFMLGraphAPI.cpp include/SFMLGraphAPI.hpp games/test/test.cpp)
