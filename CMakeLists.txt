cmake_minimum_required(VERSION 3.21)
project(hw3)
find_package(Boost REQUIRED)

add_executable(myprog src/main.cpp src/utils.cpp include/utils.hpp)
target_include_directories(myprog PRIVATE ${Boost_INCLUDE_DIRS})
target_include_directories(myprog PRIVATE include)
