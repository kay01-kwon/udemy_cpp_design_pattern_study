cmake_minimum_required(VERSION 3.12)
project(Section6_Singleton)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)

include_directories(
    include
    ${GTEST_INCLUDE_DIRS}
)

add_executable(SingletonImpl 
    src/SingletoneImpl.cpp)

add_executable(SingletonTest
    src/TestabilityIssues.cpp)

target_link_libraries(SingletonTest 
    ${GTEST_LIBRARIES} 
    pthread)


add_executable(SingletonTest2
    src/SingletonDepInj.cpp)

target_link_libraries(SingletonTest2 
    ${GTEST_LIBRARIES} 
    pthread)