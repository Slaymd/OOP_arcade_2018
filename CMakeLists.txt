cmake_minimum_required(VERSION 3.5)
project(arcade)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -W -Wextra")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/core)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/games)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

file(GLOB SRCFILES *.cpp)
file(GLOB HSRCFILES *.hpp)

add_executable(arcade ${SRCFILES} ${HSRCFILES} core/main.cpp games/test/test.cpp games/test/test.cpp games/nibbler/Nibbler.cpp games/nibbler/Nibbler.hpp lib/Frame.hpp lib/IElement.hpp lib/AElement.hpp lib/UIRect.hpp lib/UIText.hpp lib/IApi.hpp lib/SFML/SFMLApi.cpp lib/SFML/SFMLApi.hpp core/Loader.cpp core/Engine.hpp games/IGameApi.hpp core/Loader.cpp core/Engine.cpp lib/ncurses/NcursesApi.hpp lib/ncurses/NcursesApi.cpp lib/Events.hpp)