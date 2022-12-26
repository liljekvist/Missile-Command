cmake_minimum_required(VERSION 2.8.12)
set(CMAKE_CXX_STANDARD 17)

project("Missile Command")

# Before running, you have to install the SFML-libraries
# sudo apt-get install libsfml-dev

find_package(SFML COMPONENTS graphics audio REQUIRED)

# List directories where headers files can be found
include_directories(sfm include .)

add_compile_options(-std=c++20 -Wall -Wextra)

# Locate all source files
file(GLOB sources *.cpp)
file(GLOB_RECURSE sources_in_source source/*.cpp)
list(APPEND sources ${sources_in_source})

message(STATUS "Sources: ${sources}")

add_executable(run_app ${sources})
target_link_libraries(run_app sfml-graphics sfml-audio)

