cmake_minimum_required(VERSION 3.12)
project(Section10_Decorator)

include_directories(
    include
)

add_executable(DynamicDecorator
    src/DynamicDecorator.cpp)

add_executable(FunctionalDecorator
    src/FunctionalDecorator.cpp)