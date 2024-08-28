cmake_minimum_required(VERSION 3.12)
project(Section3_Builder)

set(CMAKE_CXX_STANDARD 17)

add_executable(LifeWithoutBuilder src/LifeWithoutBuilder.cpp)
add_executable(Builder src/Builder.cpp)
add_executable(FluentBuilder src/FluentBuilder.cpp)