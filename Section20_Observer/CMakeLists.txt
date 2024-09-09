cmake_minimum_required(VERSION 3.12)
project(Section20_Observer)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(observer_practice src/observer_practice.cpp)

add_executable(observer_boost_signal src/observer_practice_with_boost_signal.cpp)

add_executable(problem_dependency src/problem_dependency.cpp)

add_executable(Safer_observable src/thread_safety.cpp)

add_executable(excercise src/excercise.cpp)