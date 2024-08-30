cmake_minimum_required(VERSION 3.12)
project(Section5_Prototype)

set(CMAKE_CXX_STANDARD 17)

include_directories(
    include
)

add_executable(RecordKeeper src/RecordKeeper.cpp)
add_executable(Prototype src/Prototype.cpp)
add_executable(PrototypeFactory src/PrototypeFactory.cpp)