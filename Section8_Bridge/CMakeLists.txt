cmake_minimum_required(VERSION 3.12)
project(Section8_Bridge)

set(CMAKE_CXX_STANDARD 17)

include_directories(
    include
)

add_executable(Pimple
    include/Person.cpp
    src/Pimple.cpp)

add_executable(BridgeImpl
    src/BridgeImpl.cpp)


add_executable(excercise
    src/excercise.cpp)