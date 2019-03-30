cmake_minimum_required(VERSION 3.5)
project(arcade)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -W -Wextra")

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/core)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/games)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

file(GLOB SRCFILES *.cpp)
file(GLOB HSRCFILES *.hpp)

add_executable(arcade ${SRCFILES} ${HSRCFILES} core/main.cpp games/nibbler/Nibbler.cpp games/nibbler/Nibbler.hpp lib/Frame.hpp lib/IElement.hpp lib/AElement.hpp lib/UIRect.hpp lib/UIText.hpp lib/IApi.hpp lib/SFML/SFMLApi.cpp lib/SFML/SFMLApi.hpp core/Engine.hpp games/IGameApi.hpp core/Engine.cpp lib/ncurses/NcursesApi.hpp lib/ncurses/NcursesApi.cpp lib/Events.hpp lib/Qt/QtApi.cpp lib/Qt/QtApi.hpp lib/Qt/QtApiWindow.cpp core/EngineExceptions.hpp lib/UIExceptions.hpp core/Menu.cpp core/Menu.hpp games/solarfox/SolarFox.cpp games/solarfox/SolarFox.hpp)

target_link_libraries(arcade Qt5::Widgets Qt5::Multimedia)
