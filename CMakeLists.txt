cmake_minimum_required(VERSION 3.9.2)
project(MathToolKit)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)

include_directories(NAlgebra/header)
include_directories(NAnalysis/header)
include_directories(NGeometry/header)

add_subdirectory(NAlgebra)
add_subdirectory(NAnalysis)
add_subdirectory(NGeometry)

add_subdirectory(TestsMathToolKitCPP)

add_executable(MathToolKit ${SOURCE_FILES})

target_link_libraries(MathToolKit NAnalysis NGeometry NAlgebra)