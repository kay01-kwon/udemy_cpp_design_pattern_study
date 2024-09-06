cmake_minimum_required(VERSION 3.12)
project(Section16_Interpreter)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lexing src/Lexing.cpp)

add_executable(Parsing src/Parsing.cpp)

add_executable(excercise src/excercise.cpp)