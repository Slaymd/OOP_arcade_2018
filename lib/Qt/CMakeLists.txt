cmake_minimum_required(VERSION 3.5)

project (arcade-qt)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -fPIC")

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/..)

find_package(Qt5Widgets REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

add_library(arcade-qt SHARED QtApi.hpp QtApi.cpp)

#set_target_properties(arcade-qt PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/..")
set_target_properties(arcade-qt PROPERTIES OUTPUT_NAME "_arcade_qt")

target_link_libraries(arcade-qt Qt5::Widgets)
