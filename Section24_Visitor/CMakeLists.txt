cmake_minimum_required(VERSION 3.12)
project(Section24_Visitor)
set(CMAKE_CXX_STANDARD 17)

add_executable(IntrusiveVisitor src/IntrusiveVisitor.cpp)
add_executable(ReflectiveVisitor src/ReflectiveVisitor.cpp)