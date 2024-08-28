cmake_minimum_required(VERSION 3.12)
project(Section3_Builder)

set(CMAKE_CXX_STANDARD 17)

include_directories(
    include
)

add_executable(LifeWithoutBuilder src/LifeWithoutBuilder.cpp)
add_executable(Builder src/Builder.cpp)
add_executable(FluentBuilder src/FluentBuilder.cpp)
add_executable(GroovyStyleBuilder src/GroovyStyleBuilder.cpp)

add_executable(BuilderFacets 
src/BuilderFacets.cpp
include/Person.cpp
include/PersonBuilder.cpp)