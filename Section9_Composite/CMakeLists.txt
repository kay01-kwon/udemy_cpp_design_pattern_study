cmake_minimum_required(VERSION 3.12)
project(Section9_Composite)

include_directories(
    include
)

add_executable(GeometricShapes 
src/GeometricShapes.cpp)

add_executable(NeuralNetworks
src/NeuralNetworks.cpp)

add_executable(ArrayBackedProperties
src/ArrayBackedProperties.cpp)

add_executable(excercise 
src/excercise.cpp)