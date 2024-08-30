cmake_minimum_required(VERSION 3.12)
project(Section5_Prototype)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED COMPONENTS serialization)

include_directories(
    include
    ${BOOST_INCLUDE_DIRS}
)

add_executable(RecordKeeper src/RecordKeeper.cpp)
add_executable(Prototype src/Prototype.cpp)
add_executable(PrototypeFactory src/PrototypeFactory.cpp)

add_executable(PrototypeSerialization src/PrototypeSerialization.cpp)
target_link_libraries(PrototypeSerialization Boost::serialization)

add_executable(excercise src/excercise.cpp)