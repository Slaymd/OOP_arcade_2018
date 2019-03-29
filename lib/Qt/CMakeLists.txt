cmake_minimum_required(VERSION 3.5)

project (arcade-qt)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -fPIC")

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

add_library(arcade-qt SHARED QtApi.hpp QtApi.cpp QtApiWindow.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC TRUE)
set_target_properties(arcade-qt PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/..")
set_target_properties(arcade-qt PROPERTIES OUTPUT_NAME "_arcade_qt")

if (APPLE)
    set_property(TARGET arcade-qt PROPERTY PREFIX "lib")
    set_property(TARGET arcade-qt PROPERTY OUTPUT_NAME "_arcade_qt.so")
    set_property(TARGET arcade-qt PROPERTY SUFFIX "")
endif()

target_link_libraries(arcade-qt Qt5::Widgets Qt5::Multimedia Qt5::Core)
