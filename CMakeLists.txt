cmake_minimum_required(VERSION 2.8)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(SDL2snake)

find_package(SDL2 REQUIRED)

add_executable(SDL2snake src/rungame.cpp)
target_link_libraries(SDL2snake ${SDL2_LIBRARIES})
