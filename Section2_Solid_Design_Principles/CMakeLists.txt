cmake_minimum_required(VERSION 3.12)
project(Section2_Solid_Design_Principles)

set(CMAKE_CXX_STANDARD 17)

add_executable(SingleRespPrinc src/SingleResponsibilityPrinciple.cpp)
add_executable(OpenClosedPrinc src/OpenClosedPrinciple.cpp)
add_executable(LiskovSubPrinc src/LiskovSubstitutionPrinciple.cpp)
add_executable(DepInvPrinc src/DependencyInversionPrinciple.cpp)