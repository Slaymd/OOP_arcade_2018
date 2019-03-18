cmake_minimum_required(VERSION 3.5)
project(arcade)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -W -Wextra -I./lib")

file(GLOB SRCFILES *.cpp)
file(GLOB HSRCFILES *.hpp)

add_executable(arcade ${SRCFILES} ${HSRCFILES} core/main.cpp include/IGraphAPI.hpp lib/SFML/SFMLGraphAPI.cpp include/SFMLGraphAPI.hpp games/test/test.cpp games/test/test.cpp games/Nibbler/nibbler.cpp games/Nibbler/nibbler.hpp lib/Frame.hpp lib/IElement.hpp lib/AElement.hpp lib/UIRect.hpp lib/UIText.hpp lib/IApi.hpp lib/SFML/SFMLApi.cpp lib/SFMLApi.hpp core/Loader.cpp core/core.cpp core/core.hpp games/IGameApi.hpp)
