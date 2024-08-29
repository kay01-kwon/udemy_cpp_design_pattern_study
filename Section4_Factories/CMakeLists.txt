cmake_minimum_required(VERSION 3.12)
project(Section4_Factories)

set(CMAKE_CXX_STANDARD 17)

include_directories(
    include
)

add_executable(FactoryMethod src/FactoryMethod.cpp)
add_executable(Factory src/Factory.cpp)
add_executable(InnerFactory src/InnerFactory.cpp)