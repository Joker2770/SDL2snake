cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)
set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

if(CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "My multi config types" FORCE)
elseif(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE RELEASE)
endif()

project(SDL2snake)

find_package(SDL2 REQUIRED)

file(GLOB SDL2snake_SRCS "src/*.cpp" "src/*.h")
add_executable(${PROJECT_NAME} ${SDL2snake_SRCS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

if(UNIX)
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
endif()
