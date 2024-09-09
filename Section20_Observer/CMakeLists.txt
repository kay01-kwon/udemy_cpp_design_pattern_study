cmake_minimum_required(VERSION 3.12)
project(Section20_Observer)

include_directories(include)

add_executable(observer_practice src/observer_practice.cpp)

add_executable(observer_boost_signal src/observer_practice_with_boost_signal.cpp)