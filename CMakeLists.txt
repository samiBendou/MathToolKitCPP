cmake_minimum_required(VERSION 3.9)
project(MathToolKitCPP)

set(CMAKE_CXX_STANDARD 11)

enable_testing()
SET(COVERAGE OFF CACHE BOOL "Coverage")

add_subdirectory(MathToolKit)
add_subdirectory(TestsMathToolKitCPP)

set(MATHTOOLKIT_HEADER_PATHS MathToolKit/NAlgebra/header MathToolKit/NAnalysis/header MathToolKit/NGeometry/header)

include_directories(${MATHTOOLKIT_HEADER_PATHS})

add_executable(MathToolKitRun main.cpp)

target_link_libraries(MathToolKitRun NAnalysis NGeometry NAlgebra)