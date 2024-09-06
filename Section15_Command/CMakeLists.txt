cmake_minimum_required(VERSION 3.12)
project(Section15_Command)

set(CMAKE_CXX_STANDARD 17)

add_executable(Command src/Command.cpp)

add_executable(UndoOperations src/UndoOperations.cpp)

add_executable(Macro src/Macro.cpp)